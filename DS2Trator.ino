//*************************************************************************************************/
//   Projeto    : Controle de Trator via DS2
//   Arquivo    : DS2Trator.ino
//   Descrição  : Configurações e loop principal
//   Data       : 21/05/2019
//*************************************************************************************************/

#include "LeituraDS2.h"
#include "Sinalizacao.h"
#include "Motores.h"

void setup()
{
    // coloque aqui o seu código de configuração para ser executado uma vez:
    configuraJoy();                 //Realiza a configuração dos pinos joystick
    configuraSinalizacao();         //Realiza a configuração dos pinos dos leds e do buzzer
    configuraMotores();             //Realiza a configuração dos servo motores, e dos pinos da ponte H
}

void loop()
{
    // coloque seu código principal aqui, para executar repetidamente:
    leituraJoy();                   //Realiza a leitura das teclas do joystick
    controleLeds();                 //Liga e desliga os leds de acordo com os botões pressionados no controle
    controleBuzzer();               //Liga e desliga o buzzer de acordo com os botões pressionados no controle
    controleBracos();               //Movimenta os braços do trator de acordo com os comandos do joystick
    controleDirecao();              //Movimenta a direção do trator de acordo com os comandos do joystick
    controleMotor();                //Movimenta os motores das rodas do trator de acordo com os comandos do joystick
}