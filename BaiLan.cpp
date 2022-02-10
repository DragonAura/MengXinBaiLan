#include "total.h"

QImage GetObjImg(Object_ID id)
{
    QImage Image;
    switch (id)
    {
    case Object_GRASS:
        Image.load(":/image/grass.jpg");
        break;
    case Object_WALL:
        Image.load(":/image/wall.jpg");
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
        Image.load(":/image/player.png");
        break;
    }
    return Image;
}

BaiLan::BaiLan(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    InitGame();
    time = new QTimer();
    time->setInterval(1000/FPS);
    connect(time, SIGNAL(timeout()), this, SLOT(PlayerMovement()));
    time->start();
    
}

void BaiLan::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W ||
        event->key() == Qt::Key_Up)
        Key_W = true;
    if (event->key() == Qt::Key_A ||
        event->key() == Qt::Key_Left)
        Key_A = true;
    if (event->key() == Qt::Key_S ||
        event->key() == Qt::Key_Down)
        Key_S = true;
    if (event->key() == Qt::Key_D ||
        event->key() == Qt::Key_Right)
        Key_D = true;
}

void BaiLan::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W ||
        event->key() == Qt::Key_Up)
        Key_W = false;
    if (event->key() == Qt::Key_A ||
        event->key() == Qt::Key_Left)
        Key_A = false;
    if (event->key() == Qt::Key_S ||
        event->key() == Qt::Key_Down)
        Key_S = false;
    if (event->key() == Qt::Key_D ||
        event->key() == Qt::Key_Right)
        Key_D = false;
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
    for (int i = 0; i < MapXSize/BlockSize; i++)
        for (int j = 0; j < MapYSize/BlockSize; j++)
        {
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
            item->setPixmap(QPixmap::fromImage(GetObjImg(Map->GetObject(i, j))));
            item->setPos(QPointF(i * BlockSize, j * BlockSize));
            scene->addItem(item);
        }
    //{
    //    QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
    //    item->setPixmap(QPixmap::fromImage(GetUnitImg(Unit_Player)));
    //    item->setPos(QPointF(Player->GetX(), Player->GetY()));
    //    item->setZValue(1);
    //    scene->addItem(item);
    //}
    ui.GraphicsView->setScene(scene);
}

void BaiLan::DrawUnit()
{
    QGraphicsScene* scene = new QGraphicsScene;
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
    item->setPixmap(QPixmap::fromImage(GetUnitImg(Unit_Player)));
    item->setPos(QPointF(Player->GetX(), Player->GetY()));
    scene->addItem(item);
    scene->setSceneRect(0, 0, 960, 960);
    ui.UnitView->setScene(scene);
}

void BaiLan::InitGame()
{
    CurrentMap = Map_MAP1;
    AddMap(Map_MAP1);
    Player = new Unit(100, 1, 0, 1, Unit_Player, 4);
    bool ok = false;
    QString playername;
    while (!ok || playername.isEmpty())
        playername = QInputDialog::getText(this, tr("请输入你的名字"), tr("你的名字："), QLineEdit::Normal, 0, &ok);
    Player->SetName(playername);
    Player->ChangePosition(480, 480, Map_MAP1);
    this->grabKeyboard();
    ui.UnitView->setStyleSheet("background: transparent;border:0px");
    setFocusPolicy(Qt::StrongFocus);
    DrawMap();
    DrawUnit();
}

void BaiLan::PlayerMovement()
{
    static int i = 0;
    ui.testlabel->setNum(i++);
    if (Key_W == true)Player->ChangePosition(0, -2);
    if (Key_A == true)Player->ChangePosition(-2, 0);
    if (Key_S == true)Player->ChangePosition(0, 2);
    if (Key_D == true)Player->ChangePosition(2, 0);
    DrawUnit();
}