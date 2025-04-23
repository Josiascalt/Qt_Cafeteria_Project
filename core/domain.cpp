#include "domain.h"

#include <variant>

namespace cafeteria_app {
    namespace domain {
        namespace core_types {
        //class Group member functions definition
            bool Group::IsTAC() const {
                return std::holds_alternative<TAC>(group_);
            }

            bool Group::IsTAIS() const {
                return std::holds_alternative<TAIS>(group_);
            }

            bool Group::IsTAA() const {
                return std::holds_alternative<TAA>(group_);
            }

            Group::TAC Group::GetAsTAC() const {
                return std::get<TAC>(group_);
            }

            Group::TAIS Group::GetAsTAIS() const {
                return std::get<TAIS>(group_);
            }

            Group::TAA Group::GetAsTAA() const {
                return std::get<TAA>(group_);
            }

            bool Group::operator==(const Group& other) const {
                return group_ == other.group_;
            }

            bool Group::operator!=(const Group& other) const {
                return !(*this == other);
            }
        } //namespace props
    } // namespace domain
} // namespace cafeteria_app


