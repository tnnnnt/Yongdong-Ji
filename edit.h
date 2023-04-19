#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QSlider>
#include "timeset.h"

class Edit : public QDialog
{
    Q_OBJECT

public:
    QVBoxLayout *vbl;
    QHBoxLayout *hbl;
    QTextEdit *cont;
    QTextEdit *ans;
    Timeset *w_min;
    QWidget *w_sure;
    QPushButton *btn_sure;
    QPushButton *btn_ret;
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();
};

#endif // EDIT_H
