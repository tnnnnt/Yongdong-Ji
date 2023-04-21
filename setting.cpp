#include "setting.h"
#include "ui_setting.h"
#include "publicdata.h"
#include <QFile>
#include <item.h>

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    //最大间隔分
    for(QMap<QString,item*>::Iterator it=item::cont_item.begin();it!=item::cont_item.end();it++)
        minmax_min=qMax(minmax_min,it.value()->minute);
    ui->sb_min->setMinimum(minmax_min);
    ui->sb_min->setValue(PublicData::max_min);
    //删除确认
    if(PublicData::del_tip==1)ui->cb_del_tip->setCheckState(Qt::Checked);
    else ui->cb_del_tip->setCheckState(Qt::Unchecked);
    //新建时自动启动
    if(PublicData::new_autorun==1)ui->cb_new_autorun->setCheckState(Qt::Checked);
    else ui->cb_new_autorun->setCheckState(Qt::Unchecked);

    //保存事件
    connect(ui->btn_sure,&QPushButton::clicked,[=](){
        //保存 最大间隔分
        PublicData::max_min=ui->sb_min->value();
        PublicData::obj_setting["max_min"]=PublicData::max_min;
        //保存 删除确认
        if(ui->cb_del_tip->checkState()==Qt::Checked)PublicData::del_tip=1;
        else PublicData::del_tip=0;
        PublicData::obj_setting["del_tip"]=PublicData::del_tip;
        //保存 新建时自动启动
        if(ui->cb_new_autorun->checkState()==Qt::Checked)PublicData::new_autorun=1;
        else PublicData::new_autorun=0;
        PublicData::obj_setting["new_autorun"]=PublicData::new_autorun;

        PublicData::qjd_setting.setObject(PublicData::obj_setting);
        PublicData::byte_setting=PublicData::qjd_setting.toJson();
        PublicData::file_setting.open(QIODevice::WriteOnly);
        PublicData::file_setting.write(PublicData::byte_setting);
        PublicData::file_setting.close();
        this->close();
    });
    //取消事件
    connect(ui->btn_ret,&QPushButton::clicked,[=](){
        this->close();
    });
    this->exec();
}

Setting::~Setting(){delete ui;}
