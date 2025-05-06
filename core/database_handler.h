#ifndef BACKUP_HANDLER_H
#define BACKUP_HANDLER_H
#pragma once

#include <deque>
#include <exception>

#include "domain.h"
#include "type_aliases.h"
#include "utilities\file_handler\file_handler.h"

namespace cafeteria_app {
    namespace database {
        using namespace cafeteria_app::type_aliases;

        class UserDatabase {
        public:
            UserDatabase(fs::path path);

            template <typename UserBased>
            void Serialize(UserBased* user) {
                if (!user) {
                    throw std::invalid_argument("Invalid user pointer.");
                }
                //metadata
                SerializeMetadata(user);

                //data
                domain::interfaces::IterateAcrossInterfaces(user, [&](auto* interface) {
                    file_handler::BinaryFile<decltype(interface->value)> f(this->target_ / fs::path(interface->PrintLabel()));
                    f.Write(&interface->value);
                });

            }

            std::deque<UserPtr> Deserialize();

        private:
            inline void SerializeMetadata(domain::users::User* user) {

                auto user_type = user->GetUserType();

                types_.Write(&user_type);
            }

            UserPtr DeserializeMetadata();

        private:
            const fs::path target_;

            //Metadata
            file_handler::BinaryFile<domain::users::Users> types_;
        };

        /*class RecordDataBackup {
        public:
            void Serialize(domain::props_interfaces::Identifiable* identifiable, TimePoint timepoint) {
                if (!identifiable) {
                    throw exceptions::{};
                    
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
    } //namespace database
} //namespace cafeteria_app
#endif // BACKUP_HANDLER_H
