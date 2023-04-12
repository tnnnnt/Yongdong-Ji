#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {class Setting;}
class Setting : public QDialog
{
    Q_OBJECT
public:
    int minmax_min=1;
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
