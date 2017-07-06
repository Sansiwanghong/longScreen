#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup> //按钮分组类头文件
#include <QVector>
#include <QPixmap>
#include <QTextEdit>
#include "screen.h"
#include"inputdlg.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT



public:
    explicit Widget(QWidget *parent = 0);
    virtual void closeEvent(QCloseEvent* event);
    ~Widget();

private slots:
    void on_pushButton_openFile_clicked();

    void on_spinBox_s1_editingFinished();

    void on_spinBox_e1_editingFinished();

 //   void on_pushButton_sender_clicked();
    
    void changePicture();



    void on_spinBox_s2_editingFinished();

    void on_spinBox_e2_editingFinished();

    void on_spinBox_s2_2_editingFinished();

    void on_spinBox_e2_2_editingFinished();

    void on_pushButton_openFile_2_clicked();

    void on_spinBox_timer_editingFinished();

signals:
    //1.update Data
    void sendData(QPixmap *pix1);
    //2.update two Data
    void sendTwoData(QPixmap *pix2);
    //3.update region1 picture
    void updataPicture(int i);
    //3.update region2 picture
    void updataPicture2(int i);

private slots:
     //1.Get Index
     void getIndex(int Index);
     //2.GetText
     void GetText();
     //3.Change region Picture
     void changeRegionTwoPicture();
     //4.get Text to Image
     void getTextImage(QString &);

//Init Widet etc
     void on_pushButton_2_clicked();

protected:
   void  Init();
//Set　Class
private:
    //1. Region One
    QButtonGroup *clipNum;
    QTimer *m_Timer;
    QTimer *m_timerPaint;
    QVector<QPixmap*> pix_input1;
    QPixmap *pix1;
    QTextEdit *m_textEdit;
    QString m_Text;
    InputDlg *inputTxt1;

    //2.Region two
    QTimer *m_Timer2;
    QVector<QPixmap*> pix_input2;
    QPixmap *pix2;

    //3.public class
    Screen *Screen1;
public:
    //Region one
    int time_spin1;
    int pix_original_num;
    int count1;
    int index;


    //Region two
    int pix_original_num2;
    int count2;

    int s1,s2,s3;
    int e1,e2,e3;
private:
    Ui::Widget *ui;


};

#endif // WIDGET_H
