#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#pragma once

#include "type_aliases.h"
#include "domain.h"
#include "user_catalogue.h"
#include "database_handler.h"
#include "utilities\file_handler\file_handler.h"

namespace cafeteria_app {
    namespace request {
        using namespace type_aliases;

        class RequestHandler {
        public:
            RequestHandler(fs::path path);

            void AddUser(UserPtr&& user);
            const UserPtr& GetUserByIdentifier(domain::interfaces::Identifier identifier);
            
        private:
            //void GenerateUserQrCode(const database::UserCatalogue::RawIdentifier& identifier);
        private:
            database::UserDatabase database_;
            catalogue::UserCatalogue catalogue_;
        };
    } //namespace request
} //namespace cafeteria_app
#endif // REQUEST_HANDLER_H
