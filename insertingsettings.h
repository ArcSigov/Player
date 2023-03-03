#ifndef INSERTINGSETTINGS_H
#define INSERTINGSETTINGS_H

#include <QDialog>
#include "utils.h"
#include <mylineedit.h>

namespace Ui {
class InsertingSettings;
}

enum class StringWidgetsPos
{
    abbr,
    param,
    metric,
    abbr_2,
    param_2,
    metric_2,
    abbr_colour,
    value_colour,
    metric_colour,
    abbr_2_colour,
    value_2_colour,
    metric_2_colour
};

enum class SwitcherWidgetsPos
{
    switcher_name,
    switcher
};

class InsertingSettings : public QDialog
{
    Q_OBJECT
        struct params_t
        {
            Type type{Type::Button};
            TextPosition pos;
            text_t       text;
        };
        public:
                 explicit InsertingSettings(QWidget *parent = nullptr);
    ~InsertingSettings();
             signals:
                void TextChanged(const Type&, const TextPosition&, const Colour&,const Colour&,const QString& text, const QString& param = QString());
                void Text(const Type& type,const TextPosition&,const text_t&);
public slots:
                void runEditing(const QString&);
                void LineEditing(MyLineEdit* line);
private:
    void sendResult();
    void set_params();
    void get_params();
    Ui::InsertingSettings *ui;
    QVector<params_t>   params;
    params_t*           current;
    QVector<QWidget*> string_widgets;
    QVector<QWidget*> switcher_widgets;
    QVector<QWidget*> button_widgets;
    QVector<QWidget*> header_widgets;
};

#endif // INSERTINGSETTINGS_H
