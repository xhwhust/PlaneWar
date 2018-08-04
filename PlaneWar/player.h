#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

class Player
{
public:
    Player();
    Player(QString,int,int,int,int,int,int,int) ;//用户名，钱，最高分，飞机1，2，3，4，5
    QString username ;
    int money ;
    int maxScore ;
    int p1 ;
    int p2 ;
    int p3 ;
    int p4 ;
    int p5 ;
};

#endif // PLAYER_H
