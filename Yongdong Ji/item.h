#ifndef ITEM_H
#define ITEM_H

#include <Edit.h>
#include <Work.h>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QThread>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>
#include <Work.h>
#include <QTextBrowser>

class item : public QWidget
{
    Q_OBJECT
public:
    QHBoxLayout *qhb;
    QPushButton *ed;
    QPushButton *run;
    QPushButton *del;
    QString run_icon;
    QString content;
    QString answer;
    int minute;
    static QMap<QString,item*>cont_item;
    static QString start_icon;
    static QString stop_icon;
    Edit *e;
    QTimer *timer;
    QThread *thread;
    Work *work;
    int ttt;
    explicit item(QWidget *parent = nullptr);
    item(QString content,QWidget *parent = nullptr);
public slots:
    void showProcess();
};

#endif // ITEM_H
