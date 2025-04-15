#include <filesystem>
#include <utility>

#include "api.h"
#include "globals.h"
#include "utilities\json\json.h"
#include "file_handler.h"
#include "document_templates.h"

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

        PathSettings(Database d, Exports e) 
        : database(std::move(d))
        , exports(std::move(e))
        {
        }
    };

    PathSettings ImportPathSettings(const json::Dict& group) {
        using namespace std::literals;
        return {{group.at("Database"s).AsDict().at(__BACKUP_PARENT_FOLDER__).AsString(), group.at("Database"s).AsDict().at(__DATA_PARENT_FOLDER__).AsString()}
              , {group.at("Exports"s).AsDict().at(__QR_PARENT_FOLDER__).AsString(), group.at("Exports"s).AsDict().at(__STATS_PARENT_FOLDER__).AsString()}};
    }
} // namespace detail

cafeteria_app::request_handler::RequestHandler Start() {
    using namespace std::literals;
    using namespace file_handler::literals;
    //Import settings
    const auto SETTINGS = file_handler::CreatePathObject(__SETTINGS_PARENT_FOLDER__);

    const auto PATH_SETTINGS = file_handler::CreatePathObject(__PATH_SETTINGS_FILE__, SETTINGS);
    
    file_handler::JsonFile paths(PATH_SETTINGS, &cafeteria_app::document_templates::json::TEMPLATE_PATH_SETTINGS);
    
    auto paths_doc = paths.Get();
    
    const auto TAA_PATHS = detail::ImportPathSettings(paths_doc.GetRoot().AsDict().at(__TAA__).AsDict());
    const auto TAC_PATHS = detail::ImportPathSettings(paths_doc.GetRoot().AsDict().at(__TAC__).AsDict());
    const auto TAIS_PATHS = detail::ImportPathSettings(paths_doc.GetRoot().AsDict().at(__TAIS__).AsDict());
    
    const auto USER_DATA_PATHS = cafeteria_app::backup::UserDataPaths{}
                                     .SetMetadataPaths(file_handler::CreatePathObject(__QUEUE_METADATA_FILE__, TAC_PATHS.database.data / __DATA_PARENT_FOLDER__))
                                     .SetIdentifiersPath(file_handler::CreatePathObject(__IDENTIFIER_DATA_FILE__, TAC_PATHS.database.data / __DATA_PARENT_FOLDER__))
                                     .SetNamesPath(file_handler::CreatePathObject(__NAME_DATA_FILE__, TAC_PATHS.database.data / __DATA_PARENT_FOLDER__))
                                     .SetGendersPath(file_handler::CreatePathObject(__GENDER_DATA_FILE__, TAC_PATHS.database.data / __DATA_PARENT_FOLDER__))
                                     .SetGroupsPath(file_handler::CreatePathObject(__GROUP_DATA_FILE__, TAC_PATHS.database.data / __DATA_PARENT_FOLDER__));


    return cafeteria_app::request_handler::RequestHandler{USER_DATA_PATHS};
}
