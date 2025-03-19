#ifndef PLUGGIN_H
#define PLUGGIN_H
#pragma once

#include "request_handler.h"



cafeteria_app::request_handler::RequestHandler InitializeCatalogue(); 
/*{
    using namespace file_handler::literals;
    //Set Enviroment Varaibles
    const auto SETTINGS_DIRECTORY = "Settings"_p;

    //Subdirectories
    const auto RECORD_DIRECTORY = file_handler::CreatePathObject("Records", TEMP_DIRECTORY);
    const auto DATA_DIRECTORY = file_handler::CreatePathObject("Data", TEMP_DIRECTORY);

    const auto USER_DATA_PATHS = cafeteria_app::backup::UserDataPaths{}
                                     .SetMetadataPaths(file_handler::CreatePathObject("queue.mdat", DATA_DIRECTORY))
                                     .SetIdentifiersPath(file_handler::CreatePathObject("identifiers.dat", DATA_DIRECTORY))
                                     .SetNamesPath(file_handler::CreatePathObject("names.dat", DATA_DIRECTORY))
                                     .SetGendersPath(file_handler::CreatePathObject("genders.dat", DATA_DIRECTORY))
                                     .SetGroupsPath(file_handler::CreatePathObject("groups.dat", DATA_DIRECTORY));


    return cafeteria_app::request_handler::RequestHandler{USER_DATA_PATHS};
}*/

#endif // PLUGGIN_H
