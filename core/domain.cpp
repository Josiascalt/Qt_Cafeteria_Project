#include <string>
#include <variant>

#include "domain.h"

namespace cafeteria_app {
    namespace domain {
        namespace core_types {
        //class Namable member functions definition
            Name Nameable::StringToName(const std::string& str) {
                Name name;
                encoder::ascii::EncodeDataInIterable(str.begin(), str.end(), name.begin(), name.size());
                return name;
            }
            
            Label Nameable::PrintLabel() const {
                return text_vars::NAME_LABEL;
            }

            Text Nameable::PrintValue() const {
                return encoder::ascii::DecodeDataFromIterable(this -> GetValue().begin(), this -> GetValue().end());
            }
            
        //class Identifiable member functions definition
            Label Identifiable::PrintLabel() const {
                return text_vars::IDENTIFIER_LABEL;
            }

            Text Identifiable::PrintValue() const {
                return std::to_string(this -> GetValue());
            }

        //class Genderable member functions definition
            Label Genderable::PrintLabel() const {
                return text_vars::GENDER_LABEL;
            }

            Text Genderable::PrintValue() const {
                return GetValue() == Gender::MALE ? text_vars::MALE_GENDER_LABEL : text_vars::FEMALE_GENDER_LABEL;
            }

        //struct Group::WrappedTAA member functions definition
            Label Group::WrappedTAA::PrintLabel() const {
                return text_vars::TAA_GROUP_LABEL;
            }

            Text Group::WrappedTAA::PrintValue() const {
                switch (this -> value) {
                    case TAA::FIRST_GRADE:
                        return text_vars::TAA_SUBGROUP1_LABEL;
                    case TAA::SECOND_GRADE:
                        return text_vars::TAA_SUBGROUP2_LABEL;
                    case TAA::THIRD_GRADE:
                        return text_vars::TAA_SUBGROUP3_LABEL;
                }

                return text_vars::TAA_GROUP_LABEL;
            }

        //struct Group::WrappedTAC member functions definition
            Label Group::WrappedTAC::PrintLabel() const {
                return text_vars::TAC_GROUP_LABEL;
            }

            Text Group::WrappedTAC::PrintValue() const {
                switch (this -> value) {
                    case TAC::BILINGUAL_BUSINESS_DEPARTMENT:
                        return text_vars::TAC_SUBGROUP1_LABEL;
                    case TAC::HEALTH_EDUCATION_DEPARTMENT:
                        return text_vars::TAC_SUBGROUP2_LABEL;
                    case TAC::MUSIC_DEPARTMENT:
                        return text_vars::TAC_SUBGROUP3_LABEL;
                    case TAC::THEOLOGY_DEPARTMENT:
                        return text_vars::TAC_SUBGROUP4_LABEL;  
                }

                return text_vars::TAC_GROUP_LABEL;
            }

        //struct Group::WrappedTAIS member functions definition
            Label Group::WrappedTAIS::PrintLabel() const {
                return text_vars::TAIS_GROUP_LABEL;
            }

            Text Group::WrappedTAIS::PrintValue() const {
                switch (this -> value) {
                    case TAIS::SEVENTH_GRADE:
                        return text_vars::TAIS_SUBGROUP1_LABEL;
                    case TAIS::EIGHTH_GRADE:
                        return text_vars::TAIS_SUBGROUP2_LABEL;
                    case TAIS::NINTH_GRADE:
                        return text_vars::TAIS_SUBGROUP3_LABEL;
                    case TAIS::TENTH_GRADE:
                        return text_vars::TAIS_SUBGROUP4_LABEL;
                    case TAIS::ELEVENTH_GRADE:
                        return text_vars::TAIS_SUBGROUP5_LABEL;
                    case TAIS::TWELFTH_GRADE:
                        return text_vars::TAIS_SUBGROUP6_LABEL;  
                }

                return text_vars::TAIS_GROUP_LABEL;
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

            //class Groupable Group member functions definition
            Label Groupable::PrintLabel() const {
                return text_vars::GROUP_LABEL;
            }

            Text Groupable::PrintValue() const {
                return this -> GetValue().IsTAA() 
                ? text_vars::TAA_GROUP_LABEL 
                : (this -> GetValue().IsTAC() ? text_vars::TAC_GROUP_LABEL : text_vars::TAIS_GROUP_LABEL);
            }
        } //namespace props
    } // namespace domain
} // namespace cafeteria_app


