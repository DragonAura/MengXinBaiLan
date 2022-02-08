#include "total.h"

BaiLan::BaiLan(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void BaiLan::LoadImage()
{
    ImgGrass.load(":/image/grass.jpg");
}

void BaiLan::DrawMap()
{
    QGraphicsScene* scene = new QGraphicsScene;
    for (int i = 0; i < MapXSize / BlockSize; i++)
        for (int j = 0; j < MapYSize / BlockSize; j++)
        {
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
            item->setPixmap(QPixmap::fromImage(ImgGrass));
            item->setPos(QPointF(i * BlockSize, j * BlockSize));
            scene->addItem(item);
        }
    ui.GraphicsView->setScene(scene);
    //ui.GraphicsView->show();
}

void BaiLan::InitGame()
{
    LoadImage();
    DrawMap();
}