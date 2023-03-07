#ifndef WORK_H
#define WORK_H
#include<QObject>
#include<QApplication>
class Work : public QObject{
    Q_OBJECT
public:
    explicit Work(QObject *parent = nullptr);
signals:
    void sigProcess();
public slots:
    void dowork();
};

#endif // WORK_H
