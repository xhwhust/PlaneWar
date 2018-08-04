#include "loginwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWidget mainWidget ;
//    mainWidget.resize(1000,700);

    QPixmap welcome("..\\photo\\splash.png");
    QSplashScreen splash(welcome);
    splash.resize(600,400);
    splash.show();
    Sleep(2000);
    splash.close() ;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE") ;         //连接数据库
    db.setDatabaseName("..\\userData\\data.db");
    if(db.open()){
        qDebug() << "open success" ;
    }else{
        qDebug() << "error open database :" + db.lastError().text() ;
    }
    db.exec("create table tuser (username varchar(30) , password varchar(30) , money int ,"
            "maxScore int , p1 int , p2 int , p3 int , p4 int , p5 int)") ; //设置表格式

    LoginWidget log ;
    log.resize(600,400);
    log.show();
    //mainWidget.show();
//    myWidget w;
//    w.setMouseTracking(true);
//    w.setCursor(Qt::BlankCursor);
//    w.resize(WIDTH,HEIGHT);
//    w.show();

    return a.exec();
}
