QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/backup_handler.cpp \
    core/domain.cpp \
    core/external/excel_maker/OpenXLSX/IZipArchive.cpp \
    core/external/excel_maker/OpenXLSX/OpenXLSX-Exports.cpp \
    core/external/excel_maker/OpenXLSX/XLCell.cpp \
    core/external/excel_maker/OpenXLSX/XLCellIterator.cpp \
    core/external/excel_maker/OpenXLSX/XLCellRange.cpp \
    core/external/excel_maker/OpenXLSX/XLCellReference.cpp \
    core/external/excel_maker/OpenXLSX/XLCellValue.cpp \
    core/external/excel_maker/OpenXLSX/XLColor.cpp \
    core/external/excel_maker/OpenXLSX/XLColumn.cpp \
    core/external/excel_maker/OpenXLSX/XLCommandQuery.cpp \
    core/external/excel_maker/OpenXLSX/XLConstants.cpp \
    core/external/excel_maker/OpenXLSX/XLContentTypes.cpp \
    core/external/excel_maker/OpenXLSX/XLDateTime.cpp \
    core/external/excel_maker/OpenXLSX/XLDocument.cpp \
    core/external/excel_maker/OpenXLSX/XLException.cpp \
    core/external/excel_maker/OpenXLSX/XLFormula.cpp \
    core/external/excel_maker/OpenXLSX/XLIterator.cpp \
    core/external/excel_maker/OpenXLSX/XLMergeCells.cpp \
    core/external/excel_maker/OpenXLSX/XLProperties.cpp \
    core/external/excel_maker/OpenXLSX/XLRelationships.cpp \
    core/external/excel_maker/OpenXLSX/XLRow.cpp \
    core/external/excel_maker/OpenXLSX/XLRowData.cpp \
    core/external/excel_maker/OpenXLSX/XLSharedStrings.cpp \
    core/external/excel_maker/OpenXLSX/XLSheet.cpp \
    core/external/excel_maker/OpenXLSX/XLStyles.cpp \
    core/external/excel_maker/OpenXLSX/XLUtilities.cpp \
    core/external/excel_maker/OpenXLSX/XLWorkbook.cpp \
    core/external/excel_maker/OpenXLSX/XLXmlData.cpp \
    core/external/excel_maker/OpenXLSX/XLXmlFile.cpp \
    core/external/excel_maker/OpenXLSX/XLXmlParser.cpp \
    core/external/excel_maker/OpenXLSX/XLZipArchive.cpp \
    core/external/excel_maker/OpenXLSX/pugixml.cpp \
    core/external/qr_maker/src/qrcodegen.cpp \
    core/file_handler.cpp \
    core/request_handler.cpp \
    core/user_catalogue.cpp \
    dashboard.cpp \
    main.cpp \
    loginform.cpp \
    newuserform.cpp

HEADERS += \
    core/backup_handler.h \
    core/domain.h \
    core/external/excel_maker/OpenXLSX/IZipArchive.hpp \
    core/external/excel_maker/OpenXLSX/OpenXLSX-Exports.hpp \
    core/external/excel_maker/OpenXLSX/OpenXLSX.hpp \
    core/external/excel_maker/OpenXLSX/XLCell.hpp \
    core/external/excel_maker/OpenXLSX/XLCellIterator.hpp \
    core/external/excel_maker/OpenXLSX/XLCellRange.hpp \
    core/external/excel_maker/OpenXLSX/XLCellReference.hpp \
    core/external/excel_maker/OpenXLSX/XLCellValue.hpp \
    core/external/excel_maker/OpenXLSX/XLColor.hpp \
    core/external/excel_maker/OpenXLSX/XLColumn.hpp \
    core/external/excel_maker/OpenXLSX/XLCommandQuery.hpp \
    core/external/excel_maker/OpenXLSX/XLConstants.hpp \
    core/external/excel_maker/OpenXLSX/XLContentTypes.hpp \
    core/external/excel_maker/OpenXLSX/XLDateTime.hpp \
    core/external/excel_maker/OpenXLSX/XLDocument.hpp \
    core/external/excel_maker/OpenXLSX/XLException.hpp \
    core/external/excel_maker/OpenXLSX/XLFormula.hpp \
    core/external/excel_maker/OpenXLSX/XLIterator.hpp \
    core/external/excel_maker/OpenXLSX/XLMergeCells.hpp \
    core/external/excel_maker/OpenXLSX/XLProperties.hpp \
    core/external/excel_maker/OpenXLSX/XLRelationships.hpp \
    core/external/excel_maker/OpenXLSX/XLRow.hpp \
    core/external/excel_maker/OpenXLSX/XLRowData.hpp \
    core/external/excel_maker/OpenXLSX/XLSharedStrings.hpp \
    core/external/excel_maker/OpenXLSX/XLSheet.hpp \
    core/external/excel_maker/OpenXLSX/XLStyles.hpp \
    core/external/excel_maker/OpenXLSX/XLUtilities.hpp \
    core/external/excel_maker/OpenXLSX/XLWorkbook.hpp \
    core/external/excel_maker/OpenXLSX/XLXmlData.hpp \
    core/external/excel_maker/OpenXLSX/XLXmlFile.hpp \
    core/external/excel_maker/OpenXLSX/XLXmlParser.hpp \
    core/external/excel_maker/OpenXLSX/XLZipArchive.hpp \
    core/external/excel_maker/OpenXLSX/pugiconfig.hpp \
    core/external/excel_maker/OpenXLSX/pugixml.hpp \
    core/external/excel_maker/OpenXLSX/zippy.hpp \
    core/external/excel_maker/pluggin.hpp \
    core/external/qr_maker/pluggin.hpp \
    core/external/qr_maker/src/qrcodegen.hpp \
    core/file_handler.h \
    core/pluggin.h \
    core/record_catalogue.h \
    core/request_handler.h \
    core/tests.h \
    core/user_catalogue.h \
    core/utilities/encoder.h \
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
