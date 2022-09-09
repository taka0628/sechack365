#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

using namespace std;

namespace global {
string selected_usbID;
}

void MainWindow::error_messege_box(QString message)
{
    QMessageBox mbox(this);
    mbox.setText(message);
    mbox.exec();
    return;
}

void MainWindow::on_push_enc_clicked()
{

    string input_text = ui->lineEdit_file_path->text().toStdString();

    if (input_text.empty()) {
        return;
    }
    //パスワード入力
    pass_check pass_check_window;
    if (pass_check_window.exec()) {
        return;
    }

    // file:の文字を消去
    static const string erase_string = "file://";
    if (input_text.find(erase_string.c_str()) != string::npos) {
        input_text.erase(input_text.find(erase_string.c_str()),
            erase_string.size());
    }
    // USB idの取得
    device_c usb;
    if (!usb.set_usbID_form_file()) {
        ERROR("usbIDを取得できません");
        this->error_messege_box("usbIDをファイルから取得できません");
        return;
    }
    if (!usb.has_serial(usb.get_usbID())) {
        ERROR("USBシリアルを取得できません");
        this->error_messege_box("USBのシリアル番号を取得できません");
        return;
    }

    // Mkeyの復号
    master_key_c mkey;

    //鍵リストの復号
    key_list_c keylist;
    if (!keylist.decrypt(mkey.get_master_key(usb.get_usbID(), pass_check_window.get_pass()))) {
        ERROR("鍵リストの復号に失敗");
        PUSH_VALUE(usb.get_usbID());
        PUSH_VALUE(pass_check_window.get_pass());
        this->error_messege_box("鍵リストの復号に失敗");
        return;
    }

    //暗号化
    file_enc_c file_enc;
    file_enc.set_file_path(input_text);
    if (file_enc.is_file_exit() == false) {
        ERROR("ファイルが存在しません");
        this->error_messege_box("ファイルが存在しません");
        return;
    }
    if (file_enc.file_enc() == false) {
        this->error_messege_box("ファイルの暗号化に失敗");
        return;
    }

    if (!keylist.encrypt(mkey.get_master_key(usb.get_usbID(), pass_check_window.get_pass()))) {
        ERROR("鍵リストの暗号化に失敗");
        PUSH_VALUE(usb.get_usbID());
        PUSH_VALUE(pass_check_window.get_pass());
        this->error_messege_box("鍵リストの暗号化に失敗");
        return;
    }
    ui->lineEdit_file_path->clear();
}

void MainWindow::on_push_dec_clicked()
{
    QString fail_path = ui->lineEdit_file_path->text();
    if (fail_path.size() == 0) {
        return;
    }

    static const string erase_string = "file://";
    string input_text                = ui->lineEdit_file_path->text().toStdString();
    if (input_text.empty()) {
        return;
    }
    // file:の文字を消去
    if (input_text.find(erase_string.c_str()) != string::npos) {
        input_text.erase(input_text.find(erase_string.c_str()),
            erase_string.size());
    }

    //ファイルが存在するか確認
    file_enc_c file_dec;
    file_dec.set_file_path(input_text);
    if (file_dec.is_file_exit() == false) {
        this->error_messege_box("ファイルが存在しません");
        return;
    }
    //パスワード入力
    pass_check pass_check_window;
    if (pass_check_window.exec()) {
        return;
    }

    // USB idの取得
    device_c usb;
    usb.set_usbID_form_file();
    if (!usb.has_serial(usb.get_usbID())) {
        ERROR("USBシリアルを取得できません");
        this->error_messege_box("USBのシリアル番号を取得できません");
        return;
    }

    // Mkeyの復号
    master_key_c mkey;

    //鍵リストの復号
    key_list_c keylist;
    if (!keylist.decrypt(mkey.get_master_key(usb.get_usbID(), pass_check_window.get_pass()))) {
        ERROR("鍵リストの復号に失敗");
        PUSH_VALUE(usb.get_usbID());
        PUSH_VALUE(pass_check_window.get_pass());
        this->error_messege_box("鍵リストの復号に失敗");
        return;
    }

    //復号
    if (file_dec.file_dec() == false) {
        this->error_messege_box("ファイルの復号に失敗");
        return;
    }
    if (!keylist.encrypt(mkey.get_master_key(usb.get_usbID(), pass_check_window.get_pass()))) {
        ERROR("鍵リストの暗号化に失敗");
        PUSH_VALUE(usb.get_usbID());
        PUSH_VALUE(pass_check_window.get_pass());
        this->error_messege_box("鍵リストの暗号化に失敗");
        return;
    }



    ui->lineEdit_file_path->clear();
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->lineEdit_file_path->clear();
}


// USBのセット
void MainWindow::on_action_menue_USBSetting_triggered()
{
    usb_select usb_select_wind;
    if (usb_select_wind.exec()) {
        return;
    }
    pass_check pass_window;
    if (pass_window.exec()) {
        return;
    }
    master_key_c mkey;
    device_c usb;
    if (!usb.set_usbID_form_file()) {
        ERROR("USBIDをセットできません");
        return;
    }
    if (mkey.add_authorization(usb.get_usbID(), pass_window.get_pass(), usb_select_wind.usbID_)) {
        ERROR("Mkeyの共通鍵を追加できません");
        return;
    }

    ui->label_usb_debug->setText(QString::fromStdString(usb_select_wind.usbID_));
}

//初期化
void MainWindow::on_action_menue_Init_triggered()
{
    Dialog_password pass_window;
    if (pass_window.exec()) {
        return;
    }
    usb_select usb_select_window;
    if (usb_select_window.exec()) {
        return;
    }
    master_key_c mkey;
    if (!mkey.init(usb_select_window.usbID_, pass_window.get_pass())) {
        ERROR("初期化できません");
        exit(1);
    }
    key_list_c keylist;
    if (!keylist.init()) {
        ERROR("鍵リストの初期化に失敗");
        exit(1);
    }
    if (!keylist.encrypt(mkey.get_master_key())) {
        ERROR("鍵リストの暗号化に失敗");
        exit(1);
    }
    // cout << "usb id: " << usb_select_window.usbID_ << "\n"
    //  << "pass: " << pass_window.get_pass() << endl;
    return;
}
