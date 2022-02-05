#pragma once

#include <QtWidgets/QWidget>
#include "ui_BaiLan.h"

class BaiLan : public QWidget
{
    Q_OBJECT

public:
    BaiLan(QWidget *parent = Q_NULLPTR);

private:
    Ui::BaiLanClass ui;
};
