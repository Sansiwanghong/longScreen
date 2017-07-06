#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include<QMouseEvent>
#include<QPixmap>
#include <QResizeEvent>

class Screen : public QWidget
{
    Q_OBJECT
public:
     explicit Screen(QWidget *parent=0 );
     ~Screen();

     QPixmap *pix;
     void paintEvent(QPaintEvent *);

signals:

public slots:
     //1.屏幕尺寸选择
     void clipTimes(int num);
     //1.1.接收需要显示的图片
     void receiveData(QPixmap *pix1);

     //2.屏幕尺寸选择
     void clipTimeTwo(int num);
     //2.1 get region picture
     void receiveRegionTwoData(QPixmap *pix2);

private:
      int cliptimes;
      int clipTwoTimes;
private:
       QPoint move_point; //移动的距离
       bool mouse_press; //鼠标按下
       //鼠标按下事件
       void mousePressEvent(QMouseEvent *event);
      //鼠标释放事件
       void mouseReleaseEvent(QMouseEvent *event);
      //鼠标移动事件
       void mouseMoveEvent(QMouseEvent *event);
private:
       QPixmap *pix2;
       QPixmap *m_PixTwo;


};

#endif // SCREEN_H
