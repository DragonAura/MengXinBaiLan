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
    case Unit_Enemy_Slime:
        Image.load(":/image/Enemy_Slime.png");
        break;
    }
    return Image;
}

Object_ID GetObj(Map_ID id)
{
    Object_ID object;
    switch (id)
    {
    case Map_MAP1:
        object = Object_GRASS;
        break;
    }
    return object;
}

BaiLan::BaiLan(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    InitGame();
    time = new QTimer();
    time->setInterval(1);
    connect(time, SIGNAL(timeout()), this, SLOT(PlayerMovement()));
    time->start();
    
}

int GetLength(int num)
{
    if (num >= 0 && num < 10) return 1;
    else if (num >= 10 && num < 100) return 2;
    else if (num >= 100 && num < 1000)return 3;
    else if (num >= 1000 && num < 10000)return 4;
    else return 5;
}

void BaiLan::ResetKey()
{
    Key_W = false;
    Key_A = false;
    Key_S = false;
    Key_D = false;
}

void BaiLan::keyPressEvent(QKeyEvent* event)
{
    if (InBattle == false)
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
}

void BaiLan::keyReleaseEvent(QKeyEvent* event)
{
    if (InBattle == false)
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
}

void BaiLan::AddMap(Map_ID id)
{
    Maps.push_back(MapGenerator(id));
}

