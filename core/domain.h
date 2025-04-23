#pragma once

#include <string>
#include <array>
#include <memory>
#include <variant>
#include <chrono>

#include "text_vars.h"
#include "utilities\encoder.h"

namespace cafeteria_app {
    namespace domain {
        
        class Printable {
        public:
            virtual Label PrintLabel() const = 0;
            virtual Text PrintValue() const = 0;
        protected:
            virtual ~Printable() = default;
        };

        namespace core_types {

            template <typename T>
            class CoreType : public Printable {
            public:
                typedef T Type;

                virtual void SetValue(Type value) {
                    value_ = std::move(value);
                }

                virtual const Type& GetValue() const {
                    return value_;
                }
                
                virtual Type* GetRawPtr() {
                    return &value_;
                }

            protected:
                virtual ~CoreType() = default;
            protected:
                Type value_;
            };

            //Raw Datatype
            using Name = std::array<encoder::ascii::Item, 10>;
            //Class interface
            class Nameable : public CoreType<Name> {
            public:
                static Name StringToName(const std::string& str);
            
            public:
                Label PrintLabel() const override;
                Text PrintValue() const override;
            };

            //Raw Datatype
            using Identifier = size_t;
            //Class interface
            class Identifiable : public CoreType<Identifier> {
            public:
                Label PrintLabel() const override;
                Text PrintValue() const override;
            };
            
            //Raw Datatype
            enum class Gender : bool {
                MALE,
                FEMALE
            };
            //Class interface
            class Genderable : public CoreType<Gender> {
            public:
                Label PrintLabel() const override;
                Text PrintValue() const override;
            };

            //Raw Datatype
            class Group {
            public: 
                //Subgroups
                enum class TAA : char {
                    DEFAULT,
                    FIRST_GRADE,
                    SECOND_GRADE,
                    THIRD_GRADE
                };

                enum class TAC : char {
                    DEFAULT,
                    BILINGUAL_BUSINESS_DEPARTMENT,
                    HEALTH_EDUCATION_DEPARTMENT,
                    MUSIC_DEPARTMENT,
                    THEOLOGY_DEPARTMENT
                };

                enum class TAIS : char {
                    DEFAULT,
                    SEVENTH_GRADE,
                    EIGHTH_GRADE,
                    NINTH_GRADE,
                    TENTH_GRADE,
                    ELEVENTH_GRADE,
                    TWELFTH_GRADE
                };

                //Wrapped Subgroups
                template <typename Subgroup>
                struct Wrapper {
                    Subgroup value;
                protected:
                    virtual ~Wrapper() = default;
                };

                struct WrappedTAA : Wrapper<TAA>, Printable {
                    Label PrintLabel() const override;
                    Text PrintValue() const override;
                };

                struct WrappedTAC : Wrapper<TAC>, Printable {
                    Label PrintLabel() const override;
                    Text PrintValue() const override;
                };

                struct WrappedTAIS : Wrapper<TAIS>, Printable {
                    Label PrintLabel() const override;
                    Text PrintValue() const override;
                };
            
            private:
                using RawType = std::variant<Group::TAC, Group::TAIS, Group::TAA>;
            public:
                Group() = default;

                template <typename Subgroup>
                Group(Subgroup group)
                    : group_(group)
                {
                }

                template <typename Subgroup>
                Group& operator=(Subgroup group) {
                    group_ = group;
                    return *this;
                }

                bool IsTAA() const;
                bool IsTAC() const;
                bool IsTAIS() const;
                
                WrappedTAA GetAsTAA() const;
                WrappedTAC GetAsTAC() const;
                WrappedTAIS GetAsTAIS() const;
            
            public:
                bool operator==(const Group& other) const;
                bool operator!=(const Group& other) const;

                struct Hasher {
                    size_t operator()(const Group& group) const {
                        return static_cast<size_t>(std::hash<RawType>{}(group.group_));
                    }
                };

            private:
                friend struct Group::Hasher;
            private:
                RawType group_;
            };
            //Class interface
            class Groupable : public CoreType<Group> {
            public:
                Label PrintLabel() const override;
                Text PrintValue() const override;
            };
        } //namespace core_types


        enum class Users : char {
            STUDENT
        };

        namespace users {
            using namespace core_types;

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


