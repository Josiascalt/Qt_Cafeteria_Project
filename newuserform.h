#ifndef NEWUSERFORM_H
#define NEWUSERFORM_H

#include <QWidget>

#include "core/request_handler.h"

namespace Ui {
class NewUserForm;
}

class NewUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewUserForm(QWidget *parent = nullptr, catalogue::request_handler::RequestHandler *handler = nullptr);
    ~NewUserForm();

private slots:
    void on_save_button__clicked();

private:
    Ui::NewUserForm *ui;
    catalogue::request_handler::RequestHandler *handler_;
};

#endif // NEWUSERFORM_H
