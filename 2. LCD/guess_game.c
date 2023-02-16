/*Implementar un juego en el cual se adivine un n�mero entre 1 y 10. Existen 3 oportunidades para adivinar el 
n�mero. El n�mero a adivinar debe ser generado de forma aleatoria. Deben existir dos pulsadores, uno para 
escribir el n�mero (comienza en 1 y por cada pulsaci�n se incrementa) y otro pulsador para confirmar el 
n�mero. A trav�s de un display LCD de doble l�nea se debe mostrar en pantalla el n�mero ingresado, los 
intentos restantes y un mensaje si gan� o perdi� el juego*/
  
 #include <16f877.h> // Microcontrolador 
 #fuses XT, NOWDT    // Caracter�sticas del microcontrolador 
 #use delay(clock = 4MHz) // Frecuencia de trabajo 
 #include <lcd.c> // Librer�a del LCD 
 #use standard_io(A) // Se ajusta el registro TRIS autom�ticamente, (seleccionar autom�ticamente las entradas y salidas)
 #include <stdlib.h> // Librer�a del rand y srand
  
 void main () {
   lcd_init();  // Enciende el LCD, caracteres de 5x8, dos l�neas 
   int num_actual = 1; // Se define el n�mero actual}
   int mayor = 10, menor = 1;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2); // Timer del PIC
   srand(get_rtcc()); // Genera la semilla para el n�mero random
   int num_random = (rand() % (mayor-menor+1)) + menor; // L�gica para hallar el n�mero al azar
   int intentos = 3; // Se definen los intentos
   printf(lcd_putc, "\fAdivina el num \nIntentos: 3"); // Mensaje de inicio
   delay_ms(2000); //Tiempo de visualizaci�n
   while (TRUE) { // Se ejecuta siempre no se gane o no se pierda
      printf(lcd_putc, "\fTu numero: %d\nIntentos: %d",num_actual, intentos); // Se visualiza el n�mero actual
      
      if(input(PIN_A3) == 1){ // Bot�n de incrementar
         num_actual++; // Suma posiciones
         delay_ms(200); // Tiempo de espera entre cada cambio (evita rebote del bot�n)
      }
      if(num_actual == 11)  num_actual = 1; // Limita que num_actual vaya de 1 a 10.
      
      if(input(PIN_A5) == 1){ // Bot�n de selecci�n
         delay_ms(200); // Tiempo de espera entre cada cambio (evita rebote del bot�n)

         if(num_random == num_actual) { // Comparaci�n del n�mero actual y el n�mero random
            intentos=3;
            printf(lcd_putc, "\fGanaste, el num\nera: %d",num_random); // Se visualiza que se gan� y el n�mero que era
            delay_ms(2000); //Tiempo de visulizaci�n
            lcd_putc("\fAdivina otra vez \nIntentos: 3"); 
            delay_ms(2000);
            setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2); // Timer del PIC
            srand(get_rtcc()); // Genera la semilla para el n�mero random
            num_random = (rand() % (mayor-menor+1)) + menor; // L�gica para hallar el n�mero al azar
         }
         else {
            intentos--; // Se disminuyen los intentos
            num_actual=1; //Reinicia el n�mero actual
            
            if(intentos==0){ 
               intentos=3;
               printf(lcd_putc, "\fPerdiste, el num\nera: %d",num_random); // Se visualiza que se perdi� y el n�mero que era
               delay_ms(2000); //Tiempo de visualizaci�n
               lcd_putc("\fAdivina otra vez \nIntentos: 3");
               delay_ms(2000);
               setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2); // Timer del PIC
               srand(get_rtcc()); // Genera la semilla para el n�mero random
               num_random = (rand() % (mayor-menor+1)) + menor; // L�gica para hallar el n�mero al azar
            }
            else {
               printf(lcd_putc, "\fFallaste\nIntentos: %d",intentos); // Se visualiza que se fall� y el n�mero de intentos 
               delay_ms(800); // Tiempo de visualizaci�n
            }
         }
      }
      delay_ms(200); // Tiempo de visualizaci�n
   }
 }
