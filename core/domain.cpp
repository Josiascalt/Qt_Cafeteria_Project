#include <string>
#include <variant>

#include "domain.h"
#include "utilities\encoder.h"
#include "labels.h"

namespace cafeteria_app {
    namespace domain {
        namespace interfaces {
        //Struct Namable member functions definition
            Name Nameable::StringToName(const std::string& str) {
                Name name;
                encoder::ascii::EncodeDataInIterable(str.begin(), str.end(), name.begin(), name.size());
                return name;
            }
            
            Label Nameable::PrintLabel() const {
                return labels::NAME_LABEL;
            }

            std::string Nameable::PrintValue() const {
                return encoder::ascii::DecodeDataFromIterable(this -> value.begin(), this -> value.end());
            }
            
        //Struct Identifiable member functions definition
            Label Identifiable::PrintLabel() const {
                return labels::IDENTIFIER_LABEL;
            }

            std::string Identifiable::PrintValue() const {
                return std::to_string(this -> value);
            }

        //Struct Genderable member functions definition
            Label Genderable::PrintLabel() const {
                return labels::GENDER_LABEL;
            }

            std::string Genderable::PrintValue() const {
                return value == Gender::MALE ? labels::MALE_GENDER_LABEL : labels::FEMALE_GENDER_LABEL;
            }

        //struct Group::WrappedTAA member functions definition
            Label Group::WrappedTAA::PrintLabel() const {
                return labels::TAA_GROUP_LABEL;
            }

            std::string Group::WrappedTAA::PrintValue() const {
                switch (this -> value) {
                    case TAA::FIRST_GRADE:
                        return labels::TAA_SUBGROUP1_LABEL;
                    case TAA::SECOND_GRADE:
                        return labels::TAA_SUBGROUP2_LABEL;
                    case TAA::THIRD_GRADE:
                        return labels::TAA_SUBGROUP3_LABEL;
                }

                return labels::TAA_GROUP_LABEL;
            }

        //struct Group::WrappedTAC member functions definition
            Label Group::WrappedTAC::PrintLabel() const {
                return labels::TAC_GROUP_LABEL;
            }

            std::string Group::WrappedTAC::PrintValue() const {
                switch (this -> value) {
                    case TAC::BILINGUAL_BUSINESS_DEPARTMENT:
                        return labels::TAC_SUBGROUP1_LABEL;
                    case TAC::HEALTH_EDUCATION_DEPARTMENT:
                        return labels::TAC_SUBGROUP2_LABEL;
                    case TAC::MUSIC_DEPARTMENT:
                        return labels::TAC_SUBGROUP3_LABEL;
                    case TAC::THEOLOGY_DEPARTMENT:
                        return labels::TAC_SUBGROUP4_LABEL;  
                }

                return labels::TAC_GROUP_LABEL;
            }

        //struct Group::WrappedTAIS member functions definition
            Label Group::WrappedTAIS::PrintLabel() const {
                return labels::TAIS_GROUP_LABEL;
            }

            std::string Group::WrappedTAIS::PrintValue() const {
                switch (this -> value) {
                    case TAIS::SEVENTH_GRADE:
                        return labels::TAIS_SUBGROUP1_LABEL;
                    case TAIS::EIGHTH_GRADE:
                        return labels::TAIS_SUBGROUP2_LABEL;
                    case TAIS::NINTH_GRADE:
                        return labels::TAIS_SUBGROUP3_LABEL;
                    case TAIS::TENTH_GRADE:
                        return labels::TAIS_SUBGROUP4_LABEL;
                    case TAIS::ELEVENTH_GRADE:
                        return labels::TAIS_SUBGROUP5_LABEL;
                    case TAIS::TWELFTH_GRADE:
                        return labels::TAIS_SUBGROUP6_LABEL;  
                }

                return labels::TAIS_GROUP_LABEL;
            }

        //class Group member functions definition
            bool Group::IsTAA() const {
                return std::holds_alternative<TAA>(group_);
            }

            bool Group::IsTAC() const {
                return std::holds_alternative<TAC>(group_);
            }

            bool Group::IsTAIS() const {
                return std::holds_alternative<TAIS>(group_);
            }

            Group::WrappedTAA Group::GetAsTAA() const {
                WrappedTAA result;

                result.value = std::get<TAA>(group_);

                return result;
            }

            Group::WrappedTAC Group::GetAsTAC() const {
                WrappedTAC result;

                result.value = std::get<TAC>(group_);
                
                return result;
            }

            Group::WrappedTAIS Group::GetAsTAIS() const {
                WrappedTAIS result;

                result.value = std::get<TAIS>(group_);
                
                return result;
            }

            bool Group::operator==(const Group& other) const {
                return group_ == other.group_;
            }

            bool Group::operator!=(const Group& other) const {
                return !(*this == other);
            }

            //Struct Groupable Group member functions definition
            Label Groupable::PrintLabel() const {
                return labels::GROUP_LABEL;
            }

            std::string Groupable::PrintValue() const {
                return this -> value.IsTAA() 
                ? labels::TAA_GROUP_LABEL 
                : (this -> value.IsTAC() ? labels::TAC_GROUP_LABEL : labels::TAIS_GROUP_LABEL);
            }
        } //namespace interfaces
    } // namespace domain
} // namespace cafeteria_app


