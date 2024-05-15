#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QDebug>
#include <QStyle>
#include <QDirIterator>
#include <QFileDialog>
#include <QDateTime>
#include <QSlider>
#include <QTreeWidgetItem>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    codec =  QTextCodec::codecForName("CP1251");
    treemanager = new TreeManager(ui->treeWidget,this);

    //ui->mfpu1


    pults[0].diods.push_back(ui->planpolled);   //ms->button_fires_1_b.plan
    pults[0].diods.push_back(ui->vyppolled);    //ms->button_fires_1_b.active_route
    pults[0].diods.push_back(ui->prymonaled);   //ms->button_fires_1_b.comb
    pults[0].diods.push_back(ui->rtsled);       //ms->button_fires_2_b.rts
    pults[0].diods.push_back(ui->led19);        //ms->button_fires_1_b.u19
    pults[0].diods.push_back(ui->basuled);      //ms->button_fires_1_b.basu
    pults[0].diods.push_back(ui->poldanled);    //ms->button_fires_1_b.flight_data
    pults[0].diods.push_back(ui->suoled);       //ms->button_fires_1_b.suo
    pults[0].diods.push_back(ui->navled);       //ms->button_fires_1_b.nav
    pults[0].diods.push_back(ui->tzadled);      //ms->button_fires_2_b.selected_time
    pults[0].diods.push_back(ui->manevrled);    //ms->button_fires_2_b.maneuver
    pults[0].diods.push_back(ui->ispled);       //ms->button_fires_2_b.isp
    pults[0].diods.push_back(ui->arvarpled);    //ms->button_fires_2_b.arv_arp
    pults[0].diods.push_back(ui->korrled);      //ms->button_fires_2_b.corr
    pults[0].diods.push_back(ui->infbksled);    //ms->button_fires_2_b.bks
    pults[0].diods.push_back(ui->mastermfpuled);
    pults[0].diods.push_back(ui->iipeled);
    pults[0].diods.push_back(ui->cyfrled);
    pults[0].diods.push_back(ui->engled);

    pults[1].diods.push_back(ui->planpolled_2);
    pults[1].diods.push_back(ui->vyppolled_2);
    pults[1].diods.push_back(ui->prymonaled_2);
    pults[1].diods.push_back(ui->rtsled_2);
    pults[1].diods.push_back(ui->led19_2);
    pults[1].diods.push_back(ui->basuled_2);
    pults[1].diods.push_back(ui->poldanled_2);
    pults[1].diods.push_back(ui->suoled_2);
    pults[1].diods.push_back(ui->navled_2);
    pults[1].diods.push_back(ui->tzadled_2);
    pults[1].diods.push_back(ui->manevrled_2);
    pults[1].diods.push_back(ui->ispled_2);
    pults[1].diods.push_back(ui->arvarpled_2);
    pults[1].diods.push_back(ui->korrled_2);
    pults[1].diods.push_back(ui->infbksled_2);
    pults[1].diods.push_back(ui->mastermfpuled_2);
    pults[1].diods.push_back(ui->iipeled_2);
    pults[1].diods.push_back(ui->cyfrled_2);
    pults[1].diods.push_back(ui->engled_2);

    pults[2].diods.push_back(ui->planpolled_3);
    pults[2].diods.push_back(ui->vyppolled_3);
    pults[2].diods.push_back(ui->prymonaled_3);
    pults[2].diods.push_back(ui->rtsled_3);
    pults[2].diods.push_back(ui->led19_3);
    pults[2].diods.push_back(ui->basuled_3);
    pults[2].diods.push_back(ui->poldanled_3);
    pults[2].diods.push_back(ui->suoled_3);
    pults[2].diods.push_back(ui->navled_3);
    pults[2].diods.push_back(ui->tzadled_3);
    pults[2].diods.push_back(ui->manevrled_3);
    pults[2].diods.push_back(ui->ispled_3);
    pults[2].diods.push_back(ui->arvarpled_3);
    pults[2].diods.push_back(ui->korrled_3);
    pults[2].diods.push_back(ui->infbksled_3);
    pults[2].diods.push_back(ui->mastermfpuled_3);
    pults[2].diods.push_back(ui->iipeled_3);
    pults[2].diods.push_back(ui->cyfrled_3);
    pults[2].diods.push_back(ui->engled_3);


    pults[0].btns[1]=ui->kvs5l;
    pults[0].btns[2]=ui->kvs4l;
    pults[0].btns[3]=ui->kvs3l;
    pults[0].btns[4]=ui->kvs2l;
    pults[0].btns[5]=ui->kvs1l;
    pults[0].btns[6]=ui->PlanPol;
    pults[0].btns[7]=ui->VypPol;
    pults[0].btns[8]=ui->PryamoNA;
    pults[0].btns[9]=ui->da19;
    pults[0].btns[10]=ui->SUO;
    pults[0].btns[11]=ui->BASU;
    pults[0].btns[12]=ui->PolDann;
    pults[0].btns[17]=ui->NAV;
    pults[0].btns[18]=ui->Tzad;
    pults[0].btns[19]=ui->RTS;
    pults[0].btns[20]=ui->Maneur;


    pults[0].btns[21]=ui->ArvArp;
    pults[0].btns[22]=ui->KORR;
    pults[0].btns[23]=ui->ISP;
    pults[0].btns[24]=ui->kvs5r;
    pults[0].btns[25]=ui->kvs4r;
    pults[0].btns[26]=ui->kvs3r;
    pults[0].btns[27]=ui->kvs2r;
    pults[0].btns[28]=ui->kvs1r;
    pults[0].btns[33]=ui->q;
    pults[0].btns[34]=ui->w;
    pults[0].btns[35]=ui->e;
    pults[0].btns[36]=ui->r;
    pults[0].btns[37]=ui->t;
    pults[0].btns[38]=ui->y;
    pults[0].btns[39]=ui->u;
    pults[0].btns[40]=ui->i;

    pults[0].btns[41]=ui->o;
    pults[0].btns[42]=ui->p;
    pults[0].btns[43]=ui->ruX;
    pults[0].btns[50]=ui->a;
    pults[0].btns[51]=ui->s;
    pults[0].btns[52]=ui->d;
    pults[0].btns[53]=ui->f;
    pults[0].btns[54]=ui->g;
    pults[0].btns[55]=ui->h;
    pults[0].btns[56]=ui->j;
    pults[0].btns[57]=ui->k;
    pults[0].btns[58]=ui->l;
    pults[0].btns[59]=ui->ruG;
    pults[0].btns[60]=ui->ruA;
    pults[0].btns[65]=ui->z;
    pults[0].btns[66]=ui->x;

    pults[0].btns[67]=ui->c;
    pults[0].btns[68]=ui->v;
    pults[0].btns[69]=ui->b;
    pults[0].btns[70]=ui->n;
    pults[0].btns[71]=ui->m;
    pults[0].btns[72]=ui->ruB;
    pults[0].btns[73]=ui->ruU;
    pults[0].btns[74]=ui->ruTznak;
    pults[0].btns[75]=ui->vvd;
    pults[0].btns[81]=ui->brplus;
    pults[0].btns[82]=ui->brminus;
    pults[0].btns[83]=ui->UprMFPU;
    pults[0].btns[84]=ui->InfBKS;
    pults[0].btns[85]=ui->ENG;
    pults[0].btns[86]=ui->zero;
    pults[0].btns[87]=ui->one;

    pults[0].btns[88]=ui->two;
    pults[0].btns[89]=ui->three;
    pults[0].btns[90]=ui->clear;
    pults[0].btns[91]=ui->menu;
    pults[0].btns[92]=ui->sbros;
    pults[0].btns[97]=ui->IIPE;
    pults[0].btns[98]=ui->empty;
    pults[0].btns[99]=ui->CIFR;
    pults[0].btns[100]=ui->_;
    pults[0].btns[101]=ui->PlusMinus;
    pults[0].btns[102]=ui->four;
    pults[0].btns[103]=ui->seven;
    pults[0].btns[104]=ui->eight;
    pults[0].btns[105]=ui->five;
    pults[0].btns[106]=ui->six;
    pults[0].btns[107]=ui->nine;

    pults[1].btns[1]=ui->kvs5l_2;
    pults[1].btns[2]=ui->kvs4l_2;
    pults[1].btns[3]=ui->kvs3l_2;
    pults[1].btns[4]=ui->kvs2l_2;
    pults[1].btns[5]=ui->kvs1l_2;
    pults[1].btns[6]=ui->PlanPol_2;
    pults[1].btns[7]=ui->VypPol_2;
    pults[1].btns[8]=ui->PryamoNA_2;
    pults[1].btns[9]=ui->da19_2;
    pults[1].btns[10]=ui->SUO_2;
    pults[1].btns[11]=ui->BASU_2;
    pults[1].btns[12]=ui->PolDann_2;
    pults[1].btns[17]=ui->NAV_2;
    pults[1].btns[18]=ui->Tzad_2;
    pults[1].btns[19]=ui->RTS_2;
    pults[1].btns[20]=ui->Maneur_2;


    pults[1].btns[21]=ui->ArvArp_2;
    pults[1].btns[22]=ui->KORR_2;
    pults[1].btns[23]=ui->ISP_2;
    pults[1].btns[24]=ui->kvs5r_2;
    pults[1].btns[25]=ui->kvs4r_2;
    pults[1].btns[26]=ui->kvs3r_2;
    pults[1].btns[27]=ui->kvs2r_2;
    pults[1].btns[28]=ui->kvs1r_2;
    pults[1].btns[33]=ui->q_2;
    pults[1].btns[34]=ui->w_2;
    pults[1].btns[35]=ui->e_2;
    pults[1].btns[36]=ui->r_2;
    pults[1].btns[37]=ui->t_2;
    pults[1].btns[38]=ui->y_2;
    pults[1].btns[39]=ui->u_2;
    pults[1].btns[40]=ui->i_2;

    pults[1].btns[41]=ui->o_2;
    pults[1].btns[42]=ui->p_2;
    pults[1].btns[43]=ui->ruX_2;
    pults[1].btns[50]=ui->a_2;
    pults[1].btns[51]=ui->s_2;
    pults[1].btns[52]=ui->d_2;
    pults[1].btns[53]=ui->f_2;
    pults[1].btns[54]=ui->g_2;
    pults[1].btns[55]=ui->h_2;
    pults[1].btns[56]=ui->j_2;
    pults[1].btns[57]=ui->k_2;
    pults[1].btns[58]=ui->l_2;
    pults[1].btns[59]=ui->ruG_2;
    pults[1].btns[60]=ui->ruA_2;
    pults[1].btns[65]=ui->z_2;
    pults[1].btns[66]=ui->x_2;

    pults[1].btns[67]=ui->c_2;
    pults[1].btns[68]=ui->v_2;
    pults[1].btns[69]=ui->b_2;
    pults[1].btns[70]=ui->n_2;
    pults[1].btns[71]=ui->m_2;
    pults[1].btns[72]=ui->ruB_2;
    pults[1].btns[73]=ui->ruU_2;
    pults[1].btns[74]=ui->ruTznak_2;
    pults[1].btns[75]=ui->vvd_2;
    pults[1].btns[81]=ui->brplus_2;
    pults[1].btns[82]=ui->brminus_2;
    pults[1].btns[83]=ui->UprMFPU_2;
    pults[1].btns[84]=ui->InfBKS_2;
    pults[1].btns[85]=ui->ENG_2;
    pults[1].btns[86]=ui->zero_2;
    pults[1].btns[87]=ui->one_2;

    pults[1].btns[88]=ui->two_2;
    pults[1].btns[89]=ui->three_2;
    pults[1].btns[90]=ui->clear_2;
    pults[1].btns[91]=ui->menu_3;
    pults[1].btns[92]=ui->sbros_2;
    pults[1].btns[97]=ui->IIPE_2;
    pults[1].btns[98]=ui->empty_2;
    pults[1].btns[99]=ui->CIFR_2;
    pults[1].btns[100]=ui->_1;
    pults[1].btns[101]=ui->PlusMinus_2;
    pults[1].btns[102]=ui->four_2;
    pults[1].btns[103]=ui->seven_2;
    pults[1].btns[104]=ui->eight_2;
    pults[1].btns[105]=ui->five_2;
    pults[1].btns[106]=ui->six_2;
    pults[1].btns[107]=ui->nine_2;

    pults[2].btns[1]=ui->kvs5l_3;
    pults[2].btns[2]=ui->kvs4l_3;
    pults[2].btns[3]=ui->kvs3l_3;
    pults[2].btns[4]=ui->kvs2l_3;
    pults[2].btns[5]=ui->kvs1l_3;
    pults[2].btns[6]=ui->PlanPol_3;
    pults[2].btns[7]=ui->VypPol_3;
    pults[2].btns[8]=ui->PryamoNA_3;
    pults[2].btns[9]=ui->da19_3;
    pults[2].btns[10]=ui->SUO_3;
    pults[2].btns[11]=ui->BASU_3;
    pults[2].btns[12]=ui->PolDann_3;
    pults[2].btns[17]=ui->NAV_3;
    pults[2].btns[18]=ui->Tzad_3;
    pults[2].btns[19]=ui->RTS_3;
    pults[2].btns[20]=ui->Maneur_3;


    pults[2].btns[21]=ui->ArvArp_3;
    pults[2].btns[22]=ui->KORR_3;
    pults[2].btns[23]=ui->ISP_3;
    pults[2].btns[24]=ui->kvs5r_3;
    pults[2].btns[25]=ui->kvs4r_3;
    pults[2].btns[26]=ui->kvs3r_3;
    pults[2].btns[27]=ui->kvs2r_3;
    pults[2].btns[28]=ui->kvs1r_3;
    pults[2].btns[33]=ui->q_3;
    pults[2].btns[34]=ui->w_3;
    pults[2].btns[35]=ui->e_3;
    pults[2].btns[36]=ui->r_3;
    pults[2].btns[37]=ui->t_3;
    pults[2].btns[38]=ui->y_3;
    pults[2].btns[39]=ui->u_3;
    pults[2].btns[40]=ui->i_3;

    pults[2].btns[41]=ui->o_3;
    pults[2].btns[42]=ui->p_3;
    pults[2].btns[43]=ui->ruX_3;
    pults[2].btns[50]=ui->a_3;
    pults[2].btns[51]=ui->s_3;
    pults[2].btns[52]=ui->d_3;
    pults[2].btns[53]=ui->f_3;
    pults[2].btns[54]=ui->g_3;
    pults[2].btns[55]=ui->h_3;
    pults[2].btns[56]=ui->j_3;
    pults[2].btns[57]=ui->k_3;
    pults[2].btns[58]=ui->l_3;
    pults[2].btns[59]=ui->ruG_3;
    pults[2].btns[60]=ui->ruA_3;
    pults[2].btns[65]=ui->z_3;
    pults[2].btns[66]=ui->x_3;

    pults[2].btns[67]=ui->c_3;
    pults[2].btns[68]=ui->v_3;
    pults[2].btns[69]=ui->b_3;
    pults[2].btns[70]=ui->n_3;
    pults[2].btns[71]=ui->m_3;
    pults[2].btns[72]=ui->ruB_3;
    pults[2].btns[73]=ui->ruU_3;
    pults[2].btns[74]=ui->ruTznak_3;
    pults[2].btns[75]=ui->vvd_3;
    pults[2].btns[81]=ui->brplus_3;
    pults[2].btns[82]=ui->brminus_3;
    pults[2].btns[83]=ui->UprMFPU_3;
    pults[2].btns[84]=ui->InfBKS_3;
    pults[2].btns[85]=ui->ENG_3;
    pults[2].btns[86]=ui->zero_3;
    pults[2].btns[87]=ui->one_3;

    pults[2].btns[88]=ui->two_3;
    pults[2].btns[89]=ui->three_3;
    pults[2].btns[90]=ui->clear_3;
    pults[2].btns[91]=ui->menu_4;
    pults[2].btns[92]=ui->sbros_3;
    pults[2].btns[97]=ui->IIPE_3;
    pults[2].btns[98]=ui->empty_3;
    pults[2].btns[99]=ui->CIFR_3;
    pults[2].btns[100]=ui->_2;
    pults[2].btns[101]=ui->PlusMinus_3;
    pults[2].btns[102]=ui->four_3;
    pults[2].btns[103]=ui->seven_3;
    pults[2].btns[104]=ui->eight_3;
    pults[2].btns[105]=ui->five_3;
    pults[2].btns[106]=ui->six_3;
    pults[2].btns[107]=ui->nine_3;

    pults[0].display = ui->openGLWidget;
    pults[1].display = ui->openGLWidget_2;
    pults[2].display = ui->openGLWidget_3;

    pults[0].player.step = ui->step_mfpu1;
    pults[1].player.step = ui->step_mfpu2;
    pults[2].player.step = ui->step_mfpu3;

    pults[0].player.play = ui->mfpu1_play;
    pults[1].player.play = ui->mfpu2_play;
    pults[2].player.play = ui->mfpu3_play;

    pults[0].player.stop = ui->mfpu1_pause;
    pults[1].player.stop = ui->mfpu2_pause;
    pults[2].player.stop = ui->mfpu3_pause;

    pults[0].player.next = ui->next;
    pults[1].player.next = ui->next_2;
    pults[2].player.next = ui->next_3;

    pults[0].player.back = ui->back;
    pults[1].player.back = ui->back_2;
    pults[2].player.back = ui->back_3;

    pults[0].player.bar = ui->play_mfpu1;
    pults[1].player.bar = ui->play_mfpu2;
    pults[2].player.bar = ui->play_mfpu3;


    for (auto i = 0 ; i < 3; i++)
    {
        pults[i].ticker = new QTimer(this);
        pults[i].ticker->setInterval(1000);
        pults[i].player.step->setValue(0);
        pults[i].player.bar->setEnabled(false);
        connect(pults[i].ticker,&QTimer::timeout,this,&MainWindow::updatePlayer);
        connect(pults[i].player.play,&QPushButton::clicked,this,&MainWindow::updatePlayer);
        connect(pults[i].player.stop,&QPushButton::clicked,this,&MainWindow::updatePlayer);
        connect(pults[i].player.next,&QPushButton::clicked,this,&MainWindow::updatePlayer);
        connect(pults[i].player.back,&QPushButton::clicked,this,&MainWindow::updatePlayer);
        connect(pults[i].player.step,&QAbstractSlider::sliderReleased,this,&MainWindow::updatePlayer);

        pults[i].player.play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        pults[i].player.stop->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        pults[i].player.next->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
        pults[i].player.back->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    }
    connect(&setts,&Settings::settingsChecked,this,&MainWindow::readSettings);
    connect(ui->action_3,&QAction::triggered,&about,&About::show);

    connect(ui->x1,&QAction::triggered,this,&MainWindow::updatePlayer);
    connect(ui->x2,&QAction::triggered,this,&MainWindow::updatePlayer);
    connect(ui->x4,&QAction::triggered,this,&MainWindow::updatePlayer);
    connect(ui->x8,&QAction::triggered,this,&MainWindow::updatePlayer);
    connect(ui->x16,&QAction::triggered,this,&MainWindow::updatePlayer);
    connect(ui->x25,&QAction::triggered,this,&MainWindow::updatePlayer);
    //connect(ui->action_4,&QAction::triggered,&setts,&Settings::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play(const size_t& pos)
{
    if (pults[pos].frame_data.size() && (pults[pos].player.step->value() < pults[pos].frame_data.size()))
    {
        auto f = pults[pos].frame_data[pults[pos].player.step->value()];
        mfpu_out_b_t out;
        memcpy(&out.data,&f.info.data,sizeof(mfpu_out_sbi_sa_b_t)*12);
        pults[pos].display->draw_data(&out);
        for (auto j = 0 ; j < 12; j++)
        {
           pults[pos].diods[0]      ->    setStyle(f.info.data[j].button_fires_1_b.plan ?         dioistyle::green : dioistyle::black );
           pults[pos].diods[1]      ->    setStyle(f.info.data[j].button_fires_1_b.active_route ? dioistyle::green : dioistyle::black );
           pults[pos].diods[2]      ->    setStyle(f.info.data[j].button_fires_1_b.comb ?         dioistyle::green : dioistyle::black );
           pults[pos].diods[3]      ->    setStyle(f.info.data[j].button_fires_2_b.rts ?          dioistyle::green : dioistyle::black );
           pults[pos].diods[4]      ->    setStyle(f.info.data[j].button_fires_1_b.u19 ?          dioistyle::green : dioistyle::black );
           pults[pos].diods[5]      ->    setStyle(f.info.data[j].button_fires_1_b.basu ?         dioistyle::green : dioistyle::black );
           pults[pos].diods[6]      ->    setStyle(f.info.data[j].button_fires_1_b.flight_data ?  dioistyle::green : dioistyle::black );
           pults[pos].diods[7]      ->    setStyle(f.info.data[j].button_fires_1_b.suo ?          dioistyle::green : dioistyle::black );
           pults[pos].diods[8]      ->    setStyle(f.info.data[j].button_fires_1_b.nav ?          dioistyle::green : dioistyle::black );
           pults[pos].diods[9]      ->    setStyle(f.info.data[j].button_fires_2_b.selected_time ?dioistyle::green : dioistyle::black );
           pults[pos].diods[10]     ->    setStyle(f.info.data[j].button_fires_2_b.maneuver ?     dioistyle::green : dioistyle::black );
           pults[pos].diods[11]     ->    setStyle(f.info.data[j].button_fires_2_b.isp ?          dioistyle::green : dioistyle::black, f.info.data[j].button_fires_2_b.isp);
           pults[pos].diods[12]     ->    setStyle(f.info.data[j].button_fires_2_b.arv_arp ?      dioistyle::green : dioistyle::black );
           pults[pos].diods[13]     ->    setStyle(f.info.data[j].button_fires_2_b.corr ?         dioistyle::green : dioistyle::black );
           pults[pos].diods[14]     ->    setStyle(f.info.data[j].button_fires_2_b.bks ?          dioistyle::green : dioistyle::black );
           pults[pos].diods[15]     ->    setStyle(f.info.data[j].button_fires_2_b.mfpu_control ? dioistyle::green : dioistyle::black );
           pults[pos].diods[16]     ->    setStyle(f.info.data[j].button_fires_2_b.iipa ?         dioistyle::green : dioistyle::black );
           pults[pos].diods[17]     ->    setStyle(f.info.data[j].button_fires_2_b.digits ?       dioistyle::green : dioistyle::black );
           pults[pos].diods[18]     ->    setStyle(f.info.data[j].button_fires_2_b.eng ?          dioistyle::green : dioistyle::black );

            for (const auto& b:qAsConst(pults[pos].btns))
                b->setStyle(btnstyle::white_text_black_background);

            if (f.info.data[j].button_fires_1_b.pressed_button)
            {
                auto btn = pults[pos].btns.find(f.info.data[j].button_fires_1_b.pressed_button);
                if (btn != pults[pos].btns.end())
                    btn.value()->setStyle(btnstyle::clicked);
            }
        }

        switch (pos)
        {
            case 0:
                ui->progress->setText(f.time.toString()+"/"+pults[pos].frame_data.back().time.toString());
                break;
            case 1:
                ui->progress_2->setText(f.time.toString()+"/"+pults[pos].frame_data.back().time.toString());
                break;
            case 2:
                ui->progress_3->setText(f.time.toString()+"/"+pults[pos].frame_data.back().time.toString());
                break;
            default: break;
        }
        pults[pos].player.step->setValue(pults[pos].player.step->value()+1);
    }
    else {
        pults[pos].player.step->setValue(0);
    }
}

