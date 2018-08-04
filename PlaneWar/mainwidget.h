#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#define TOTALSONG 4
#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QPainter>
#include <QApplication>
#include <QString>
#include <QPaintEvent>
#include <QDesktopWidget>
#include <QPushButton>
#include <QSqlTableModel>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>
#include <QSqlRecord>
#include <QTextEdit>
#include "mywidget.h"
#include "player.h"
#include "storewidget.h"
#include "settingwidget.h"
#include "onewidget.h"
#include "twowidget.h"
#include "helpwidget.h"


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);
    QPixmap mainBk ;
    QPixmap moneyPic ;
    myWidget* w ;
    oneWidget* ow ;
    twoWidget* tw ;
    StoreWidget* sw ;
    SettingWidget* setw ;
    HelpWidget* hw ;
    QPushButton b_start ;
    QPushButton b_quit ;
    QPushButton b_store ;
    QPushButton b_help ;
    QPushButton b_setting ;
    QPushButton welMsg ;//欢迎信息
    QPushButton money ;
    QPushButton maxScore ;
    QPushButton partOne ;
    QPushButton partTwo ;
    QPushButton partThree ;
    QSignalMapper* myMapper ;
    Player player ;
    int flag = 0 ;
    int musicVolume = 100 ;
    int soundVolume = 100 ;
    QMediaPlayer* m_player ;
    QMediaPlayer* c_player ;
    QMediaPlaylist* m_playerList ;
    int currentSong = 1 ;

signals:
    void sendPlayer(Player) ;
    void sendVolume(int,int) ;
public slots:
    void change(int) ;
    void reShow(Player) ;
    void getData(Player) ;
    void closeWindows() ;
    void pushPartOne() ;
    void pushPartTwo() ;
    void pushPartThree() ;
    void getVolumeBack(int,int) ;
    void showAgain() ;
};

#endif // MAINWIDGET_H
