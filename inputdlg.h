#ifndef INPUTDLG_H
#define INPUTDLG_H

#include <QDialog>
#include <QPushButton>
#include<QTextEdit>
#include <QGridLayout>

class InputDlg : public QDialog
{
    Q_OBJECT
public:
    explicit InputDlg(QWidget *parent = 0);
    ~InputDlg();

signals:
    getText(QString &);

public slots:
  void  sendText();

private:
    QGridLayout *inputLayout;
    QPushButton *inputBtn;
    QTextEdit   *textEdit;

};

#endif // INPUTDLG_H
