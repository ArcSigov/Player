#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QDebug>
#include <QStyle>
#include <QDirIterator>
#include <QFileDialog>
#include <QDateTime>
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    pults[0].ticker = new QTimer(this);
    pults[1].ticker = new QTimer(this);
    pults[2].ticker = new QTimer(this);
    pults[0].ticker->setInterval(1000);
    pults[1].ticker->setInterval(1000);
    pults[2].ticker->setInterval(1000);

    connect(pults[0].ticker,&QTimer::timeout,this,&MainWindow::updatePlayer);
    connect(pults[1].ticker,&QTimer::timeout,this,&MainWindow::updatePlayer);
    connect(pults[2].ticker,&QTimer::timeout,this,&MainWindow::updatePlayer);
    connect(ui->step_mfpu1,&QAbstractSlider::valueChanged,this,&MainWindow::updatePlayer);
    connect(ui->step_mfpu2,&QAbstractSlider::valueChanged,this,&MainWindow::updatePlayer);
    connect(ui->step_mfpu3,&QAbstractSlider::valueChanged,this,&MainWindow::updatePlayer);
    connect(ui->mfpu1_play,&QPushButton::clicked,this, &MainWindow::updatePlayer);
    connect(ui->mfpu2_play,&QPushButton::clicked,this, &MainWindow::updatePlayer);
    connect(ui->mfpu3_play,&QPushButton::clicked,this, &MainWindow::updatePlayer);
    connect(ui->mfpu1_pause,&QPushButton::clicked,this, &MainWindow::updatePlayer);
    connect(ui->mfpu2_pause,&QPushButton::clicked,this, &MainWindow::updatePlayer);
    connect(ui->mfpu3_pause,&QPushButton::clicked,this, &MainWindow::updatePlayer);



    ui->mfpu1_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->mfpu1_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->next->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->back->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));

    ui->mfpu2_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->mfpu2_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->next_2->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->back_2->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));

    ui->mfpu3_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->mfpu3_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->next_3->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->back_3->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play(const size_t& pos)
{
    auto mfpu = static_cast<mfpu_out_b_t*>(static_cast<void*>(d[pos].begin()+pults[pos].step*sizeof(mfpu_out_b_t)));
    pults[pos].display->draw_data(mfpu);
    for (auto j = 0 ; j < 12; j++)
    {
       pults[pos].diods[0]      ->    setStyle(mfpu->data[j].button_fires_1_b.plan ?         dioistyle::green : dioistyle::black );
       pults[pos].diods[1]      ->    setStyle(mfpu->data[j].button_fires_1_b.active_route ? dioistyle::green : dioistyle::black );
       pults[pos].diods[2]      ->    setStyle(mfpu->data[j].button_fires_1_b.comb ?         dioistyle::green : dioistyle::black );
       pults[pos].diods[3]      ->    setStyle(mfpu->data[j].button_fires_2_b.rts ?          dioistyle::green : dioistyle::black );
       pults[pos].diods[4]      ->    setStyle(mfpu->data[j].button_fires_1_b.u19 ?          dioistyle::green : dioistyle::black );
       pults[pos].diods[5]      ->    setStyle(mfpu->data[j].button_fires_1_b.basu ?         dioistyle::green : dioistyle::black );
       pults[pos].diods[6]      ->    setStyle(mfpu->data[j].button_fires_1_b.flight_data ?  dioistyle::green : dioistyle::black );
       pults[pos].diods[7]      ->    setStyle(mfpu->data[j].button_fires_1_b.suo ?          dioistyle::green : dioistyle::black );
       pults[pos].diods[8]      ->    setStyle(mfpu->data[j].button_fires_1_b.nav ?          dioistyle::green : dioistyle::black );
       pults[pos].diods[9]      ->    setStyle(mfpu->data[j].button_fires_2_b.selected_time ?dioistyle::green : dioistyle::black );
       pults[pos].diods[10]     ->    setStyle(mfpu->data[j].button_fires_2_b.maneuver ?     dioistyle::green : dioistyle::black );
       pults[pos].diods[11]     ->    setStyle(mfpu->data[j].button_fires_2_b.isp ?          dioistyle::green : dioistyle::black, mfpu->data[j].button_fires_2_b.isp);
       pults[pos].diods[12]     ->    setStyle(mfpu->data[j].button_fires_2_b.arv_arp ?      dioistyle::green : dioistyle::black );
       pults[pos].diods[13]     ->    setStyle(mfpu->data[j].button_fires_2_b.corr ?         dioistyle::green : dioistyle::black );
       pults[pos].diods[14]     ->    setStyle(mfpu->data[j].button_fires_2_b.bks ?          dioistyle::green : dioistyle::black );
       pults[pos].diods[15]     ->    setStyle(mfpu->data[j].button_fires_2_b.mfpu_control ? dioistyle::green : dioistyle::black );
       pults[pos].diods[16]     ->    setStyle(mfpu->data[j].button_fires_2_b.iipa ?         dioistyle::green : dioistyle::black );
       pults[pos].diods[17]     ->    setStyle(mfpu->data[j].button_fires_2_b.digits ?       dioistyle::green : dioistyle::black );
       pults[pos].diods[18]     ->    setStyle(mfpu->data[j].button_fires_2_b.eng ?          dioistyle::green : dioistyle::black );

        for (const auto& b:qAsConst(pults[pos].btns))
            b->setStyle(btnstyle::white_text_black_background);

        if (mfpu->data[j].button_fires_1_b.pressed_button)
        {
            auto btn = pults[pos].btns.find(mfpu->data[j].button_fires_1_b.pressed_button);
            if (btn != pults[pos].btns.end())
                btn.value()->setStyle(btnstyle::clicked);
        }
    }

    switch (pos)
    {
        case 0:
            ui->progress->setText(QDateTime::fromMSecsSinceEpoch(mfpu->time).time().toString()+pults[pos].summary_time); break;
            ui->step_mfpu1->setValue(pults[pos].step);
            break;
        case 1:
            ui->progress_2->setText(QDateTime::fromMSecsSinceEpoch(mfpu->time).time().toString()+pults[pos].summary_time); break;
            ui->step_mfpu2->setValue(pults[pos].step);
            break;
        case 2:
            ui->progress_3->setText(QDateTime::fromMSecsSinceEpoch(mfpu->time).time().toString()+pults[pos].summary_time); break;
            ui->step_mfpu3->setValue(pults[pos].step);
            break;
        default: break;
    }
    pults[pos].step++;
}

