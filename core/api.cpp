#include <filesystem>
#include <utility>
#include <unordered_map>
#include <string_view>

#include "api.h"
#include "labels.h"
#include "utilities\json\json.h"
#include "file_handler.h"
#include "document_templates.h"

namespace cafeteria_app {

    /*cafeteria_app::request_handler::RequestHandler*/void Start() {
        using namespace file_handler::literals;

        //Set folders and files to hold the program settings

        const auto SETTINGS = file_handler::CreatePathObject(labels::SEETINGS_PARENT_FOLDER);

        const auto PATH_SETTINGS = file_handler::CreatePathObject(SETTINGS / labels::PATH_SETTINGS_FILE);

        //Read the contents of the path settings files using a JsonFile
        
        file_handler::JsonFile path_settings_file(PATH_SETTINGS, &cafeteria_app::document_templates::json::TEMPLATE_PATH_SETTINGS);
        auto paths_doc = path_settings_file.Get();

        
        


        //return cafeteria_app::request_handler::RequestHandler{USER_DATA_PATHS};
    }
} //namespace cafeteria_app

