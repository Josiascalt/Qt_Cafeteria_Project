#ifndef BACKUP_HANDLER_H
#define BACKUP_HANDLER_H
#pragma once

#include <deque>
#include "domain.h"
#include "file_handler.h"

namespace cafeteria_app {
    namespace backup {
        using namespace domain;
        
        namespace exceptions {
        struct InvalidPtr {};
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
                    throw exceptions::InvalidPtr{};
                }
                //metadata
                SerializeMetadata(user);
                //data
                if (auto identifier = dynamic_cast<domain::interfaces::Identifiable*>(user)) {
                    identifiers_.Write(&identifier->value);
                }

                if (auto name = dynamic_cast<domain::interfaces::Nameable*>(user)) {
                    names_.Write(&name->value);
                }

                if (auto gender = dynamic_cast<domain::interfaces::Genderable*>(user)) {
                    genders_.Write(&gender->value);
                }

                if (auto group = dynamic_cast<domain::interfaces::Groupable*>(user)) {
                    groups_.Write(&group->value);
                }
            }

            std::deque<UserPtr> Deserialize();

        private:
            template <typename T>
            inline void SerializeMetadata(T* user) {
                domain::users::Users user_type = user->GetUserType();
                user_types_.Write(&user_type);
            }

            UserPtr DeserializeMetadata();

        private:
            //Metadata
            file_handler::BinaryFile<domain::Users> user_types_;
            //Data
            file_handler::BinaryFile<domain::interfaces::interfaces::Nameable::Type> names_;
            file_handler::BinaryFile<domain::interfaces::interfaces::Identifiable::Type> identifiers_;
            file_handler::BinaryFile<domain::interfaces::interfaces::Genderable::Type> genders_;
            file_handler::BinaryFile<domain::interfaces::interfaces::Groupable::Type> groups_;
        };

        /*class RecordDataBackup {
        public:
            void Serialize(domain::props_interfaces::Identifiable* identifiable, TimePoint timepoint) {
                if (!identifiable) {
                    throw exceptions::InvalidPtr{};
                    
                } 

                auto identifier = identifiable -> value;
                this -> identifiers_.Write(&identifier);
                this -> timepoints_.Write(&timepoint);

            }

            void Deserialize();

            ~RecordDataBackup() {
            }

        private:
            void SerializeMetadata() {
                
            }

            void DeserializeMetadata() {

            }

        private:
            //Metadata
            file_handler::BinaryFile<Session> sessions_;
            //Data
            file_handler::BinaryFile<domain::props_interfaces::Identifiable::Type> identifiers_;
            file_handler::BinaryFile<TimePoint> timepoints_;
        };*/
    } //namespace backup
} //namespace cafeteria_app
#endif // BACKUP_HANDLER_H
