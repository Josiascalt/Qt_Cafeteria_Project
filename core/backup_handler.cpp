#include <utility>

#include "backup_handler.h"
#include "utilities\json\json.h"

namespace cafeteria_app {
    namespace backup {
        //class UserDataBackup member functions definition
        UserDataBackup::UserDataBackup(const json::Dict& path_settings)
        : paths_settings_(path_settings)
        , types_(file_handler::CreatePathObject(labels::TYPES_METADATA_FILE))
        {
        }

        /*std::deque<UserPtr> UserDataBackup::Deserialize() {
            std::deque<UserPtr> result;
            auto total_users = user_types_.GetSize();

            for (Size index = 0; index < total_users; index++) {
                auto user = DeserializeMetadata();
                if (user) {

                    if (auto identifier = dynamic_cast<domain::interfaces::Identifiable*>(user.get())) {
                        identifiers_.Read(&identifier->value);
                    }

                    if (auto name = dynamic_cast<domain::interfaces::Nameable*>(user.get())) {
                        names_.Read(&name->value);
                    }

                    if (auto gender = dynamic_cast<domain::interfaces::Genderable*>(user.get())) {
                        genders_.Read(&gender->value);
                    }

                    if (auto group = dynamic_cast<domain::interfaces::Groupable*>(user.get())) {
                        groups_.Read(&group->value);
                    }

                    result.push_back(std::move(user));
                }
                else {
                    throw exceptions::InvalidPtr{};

                }
            }

            return result;
        }

        UserPtr UserDataBackup::DeserializeMetadata() {
            domain::Users user_type = {};

            user_types_.Read(&user_type);

            return domain::users::MakeUser(user_type);
        }*/


    } //namespace backup
} //namespace cafeteria_app