void MainWindow::setbytes(const QByteArray& _d)
{
    size_t num = _d[0];
    d[num-1] = _d;
    d[num-1].remove(0,8);

    auto front = static_cast<mfpu_out_b_t*>(static_cast<void*>(d[num-1].begin()));
    auto back = static_cast<mfpu_out_b_t*>(static_cast<void*>(d[num-1].end()-sizeof(mfpu_out_b_t)));
    pults[num-1].summary_time = "/"+QDateTime::fromMSecsSinceEpoch(back->time).time().toString();
    auto timef = QDateTime::fromMSecsSinceEpoch(front->time).time().toString();
    switch(num)
    {
        case 1:
            ui->step_mfpu1->setTickInterval(100);
            ui->step_mfpu1->setMaximum(d[num-1].size()/sizeof(mfpu_out_b_t));
            ui->progress->setText(timef+ pults[num-1].summary_time);
            break;
        case 2:
            ui->step_mfpu2->setTickInterval(100);
            ui->step_mfpu2->setMaximum(d[num-1].size()/sizeof(mfpu_out_b_t));
            ui->progress_2->setText(timef+ pults[num-1].summary_time);
            break;
        case 3:
            ui->step_mfpu3->setTickInterval(100);
            ui->step_mfpu3->setMaximum(d[num-1].size()/sizeof(mfpu_out_b_t));
            ui->progress_3->setText(timef+ pults[num-1].summary_time);
            break;
        default:break;
    }
}

void MainWindow::readfonts(const QByteArray& fnt)
{
    for (const auto& pult:qAsConst(pults))
        pult.display->readFonts(fnt);
}

void MainWindow::on_open_sbi_triggered()
{
    auto path = QFileDialog::getExistingDirectory(this,"",QDir::currentPath());
    QDirIterator files (path, QStringList() << "*.bin" << "*.txt", QDir::Files);
    while (files.hasNext())
       emit FileChanged(files.next());
}

void MainWindow::updatePlayer()
{
    auto btn = qobject_cast<QPushButton*>(QObject::sender());
    auto timer = qobject_cast<QTimer*>(QObject::sender());
    auto slider = qobject_cast<QSlider*>(QObject::sender());

    if      (btn    == ui->mfpu1_play)    pults[0].ticker->start();
    else if (btn    == ui->mfpu2_play)    pults[1].ticker->start();
    else if (btn    == ui->mfpu3_play)    pults[2].ticker->start();
    else if (btn    == ui->mfpu1_pause)   pults[0].ticker->stop();
    else if (btn    == ui->mfpu2_pause)   pults[1].ticker->stop();
    else if (btn    == ui->mfpu3_pause)   pults[2].ticker->stop();
    else if (timer  == pults[0].ticker)   play(0);
    else if (timer  == pults[1].ticker)   play(1);
    else if (timer  == pults[2].ticker)   play(2);
    else if (slider == ui->step_mfpu1)    pults[0].step = ui->step_mfpu1->value();
    else if (slider == ui->step_mfpu2)    pults[1].step = ui->step_mfpu2->value();
    else if (slider == ui->step_mfpu3)    pults[2].step = ui->step_mfpu3->value();
}