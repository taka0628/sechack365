#include "dialog_dec_pass.h"
#include "ui_dialog_dec_pass.h"

Dialog_dec_pass::Dialog_dec_pass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_dec_pass)
{
    ui->setupUi(this);
}

Dialog_dec_pass::~Dialog_dec_pass()
{
    delete ui;
}

using namespace std;

//ファイル復号
void Dialog_dec_pass::on_buttonBox_accepted()
{
    QString pass = ui->lineEdit_dec_pass->text();
    if(pass.size() == 0){
        return;
    }

//    ファイルパス渡し
    file_enc_c file_dec;
    file_dec.set_file_path(this->file_path_);
    if(file_dec.is_file_exit() == false){
        return;
    }

    //復号
    auto start = chrono::system_clock::now();
    file_dec.set_password(ui->lineEdit_dec_pass->text().toStdString());
    if(file_dec.file_dec() == false){
        cerr << "復号に失敗しました" << endl;
    }
    auto end = std::chrono::system_clock::now();
    auto dur = end - start;
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    // 要した時間をミリ秒（1/1000秒）に変換して表示
    std::cout << msec << " milli sec" << endl;
    this->close();
}

void Dialog_dec_pass::set_file_path(string file_path){
    this->file_path_ = file_path;
}
