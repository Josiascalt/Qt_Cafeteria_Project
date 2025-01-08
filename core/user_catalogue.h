#ifndef USER_CATALOGUE_H
#define USER_CATALOGUE_H
#pragma once

#include <string>
#include <deque>
#include <unordered_map>


#include "domain.h"

namespace catalogue {
    namespace database {

        using namespace domain::type_naming;
        using namespace domain::components;

        class UserCatalogue {
        public:
            using RawIdentifier = std::string;
        public:
            UserCatalogue();
            UserCatalogue(std::deque<UserPtr>&& users);

            //bool HasUser(const UserPtr& user) const;
            RawIdentifier AddUser(UserPtr&& user);
            const UserPtr& GetUserByIdentifier(types::Identifier identifier) const;
            const std::deque<UserPtr>& GetUsers() const;

        private:
            RawIdentifier AssignIdentifier(Identifiable* identifiable_user) const;

        private:
            std::deque<UserPtr> users_;
            std::unordered_map<types::Identifier, Index> identifier_to_user_;
        };
    } //namespace database
} //namespace catalogue
#endif // USER_CATALOGUE_H
