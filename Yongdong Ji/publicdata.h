#ifndef PUBLICDATA_H
#define PUBLICDATA_H

#include <QJsonObject>
#include <QJsonDocument>

class PublicData
{
public:
    static QString file;
    static QJsonDocument qjd;
    static QJsonObject obj;
    static QByteArray data;
    static QString icon_path;
    static QString title;
    PublicData();
};

#endif // PUBLICDATA_H
