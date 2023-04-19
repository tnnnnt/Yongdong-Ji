#include"work.h"

Work::Work(QObject *parent):QObject{parent}{}
void Work::dowork(){
    QApplication::beep();//提示音
    emit sigProcess();
}
