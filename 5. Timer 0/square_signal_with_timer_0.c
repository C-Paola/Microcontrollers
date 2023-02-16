/*Generar una señal cuadrada de 1kHz utilizando la interrupción del TIMER 0*/

#include <16f877.h> //Microcontrolador
#fuses XT, NOWDT  //Características del PIC
#use delay(clock=4Mhz)  //Frecuencia
#use standard_io(B)  //Ajusta el puerto B para la salida

#INT_TIMER0
void functemp0(void){
   output_toggle(PIN_B0);  //Cambia el estado del PIN B0
   set_timer0(0x1B);    //Carga del timer
}

void main(){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2); //Inicializa el Timer 0
   set_timer0(0x1B);   //Carga del timer (hallada de la fórmula pero para el Timer 0 se modifica el valor hasta obtener la frecuencia requerida)
   enable_interrupts(INT_TIMER0);  //Habilita las interrupciones del timer 0
   enable_interrupts(global);   //Habilita las interrupciones de manera global
   while(TRUE); 
}
