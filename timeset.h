#ifndef TIMESET_H
#define TIMESET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

class Timeset : public QWidget
{
    Q_OBJECT
public:
    QHBoxLayout *hbl;
    QLabel *l;
    QSpinBox *sb;
    QSlider *s;
    explicit Timeset(QWidget *parent = nullptr);
    Timeset(QString cont,int num,int setnum,QWidget *parent = nullptr);

signals:

};

#endif // TIMESET_H
