//*************************************************************************************************/
//   Projeto    : Controle de Trator via DS2
//   Arquivo    : DS2Trator.ino
//   Descri��o  : Configura��es e loop principal
//   Data       : 21/05/2019
//*************************************************************************************************/

#include "LeituraDS2.h"
#include "Sinalizacao.h"
#include "Motores.h"

void setup()
{
    // coloque aqui o seu c�digo de configura��o para ser executado uma vez:
    configuraJoy();                 //Realiza a configura��o dos pinos joystick
    configuraSinalizacao();         //Realiza a configura��o dos pinos dos leds e do buzzer
    configuraMotores();             //Realiza a configura��o dos servo motores, e dos pinos da ponte H
}

void loop()
{
    // coloque seu c�digo principal aqui, para executar repetidamente:
    leituraJoy();                   //Realiza a leitura das teclas do joystick
    controleLeds();                 //Liga e desliga os leds de acordo com os bot�es pressionados no controle
    controleBuzzer();               //Liga e desliga o buzzer de acordo com os bot�es pressionados no controle
    controleBracos();               //Movimenta os bra�os do trator de acordo com os comandos do joystick
    controleDirecao();              //Movimenta a dire��o do trator de acordo com os comandos do joystick
    controleMotor();                //Movimenta os motores das rodas do trator de acordo com os comandos do joystick
}