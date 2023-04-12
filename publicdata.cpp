#include "publicdata.h"

PublicData::PublicData()
{

}
QString PublicData::file="data.json";
QJsonDocument PublicData::qjd;
QJsonObject PublicData::obj;
QByteArray PublicData::data;
QString PublicData::icon_path=":/images/icon.jpg";
QString PublicData::title="永动姬";
