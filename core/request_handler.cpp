#include <utility>
#include <iostream>

#include "request_handler.h"
#include "..\..\..\proyecto_cafeteria\external\QR-Code-generator\pluggin.hpp"

namespace cafeteria_app {
    namespace request_handler {
        //class RequestHandler member functions definition
        RequestHandler::RequestHandler(const backup::UserDataPaths& paths)
            : user_data_(paths)
            , catalogue_(user_data_.Deserialize())
        {

        }

        bool RequestHandler::AddUser(UserPtr&& user) {
            user_data_.Serialize(user.get());
            auto raw_identifier = catalogue_.AddUser(std::move(user));
            this->GenerateUserQrCode(raw_identifier);
            
            return true;
        }

        const UserPtr& RequestHandler::GetUserByIdentifier(domain::components::types::Identifier identifier) {
            return catalogue_.GetUserByIdentifier(identifier);
        }

        const std::deque<UserPtr>& RequestHandler::GetUsers() const {
            return catalogue_.GetUsers();
        }

        void RequestHandler::GenerateUserQrCode(const database::UserCatalogue::RawIdentifier& identifier) {
            std::cout << '\n' << qrcodegen::pluggin::GenerateSvgQrCode(identifier) << '\n';
        }

    } //namespace request_handler
} //namespace cafeteria_app
