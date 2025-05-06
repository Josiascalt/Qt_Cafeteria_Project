#ifndef USER_CATALOGUE_H
#define USER_CATALOGUE_H
#pragma once

#include <string>
#include <deque>
#include <unordered_map>

#include "domain.h"
#include "type_aliases.h"

namespace cafeteria_app {
    namespace catalogue {

        using namespace type_aliases;

        class UserCatalogue {
        public:
            UserCatalogue();
            UserCatalogue(std::deque<UserPtr>&& users);

            bool HasUser(const UserPtr& user) const;
            void AddUser(UserPtr&& user);
            const UserPtr& GetUserByIdentifier(domain::interfaces::Identifier identifier) const;
        private:
            std::deque<UserPtr> users_;
            std::unordered_map<domain::interfaces::Identifier, Index> identifier_to_user_;
        };
    } //namespace catalogue
} //namespace cafeteria_app
#endif // USER_CATALOGUE_H
