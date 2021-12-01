#include "pass_check.h"
#include "ui_pass_check.h"

pass_check::pass_check(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pass_check)
{
    ui->setupUi(this);
}

pass_check::~pass_check()
{
    delete ui;
}
