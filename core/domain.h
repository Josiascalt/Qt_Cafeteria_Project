#pragma once

#include <string>
#include <array>
#include <memory>
#include <variant>

#include "labels.h"
#include "utilities\encoder.h"

namespace cafeteria_app {
    namespace domain {

        namespace interfaces {
            //Base class
            struct Printable {
                virtual Label PrintLabel() const = 0;
                virtual std::string PrintValue() const = 0;
            protected:
                virtual ~Printable() = default;
            };

            //Base class for all core types
            template <typename T>
            struct CoreType : Printable {
                typedef T Type;

                Type value;
            protected:
                virtual ~CoreType() = default;
            };

            //Raw Datatype
            using Identifier = size_t;
            //Struct interface
            struct Identifiable : CoreType<Identifier> {
                Label PrintLabel() const override;
                std::string PrintValue() const override;
            };

            //Raw Datatype
            using Name = std::array<encoder::ascii::Item, 10>;
            //Struct interface
            struct Nameable : CoreType<Name> {
                static Name StringToName(const std::string& str);
            
                Label PrintLabel() const override;
                std::string PrintValue() const override;
            };
            
            //Raw Datatype
            enum class Gender : bool {
                MALE,
                FEMALE
            };
            //Struct interface
            struct Genderable : CoreType<Gender> {
                Label PrintLabel() const override;
                std::string PrintValue() const override;
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
                    std::string PrintValue() const override;
                };

                struct WrappedTAC : Wrapper<TAC>, Printable {
                    Label PrintLabel() const override;
                    std::string PrintValue() const override;
                };

                struct WrappedTAIS : Wrapper<TAIS>, Printable {
                    Label PrintLabel() const override;
                    std::string PrintValue() const override;
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
            //Struct interface
            struct Groupable : CoreType<Group> {
                Label PrintLabel() const override;
                std::string PrintValue() const override;
            };

            template <typename Obj, typename Func>
            static void IterateAcrossInterfaces(Obj* obj, Func func) {
                if (auto identifiable = dynamic_cast<Identifiable*>(obj)) {
                    func(identifiable);
                }

                if (auto nameable = dynamic_cast<Nameable*>(obj)) {
                    func(nameable);
                }

                if (auto genderable = dynamic_cast<Genderable*>(obj)) {
                    func(genderable);
                }

                if (auto groupable = dynamic_cast<Groupable*>(obj)) {
                    func(groupable);
                }
            }
        } //namespace interfaces

        namespace users {
            enum class Users : char {
                STUDENT
            };
            
            using namespace interfaces;

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

        

        /*struct Session {
            TimePoint time;
            Index first;
            Index last;
        };*/
        

    } // namespace domain
} // namespace cafeteria_app


