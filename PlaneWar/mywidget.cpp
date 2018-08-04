#include "mywidget.h"
#include "ui_mywidget.h"

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
    this->setMaximumSize(800,1000);
    this->setMinimumSize(800,1000);
    this->setAttribute(Qt::WA_DeleteOnClose,1);//关闭时删除数据
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//随机数种子

    bk1.load("..\\photo\\bk2.jpg") ;//加载背景图片
    moneyPic.load("..\\photo\\money.png") ;//钱
    pPic1.load("..\\photo\\plane1.png") ;//加载我方飞机图片
    _pPic1.load("..\\photo\\enemy1.png") ;//敌机1
    _pPic2.load("..\\photo\\enemy2.png") ;//敌机2
    _pPic3.load("..\\photo\\enemy3.png") ;
    _pPic4.load("..\\photo\\enemy4.png") ;
    _pPic5.load("..\\photo\\enemy5.png") ;//boss
    bPic1.load("..\\photo\\bullet1.png") ;//加载我方子弹图片
    bPic3.load("..\\photo\\bullet4.png") ;
    bPic4.load("..\\photo\\bullet5.png") ;
    bPic5.load("..\\photo\\bullet6.png") ;
    bPic6.load("..\\photo\\bullet7.png") ;
    _bPic1.load("..\\photo\\bullet2.png");//子弹1
    _bPic2.load("..\\photo\\bullet3.png");//子弹2
    hurt1.load("..\\photo\\hurt1.png") ;//受到伤害时的图片
    die1.load("..\\photo\\die1.png") ;//死亡时图片
    buff1.load("..\\photo\\buff1.png") ;//血包
    buff2.load("..\\photo\\buff2.png") ;//散弹
    buff3.load("..\\photo\\buff3.png") ;
    shield.load("..\\photo\\shield.png") ;//护盾
    bloodBar.load("..\\photo\\bloodBar.png") ;//血条
    smallBlood.load("..\\photo\\smallBlood.png") ;//血块
    //商店的飞机
    sp[0].load("..\\photo\\sp1.png") ;
    sp[1].load("..\\photo\\sp2.png") ;
    sp[2].load("..\\photo\\sp3.png") ;
    sp[3].load("..\\photo\\sp4.png") ;
    sp[4].load("..\\photo\\sp5.png") ;

    plane = new Plane(WIDTH/2 - 40,HEIGHT*2/3,QSize(80,80),0,100,1,pPic1) ;//飞机初始化
    controlTime();//控制刷新时间
}

myWidget::~myWidget()
{
    delete ui;
}

