
#include "loginform.h"
#include "ui_loginform.h"


LoginForm::LoginForm(QWidget *parent, catalogue::request_handler::RequestHandler *handler)
    : QMainWindow(parent)
    , ui(new Ui::LoginForm)
    , dashboard_(nullptr)
    , handler_(handler)
{
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete dashboard_;
    delete ui;
}

void LoginForm::on_login_button__clicked()
{
    if (!dashboard_) {
        dashboard_ = new Dashboard(nullptr, handler_, this);
    }

    this->hide();
    dashboard_->show();
}

