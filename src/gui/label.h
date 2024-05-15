#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QObject>
#include <QTimer>
enum class dioistyle
{
    def,
    black,
    green,
    pinggreen
};

class Diod : public QLabel
{
    Q_OBJECT
public:
    Diod(QWidget* parent = nullptr);
    void setStyle(const dioistyle& style, const bool& ping = false);

public   slots:
    void ping();
private:
    size_t step{0};
    QTimer *t;
};
#endif // LABEL_H
