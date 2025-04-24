#pragma once
#include "labels.h"
#include "utilities\json\json_builder.h"
#include "utilities\json\json.h"

namespace cafeteria_app {
    namespace document_templates {
        using namespace std::literals;
        
        namespace json {
            static const auto TEMPLATE_PATH_SETTINGS = ::json::Document(::json::Builder{}.StartDict()
                                                                                            .Key(labels::TAA_GROUP_LABEL)
                                                                                                .StartDict()
                                                                                                    .Key(labels::DATABASE_PARENT_FOLDER)
                                                                                                        .StartDict()
                                                                                                            .Key(labels::DATA_FOLDER)
                                                                                                                .Value(""s)
                                                                                                            .Key(labels::BACKUP_FOLDER)
                                                                                                                .Value(""s)
                                                                                                        .EndDict()
                                                                                                    .Key(labels::EXPORTS_PARENT_FOLDER)
                                                                                                        .StartDict()
                                                                                                            .Key(labels::QR_FOLDER)
                                                                                                                .Value(""s)
                                                                                                            .Key(labels::STATS_FOLDER)
                                                                                                                .Value(""s)
                                                                                                        .EndDict()
                                                                                                .EndDict()
                                                                                            .Key(labels::TAC_GROUP_LABEL)
                                                                                                .StartDict()
                                                                                                    .Key(labels::DATABASE_PARENT_FOLDER)
                                                                                                        .StartDict()
                                                                                                            .Key(labels::DATA_FOLDER)
                                                                                                                .Value(""s)
                                                                                                            .Key(labels::BACKUP_FOLDER)
                                                                                                                .Value(""s)
                                                                                                        .EndDict()
                                                                                                    .Key(labels::EXPORTS_PARENT_FOLDER)
                                                                                                        .StartDict()
                                                                                                            .Key(labels::QR_FOLDER)
                                                                                                                .Value(""s)
                                                                                                            .Key(labels::STATS_FOLDER)
                                                                                                                .Value(""s)
                                                                                                        .EndDict()
                                                                                                .EndDict()
                                                                                            .Key(labels::TAIS_GROUP_LABEL)
                                                                                                .StartDict()
                                                                                                    .Key(labels::DATABASE_PARENT_FOLDER)
                                                                                                        .StartDict()
                                                                                                            .Key(labels::DATA_FOLDER)
                                                                                                                .Value(""s)
                                                                                                            .Key(labels::BACKUP_FOLDER)
                                                                                                                .Value(""s)
                                                                                                        .EndDict()
                                                                                                    .Key(labels::EXPORTS_PARENT_FOLDER)
                                                                                                        .StartDict()
                                                                                                            .Key(labels::QR_FOLDER)
                                                                                                                .Value(""s)
                                                                                                            .Key(labels::STATS_FOLDER)
                                                                                                                .Value(""s)
                                                                                                        .EndDict()
                                                                                                .EndDict()
                                                                                        .EndDict().Build());
        } //namespace json

        namespace qr {
            //first part
            const auto TEMPLATE_QR_FILE_1P = "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<meta charset=\"utf-8\">\n\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t\t<title>CAFETERIA KEY</title>\n\t</head>\n\t<style>\n\t\t* {\n\t\t\tmargin: 0;\n\t\t\tpadding: 0;\n\t\t\tbox-sizing: border-box;\n\t\t}\n\n\t\t:root {\n\t\t\t--bg: linear-gradient(-60deg, #16a085 0%, #f4d03f 100%);\n\n\t\t\t--main-color: #fff;\n\n\t\t\tfont-size: 20px;\n\t\t}\n\n\t\t#app {\n\t\t\theight: 100vh;\n\t\t\twidth: 100vw;\n\t\t\tbackground: var(--bg);\n\t\t\tdisplay: flex;\n\t\t\tflex-wrap: wrap;\n\t\t\talign-items: center;\n\t\t\tjustify-content: center;\n\t\t}\n\n\t\t#app > .wrapper {\n\t\t\twidth: 250px;\n\t\t\theight: auto;\n\t\t\tdisplay: flex;\n\t\t\talign-items: center;\n\t\t\tjustify-content: center;\n\t\t\tmargin: 0 50px;\n\t\t}\n\n\t\t#app > .wrapper > .label {\n\t\t\tbackground: var(--main-color);\n\t\t\tline-height: 1.75rem;\n\t\t\ttext-align: center;\n\t\t\tfont-size: 1.25rem;\n\t\t\tfont-family: Gill Sans, sans-serif;\n\t\t\tfont-weight: 600;\n\t\t\tpadding: 1rem;\n\t\t\tborder-radius:10px;\n\t\t\tmix-blend-mode: screen;\n\t\t\tword-wrap: break-word;\n\t\t\tmax-width: 300px;\n\t\t}\n\t</style>\n\t<body>\n\t\t<div id=\"app\">\n\t\t\t<div class=\"wrapper\">\n";
            
            const auto TEMPLATE_QR_FILE_2P = "\n\t\t\t</div>\n\t\t\t<div class=\"wrapper\">\n\t\t\t\t<span class=\"label\">";
            const auto TEMPLATE_QR_FILE_3P = "\n\t\t\t\t</span>\n\t\t\t</div>\n\t\t</div>\n\t</body>\n</html>";
        } //namespace qr
    } //namespace document_templates
} //namespace cafeteria_app