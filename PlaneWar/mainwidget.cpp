#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMouseTracking(true);

    //放音乐
    c_player = new QMediaPlayer ;
    c_player->setMedia(QUrl::fromLocalFile("..\\music\\click.wav"));

    m_playerList = new QMediaPlaylist;
    m_playerList->addMedia(QUrl::fromLocalFile("..\\music\\song1.mp3")) ;
    m_playerList->addMedia(QUrl::fromLocalFile("..\\music\\song2.mp3")) ;
    m_playerList->addMedia(QUrl::fromLocalFile("..\\music\\song3.mp3")) ;
    m_playerList->addMedia(QUrl::fromLocalFile("..\\music\\song4.mp3")) ;
    m_playerList->setCurrentIndex(currentSong);
    m_playerList->setPlaybackMode(QMediaPlaylist::Loop);
    m_player = new QMediaPlayer ;
    m_player->setPlaylist(m_playerList);
    m_player->setVolume(this->musicVolume);
    m_player->play();

    //游戏开始按键
    b_start.setParent(this);//开始游戏
    b_start.setText("New Game");
    b_start.setFont(QFont("Segoe Script",30));
    b_start.setStyleSheet("QPushButton{background: transparent; color:#0099FF; }QPushButton:hover{color:#CCFFCC;}");
    b_start.move(350,180);

    b_store.setParent(this);//商店
    b_store.setText("Store");
    b_store.setFont(QFont("Segoe Script",30)); //Algerian
    b_store.setStyleSheet("QPushButton{background: transparent; color:#0099FF; }QPushButton:hover{color:#CCFFCC;}");
    b_store.move(410,250);

    b_setting.setParent(this); //设置
    b_setting.setText("Setting");
    b_setting.setFont(QFont("Segoe Script",30)); //Algerian
    b_setting.setStyleSheet("QPushButton{background: transparent; color:#0099FF; }QPushButton:hover{color:#CCFFCC;}");
    b_setting.move(390,320);

    b_help.setParent(this); //设置
    b_help.setText("Help");
    b_help.setFont(QFont("Segoe Script",30)); //Algerian
    b_help.setStyleSheet("QPushButton{background: transparent; color:#0099FF; }QPushButton:hover{color:#CCFFCC;}");
    b_help.move(410,390);

    b_quit.setParent(this);//退出按键
    b_quit.setText("Quit");
    b_quit.setFont(QFont("Segoe Script",30)); //Algerian
    b_quit.setStyleSheet("QPushButton{background: transparent; color:#0099FF; }QPushButton:hover{color:#CCFFCC;}");
    b_quit.move(410,460);

    partOne.setParent(this);//场景一
    partOne.setText("Sence One");
    partOne.setFont(QFont("Segoe Script",20)); //Algerian
    partOne.setStyleSheet("QPushButton{background: transparent; color:#9966FF; }QPushButton:hover{color:red;}");
    partOne.move(195,120);
    partOne.setMouseTracking(true);
    partOne.hide();
    connect(&partOne,SIGNAL(clicked(bool)),this,SLOT(pushPartOne())) ;

    partTwo.setParent(this);//场景二
    partTwo.setText("Sence Two");
    partTwo.setFont(QFont("Segoe Script",20)); //Algerian
    partTwo.setStyleSheet("QPushButton{background: transparent; color:#9966FF; }QPushButton:hover{color:red;}");
    partTwo.move(380,120);
    partTwo.setMouseTracking(true);
    partTwo.hide();
    connect(&partTwo,SIGNAL(clicked(bool)),this,SLOT(pushPartTwo())) ;

    partThree.setParent(this);//场景三
    partThree.setText("Sence Three");
    partThree.setFont(QFont("Segoe Script",20)); //Algerian
    partThree.setStyleSheet("QPushButton{background: transparent; color:#9966FF; }QPushButton:hover{color:red;}");
    partThree.move(565,120);
    partThree.setMouseTracking(true);
    partThree.hide();
    connect(&partThree,SIGNAL(clicked(bool)),this,SLOT(pushPartThree())) ;


    //不同按键发送不同信号
    myMapper = new QSignalMapper();
    connect(&b_start, SIGNAL(clicked()), myMapper, SLOT(map()));
    connect(&b_store, SIGNAL(clicked()), myMapper, SLOT(map()));
    connect(&b_setting, SIGNAL(clicked()), myMapper, SLOT(map()));
    connect(&b_help, SIGNAL(clicked()), myMapper, SLOT(map()));
    connect(&b_quit , SIGNAL(clicked()), this , SLOT(closeWindows()));
    myMapper->setMapping(&b_start, 1);
    myMapper->setMapping(&b_store, 2);
    myMapper->setMapping(&b_setting, 3);
    myMapper->setMapping(&b_help, 4);
    connect(myMapper, SIGNAL(mapped(int)), this, SLOT(change(int)));
}
void MainWidget::change(int a){
    switch(a){
        case 1 :
            c_player->play();
//            w = new myWidget() ;
//            connect(this,SIGNAL(sendPlayer(Player)),w,SLOT(getPlayer(Player))) ;
//            emit sendPlayer(this->player);
//            w->setMouseTracking(true);
//            w->setCursor(Qt::BlankCursor);
//            w->resize(WIDTH,HEIGHT);
//            connect(w,SIGNAL(back(Player)),this,SLOT(reShow(Player)));
//            //w->move((QApplication::desktop()->width() - w->width())/2,0);
//            w->setGeometry((QApplication::desktop()->width() - w->width())/2,30,800,1000);
//            w->show();
//            this->hide();
            partOne.show();
            partTwo.show();
            partThree.show();
            break ;
        case 2:
            c_player->play();
            sw = new StoreWidget() ;
            connect(this,SIGNAL(sendPlayer(Player)),sw,SLOT(getPlayerMsg(Player))) ;
            connect(sw,SIGNAL(goBack(Player)),this,SLOT(reShow(Player))) ;
            emit sendPlayer(this->player);
            sw->resize(1000,800);
            sw->show();
            this->hide();
            break ;
        case 3:
            c_player->play();
            setw = new SettingWidget() ;
            connect(this,SIGNAL(sendVolume(int,int)),setw,SLOT(getVolume(int,int))) ;
            connect(setw,SIGNAL(sendVolumeBack(int,int)),this,SLOT(getVolumeBack(int,int))) ;
            emit sendVolume(this->musicVolume,this->soundVolume);
            setw->show();
            this->hide();
            break ;
        case 4:
            c_player->play();
            hw = new HelpWidget() ;
            connect(hw,SIGNAL(goBack()),this,SLOT(showAgain())) ;
            hw->show();
            this->hide();
            break ;
        default:
            break;
    }
}
void MainWidget::reShow(Player player){
    this->player = player ;
    money.setText(QString::number(player.money));
    maxScore.setText("MaxScore : " + QString::number(player.maxScore));
    //qDebug() << player.money << player.p1 << player.p2 << player.p3 << player.p4 << player.p5 ;
    this->show();
}
void MainWidget::paintEvent(QPaintEvent *){
    QPainter p(this) ;
    mainBk.load("..\\photo\\mainBk.png") ;
    moneyPic.load("..\\photo\\money.png") ;
    p.drawPixmap(QRect(QPoint(0,0),size()),mainBk);
    p.drawPixmap(QRect(QPoint(10,60),QSize(50,50)),moneyPic);
}
void MainWidget::getData(Player player){
    this->player = player ;

    welMsg.setParent(this);//欢迎信息
    welMsg.setText("Welcome To Plane War ! " + player.username);
    welMsg.setFont(QFont("Segoe Script",20)); //Algerian
    welMsg.setStyleSheet("QPushButton{background: transparent; color:#0000CC; }QPushButton:hover{color:red;}");
    welMsg.move(0,5);

    money.setParent(this);//钱
    money.setText(QString::number(player.money));
    money.setFont(QFont("Segoe Script",20)); //Algerian
    money.setStyleSheet("QPushButton{background: transparent; color:yellow; }QPushButton:hover{color:#FF6600;}");
    //money.move(60,55);
    money.setGeometry(0,60,300,50);

    maxScore.setParent(this);//最高分
    maxScore.setText("MaxScore : " + QString::number(player.maxScore));
    maxScore.setFont(QFont("Segoe Script",20)); //Algerian
    maxScore.setStyleSheet("QPushButton{background: transparent; color:#0000CC; }QPushButton:hover{color:red;}");
    //maxScore.move(720,5);
    maxScore.setGeometry(140,60,500,50);

    //qDebug() << player.username << player.money << player.maxScore << player.p1 << player.p2 ;
}
void MainWidget::closeWindows(){
    QSqlTableModel model ;
    model.setTable("tuser") ;
    model.select() ;
    int ret = model.rowCount() ;
    for(int i = 0 ; i < ret ; i++){
        QSqlRecord record = model.record(i) ;
        if(record.value("username").toString() == player.username){
            record.setValue("money",player.money);
            record.setValue("maxScore",player.maxScore);
            record.setValue("p1",player.p1);
            record.setValue("p2",player.p2);
            record.setValue("p3",player.p3);
            record.setValue("p4",player.p4);
            record.setValue("p5",player.p5);
            model.setRecord(i,record) ;
            model.submitAll() ;
        }
    }
    this->close() ;
}
void MainWidget::mouseMoveEvent(QMouseEvent * ev){
    if(partOne.frameGeometry().contains(ev->pos()) || partTwo.frameGeometry().contains(ev->pos()) || partThree.frameGeometry().contains(ev->pos())){
        flag = 1 ;
    }
    if(!(partOne.frameGeometry().contains(ev->pos()) || partTwo.frameGeometry().contains(ev->pos()) || partThree.frameGeometry().contains(ev->pos()))
            && flag){
        flag = 0 ;
        partOne.hide();
        partTwo.hide();
        partThree.hide();
    }
}
void MainWidget::pushPartOne(){
    c_player->play();
    w = new myWidget() ;
    connect(this,SIGNAL(sendPlayer(Player)),w,SLOT(getPlayer(Player))) ;
    emit sendPlayer(this->player);
    w->setMouseTracking(true);
    w->setCursor(Qt::BlankCursor);
    w->resize(WIDTH,HEIGHT);
    connect(w,SIGNAL(back(Player)),this,SLOT(reShow(Player)));
    //w->move((QApplication::desktop()->width() - w->width())/2,0);
    w->setGeometry((QApplication::desktop()->width() - w->width())/2,30,800,1000);
    w->show();
    this->hide();
}
void MainWidget::pushPartTwo(){
    c_player->play();
    ow = new oneWidget() ;
    connect(this,SIGNAL(sendPlayer(Player)),ow,SLOT(getPlayer(Player))) ;
    emit sendPlayer(this->player);
    ow->setMouseTracking(true);
    ow->setCursor(Qt::BlankCursor);
    ow->resize(WIDTH,HEIGHT);
    connect(ow,SIGNAL(back(Player)),this,SLOT(reShow(Player)));
    //w->move((QApplication::desktop()->width() - w->width())/2,0);
    ow->setGeometry((QApplication::desktop()->width() - ow->width())/2,30,800,1000);
    ow->show();
    this->hide();
}
void MainWidget::pushPartThree(){
    c_player->play();
    tw = new twoWidget() ;
    connect(this,SIGNAL(sendPlayer(Player)),tw,SLOT(getPlayer(Player))) ;
    emit sendPlayer(this->player);
    tw->setMouseTracking(true);
    tw->setCursor(Qt::BlankCursor);
    tw->resize(WIDTH,HEIGHT);
    connect(tw,SIGNAL(back(Player)),this,SLOT(reShow(Player)));
    //w->move((QApplication::desktop()->width() - w->width())/2,0);
    tw->setGeometry((QApplication::desktop()->width() - tw->width())/2,30,800,1000);
    tw->show();
    this->hide();
}
void MainWidget::getVolumeBack(int musicVolume, int soundVolume){
    this->musicVolume = musicVolume ;
    this->soundVolume = soundVolume ;
    m_player->setVolume(this->musicVolume);
    c_player->setVolume(this->soundVolume);
    //qDebug() << this->musicVolume << this->soundVolume ;
    this->show();
}
void MainWidget::keyPressEvent(QKeyEvent * ev){
    if(ev->key() == Qt::Key_Shift){
        currentSong = (currentSong+1)%(TOTALSONG+1) ;
        if(currentSong == 0){
            currentSong = 1 ;
        }
        //qDebug() << currentSong ;
        m_playerList->setCurrentIndex(currentSong);
        m_player->play();
    }
}
void MainWidget::showAgain(){
    this->show();
}
