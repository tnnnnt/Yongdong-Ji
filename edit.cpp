#include "edit.h"
#include "publicdata.h"
Edit::Edit(QWidget *parent) :
    QDialog(parent)
{
    vbl=new QVBoxLayout();
    hbl0=new QHBoxLayout();
    hbl1=new QHBoxLayout();
    cont=new QTextEdit();
    cont->setPlaceholderText("请在此处输入内容");
    ans=new QTextEdit();
    ans->setPlaceholderText("请在此处输入答复（选填）");
    w_min=new QWidget();
    w_sure=new QWidget();
    l_min=new QLabel();
    l_min->setText("间隔分钟数");
    sb_min=new QSpinBox();
    sb_min->setMinimum(1);
    sb_min->setMaximum(2147483647);
    si0=new QSpacerItem(40,20);
    si1=new QSpacerItem(40,20);
    si2=new QSpacerItem(40,20);
    si3=new QSpacerItem(40,20);
    btn_sure=new QPushButton();
    btn_sure->setText("确认");
    btn_ret=new QPushButton();
    btn_ret->setText("取消");
    this->setLayout(vbl);
    vbl->addWidget(cont);
    vbl->addWidget(ans);
    vbl->addWidget(w_min);
    vbl->addWidget(w_sure);
    w_min->setLayout(hbl0);
    hbl0->addSpacerItem(si0);
    hbl0->addWidget(l_min);
    hbl0->addWidget(sb_min);
    hbl0->addSpacerItem(si1);
    w_sure->setLayout(hbl1);
    hbl1->addSpacerItem(si2);
    hbl1->addWidget(btn_sure);
    hbl1->addWidget(btn_ret);
    hbl1->addSpacerItem(si3);
    this->setWindowIcon(QIcon(PublicData::icon_path));
    //取消事件
    connect(this->btn_ret,&QPushButton::clicked,[=](){
        this->close();
    });
}

Edit::~Edit(){}
