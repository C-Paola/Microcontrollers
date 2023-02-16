#include<16F877.h> //Microcontrolador
#use delay(clock = 4000000) //Frecuencia
#fuses XT, NOWDT, NOPROTECT, NOPUT //Características del PIC
#use fast_io (B) //Inicializa el puerto B
#use fast_io (D) //Inicializa el puerto D

byte CONST display[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98}; //Vector para definir los números en ánodo común

void main() {
   byte ud = 0, dec = 0; //Inicialización de variables
   set_tris_b(0x00); //Puerto B como salidas
   set_tris_d(0x00); //Puerto D como salidas
   output_d(0); //Define todo el puerto D como cero (está de más)
   while(1){ 
      for(dec = 0; dec < 10; dec++){ //Ciclo de las decenas, comienza en cero y va hasta 9
         for(ud = 0; ud < 10; ud++){ //Ciclo de las unidades, comienza en cero y va hasta 9
            output_b(0x01); //Enciende el display de las unidades
            output_d(display[ud]); //Envía el valor de las unidades al 7 segmentos
            delay_ms(10); //Tiempo de visualización
            if(dec == 0) output_b(0x00); //Si las decenas son cero se apagan ambos displays
            else output_b(0x02); //Si las decenas son mayores a 1 se muestran las decenas
            output_d(display[dec]); //Muestra el valor de las decenas en el 7 segmentos
            delay_ms(10); //Tiempo de visualización
         }
      }
   }
}
