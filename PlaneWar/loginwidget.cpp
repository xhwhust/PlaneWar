#include "loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{
    bName.setParent(this);
    bName.setText("Name:");
    bName.setFont(QFont("Segoe Script",28)); //Monotype Corsiva Segoe Script
    bName.setStyleSheet("QPushButton{background: transparent; color:#FF9900; }QPushButton:hover{color:red;}");//#FF9900
    bName.move(40,60);

    name = new QLineEdit(this) ;
    name->setFrame(false);
    name->setStyleSheet("QLineEdit{ background-color: #CCCCFF; }QLineEdit:focus{background-color: #CCFFFF}");
    name->setGeometry(220,90,250,26);

    bPassWord.setParent(this);
    bPassWord.setText("Password:");
    bPassWord.setFont(QFont("Segoe Script",28)); //Algerian
    bPassWord.setStyleSheet("QPushButton{background: transparent; color:#FF9900; }QPushButton:hover{color:red;}");
    bPassWord.move(20,160);

    passWord = new QLineEdit(this) ;
    passWord->setFrame(false);
    passWord->setStyleSheet("QLineEdit{ background-color: #CCCCFF; }QLineEdit:focus{background-color: #CCFFFF}");
    passWord->setGeometry(290,190,250,26);
    passWord->setEchoMode(QLineEdit::Password);

    login.setParent(this);
    login.setText("Login");
    login.setFont(QFont("Monotype Corsiva",28)); //Algerian
    login.setStyleSheet("QPushButton{background: transparent; color:#6699FF; }QPushButton:hover{color:red;}");
    login.move(100,270);
    login.setShortcut(Qt::Key_Return);

    create.setParent(this);
    create.setText("Registe");
    create.setFont(QFont("Monotype Corsiva",28)); //Algerian
    create.setStyleSheet("QPushButton{background: transparent; color:#6699FF; }QPushButton:hover{color:red;}");
    create.move(290,270);

    QObject::connect(&login,SIGNAL(clicked()),this,SLOT(saveData())) ;
    QObject::connect(&create,SIGNAL(clicked()),this,SLOT(createAcount())) ;
}
void LoginWidget::paintEvent(QPaintEvent *){
    QPixmap pic;
    pic.load("..\\photo\\login.jpg") ;
    QPainter p(this) ;
    p.drawPixmap(QRect(QPoint(0,0),size()),pic);
}
void LoginWidget::saveData(){
    Player player ;
    QString rn ;
    QString rp  ;
    QString n ;
    QString p  ;
    int flag = 0 ;
    rn = name->text() ;//输入的数据
    rp = passWord->text() ;

    if(rn.size() > 0 && rp.size() > 0){
        model.setTable("tuser") ;
        model.select() ;
        int ret = model.rowCount() ;
        for(int i = 0 ; i < ret ; i++){
            QSqlRecord record = model.record(i) ;
            n = record.value("username").toString() ;
            p = record.value("password").toString() ;
            if(n == rn && p == rp){
                flag = 1 ;
                player.username = rn ;
                player.money = record.value("money").toInt() ;
                player.maxScore = record.value("maxScore").toInt() ;
                player.p1 = record.value("p1").toInt() ;
                player.p2 = record.value("p2").toInt() ;
                player.p3 = record.value("p3").toInt() ;
                player.p4 = record.value("p4").toInt() ;
                player.p5 = record.value("p5").toInt() ;
            }
        }
        if(flag){
            mainWidget = new MainWidget() ;
            connect(this,SIGNAL(sendData(Player)),mainWidget,SLOT(getData(Player))) ;
            emit sendData(player);
            mainWidget->resize(1000,700);
            mainWidget->show();
            this->close() ;
        }else{
            QMessageBox::warning(NULL, "Warning", "Username or passworld is wrong !",QMessageBox::Ok,QMessageBox::NoButton);
        }
    }else{
        QMessageBox::warning(NULL, "Warning", "Username or passworld should be null !",QMessageBox::Ok,QMessageBox::NoButton);
    }

}
void LoginWidget::createAcount(){
    QString rn ;
    QString rp  ;
    QString n ;
    QString p  ;
    int flag = 0 ;
    rn = name->text() ;
    rp = passWord->text() ;

    if(rn.size() > 0 && rp.size() > 0){
        model.setTable("tuser") ;
        model.select() ;
        int ret = model.rowCount() ;
        for(int i = 0 ; i < ret ; i++){
            QSqlRecord record = model.record(i) ;
            n = record.value("username").toString() ;
            if(n == rn){
                flag = 1 ;
            }
        }
        if(flag){
            QMessageBox::warning(NULL, "Warning", "The account is already exist !",QMessageBox::Ok,QMessageBox::NoButton);
        }else{
            QSqlRecord record = model.record() ;
            record.setValue("username",rn);
            record.setValue("password",rp);
            record.setValue("money",90000);
            record.setValue("maxScore",0);
            record.setValue("p1",0);
            record.setValue("p2",0);
            record.setValue("p3",0);
            record.setValue("p4",0);
            record.setValue("p5",0);
            model.insertRecord(-1,record) ;
            QMessageBox::about(NULL, "Information", "Register Successfully");
        }
    }else{
        QMessageBox::warning(NULL, "Warning", "Username or passworld should be null !",QMessageBox::Ok,QMessageBox::NoButton);
    }
}

