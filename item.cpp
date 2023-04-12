#include "item.h"
#include "publicdata.h"

item::item(QWidget *parent)
    : QWidget{parent}{}
item::item(QString cont,QWidget *parent)
    : QWidget{parent}
{
    ttt=60000;
    run_icon=":/images/start.png";
    //定义线程的东西
    timer = new QTimer();
    thread = new QThread();
    work = new Work();
    work->moveToThread(thread);
    connect(timer,SIGNAL(timeout()),work,SLOT(dowork()));
    connect(work,SIGNAL(sigProcess()),this,SLOT(showProcess()));
    connect(work,SIGNAL(sigProcess()),timer,SLOT(stop()));

    content=cont;
    qhb=new QHBoxLayout();
    ed=new QPushButton();
    ed->setMinimumSize(116,64);
    ed->setMaximumSize(1800,64);
    ed->setFont(QFont("Microsoft YaHei UI",35));
    ed->setStyleSheet("text-align:left");
    ed->setText(content);

    run=new QPushButton();
    run->setMinimumSize(64,64);
    run->setMaximumSize(64,64);
    run->setCursor(QCursor(Qt::PointingHandCursor));
    run->setStyleSheet("background-color:rgba(255,255,255,0)");
    run->setIcon(QIcon(run_icon));
    run->setIconSize(QSize(64,64));
    run->setText("");

    del=new QPushButton();
    del->setMinimumSize(64,64);
    del->setMaximumSize(64,64);
    del->setCursor(QCursor(Qt::PointingHandCursor));
    del->setStyleSheet("background-color:rgba(255,255,255,0)");
    del->setIcon(QIcon(":/images/delete.png"));
    del->setIconSize(QSize(64,64));
    del->setText("");

    qhb->setContentsMargins(0,0,0,0);
    qhb->setSpacing(0);
    qhb->addWidget(ed);
    qhb->addWidget(run);
    qhb->addWidget(del);
    this->setLayout(qhb);
    this->setMinimumSize(180,64);
    this->setMaximumSize(1864,64);
    //启动事件
    connect(run,&QPushButton::clicked,[=](){
        if(run_icon==start_icon){
            run_icon=stop_icon;
            //启动线程
            thread->start();
            timer->start(ttt*minute);
        }else{
            run_icon=start_icon;
            //暂停线程
            timer->stop();
            thread->quit();
            thread->wait();
        }
        run->setIcon(QIcon(run_icon));
    });
    //编辑事件
    connect(ed,&QPushButton::clicked,[=](){
        e=new Edit();
        e->setWindowTitle("编辑提醒");
        e->cont->setText(content);
        e->ans->setText(answer);
        e->sb_min->setValue(minute);
        //确认事件
        connect(e->btn_sure,&QPushButton::clicked,[=](){
            QString new_cont=e->cont->toPlainText();
            if(new_cont==""){
                QMessageBox::critical(e,"错误！","请输入内容！");
            }else if(new_cont==content){
                answer=e->ans->toPlainText();
                minute=e->sb_min->value();
                QJsonObject obj2;
                obj2["answer"]=answer;
                obj2["minute"]=minute;
                PublicData::obj[content]=obj2;
                PublicData::qjd.setObject(PublicData::obj);
                PublicData::data=PublicData::qjd.toJson();
                QFile out(PublicData::file);
                out.open(QIODevice::WriteOnly);
                out.write(PublicData::data);
                out.close();
                e->close();
            }else if(cont_item.find(new_cont)!=cont_item.end()){
                QMessageBox::critical(e,"错误！","该内容已存在！");
            }else{
                cont_item[new_cont]=cont_item[content];
                cont_item.remove(content);
                PublicData::obj.remove(content);

                content=new_cont;
                answer=e->ans->toPlainText();
                minute=e->sb_min->value();

                ed->setText(content);

                QJsonObject obj2;
                obj2["answer"]=answer;
                obj2["minute"]=minute;
                PublicData::obj[content]=obj2;
                PublicData::qjd.setObject(PublicData::obj);
                PublicData::data=PublicData::qjd.toJson();
                QFile out(PublicData::file);
                out.open(QIODevice::WriteOnly);
                out.write(PublicData::data);
                out.close();
                e->close();
            }
        });
        e->exec();
    });
    //删除事件
    connect(del,&QPushButton::clicked,[=](){
        //更改json
        PublicData::obj.remove(content);
        PublicData::qjd.setObject(PublicData::obj);
        PublicData::data=PublicData::qjd.toJson();
        QFile out(PublicData::file);
        out.open(QIODevice::WriteOnly);
        out.write(PublicData::data);
        out.close();
        //删除该组件
        cont_item.remove(content);
        delete this;
    });
}
QMap<QString,item*>item::cont_item;
QString item::start_icon=":/images/start.png";
QString item::stop_icon=":/images/stop.png";
void item::showProcess(){
    QDialog *w=new QDialog();
    QVBoxLayout *vbl=new QVBoxLayout();
    QTextBrowser *tb=new QTextBrowser();
    QPushButton *btn=new QPushButton("好！");
    tb->setPlainText(content);
    vbl->addWidget(tb);
    vbl->addWidget(btn);
    w->setLayout(vbl);
    w->setWindowIcon(QIcon(PublicData::icon_path));
    if(answer==""){
        //无answer（【继续/暂停】）
        w->setWindowTitle("Tip");
        connect(btn,&QPushButton::clicked,[=](){
            timer->start(ttt*minute);
            w->close();
        });
    }else{
        //有answer（【继续】->【继续/暂停】）
        w->setWindowTitle("问题");
        connect(btn,&QPushButton::clicked,[=](){
            if(w->windowTitle()=="问题"){
                w->setWindowTitle("答案");
                tb->setPlainText(answer);
            }else{
                timer->start(ttt*minute);
                w->close();
            }
        });
    }
    w->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
    w->exec();
}
