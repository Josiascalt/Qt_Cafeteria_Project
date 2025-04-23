#ifndef TEXT_VARS_H
#define TEXT_VARS_H

#pragma once

#include <string>

namespace cafeteria_app {
    using Label = const char*;
    
    namespace text_vars {
        //Core types
        static constexpr Label NAME_LABEL = "name";

        static constexpr Label IDENTIFIER_LABEL = "identifier";

        static constexpr Label GENDER_LABEL = "gender";
            static constexpr Label MALE_GENDER_LABEL = "male";
            static constexpr Label FEMALE_GENDER_LABEL = "female";
        
        static constexpr Label GROUP_LABEL = "group";
            static constexpr Label TAA_GROUP_LABEL = "TAA";
                static constexpr Label TAA_SUBGROUP1_LABEL = "first";
                static constexpr Label TAA_SUBGROUP2_LABEL = "second";
                static constexpr Label TAA_SUBGROUP3_LABEL = "third";
            static constexpr Label TAC_GROUP_LABEL = "TAC";
                static constexpr Label TAC_SUBGROUP1_LABEL = "bilingual business";
                static constexpr Label TAC_SUBGROUP2_LABEL = "health education";
                static constexpr Label TAC_SUBGROUP3_LABEL = "music";
                static constexpr Label TAC_SUBGROUP4_LABEL = "theology";
            static constexpr Label TAIS_GROUP_LABEL = "TAIS";
                static constexpr Label TAIS_SUBGROUP1_LABEL = "seventh";
                static constexpr Label TAIS_SUBGROUP2_LABEL = "eighth";
                static constexpr Label TAIS_SUBGROUP3_LABEL = "ninth";
                static constexpr Label TAIS_SUBGROUP4_LABEL = "tenth";
                static constexpr Label TAIS_SUBGROUP5_LABEL = "eleventh";
                static constexpr Label TAIS_SUBGROUP6_LABEL = "twelfth";
    } //namespace text_vars
} // namespace cafeteria_app

#endif //TEXT_VARS_H