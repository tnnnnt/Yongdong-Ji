#ifndef PUBLICDATA_H
#define PUBLICDATA_H

#include <QJsonObject>
#include <QJsonDocument>

class PublicData
{
public:
    static QString file;
    static QString file_max_min;
    static QString file_del_tip;
    static QString file_new_autorun;
    static QJsonDocument qjd;
    static QJsonObject obj;
    static QByteArray data;
    static QString icon_path;
    static QString title;
    static int max_min;
    static int del_tip;//删除提醒
    static int new_autorun;//新建时自动启动
    PublicData();
};

#endif // PUBLICDATA_H
