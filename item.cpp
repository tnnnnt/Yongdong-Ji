#include "item.h"
#include "publicdata.h"

item::item(QWidget *parent)
    : QWidget{parent}{}
item::item(QString cont,QWidget *parent)
    : QWidget{parent}
{
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
    //启动及暂停事件
    connect(run,&QPushButton::clicked,[=](){
        if(run_icon==start_icon){
            run_icon=stop_icon;
            //启动线程
            thread->start();
            timer->start(ttt*minute);
        }else{
            run_icon=start_icon;
            //停止线程
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
        e->w_min->s->setValue(minute);
        e->w_min->sb->setValue(minute);
        //确认事件
        connect(e->btn_sure,&QPushButton::clicked,[=](){
            QString new_cont=e->cont->toPlainText();
            if(new_cont==""){
                QMessageBox::critical(e,"错误！","请输入内容！");
            }else if(new_cont==content){
                answer=e->ans->toPlainText();
                minute=e->w_min->s->value();
                PublicData::newOrEditItem(content,answer,minute);
                e->close();
            }else if(cont_item.find(new_cont)!=cont_item.end()){
                QMessageBox::critical(e,"错误！","该内容已存在！");
            }else{
                cont_item[new_cont]=cont_item[content];
                cont_item.remove(content);
                PublicData::obj_data.remove(content);
                content=new_cont;
                answer=e->ans->toPlainText();
                minute=e->w_min->s->value();
                ed->setText(content);
                PublicData::newOrEditItem(content,answer,minute);
                e->close();
            }
        });
        e->exec();
    });
    //删除事件
    connect(del,&QPushButton::clicked,[=](){
        if(!PublicData::del_tip||QMessageBox::Yes  ==  QMessageBox::question(this,"删除确认","您真的要删除吗？无法恢复哦~",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)){
            delItem(content);
            delete this;
        }
    });
}
QMap<QString,item*>item::cont_item;
QString item::start_icon=":/images/start.png";
QString item::stop_icon=":/images/stop.png";
int item::ttt=60000;//单位为毫秒，通常为60000，即1分钟，其他值为方便测试
void item::showProcess(){
    Timeset *w_min=new Timeset("间隔分钟数",PublicData::max_min,minute);
    QPushButton *btn_con=new QPushButton("继续");
    QPushButton *btn_stop=new QPushButton("停止");
    QPushButton *btn_del=new QPushButton("删除");
    QHBoxLayout *hbl=new QHBoxLayout();
    QWidget *w_btn=new QWidget();
    QTextBrowser *tb=new QTextBrowser();
    QVBoxLayout *vbl=new QVBoxLayout();
    QDialog *w=new QDialog();

    tb->setFont(PublicData::qf);
    tb->setPlainText(content);
    hbl->addWidget(btn_con);
    hbl->addWidget(btn_stop);
    hbl->addWidget(btn_del);
    w_btn->setLayout(hbl);
    vbl->addWidget(tb);
    vbl->addWidget(w_min);
    vbl->addWidget(w_btn);
    w->setLayout(vbl);
    w->setWindowIcon(QIcon(PublicData::icon_path));
    connect(btn_stop,&QPushButton::clicked,[=](){
        run_icon=start_icon;
        run->setIcon(QIcon(run_icon));
        changeMin(w_min->s->value());
        w->close();
        //停止线程
        thread->quit();
        thread->wait();
    });
    connect(btn_del,&QPushButton::clicked,[=](){
        delItem(content);
        w->close();
        delete this;
    });
    if(answer==""){
        //无answer（【继续/暂停】）
        w->setWindowTitle("Tip");
        connect(btn_con,&QPushButton::clicked,[=](){
            changeMin(w_min->s->value());
            timer->start(ttt*minute);
            w->close();
        });
    }else{
        //有answer（【继续】->【继续/暂停】）
        w->setWindowTitle("问题");
        connect(btn_con,&QPushButton::clicked,[=](){
            if(w->windowTitle()=="问题"){
                w->setWindowTitle("答案");
                tb->setPlainText(answer);
            }else{
                changeMin(w_min->s->value());
                timer->start(ttt*minute);
                w->close();
            }
        });
    }
    w->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
    w->exec();
}
void item::changeMin(int m){
    if(minute!=m){
        minute=m;
        QJsonObject obj_tmp;
        obj_tmp["answer"]=answer;
        obj_tmp["minute"]=minute;
        PublicData::obj_data[content]=obj_tmp;
        PublicData::qjd_data.setObject(PublicData::obj_data);
        PublicData::byte_data=PublicData::qjd_data.toJson();
        PublicData::file_data.open(QIODevice::WriteOnly);
        PublicData::file_data.write(PublicData::byte_data);
        PublicData::file_data.close();
    }
}
void item::delItem(QString s){
    //更改json
    PublicData::obj_data.remove(s);
    PublicData::qjd_data.setObject(PublicData::obj_data);
    PublicData::byte_data=PublicData::qjd_data.toJson();
    PublicData::file_data.open(QIODevice::WriteOnly);
    PublicData::file_data.write(PublicData::byte_data);
    PublicData::file_data.close();
    //删除该组件
    cont_item.remove(s);
}


