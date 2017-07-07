#include "inputdlg.h"
#include <QInputDialog>

InputDlg::InputDlg(QWidget *parent) : QDialog(parent)
{
      setWindowTitle("输入文本");

     inputLayout=new QGridLayout(this);

     textEdit=new QTextEdit(this);
     inputBtn=new QPushButton(this);
     inputBtn->setText("上传文本");

     inputLayout->addWidget(textEdit,0,0);
     inputLayout->addWidget(inputBtn,1,0);

     connect(inputBtn,SIGNAL(clicked()),this,SLOT(sendText()));

}
InputDlg::~InputDlg()
{

}

void InputDlg::sendText()
{
    QString txt;
    txt=textEdit->toPlainText();
    emit getText(txt);
}
