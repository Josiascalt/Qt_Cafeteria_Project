QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/backup_handler.cpp \
    core/domain.cpp \
    core/external/excel_maker/src/IZipArchive.cpp \
    core/external/excel_maker/src/OpenXLSX-Exports.cpp \
    core/external/excel_maker/src/XLCell.cpp \
    core/external/excel_maker/src/XLCellIterator.cpp \
    core/external/excel_maker/src/XLCellRange.cpp \
    core/external/excel_maker/src/XLCellReference.cpp \
    core/external/excel_maker/src/XLCellValue.cpp \
    core/external/excel_maker/src/XLColor.cpp \
    core/external/excel_maker/src/XLColumn.cpp \
    core/external/excel_maker/src/XLCommandQuery.cpp \
    core/external/excel_maker/src/XLConstants.cpp \
    core/external/excel_maker/src/XLContentTypes.cpp \
    core/external/excel_maker/src/XLDateTime.cpp \
    core/external/excel_maker/src/XLDocument.cpp \
    core/external/excel_maker/src/XLException.cpp \
    core/external/excel_maker/src/XLFormula.cpp \
    core/external/excel_maker/src/XLIterator.cpp \
    core/external/excel_maker/src/XLMergeCells.cpp \
    core/external/excel_maker/src/XLProperties.cpp \
    core/external/excel_maker/src/XLRelationships.cpp \
    core/external/excel_maker/src/XLRow.cpp \
    core/external/excel_maker/src/XLRowData.cpp \
    core/external/excel_maker/src/XLSharedStrings.cpp \
    core/external/excel_maker/src/XLSheet.cpp \
    core/external/excel_maker/src/XLStyles.cpp \
    core/external/excel_maker/src/XLUtilities.cpp \
    core/external/excel_maker/src/XLWorkbook.cpp \
    core/external/excel_maker/src/XLXmlData.cpp \
    core/external/excel_maker/src/XLXmlFile.cpp \
    core/external/excel_maker/src/XLXmlParser.cpp \
    core/external/excel_maker/src/XLZipArchive.cpp \
    core/external/excel_maker/src/pugixml.cpp \
    core/external/qr_maker/src/qrcodegen.cpp \
    core/file_handler.cpp \
    core/request_handler.cpp \
    core/user_catalogue.cpp \
    core/utilities/json/json.cpp \
    core/utilities/json/json_builder.cpp \
    dashboard.cpp \
    main.cpp \
    loginform.cpp \
    newuserform.cpp

HEADERS += \
    core/backup_handler.h \
    core/domain.h \
    core/external/excel_maker/pluggin.hpp \
    core/external/excel_maker/src/IZipArchive.hpp \
    core/external/excel_maker/src/OpenXLSX-Exports.hpp \
    core/external/excel_maker/src/OpenXLSX.hpp \
    core/external/excel_maker/src/XLCell.hpp \
    core/external/excel_maker/src/XLCellIterator.hpp \
    core/external/excel_maker/src/XLCellRange.hpp \
    core/external/excel_maker/src/XLCellReference.hpp \
    core/external/excel_maker/src/XLCellValue.hpp \
    core/external/excel_maker/src/XLColor.hpp \
    core/external/excel_maker/src/XLColumn.hpp \
    core/external/excel_maker/src/XLCommandQuery.hpp \
    core/external/excel_maker/src/XLConstants.hpp \
    core/external/excel_maker/src/XLContentTypes.hpp \
    core/external/excel_maker/src/XLDateTime.hpp \
    core/external/excel_maker/src/XLDocument.hpp \
    core/external/excel_maker/src/XLException.hpp \
    core/external/excel_maker/src/XLFormula.hpp \
    core/external/excel_maker/src/XLIterator.hpp \
    core/external/excel_maker/src/XLMergeCells.hpp \
    core/external/excel_maker/src/XLProperties.hpp \
    core/external/excel_maker/src/XLRelationships.hpp \
    core/external/excel_maker/src/XLRow.hpp \
    core/external/excel_maker/src/XLRowData.hpp \
    core/external/excel_maker/src/XLSharedStrings.hpp \
    core/external/excel_maker/src/XLSheet.hpp \
    core/external/excel_maker/src/XLStyles.hpp \
    core/external/excel_maker/src/XLUtilities.hpp \
    core/external/excel_maker/src/XLWorkbook.hpp \
    core/external/excel_maker/src/XLXmlData.hpp \
    core/external/excel_maker/src/XLXmlFile.hpp \
    core/external/excel_maker/src/XLXmlParser.hpp \
    core/external/excel_maker/src/XLZipArchive.hpp \
    core/external/excel_maker/src/pugiconfig.hpp \
    core/external/excel_maker/src/pugixml.hpp \
    core/external/excel_maker/src/zippy.hpp \
    core/external/qr_maker/pluggin.hpp \
    core/external/qr_maker/src/qrcodegen.hpp \
    core/file_handler.h \
    core/pluggin.h \
    core/record_catalogue.h \
    core/request_handler.h \
    core/tests.h \
    core/user_catalogue.h \
    core/utilities/encoder.h \
    core/utilities/json/json.h \
    core/utilities/json/json_builder.h \
    core/utilities/utilities.h \
    dashboard.h \
    loginform.h \
    newuserform.h

FORMS += \
    dashboard.ui \
    loginform.ui \
    newuserform.ui

TRANSLATIONS += \
    CafeteriaRecordSysInterface_zh_TW.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc

DISTFILES += \
    .gitignore \
    media/icons/add_user_blue.png \
    media/icons/analytics.png \
    media/icons/database.png \
    media/icons/home.png \
    media/icons/log_out.png \
    media/icons/log_out_black.png \
    media/icons/log_out_blue.png \
    media/pics/avatar.png \
    media/pics/logo_tac.png
