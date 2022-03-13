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
#include<QGraphicsProxyWidget>
#include<QMouseEvent>
#include<QGraphicsSceneMouseEvent>
#include<QCloseEvent>
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

typedef struct Coord
{
    int x;
    int y;
}Coordinates;

class Explore;
class Unit;
class Battle;

QImage GetObjImg(Object_ID id);//返回某一Object的贴图
QImage GetUnitImg(Unit_ID id);//返回某一Unit的贴图
QString GetName(Unit_ID id);
Object_ID GetObj(Map_ID id);
int GetLength(int num);

class BaiLan : public QWidget
{
    Q_OBJECT

public:
    friend class MyGraphicsScene;

    BaiLan(QWidget *parent = Q_NULLPTR);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);

    void ResetKey();

    void AddMap(Map_ID id);
    void ResetMap();
    void TestHeal();

    void RefreshHp();
    void RefreshSp();
    void RefreshMap();

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
    bool UseSkill = false;
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
    bool SkillChosen = false;//记录是否已经选择了技能
    bool MouseHaveUnit = false;//记录鼠标所在位置是否有单位

    bool Key_W = false;
    bool Key_A = false;
    bool Key_S = false;
    bool Key_D = false;


    Ui::BaiLanClass ui;

    int EnemyX=-9999, EnemyY=-9999;//记录正在发生战斗的敌人的位置
    int MouseX = -1, MouseY = -1;

    Unit* Player;

    Map_ID CurrentMap;
    std::vector<Explore*> Maps;

    Battle* battle;

    QTimer* time;

public slots:
    void PlayerMovement();
    void on_AttackButton_clicked();
    void on_ConfirmButton_clicked();
    void on_Skill1Button_clicked();
    void on_Skill2Button_clicked();
    void on_Skill3Button_clicked();
    void on_Skill4Button_clicked();

};

class MyGraphicsScene :public QGraphicsScene
{
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    BaiLan* bailan;
    Unit* CurrentUnit = nullptr;

public:
    MyGraphicsScene(BaiLan* bl) :bailan(bl) {}

};

void Juqing1();