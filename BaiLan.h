#pragma once

#include <QtWidgets/QWidget>
#include<QImage>
#include<QEventLoop>
#include<QGraphicsView>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include<QInputDialog>
#include<QKeyEvent>
#include<QTimer>
#include "ui_BaiLan.h"

enum Object_ID;
enum Map_ID;
enum Unit_ID;

enum Direction
{
    Up,
    Left,
    Down,
    Right
};

class Explore;
class Unit;
class Battle;

QImage GetObjImg(Object_ID id);//返回某一Object的贴图
QImage GetUnitImg(Unit_ID id);//返回某一Unit的贴图
QString GetName(Unit_ID id);
Object_ID GetObj(Map_ID id);

class BaiLan : public QWidget
{
    Q_OBJECT

public:
    BaiLan(QWidget *parent = Q_NULLPTR);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void ResetKey();

    void AddMap(Map_ID id);

    void ChangeUIPlayerHP(int hp) { ui.HpLabel->setNum(hp); }
    void ChangeUIEnemyName(QString name) { ui.NameEnemy->setText(name); }
    void ChangeUIEnemyHealth(int hp) { ui.HealthEnemy->setNum(hp); }
    void ChangeUIEnemyHealth(QString hp) { ui.HealthEnemy->setText(hp); }

    int GetSlot() { return SlotToUse; }
    void ResetSlot() { SlotToUse = -1; }

//该函数作用为画出不可移动的部分
    void DrawMap();//该函数未检测数据合法性，要求自行注意以CurrentMap为ID的Explore类是否存在于Maps数组内

//该函数作用为画出可以移动的部分
    void DrawUnit();

//该函数画出战斗地图
    void DrawBattleMap();

//该函数画出战斗中的Unit的位置
    void DrawBattleUnit();

    Map_ID GetMap() { return CurrentMap; }

    bool EncounterEnemy();
    void StartBattle();
    void KillEnemy();
    void ChangeControl();

    void AddInformation(QString text);

    void InitGame();

private:
    int SlotToUse = -1;//记录玩家接下来将要使用的技能所在的技能槽

    bool InBattle = false;
    bool PlayerControl = false;

    bool PlayerWin = true;

    bool Test_Wall(Direction dir);

    bool Key_W = false;
    bool Key_A = false;
    bool Key_S = false;
    bool Key_D = false;

    Ui::BaiLanClass ui;

    int EnemyX=-9999, EnemyY=-9999;//记录正在发生战斗的敌人的位置

    Unit* Player;

    Map_ID CurrentMap;
    std::vector<Explore*> Maps;

    Battle* battle;

    QTimer* time;

public slots:
    void PlayerMovement();
    void on_AttackButton_clicked();

};
