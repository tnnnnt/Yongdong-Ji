#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Edit.h>
#include <QMenu>
#include <QSystemTrayIcon>  //t托盘类
#include <QFile>
#include <QJsonObject>
#include <item.h>
#include <QPushButton>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    QMenu *trayMenu;//托盘菜单
    QSystemTrayIcon *tray;//托盘图标添加成员
    //右键菜单栏选项
    QAction* newAction;
    QAction* quitAction;
    Edit *e;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
public slots:
    void iconActivated(QSystemTrayIcon::ActivationReason ireason);
    void additem();
};
#endif // WIDGET_H
