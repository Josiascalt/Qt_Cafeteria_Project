#include "newuserform.h"
#include "ui_newuserform.h"

NewUserForm::NewUserForm(QWidget *parent, cafeteria_app::request_handler::RequestHandler *handler)
    : QWidget(parent)
    , ui(new Ui::NewUserForm)
    , handler_(handler)
{
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    ui->setupUi(this);

}

NewUserForm::~NewUserForm()
{
    delete ui;
}

void NewUserForm::on_save_button__clicked()
{
    using namespace std::literals;

    cafeteria_app::domain::standardized_types::UserPtr user(new cafeteria_app::domain::compound_types::Student);
    if (auto student = dynamic_cast<cafeteria_app::domain::compound_types::Student*>(user.get())) {

        student->SetName(ui->name_->text().toStdString() + " "s + ui->surname_->text().toStdString());
        if (ui->gender_->currentText() == "Male") {
            student->SetGender(cafeteria_app::domain::components::types::Gender::MALE);
        } else {
            student->SetGender(cafeteria_app::domain::components::types::Gender::FEMALE);
        }

        if (auto group = ui->group_->currentText(); group == "TAC - Bilingual Business") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAC::BILINGUAL_BUSINESS_DEPARTMENT));
        } else if (group == "TAC - Health Education") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAC::HEALTH_EDUCATION_DEPARTMENT));
        } else if (group == "TAC - Music") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAC::MUSIC_DEPARTMENT));
        } else if (group == "TAC - Theology") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAC::THEOLOGY_DEPARTMENT));
        } else if (group == "TAIS - 7th") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAIS::SEVENTH_GRADE));
        } else if (group == "TAIS - 8th") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAIS::EIGHTH_GRADE));
        } else if (group == "TAIS - 9th") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAIS::NINTH_GRADE));
        } else if (group == "TAIS - 10th") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAIS::TENTH_GRADE));
        } else if (group == "TAIS - 11th") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAIS::ELEVENTH_GRADE));
        } else if (group == "TAIS - 12th") {
            student->SetGroup(cafeteria_app::domain::components::types::Group(cafeteria_app::domain::components::types::Group::TAIS::TWELFTH_GRADE));
        }
        handler_->AddUser(std::move(user));
    }


    this->close();
}

