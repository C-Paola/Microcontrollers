/*Crear una secuencia de luces con  diodos LED. Cambiar el estado de otro diodo LED
  cada vez que se accione un interruptor utilizando para ello la interrupción externa
  (RB0/INT)*/
  
#include <16f877.h> //Microcontrolador
#fuses XT, NOWDT, PUT, NOWRT  //Características del PIC
#use delay(clock=4Mhz)  //Frecuencia
#use standard_io(A)  //Led
#use standard_io(B)  //Interrupción externa
#use standard_io(D)  //Encienden los 8 leds

#INT_EXT
void ext_int(void){  //Se ejecuta cada vez que se activa la interrupción externa
   output_toggle(PIN_A0);  //Cambia el estado del led
}

void main(){
   int x=0xAA;   //Secuencia de LEDS (No se utiliza)
   output_low(PIN_A0);  //Envía un cero lógico al PIN A0
   enable_interrupts(INT_EXT); //Habilita la interrupción externa
   ext_int_edge(L_TO_H);    //Hace que la interrupción externa vaya de LOW a HIGH
   enable_interrupts(GLOBAL);  //Activa las interrupciones globales
   while (TRUE){
      for(x=0;x<6;x++){   //Secuencia de números para encender los lEDS
         output_D(0xAA);
         delay_ms(200);
         output_D(0x55);
         delay_ms(200);
      }
      for(x=0;x<200;){
         output_D(x);
         delay_ms(200);
         x+=30;
      }
   }
}
  
