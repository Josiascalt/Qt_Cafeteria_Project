#include "admin_dashboard.h"
#include "ui_admin_dashboard.h"

AdminDashboard::AdminDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);
    this->on_home_tab_button__clicked();
    //ui->tab_display_->hide();
}

AdminDashboard::~AdminDashboard()
{
    delete login_;
    delete ui;
}

void AdminDashboard::on_home_tab_button__clicked()
{
    ui->database_tab_->hide();
    ui->home_tab_->show();
}


void AdminDashboard::on_database_tab_button__clicked()
{
    ui->home_tab_->hide();
    ui->database_tab_->show();
}

void AdminDashboard::on_log_button__clicked()
{
    if (!this->login_) {
        this->login_ = new Login();
    }

    this->login_->show();

}

