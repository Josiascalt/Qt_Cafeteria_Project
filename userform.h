#ifndef USERFORM_H
#define USERFORM_H

#include <QWidget>

//#include "core/request_handler.h"

namespace Ui {
class UserForm;
}

class UserForm : public QWidget
{
    Q_OBJECT

public:
    explicit UserForm(QWidget *parent = nullptr/*, cafeteria_app::request_handler::RequestHandler *handler = nullptr*/);
    ~UserForm();

private slots:
    void on_save_button__clicked();

private:
    Ui::UserForm *ui;
    //cafeteria_app::request_handler::RequestHandler *handler_;
};

#endif // USERFORM_H
