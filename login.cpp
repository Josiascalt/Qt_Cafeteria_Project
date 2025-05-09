#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent, cafeteria_app::CoreHandler *core)
    : QWidget(parent)
    , ui(new Ui::Login)
    , core_(core)
{
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_button__clicked()
{

}

