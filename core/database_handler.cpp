#include <utility>

#include "database_handler.h"
#include "labels.h"
#include "domain.h"
#include "utilities\file_handler\file_handler.h"

namespace cafeteria_app {
    namespace database {
        //class UserDatabase member functions definition
        UserDatabase::UserDatabase(fs::path path)
        : target_(std::move(path))
        {
            //set metadata files
            auto metadata_folder = file_handler::MakeValidPath(target_ / labels::METADATA_FOLDER);
            this->types_.SetFilename(metadata_folder/ fs::path(labels::TYPES_METADATA_FILE));
        }

        UserPtr UserDatabase::DeserializeMetadata() {
            domain::users::Users user_type;

            this->types_.Read(&user_type);

            return domain::users::MakeUser(user_type);
        }

        std::deque<UserPtr> UserDatabase::Deserialize() {
            std::deque<UserPtr> result;

            auto total_users = types_.GetSize();

            for (size_t index = 0; index < total_users; index++) {
                auto user = DeserializeMetadata();

                if (user) {
                    domain::interfaces::IterateAcrossInterfaces(user.get(), [&](auto* interface) {
                        file_handler::BinaryFile<decltype(interface->value)> f(this->target_ / fs::path(interface->PrintLabel()));
                        f.Read(&interface->value, 1, index);
                    });

                    result.push_back(std::move(user));
                }
                else {
                    throw std::invalid_argument("Invalid user pointer.");
                }
            }

            return result;
        }

        


    } //namespace database
} //namespace cafeteria_app
