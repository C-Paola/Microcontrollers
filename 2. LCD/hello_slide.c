/*Mostrar en una pantalla LCD (2X16) un letrero movible en la l�nea superior.
  En la l�nea inferior se debe mostrar la posici�n en la que se encuentra el 
  cursor del letrero.*/
  
  #include <16f877.h> // Microcontrolador 
  #fuses XT, NOWDT    // Caracter�sticas del microcontrolador 
  #use delay(clock = 4MHz) // Frecuencia de trabajo 
  #include <lcd.c> // Librer�a del LCD 
  
  void main () {
   int x = 1;  // inicializaci�n de la variable 
   lcd_init();  // Enciende el LCD, caracteres de 5x8, dos l�neas 
   lcd_gotoxy(1,1); // Posici�n inicial en pantalla (x,y) {Sobra esta condici�n}
  
    while (TRUE) {
       lcd_putc('\f'); // elimina lo que hay en la pantalla del LCD 
       lcd_gotoxy(x,1); //posici�n x=1, del caracter inicial 
       printf(lcd_putc, "Hola\nx = %d",x); //Escribe en la pantalla el Hola y X
       x++; //Incremento en X de una unidad
       if(x==17) x=1; // El LCD es 2X16, si el Hola llega a a�la posici�n inicial otra vez x=1
       delay_ms(200); // Tiempo de desplazamiento
    }
  }
       
  
   
