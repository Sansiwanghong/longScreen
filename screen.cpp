#include "screen.h"
//#include"widget.h"
#include<QMouseEvent>
#include<QPainter>
#include <QtGui>
#include<QWidget>
#include<QDebug>
Screen::Screen(QWidget *parent) : QWidget(parent)
{

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->updateGeometry();
    move(0,0);

   // setGeometry(600,0,800,100);     	//设置窗体的大小
    setAutoFillBackground(true);    //对窗体背景色的设置
    setPalette(QPalette(Qt::black));
    pix=new QPixmap(size());      	//此QPixmap对象用来准备随时接收绘制的内容
    pix->fill(Qt::black);           //填充背景色为白色

}
Screen::~Screen()
{

}


void Screen::mousePressEvent(QMouseEvent *event)
{
 if(event->button() == Qt::LeftButton)
 {
      mouse_press = true;
      //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
      move_point = event->pos();;
 }
}
void Screen::mouseMoveEvent(QMouseEvent *event)
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = event->globalPos();

       //移动主窗体位置
       this->move(move_pos - move_point);
    }
}
void Screen::mouseReleaseEvent(QMouseEvent *)
{
    //设置鼠标为未被按下
    mouse_press = false;
}

void Screen::receiveData(QPixmap *pix1)//接收打印来自主窗口的图片
{
    update();
    pix2 = new QPixmap;
    pix2 = pix1;
    if(!(pix2->isNull()))
        qDebug()<<" I have received pix1/n";

    // pix=pix2;
}

void Screen::clipTimes(int num)
{
    if(pix2->isNull())
    {
        return;
    }
    cliptimes=num;

    int width;
    int height;
    int copy_w1;
    int copy_w2;
    int copy_h;

    QPixmap pix11;

    QPixmap pix21;
    QPixmap pix22;

    QPixmap pix31;
    QPixmap pix32;
    QPixmap pix33;

   // QPainter painter;
    setHidden(false);

    //*************必须先输入图片再选择屏幕折叠的份数，否则找不到切割的图片而导致copy函数无输入而导致程序崩溃【重要】***********
    if(cliptimes==0)
    {
        width=900;height=100;
        resize(width,height);

        copy_w1=width;
        copy_h=100;
        pix11=pix2->copy(0,0,copy_w1,copy_h);

        QPixmap *resultPix3=new QPixmap(size());
        QPainter painter(resultPix3);
        painter.drawPixmap(0,0,this->width(),this->height(),pix11);//直接绘制receiveData 接收到的pix2不行，我也不知道为什么。

        pix=resultPix3;
        update();
        //    delete resultPix3;
    }

    else if(cliptimes==1)
    {
        width=450;height=200;
        resize(width,height);
        //切割然后重新painter新的pixmap图片
        copy_w1=width;
        copy_h=100;
        pix21= pix2->copy(0,0,copy_w1,copy_h);
        pix22= pix2->copy(copy_w1,0,this->width(),copy_h);

        QPixmap *resultPix=new QPixmap(size());

        QPainter painter(resultPix);
        painter.drawPixmap(0,0,copy_w1,copy_h,pix21);
        painter.drawPixmap(0,copy_h,copy_w1,copy_h,pix22);

        pix=resultPix;
        update();
    }

    else
    {
        width=300;height=300;
        resize(width,height);

        copy_w1=width;
        copy_w2=width*2;
        copy_h=100;
        pix31= pix2->copy(0,0,copy_w1,copy_h);
        pix32= pix2->copy(copy_w1,0,this->width(),copy_h);
        pix33= pix2->copy(copy_w2,0,this->width(),copy_h);

        QPixmap *resultPix2=new QPixmap(size());

        QPainter painter(resultPix2);
        painter.drawPixmap(0,0,copy_w1,copy_h,pix31);
        painter.drawPixmap(0,copy_h,copy_w1,copy_h,pix32);
        painter.drawPixmap(0,copy_h*2,copy_w1,copy_h,pix33);

        pix = resultPix2;
        update();

    }
    qDebug()<<"w"<<width;
}

/**
* @brief: get region picture
* @Param: [in]QPixmap
* @return:
*/
void Screen::receiveRegionTwoData(QPixmap *pix2)
{
    update();
    m_PixTwo = new QPixmap;
    m_PixTwo = pix2;
    if(!(m_PixTwo->isNull()))
    {
        qDebug()<<" I have received pix1/n";
    }
}
/**
* @brief: Select screen size
* @Param: [in] num
* @return:
*/
void Screen::clipTimeTwo(int num)
{
    if(m_PixTwo != NULL)
    {
        return;
    }

    clipTwoTimes = num;

    int width;
    int height;
    int copy_w1;
    int copy_w2;
    int copy_h;

    QPixmap pix11;

    QPixmap pix21;
    QPixmap pix22;

    QPixmap pix31;
    QPixmap pix32;
    QPixmap pix33;

    setHidden(false);

    //*************必须先输入图片再选择屏幕折叠的份数，否则找不到切割的图片而导致copy函数无输入而导致程序崩溃【重要】***********
    if(cliptimes == 0)
    {
        width = 900;height = 100;
        resize(width,height);

        copy_w1=width;
        copy_h=100;
        pix11 = m_PixTwo->copy(0,0,copy_w1,copy_h);

        QPixmap *resultPix3=new QPixmap(size());
        QPainter painter(resultPix3);
        painter.drawPixmap(0,0,this->width(),this->height(),pix11);//直接绘制receiveData 接收到的pix2不行，我也不知道为什么。

        pix = resultPix3;
        update();
    }

    else if(cliptimes==1)
    {
        width=450;height=200;
        resize(width,height);
        //切割然后重新painter新的pixmap图片
        copy_w1=width;
        copy_h=100;
        pix21= m_PixTwo->copy(0,0,copy_w1,copy_h);
        pix22= m_PixTwo->copy(copy_w1,0,this->width(),copy_h);

        QPixmap *resultPix=new QPixmap(size());

        QPainter painter(resultPix);
        painter.drawPixmap(0,0,copy_w1,copy_h,pix21);
        painter.drawPixmap(0,copy_h,copy_w1,copy_h,pix22);

        pix = resultPix;
        update();
    }

    else
    {
        width=300;height=300;
        resize(width,height);

        copy_w1=width;
        copy_w2=width*2;
        copy_h=100;
        pix31= m_PixTwo->copy(0,0,copy_w1,copy_h);
        pix32= m_PixTwo->copy(copy_w1,0,this->width(),copy_h);
        pix33= m_PixTwo->copy(copy_w2,0,this->width(),copy_h);

        QPixmap *resultPix2=new QPixmap(size());

        QPainter painter(resultPix2);
        painter.drawPixmap(0,0,copy_w1,copy_h,pix31);
        painter.drawPixmap(0,copy_h,copy_w1,copy_h,pix32);
        painter.drawPixmap(0,copy_h*2,copy_w1,copy_h,pix33);

        pix = resultPix2;
        update();

    }
    qDebug()<<"w"<<width;

}

//绘图部分
void Screen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0),*pix);
}

