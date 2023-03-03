#include "insertingsettings.h"
#include "ui_insertingsettings.h"
#include <QDebug>
#include <QCloseEvent>

InsertingSettings::InsertingSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertingSettings)
{
    ui->setupUi(this);
    connect(ui->ok,&QPushButton::clicked,this,&InsertingSettings::sendResult);
    connect(ui->cancel,&QPushButton::clicked,this,&InsertingSettings::close);

    //собираем в контейнер виджеты для работы со типом строки
    string_widgets.push_back(ui->abbr);
    string_widgets.push_back(ui->param);
    string_widgets.push_back(ui->metric);
    string_widgets.push_back(ui->abbr_2);
    string_widgets.push_back(ui->param_2);
    string_widgets.push_back(ui->metric_2);
    string_widgets.push_back(ui->abbr_colour);
    string_widgets.push_back(ui->value_colour);
    string_widgets.push_back(ui->metric_colour);
    string_widgets.push_back(ui->abbr_2_colour);
    string_widgets.push_back(ui->value_2_colour);
    string_widgets.push_back(ui->metric_2_colour);

    //cобираем в контейнер виджеты для работы с переключателем
    switcher_widgets.push_back(ui->switcher_name);
    switcher_widgets.push_back(ui->switcher);

    button_widgets.push_back(ui->name);

    header_widgets.push_back(ui->header_name);
    header_widgets.push_back(ui->param_header_name);

    //обрабатываем коннекты
    //если нажали кнопку
    for (const auto& it : qAsConst(button_widgets))
        connect(ui->isbutton,&QRadioButton::toggled,it,&QWidget::show);
    for (const auto& it : qAsConst(string_widgets))
        connect(ui->isbutton,&QRadioButton::toggled,it,&QWidget::hide);
    for (const auto& it : qAsConst(switcher_widgets))
        connect(ui->isbutton,&QRadioButton::toggled,it,&QWidget::hide);
    for (const auto& it : qAsConst(header_widgets))
        connect(ui->isbutton,&QRadioButton::toggled,it,&QWidget::hide);

    //если выбрали строку
    for (const auto& it : qAsConst(string_widgets))
        connect(ui->isstring,&QRadioButton::toggled,it,&QWidget::show);
    for (const auto& it : qAsConst(switcher_widgets))
        connect(ui->isstring,&QRadioButton::toggled,it,&QWidget::hide);
    for (const auto& it : qAsConst(button_widgets))
        connect(ui->isstring,&QRadioButton::toggled,it,&QWidget::hide);
    for (const auto& it : qAsConst(header_widgets))
        connect(ui->isstring,&QRadioButton::toggled,it,&QWidget::hide);

     //если выбрали переключатель
    for (const auto& it : qAsConst(button_widgets))
        connect(ui->isswitcher,&QRadioButton::toggled,it,&QWidget::hide);
    for (const auto& it : qAsConst(string_widgets))
        connect(ui->isswitcher,&QRadioButton::toggled,it,&QWidget::hide);
    for (const auto& it : qAsConst(switcher_widgets))
        connect(ui->isswitcher,&QRadioButton::toggled,it,&QWidget::show);
    for (const auto& it : qAsConst(header_widgets))
        connect(ui->isswitcher,&QRadioButton::toggled,it,&QWidget::hide);


    //подключаем к обработчику строки
    for (const auto& it : qAsConst(button_widgets))
    {
        auto line = dynamic_cast<MyLineEdit*>(it);
        if (line)
            connect(line,&MyLineEdit::currentFieldEnabled,this,&InsertingSettings::LineEditing);
    }


    //подключаем к обработчику строки
    for (const auto& it : qAsConst(string_widgets))
    {
        auto line = dynamic_cast<MyLineEdit*>(it);
        if (line)
            connect(line,&MyLineEdit::currentFieldEnabled,this,&InsertingSettings::LineEditing);
    }

    //подключаем к обработчику строки
    for (const auto& it : qAsConst(switcher_widgets))
    {
        auto line = dynamic_cast<MyLineEdit*>(it);
        if (line)
            connect(line,&MyLineEdit::currentFieldEnabled,this,&InsertingSettings::LineEditing);
    }


    //подключаем к обработчику строки
    for (const auto& it : qAsConst(header_widgets))
    {
        auto line = dynamic_cast<MyLineEdit*>(it);
        if (line)
            connect(line,&MyLineEdit::currentFieldEnabled,this,&InsertingSettings::LineEditing);
    }


    params.resize(11);

    params[0].pos = KVS1L_1;
    params[1].pos = KVS2L_1;
    params[2].pos = KVS3L_1;
    params[3].pos = KVS4L_1;
    params[4].pos = KVS5L_1;
    params[5].pos = KVS1R_1;
    params[6].pos = KVS2R_1;
    params[7].pos = KVS3R_1;
    params[8].pos = KVS4R_1;
    params[9].pos = KVS5R_1;
    params[10].pos = HEADER_1;

    params[0].type= Type::Button;
    params[1].type= Type::Button;
    params[2].type= Type::Button;
    params[3].type= Type::Button;
    params[4].type= Type::Button;
    params[5].type= Type::Button;
    params[6].type= Type::Button;
    params[7].type= Type::Button;
    params[8].type= Type::Button;
    params[9].type= Type::Button;
    params[10].type = Type::Header;


}

InsertingSettings::~InsertingSettings()
{
    delete ui;
}

void InsertingSettings::LineEditing(MyLineEdit* line)
{
    static MyLineEdit* prev_line = nullptr;
    if (prev_line != line)
    {
        for (const auto& it : ui->specialsymbols->children())
        {
            if (prev_line)
                disconnect(static_cast<MyButton*>(it),&MyButton::oneClicked,prev_line,&MyLineEdit::InsertSymbol);
            connect(static_cast<MyButton*>(it),&MyButton::oneClicked,line,&MyLineEdit::InsertSymbol);
        }
        prev_line = line;
    }
}

