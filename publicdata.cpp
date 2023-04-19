#include "publicdata.h"

PublicData::PublicData(){}
QString PublicData::file="data.json";
QJsonDocument PublicData::qjd;
QJsonObject PublicData::obj;
QByteArray PublicData::data;
QString PublicData::file_max_min="max_min.txt";
int PublicData::max_min;
QString PublicData::file_del_tip="del_tip.txt";
int PublicData::del_tip=1;
QString PublicData::file_new_autorun="new_autorun.txt";
int PublicData::new_autorun=1;

QString PublicData::icon_path=":/images/icon.jpg";
QString PublicData::title="永动姬";
