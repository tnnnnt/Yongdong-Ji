#ifndef PUBLICDATA_H
#define PUBLICDATA_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFont>

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

    //设置项
    static int max_min;//最大间隔分
    static bool del_tip;//删除提醒
    static bool new_autorun;//新建时自动启动
    static QString family;//字体
    static int pointsize;//字体像素大小
    static bool bold;//字体加粗
    static bool italic;//斜体
    static bool underline;//下划线
    static QString words;//展示字体

    static QString icon_path;
    static QString title;
    static QFont qf;
    PublicData();
    static void newOrEditItem(QString cont,QString ans,int min);
};

#endif // PUBLICDATA_H
