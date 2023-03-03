#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent, PageCreator *p)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , insertSettings(new InsertingSettings(this))
{
    ui->setupUi(this);

    ui->PlanPol->setStyle(btnstyle::white_text_black_background);
    ui->VypPol->setStyle(btnstyle::white_text_black_background);
    ui->PryamoNA->setStyle(btnstyle::white_text_black_background);
    ui->da19->setStyle(btnstyle::white_text_black_background);
    ui->SUO->setStyle(btnstyle::white_text_black_background);
    ui->BASU->setStyle(btnstyle::white_text_black_background);
    ui->PolDann->setStyle(btnstyle::white_text_black_background);
    ui->NAV->setStyle(btnstyle::white_text_black_background);
    ui->ISP->setStyle(btnstyle::white_text_black_background);
    ui->RTS->setStyle(btnstyle::white_text_black_background);
    ui->Maneur->setStyle(btnstyle::white_text_black_background);
    ui->ArvArp->setStyle(btnstyle::white_text_black_background);
    ui->KORR->setStyle(btnstyle::white_text_black_background);
    ui->Tzad->setStyle(btnstyle::white_text_black_background);
    ui->InfBKS->setStyle(btnstyle::white_text_black_background);
    ui->ENG->setStyle(btnstyle::white_text_black_background);
    ui->UprMFPU->setStyle(btnstyle::white_text_black_background);
    ui->IIPE->setStyle(btnstyle::white_text_black_background);
    ui->CIFR->setStyle(btnstyle::white_text_black_background);
    ui->empty->setStyle(btnstyle::white_text_black_background);
    ui->q->setStyle(btnstyle::white_text_black_background);
    ui->w->setStyle(btnstyle::white_text_black_background);
    ui->e->setStyle(btnstyle::white_text_black_background);
    ui->r->setStyle(btnstyle::white_text_black_background);
    ui->t->setStyle(btnstyle::white_text_black_background);
    ui->y->setStyle(btnstyle::white_text_black_background);
    ui->u->setStyle(btnstyle::white_text_black_background);
    ui->i->setStyle(btnstyle::white_text_black_background);
    ui->o->setStyle(btnstyle::white_text_black_background);
    ui->p->setStyle(btnstyle::white_text_black_background);
    ui->ruX->setStyle(btnstyle::white_text_black_background);
    ui->a->setStyle(btnstyle::white_text_black_background);
    ui->s->setStyle(btnstyle::white_text_black_background);
    ui->d->setStyle(btnstyle::white_text_black_background);
    ui->f->setStyle(btnstyle::white_text_black_background);
    ui->g->setStyle(btnstyle::white_text_black_background);
    ui->h->setStyle(btnstyle::white_text_black_background);
    ui->j->setStyle(btnstyle::white_text_black_background);
    ui->k->setStyle(btnstyle::white_text_black_background);
    ui->l->setStyle(btnstyle::white_text_black_background);
    ui->ruG->setStyle(btnstyle::white_text_black_background);
    ui->ruA->setStyle(btnstyle::white_text_black_background);
    ui->z->setStyle(btnstyle::white_text_black_background);
    ui->x->setStyle(btnstyle::white_text_black_background);
    ui->c->setStyle(btnstyle::white_text_black_background);
    ui->v->setStyle(btnstyle::white_text_black_background);
    ui->b->setStyle(btnstyle::white_text_black_background);
    ui->n->setStyle(btnstyle::white_text_black_background);
    ui->m->setStyle(btnstyle::white_text_black_background);
    ui->ruB->setStyle(btnstyle::white_text_black_background);
    ui->ruU->setStyle(btnstyle::white_text_black_background);
    ui->ruTznak->setStyle(btnstyle::white_text_black_background);
    ui->vvd->setStyle(btnstyle::white_text_black_background);
    ui->one->setStyle(btnstyle::white_text_black_background);
    ui->two->setStyle(btnstyle::white_text_black_background);
    ui->three->setStyle(btnstyle::white_text_black_background);
    ui->four->setStyle(btnstyle::white_text_black_background);
    ui->five->setStyle(btnstyle::white_text_black_background);
    ui->six->setStyle(btnstyle::white_text_black_background);
    ui->seven->setStyle(btnstyle::white_text_black_background);
    ui->eight->setStyle(btnstyle::white_text_black_background);
    ui->nine->setStyle(btnstyle::white_text_black_background);
    ui->zero->setStyle(btnstyle::white_text_black_background);
    ui->PlusMinus->setStyle(btnstyle::white_text_black_background);
    ui->_->setStyle(btnstyle::white_text_black_background);
    ui->clear->setStyle(btnstyle::white_text_black_background);
    ui->menu->setStyle(btnstyle::white_text_black_background);
    ui->sbros->setStyle(btnstyle::white_text_black_background);

    ui->kvs1l->setStyle(btnstyle::black_background);
    ui->kvs2l->setStyle(btnstyle::black_background);
    ui->kvs3l->setStyle(btnstyle::black_background);
    ui->kvs4l->setStyle(btnstyle::black_background);
    ui->kvs5l->setStyle(btnstyle::black_background);
    ui->kvs1r->setStyle(btnstyle::black_background);
    ui->kvs2r->setStyle(btnstyle::black_background);
    ui->kvs3r->setStyle(btnstyle::black_background);
    ui->kvs4r->setStyle(btnstyle::black_background);
    ui->kvs5r->setStyle(btnstyle::black_background);

    connect(insertSettings,&InsertingSettings::Text,this,&MainWindow::Text);

    connect(ui->kvs1l,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->kvs2l,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->kvs3l,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->kvs4l,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->kvs5l,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);

    connect(ui->kvs1r,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->kvs2r,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->kvs3r,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->kvs4r,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->kvs5r,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);

    connect(ui->eight,&MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->four, &MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);
    connect(ui->six,  &MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);

    connect(ui->empty,  &MyButton::doubleClicked,insertSettings,&InsertingSettings::runEditing);

    connect(ui->kvs1l,&MyButton::oneClicked,p,&PageCreator::SwitchPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_kvs1l_clicked()
{

}



