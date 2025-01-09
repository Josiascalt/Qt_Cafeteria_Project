#include <utility>
#include <deque>

#include "user_catalogue.h"
#include "utilities/utilities.h"

namespace cafeteria_app {
namespace database {
    using namespace domain::standardized_types;
    using namespace domain::components;

        //UserCatalogue class member functions definition
        UserCatalogue::UserCatalogue() = default;
        UserCatalogue::UserCatalogue(std::deque<UserPtr>&& users)
        {
            for (auto&& user : users) {
                this->AddUser(std::move(user));
            }
        }

        /*bool UserCatalogue::HasUser(const UserPtr& user) const {
            using namespace domain::components;
            if (user) {
                if (auto identifier = dynamic_cast<const Identifiable*>(user.get());
                    identifier && identifier_to_user_.count(identifier->GetIdentifier())) {
                    return false;
                }

                return true;
            }

            return false;
        }*/

        UserCatalogue::RawIdentifier UserCatalogue::AddUser(UserPtr&& user) {
            if (user) {
                users_.push_back(std::move(user));

                if (auto identifier = dynamic_cast<Identifiable*>(users_.back().get())) {
                    auto raw_identifier = this->AssignIdentifier(identifier);
                    identifier_to_user_[identifier->GetIdentifier()] = users_.size() - 1;
                    return raw_identifier;
                }
            }
            return RawIdentifier{}; 
        }

        const UserPtr& UserCatalogue::GetUserByIdentifier(types::Identifier identifier) const {
            static const UserPtr dummy_user;
            auto result = identifier_to_user_.find(identifier);
            return result == identifier_to_user_.end() ? dummy_user : users_[result->second];
        }

        const std::deque<UserPtr>& UserCatalogue::GetUsers() const {
            return users_;
        }

        UserCatalogue::RawIdentifier UserCatalogue::AssignIdentifier(Identifiable* identifiable_user) const {
            std::string raw_identifier;

            while (true) {
                raw_identifier = utilities::GenerateRandomStr(100);
                identifiable_user->SetIdentifier(raw_identifier);

                if (!identifier_to_user_.count(identifiable_user->GetIdentifier())) {
                    break;
                }
            }

            return raw_identifier;
        }

    } //namespace database
} //namespace cafeteria_app
