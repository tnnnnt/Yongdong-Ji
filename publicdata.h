#ifndef PUBLICDATA_H
#define PUBLICDATA_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

class PublicData
{
public:
    static QFile file_data;
    static QByteArray byte_data;
    static QJsonDocument qjd_data;
    static QJsonObject obj_data;

    static QFile file_setting;
    static QByteArray byte_setting;
    static QJsonDocument qjd_setting;
    static QJsonObject obj_setting;

    static int max_min;
    static int del_tip;//删除提醒
    static int new_autorun;//新建时自动启动

    static QString icon_path;
    static QString title;
    PublicData();
    static void newOrEditItem(QString cont,QString ans,int min);
};

#endif // PUBLICDATA_H