void InsertingSettings::runEditing(const QString& name)
{
    show();
    setWindowTitle("Конструктор " + name);
    ui->types->show();

    if      (name == "КВС1Л")     current = &params[0];
    else if (name == "КВС2Л")     current = &params[1];
    else if (name == "КВС3Л")     current = &params[2];
    else if (name == "КВС4Л")     current = &params[3];
    else if (name == "КВС5Л")     current = &params[4];
    else if (name == "КВС1Р")     current = &params[5];
    else if (name == "КВС2Р")     current = &params[6];
    else if (name == "КВС3Р")     current = &params[7];
    else if (name == "КВС4Р")     current = &params[8];
    else if (name == "КВС5Р")     current = &params[9];
    else if (name == "НАЗВ\nСТР")
    {
        current = &params[10];
        current->type = Type::Header;
        for (const auto& widget: qAsConst(header_widgets))   widget->show();
        for (const auto& widget: qAsConst(string_widgets))   widget->hide();
        for (const auto& widget: qAsConst(switcher_widgets)) widget->hide();
        for (const auto& widget: qAsConst(button_widgets))   widget->hide();

        ui->types->hide();
    }
    else return;


    for (auto i = 0 ; i <= static_cast<int>(StringWidgetsPos::metric_2_colour);  i++)
    {
        if (i < 1)  static_cast<QLineEdit*>(button_widgets.at(i))->setText(QString());
        if (i < 2)  static_cast<QLineEdit*>(switcher_widgets.at(i))->setText(QString());
        if (i <= 5) static_cast<QLineEdit*>(string_widgets.at(i))->setText(QString());
        else        static_cast<QComboBox*>(string_widgets.at(i))->setCurrentIndex(0);
    }
    set_params();
}

void InsertingSettings::sendResult()
{

    get_params();
    if (!current->text.text.isEmpty())
        emit Text(current->type,current->pos,current->text);
    close();
}

void InsertingSettings::get_params()
{
    current->text.text.clear();
    current->text.colour.clear();

    if (current->type == Type::Header)
    {
        for (auto i = 0 ; i < header_widgets.size();  i++)
            current->text.text.push_back(static_cast<QLineEdit*>(header_widgets.at(i))->text());
    }
    //обработчик для строки
    else if (ui->isstring->isChecked())
    {
        current->type = Type::String;
        for (auto i = 0 ; i <= static_cast<int>(StringWidgetsPos::metric_2);  i++)
           current->text.text.push_back(static_cast<QLineEdit*>(string_widgets.at(i))->text());

        for (auto i = static_cast<int>(StringWidgetsPos::abbr_colour) ; i <= static_cast<int>(StringWidgetsPos::metric_2_colour);i++)
        {
            switch(static_cast<QComboBox*>(string_widgets.at(i))->currentIndex())
            {
                case 0: current->text.colour.push_back(Colour::blue);  break;
                case 1: current->text.colour.push_back(Colour::white); break;
                case 2: current->text.colour.push_back(Colour::green); break;
                default:break;
            }
        }
    }
    //обработчик для кнопки
    else if (ui->isbutton->isChecked())
    {
        current->type = Type::Button;
        current->text.text.push_back(ui->name->text());
    }
    //обработчик для переключателя
    else if (ui->isswitcher->isChecked())
    {
        current->type = Type::Switcher;
        for (auto i = 0 ; i < switcher_widgets.size();  i++)
           current->text.text.push_back(static_cast<QLineEdit*>(switcher_widgets.at(i))->text());
    }
}

void InsertingSettings::set_params()
{
    switch (current->type)
    {
        //обработчик для строки
        case Type::String:
        {
            ui->isstring->setChecked(true);
            emit ui->isstring->toggled(true);

            //выставляем настроенные значения строк
            for (auto i = 0; i < current->text.text.size(); i++)
                static_cast<QLineEdit*>(string_widgets.at(i))->setText(current->text.text.at(i));

            //выставляем настроенные цвета кнопок
            for (auto i = 0; i < current->text.colour.size(); i++)
            {
                switch(current->text.colour.at(i))
                {
                    case Colour::blue:  static_cast<QComboBox*>(string_widgets.at(i+6))->setCurrentIndex(0); break;
                    case Colour::white: static_cast<QComboBox*>(string_widgets.at(i+6))->setCurrentIndex(1); break;
                    case Colour::green: static_cast<QComboBox*>(string_widgets.at(i+6))->setCurrentIndex(2); break;
                    default: break;
                }
            }
            break;
        }
        //обработчик для кнопки
        case Type::Button:
        {
            ui->isbutton->setChecked(true);
            emit ui->isbutton->toggled(true);
            if(!current->text.text.isEmpty())
                ui->name->setText(current->text.text.at(0));
            break;
        }
        //обработчик для переключателя
        case Type::Switcher:
        {
            ui->isswitcher->setChecked(true);
            emit ui->isswitcher->toggled(true);
            QString switch_variables;
            for (auto i = 0 ; i < current->text.text.size();i++)
            {
                if (!i)  ui->switcher_name->setText(current->text.text.at(i));
                else     switch_variables+=current->text.text.at(i);
            }
            ui->switcher->setText(switch_variables);
            break;
        }
        case Type::Header:
        {
            for (auto i = 0 ; i < current->text.text.size();i++)
                static_cast<QLineEdit*>(header_widgets.at(i))->setText(current->text.text[i]);
            break;
        }
        default:break;
    }
}
