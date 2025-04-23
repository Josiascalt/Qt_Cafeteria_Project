#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#pragma once

#include "domain.h"
#include "user_catalogue.h"
#include "backup_handler.h"

namespace cafeteria_app {
    namespace request_handler {

        using namespace domain::types;

        class RequestHandler {
        public:
            RequestHandler(const backup::UserDataPaths& paths);

            bool AddUser(UserPtr&& user);
            const UserPtr& GetUserByIdentifier(domain::interfaces::core_types::Identifier identifier);
            const std::deque<UserPtr>& GetUsers() const;

        private:
            void GenerateUserQrCode(const database::UserCatalogue::RawIdentifier& identifier);
        private:
            backup::UserDataBackup user_data_;
            database::UserCatalogue catalogue_;
        };
    } //namespace request_handler
} //namespace cafeteria_app
#endif // REQUEST_HANDLER_H
