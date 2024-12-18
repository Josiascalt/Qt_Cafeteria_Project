#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#pragma once

#include "domain.h"
#include "user_catalogue.h"
#include "backup_handler.h"

namespace catalogue {
    namespace request_handler {

        using namespace domain::type_naming;

        class RequestHandler {
        public:
            RequestHandler(const backup::UserDataPaths& paths);
            bool AddUser(UserPtr&& user);
            const UserPtr& GetUserByIdentifier(domain::components::types::Identifier identifier);
            const std::deque<UserPtr>& GetUsers() const;
        private:
            backup::UserDataBackup user_data_;
            database::UserCatalogue catalogue_;
        };
    } //namespace request_handler
} //namespace catalogue
#endif // REQUEST_HANDLER_H
