#include <filesystem>
#include <utility>
#include <unordered_map>
#include <string_view>

#include "api.h"
#include "globals.h"
#include "utilities\json\json.h"
#include "file_handler.h"
#include "document_templates.h"

namespace cafeteria_app {
    namespace detail {
        struct GroupPaths : std::unordered_map<std::string_view, std::unordered_map<std::string_view, fs::path>> {
            GroupPaths(const json::Document& doc, std::string_view group) {

            }
        };

        GroupPaths ImportGroupPaths(const json::Document& doc, std::string_view group) {
            return {
                        {
                            file_handler::CreatePathObject(group.at(__DATABASE_PARENT_FOLDER__).AsDict().at(__BACKUP_FOLDER__).AsString())
                            , file_handler::CreatePathObject(group.at(__DATABASE_PARENT_FOLDER__).AsDict().at(__DATA_FOLDER__).AsString())
                        }
                        , {
                            file_handler::CreatePathObject(group.at(__EXPORTS_PARENT_FOLDER__).AsDict().at(__QR_FOLDER__).AsString())
                            , file_handler::CreatePathObject(group.at(__EXPORTS_PARENT_FOLDER__).AsDict().at(__STATS_FOLDER__).AsString())
                        }
                };
        }
    } // namespace detail

    /*cafeteria_app::request_handler::RequestHandler*/void Start() {
        using namespace file_handler::literals;

        //Set folders and files to hold the program settings

        const auto SETTINGS = file_handler::CreatePathObject(__SETTINGS_PARENT_FOLDER__);

        const auto PATH_SETTINGS = file_handler::CreatePathObject(SETTINGS / __PATH_SETTINGS_FILE__);

        //Read the contents of the path settings files using a JsonFile
        
        file_handler::JsonFile path_settings_file(PATH_SETTINGS, &cafeteria_app::document_templates::json::TEMPLATE_PATH_SETTINGS);
        
        auto paths_doc = path_settings_file.Get();
        
        const auto TAA_PATHS = detail::ImportGroupPaths(paths_doc.GetRoot().AsDict().at(__TAA__).AsDict());
        const auto TAC_PATHS = detail::ImportGroupPaths(paths_doc.GetRoot().AsDict().at(__TAC__).AsDict());
        const auto TAIS_PATHS = detail::ImportGroupPaths(paths_doc.GetRoot().AsDict().at(__TAIS__).AsDict());

        
        const auto USER_DATA_PATHS = cafeteria_app::backup::UserDataPaths{}
                                        .SetMetadataPaths(TAC_PATHS.database.data / __DATA_FOLDER__ / __QUEUE_DATA_FILE__);
                                        //.SetIdentifiersPath(file_handler::CreatePathObject(__IDENTIFIER_DATA_FILE__, TAC_PATHS.database.data / __DATA_FOLDER__))
                                        //.SetNamesPath(file_handler::CreatePathObject(__NAME_DATA_FILE__, TAC_PATHS.database.data / __DATA_FOLDER__))
                                        //.SetGendersPath(file_handler::CreatePathObject(__GENDER_DATA_FILE__, TAC_PATHS.database.data / __DATA_FOLDER__))
                                        //.SetGroupsPath(file_handler::CreatePathObject(__GROUP_DATA_FILE__, TAC_PATHS.database.data / __DATA_FOLDER__));


        //return cafeteria_app::request_handler::RequestHandler{USER_DATA_PATHS};
    }
} //namespace cafeteria_app

