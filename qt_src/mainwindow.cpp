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
    if(input_text.find(erase_string.c_str()) != string::npos){
        input_text.erase(input_text.find(erase_string.c_str()), erase_string.size());
    }


    cout << input_text << endl;
}
