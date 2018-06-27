/** @brief Esta é uma classe criada junto a uma interface gráfica do Qt para receber dados de um servidor e criar um gráfico com os valores recebidos. Ela é herdeira de QMainWindow.
 */

#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>

class Plotter : public QWidget
{
  Q_OBJECT
private:
  /** @param Dá uma identidade ao timer, permitindo que ele seja resetado.
      @param Determina a frequência de ativação do timer*/
  int timerctrl, speed;
  /** @param Determina a posição das matrizes utilizadas para desenhar o gráfico. */
  int timer;
  /** @param Armazena as coordenadas Y, representando os dados emitidos pelo servidor.
      @param Armazena as coordenadas X, representando o tempo dos dados emitidos pelo servidor*/
  int storagea[1000],time[1000];
  /** @param Armazena o endereço de IP ao qual se deseja se conectar.*/
  QString ipaddress;
  /** @param Determina o socket de conexão utilizado.*/
  QTcpSocket *socket;
public:
  explicit Plotter(QWidget *parent = nullptr);
  /** @brief É usada para criar o gráfico*/
  void paintEvent(QPaintEvent *event);
//  void setCorDeFundo(int r, int g, int b);
  /** @brief É usada para ativar a coleta dos dados e criação do gráfico.*/
  void timerEvent(QTimerEvent *event);
signals:

public slots:
  /** @brief Encerra o Timer.*/
  void stopData();
  /** @brief Altera a velocidade de atualização do comando 'get' */
  void changeTiming(int _speed);
  /** @brief Ativa o Timer*/
  void getDataB();
  /** @brief Altera o endereço de IP de acordo com o que foi escrito na caixa de texto. */
  void setIP(QString _ipaddress);
  /** @brief Inicia a conexão com o IP designado. */
  void tcpConnect();
  /** @brief Encerra a conexão com o IP designado. */
  void tcpDisconnect();
};

#endif // PLOTTER_H
