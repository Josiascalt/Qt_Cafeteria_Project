#include <utility>

#include "labels.h"
#include "file_handler.h"
#include "backup_handler.h"

using namespace std::literals;

namespace cafeteria_app {
    namespace backup {
        //class UserDataBackup member functions definition
        UserDataBackup::UserDataBackup(fs::path path)
        : target_(std::move(path))
        {
            //set metadata files
            auto metadata_folder = file_handler::MakeValidPath(target_ / labels::DATABASE_PARENT_FOLDER);
            this->types_.SetFilename(metadata_folder/ fs::path(labels::TYPES_METADATA_FILE));
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
