#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent, cafeteria_app::CoreHandler *core)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
    , core_(core)
    , new_user_form_(nullptr)

{
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    ui->database_viewer_->setColumnCount(3);
    ui->database_viewer_->setRowCount(1);
    for (int i = 0; i < 3; i++) {
        ui->database_viewer_->setColumnWidth(i, (ui->database_viewer_->width()/3));
    }

    ui->database_viewer_->setItem(0,0, new QTableWidgetItem(QString("Name")));
    ui->database_viewer_->setItem(0,1, new QTableWidgetItem(QString("Gender")));
    ui->database_viewer_->setItem(0,2, new QTableWidgetItem(QString("Group")));
    /*if (handler_) {
        for (const auto& user : handler_->GetUsers()) {
            ui->database_viewer_->insertRow(1);
            if (auto student = dynamic_cast<const cafeteria_app::domain::compound_types::Student*>(user.get())) {
                ui->database_viewer_->setItem(1,0, new QTableWidgetItem(student->GetName().c_str()));
                ui->database_viewer_->setItem(1,1, new QTableWidgetItem(student->GetGender() == cafeteria_app::domain::components::types::Gender::MALE ? "Male" : "Female"));
                ui->database_viewer_->setItem(1,2, new QTableWidgetItem(student->GetGroup().IsTAC() ? "TAC" : "TAIS"));
            }
        }
    }*/

}

Dashboard::~Dashboard()
{
    delete new_user_form_;
    delete ui;
}


void Dashboard::on_exit_button__clicked()
{

}


void Dashboard::on_home_tab_button__clicked()
{
    ui->home_tab_->show();
    ui->database_tab_->hide();
}


void Dashboard::on_database_tab_button__clicked()
{
    ui->home_tab_->hide();
    ui->database_tab_->show();

}


void Dashboard::on_add_user_button__clicked()
{
    if (!new_user_form_) {
        new_user_form_ = new NewUserForm(nullptr/*, handler_*/);
    }

    new_user_form_->show();
}

