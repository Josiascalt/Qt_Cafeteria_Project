#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "admin_dashboard.h"
#include "core\api.cpp"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "CafeteriaRecordSysInterface_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    auto core = cafeteria_app::Start();

    AdminDashboard d;
    d.show();

    return a.exec();
}
