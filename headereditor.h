#ifndef HEADEREDITOR_H
#define HEADEREDITOR_H

#include <QWidget>
#include "utils.h"

namespace Ui {
class headereditor;
}

class headereditor : public QWidget
{
    Q_OBJECT

        public:
                 explicit headereditor(QWidget *parent = nullptr);
    ~headereditor();
        public slots:
        void editname(const QString&);
        signals:
            void TextChanged(const Type&, const TextPosition&, const Colour&,const Colour&,const QString& text, const QString& param = QString());
private:
    Ui::headereditor *ui;
};

#endif // HEADEREDITOR_H
