#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

struct settings{
    bool   treetype;        // 0-развернуто, 1-вложенно
    size_t num_mfpu;        // 0-нет, 1-КК, 2-ШН, 3-ШО
};

class Settings : public QWidget
{
    Q_OBJECT
    settings s;
public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
public slots:
    void EnableNum(const size_t& num);
signals:
    void settingsChecked(const settings&);
private:
    Ui::Settings *ui;
    void makeInfo();
};

#endif // SETTINGS_H