void MainWindow::updateData(const QVector<QVector<frame_info>>& data)
{
    for (auto i = 0 ; i < data.size();i++)
    {
        if (data[i].size()> 0)
        {
            setts.EnableNum(i);
            pults[i].frame_data = data[i];
            pults[i].player.step->setMaximum(data[i].size());
            play(i);
        }
    }
}

void MainWindow::readcfg(const QByteArray& cfg)
{
    if (!cfg.size()) this->cfg = QDir::currentPath();
    else             this->cfg = QString::fromStdString(cfg.toStdString());
}

void MainWindow::readfonts(const QByteArray& fnt)
{
    for (const auto& pult:qAsConst(pults))
        pult.display->readFonts(fnt);
}

void MainWindow::defaultShow()
{
    for (auto i = 0 ; i < 3;i++)
    {
        pults[i].frame_data.push_back(initDefaultFrame());
        play(i);
    }
}

void MainWindow::on_open_sbi_triggered()
{
    auto path = QFileDialog::getExistingDirectory(this,"",this->cfg);
    QDirIterator files (path, QStringList() << "*.bin" << "*.txt", QDir::Files);
    if (!path.isEmpty())
    {
        this->cfg = files.filePath();
        while (files.hasNext())
           emit FileChanged(files.next());

        setEnabled(false);
        setts.show();
    }
}

