#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QList>
#include <QObject>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ipaddress = "127.0.0.1";
  ui->setupUi(this);
  connect(ui->pushButtonGet,
          SIGNAL(clicked(bool)),
          this,
          SLOT(getData()));
  connect(ui->pushButtonGet,SIGNAL(clicked(bool)),ui->plotter,SLOT(getDataB()));
  connect(ui->pushButtonStop,SIGNAL(clicked(bool)),ui->plotter,SLOT(stopData()));
  connect(ui->pushButtonConnect,SIGNAL(clicked(bool)),ui->plotter,SLOT(tcpConnect()));
  connect(ui->pushButtonConnect,SIGNAL(clicked(bool)),this,SLOT(addip()));
  connect(ui->pushButtonDisconnect,SIGNAL(clicked(bool)),ui->plotter,SLOT(tcpDisconnect()));
  connect(ui->pushButtonDisconnect,SIGNAL(clicked(bool)),ui->plotter,SLOT(removeip()));
  connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),ui->plotter,SLOT(changeTiming(int)));
  connect(ui->lineEdit,SIGNAL(textChanged(QString)),ui->plotter,SLOT(setIP(QString)));
  connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(setIP(QString)));
}

void MainWindow::addip(){
    ui->listWidget->addItem(ipaddress);
}

void MainWindow::removeip(){
}

void MainWindow::getData(){

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setIP(QString _ipaddress)
{
    ipaddress = _ipaddress;
}
