

#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QMouseEvent>
#include <cmath>
#include <QDebug>
#include <QStringList>

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{
  speed = 1000;
  ipaddress = "127.0.0.1";
  socket = new QTcpSocket(this);
  timerctrl = 0;
  killTimer(timerctrl);
  timer = 0;
}

void Plotter::timerEvent(QTimerEvent *event)
{
  repaint();
}

void Plotter::getDataB()
{
    killTimer(timerctrl);
    timerctrl = startTimer(speed);
}

void Plotter::stopData()
{
    killTimer(timerctrl);
}

void Plotter::changeTiming(int _speed)
{
    speed = 1000*_speed;
}

void Plotter::tcpConnect(){
  socket->connectToHost(ipaddress,1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
  //ui->listWidget->addItem(list);
}

void Plotter::tcpDisconnect()
{
    socket->disconnectFromHost();
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
    }
    else{
      qDebug() << "Disconnected";
    }

}

void Plotter::setIP(QString _ipaddress)
{
    ipaddress = _ipaddress;
}

void Plotter::paintEvent(QPaintEvent *event){
  QPainter painter(this);
  QBrush brush;
  QPen pen;

  // habilita o anti aliasing (atenua o
  // efeito de serrilhado nas figuras geometricas)
  painter.setRenderHint(QPainter::Antialiasing);

  // brush com a cor amarela com preenchimento
  // solido
  brush.setColor(QColor(25,25,25));
  brush.setStyle(Qt::SolidPattern);
  // informa ao painter qual o pincel atual
  painter.setBrush(brush);

  // pen com cor vermelha e dois pixels de largura
  pen.setColor(QColor(255,255,255));
  pen.setWidth(2);

  // informa ao painter qual o pen atual
  painter.setPen(pen);

  // desenha um retangulo tomando toda a area
  // do componente
  painter.drawRect(0,0,width(), height());
  pen.setWidth(1);
  pen.setColor(QColor(200,200,231));
  pen.setStyle(Qt::SolidLine);
  painter.setPen(pen);
  QString summon = "get ";
  summon.append(ipaddress);
  summon.append(" 5\r\n");

  QString str;
  QByteArray array;
  QStringList list;
  qint64 thetime;
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write("get 127.0.0.1 5\r\n");
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          thetime = str.toLongLong(&ok);
          str = list.at(1);
          qDebug() << thetime << ": " << str;
          time[timer] = timer;
          storagea[timer] = height() - (str.toInt())*height()/100;
          timer = timer +1;
          if (timer == width()) {
              timer = 0;
          }
          for (int i=0; i < timer-1; i++) {
                        painter.drawLine(time[i],storagea[i],time[i+1],storagea[i+1]);
        }
        }
      }
    }
  }

}







