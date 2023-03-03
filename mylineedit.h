#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QObject>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    MyLineEdit(QWidget* parent = nullptr);
public slots:
    void InsertSymbol(const QString& symbol);
signals:
    void currentFieldEnabled(MyLineEdit* ptr);
protected:
    void mousePressEvent(QMouseEvent*) override;
};

#endif // MYLINEEDIT_H
