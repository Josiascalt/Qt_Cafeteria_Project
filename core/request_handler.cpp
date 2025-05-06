#include <utility>

#include "request_handler.h"
#include "external\qr_maker\api.h"

namespace cafeteria_app {
    namespace request {
        namespace exceptions {
            struct InvalidUser : public std::invalid_argument {
                using std::invalid_argument::invalid_argument;
            };
        } //namespace exceptions

        //class RequestHandler member functions definition
        RequestHandler::RequestHandler(fs::path path)
        : database_(std::move(path))
        , catalogue_(database_.Deserialize())
        {

        }

        void RequestHandler::AddUser(UserPtr&& user) {
            if (!catalogue_.HasUser(user)) {
                throw exceptions::InvalidUser{"User with identifier " + std::to_string(user->GetIdentifier()) + " already exists."};
            }

            database_.Serialize(user.get());
            catalogue_.AddUser(std::move(user));
        }

        const UserPtr& RequestHandler::GetUserByIdentifier(domain::interfaces::Identifier identifier) {
            return catalogue_.GetUserByIdentifier(identifier);
        }

        /*void RequestHandler::GenerateUserQrCode(const database::UserCatalogue::RawIdentifier& identifier) {
            std::cout << '\n' << qr_maker::GenerateSvgQrCode(identifier) << '\n';
        }*/

    } //namespace request
} //namespace cafeteria_app

