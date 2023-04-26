#include "edit.h"
#include "publicdata.h"
Edit::Edit(QWidget *parent) :
    QDialog(parent)
{
    vbl=new QVBoxLayout();
    hbl=new QHBoxLayout();
    cont=new QTextEdit();
    ans=new QTextEdit();
    cont->setFont(PublicData::qf);
    ans->setFont(PublicData::qf);
    cont->setPlaceholderText("请在此处输入内容");
    ans->setPlaceholderText("请在此处输入答复（选填）");
    w_min=new Timeset("间隔分钟数",PublicData::max_min,1);
    w_sure=new QWidget();
    btn_sure=new QPushButton();
    btn_sure->setText("确认");
    btn_ret=new QPushButton();
    btn_ret->setText("取消");
    this->setLayout(vbl);
    vbl->addWidget(cont);
    vbl->addWidget(ans);
    vbl->addWidget(w_min);
    vbl->addWidget(w_sure);
    w_sure->setLayout(hbl);
    hbl->addWidget(btn_sure);
    hbl->addWidget(btn_ret);
    this->setWindowIcon(QIcon(PublicData::icon_path));
    //取消事件
    connect(this->btn_ret,&QPushButton::clicked,[=](){
        this->close();
    });
}

Edit::~Edit(){}
