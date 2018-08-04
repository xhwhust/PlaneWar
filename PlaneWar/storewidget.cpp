#include "storewidget.h"

StoreWidget::StoreWidget(QWidget *parent) : QWidget(parent)
{
    c_player = new QMediaPlayer ;
    c_player->setMedia(QUrl::fromLocalFile("..\\music\\click.wav"));

    bk.load("..\\photo\\storebk.jpg") ;
    money.load("..\\photo\\moneybag.png") ;
    sp[0].load("..\\photo\\sp1.png") ;
    sp[1].load("..\\photo\\sp2.png") ;
    sp[2].load("..\\photo\\sp3.png") ;
    sp[3].load("..\\photo\\sp4.png") ;
    sp[4].load("..\\photo\\sp5.png") ;
    showPlane = sp[0] ;

    price[0] = 3000 ; price[1] = 1800 ; price[2] = 2500 ; price[3] = 1000 ; price[4] = 3500 ;

    next.setParent(this);//开始游戏
    next.setText("Next");
    next.setFont(QFont("Segoe Script",30));
    next.setStyleSheet("QPushButton{background: transparent; color:#0099FF; }QPushButton:hover{color:#CCFFCC;}");
    next.move(700,500);
    connect(&next,SIGNAL(clicked(bool)),this,SLOT(nextPlane())) ;

    pre.setParent(this);//开始游戏
    pre.setText("Pre");
    pre.setFont(QFont("Segoe Script",30));
    pre.setStyleSheet("QPushButton{background: transparent; color:#0099FF; }QPushButton:hover{color:#CCFFCC;}");
    pre.move(200,500);
    connect(&pre,SIGNAL(clicked(bool)),this,SLOT(prePlane())) ;

    moneyButton.setParent(this);//开始游戏
    moneyButton.setText("");
    moneyButton.setFont(QFont("Segoe Script",30));
    moneyButton.setStyleSheet("QPushButton{background: transparent; color:yellow; }QPushButton:hover{color:#CCFFCC;}");
    //moneyButton.move(440,80);
    moneyButton.setGeometry(410,90,300,50);

    priceButton.setParent(this);//开始游戏
    priceButton.setText("");
    priceButton.setFont(QFont("Segoe Script",30));
    priceButton.setStyleSheet("QPushButton{background: transparent; color:yellow; }QPushButton:hover{color:#CCFFCC;}");
    //priceButton.move(430,600);
    priceButton.setGeometry(250,630,500,50);
    connect(&priceButton,SIGNAL(clicked(bool)),this,SLOT(buyPlane())) ;

    equip.setParent(this);//开始游戏
    equip.setText("");
    equip.setFont(QFont("Segoe Script",30));
    equip.setStyleSheet("QPushButton{background: transparent; color:yellow; }QPushButton:hover{color:#CCFFCC;}");
    //equip.move(700,300);
    equip.setGeometry(500,200,600,50);
    connect(&equip,SIGNAL(clicked(bool)),this,SLOT(equipPlane())) ;

}
void StoreWidget::getPlayerMsg(Player player){
    this->player = player ;
    flag[0] = player.p1 ;
    flag[1] = player.p2 ;
    flag[2] = player.p3 ;
    flag[3] = player.p4 ;
    flag[4] = player.p5 ;
}
void StoreWidget::closeEvent(QCloseEvent *){
    player.p1 = flag[0] ;
    player.p2 = flag[1] ;
    player.p3 = flag[2] ;
    player.p4 = flag[3] ;
    player.p5 = flag[4] ;
    emit goBack(this->player);
}
void StoreWidget::paintEvent(QPaintEvent *){
    QPainter p(this) ;
    p.drawPixmap(QRect(QPoint(0,0),size()),bk);
    p.drawPixmap(QRect(QPoint(300,200),QSize(400,400)),showPlane);
    p.drawPixmap(QRect(QPoint(330,40),QSize(150,150)),money);
    moneyButton.setText(QString::number(player.money));
    if(flag[presentShow] >= 1){
        priceButton.setText("Owned");
    }else{
        priceButton.setText("Price : " + QString::number(price[presentShow]));
    }
    if(flag[presentShow] == 2){
        equip.setText("Equipped");
    }else if(flag[presentShow] == 1){
        equip.setText("Equip");
    }else{
        equip.setText("");
    }
}
void StoreWidget::nextPlane(){
    c_player->play();
    presentShow = (presentShow+1)%5 ;
    showPlane = sp[presentShow] ;
    update();
}
void StoreWidget::prePlane(){
    c_player->play();
    presentShow = (presentShow-1+5)%5 ;
    showPlane = sp[presentShow] ;
    update();
}
void StoreWidget::buyPlane(){
    c_player->play();
    if(flag[presentShow] >= 1){
        QMessageBox::about(NULL, "Information", "You already buy it !");
    }else if(player.money < price[presentShow]){
        QMessageBox::warning(NULL, "Warning", "You don't have enough money !",QMessageBox::Ok,QMessageBox::NoButton);
    }else{
        flag[presentShow]++ ;
        player.money -= price[presentShow] ;
        QMessageBox::about(NULL, "Information", "Buy Successfully");
        update();
    }
}
void StoreWidget::equipPlane(){
    c_player->play();
    if(flag[presentShow] == 2){
        QMessageBox::about(NULL, "Information", "You already equip it !");
    }else if(flag[presentShow] == 1){
        for(int i = 0 ; i < PLANENUM ; i++){
            if(flag[i] == 2){
                flag[i] = 1 ;
            }
        }
        flag[presentShow] = 2 ;
        QMessageBox::about(NULL, "Information", "Equip Successfully");
        update();
    }
}
