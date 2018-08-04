#ifndef ONEWIDGET_H
#define ONEWIDGET_H
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QTimer>
#include <QTime>
#include <QDialog>
#include <QRect>
#include <QSize>
#include <QCloseEvent>
#include <QMessageBox>
#include "flyer.h"
#include "player.h"
#define WIDTH 800
#define HEIGHT 1000
#define PLANENUM 5

class oneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit oneWidget(QWidget *parent = 0);
    ~oneWidget();
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void closeEvent(QCloseEvent*);
    void controlTime() ;
    bool isCrash(Flyer,Flyer) ;
    Player player ;
    QPixmap moneyPic ;
    QPixmap bk1 ;
    QPixmap pPic1 ;//我方飞机和子弹
    QPixmap bPic1 ;
    QPixmap _pPic1 ;//敌方飞机和子弹
    QPixmap _pPic2 ;
    QPixmap _pPic3 ;
    QPixmap _pPic4 ;
    QPixmap _pPic5 ;
    QPixmap _pPic6 ;
    QPixmap _bPic1 ;
    QPixmap _bPic2 ;
    QPixmap bPic2 ;
    QPixmap bPic3 ;
    QPixmap bPic4 ;
    QPixmap bPic5 ;
    QPixmap bPic6 ;
    QPixmap hurt1 ;
    QPixmap die1 ;
    QPixmap buff1 ;
    QPixmap buff2 ;
    QPixmap buff3 ;
    QPixmap shield ;
    QPixmap bloodBar ;
    QPixmap smallBlood ;
    QVector<Bullet> bullets ;
    QVector<Bullet> enemyBullets ;
    QVector<Enemy> enemys ;
    QVector<Prop> props ;
    Plane* plane ;
    QTimer* timer1 ;//moveBullet
    QTimer* timer2 ;//生成普通敌机
    QTimer* timer3 ;//生成敌方子弹
    QTimer* timer4 ;//生成发射三发子弹的敌机
    QTimer* timer5 ;//散射敌机
    QTimer* timer6 ;//生成追踪机
    QTimer* timer7 ;//停止其他计时器，产生boss
    QTimer* timer8 ;//boss子弹
    QTimer* timer9 ;//boss子弹
    QTimer*timer10;//自动瞄准
    QTimer*timer11;//自爆机2号
    QTimer* bufftime2 ;
    QTimer* bufftime3 ;
    int flag[99999] = {0} ;
    int bossBulletFlag = 0 ;
    int intervalTime1 = 30; //move刷新间隔时间
    int intervalTime2 = 1400; //普通飞机
    int intervalTime3 = 2700; //生成子弹
    int intervalTime4 = 3000; //三发子弹飞机
    int intervalTime5 = 8500; //散射敌机
    int intervalTime6 = 8200; //自爆机
    int intervalTime7 = 60000; //生成boss
    int intervalTime8 = 3600;  //boss子弹A
    int intervalTime9 = 2800;  //boss子弹B
    int intervalTime10 = 5100;//自动瞄准飞机
    int intervalTime11 =700;//自爆机
    QPixmap sp[PLANENUM] ;
    int spFlag[PLANENUM] ;
    int whichPlane = -1;
    int planeFourAttackFlag = 0 ;

signals:
    void back(Player) ;
public slots:
    void move() ;
    void createEnemy() ;
    void createBullet() ;
    void changeAttack() ;
    void changeShield() ;
    void createBoss() ;
    void createBullet_A();
    void createBullet_B();
    void getPlayer(Player) ;
};

#endif // ONEWIDGET_H
