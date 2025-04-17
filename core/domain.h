#pragma once

#include <string>
#include <array>
#include <memory>
#include <variant>
#include <chrono>

#include "utilities/encoder.h"

namespace cafeteria_app {
    namespace domain {

        enum class Props : int_fast16_t {
            NAME,
            INDENTIFIER,
            GENDER,
            GROUP    
        };

        namespace props {
            
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

            namespace interfaces {
                
                //class interface
                template <typename T>
                struct Component {
                    typedef T Type;
                    T value;
                protected:
                    virtual ~Component() = default;
                };

                struct Nameable : Component<props::Name> {
                    void SetName(const std::string& name) {
                        encoder::ascii::EncodeDataInIterable(name.begin(), name.end(), value.begin(), value.size());
                    }

                    std::string GetName() const {
                        return encoder::ascii::DecodeDataFromIterable(value.begin(), value.end());
                    }

                    virtual ~Nameable() = default;
                };

                struct Identifiable : Component<props::Identifier> {
                    void SetIdentifier(const std::string& identifier) {
                        const static std::hash<std::string> hasher;
                        this -> value = hasher(identifier);
                    }

                    Type GetIdentifier() const {
                        return value;
                    }

                    virtual ~Identifiable() = default;
                };

                struct Genderable : Component<props::Gender> {
                    void SetGender(Type gender) {
                        this -> value = gender;
                    }

                    Type GetGender() const {
                        return value;
                    }

                    virtual ~Genderable() = default;
                };

                struct Groupable : Component<props::Group> {
                    void SetGroup(Type group) {
                        this -> value = group;
                    }

                    Type GetGroup() const {
                        return value;
                    }

                    virtual ~Groupable() = default;
                };
            } //namespace interfaces
        } //namespace props


        enum class Users : char {
            STUDENT
        };

        namespace users {
            using namespace props::interfaces;

            //class Interface
            class User {
            public:
                virtual Users GetUserType() = 0;

                virtual ~User() = default;
            };

            class Student final : public User
                                , public Identifiable
                                , public Nameable
                                , public Genderable
                                , public Groupable {
            public:
                inline Student() = default;
                inline Users GetUserType() override {
                    return Users::STUDENT;
                }
            };

            inline static std::unique_ptr<User> MakeUser(Users user_type) {
                if (user_type == Users::STUDENT) {
                    return std::make_unique<Student>();
                }

                return nullptr;
            }
        } //namespace users

        //app types
        using UserPtr = std::unique_ptr<users::User>;
        using Size = size_t;
        using Index = size_t;
        using TimePoint = std::time_t;

        struct Session {
            TimePoint time;
            Index first;
            Index last;
        };
        

    } // namespace domain
} // namespace cafeteria_app


