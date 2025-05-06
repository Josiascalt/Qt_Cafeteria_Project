#include <utility>
#include <filesystem>
#include <exception>
#include <optional>


#include "api.h"
#include "labels.h"
#include "document_templates.h"
#include "utilities\document_types.h"
#include "database_handler.h"
#include "user_catalogue.h"

namespace cafeteria_app {
    namespace detail {
        fs::path GetPathSetting(const file_handler::JsonFile::Type& path_settings, Label group, Label parent_folder, Label child_folder) {
            fs::path target_folder(path_settings.GetRoot().AsDict().at(group).AsDict().at(parent_folder).AsDict().at(child_folder).AsString());

            if (!fs::exists(target_folder)) {
                using namespace std::literals;
                throw std::logic_error{"The path: "s + target_folder.string() + " does not exist."s};
            }

            return file_handler::MakeValidPath(target_folder / fs::path{group} / fs::path{parent_folder} / fs::path{child_folder} , true);
        };
    } //namespace detail

    cafeteria_app::request::RequestHandler Start() {
        //Get the path to the settings folder
        const auto SETTINGS = file_handler::MakeValidPath(labels::SEETINGS_PARENT_FOLDER);

        //Read the contents of the path settings files using a JsonFile
        file_handler::JsonFile path_settings_file(SETTINGS / labels::PATH_SETTINGS_FILE, &cafeteria_app::document_templates::json::TEMPLATE_PATH_SETTINGS);
        auto path_settings = path_settings_file.Get();

        fs::path tac_db;

        try {
            tac_db = detail::GetPathSetting(path_settings, labels::TAC_GROUP_LABEL,labels::DATABASE_PARENT_FOLDER, labels::DATA_FOLDER);
        } 

        catch (const json::ContextError& e) {
            using namespace std::literals;
            path_settings_file.Restore();
            throw std::logic_error{"Error while parsing the path settings file. Please check the path settings file values at "s + fs::absolute(path_settings_file.GetFilename()).string()};
        }
        
        catch (const std::logic_error& e) {
            using namespace std::literals;
            throw std::logic_error{std::string(e.what()) + "\nPlease check the path settings file values at "s + fs::absolute(path_settings_file.GetFilename()).string()};
        }

    /*std::array<domain::users::Student, 10> students;

        students[0].SetIdentifier(1234567890);
        static_cast<domain::users::Nameable*>(&students[0])->value = domain::interfaces::Nameable::StringToName("John Doe");
        static_cast<domain::users::Genderable*>(&students[0])->value = domain::interfaces::Gender::MALE;
        static_cast<domain::users::Groupable*>(&students[0])->value = domain::users::Group::TAC::MUSIC_DEPARTMENT;

        students[1].SetIdentifier(12345);
        static_cast<domain::users::Nameable*>(&students[1])->value = domain::interfaces::Nameable::StringToName("Abigail Doe");
        static_cast<domain::users::Genderable*>(&students[1])->value = domain::interfaces::Gender::FEMALE;
        static_cast<domain::users::Groupable*>(&students[1])->value = domain::users::Group::TAC::BILINGUAL_BUSINESS_DEPARTMENT;

        students[2].SetIdentifier(123);
        static_cast<domain::users::Nameable*>(&students[2])->value = domain::interfaces::Nameable::StringToName("Michael Doe");
        static_cast<domain::users::Genderable*>(&students[2])->value = domain::interfaces::Gender::MALE;
        static_cast<domain::users::Groupable*>(&students[2])->value = domain::users::Group::TAC::HEALTH_EDUCATION_DEPARTMENT;

        tac_db->Serialize(&students.data()[0]);
        tac_db->Serialize(&students.data()[1]);
        tac_db->Serialize(&students.data()[2]);

        auto users = tac_db->Deserialize();
        
        catalogue::UserCatalogue user_catalogue(std::move(users));

        if (const auto& user = user_catalogue.GetUserByIdentifier(12345)) {
            if (user) {
                std::cout << "User found!" << std::endl;
                std::cout << "Identifier: " << user->GetIdentifier() << std::endl;
                std::cout << "Name: " << (dynamic_cast<domain::users::Nameable*>(user.get())->PrintValue()) << std::endl;}
        } else {
            std::cout << "User not found!" << std::endl;
        }*/

        

        
        return cafeteria_app::request::RequestHandler{std::move(tac_db)};
    }
} //namespace cafeteria_app

