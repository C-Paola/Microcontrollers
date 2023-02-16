#include<16F877.h> //Microcontrolador
#use delay(clock = 4000000) //Frecuencia
#fuses XT, NOWDT, NOPROTECT, NOPUT //Características de PIC
#use fast_io (B) //Inicializa el puerto B
#use fast_io (D) //Inicializa el puerto A

byte CONST display[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98}; //Vector para definir los números en ánodo común

void main(){
   byte ud = 0, dec = 0; //Inicialización de variables
   set_tris_b(0x04); //Pin B2 como entrada
   set_tris_d(0x00); //Puerto D como salidas
   port_b_pullups(TRUE); //Activa el uso de botones en el puerto B
   output_b(0); //Envía un cero lógico al puerto B (está de más)
   while(1){
      output_b(0x01); //Enciende el display de las unidades
      output_d(display[ud]); //Envía el valor de las unidades al display
      delay_ms(10); //Tiempo de visualización
      if(dec == 0) output_b(0x00); //Si las decenas son cero, entonces se apagan ambos display
      else output_b(0x02); //Si las decenas son diferentes de cero se enciende el display de las decenas
      output_d(display[dec]); //Se envían los valores de las decenas al display
      delay_ms(10); //Tiempo de visualización
      if(input(PIN_B2) == 0){ //Cuando se pulsa el botón
         ud++; //Se incrementan las unidades
         if(ud == 10){ //Si unidades ya es 10
            ud = 0; //Unidades toma el valor cero
            dec++; //Se incrementan las decenas
            if(dec == 10) dec = 0; //Si las decenas ya son 10, entonces se vuelven cero otra vez
         }
         while(input(PIN_B2)==0){} //Antirebote
      }
   }
}
