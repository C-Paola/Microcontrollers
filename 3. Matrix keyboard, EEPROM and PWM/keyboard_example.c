/*Introducir datos por el teclado y visualizarlos en el LCD. Cuando se pulsa la 
tecla ' * ' borrar el LCD.*/

#include <16f877.h> //Microcontrolador
#fuses XT,NOWDT,NOPROTECT,NOLVP //Caracter�sticas del PIC
#use delay(clock=4Mhz) //Frecuencia del PIC
#include <lcd.c> //Librer�a de la LCD
#include <kbd.c> //librer�a del teclado matricial

void main() {
   char k; //Variable que recibe el caracter
   int x; //Variable no utilizada
   lcd_init(); //Enciende la LCD
   kbd_init(); //Inicializa el teclado
   port_b_pullups(TRUE); //Activa los botones en el puerto B
   lcd_putc("\fEscriba...\n"); //Se visualiza un mensaje
   
   while(TRUE){
      k = kbd_getc(); //Lee el teclado y almacena el caracter en k
      x=k-48; //No se utiliza para nada
      if (k!=0){ //Se presiona alg�n bot�n
         if(k=='*'){ //Se oprime '*'
            lcd_putc("\fBorrando..."); //Se imprime el mensaje
            delay_ms(1000); //Tiempo de visualizaci�n
            lcd_putc('\f'); //Limpia la pantalla de la LCD
         }
         else{
            lcd_putc(k); //Se imprime el caracter
            delay_ms(500); //Tiempo de visualizaci�n
         }
      }
   }
}
