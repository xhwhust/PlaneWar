#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QPainter>
#include <QCloseEvent>
#include <QSlider>
#include <QPixmap>
#include <QDebug>

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent*);
    QToolButton btn1;
    QToolButton btn2;
    QSlider slider1;
    QSlider slider2;
    QPixmap settingBk;
    int musicVolume  = 100;
    int soundVolume  = 100;

signals:
    void sendVolumeBack(int,int) ;
public slots:
    void getVolume(int,int) ;
};

#endif // SETTINGWIDGET_H
