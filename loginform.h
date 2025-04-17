#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>

#include "dashboard.h"
//#include "core/request_handler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginForm;
}
QT_END_NAMESPACE

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    LoginForm(QWidget *parent = nullptr/*, cafeteria_app::request_handler::RequestHandler *handler = nullptr*/);
    ~LoginForm();

private slots:
    void on_login_button__clicked();

private:
    Ui::LoginForm *ui;
    Dashboard *dashboard_;
    //cafeteria_app::request_handler::RequestHandler *handler_;

};
#endif // LOGINFORM_H
