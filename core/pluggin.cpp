#include "pluggin.h"

#include <filesystem>


#include "file_handler.h"
#include "utilities\json\json.h"
#include "utilities\json\json_builder.h"

namespace detail {

    struct PathSettings {
        struct Database {
            fs::path backup;
            fs::path data;
        };

        struct Exports {
            fs::path stats;
            fs::path qrcode;
        };

        Database database;
        Exports exports;
    };
    
    
    PathSettings GetPathSettings(const fs::path& json_file) {
        try {
            file_handler::LoadJsonFile(json_file);
        } catch (json::ParsingError&) {
            auto empty_path_settings = CreatePathSettingsTemplate();
            std::ofstream file(json_file, std::ios::out | std::ios::trunc);
            if (file) {
                json::Print(empty_path_settings, file);
            } else {

            }
            
        }
        
        PathSettings settings;
        return settings;
    }

    void ApplySettings(const fs::path& settings_dir) {
        //if the default file not exist, creates one
        const auto PATH_SETTINGS = file_handler::CreatePathObject("paths.json");
        GetPathSettings(PATH_SETTINGS);
    }
    
} // namespace detail

cafeteria_app::request_handler::RequestHandler InitializeCatalogue() {
    //if the default settings directory does not exist, creates one
    const auto SETTINGS_DIRECTORY = file_handler::CreatePathObject("Settings");

    detail::ApplySettings(SETTINGS_DIRECTORY);

}