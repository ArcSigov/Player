#include "label.h"


Diod::Diod(QWidget* parent ) : QLabel(parent)
{
    t = new QTimer(this);
    connect(t,&QTimer::timeout,this,&Diod::ping);
}


void Diod::setStyle(const labelstyle& style,const bool& is_ping) {
    switch (style){
        case labelstyle::def:
            setStyleSheet({});
        break;
        case labelstyle::green:
            setStyleSheet("min-width: 8px; min-height: 8px;max-width:8px; max-height: 8px;border-radius: 5px;  border:1px solid black;background:#00e000");
        break;
        case labelstyle::black:
            setStyleSheet("min-width: 8px; min-height: 8px;max-width:8px; max-height: 8px;border-radius: 5px;  border:1px solid black;background:black");
        break;
    default: break;
    }

    if (is_ping){
        t->start(200);
    } else{
        t->stop();
    }
}

void Diod::ping(){
    if (!step)
    {
        step++;
        setStyleSheet("min-width: 8px; min-height: 8px;max-width:8px; max-height: 8px;border-radius: 5px;  border:1px solid black;background:#00e000");
    }
    else
    {
        step = 0;
        setStyleSheet("min-width: 8px; min-height: 8px;max-width:8px; max-height: 8px;border-radius: 5px;  border:1px solid black;background:black");
    }
}
