#include <utility>
#include <deque>

#include "user_catalogue.h"
#include "domain.h"

namespace cafeteria_app {
namespace catalogue {

        //UserCatalogue class member functions definition
        UserCatalogue::UserCatalogue() = default;
        UserCatalogue::UserCatalogue(std::deque<UserPtr>&& users)
        {
            for (auto&& user : users) {
                this->AddUser(std::move(user));
            }
        }

        void UserCatalogue::AddUser(UserPtr&& user) {
            if (user) {
                users_.push_back(std::move(user));
                identifier_to_user_[users_.back()->GetIdentifier()] = users_.size() - 1;
            } else {
                throw std::invalid_argument("Invalid user pointer.");
            }
        }
        
        bool UserCatalogue::HasUser(const UserPtr& user) const {
            return user ? identifier_to_user_.count(user->GetIdentifier()) : throw std::invalid_argument("Invalid user pointer.");
        }

        const UserPtr& UserCatalogue::GetUserByIdentifier(domain::interfaces::Identifier identifier) const {
            static const UserPtr dummy_user;
            auto result = identifier_to_user_.find(identifier);
            return result == identifier_to_user_.end() ? dummy_user : users_[result->second];
        }
    } //namespace catalogue
} //namespace cafeteria_app
