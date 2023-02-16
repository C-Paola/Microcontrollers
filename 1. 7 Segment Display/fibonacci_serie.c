#include<16F877.h> /* Librería del microcontrolador */
#use delay(clock = 4MHz) /* Velocidad del reloj, importante poner la misma en Proteus */
#fuses XT,NOWDT,NOPROTECT,NOPUT /* Parámetros de la simulación */
#use fast_io (B) /* Declaración del puerto B */
#use fast_io (D) /* Declaración del puerto D */

byte CONST display[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98}; /* Código hexadecimal de los números del 0 al 9 en Anodo común */

void main(){

   byte ud = 0, dec = 0, numero = 0, num_actual = 1, num_anterior = 0, posicion = 0; /* Declaración de variables */
   byte lista_fibonacci[12] = {}; /* Creación de una lista vacía, donde luego se almacenará la serie */
   set_tris_b(0x0c); /* Definición de los puertos B como entradas */
   set_tris_d(0x00); /* Definición de los puertos D como salidas */
   port_b_pullups(TRUE); /* Activación de los Pull Ups en el puerto B */
   output_d(0xff); /* Activar por defecto todas las salidas del puerto D */
   
   for (int i = 0; i<12 ; i++){ /* Dentro de este ciclo For se crea toda la serie y se almacena en "lista_fibonacci" */
      lista_fibonacci[i] = num_anterior;
      numero = num_anterior + num_actual;
      num_anterior = num_actual;
      num_actual = numero;
   }
      
   while(1){ /* Este ciclo While se ejecuta infinitamente */
      output_b(0x01); /* Enciende el segmento de las unidades */
      output_d(display[ud]); /* Escribe el número de unidades */
      delay_ms(50); /* Espera 50 ms */
      if(dec == 0) output_b(0x00); /* Sí aún no se llega a las decenas no se enciende nada */
      else output_b(0x02); /* Sí por el contrario, hay decenas, se enciende el segmento de las decenas */
      output_d(display[dec]); /* Se escribe el número de las decenas, nótese que el de las unidades se apaga, solo puede estar uno encendido al tiempo */
      delay_ms(50); /* Espera 50 ms */
      
      if(input(PIN_B2) == 0){ /* Sí se presiona el botón de B2, se avanza en la posición de la serie a imprimir */
         if(posicion <= 10) posicion++;
      }
         while(input(PIN_B2) == 0) {
            output_b(0x01); /* Enciende el segmento de las unidades */
            output_d(display[ud]); /* Escribe el número de unidades */
            delay_ms(50); /* Espera 50 ms */
            if(dec == 0) output_b(0x00); /* Sí aún no se llega a las decenas no se enciende nada */
            else output_b(0x02); /* Sí por el contrario, hay decenas, se enciende el segmento de las decenas */
            output_d(display[dec]); /* Se escribe el número de las decenas, nótese que el de las unidades se apaga, solo puede estar uno encendido al tiempo */
            delay_ms(50); /* Espera 50 ms */
         } /* Este ciclo While evita bugs, solo se ejecuta el código cuando se suelte el botón */
         
      if(input(PIN_B3) == 0){ /* Sí se presiona el botón de B3, se retrocede en la posición de la serie a imprimir */
         if(posicion != 0) posicion--;
      }
         while(input(PIN_B3) == 0) {
            output_b(0x01); /* Enciende el segmento de las unidades */
            output_d(display[ud]); /* Escribe el número de unidades */
            delay_ms(50); /* Espera 50 ms */
            if(dec == 0) output_b(0x00); /* Sí aún no se llega a las decenas no se enciende nada */
            else output_b(0x02); /* Sí por el contrario, hay decenas, se enciende el segmento de las decenas */
            output_d(display[dec]); /* Se escribe el número de las decenas, nótese que el de las unidades se apaga, solo puede estar uno encendido al tiempo */
            delay_ms(50); /* Espera 50 ms */
         } /* Este ciclo While evita bugs, solo se ejecuta el código cuando se suelte el botón */
      
      numero = lista_fibonacci[posicion]; /* Se lee el número en la posición actual de la serie */
      dec = numero/10; /* Se halla el número de decena que será el próximo en imprimirse */
      ud = numero - (dec*10); /* Se halla el número de unidades que será el próximo en imprimirse */
      /* Cuando el ciclo While se repita, el proceso se ejecutará con estos nuevos valores de unidades y decenas */
   }
}
