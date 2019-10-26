//*************************************************************************************************/
//   Projeto    : Controle de Trator via DS2
//   Arquivo    : LeituraDS2.h
//   Descriao  : Funaaes para realizar a leitura e interpretaaao do joystick DS2
//   Data       : 21/05/2019
//*************************************************************************************************/

#include "PS2X_lib.h"

PS2X joyPS2;                                //Joystick que controla os motores, leds e buzzer

#define btFarol PSB_PINK                    //O botao que sera utilizado para alternar o farol
#define btGiroFlex PSB_GREEN                //O botao que sera utilizado para ligar/desligar o giroflex
#define btBuzzer PSB_BLUE                   //O botao que sera utilizado para acionar o buzzer
#define btFarolSec PSB_RED                  //O botao que sera utilizado para alternar o farol secundario
#define btGravaVel PSB_L1                   //O botao utilizado para manter a velocidade atual do trator
#define btBracoCima PSB_PAD_UP              //O botao que levanta o braao do trator
#define btBracoBaixo PSB_PAD_DOWN           //O botao que desce o braao do trator
#define btAnteBracoCima PSB_R1              //O botao que levanta o ante-braao do trator
#define btAnteBracoBaixo PSB_R2             //O botao que desce o ante-braao do trator
#define analogFrenteTras PSS_LY             //O analagico utilizado para mover o trator para frente ou para tras
#define analogDirecao PSS_LX                //O analagico utilizado para a direaao do trator

//#define DS2_SERIAL_DEBUGGER                 //Descomente essa linha para ativar o debugger do controle via porta serial

void configuraJoy()                         //Realiza a configuraaao dos pinos joystick
{
    joyPS2.config_gamepad(13, 11, 10, 12, false, false);
    #ifdef DS2_SERIAL_DEBUGGER
        Serial.begin(9600);
    #endif
}

void leituraJoy()                           //Realiza a leitura das teclas do joystick
{
    joyPS2.read_gamepad();
}

int joyLeituraAnalog(int analog)          //Faz a leitura da posiaao do analagico de 0 a 255
{
    int value = joyPS2.Analog(analog);
    return(value);
}

bool joyLeituraBotao(int bt)                //Verifica se o botao esta pressionado
{
    bool status = joyPS2.ButtonPressed(bt);
    #ifdef DS2_SERIAL_DEBUGGER
        if(status)
        { 
            Serial.println(bt);
        }
    #endif
    return(status);
}

bool joyBtSolto(int bt)
{
    bool status = joyPS2.ButtonReleased(bt);
    #ifdef DS2_SERIAL_DEBUGGER
        if(status)
        { 
            Serial.println(bt);
        }
    #endif
    return(status);
}
