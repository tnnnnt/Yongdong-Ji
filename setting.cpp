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
    if(PublicData::del_tip)ui->cb_del_tip->setCheckState(Qt::Checked);
    else ui->cb_del_tip->setCheckState(Qt::Unchecked);
    //新建时自动启动
    if(PublicData::new_autorun)ui->cb_new_autorun->setCheckState(Qt::Checked);
    else ui->cb_new_autorun->setCheckState(Qt::Unchecked);
    //字体
    QStringList strList;
    strList<<"SimSun"<<"SimHei"<<"Microsoft YaHei"<<"Microsoft JhengHei"<<"NSimSun"<<"MingLiU"<<"FangSong"<<"KaiTi"<<"STHeiti"<<"STKaiti"<<"STFangsong"<<"BiauKai"<<"LiSu"<<"YouYuan"<<"STXihei"<<"STZhongsong"<<"FZShuTi"<<"FZYaoti"<<"STCaiyun"<<"STHupo"<<"STLiti"<<"STXingkai"<<"STXinwei";
    ui->cbb_family->addItems(strList);
    ui->cbb_family->setCurrentText(PublicData::family);
    ui->sb_pointsize->setValue(PublicData::pointsize);
    if(PublicData::bold)ui->cb_bold->setCheckState(Qt::Checked);
    else ui->cb_bold->setCheckState(Qt::Unchecked);
    if(PublicData::italic)ui->cb_italic->setCheckState(Qt::Checked);
    else ui->cb_italic->setCheckState(Qt::Unchecked);
    if(PublicData::underline)ui->cb_underline->setCheckState(Qt::Checked);
    else ui->cb_underline->setCheckState(Qt::Unchecked);
    ui->te_show->setFont(PublicData::qf);
    ui->te_show->setText(PublicData::words);

    //展示字体事件
    connect(ui->cbb_family,&QComboBox::activated,[=](){
        ui->te_show->setFontFamily(ui->cbb_family->currentText());
        ui->te_show->setText(PublicData::words);
    });
    connect(ui->sb_pointsize,&QSpinBox::valueChanged,[=](){
        ui->te_show->setFontPointSize(ui->sb_pointsize->value());
        ui->te_show->setText(PublicData::words);
    });
    connect(ui->cb_bold,&QCheckBox::stateChanged,[=](){
        ui->te_show->setFontWeight(ui->cb_bold->isChecked()?QFont::Bold:QFont::Normal);
        ui->te_show->setText(PublicData::words);
    });
    connect(ui->cb_italic,&QCheckBox::stateChanged,[=](){
        ui->te_show->setFontItalic(ui->cb_italic->isChecked());
        ui->te_show->setText(PublicData::words);
    });
    connect(ui->cb_underline,&QCheckBox::stateChanged,[=](){
        ui->te_show->setFontUnderline(ui->cb_underline->isChecked());
        ui->te_show->setText(PublicData::words);
    });
    connect(ui->te_show,&QTextEdit::textChanged,[=](){
        PublicData::obj_setting["words"]=PublicData::words=ui->te_show->toPlainText();
    });
    //保存事件
    connect(ui->btn_sure,&QPushButton::clicked,[=](){
        //保存 最大间隔分
        PublicData::obj_setting["max_min"]=PublicData::max_min=ui->sb_min->value();
        //保存 删除确认
        PublicData::obj_setting["del_tip"]=PublicData::del_tip=ui->cb_del_tip->isChecked();
        //保存 新建时自动启动
        PublicData::obj_setting["new_autorun"]=PublicData::new_autorun=ui->cb_new_autorun->isChecked();
        //保存 字体
        PublicData::obj_setting["family"]=PublicData::family=ui->cbb_family->currentText();
        PublicData::obj_setting["pointsize"]=PublicData::pointsize=ui->sb_pointsize->value();
        PublicData::obj_setting["bold"]=PublicData::bold=ui->cb_bold->isChecked();
        PublicData::obj_setting["italic"]=PublicData::italic=ui->cb_italic->isChecked();
        PublicData::obj_setting["underline"]=PublicData::underline=ui->cb_underline->isChecked();

        PublicData::qjd_setting.setObject(PublicData::obj_setting);
        PublicData::byte_setting=PublicData::qjd_setting.toJson();
        PublicData::file_setting.open(QIODevice::WriteOnly);
        PublicData::file_setting.write(PublicData::byte_setting);
        PublicData::file_setting.close();

        PublicData::qf.setFamily(PublicData::family);
        PublicData::qf.setPointSize(PublicData::pointsize);
        PublicData::qf.setBold(PublicData::bold);
        PublicData::qf.setItalic(PublicData::italic);
        PublicData::qf.setUnderline(PublicData::underline);
        this->close();
    });
    //取消事件
    connect(ui->btn_ret,&QPushButton::clicked,[=](){
        this->close();
    });
    this->exec();
}

Setting::~Setting(){delete ui;}
