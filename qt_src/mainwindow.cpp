#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

using namespace std;

namespace global {
string selected_usbID;
}

void MainWindow::on_push_enc_clicked()
{
    static const string erase_string = "file://";

    string input_text = ui->lineEdit_file_path->text().toStdString();

    if(input_text.empty()){
        return;
    }

    if(input_text.find(erase_string.c_str()) != string::npos){
        input_text.erase(input_text.find(erase_string.c_str()), erase_string.size());
    }

    //暗号化
    file_enc_c file_enc;
    file_enc.set_file_path(input_text);
    if(file_enc.is_file_exit() == false){
        return;
    }
    if(file_enc.file_enc() == false){
        cerr << "暗号化に失敗しました" << endl;
    }


    //    get_password_wind = new Dialog_password(this);
    //    get_password_wind->set_file_path(input_text);
    //    get_password_wind->show();

    //    cout << "OK: " << get_password_wind->is_ok() << endl;


    cout << input_text << endl;
    ui->lineEdit_file_path->clear();
}

void MainWindow::on_push_dec_clicked()
{
    QString fail_path = ui->lineEdit_file_path->text();
    if(fail_path.size() == 0){
        return;
    }

    static const string erase_string = "file://";
    string input_text = ui->lineEdit_file_path->text().toStdString();
    if(input_text.empty()){
        return;
    }

    if(input_text.find(erase_string.c_str()) != string::npos){
        input_text.erase(input_text.find(erase_string.c_str()), erase_string.size());
    }

    //ファイルが存在するか確認
    file_enc_c file_dec;
    file_dec.set_file_path(input_text);
    if(file_dec.is_file_exit() == false){
        return;
    }
    //復号
    if(file_dec.file_dec() == false){
        cerr << "復号に失敗しました" << endl;
    }
    //    get_dec_pass_wind = new Dialog_dec_pass(this);
    //    get_dec_pass_wind->set_file_path(input_text);
    //    get_dec_pass_wind->show();
    //    ui->lineEdit_file_path->clear();
    ui->lineEdit_file_path->clear();
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->lineEdit_file_path->clear();
}

void MainWindow::on_pushButton_pass_register_clicked()
{
    usb_select_wind = new usb_select(this);
    usb_select_wind->show();
    printf("usbID: %s\n", usb_select_wind->usbID_);
}
