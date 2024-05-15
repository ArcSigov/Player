#include "settings.h"
#include "ui_settings.h"
#include <QDebug>
Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    connect(ui->synchr,&QCheckBox::clicked,ui->mfpu_type,&QGroupBox::setEnabled);
    connect(ui->ok,&QPushButton::clicked,this,&Settings::makeInfo);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinMaxButtonsHint);
    ui->kk->setVisible(false);
    ui->sn->setVisible(false);
    ui->so->setVisible(false);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::makeInfo()
{
    s.num_mfpu = 0;
    if (ui->mfpu_type->isEnabled())
    {
        if (ui->kk->isChecked()) s.num_mfpu = 1;
        if (ui->sn->isChecked()) s.num_mfpu = 2;
        if (ui->so->isChecked()) s.num_mfpu = 3;
    }
    if (ui->expanded->isChecked()) s.treetype = 1;
    if (ui->notexpanded->isChecked()) s.treetype = 0;
    emit settingsChecked(s);
    close();
}

void Settings::EnableNum(const size_t& num)
{
    switch (num)
    {
        case 0: ui->kk->setVisible(true); break;
        case 1: ui->sn->setVisible(true); break;
        case 2: ui->so->setVisible(true); break;
        default: break;
    }
}
