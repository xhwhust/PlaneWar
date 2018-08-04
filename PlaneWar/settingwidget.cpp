#include "settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent) : QWidget(parent)
{
                   settingBk.load("..\\photo\\settingbk.png");
                     this->setWindowTitle(tr("setting"));
                     this->setMaximumSize(600,450);
                     this->setMinimumSize(600,450);
                     this->setStyleSheet("QAbstractButton{font-family:'Comic Sans MS';font-size:35px;"
                                         "background:transparent;color:#FF9900;}"
                                          "QAbstractButton:hover{color:red;}"
                                         );

                      btn1.setParent(this);
                       btn1.move(120,120);
                        btn1.setText(tr("Music"));
                         btn1.show();
                         slider1.setParent(this);
                      slider1.setOrientation(Qt::Horizontal);
                     slider1.setStyleSheet(
                                 "QSlider::groove:horizontal {  "
                                           " border: 1px solid #bbb; "
                                           " background: white; "
                                           " height: 15px;  "
                                           " border-radius: 4px;"
                                          "  }"

                                           " QSlider::sub-page:horizontal { "
                                        "background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), "
                                        "stop:1 rgba(7,208,255, 255)); "
                                           " border: 1px solid #777;  "
                                           " height: 10px; "
                                          "  border-radius: 4px;"
                                          "  }  "

                                           " QSlider::add-page:horizontal {"
                                           " background: #fff;"
                                           " border: 1px solid #777; "
                                          "  height: 10px; "
                                            "border-radius: 4px;  "
                                           " } "

                                           " QSlider::handle:horizontal {"
                                            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,  "
                                                "stop:0 #eee, stop:1 #ccc); "
                                            "border: 1px solid #777;  "
                                           " width: 15px;  "
                                            "margin-top: -2px;"
                                            "margin-bottom: -2px; "
                                           " border-radius: 4px;"
                                            "}  "

                                            "QSlider::handle:horizontal:hover {"
                                            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
                                             "   stop:0 #fff, stop:1 #ddd);"
                                            "border: 1px solid #444;"
                                            "border-radius: 4px;"
                                            "}  "

                                            "QSlider::sub-page:horizontal:disabled { "
                                            "background: #bbb;  "
                                            "border-color: #999;"
                                            "}  "

                                            "QSlider::add-page:horizontal:disabled {"
                                           " background: #eee;  "
                                           " border-color: #999;"
                                            "}"

                                           "QSlider::handle:horizontal:disabled {  "
                                           " background: #eee;  "
                                            "border: 1px solid #aaa;"
                                           "border-radius: 4px;} "
                                 );
                      slider1.setRange(0,100);
                     slider1.setValue(this->musicVolume);
                      slider1.setMinimumSize(200,50);
                        slider1.move(280,125);
                        slider1.show();

                        connect(&slider1,&QSlider::valueChanged,
                               [=](){
                        this->musicVolume = slider1.value();
//                        qDebug()<<player.musicvolume;
                        }
                                );

                        btn2.setParent(this);
                          btn2.move(120,320);
                           btn2.setText(tr("Sound"));
                            btn2.show();
                            slider2.setParent(this);
                       slider2.setOrientation(Qt::Horizontal);
                        slider2.setStyleSheet(
                                    "QSlider::groove:horizontal {  "
                                              " border: 1px solid #bbb; "
                                              " background: white; "
                                              " height: 15px;  "
                                              " border-radius: 4px;"
                                             "  }"

                                              " QSlider::sub-page:horizontal { "
                                           "background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), "
                                           "stop:1 rgba(7,208,255, 255)); "
                                              " border: 1px solid #777;  "
                                              " height: 10px; "
                                             "  border-radius: 4px;"
                                             "  }  "

                                              " QSlider::add-page:horizontal {"
                                              " background: #fff;"
                                              " border: 1px solid #777; "
                                             "  height: 10px; "
                                               "border-radius: 4px;  "
                                              " } "

                                              " QSlider::handle:horizontal {"
                                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,  "
                                                   "stop:0 #eee, stop:1 #ccc); "
                                               "border: 1px solid #777;  "
                                              " width: 15px;  "
                                               "margin-top: -2px;"
                                               "margin-bottom: -2px; "
                                              " border-radius: 4px;"
                                               "}  "

                                               "QSlider::handle:horizontal:hover {"
                                               "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
                                                "   stop:0 #fff, stop:1 #ddd);"
                                               "border: 1px solid #444;"
                                               "border-radius: 4px;"
                                               "}  "

                                               "QSlider::sub-page:horizontal:disabled { "
                                               "background: #bbb;  "
                                               "border-color: #999;"
                                               "}  "

                                               "QSlider::add-page:horizontal:disabled {"
                                              " background: #eee;  "
                                              " border-color: #999;"
                                               "}"

                                              "QSlider::handle:horizontal:disabled {  "
                                              " background: #eee;  "
                                               "border: 1px solid #aaa;"
                                              "border-radius: 4px;} "
                                   );
                         slider2.setRange(0,100);
                          slider2.setValue(this->soundVolume);
                          slider2.setMinimumSize(200,50);
                           slider2.move(280,325);
                           connect(&slider2,&QSlider::valueChanged,
                                  [=](){
                           this->soundVolume = slider2.value();
//                           qDebug()<<player.soundvolume;
                           }
                                   );

}

void SettingWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this) ;
    p.drawPixmap(QRect(QPoint(0,0),size()),settingBk) ;
}
void SettingWidget:: closeEvent(QCloseEvent*)
{
    emit sendVolumeBack(this->musicVolume,this->soundVolume);
}
void SettingWidget::getVolume(int musicVolume, int soundVolume){
    this->musicVolume = musicVolume ;
    this->soundVolume = soundVolume ;
    slider1.setValue(this->musicVolume);
    slider2.setValue(this->soundVolume);
}
