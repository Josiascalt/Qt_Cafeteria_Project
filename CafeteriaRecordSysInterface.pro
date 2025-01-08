QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../proyecto_cafeteria/external/QR-Code-generator/src/qrcodegen.cpp \
    core/backup_handler.cpp \
    core/domain.cpp \
    core/file_handler.cpp \
    core/request_handler.cpp \
    core/user_catalogue.cpp \
    dashboard.cpp \
    main.cpp \
    loginform.cpp \
    newuserform.cpp

HEADERS += \
    ../../proyecto_cafeteria/external/QR-Code-generator/pluggin.hpp \
    ../../proyecto_cafeteria/external/QR-Code-generator/src/qrcodegen.hpp \
    core/backup_handler.h \
    core/domain.h \
    core/file_handler.h \
    core/pluggin.h \
    core/request_handler.h \
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
    media/icons/analytics.png