void MainWindow::readSettings(const settings& _s)
{
    setEnabled(true);
    ui->treeWidget->clear();
    QStringList names = {"КК","ШН","ШО"};
    s = _s;
    for (auto i = 0ull; i<3;i++)
    {
        if (pults[i].frame_data.size() > 0)
        {
            pults[i].player.bar->setEnabled(true);
            pults[i].player.bar->setStyleSheet("");
            pults[i].master_num = s.num_mfpu;
            treemanager->createTree(names[i],pults[i].frame_data,s.treetype);
            //если выбран этот МФПУ ведущим
            if (s.num_mfpu && s.num_mfpu == i+1)
            {
                pults[i].player.bar->setStyleSheet("QGroupBox{border: 2px solid green}");
                pults[i].player.play->setEnabled(true);
                pults[i].player.stop->setEnabled(false);
            }
            //если этот не ведущий, но номер выбран
            else if (s.num_mfpu)
            {
                pults[i].player.bar->setEnabled(false);
                pults[i].player.play = pults[s.num_mfpu-1].player.play;
                pults[i].player.stop = pults[s.num_mfpu-1].player.stop;
                pults[i].player.next = pults[s.num_mfpu-1].player.next;
                pults[i].player.back = pults[s.num_mfpu-1].player.back;
            }
            else
            {
                pults[i].player.play->setEnabled(true);
                pults[i].player.stop->setEnabled(false);
            }
        }
    }
}

