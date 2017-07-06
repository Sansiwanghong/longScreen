#include<QFileDialog>
#include "widget.h"
#include<QTimer>
#include "ui_widget.h"
#include<QDebug>
#include<QPainter>
#include<QString>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Init();
}

Widget::~Widget()
{
    delete ui;

}

void Widget::on_spinBox_s1_editingFinished()
{
    s1=ui->spinBox_s1->text().toInt();
    qDebug()<<"s1="<<s1;
    if(!(s1<5000))
        s1=0;

}

void Widget::on_spinBox_e1_editingFinished()
{
    e1=ui->spinBox_e1->text().toInt();
    qDebug()<<"e1"<<e1;
    if(!(e1<5000))
        e1=300;

}

void Widget::on_spinBox_s2_editingFinished()
{
    s2=ui->spinBox_s2->text().toInt();
}

void Widget::on_spinBox_e2_editingFinished()
{
    e2=ui->spinBox_e2->text().toInt();
}

void Widget::on_spinBox_s2_2_editingFinished()
{
    s3=ui->spinBox_s2_2->text().toInt();
}

void Widget::on_spinBox_e2_2_editingFinished()
{
    e3=ui->spinBox_e2_2->text().toInt();
}
void Widget::on_spinBox_timer_editingFinished()//区域一的循环播放时间间隔
{
    time_spin1=ui->spinBox_timer->text().toInt();
}

void Widget::getIndex(int Index)
{
    index = Index;
}

void Widget::GetText()
{
    ui->textEdit->toPlainText();
}

//加载不定张数的图片实现循环播放
void Widget::on_pushButton_openFile_clicked()
{
    pix_input1.clear();
    //1.Load picture
    QStringList strFileNames;

    strFileNames = QFileDialog::getOpenFileNames(this, tr("Open a picture"),"./Picture",
                                                 "Images(*.bmp *.jpg *.jpeg *.png *.xpm);;All files(*)");

    pix_original_num = strFileNames.count();
    for(int i = 0; i<pix_original_num; i++)
    {
        pix_input1.push_back(new QPixmap(strFileNames[i]));
    }

    qDebug() << "picture_num" << pix_original_num;
    m_Timer->start(time_spin1);

    //2.setQTimer and set filename
    count1=0;
    QString text;
    for(int i=0; i< pix_original_num; i++)
    {
        text.append(i);
        text.append(strFileNames[i]);
        text.append("\n");
        ui->textEdit->setText(text);
    }
}


void Widget::on_pushButton_openFile_2_clicked()
{
    QStringList strFileNames2;
    strFileNames2 = QFileDialog::getOpenFileNames(this, tr("Open a picture"),"./Picture",
                                                  "Images(*.bmp *.jpg *.jpeg *.png *.xpm);;All files(*)");

    pix_original_num2 = strFileNames2.count();

    for(int i = 0; i< pix_original_num2; i++)
    {
        pix_input2.push_back(new QPixmap(strFileNames2[i]));
    }


    qDebug()<<"picture2_num"<<pix_original_num2;
    m_Timer2->start(888);

    //2.setQTimer and set filename
    count2=0;
    QString text;
    for(int i=0; i< pix_original_num2; i++)
    {
        text.append(strFileNames2[i]);
        text.append("\n");
        ui->textEdit_2->setText(text);
    }
}

void Widget::closeEvent(QCloseEvent *)
{
    Screen1->close();
    inputTxt1->close();

}


void Widget::Init()


{
    setWindowTitle("SansiLED");




    m_Timer=new QTimer(this);
    m_timerPaint=new QTimer(this);
 //   m_textEdit = new QTextEdit;
    index = 4;
    ui->textEdit->wordWrapMode();

    m_Timer2 = new QTimer(this);

    //初始化
    time_spin1 = 1000;
    pix_original_num = 0;
    pix_original_num2 = 0;

    Screen1=new Screen;
    clipNum=new QButtonGroup;     //屏幕分割按钮及槽函数连接
    clipNum->addButton(ui->radioButton_1x4,0);
    clipNum->addButton(ui->radioButton_2x2,1);
    clipNum->addButton(ui->radioButton_4x1,2);

    //Region One
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(changePicture()));
    connect(clipNum,SIGNAL(buttonClicked(int)),Screen1,SLOT(clipTimes(int)));

    connect(clipNum,SIGNAL(buttonClicked(int)),SLOT(getIndex(int)));

    connect(this,SIGNAL(updataPicture(int)),Screen1,SLOT(clipTimes(int)));

    connect(this,SIGNAL(updataPicture2(int)),Screen1,SLOT(clipTimeTwo(int)));

    //Region Two
    connect(clipNum,SIGNAL(buttonClicked(int)),Screen1,SLOT(clipTimeTwo(int)));
    connect(m_Timer2,SIGNAL(timeout()),this,SLOT(changeRegionTwoPicture()));

    //将pix1传递给Screen1对象
    connect(this,SIGNAL(sendData(QPixmap *)),Screen1,SLOT(receiveData(QPixmap *)));

    connect(this,SIGNAL(sendTwoData(QPixmap *)),Screen1,SLOT(receiveRegionTwoData(QPixmap *)));

    // get Text
 //   connect(m_textEdit,SIGNAL(textChanged()),SLOT(getTextImage()));
}

