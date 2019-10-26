//*************************************************************************************************/
//   Projeto    : Controle de Trator via DS2
//   Arquivo    : AcionamentoMotores.h
//   Descricao  : Funcoes para controlar os acionamentos dos Servos e do Motor de tracao
//   Data       : 21/05/2019
//*************************************************************************************************/

#include "ServoControl.h"
#include "Pls.h"

#define pinoMotorVelocidade 3
#define pinoMotorFrente 7
#define pinoMotorTras 8
#define pinoServoDirecao 5
#define pinoServoAnteBraco 6
#define pinoServoBraco 9

//Configuracao do servo: (pino, velocidade, posicao man, posicao max)
ServoControl servoDirecao = ServoControl(pinoServoDirecao, 100, 60, 130);        //Servo que controla a direcao para onde o trator ira se locomover
ServoControl servoAnteBraco = ServoControl(pinoServoAnteBraco, 100, 20, 180);    //Servo que controla o movimento do ante-braao do trator
ServoControl servoBraco = ServoControl(pinoServoBraco, 100, 20, 180);            //Servo que controla o movimento do braao do trator

//ATENCAO: DEPURAR UM COMPONENTE DE CADA VEZ!!!
//#define PONTEH_SERIAL_DEBUGGER                                               //Descomente essa linha para ativar o debugger da ponte h via porta serial
//#define SERVO_DIR_SERIAL_DEBUGGER                                            //Descomente essa linha para ativar o debugger do servo da direcao via porta serial
//#define SERVO_BRACO_DEBUGGER                                                 //Descomente essa linha para ativar o debugger do servo do braao via porta serial
//#define SERVO_ANTEBRACO_DEBUGGER                                             //Descomente essa linha para ativar o debugger do servo da antebraao via porta serial

Pls servoBracoSobe;                                                           //Gerencia o acionamento do servo do bra�o
Pls servoBracoDesce;
Pls servoAnteBracoSobe;                                                       //Gerencia o acionamento do servo do ante-bra�o
Pls servoAnteBracoDesce;

void configuraMotores()                                                        //Realiza a configuracao dos servo motores, e dos pinos da ponte H
{
    servoDirecao.on();
    servoAnteBraco.on();
    servoBraco.on();
    pinMode(pinoMotorVelocidade, OUTPUT);
    pinMode(pinoMotorFrente, OUTPUT);
    pinMode(pinoMotorTras, OUTPUT);
    #if defined (PONTEH_SERIAL_DEBUGGER) || defined (SERVO_DIR_SERIAL_DEBUGGER) || defined (SERVO_BRACO_DEBUGGER) || defined (SERVO_ANTEBRACO_DEBUGGER)
        Serial.begin(9600);
    #endif
}

void acionaMotor(int velocidade)                                               //Aciona a ponte h para mover o motor de acordo com a velocidade definida
{
    velocidade = map(velocidade, 0, 255, -255, 255);
    bool frente = velocidade > 0;
    bool tras = velocidade < 0;
    int velAbsoluta = abs(velocidade);
    digitalWrite(pinoMotorFrente, frente);
    digitalWrite(pinoMotorTras, tras);
    if(velAbsoluta > 10)
    {
        analogWrite(pinoMotorVelocidade,velAbsoluta);
    }
    else
    {
        analogWrite(pinoMotorVelocidade,0);
    }
    #ifdef PONTEH_SERIAL_DEBUGGER
        Serial.print("frente = "); Serial.print(frente);
        Serial.print(" || tras = "); Serial.print(tras);
        Serial.println(" || velAbsoluta = "); Serial.print(velAbsoluta);
    #endif
}

void controleMotor()                                                           //Movimenta as rodas do trator de acordo com os comandos do joystick
{
    static int velocidadeMemorizada = 127;
    if(joyLeituraBotao(btGravaVel))
    {
        int vel = joyLeituraAnalog(analogFrenteTras);
        velocidadeMemorizada = vel > 120 and vel < 140 ? 127 : vel;
    }
    int joyFrenteTrasValue = joyLeituraAnalog(analogFrenteTras);
    if(velocidadeMemorizada == 127)
    {
        acionaMotor(joyFrenteTrasValue);
    }
    else
    {
        //acionaMotor(velocidadeMemorizada);
    }
}

void controleBracos()                                                          //Movimenta os braaos do trator de acordo com os comandos do joystick
{
    bool sobeAnteBraco = joyLeituraBotao(btAnteBracoCima);
    bool desceAnteBraco = joyLeituraBotao(btAnteBracoBaixo);
    bool sobeBraco = joyLeituraBotao(btBracoCima);
    bool desceBraco = joyLeituraBotao(btBracoBaixo);
    bool btSolto = joyBtSolto(btAnteBracoCima) || joyBtSolto(btAnteBracoBaixo) || joyBtSolto(btBracoCima) || joyBtSolto(btBracoBaixo);
    if(servoAnteBracoSobe.selo(sobeAnteBraco, btSolto))
    {
        servoAnteBraco.asyncMoveTo(servoAnteBraco.getMax());
    }
    if(servoAnteBracoDesce.selo(desceAnteBraco, btSolto))
    {
        servoAnteBraco.asyncMoveTo(servoAnteBraco.getMin());
    }
    if(servoBracoSobe.selo(sobeBraco, btSolto))
    {
        servoBraco.asyncMoveTo(servoBraco.getMax());
    }
    if(servoBracoDesce.selo(desceBraco, btSolto))
    {
        servoBraco.asyncMoveTo(servoBraco.getMin());
    }
    #ifdef SERVO_BRACO_DEBUGGER
        Serial.println(servoBraco.getPos());
    #endif
    #ifdef SERVO_ANTEBRACO_DEBUGGER
        Serial.print(servoAnteBraco.getPos());
    #endif
}

void controleDirecao()                                                         //Movimenta a direcao do trator de acordo com os comandos do joystick
{
    int analogValue = joyLeituraAnalog(analogDirecao);
    int posDirecao = map(analogValue, 0, 255, 0, 180);
    servoDirecao.asyncMoveTo(posDirecao);
    #ifdef SERVO_DIR_SERIAL_DEBUGGER
        Serial.println(servoDirecao.getPos());
    #endif
}
