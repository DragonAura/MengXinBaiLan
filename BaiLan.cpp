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
    case Unit_Enemy_Demon:
        Image.load(":/image/Enemy_Demon.png");
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
    time->setInterval(16);
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
    for (auto item : Map->GetEnemies())
    {
        QGraphicsPixmapItem* pixitem = new QGraphicsPixmapItem;
        pixitem->setPixmap(QPixmap::fromImage(GetUnitImg(item->GetID())));
        pixitem->setZValue(1);
        pixitem->setPos(QPointF(item->GetX(), item->GetY()));
        scene->addItem(pixitem);
    }
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

bool BaiLan::EncounterEnemy()
{
    Explore* Map = new Explore;
    for (auto item : Maps)
        if (item->GetID() == CurrentMap)
        {
            Map = item;
            break;
        }
    for (auto item : Map->GetEnemies())
        if (Player->GetX() <= item->GetX() + PlayerXSize && Player->GetX() >= item->GetX() - PlayerXSize &&
            Player->GetY() <= item->GetY() + PlayerYSize && Player->GetY() >= item->GetY() - PlayerYSize)
        {
            EnemyX = item->GetX();
            EnemyY = item->GetY();
            return true;
        }
    EnemyX = -9999;
    EnemyY = -9999;
    return false;
}

void BaiLan::Battle()
{
    Explore* Map = new Explore;
    for (auto item : Maps)
        if (item->GetID() == CurrentMap)
        {
            Map = item;
            break;
        }
    Unit* Enemy = new Unit;
    for(auto item:Map->GetEnemies())
        if (item->GetX() == EnemyX && item->GetY() == EnemyY)
        {
            Enemy = item;
            break;
        }
    //此处应当new一个Battle类，由于还没写，暂时跳过
    ui.testlabel->setText("遇敌！");
    if (PlayerWin)
        KillEnemy();
}

void BaiLan::KillEnemy()
{
    for (auto item : Maps)
        if (item->GetID() == CurrentMap)
        {
            item->KillEnemey(EnemyX, EnemyY);
            EnemyX = -9999, EnemyY = -9999;
            DrawMap();
            return;
        }
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

bool BaiLan::Test_Wall(Direction dir)
{
    int i;
    for (i = 0; i < Maps.size(); i++)
        if (Maps[i]->GetID() == CurrentMap)
            break;
    Explore* Map = Maps[i];
    bool result = false;
    switch (dir)
    {
    case Up:
        result = Map->GetObject(Player->GetX() / BlockSize, (Player->GetY() - 2) / BlockSize) == Object_WALL ||
            Map->GetObject(Player->GetX() / BlockSize + 1, (Player->GetY() - 2) / BlockSize) == Object_WALL ?
            true : false;
        break;
    case Left:
        result = Map->GetObject((Player->GetX() - 2) / BlockSize, Player->GetY() / BlockSize) == Object_WALL ||
            Map->GetObject((Player->GetX() - 2) / BlockSize, Player->GetY() / BlockSize + 1) == Object_WALL ||
            Map->GetObject((Player->GetX() - 2) / BlockSize, Player->GetY() / BlockSize + 2) == Object_WALL ?
            true : false;
        break;
    case Down:
        result = Map->GetObject(Player->GetX() / BlockSize, (Player->GetY() + PlayerYSize + 2) / BlockSize) == Object_WALL ||
            Map->GetObject(Player->GetX() / BlockSize + 1, (Player->GetY() + PlayerYSize + 2) / BlockSize) == Object_WALL ?
            true : false;
        break;
    case Right:
        result = Map->GetObject((Player->GetX() + PlayerXSize + 2) / BlockSize, Player->GetY() / BlockSize) == Object_WALL ||
            Map->GetObject((Player->GetX() + PlayerXSize + 2) / BlockSize, Player->GetY() / BlockSize + 1) == Object_WALL ||
            Map->GetObject((Player->GetX() + PlayerXSize + 2) / BlockSize, Player->GetY() / BlockSize + 2) == Object_WALL ?
            true : false;
        break;
    }
    return result;
}

void BaiLan::PlayerMovement()
{
    //static int i=0;
    //ui.testlabel->setNum(i++);
    if (Key_W == true && Test_Wall(Up) == false)Player->ChangePosition(0, -2);
    if (Key_A == true && Test_Wall(Left) == false)Player->ChangePosition(-2, 0);
    if (Key_S == true && Test_Wall(Down) == false)Player->ChangePosition(0, 2);
    if (Key_D == true && Test_Wall(Right) == false)Player->ChangePosition(2, 0);
    DrawUnit();
    if (EncounterEnemy())
        Battle();
}