void myWidget::paintEvent(QPaintEvent *){
    QPainter p(this) ;
    p.drawPixmap(QRect(QPoint(0,0),size()),bk1) ;

    if(plane->shield == 1){
        p.drawPixmap(QRect(QPoint(plane->x - 35,plane->y - 35),QSize(150,150)),shield);
    }
    p.drawPixmap(QRect(QPoint(plane->x,plane->y),plane->size),plane->pic);//画飞机
    if(plane->kill % 30 == 0 && flag[plane->kill] == 0){
        plane->skill ++ ;
        flag[plane->kill] = 1 ;
    }
    //死亡判定
    if(plane->life <= 0){
        QMessageBox message(QMessageBox::NoIcon, "Tip", "You are died !", QMessageBox::Yes, NULL);
        if(message.exec() == QMessageBox::Yes)
        {
            if(plane->kill > player.maxScore){
                player.maxScore = plane->kill ;
            }
            player.money += plane->wealth ;
            emit back(this->player);
            this->close() ;
        }
    }
    //更新血条
    p.drawPixmap(QRect(QPoint(0,0),QSize(375,70)),bloodBar);
    for(int i = 0 ; i < plane->life / 4 ; i++){
        p.drawPixmap(QRect(QPoint(i*15,26),QSize(15,23)),smallBlood);
    }
    p.setPen(Qt::red);
    QFont font1("Monospace",15,QFont::Bold,true) ;
    p.setFont(font1);
    p.drawText(QRect(QPoint(380,25),QSize(80,50)),"life:" + QString::number(plane->life));
    p.drawText(QRect(QPoint(470,25),QSize(80,50)),"kill:" + QString::number(plane->kill));
    p.drawText(QRect(QPoint(560,25),QSize(80,50)),"skill:" + QString::number(plane->skill));

    //胜利判定
    if(bossBulletFlag != 0){
        for(int i = 0 ; i < enemys.size() ; i++){
            if(enemys[i].type == 5){

                p.drawText(QRect(QPoint(650,25),QSize(80,50)),"boss:" + QString::number(enemys[i].life));

                if(enemys[i].life <= 0){
                    QMessageBox message(QMessageBox::NoIcon, "Tip", "You are win !", QMessageBox::Yes, NULL);
                    if(message.exec() == QMessageBox::Yes)
                    {
                        if(plane->kill > player.maxScore){
                            player.maxScore = plane->kill ;
                        }
                        player.money += plane->wealth ;
                        emit back(this->player);
                        this->close() ;
                    }
                }
            }
        }
    }

    if(bullets.size() > 0){ //画我方子弹
        for(int i = 0 ; i < bullets.size() ; i++){
            Bullet bullet = bullets.at(i) ;
            if(bullet.y >= 0-bullet.size.height()){ //判断是否出界
                if(enemys.size() > 0){
                    for(int j = 0 ; j < enemys.size() && bullet.life ; j++){
                        if(isCrash(enemys[j],bullet)){ //判断是否打中敌方飞机
                            enemys[j].life-- ;
                            bullet.life = 0 ;
                            if(enemys[j].life == 0){
                                if(qrand()%17 == 0){ //护盾
                                    Prop* prop = new Prop(enemys[j].x,enemys[j].y,3,buff3,QSize(50,50)) ;
                                    p.drawPixmap(QRect(QPoint(prop->x,prop->y),prop->size),prop->pic);
                                    props.append(*prop);
                                }else if(qrand()%21 == 0){//击毁飞机后产生道具血包的概率
                                    Prop* prop = new Prop(enemys[j].x,enemys[j].y,1,buff1,QSize(50,50)) ;
                                    p.drawPixmap(QRect(QPoint(prop->x,prop->y),prop->size),prop->pic);
                                    props.append(*prop);
                                }else if(qrand()%25 == 0){//击毁飞机后产生道具散弹的概率
                                    Prop* prop = new Prop(enemys[j].x,enemys[j].y,2,buff2,QSize(50,50)) ;
                                    p.drawPixmap(QRect(QPoint(prop->x,prop->y),prop->size),prop->pic);
                                    props.append(*prop);
                                }else if(qrand()%11 == 0){//钱的概率
                                    Prop* prop = new Prop(enemys[j].x,enemys[j].y,4,moneyPic,QSize(50,50)) ;
                                    p.drawPixmap(QRect(QPoint(prop->x,prop->y),prop->size),prop->pic);
                                    props.append(*prop);
                                }
                                plane->kill ++ ;//杀敌数增加
                                p.drawPixmap(QRect(QPoint(enemys[j].x,enemys[j].y),enemys[j].size),die1);
                                if(enemys[j].type != 5){
                                    enemys.erase(enemys.begin()+j) ;
                                }
                            }else{
                                p.drawPixmap(QRect(QPoint(enemys[j].x,enemys[j].y),enemys[j].size),hurt1);
                            }
                        }
                    }
                    if(bullet.life == 1){
                        p.drawPixmap(QRect(QPoint(bullet.x,bullet.y),bullet.size),bullet.pic);
                    }else{
                        bullets.erase(bullets.begin()+i) ;
                    }
                }else{
                    p.drawPixmap(QRect(QPoint(bullet.x,bullet.y),bullet.size),bullet.pic);
                }
            }else{
                bullets.erase(bullets.begin()+i) ;
            }
        }
    }
    if(enemys.size() > 0){ //画敌方飞机
        for(int i = 0 ; i < enemys.size() ; i++){
            Enemy enemy = enemys.at(i) ;
            if(enemy.y > HEIGHT){  //判断是否出界
                enemys.erase(enemys.begin()+i) ;
            }else if(isCrash(*plane,enemy)){  //判断是否与我方飞机相撞
                if(enemy.type == 5){
                    plane->life -= 10 ;
                    enemys[i].life -= 3 ;
                    p.drawPixmap(QRect(QPoint(enemys[i].x,enemys[i].y),enemys[i].size),hurt1);
                }else{
                    if(enemy.type == 3){
                        plane->life -= 15 ;
                    }else{
                        plane->life -= 5 ;
                    }
                    plane->kill ++ ;
                    p.drawPixmap(QRect(QPoint(enemys[i].x,enemys[i].y),enemys[i].size),die1);
                    enemys.erase(enemys.begin()+i) ;
                }
            }else{
                p.drawPixmap(QRect(QPoint(enemy.x,enemy.y),enemy.size),enemy.pic);
                //p.drawRect(QRect(QPoint(enemy.x,enemy.y),enemy.size));
            }
        }
    }
    if(enemyBullets.size() > 0){  //画敌方子弹
        for(int i = 0 ; i < enemyBullets.size() ; i++){
            Bullet enemyBullet = enemyBullets.at(i) ;
            if(enemyBullet.x < 0 || enemyBullet.x > WIDTH || enemyBullet.y > HEIGHT){  //判断是否出界
                enemyBullets.erase(enemyBullets.begin()+i) ;
            }else if(isCrash(*plane,enemyBullet)){  //判断是否打中我方飞机
                if(plane->shield == 0){
                    plane->life -= 1 ;
                    p.drawPixmap(QRect(QPoint(enemyBullet.x,enemyBullet.y),plane->size),hurt1);
                }
                enemyBullets.erase(enemyBullets.begin()+i) ;
            }else{
                p.drawPixmap(QRect(QPoint(enemyBullet.x,enemyBullet.y),enemyBullet.size),enemyBullet.pic);
                //无法获取到生成该子弹的敌机的size，此处暂时用40，80，的数字代替数据
            }
        }
    }
    if(props.size() > 0){
        for(int i = 0 ; i < props.size() ; i++){
            if(isCrash(*plane,props[i])){
                if(props[i].type == 1){
                    plane->life += 5 ;
                    if(plane->life > 100){
                        plane->life = 100 ;
                    }
                }else if(props[i].type == 2){
                    plane->attack = 1 ;
                    bufftime2 = new QTimer(this) ;
                    bufftime2->setSingleShot(true);
                    connect(bufftime2,SIGNAL(timeout()),this,SLOT(changeAttack()));//获得buff加成
                    bufftime2->start(6000);//散弹时间
                }else if(props[i].type == 3){
                    plane->shield = 1 ;
                    bufftime3 = new QTimer(this) ;
                    bufftime3->setSingleShot(true);
                    connect(bufftime3,SIGNAL(timeout()),this,SLOT(changeShield()));
                    bufftime3->start(3000);//护盾时间
                }else if(props[i].type == 4){
                    plane->wealth += 50 ;
                }
                props.erase(props.begin()+i) ;
            }else{
                p.drawPixmap(QRect(QPoint(props[i].x,props[i].y),props[i].size),props[i].pic);
            }
        }
    }
}
void myWidget::mouseMoveEvent(QMouseEvent * ev){  //鼠标即飞机移动坐标获取
    plane->x = ev->pos().rx() ;
    plane->y = ev->pos().ry() ;
    if(plane->x >= WIDTH - plane->size.rwidth()){
        plane->x = WIDTH - plane->size.rwidth() ;
    }
    if(plane->y >= HEIGHT - plane->size.rheight()){
        plane->y = HEIGHT - plane->size.rheight() ;
    }
    update();
}
void myWidget::mousePressEvent(QMouseEvent * ev){  //鼠标单击射击
    if(ev->button() == Qt::LeftButton){
        if(plane->attack == 0){
            if(whichPlane == 0){
                Bullet* bullet = new Bullet(plane->x,plane->y,QSize(10,40),1,1,2,bPic1,0,-6) ;
                Bullet* bullet2 = new Bullet(plane->x + plane->size.rwidth() ,plane->y,QSize(10,40),-1,1,2,bPic1,0,-6) ;
                bullets.append(*bullet);
                bullets.append(*bullet2);
                update();
            }else if(whichPlane == 1){
                Bullet* bullet = new Bullet(plane->x + plane->size.rwidth()/2 - 5,plane->y,QSize(10,40),6,1,1,bPic1,0,-6) ;
                Bullet bullet2 = *bullet ;
                bullet2.x = bullet2.x - 7 ;
                bullet->x = bullet->x + 7 ;
                bullets.append(*bullet);
                bullets.append(bullet2);
                update();
            }else if(whichPlane == 2){
                Bullet* bullet = new Bullet(plane->x + plane->size.rwidth()/2 - 5,plane->y,QSize(10,40),6,1,1,bPic4,0,-7) ;
                Bullet bullet2 = *bullet ;
                bullet2.x = bullet2.x - 38 ;
                bullet->x = bullet->x + 38 ;
                bullet2.dx = 1 ;
                bullet->dx = -1 ;
                bullets.append(*bullet);
                bullets.append(bullet2);
                update();
            }else if(whichPlane == 3){
                Bullet* bullet = new Bullet(plane->x + plane->size.rwidth()/2 - 5,plane->y,QSize(10,40),6,1,1,bPic1,0,-15) ;
                bullets.append(*bullet);
                update();
//                Bullet* bullet = new Bullet(plane->x + plane->size.rwidth()/2 - 5,plane->y,QSize(10,40),6,1,1,bPic1,0,-6) ;
//                Bullet bullet2 = *bullet ;
//                Bullet bullet3 = *bullet ;
//                Bullet bullet4 = *bullet ;
//                bullet2.dx = -6 ; bullet2.dy = 0 ;
//                bullet3.dx = 6  ; bullet3.dy = 0 ;
//                bullet4.dy = 6 ;
//                bullets.append(*bullet);
//                bullets.append(bullet2);
//                bullets.append(bullet3);
//                bullets.append(bullet4);
                update();
            }else if(whichPlane == 4){
                if(planeFourAttackFlag % 2){
                    Bullet* bullet = new Bullet(plane->x + plane->size.rwidth()/2 - 15,plane->y,QSize(30,30),6,1,1,bPic6,0,-6) ;
                    Bullet bullet2 = *bullet ;
                    Bullet bullet3 = *bullet ;
                    Bullet bullet4 = *bullet ;
                    bullet2.dx = -6 ; bullet2.dy = 0 ;
                    bullet3.dx = 6  ; bullet3.dy = 0 ;
                    bullet4.dy = 6 ;
                    bullets.append(*bullet);
                    bullets.append(bullet2);
                    bullets.append(bullet3);
                    bullets.append(bullet4);
                    update();
                }else{
                    Bullet* bullet = new Bullet(plane->x + plane->size.rwidth()/2 - 15,plane->y,QSize(30,30),6,1,1,bPic6,-6,-6) ;
                    Bullet bullet2 = *bullet ;
                    Bullet bullet3 = *bullet ;
                    Bullet bullet4 = *bullet ;
                    bullet2.dx = 6  ;  bullet2.dy = 6 ;
                    bullet3.dx = 6  ;  bullet3.dy = -6 ;
                    bullet4.dx = -6 ;  bullet4.dy = 6 ;
                    bullets.append(*bullet);
                    bullets.append(bullet2);
                    bullets.append(bullet3);
                    bullets.append(bullet4);
                    update();
                }
            }else{
                Bullet* bullet = new Bullet(plane->x + plane->size.rwidth()/2 - 5,plane->y,QSize(10,40),6,1,1,bPic1,0,-6) ;
                bullets.append(*bullet);
                update();
            }
        }else if(plane->attack == 1){
            Bullet* bullet = new Bullet(plane->x + plane->size.rwidth()/2 - 20,plane->y,QSize(40,40),6,1,1,bPic3,0,-6) ;
            Bullet bullet2 = *bullet ;
            Bullet bullet3 = *bullet ;
            bullet2.dx = -2 ;
            bullet3.dx = 2 ;
            bullets.append(*bullet);
            bullets.append(bullet2);
            bullets.append(bullet3);
            update();
        }
    }else{
        planeFourAttackFlag++ ;
    }
}
void myWidget::controlTime(){  //定时
    timer1 = new QTimer(this) ;
    connect(timer1,SIGNAL(timeout()),this,SLOT(move()));//移动，更新dx,dy
    timer1->start(intervalTime1);

    timer2 = new QTimer(this) ;
    connect(timer2,SIGNAL(timeout()),this,SLOT(createEnemy()));//创造普通飞机
    timer2->start(intervalTime2);

    timer3 = new QTimer(this) ;
    connect(timer3,SIGNAL(timeout()),this,SLOT(createBullet()));//创造子弹
    timer3->start(intervalTime3);

    timer4 = new QTimer(this) ;
    connect(timer4,SIGNAL(timeout()),this,SLOT(createEnemy()));//三发子弹的飞机
    timer4->start(intervalTime4);

    timer5 = new QTimer(this) ;
    connect(timer5,SIGNAL(timeout()),this,SLOT(createEnemy()));//散射敌机
    timer5->start(intervalTime5);

    timer6 = new QTimer(this) ;
    connect(timer6,SIGNAL(timeout()),this,SLOT(createEnemy()));//追踪自爆机
    timer6->start(intervalTime6);

    timer7 = new QTimer(this) ;
    timer7->setSingleShot(true);
    connect(timer7,SIGNAL(timeout()),this,SLOT(createBoss()));//产生boss
    timer7->start(intervalTime7);

    timer8 = new QTimer(this) ;
    connect(timer8,SIGNAL(timeout()),this,SLOT(createBullet_A()));//boss子弹A


    timer9 = new QTimer(this) ;
    connect(timer9,SIGNAL(timeout()),this,SLOT(createBullet_B()));//boss子弹B
}
void myWidget::move(){  //按照定时改变子弹，飞机坐标使其移动
    if(bullets.size() > 0){
        for(int i = 0 ; i < bullets.size() ; i++){
            if(bullets[i].type == 2){
                bullets[i].dx += bullets[i].speed ;
                if(bullets[i].dx == 10){
                    bullets[i].speed = - bullets[i].speed ;
                }
                if(bullets[i].dx == -10){
                    bullets[i].speed = - bullets[i].speed ;
                }
            }
            bullets[i].x += bullets[i].dx ;
            bullets[i].y += bullets[i].dy ;
        }
        update();
    }
    if(enemys.size() > 0){
        for(int i = 0 ; i < enemys.size() ; i++){
            if(enemys[i].type == 3 && enemys[i].x >= (WIDTH/2 - enemys[i].size.rwidth()/2)){
                enemys[i].x = WIDTH/2 - enemys[i].size.rwidth()/2 ;
                enemys[i].dx = 0 ;
            }
            if(enemys[i].type == 5 && enemys[i].y >= 80){
                enemys[i].y = 80 ;
                enemys[i].dy = 0 ;
            }
            if(enemys[i].type == 4){
                if(plane->x > enemys[i].x){
                    enemys[i].dx = 6 ;
                }else if(plane->x < enemys[i].x){
                    enemys[i].dx = -6 ;
                }else{
                    enemys[i].dx = 0 ;
                }
                if(plane->y > enemys[i].y){
                    enemys[i].dy = 18 ;
                }else if(plane->y < enemys[i].y){
                    enemys[i].dy = -18 ;
                }else{
                    enemys[i].dy = 0 ;
                }
            }
            enemys[i].x += enemys[i].dx ;
            enemys[i].y += enemys[i].dy ;
        }
        update();
    }
    if(enemyBullets.size() > 0){
        for(int i = 0 ; i < enemyBullets.size() ; i++){
            enemyBullets[i].x += enemyBullets[i].dx ;
            enemyBullets[i].y += enemyBullets[i].dy ;
        }
        update();
    }
}
void myWidget::createEnemy(){  //按照时间生成敌机，根据信号发送者的不同创造不同敌机
    if((QTimer*)sender() == timer2){
        Enemy* enemy = new Enemy(qrand()%(WIDTH-80),70,QSize(80,80),0,3,1,_pPic1,0,2) ;
        if(enemys.size() > 0){
            for(int i = 0 ; i < enemys.size() ; i++){
                if(isCrash(*enemy,enemys[i])){
                    i = -1 ;
                    enemy->x = qrand()%(WIDTH-80) ;
                }
            }
        }
        enemys.append(*enemy);
        update();
    }else if((QTimer*)sender() == timer4){
        Enemy* enemy = new Enemy(qrand()%(WIDTH-80),70,QSize(80,80),0,3,2,_pPic2,0,3) ;
        if(enemys.size() > 0){
            for(int i = 0 ; i < enemys.size() ; i++){
                if(isCrash(*enemy,enemys[i])){
                    i = -1 ;
                    enemy->x = qrand()%(WIDTH-80) ;
                }
            }
        }
        enemys.append(*enemy);
        update();
    }else if((QTimer*)sender() == timer5){
        Enemy* enemy = new Enemy(-80,WIDTH/2,QSize(80,80),0,20,3,_pPic3,6,0) ;
        enemys.append(*enemy);
        update();
    }else if((QTimer*)sender() == timer6){
        Enemy* enemy = new Enemy(qrand()%(WIDTH-80),-800,QSize(80,80),0,2,4,_pPic4,0,0) ;
        enemys.append(*enemy);
        update();
    }
}
void myWidget::createBullet(){  //创造敌方子弹
    if(enemys.size() > 0){
        for(int i = 0 ; i < enemys.size() ; i++){
            Enemy enemy = enemys.at(i) ;
            if(enemy.type == 1){  //根据飞机类型不同创造不同的子弹
                Bullet* bullet = new Bullet(enemy.x + enemy.size.rwidth()/2 - 5,enemy.y + enemy.size.rheight(),QSize(10,40),0,1,1,_bPic1,0,7) ;
                enemyBullets.append(*bullet);
            }else if(enemy.type == 2){
                Bullet* bullet = new Bullet(enemy.x + enemy.size.rwidth()/2 - 20,enemy.y + enemy.size.rheight(),QSize(40,40),0,1,2,_bPic2,0,6) ;
                Bullet bullet2 = *bullet ;
                Bullet bullet3 = *bullet ;
                bullet2.dx = -2 ;
                bullet3.dx = 2 ;
                enemyBullets.append(*bullet);
                enemyBullets.append(bullet2);
                enemyBullets.append(bullet3);
            }else if(enemy.type == 3){
                Bullet* bullet = new Bullet(enemy.x + enemy.size.rwidth()/2 - 20,enemy.y + enemy.size.rheight()/2 - 20,QSize(40,40),0,1,3,bPic4,0,6) ;//下
                Bullet bullet2 = *bullet ;   Bullet bullet3 = *bullet ;
                Bullet bullet4 = *bullet ;   Bullet bullet5 = *bullet ;
                Bullet bullet6 = *bullet ;   Bullet bullet7 = *bullet ;
                Bullet bullet8 = *bullet ;   Bullet bullet9 = *bullet ;
                Bullet bullet10 = *bullet ;  Bullet bullet11 = *bullet ;
                Bullet bullet12 = *bullet ;
                bullet2.dy = -6 ;//上
                bullet3.dx = -6 ;   bullet3.dy = 0 ;//左
                bullet4.dx = 6  ;   bullet4.dy = 0 ;//右
                bullet5.dx = -4 ;   bullet5.dy = 4 ;
                bullet6.dx = 4 ;    bullet6.dy = 4 ;
                bullet7.dx = -4 ;   bullet7.dy = -4 ;
                bullet8.dx = 4 ;    bullet8.dy = -4 ;
                bullet9.dx = -1 ;   bullet9.dy = 5 ;
                bullet10.dx = 1 ;    bullet10.dy = 5 ;
                bullet11.dx = -1 ;   bullet11.dy = -5 ;
                bullet12.dx = 1 ;    bullet12.dy = -5 ;
                enemyBullets.append(*bullet);
                enemyBullets.append(bullet2);
                enemyBullets.append(bullet3);
                enemyBullets.append(bullet4);
                enemyBullets.append(bullet5);
                enemyBullets.append(bullet6);
                enemyBullets.append(bullet7);
                enemyBullets.append(bullet8);
                enemyBullets.append(bullet9);
                enemyBullets.append(bullet10);
                enemyBullets.append(bullet11);
                enemyBullets.append(bullet12);
            }else if(enemy.type == 4){
                Bullet* bullet = new Bullet(enemy.x,enemy.y,QSize(40,40),0,1,4,bPic3,0,10) ;//下
                Bullet bullet2 = *bullet ;   Bullet bullet3 = *bullet ;
                Bullet bullet4 = *bullet ;   Bullet bullet5 = *bullet ;
                bullet2.x = bullet->x + 20 ;
                bullet4.x = bullet->x + 20 ;
                bullet3.y = bullet->y + 20 ;
                bullet4.y = bullet->y + 20 ;
                bullet5.x = bullet->x + 10 ;
                bullet5.y = bullet->y + 10 ;
                enemyBullets.append(*bullet);
                enemyBullets.append(bullet2);
                enemyBullets.append(bullet3);
                enemyBullets.append(bullet4);
                enemyBullets.append(bullet5);
            }
        }
    }
}
bool myWidget::isCrash(Flyer a, Flyer b){  //碰撞算法
    if(QRect(QPoint(a.x,a.y),a.size).contains(QPoint(b.x,b.y)) ||
       QRect(QPoint(a.x,a.y),a.size).contains(QPoint(b.x + b.size.rwidth(),b.y)) ||
       QRect(QPoint(a.x,a.y),a.size).contains(QPoint(b.x,b.y + b.size.rheight())) ||
       QRect(QPoint(a.x,a.y),a.size).contains(QPoint(b.x + b.size.rwidth(),b.y + b.size.rheight()))){
        return true ;
    }
    return false ;
}
void myWidget::changeAttack(){
    plane->attack = 0 ;
}
void myWidget::changeShield(){
    plane->shield = 0 ;
}
void myWidget::keyPressEvent(QKeyEvent * ev){
    if(ev->key() == Qt::Key_Space){
        if(plane->skill >= 1){
            plane->skill -- ;
            if(enemys.size() > 0){
                for(int i = 0 ; i < enemys.size() ; i++){
                    if(enemys[i].type != 5){
                        enemys.erase(enemys.begin()+i) ;
                        i-- ;
                    }else{
                        enemys[i].life -= 10 ;
                    }
                }
                update();
            }
            if(enemyBullets.size() > 0){
                for(int i = 0 ; i < enemyBullets.size() ; i++){
                    enemyBullets.erase(enemyBullets.begin()+i) ;
                    i-- ;
                }
                update();
            }
        }
    }
}
void myWidget::closeEvent(QCloseEvent *){
    if(plane->kill > player.maxScore){
        player.maxScore = plane->kill ;
    }
    player.money += plane->wealth ;
    emit back(this->player);
}
void myWidget::createBoss(){
    timer5->stop();
    timer6->stop();
    intervalTime2 = 2500 ; //普通飞机
    intervalTime4 = 3000 ; //三发子弹
    intervalTime3 = 3000 ; //生成子弹
    timer8->start(intervalTime8) ;//开始生成子弹A
    timer9->start(intervalTime9); //子弹B
    Enemy* enemy = new Enemy(WIDTH/2 - 200,-200,QSize(400,200),0,100,5,_pPic5,0,4) ;
    enemys.append(*enemy);
    update();
}
void myWidget::createBullet_A(){
    bossBulletFlag++ ;
    if(bossBulletFlag%2 == 0){
        Bullet* bullet = new Bullet(380,230,QSize(40,40),0,1,4,bPic5,0,7) ;
        Bullet bullet2 = *bullet ;   Bullet bullet3 = *bullet ;
        Bullet bullet4 = *bullet ;   Bullet bullet5 = *bullet ;
        Bullet bullet6 = *bullet ;   Bullet bullet7 = *bullet ;
        Bullet bullet8 = *bullet ;   Bullet bullet9 = *bullet ;
        bullet2.dx = 1 ;    bullet2.dy = 7 ;
        bullet3.dx = -1 ;   bullet3.dy = 7 ;
        bullet4.dx = 2  ;   bullet4.dy = 6 ;
        bullet5.dx = -2 ;   bullet5.dy = 6 ;
        bullet6.dx = 3 ;    bullet6.dy = 5 ;
        bullet7.dx = -3 ;   bullet7.dy = 5 ;
        bullet8.dx = 4 ;    bullet8.dy = 4 ;
        bullet9.dx = -4 ;   bullet9.dy = 4 ;
        enemyBullets.append(*bullet);
        enemyBullets.append(bullet2);
        enemyBullets.append(bullet3);
        enemyBullets.append(bullet4);
        enemyBullets.append(bullet5);
        enemyBullets.append(bullet6);
        enemyBullets.append(bullet7);
        enemyBullets.append(bullet8);
        enemyBullets.append(bullet9);
        update();
    }else{
        Bullet* bullet = new Bullet(380,230,QSize(40,40),0,1,5,bPic5,0,23) ;
        Bullet bullet2 = *bullet ;   Bullet bullet3 = *bullet ;
        Bullet bullet4 = *bullet ;   Bullet bullet5 = *bullet ;
        bullet2.x = 460 ;    bullet3.x = 540 ;
        bullet4.x = 300  ;   bullet5.x = 220 ;
        bullet->dx = (bullet->dy)*(plane->x - bullet->x)/(plane->y - bullet->y) ;
        bullet2.dx = (bullet2.dy)*(plane->x - bullet2.x)/(plane->y - bullet2.y) ;
        bullet3.dx = (bullet3.dy)*(plane->x - bullet3.x)/(plane->y - bullet3.y) ;
        bullet4.dx = (bullet4.dy)*(plane->x - bullet4.x)/(plane->y - bullet4.y) ;
        bullet5.dx = (bullet5.dy)*(plane->x - bullet5.x)/(plane->y - bullet5.y) ;
        enemyBullets.append(*bullet);
        enemyBullets.append(bullet2);
        enemyBullets.append(bullet3);
        enemyBullets.append(bullet4);
        enemyBullets.append(bullet5);
        update();
    }
}
void myWidget::createBullet_B(){
    Bullet* bullet = new Bullet(380,230,QSize(40,40),0,1,6,bPic5,0,7) ;
    Bullet bullet2 = *bullet ;   Bullet bullet3 = *bullet ;
    Bullet bullet4 = *bullet ;   Bullet bullet5 = *bullet ;
    Bullet bullet6 = *bullet ;   Bullet bullet7 = *bullet ;
    Bullet bullet8 = *bullet ;   Bullet bullet9 = *bullet ;
    bullet2.x = 460 ;    bullet3.x = 300 ;
    bullet4.x = 540  ;   bullet4.dy = 18  ;
    bullet4.dx = (bullet4.dy)*(plane->x - bullet4.x)/(plane->y - bullet4.y) ;
    bullet5.x = 220  ;   bullet5.dy = 18  ;
    bullet5.dx = (bullet5.dy)*(plane->x - bullet5.x)/(plane->y - bullet5.y) ;
    bullet6.x = 620 ;    bullet7.x = 140 ;
    bullet8.x = 700  ;   bullet8.dy = 14  ;
    bullet8.dx = (bullet8.dy)*(plane->x - bullet8.x)/(plane->y - bullet8.y) ;
    bullet9.x = 60  ;   bullet9.dy = 14  ;
    bullet9.dx = (bullet9.dy)*(plane->x - bullet9.x)/(plane->y - bullet9.y) ;
    enemyBullets.append(*bullet);
    enemyBullets.append(bullet2);
    enemyBullets.append(bullet3);
    enemyBullets.append(bullet4);
    enemyBullets.append(bullet5);
    enemyBullets.append(bullet6);
    enemyBullets.append(bullet7);
    enemyBullets.append(bullet8);
    enemyBullets.append(bullet9);
    update();
}
void myWidget::getPlayer(Player player){
    this->player = player ;
    spFlag[0] = player.p1 ;
    spFlag[1] = player.p2 ;
    spFlag[2] = player.p3 ;
    spFlag[3] = player.p4 ;
    spFlag[4] = player.p5 ;
    for(int i = 0 ; i < PLANENUM ; i++){
        if(spFlag[i] == 2){
            plane->pic = sp[i] ;
            whichPlane = i ;
        }
    }
    //qDebug() << player.username << player.money << player.maxScore ;
}
