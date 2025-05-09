#include "dashboard.h"
#include "ui_dashboard.h"
#include <iostream>

Dashboard::Dashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
    , login_(nullptr)
{
    ui->setupUi(this);
    this->on_home_tab_button__clicked();
    //ui->tab_display_->hide();
}

Dashboard::~Dashboard()
{
    if (login_) {
        delete login_;
    }

    delete ui;
}

void Dashboard::on_home_tab_button__clicked()
{
    ui->database_tab_->hide();
    ui->home_tab_->show();
}


void Dashboard::on_database_tab_button__clicked()
{
    ui->home_tab_->hide();
    ui->database_tab_->show();
}

void Dashboard::on_log_button__clicked()
{
    if (!this->login_){
        this->login_ = new Login{};
    }

    this->login_->show();
}

