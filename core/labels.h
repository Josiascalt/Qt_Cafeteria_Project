#ifndef LABELS_H
#define LABELS_H

#pragma once

namespace cafeteria_app {
    using Label = const char*;
    
    namespace labels {
    /*----------Core Types----------*/
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
    
    
    
    
    /*----------App Files----------*/
        //Settings
        static constexpr Label SEETINGS_PARENT_FOLDER = "settings";
            static constexpr Label PATH_SETTINGS_FILE = "path_settings.json";

        //Database
        static constexpr Label DATABASE_PARENT_FOLDER = "database";
            static constexpr Label BACKUP_FOLDER = "backup";
            static constexpr Label DATA_FOLDER = "data";
            static constexpr Label METADATA_FOLDER = "metadata";
                static constexpr Label TYPES_METADATA_FILE = "types.mdat";
        
        //Exports
            static constexpr Label EXPORTS_PARENT_FOLDER = "exports";
                static constexpr Label QR_FOLDER = "qr_codes";
                static constexpr Label STATS_FOLDER = "stats";
        
    } //namespace labels
} // namespace cafeteria_app

#endif //LABELS_H