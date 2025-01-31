#pragma once

#include "utilities/encoder.h"

#include <string>
#include <array>
#include <memory>
#include <variant>
#include <chrono>


namespace cafeteria_app {
    namespace domain {
        /*
            Every data members of every single struct/class declared within the namespace compound_types
            should be declared in the namespace "components", in order to keep all the basic types
            in one place. This process makes easier the handling of types for storing them properly.

            | | | | | | | | | |
            v v v v v v v v v v
        */

        namespace components {
            namespace types {
            using Name = std::array<encoder::ascii::Item, 10>;

            using Identifier = size_t;

            enum class Gender : bool {
                MALE,
                FEMALE
            };

            class Group {
            public:
                enum class TAA : char {
                    MONOSTATE,
                    FIRST_GRADE,
                    SECOND_GRADE,
                    THIRD_GRADE
                };

                enum class TAC : char {
                    MONOSTATE,
                    BILINGUAL_BUSINESS_DEPARTMENT,
                    HEALTH_EDUCATION_DEPARTMENT,
                    MUSIC_DEPARTMENT,
                    THEOLOGY_DEPARTMENT
                };

                enum class TAIS : char {
                    MONOSTATE,
                    SEVENTH_GRADE,
                    EIGHTH_GRADE,
                    NINTH_GRADE,
                    TENTH_GRADE,
                    ELEVENTH_GRADE,
                    TWELFTH_GRADE
                };

                Group() = default;

                template <class GroupName>
                Group(GroupName group)
                    : group_(group)
                {
                }

                template <class GroupName>
                Group& operator=(GroupName group) {
                    group_ = group;
                    return *this;
                }

                bool IsTAC() const;
                bool IsTAIS() const;
                bool IsTAA() const;
                TAC GetAsTAC() const;
                TAIS GetAsTAIS() const;
                TAA GetAsTAA() const;

                bool operator==(const Group& other) const;
                bool operator!=(const Group& other) const;

            private:
                std::variant<TAC, TAIS, TAA> group_;
            };

            } //namespace types

            //class interface
            template <typename T>
            struct Component {
                typedef T Type;
                T value;
            protected:
                virtual ~Component() = default;
            };

            struct Nameable : Component<types::Name> {
                void SetName(const std::string& name) {
                    encoder::ascii::EncodeDataInIterable(name.begin(), name.end(), value.begin(), value.size());
                }

                std::string GetName() const {
                    return encoder::ascii::DecodeDataFromIterable(value.begin(), value.end());
                }

                virtual ~Nameable() = default;
            };

            struct Identifiable : Component<types::Identifier> {
                void SetIdentifier(const std::string& identifier) {
                    const static std::hash<std::string> hasher;
                    this -> value = hasher(identifier);
                }

                Type GetIdentifier() const {
                    return value;
                }

                virtual ~Identifiable() = default;
            };

            struct Genderable : Component<types::Gender> {
                void SetGender(Type gender) {
                    this -> value = gender;
                }

                Type GetGender() const {
                    return value;
                }

                virtual ~Genderable() = default;
            };

            struct Groupable : Component<types::Group> {
                void SetGroup(Type group) {
                    this -> value = group;
                }

                Type GetGroup() const {
                    return value;
                }

                virtual ~Groupable() = default;
            };
        } //namespace components

        /*
            Every single class/struct should be declared in the namespace compound_types,
            and every data member type should be taken from the namespace components.
            In case that the desired datatype is not declared in the namespace component,
            it must be declared there and then make use of it as a data member type
            in a class/struct in the namespace compound_types.
            | | | | | | | | | |
            v v v v v v v v v v
        */

        namespace compound_types {
        /*
            Every single final class/struct should be declared in the namespace final_types.
            All final types should he under the UserType interface.
            Final types are the classes/structs available for the user.
            | | | | | | | | | |
            v v v v v v v v v v
        */

        using namespace components;

        enum class UserType : char {
            MONOSTATE,
            STUDENT
        };

        //class Interface
        class User {
        public:
            virtual UserType GetUserType() = 0;

            virtual ~User() = default;
        };

        class Student final : public User
            , public Identifiable
            , public Nameable
            , public Genderable
            , public Groupable {
        public:
            inline Student() = default;
            inline UserType GetUserType() override {
                return UserType::STUDENT;
            }
        };

        inline static std::unique_ptr<User> MakeUser(UserType user_type) {
            if (user_type == UserType::STUDENT) {
                return std::make_unique<Student>();
            }

            return nullptr;
        }
        } //namespace compound_types

        namespace standardized_types {
            using UserPtr = std::unique_ptr<compound_types::User>;
            using Size = size_t;
            using Index = size_t;
            using TimePoint = std::time_t;

            struct Session {
                TimePoint time;
                Index first;
                Index last;
            };
        } //namespace catalogue_naming

    } // namespace domain
} // namespace cafeteria_app