//***************循环播放*********
void Widget::changePicture()
{
    update();
    int Screen1Width = 900;
    int Screen1Height = 100;

    if(count1 >= pix_original_num)
    {
        count1=0;
    }

    QPixmap *p1=new QPixmap(Screen1Width,Screen1Height);
    p1->fill(Qt::black);
    QPainter painter(p1);
    if(!pix_input1.empty())
    {
        painter.drawPixmap(s1,0,e1-s1,Screen1Height,pix_input1[count1]->copy());//接收load进来的图片，传递给接口pix1，
    }

    qDebug()<<"count1_Value:-------------------------------"<<count1;
    pix1 = p1;
    emit sendData(pix1);
    if(index != 4)
    {
          emit updataPicture(index);
    }
    count1 = count1 + 1;
}

/**
* @brief: Loop Playback Region Picture
* @Param:
* @return:
*/
void Widget::changeRegionTwoPicture()
{
    update();
    int Screen1Width = 900;
    int Screen1Height = 100;

    if(count2 >= pix_original_num2)
    {
        count2=0;
    }

    QPixmap *p1=new QPixmap(Screen1Width,Screen1Height);
    p1->fill(Qt::black);
    QPainter painter(p1);
    if(!pix_input2.empty())
    {
        painter.drawPixmap(s2,0,e2-s2,Screen1Height,pix_input2[count2]->copy());//接收load进来的图片，传递给接口 pix1，
    }

    qDebug()<<"count1_Value:-------------------------------"<< count2;
    pix2 = p1;
    emit sendTwoData(pix2);

    if(index != 4)
    {
        emit updataPicture2(index);
    }
    count2 = count2 + 1;
}
/**
* @brief:add Text to　Ｉｍａｇｅ
* @Param:
* @return:
*/
void Widget::on_pushButton_2_clicked()
{

 /*   m_textEdit->resize(ui->textEdit->width(),ui->textEdit->height());
    m_textEdit->setVisible(false);
    m_textEdit->show();
 */
    inputTxt1=new InputDlg(this);
    connect(inputTxt1,SIGNAL(getText(QString&)),this,SLOT(getTextImage(QString&)));
    inputTxt1->show();

}
/**
* @brief: get Image Text
* @Param:
* @return:
*/
void Widget::getTextImage(QString &txt)
{
  // m_Text.clear();
  //  m_Text = m_textEdit->toPlainText();
    m_Text=txt;

    if(!m_Text.isEmpty())
    {
        QSize size(300,100);
        QImage image(size,QImage::Format_ARGB32);
        image.fill(qRgba(0,0,0,100));
        QPainter painter(&image);
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
        QPen pen = painter.pen();
        pen.setColor(Qt::green);
        QFont font = painter.font();
        font.setBold(true);
        font.setPixelSize(35);
        painter.setPen(pen);
        painter.setFont(font);
        painter.drawText(image.rect(),Qt::AlignCenter,m_Text);
        if(image.save("C:/Users/xid01419/Desktop/sansi/longScreen/textImage.png"))
        {
            m_Timer->stop();
            QString _imageName;
            _imageName.append("C:/Users/xid01419/Desktop/sansi/longScreen/textImage.png");

            qDebug() << "text" << m_Text;
            QPixmap *_pixmap = new QPixmap(_imageName);
            pix_input1.push_back(_pixmap);
            pix_original_num++;
        }
        m_Timer->start(time_spin1);
    }
}
/**
* @brief: Generate images
* @Param:
* @return:
*/
/*  void Widget::on_pushButton_sender_clicked()
{
    if(!m_Text.isEmpty())
    {
        QSize size(200,200);
        QImage image(size,QImage::Format_ARGB32);
        image.fill(qRgba(0,0,0,100));
        QPainter painter(&image);
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
        QPen pen = painter.pen();
        pen.setColor(Qt::red);
        QFont font = painter.font();
        font.setBold(true);
        font.setPixelSize(20);
        painter.setPen(pen);
        painter.setFont(font);
        painter.drawText(image.rect(),Qt::AlignCenter,m_Text);
        if(image.save("C:/Users/xid01419/Desktop/sansi/longScreen/textImage.png"))
        {
            m_Timer->stop();
            QString _imageName;
            _imageName.append("C:/Users/xid01419/Desktop/sansi/longScreen/textImage.png");

            qDebug() << "text" << m_Text;
            QPixmap *_pixmap = new QPixmap(_imageName);
            pix_input1.replace(0,_pixmap);
        }
        m_Timer->start(time_spin1);
    }
}
*/
