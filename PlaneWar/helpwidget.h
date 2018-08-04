#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCloseEvent>




class HelpWidget : public QWidget
{
    Q_OBJECT

public:
    HelpWidget(QWidget *parent = 0);
    ~HelpWidget();
    void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent*);
    QPixmap helpBk;
    QHBoxLayout *m_Hlt1;
     QHBoxLayout *m_Hlt2;
    QVBoxLayout *m_Vlt1;
     QVBoxLayout *m_Vlt2;
       QVBoxLayout *m_Vlt3;
     QLabel m_Tip0;
    QLabel m_Tip1;
    QLabel m_Tip2;
    QLabel m_Tip3;
    QLabel m_Tip4;
    QLabel m_Tip5;
    QLabel m_Tip6;

    QLabel m_Us0;
    QLabel m_Us1;
    QLabel m_Us2;
    QLabel m_Us3;
    QLabel m_Us4;
signals:
    void goBack() ;
};

#endif // HELPWIDGET_H
