#include "dialog_password.h"
#include "ui_dialog_password.h"

Dialog_password::Dialog_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_password)
{
    ui->setupUi(this);
}

Dialog_password::~Dialog_password()
{
    delete ui;
}


void Dialog_password::on_lineEdit_password_check_textChanged(const QString &arg1)
{
   QString input_pass_ck = arg1;
   QString input_pass_origin = ui->lineEdit_password->text();
   QString  out_put;
   if(input_pass_origin == input_pass_ck){
        out_put.push_back("OK");
   }else{
       out_put.push_back(("NG"));
   }
   ui->label_show_pass_check->setText(out_put);
}
