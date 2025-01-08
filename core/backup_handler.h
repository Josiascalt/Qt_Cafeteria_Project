#ifndef BACKUP_HANDLER_H
#define BACKUP_HANDLER_H
#pragma once

#include <deque>
#include <chrono>

#include "domain.h"
#include "file_handler.h"

namespace catalogue {
    namespace backup {

        using namespace domain::type_naming;

        namespace exceptions {
        struct InvalidUserPtr {};
        }

        struct UserDataPaths {
            struct Metadata {
                fs::path queue;
            };

            Metadata metadata;
            fs::path names;
            fs::path identifiers;
            fs::path genders;
            fs::path groups;

            UserDataPaths& SetMetadataPaths(fs::path queue_path);
            UserDataPaths& SetNamesPath(fs::path names_path);
            UserDataPaths& SetIdentifiersPath(fs::path identifiers_path);
            UserDataPaths& SetGendersPath(fs::path genders_path);
            UserDataPaths& SetGroupsPath(fs::path groups_path);
        };

        class UserDataBackup {
        public:
            UserDataBackup(const UserDataPaths& user_data);

            template <typename T>
            inline void Serialize(T* user) {
                if (!user) {
                    throw exceptions::InvalidUserPtr{};
                }
                //metadata
                SerializeMetadata(user);
                //data
                if (auto identifier = dynamic_cast<domain::components::Identifiable*>(user)) {
                    identifiers_.Write(&identifier->value);
                }

                if (auto name = dynamic_cast<domain::components::Nameable*>(user)) {
                    names_.Write(&name->value);
                }

                if (auto gender = dynamic_cast<domain::components::Genderable*>(user)) {
                    genders_.Write(&gender->value);
                }

                if (auto group = dynamic_cast<domain::components::Groupable*>(user)) {
                    groups_.Write(&group->value);
                }
            }

            std::deque<UserPtr> Deserialize();

        private:
            template <typename T>
            inline void SerializeMetadata(T* user) {
                domain::compound_types::UserType user_type = user->GetUserType();
                user_types_.Write(&user_type);
            }

            UserPtr DeserializeMetadata();

        private:
            //Metadata
            file_handler::BinaryFile<domain::compound_types::UserType> user_types_;
            //Data
            file_handler::BinaryFile<domain::components::Nameable> names_;
            file_handler::BinaryFile<domain::components::Identifiable> identifiers_;
            file_handler::BinaryFile<domain::components::Genderable> genders_;
            file_handler::BinaryFile<domain::components::Groupable> groups_;
        };

        class RecordDataBackup {
        public:
            void Serialize(domain::components::Identifiable* identifiable) {
                if (identifiable) {
                    identifiable -> GetIdentifier();
                }

                auto now = std::chrono::system_clock::now();
                auto formatted_time = std::chrono::system_clock::to_time_t(now);
                auto localtime = *std::localtime(&formatted_time);


                
            }

            void Deserialize();
        private:
            struct Session {
                std::time_t date;
                Index first;
                Index last;
            };

            void SerializeMetadata() {

            }

            void DeserializeMetadata() {

            }

        private:
            //Cache
            Session current_session_;
            //Metadata
            file_handler::BinaryFile sessions_;
            //Data
            file_handler::BinaryFile identifiers_;
            file_handler::BinaryFile timepoints_;
        };
    } //namespace backup
} //namespace catalogue
#endif // BACKUP_HANDLER_H
