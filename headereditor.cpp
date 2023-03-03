#include "headereditor.h"
#include "ui_headereditor.h"

headereditor::headereditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::headereditor)
{
    ui->setupUi(this);
    connect (ui->ok)
}

headereditor::~headereditor()
{
    delete ui;
}
void headereditor::editname(const QString&)
{



}
