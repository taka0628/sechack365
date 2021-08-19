#include "dialog_password.h"
#include "ui_dialog_password.h"

using namespace std;

bool IS_PASSWORD_CORRECT;

Dialog_password::Dialog_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_password)
{
    ui->setupUi(this);

    IS_PASSWORD_CORRECT = false;
    this->is_canceled_ = false;
    this->is_ok_ = false;
}

Dialog_password::~Dialog_password()
{
    delete ui;
}

bool Dialog_password::is_ok() const{
    return this->is_ok_;
}

bool Dialog_password::is_calcel() const{
    return this->is_canceled_;
}

void Dialog_password::set_file_path(string file_path){
    this->file_path_ = file_path;
}


void Dialog_password::on_lineEdit_password_check_textChanged(const QString &arg1)
{
   QString input_pass_ck = arg1;
   QString input_pass_origin = ui->lineEdit_password->text();
   QString  out_put;
   if(input_pass_origin == input_pass_ck){
        out_put.push_back("OK");
        IS_PASSWORD_CORRECT = true;
   }else{
       out_put.push_back(("NG"));
       IS_PASSWORD_CORRECT = false;
   }
   ui->label_show_pass_check->setText(out_put);
}

//暗号化を行う
void Dialog_password::on_pushButton_OK_clicked()
{
    if(!IS_PASSWORD_CORRECT){
        return;
    }

     this->is_ok_ = true;
     file_enc_c file_enc;
     file_enc.set_file_path(this->file_path_);
     if(file_enc.is_file_exit() == false){
         return;
     }

     file_enc.set_password(ui->lineEdit_password->text().toStdString());
     if(file_enc.file_enc() == false){
         cerr << "暗号化に失敗しました" << endl;
     }
     this->close();
}

void Dialog_password::on_pushButton_Cancel_clicked()
{
    this->close();
}
