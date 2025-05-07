#ifndef LOGIN_H
#define LOGIN_H
#pragma once

#include <QWidget>
#include "core/api.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr, cafeteria_app::CoreHandler *core = nullptr);
    ~Login();

private slots:
    void on_login_button__clicked();

private:
    Ui::Login *ui;
    cafeteria_app::CoreHandler *core_;

};
#endif // LOGIN_H
