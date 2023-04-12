#include "timeset.h"

Timeset::Timeset(QWidget *parent)
    : QWidget{parent}{}
Timeset::Timeset(QString cont,int num,int setnum,QWidget *parent)
    : QWidget{parent}
{
    hbl=new QHBoxLayout();
    l=new QLabel(cont);
    sb=new QSpinBox();
    s=new QSlider();
    sb->setMinimum(1);
    sb->setMaximum(num);
    sb->setValue(setnum);
    s->setMinimum(1);
    s->setMaximum(num);
    s->setValue(setnum);
    s->setOrientation(Qt::Horizontal);
    hbl->addWidget(l);
    hbl->addWidget(sb);
    hbl->addWidget(s);
    this->setLayout(hbl);
    //同步两种时间设置
    //QSpinBox移动 QSlider跟着移动
    void(QSpinBox:: *spSignal )(int) = &QSpinBox::valueChanged;
    connect(sb, spSignal, s, &QSlider::setValue);
    //QSlider滑动  QSpinBox数字跟着改变
    connect(s, &QSlider::valueChanged, sb, &QSpinBox::setValue);
}
