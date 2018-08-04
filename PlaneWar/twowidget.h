#ifndef TWOWIDGET_H
#define TWOWIDGET_H

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

class twoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit twoWidget(QWidget *parent = 0);
    ~twoWidget();
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    void closeEvent(QCloseEvent*);
    void controlTime() ;
    bool isCrash(Flyer,Flyer) ;
    //QPainter p ;
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
    QPixmap _pPic6;
    QPixmap _bPic1 ;
    QPixmap _bPic2 ;
    QPixmap bPic2 ;
    QPixmap bPic3 ;
    QPixmap bPic4 ;
    QPixmap bPic5 ;
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
    QTimer* timer10;//自动跟踪子弹
    QTimer* timer11;
    QTimer* bufftime2 ;
    QTimer* bufftime3 ;
    int flag[99999] = {0} ;
    int bossBulletFlag = 0 ;
    int intervalTime1 = 30; //move刷新间隔时间
    int intervalTime2 = 1800; //普通飞机
    int intervalTime3 = 2500; //生成子弹
    int intervalTime4 = 8000; //三发子弹飞机
    int intervalTime5 = 20000; //散射敌机
    int intervalTime6 = 8000; //自爆机
    int intervalTime7 = 70000; //生成boss
    int intervalTime8 = 1200;  //boss子弹A
    int intervalTmer10 =150; //自动跟踪的子弹
    int intervalTimer11=500;
    QPixmap sp[PLANENUM] ;
    int spFlag[PLANENUM] ;
signals:
    void back(Player) ;
public slots:
    void move() ;
    void createEnemy() ;
    void createBullet() ;
    void changeAttack_1() ;
    void changeAttack_2();
    void changeShield() ;
    void createBoss() ;
    void createBullet_A();
    void getPlayer(Player) ;
};

#endif // TWOWIDGET_H
