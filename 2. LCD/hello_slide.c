/*Mostrar en una pantalla LCD (2X16) un letrero movible en la línea superior.
  En la línea inferior se debe mostrar la posición en la que se encuentra el 
  cursor del letrero.*/
  
  #include <16f877.h> // Microcontrolador 
  #fuses XT, NOWDT    // Características del microcontrolador 
  #use delay(clock = 4MHz) // Frecuencia de trabajo 
  #include <lcd.c> // Librería del LCD 
  
  void main () {
   int x = 1;  // inicialización de la variable 
   lcd_init();  // Enciende el LCD, caracteres de 5x8, dos líneas 
   lcd_gotoxy(1,1); // Posición inicial en pantalla (x,y) {Sobra esta condición}
  
    while (TRUE) {
       lcd_putc('\f'); // elimina lo que hay en la pantalla del LCD 
       lcd_gotoxy(x,1); //posición x=1, del caracter inicial 
       printf(lcd_putc, "Hola\nx = %d",x); //Escribe en la pantalla el Hola y X
       x++; //Incremento en X de una unidad
       if(x==17) x=1; // El LCD es 2X16, si el Hola llega a a¿la posición inicial otra vez x=1
       delay_ms(200); // Tiempo de desplazamiento
    }
  }
       
  
   
