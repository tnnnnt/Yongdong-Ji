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

class Edit : public QDialog
{
    Q_OBJECT

public:
    QVBoxLayout *vbl;
    QHBoxLayout *hbl0;
    QHBoxLayout *hbl1;
    QTextEdit *cont;
    QTextEdit *ans;
    QWidget *w_min;
    QWidget *w_sure;
    QLabel *l_min;
    QSpinBox *sb_min;
    QSpacerItem *si0;
    QSpacerItem *si1;
    QSpacerItem *si2;
    QSpacerItem *si3;
    QPushButton *btn_sure;
    QPushButton *btn_ret;
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();
};

#endif // EDIT_H
