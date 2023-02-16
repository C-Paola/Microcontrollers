#include<16F877.h> /* Librer�a del microcontrolador */
#use delay(clock = 4MHz) /* Velocidad del reloj, importante poner la misma en Proteus */
#fuses XT,NOWDT,NOPROTECT,NOPUT /* Par�metros de la simulaci�n */
#use fast_io (B) /* Declaraci�n del puerto B */
#use fast_io (D) /* Declaraci�n del puerto D */

byte CONST display[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98}; /* C�digo hexadecimal de los n�meros del 0 al 9 en Anodo com�n */

void main(){

   byte ud = 0, dec = 0, numero = 0, num_actual = 1, num_anterior = 0, posicion = 0; /* Declaraci�n de variables */
   byte lista_fibonacci[12] = {}; /* Creaci�n de una lista vac�a, donde luego se almacenar� la serie */
   set_tris_b(0x0c); /* Definici�n de los puertos B como entradas */
   set_tris_d(0x00); /* Definici�n de los puertos D como salidas */
   port_b_pullups(TRUE); /* Activaci�n de los Pull Ups en el puerto B */
   output_d(0xff); /* Activar por defecto todas las salidas del puerto D */
   
   for (int i = 0; i<12 ; i++){ /* Dentro de este ciclo For se crea toda la serie y se almacena en "lista_fibonacci" */
      lista_fibonacci[i] = num_anterior;
      numero = num_anterior + num_actual;
      num_anterior = num_actual;
      num_actual = numero;
   }
      
   while(1){ /* Este ciclo While se ejecuta infinitamente */
      output_b(0x01); /* Enciende el segmento de las unidades */
      output_d(display[ud]); /* Escribe el n�mero de unidades */
      delay_ms(50); /* Espera 50 ms */
      if(dec == 0) output_b(0x00); /* S� a�n no se llega a las decenas no se enciende nada */
      else output_b(0x02); /* S� por el contrario, hay decenas, se enciende el segmento de las decenas */
      output_d(display[dec]); /* Se escribe el n�mero de las decenas, n�tese que el de las unidades se apaga, solo puede estar uno encendido al tiempo */
      delay_ms(50); /* Espera 50 ms */
      
      if(input(PIN_B2) == 0){ /* S� se presiona el bot�n de B2, se avanza en la posici�n de la serie a imprimir */
         if(posicion <= 10) posicion++;
      }
         while(input(PIN_B2) == 0) {
            output_b(0x01); /* Enciende el segmento de las unidades */
            output_d(display[ud]); /* Escribe el n�mero de unidades */
            delay_ms(50); /* Espera 50 ms */
            if(dec == 0) output_b(0x00); /* S� a�n no se llega a las decenas no se enciende nada */
            else output_b(0x02); /* S� por el contrario, hay decenas, se enciende el segmento de las decenas */
            output_d(display[dec]); /* Se escribe el n�mero de las decenas, n�tese que el de las unidades se apaga, solo puede estar uno encendido al tiempo */
            delay_ms(50); /* Espera 50 ms */
         } /* Este ciclo While evita bugs, solo se ejecuta el c�digo cuando se suelte el bot�n */
         
      if(input(PIN_B3) == 0){ /* S� se presiona el bot�n de B3, se retrocede en la posici�n de la serie a imprimir */
         if(posicion != 0) posicion--;
      }
         while(input(PIN_B3) == 0) {
            output_b(0x01); /* Enciende el segmento de las unidades */
            output_d(display[ud]); /* Escribe el n�mero de unidades */
            delay_ms(50); /* Espera 50 ms */
            if(dec == 0) output_b(0x00); /* S� a�n no se llega a las decenas no se enciende nada */
            else output_b(0x02); /* S� por el contrario, hay decenas, se enciende el segmento de las decenas */
            output_d(display[dec]); /* Se escribe el n�mero de las decenas, n�tese que el de las unidades se apaga, solo puede estar uno encendido al tiempo */
            delay_ms(50); /* Espera 50 ms */
         } /* Este ciclo While evita bugs, solo se ejecuta el c�digo cuando se suelte el bot�n */
      
      numero = lista_fibonacci[posicion]; /* Se lee el n�mero en la posici�n actual de la serie */
      dec = numero/10; /* Se halla el n�mero de decena que ser� el pr�ximo en imprimirse */
      ud = numero - (dec*10); /* Se halla el n�mero de unidades que ser� el pr�ximo en imprimirse */
      /* Cuando el ciclo While se repita, el proceso se ejecutar� con estos nuevos valores de unidades y decenas */
   }
}
