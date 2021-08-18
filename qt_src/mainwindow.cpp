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


    get_password_wind = new Dialog_password(this);
    get_password_wind->show();

    cout << "OK: " << get_password_wind->is_ok() << endl;


    cout << input_text << endl;
}

void MainWindow::on_pushButton_debug_clicked()
{
    cout << "OK: " << get_password_wind->is_ok() << endl;
}
