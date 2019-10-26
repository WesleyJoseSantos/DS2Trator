//*************************************************************************************************/
//   Projeto    : Controle de Trator via DS2
//   Arquivo    : Sinalizacao.h
//   Descricao  : Funcoes para controlar os acionamentos dos leds e buzzer do trator
//   Data       : 21/05/2019
//*************************************************************************************************/

#include "Timer.h"
#include "Pls.h"

#define pinoFarol 2                     //Pino onde esta ligado o led do farol
#define pinoGiroFlex 4                  //Pino onde esta ligado o led do giroFlex
#define pinoBuzzer A0                   //Pino onde esta ligado o buzzer
#define pinoFarolSec A1                 //Pino onde esta ligado o farol secundario

Timer tempoPiscaLed = Timer(100);       //Tempo de acionamento para o led do giroflex
Timer intervaloPiscaLed = Timer(300);   //Intervalo entre os tempos de acionamento
Timer filtroFarol = Timer(50);          //Filtro para o botão de ligar o farol
Timer filtroFarolSec = Timer(50);       //Filtro para o botão de ligar o farol secundario
Timer filtroGiroFlex = Timer(50);       //Filtro para o botão de ligar o giroflex

Pls seloFarol;                          //Objeto auxiliar para leitura das bordas de subida/descida do bt do farol
Pls pulsoFarol;                         //Objeto auxiliar para filtrar o botao do controle que aciona o farol
Pls seloFarolSec;                       //Objeto auxiliar para leitura das bordas de subida/descida do bt do farol
Pls pulsoFarolSec;                      //Objeto auxiliar para filtrar o botao do controle que aciona o farol
Pls seloGiroFlex;                       //Objeto auxiliar para leitura das bordas de subida/descidda do bt do giroflex
Pls pulsoGiroFlex;                      //Objeto auxiliar para filtrar o botao do controle que aciona o giroflex

void configuraSinalizacao()             //Realiza a configuraaao dos pinos dos leds e do buzzer
{
    pinMode(pinoFarol, OUTPUT);
    pinMode(pinoGiroFlex, OUTPUT);
    pinMode(pinoBuzzer, OUTPUT);
    pinMode(pinoFarolSec, OUTPUT);
}

bool piscaLed()                         //Funcao auxiliar para piscar o led
{
    static bool statusLed = false;
    static byte cont = 0;
    if(tempoPiscaLed.tick() and cont <= 4)
    {
        statusLed = !statusLed;
        tempoPiscaLed.reset();
        cont++;
    }
    if(cont > 4)
    {
        statusLed = false;
        if(intervaloPiscaLed.tick())
        {
            intervaloPiscaLed.reset();
            cont = 0;
        }
    }
    return(statusLed);
}

void alternaFarol(bool on, bool off)           //Alterna a claridade do farol do trator
{
    bool bt = seloFarol.selo(on, off);
    bool filtro = filtroFarol.onDelay(bt);
    bool status = pulsoFarol.alternate(filtro);
    digitalWrite(pinoFarol, status);
}

void alternaFarolSec(bool on, bool off)           //Alterna a claridade do farol do trator
{
    bool bt = seloFarolSec.selo(on, off);
    bool filtro = filtroFarolSec.onDelay(bt);
    bool status = pulsoFarolSec.alternate(filtro);
    digitalWrite(pinoFarolSec, status);
}

void alternaGiroFlex(bool on, bool off)        //Liga e desliga o giroflex de acordo com os botaes pressionados no controle
{
    bool bt = seloGiroFlex.selo(on, off);
    bool filtro = filtroGiroFlex.onDelay(bt);
    bool status = pulsoGiroFlex.alternate(filtro);
    if(status)
    {
        digitalWrite(pinoGiroFlex, piscaLed());
    }
    else
    {
        digitalWrite(pinoGiroFlex, LOW);
    }
}

void controleLeds()                     //Liga e desliga os leds de acordo com os botaes pressionados no controle
{
    bool ds2AcionaFarol = joyLeituraBotao(btFarol);
    bool ds2AcionaFarolSolto = joyBtSolto(btFarol);
    bool ds2AcionaGiroFlex = joyLeituraBotao(btGiroFlex);
    bool ds2AcionaGiroFlexSolto = joyBtSolto(btGiroFlex);
    bool ds2AcionaFarolSec = joyLeituraBotao(btFarolSec);
    bool ds2AcionaFarolSecSolto = joyBtSolto(btFarolSec);
    alternaFarol(ds2AcionaFarol, ds2AcionaFarolSolto);
    alternaFarolSec(ds2AcionaFarolSec, ds2AcionaFarolSecSolto);
    alternaGiroFlex(ds2AcionaGiroFlex, ds2AcionaGiroFlexSolto);
}

void controleBuzzer()                   //Liga e desliga o buzzer de acordo com os botaes pressionados no controle
{
    bool ds2AcionaBuzzer = joyLeituraBotao(btBuzzer);
    digitalWrite(pinoBuzzer, ds2AcionaBuzzer);
}
