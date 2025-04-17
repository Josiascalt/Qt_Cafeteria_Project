#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QMainWindow>
#include "newuserform.h"
//#include "core/request_handler.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr/*, cafeteria_app::request_handler::RequestHandler *handler = nullptr*/, QMainWindow* login_form = nullptr);
    ~Dashboard();

private slots:
    void on_exit_button__clicked();

    void on_home_tab_button__clicked();

    void on_database_tab_button__clicked();

    void on_add_user_button__clicked();

private:
    Ui::Dashboard *ui;
    //cafeteria_app::request_handler::RequestHandler *handler_;
    QMainWindow *login_form_;
    NewUserForm *new_user_form_;

};

#endif // DASHBOARD_H
