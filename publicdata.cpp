#include "publicdata.h"

PublicData::PublicData(){}
QFile PublicData::file_data=QFile("data.json");
QByteArray PublicData::byte_data;
QJsonDocument PublicData::qjd_data;
QJsonObject PublicData::obj_data;

QFile PublicData::file_setting=QFile("setting.json");
QByteArray PublicData::byte_setting;
QJsonDocument PublicData::qjd_setting;
QJsonObject PublicData::obj_setting;

int PublicData::max_min=360;
bool PublicData::del_tip=true;
bool PublicData::new_autorun=true;
QString PublicData::family="SimSun";//字体
int PublicData::pointsize=20;//字体像素大小
bool PublicData::bold=false;
bool PublicData::italic=false;
bool PublicData::underline=false;
QString PublicData::words;

QString PublicData::icon_path=":/images/icon.jpg";
QString PublicData::title="永动姬";
QFont PublicData::qf=QFont();

void PublicData::newOrEditItem(QString cont,QString ans,int min){
    QJsonObject obj_tmp;
    obj_tmp["answer"]=ans;
    obj_tmp["minute"]=min;
    PublicData::obj_data[cont]=obj_tmp;
    PublicData::qjd_data.setObject(PublicData::obj_data);
    PublicData::byte_data=PublicData::qjd_data.toJson();
    PublicData::file_data.open(QIODevice::WriteOnly);
    PublicData::file_data.write(PublicData::byte_data);
    PublicData::file_data.close();
}