void BaiLan::DrawMap()//画出以CurrentMap为ID的地图
{
    Explore* Map = new Explore;
    QGraphicsScene* scene = new QGraphicsScene;
    for(auto item:Maps)
        if (item->GetID() == CurrentMap)
        {
            *Map = *item;
            break;
        }
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

void BaiLan::DrawBattleMap()
{
    QGraphicsScene* scene = new QGraphicsScene;
    for (int i = 0; i < MapXSize / BlockSize; i++)
        for (int j = 0; j < MapYSize / BlockSize; j++)
        {
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
            item->setPixmap(QPixmap::fromImage(GetObjImg(battle->GetMap())));
            item->setPos(QPointF(i * BlockSize, j * BlockSize));
            scene->addItem(item);
        }
    scene->setSceneRect(0, 0, 960, 960);
    ui.GraphicsView->setScene(scene);
}

void BaiLan::DrawBattleUnit()
{
    MyGraphicsScene* scene = new MyGraphicsScene(this);
    for (auto item : battle->BattleUnit)
    {
        QLabel* newlabel = new QLabel;
        newlabel->setNum(item->GetHP());
        QGraphicsProxyWidget* proxyWidget = scene->addWidget(newlabel);
        int length = GetLength(item->GetHP());
        switch (length)
        {
        case 1:
            proxyWidget->setPos(QPointF(item->BattleX * BlockSize+10, item->BattleY * BlockSize - 9));
            break;
        case 2:
            proxyWidget->setPos(QPointF(item->BattleX * BlockSize+6, item->BattleY * BlockSize - 9));
            break;
        case 3:
            proxyWidget->setPos(QPointF(item->BattleX * BlockSize+2, item->BattleY * BlockSize - 9));
            break;
        case 4:
            proxyWidget->setPos(QPointF(item->BattleX * BlockSize-1, item->BattleY * BlockSize - 9));
            break;
        }
        
        QGraphicsPixmapItem* pixitem = new QGraphicsPixmapItem;
        pixitem->setPixmap(QPixmap::fromImage(GetUnitImg(item->GetID())));
        pixitem->setPos(QPointF(item->BattleX * BlockSize, item->BattleY * BlockSize));
        scene->addItem(pixitem);
    }
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
        if (Player->GetX() <= item->GetX() + item->SizeX && Player->GetX() >= item->GetX() - Player->SizeX &&
            Player->GetY() <= item->GetY() + item->SizeY && Player->GetY() >= item->GetY() - Player->SizeY)
        {
            EnemyX = item->GetX();
            EnemyY = item->GetY();
            return true;
        }
    EnemyX = -9999;
    EnemyY = -9999;
    return false;
}

void BaiLan::StartBattle()
{
    ResetKey();
    Explore* Map = new Explore;
    for (auto item : Maps)
        if (item->GetID() == CurrentMap)
        {
            Map = item;
            break;
        }
    Unit* Enemy = new Unit;
    //int PlayerX = Player->GetX(), PlayerY = Player->GetY();
    for(auto item:Map->GetEnemies())
        if (item->GetX() == EnemyX && item->GetY() == EnemyY)
        {
            Enemy = item;
            break;
        }
    battle = new Battle(Player, Enemy, this, GetObj(Map->GetID()));
    InBattle = true;
    battle->InBattle();
    DrawMap();
    delete battle;
    battle = nullptr;
    InBattle = false;
    if (Player->LevelUp())ui.Information->append(Player->GetName() + " Level up! ");
    ui.HpLabel->setNum(Player->GetHP());
    ui.testlabel->setText("遇敌！");
    if (Player->Alive())
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

void BaiLan::ChangeControl()
{
    MouseX = -1, MouseY = -1;
    PlayerControl = !PlayerControl;
}

void BaiLan::AddInformation(QString text)
{
    ui.Information->append(text);
}

void BaiLan::InitGame()
{
    CurrentMap = Map_MAP1;
    AddMap(Map_MAP1);
    Player = new Unit(100, 5, 100, 1, Unit_Player, 4);
    battle = nullptr;
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
    setMouseTracking(true);
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
        result = Map->GetObject(Player->GetX() / BlockSize, (Player->GetY() + Player->SizeY + 2) / BlockSize) == Object_WALL ||
            Map->GetObject(Player->GetX() / BlockSize + 1, (Player->GetY() + Player->SizeY + 2) / BlockSize) == Object_WALL ?
            true : false;
        break;
    case Right:
        result = Map->GetObject((Player->GetX() + Player->SizeX + 2) / BlockSize, Player->GetY() / BlockSize) == Object_WALL ||
            Map->GetObject((Player->GetX() + Player->SizeX + 2) / BlockSize, Player->GetY() / BlockSize + 1) == Object_WALL ||
            Map->GetObject((Player->GetX() + Player->SizeX + 2) / BlockSize, Player->GetY() / BlockSize + 2) == Object_WALL ?
            true : false;
        break;
    }
    return result;
}

void BaiLan::PlayerMovement()
{
    //static int i=0;
    //ui.testlabel->setNum(i++);
    if (Key_W == true && Test_Wall(Up) == false)Player->ChangePosition(0, -1);
    if (Key_A == true && Test_Wall(Left) == false)Player->ChangePosition(-1, 0);
    if (Key_S == true && Test_Wall(Down) == false)Player->ChangePosition(0, 1);
    if (Key_D == true && Test_Wall(Right) == false)Player->ChangePosition(1, 0);
    DrawUnit();
    if (EncounterEnemy())
        StartBattle();
}

void BaiLan::on_AttackButton_clicked()
{
    if (InBattle == true && PlayerControl == true && SlotToUse != 0)
    {
        SlotToUse = 0;
        SkillChosen = true;
        AddInformation("Skill Chosen: Attack");
    }
    else if (SkillChosen == true && SlotToUse == 0)
    {
        SlotToUse = -1;
        SkillChosen = false;
        Player->ClearOpponent();
        AddInformation("Skill Unchosen: Attack");
    }
}

void BaiLan::on_ConfirmButton_clicked()
{
    if (SkillChosen == true && Player->OpponentNum > 0)
    {
        Player->UseSkill(SlotToUse);
        UseSkill = true;
        SlotToUse = -1;
        SkillChosen = false;
    }
    else
        AddInformation("Failed to do so!");
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    bool test = false;
    bailan->MouseX = event->scenePos().x() / BlockSize;
    bailan->MouseY = event->scenePos().y() / BlockSize;
    if (bailan->PlayerControl == true)
    {
        for (auto item : bailan->battle->BattleUnit)
        {
            if (bailan->MouseX <= item->BattleX + item->SizeX / BlockSize &&
                bailan->MouseX >= item->BattleX &&
                bailan->MouseY <= item->BattleY + item->SizeY / BlockSize &&
                bailan->MouseY >= item->BattleY)
            {
                CurrentUnit = item;
                bailan->MouseHaveUnit = true;
                test = true;
                break;
            }
        }
        if (test == false)
        {
            CurrentUnit = nullptr;
            bailan->MouseHaveUnit = false;
        }
    }
    bailan->ui.MouseX->setNum(bailan->MouseX);
    bailan->ui.MouseY->setNum(bailan->MouseY);
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (bailan->SkillChosen == true && bailan->MouseHaveUnit == true)
    {
        bool test = false;
        for (auto item : bailan->Player->GetOpponent())
        {
            if (item->GetName() == CurrentUnit->GetName())
            {
                test = true;
                bailan->Player->RemoveOpponent(CurrentUnit);
                bailan->AddInformation("Removed Opponent: " + CurrentUnit->GetName());
                break;
            }
        }
        if (test == false&&bailan->Player->testOpp(bailan->SlotToUse) == true)
        {
            bailan->Player->AddOpponent(CurrentUnit);
            bailan->AddInformation("Added Opponent: " + CurrentUnit->GetName());
        }
        else if (test == false && bailan->Player->testOpp(bailan->SlotToUse) == false)
        {
            bailan->AddInformation("Failed to add opponent! Reached max number of your chosen skill! ");
        }
    }
    else if (bailan->SkillChosen == false && bailan->MouseHaveUnit == false)
    {
        bailan->Player->BattleX = bailan->MouseX / BlockSize;
        bailan->Player->BattleY = bailan->MouseY / BlockSize;
        bailan->DrawBattleUnit();
    }

}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    
}