void MainWindow::updatePlayer()
{
    auto btn = qobject_cast<QPushButton*>(QObject::sender());
    auto timer = qobject_cast<QTimer*>(QObject::sender());
    auto slider = qobject_cast<QSlider*>(QObject::sender());
    auto speed = qobject_cast<QAction*>(QObject::sender());
    for (auto i = 0; i < 3; i++)
    {
        if (btn == pults[i].player.play)
        {
            pults[i].player.play->setEnabled(false);
            pults[i].player.stop->setEnabled(true);
            pults[i].ticker->start();
        }
        else if (btn == pults[i].player.stop)
        {
            pults[i].player.play->setEnabled(true);
            pults[i].player.stop->setEnabled(false);
            pults[i].ticker->stop();
        }
        else if (btn == pults[i].player.back && pults[i].player.step->value())
        {
            pults[i].player.step->setValue(pults[i].player.step->value()-2);
            auto out = synchronize();
            if (out[i]) play(i);
        }
        else if (btn == pults[i].player.next)
        {
            pults[i].player.step->setValue(pults[i].player.step->value()+1);
            auto out = synchronize();
            if (out[i]) play(i);
        }
        else if (slider == pults[i].player.step || timer == pults[i].ticker)
        {
            auto out = synchronize();
            if (out[i]) play(i);
        }

        if      (speed == ui->x1)  pults[i].ticker->setInterval(1000);
        else if (speed == ui->x2)  pults[i].ticker->setInterval(500);
        else if (speed == ui->x4)  pults[i].ticker->setInterval(250);
        else if (speed == ui->x8)  pults[i].ticker->setInterval(125);
        else if (speed == ui->x16) pults[i].ticker->setInterval(63);
        else if (speed == ui->x25) pults[i].ticker->setInterval(40);
    }
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
   auto result = treemanager->findInTree(item,column);
   if (result.size() == 3)
   {
       auto num = result[0] == "КК" ? 0ull :
                  result[0] == "ШН" ? 1ull : 2ull;

       for (auto i = 0 ; i < pults[num].frame_data.size();i++)
       {
           if (pults[num].frame_data[i].name.contains(result[1]) &&
               pults[num].frame_data[i].time.toString().contains(result[2]))
           {
               pults[num].player.step->setValue(i);
               play(num);
               break;
           }
       }
   }
}

