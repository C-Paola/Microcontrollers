/*Implementar un juego en el cual se adivine un número entre 1 y 10. Existen 3 oportunidades para adivinar el 
número. El número a adivinar debe ser generado de forma aleatoria. Deben existir dos pulsadores, uno para 
escribir el número (comienza en 1 y por cada pulsación se incrementa) y otro pulsador para confirmar el 
número. A través de un display LCD de doble línea se debe mostrar en pantalla el número ingresado, los 
intentos restantes y un mensaje si ganó o perdió el juego*/
  
 #include <16f877.h> // Microcontrolador 
 #fuses XT, NOWDT    // Características del microcontrolador 
 #use delay(clock = 4MHz) // Frecuencia de trabajo 
 #include <lcd.c> // Librería del LCD 
 #use standard_io(A) // Se ajusta el registro TRIS automáticamente, (seleccionar automáticamente las entradas y salidas)
 #include <stdlib.h> // Librería del rand y srand
  
 void main () {
   lcd_init();  // Enciende el LCD, caracteres de 5x8, dos líneas 
   int num_actual = 1; // Se define el número actual}
   int mayor = 10, menor = 1;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2); // Timer del PIC
   srand(get_rtcc()); // Genera la semilla para el número random
   int num_random = (rand() % (mayor-menor+1)) + menor; // Lógica para hallar el número al azar
   int intentos = 3; // Se definen los intentos
   printf(lcd_putc, "\fAdivina el num \nIntentos: 3"); // Mensaje de inicio
   delay_ms(2000); //Tiempo de visualización
   while (TRUE) { // Se ejecuta siempre no se gane o no se pierda
      printf(lcd_putc, "\fTu numero: %d\nIntentos: %d",num_actual, intentos); // Se visualiza el número actual
      
      if(input(PIN_A3) == 1){ // Botón de incrementar
         num_actual++; // Suma posiciones
         delay_ms(200); // Tiempo de espera entre cada cambio (evita rebote del botón)
      }
      if(num_actual == 11)  num_actual = 1; // Limita que num_actual vaya de 1 a 10.
      
      if(input(PIN_A5) == 1){ // Botón de selección
         delay_ms(200); // Tiempo de espera entre cada cambio (evita rebote del botón)

         if(num_random == num_actual) { // Comparación del número actual y el número random
            intentos=3;
            printf(lcd_putc, "\fGanaste, el num\nera: %d",num_random); // Se visualiza que se ganó y el número que era
            delay_ms(2000); //Tiempo de visulización
            lcd_putc("\fAdivina otra vez \nIntentos: 3"); 
            delay_ms(2000);
            setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2); // Timer del PIC
            srand(get_rtcc()); // Genera la semilla para el número random
            num_random = (rand() % (mayor-menor+1)) + menor; // Lógica para hallar el número al azar
         }
         else {
            intentos--; // Se disminuyen los intentos
            num_actual=1; //Reinicia el número actual
            
            if(intentos==0){ 
               intentos=3;
               printf(lcd_putc, "\fPerdiste, el num\nera: %d",num_random); // Se visualiza que se perdió y el número que era
               delay_ms(2000); //Tiempo de visualización
               lcd_putc("\fAdivina otra vez \nIntentos: 3");
               delay_ms(2000);
               setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2); // Timer del PIC
               srand(get_rtcc()); // Genera la semilla para el número random
               num_random = (rand() % (mayor-menor+1)) + menor; // Lógica para hallar el número al azar
            }
            else {
               printf(lcd_putc, "\fFallaste\nIntentos: %d",intentos); // Se visualiza que se falló y el número de intentos 
               delay_ms(800); // Tiempo de visualización
            }
         }
      }
      delay_ms(200); // Tiempo de visualización
   }
 }
