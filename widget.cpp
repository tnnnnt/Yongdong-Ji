#include "widget.h"
#include "ui_widget.h"
#include "publicdata.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(QPixmap(PublicData::icon_path)));
    this->setWindowTitle(PublicData::title);
    QFile in(PublicData::file);
    in.open(QIODevice::ReadOnly);
    PublicData::data=in.readAll();
    in.close();
    //解析
    PublicData::qjd=QJsonDocument::fromJson(PublicData::data);
    PublicData::obj=PublicData::qjd.object();
    QJsonObject::Iterator iter;
    for(iter=PublicData::obj.begin();iter!=PublicData::obj.end();iter++){
        QJsonValue sub=iter.value();
        QJsonObject subObj=sub.toObject();
        QString content=iter.key();
        item::cont_item[content]=new item(content);
        item::cont_item[content]->answer=subObj["answer"].toString();
        item::cont_item[content]->minute=subObj["minute"].toInt();
        ui->vvv->addWidget(item::cont_item[content]);
    }
    //添加事件
    connect(ui->btn_add,&QPushButton::clicked,[=](){
        additem();
    });

    //***托盘***
    tray= new QSystemTrayIcon(this);//初始化托盘对象tray
    tray->setIcon(QIcon(PublicData::icon_path));//设定托盘图标，引号内是自定义的png图片路径
    tray->setToolTip(PublicData::title); //提示文字
    tray->show();//让托盘图标显示在系统托盘上
    tray->showMessage(PublicData::title,PublicData::title+"已启动",QIcon(PublicData::icon_path),3000); //最后一个参数为提示时长，默认10000，即10s
    //创建菜单项动作
    newAction = new QAction("新建提醒", this);
    connect(newAction, SIGNAL(triggered()), this, SLOT(additem())); //新建提醒
    quitAction = new QAction("退出", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit())); //关闭应用
    //创建托盘菜单
    trayMenu = new QMenu(this);
    trayMenu->addAction(newAction);
    tray->setContextMenu(trayMenu);
    trayMenu->addAction(quitAction);
    tray->setContextMenu(trayMenu);
    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    QApplication::setQuitOnLastWindowClosed(false);//窗口关闭，程序不退出
}
Widget::~Widget(){delete ui;}

void Widget::iconActivated(QSystemTrayIcon::ActivationReason ireason)
{
    switch (ireason)
    {
    case QSystemTrayIcon::Trigger:
        this->showNormal();
        break;
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        break;
    }
}
void Widget::additem(){
    e=new Edit();
    e->setWindowTitle("新建提醒");
    //确认事件
    connect(e->btn_sure,&QPushButton::clicked,[=](){
        QString new_cont=e->cont->toPlainText();
        if(new_cont==""){
            QMessageBox::critical(e,"错误！","请输入内容！");
        }else if(item::cont_item.find(new_cont)!=item::cont_item.end()){
            QMessageBox::critical(e,"错误！","该内容已存在！");
        }else{
            item::cont_item[new_cont]=new item(new_cont);
            item::cont_item[new_cont]->answer=e->ans->toPlainText();
            item::cont_item[new_cont]->minute=e->sb_min->value();
            ui->vvv->addWidget(item::cont_item[new_cont]);
            QJsonObject obj2;
            obj2["answer"]=item::cont_item[new_cont]->answer;
            obj2["minute"]=item::cont_item[new_cont]->minute;
            PublicData::obj[new_cont]=obj2;
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
}