frame_info MainWindow::initDefaultFrame()
{
    frame_info def{};
    auto word = codec->fromUnicode("          НЕТ ДАННЫХ           ");
    def.info.data->id_b.line_number = 6;
    def.info.data->button_fires_1_b.pressed_button = 0;
    for (auto i = 0; i < word.size();i++)
    {
        if (i >= 10 && i <=19)
        {
            def.info.data->symbols_b[i].small = 0;
            def.info.data->symbols_b[i].code = word[i];
            def.info.data->symbols_b[i].backcolor = 3;
            def.info.data->symbols_b[i].forecolor = 0;
        }
    }
    return def;
}

QVector<bool> MainWindow::synchronize()
{
    QVector<bool> out{false,false,false};
    if (s.num_mfpu)
    {
        auto step = pults[s.num_mfpu-1].player.step->value();
        auto time = pults[s.num_mfpu-1].frame_data[step].time;
        for (auto i = 0ull ; i < 3;i++)
        {
            //если этот не ведущий
            if (s.num_mfpu != i+1)
            {
                auto pos = std::find_if(pults[i].frame_data.begin(),pults[i].frame_data.end(),[time](frame_info& data){
                        return abs(time.msecsSinceStartOfDay() - data.time.msecsSinceStartOfDay()) <= 600;
                });
                if (pos != pults[i].frame_data.end())
                {
                    pults[i].player.step->setValue(std::distance(pults[i].frame_data.begin(),pos));
                    out[i] = true;
                }
            }
            else
            {
                out[i] = true;
            }
        }
    }
    else
    {
        out[0] = true;
        out[1] = true;
        out[2] = true;
    }
    return out;
}
