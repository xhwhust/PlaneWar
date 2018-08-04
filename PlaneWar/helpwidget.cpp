#include "helpwidget.h"
#include<QPainter>
HelpWidget::HelpWidget(QWidget *parent)
    : QWidget(parent)
{
 helpBk.load("..\\photo\\help2.png");

 this->setMaximumSize(1100,700);
   this->setMinimumSize(1100,700);
m_Tip0.setParent(this);
 m_Tip1.setParent(this);
 m_Tip2.setParent(this);
 m_Tip3.setParent(this);
 m_Tip4.setParent(this);
 m_Tip5.setParent(this);
 m_Tip6.setParent(this);
 m_Tip0.setText(tr("About:"));
 m_Tip1.setText(tr("1.The mouse controls the"
                   " movement \n of  the plane"));
 m_Tip2.setText(tr("2.Click the mouse button to shoot"));
 m_Tip3.setText(tr("3.Press space to use your plane's \nskill"));
 m_Tip4.setText(tr("4.Press shift to switch the background\n music"));
 m_Tip5.setText(tr("5.Be sure to live"));
 m_Tip6.setText(tr("6.Well,have fun"));

 m_Us0.setParent(this);
 m_Us1.setParent(this);
 m_Us2.setParent(this);
 m_Us3.setParent(this);
 m_Us4.setParent(this);
 m_Us0.setText(tr("About Us:"));
m_Us1.setText(tr("This game is technically\n supported by Team ZHUO MI "));
m_Us2.setText(tr("Game Logic : Xin Huangwei"));
m_Us3.setText(tr("Scene Design : Lv Yi & Li Kejin"));
m_Us4.setText(tr("Ui Design : Luo Aojie & Wang Shuo"));



this->setStyleSheet(
     "QLabel{font-family:'Comic Sans MS';"
            "font-size:30px;"
            "background:transparent;"
            "color:rgb(255,165,0);}"
                         );
m_Tip0.setStyleSheet(
            "QLabel{font-family:'Comic Sans MS';"
                     "font-size:50px;"
                     "background:transparent;"
                     "color:rgb(255,255,255);}"
                );
m_Us0.setStyleSheet(
            "QLabel{font-family:'Comic Sans MS';"
                     "font-size:50px;"
                     "background:transparent;"
                     "color:rgb(255,255,255);}"
                );


 m_Hlt1 = new QHBoxLayout;
 m_Hlt1->addWidget(&m_Tip0);
 m_Hlt1->addStretch();
 m_Hlt1->addWidget(&m_Us0);
 m_Hlt1->addStretch();
 m_Vlt1 = new QVBoxLayout;
 m_Vlt1->addStretch();
 m_Vlt1->addStretch();
 m_Vlt1->addWidget(&m_Tip1);
 m_Vlt1->addStretch();
 m_Vlt1->addWidget(&m_Tip2);
 m_Vlt1->addStretch();
 m_Vlt1->addWidget(&m_Tip3);
 m_Vlt1->addStretch();
 m_Vlt1->addWidget(&m_Tip4);
 m_Vlt1->addStretch();
 m_Vlt1->addWidget(&m_Tip5);
 m_Vlt1->addStretch();
 m_Vlt1->addWidget(&m_Tip6);
 m_Vlt1->addStretch();
 m_Vlt1->addStretch();
 m_Vlt2 = new QVBoxLayout;
  m_Vlt2->addStretch();
 m_Vlt2->addStretch();
 m_Vlt2->addWidget(&m_Us1);
  m_Vlt2->addStretch();
 m_Vlt2->addWidget(&m_Us2);
  m_Vlt2->addStretch();
 m_Vlt2->addWidget(&m_Us3);
  m_Vlt2->addStretch();
 m_Vlt2->addWidget(&m_Us4);
  m_Vlt2->addStretch();
   m_Vlt2->addStretch();
 m_Hlt2 = new QHBoxLayout;
 m_Hlt2->addLayout(m_Vlt1);
 m_Hlt2->addStretch();
 m_Hlt2->addLayout(m_Vlt2);
m_Vlt3 = new QVBoxLayout;
m_Vlt3->addLayout(m_Hlt1);
m_Vlt3->addLayout(m_Hlt2);

 this->setLayout(m_Vlt3);

}

HelpWidget::~HelpWidget()
{

}
void HelpWidget::paintEvent(QPaintEvent*)
{

    QPainter p(this) ;
    p.drawPixmap(QRect(QPoint(0,0),size()),helpBk) ;

}
void HelpWidget::closeEvent(QCloseEvent *){
    emit goBack();
}
