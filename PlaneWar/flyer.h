#ifndef FLYER_H
#define FLYER_H
#include <QSize>
#include <QPixmap>

class Flyer
{
public:
    Flyer() ;
    Flyer(int x, int y, QSize size, int speed, int life, int type, QPixmap pic);
    Flyer(const Flyer&) ;
    int x ;
    int y ;
    int dx ;
    int dy ;
    int speed ;
    int life ;
    int type ;
    QSize size ;
    QPixmap pic ;
};

class Plane : public Flyer
{
public:
    Plane(int x, int y, QSize size, int speed, int life, int type, QPixmap pic) ;
    int attack = 0 ;
    int shield = 0 ;
    int kill = 0 ;
    int skill = 0 ;
    int wealth = 0 ;
};

class Bullet : public Flyer
{
public:
    Bullet() ;
    Bullet(int x, int y, QSize size, int speed, int life, int type, QPixmap pic, int dx, int dy);
    Bullet(const Bullet&) ;
};

class Enemy : public Flyer
{
public:
    Enemy() ;
    Enemy(int x, int y, QSize size, int speed, int life, int type, QPixmap pic, int dx, int dy);
    Enemy(const Enemy&) ;
};

class Prop : public Flyer
{
public:
    Prop() ;
    Prop(int x , int y ,int type , QPixmap pic , QSize size) ;
};
#endif // FLYER_H
