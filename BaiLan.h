#pragma once

#include <QtWidgets/QWidget>
#include<QImage>
#include<QGraphicsView>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include "ui_BaiLan.h"

class Unit;

class BaiLan : public QWidget
{
    Q_OBJECT

public:
    BaiLan(QWidget *parent = Q_NULLPTR);

    void LoadImage();//任何图片素材要求在类中添加新的QImage，然后在该函数中加载

    void DrawMap();

    void InitGame();

private:

    Ui::BaiLanClass ui;

    Unit* Player;

    QImage ImgGrass;

};
