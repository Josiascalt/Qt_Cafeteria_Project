#pragma once

#include <QMainWindow>

#include "login.h"

namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

private slots:
    void on_home_tab_button__clicked();

    void on_database_tab_button__clicked();

    void on_log_button__clicked();

private:
    Ui::AdminDashboard *ui;

    Login *login_;
};
