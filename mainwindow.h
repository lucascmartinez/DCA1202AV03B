#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:
  void getData();
  void addip();
  void removeip();
  void setIP(QString _ipaddress);
//  void showMessage(QString msg);
//  void timerEvent(QTimerEvent *event);
private:
  Ui::MainWindow *ui;
  QString ipaddress;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
