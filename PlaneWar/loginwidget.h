#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLineEdit>
#include <QString>
#include <QPaintEvent>
#include <QMessageBox>
#include <QDataStream>
#include <QFile>
#include <QSplashScreen>
#include <windows.h>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "mainwidget.h"
#include <player.h>

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    MainWidget* mainWidget ;
    QPushButton bName ;
    QPushButton bPassWord ;
    QPushButton login ;
    QPushButton create ;
    QLineEdit* name ;
    QLineEdit* passWord ;
    QSqlTableModel model ;

signals:
    void sendData(Player) ;
public slots:
    void saveData() ;
    void createAcount() ;
};

#endif // LOGINWIDGET_H
