#include "flyer.h"

Flyer::Flyer(){

}
Flyer::Flyer(int x, int y, QSize size, int speed, int life, int type, QPixmap pic)
{
    this->x = x ;
    this->y = y ;
    this->size = size ;
    this->speed = speed ;
    this->life = life ;
    this->type = type ;
    this->pic = pic ;
}
Flyer::Flyer(const Flyer & flyer){
    this->dx = flyer.dx ;
    this->dy = flyer.dy ;
    this->life = flyer.life ;
    this->pic = flyer.pic ;
    this->size = flyer.size ;
    this->speed = flyer.speed ;
    this->type = flyer.type ;
    this->x = flyer.x ;
    this->y = flyer.y ;
}
Plane::Plane(int x, int y, QSize size, int speed, int life, int type, QPixmap pic) : Flyer(x,y,size,speed,life,type,pic)
{

}

Bullet::Bullet(){

}
Bullet::Bullet(int x, int y, QSize size, int speed, int life, int type, QPixmap pic, int dx, int dy) : Flyer(x,y,size,speed,life,type,pic)
{
    this->dx = dx ;
    this->dy = dy ;
}

Bullet::Bullet(const Bullet &bullet)
{
    this->dx = bullet.dx ;
    this->dy = bullet.dy ;
    this->life = bullet.life ;
    this->pic = bullet.pic ;
    this->size = bullet.size ;
    this->speed = bullet.speed ;
    this->type = bullet.type ;
    this->x = bullet.x ;
    this->y = bullet.y ;
}
Enemy::Enemy(){

}
Enemy::Enemy(int x, int y, QSize size, int speed, int life, int type, QPixmap pic, int dx, int dy) : Flyer(x,y,size,speed,life,type,pic)
{
    this->dx = dx ;
    this->dy = dy ;
}
Enemy::Enemy(const Enemy & enemy){
    this->dx = enemy.dx ;
    this->dy = enemy.dy ;
    this->life = enemy.life ;
    this->pic = enemy.pic ;
    this->size = enemy.size ;
    this->speed = enemy.speed ;
    this->type = enemy.type ;
    this->x = enemy.x ;
    this->y = enemy.y ;
}
Prop::Prop(){

}
Prop::Prop(int x, int y, int type, QPixmap pic, QSize size){
    this->x = x ;
    this->y = y ;
    this->type = type ;
    this->pic = pic ;
    this->size = size ;
}
