#include "total.h"

QImage GetObjImg(Object_ID id)
{
    QImage Image;
    switch (id)
    {
    case Object_GRASS:
        Image.load(":/image/grass.jpg");
        break;
    case Object_AIR:
        Image.load(":/image/air.jpg");
        break;
    default:
        Image.load(":/image/black.jpg");
        break;
    }
    return Image;
}

QImage GetUnitImg(Unit_ID id)
{
    QImage Image;
    switch (id)
    {
    case Unit_Player:
        Image.load(":/image/player.jpg");
        break;
    }
    return Image;
}

BaiLan::BaiLan(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void BaiLan::AddMap(Map_ID id)
{
    Maps.push_back(MapGenerator(id));
}

void BaiLan::DrawMap()//画出以CurrentMap为ID的地图
{
    int i;
    QGraphicsScene* scene = new QGraphicsScene;
    for (i = 0; i < Maps.size(); i++)
        if (Maps[i]->GetID() == CurrentMap)
            break;
    Explore* Map = Maps[i];
    for (int i = 0; i < MapXSize / BlockSize; i++)
        for (int j = 0; j < MapYSize / BlockSize; j++)
        {
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
            item->setPixmap(QPixmap::fromImage(GetObjImg(Map->GetObject(i, j))));
            item->setPos(QPointF(i * BlockSize, j * BlockSize));
            scene->addItem(item);
        }
    {
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
        item->setPixmap(QPixmap::fromImage(GetUnitImg(Unit_Player)));
        item->setPos(QPointF(Player->GetX(), Player->GetY()));
        item->setZValue(1);
        scene->addItem(item);
    }
    ui.GraphicsView->setScene(scene);
    //ui.GraphicsView->show();
}

//这是首次测试绘图时使用的版本，和正式版本有较大的差异
//void BaiLan::DrawMap()
//{
//    QGraphicsScene* scene = new QGraphicsScene;
//    for (int i = 0; i < MapXSize / BlockSize; i++)
//        for (int j = 0; j < MapYSize / BlockSize; j++)
//        {
//            QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
//            item->setPixmap(QPixmap::fromImage(ImgGrass));
//            item->setPos(QPointF(i * BlockSize, j * BlockSize));
//            scene->addItem(item);
//        }
//    ui.GraphicsView->setScene(scene);
//    //ui.GraphicsView->show();
//}

void BaiLan::InitGame()
{
    CurrentMap = Map_MAP1;
    AddMap(Map_MAP1);

}