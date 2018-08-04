#ifndef STOREWIDGET_H
#define STOREWIDGET_H

#define PLANENUM 5 //飞机数量

#include <QWidget>
#include <QCloseEvent>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QMediaPlayer>
#include "player.h"

class StoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StoreWidget(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*);
    void paintEvent(QPaintEvent*);
    QPixmap bk ;
    QPixmap showPlane ;
    QPixmap sp[PLANENUM] ;
    int price[PLANENUM] ;
    QPixmap money ;
    Player player ;
    int presentShow = 0 ;
    int flag[PLANENUM] ;
    QPushButton next ;
    QPushButton pre ;
    QPushButton moneyButton ;
    QPushButton priceButton ;
    QPushButton equip ;
    QMediaPlayer* c_player ;

signals:
    void goBack(Player) ;

public slots:
    void getPlayerMsg(Player) ;
    void nextPlane() ;
    void prePlane() ;
    void buyPlane() ;
    void equipPlane() ;
};

#endif // STOREWIDGET_H
