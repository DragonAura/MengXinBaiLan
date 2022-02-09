#pragma once

#include <QtWidgets/QWidget>
#include<QImage>
#include<QGraphicsView>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include "ui_BaiLan.h"

enum Object_ID;
enum Map_ID;
enum Unit_ID;

class Explore;
class Unit;

QImage GetObjImg(Object_ID id);//返回某一Object的贴图
QImage GetUnitImg(Unit_ID id);//返回某一Unit的贴图

class BaiLan : public QWidget
{
    Q_OBJECT

public:
    BaiLan(QWidget *parent = Q_NULLPTR);

    void AddMap(Map_ID id);
    void DrawMap();//该函数未检测数据合法性，要求自行注意以CurrentMap为ID的Explore类是否存在于Maps数组内

    void InitGame();

private:

    Ui::BaiLanClass ui;

    Unit* Player;

    Map_ID CurrentMap;
    std::vector<Explore*> Maps;

};
