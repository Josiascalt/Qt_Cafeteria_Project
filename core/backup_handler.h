#ifndef BACKUP_HANDLER_H
#define BACKUP_HANDLER_H
#pragma once

#include <deque>
#include <exception>

#include "domain.h"
#include "type_aliases.h"
#include "file_handler.h"
#include "utilities\json\json.h"

namespace cafeteria_app {
    namespace backup {
        using namespace cafeteria_app::type_aliases;
        
        namespace exceptions {
            struct InvalidPtr {};
        }

        class UserDataBackup {
        public:
            UserDataBackup(const json::Dict& path_settings);

            template <typename UserBased>
            void Serialize(UserBased* user) {
                if (!user) {
                    throw std::invalid_argument("Invalid user pointer.");
                }
                //metadata
                SerializeMetadata(user);

                //data
                domain::interfaces::IterateAcrossInterfaces(user, [&](auto* interface) {
                    auto path = file_handler::CreatePathObject((interface->PrintLabel() + ".dat"s));
                    file_handler::BinaryFile<decltype(interface->value)> f(path);
                    f.Write(&interface->value);
                });

            }

            //std::deque<UserPtr> Deserialize();

        private:
            template <typename UserBased>
            inline void SerializeMetadata(UserBased* user) {
                domain::users::Users user_type = user->GetUserType();

                types_.Write(&user_type);
            }

            //UserPtr DeserializeMetadata();

        private:
            const json::Dict& paths_settings_;

            //Metadata
            file_handler::BinaryFile<domain::users::Users> types_;
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
