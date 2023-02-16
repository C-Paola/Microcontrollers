/*Diseñar un sistema para el control de acceso; a través de un teclado de 3x4 
introducir una clave de 3 dígitos que cuando sea correcta abra una puerta (con 
un pulso a un relé) y lo indique a una pantalla LCD. Guardar la clave de acceso 
en la memoria EEPROM.*/

#include <16f877.h> //Microcontrolador
#fuses XT, NOWDT, NOPROTECT, NOLVP //Características del PIC
#use delay(clock=4MHz) //Frecuencia
#use standard_io(A) //Define automáticamente los pines del puerto A (entradas o salidas)
#include <lcd.c> //Librería de la LCD
#include <kbd.c> //Librería del teclado matricial
#include <stdlib.h> //Librería para manejar la memoria
#rom 0x2100={'7','1','5'} //En la dirección 2100 se guarda 7, en la 2101 se guarda 1 y en la 2102 se guarda 5 (clave de la puerta)

void main(){
   char k; //Variable que almacena los caracteres del teclado
   int i; //Iterador para el while
   int j; //Iterador para el for
   char data[3], pass[3]; //Vectores vacíos con tres posiciones
   lcd_init(); //Inicializa la LCD
   kbd_init(); //Inicializa el teclado
   output_low(PIN_A0); //Cierra la puerta
   port_b_pullups(TRUE); //Activa el puerto B para uso de botones
   while(TRUE) {
      i = 0; //Iterador
      lcd_putc("\fIngrese clave:\n"); //Imprime el mensaje en la LCD
      while(i<=2){ //Limita la clave a 3 números
         k = kbd_getc(); //Recibe y almacena cada caracter
         if(k!=0){ //Se oprime cualquier tecla del teclado
            data[i]=k; //Se almacena en el vector cada caracter
            i++; //Se aumenta el número de iteraciones
            printf(lcd_putc,"*"); //Se imprime un asterisco por cada caracter
         }
      }
      delay_ms(500); //Tiempo de visualización
      for(j=0;j<=2;j++) //Se repite tres veces
         pass[j] = read_eeprom(j); //Se almacena la clave real (715) en el vector password
      if((data[0]==pass[0])&& //Compara la clave digitada con la clave real 
         (data[1]==pass[1])&&
         (data[2]==pass[2])){
         lcd_putc("\fPuerta abierta!"); //Si la clave es la misma se abre la puerta
         output_high(PIN_A0); //Se envía el 1 lógico para abrir la puerta (relay)
         delay_ms(3000); //La puerta dura 3 segundos abierta
         output_low(PIN_A0); //Se cierra la puerta
      }
      else{
         lcd_putc("\fClave incorrecta!\nPuerta cerrada!"); //Si no es la misma clave se imprime el mensaje y se mantiene la puerta cerrada
         delay_ms(3000); //Espera 3 segundos
      }
   }
}
