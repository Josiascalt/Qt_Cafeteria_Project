#ifndef DASHBOARD_H
#define DASHBOARD_H
#pragma once

#include <QMainWindow>

#include "login.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void on_home_tab_button__clicked();

    void on_database_tab_button__clicked();

    void on_log_button__clicked();

private:
    Ui::Dashboard *ui;
    Login *login_;
};

#endif //DASHBOARD_H
