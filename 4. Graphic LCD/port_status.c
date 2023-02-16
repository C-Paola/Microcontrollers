/*Mostrar en un LCD gráfico el estado de los pines de entrada del puerto A.*/

#include <16f877.h> //Microcontrolador
#fuses HS,NOWDT,NOPROTECT,NOLVP //Cararacterísticas del PIC
#use delay(clock=20MHz) //Frecuencia
#include <HDM64GS12.c> //Librería de la LCD gráfica
#include <graphics.c> //Librería para dibujar en la pantalla
#use standard_io(a) //Define los pines del puerto A automáticamente (Para usar los switches)

void inicializar(void); //Función para incializar la LCD

char A5[ ]="A5"; //Vectores que almacenan palabras (A5, A4, A3, A2, A1, A0, Puerto A)
char A4[ ]="A4";
char A3[ ]="A3";
char A2[ ]="A2";
char A1[ ]="A1";
char A0[ ]="A0";
char IN[ ]="Puerto A";

void main(){
   inicializar(); //Se llama la función definida abajo
   while(TRUE){
      if(input_state(PIN_A5) == 0) //Si se activa el switch se rellena el rectángulo con negro (ON)
         glcd_rect(33,41,45,59,YES,ON);
      else
         glcd_rect(33,41,45,59,YES,OFF); //si no se activa el switch se rellena el rectángulo con blanco (OFF)
      if (input_state(PIN_A4) == 0)
         glcd_rect(49,41,61,59,YES,ON);
      else
         glcd_rect(49,41,61,59,YES,OFF);
      if (input_state(PIN_A3) == 0)
         glcd_rect(65,41,77,59,YES,ON);
      else
         glcd_rect(65,41,77,59,YES,OFF);
      if (input_state(PIN_A2) == 0)
         glcd_rect(81,41,93,59,YES,ON);
      else
         glcd_rect(81,41,93,59,YES,OFF);
      if (input_state(PIN_A1) == 0)
         glcd_rect(97,41,109,59,YES,ON);
      else
         glcd_rect(97,41,109,59,YES,OFF);
      if (input_state(PIN_A0) == 0)
         glcd_rect(113,41,125,59,YES,ON);
      else 
         glcd_rect(113,41,125,59,YES,OFF);
   }
}

void inicializar(void){
   glcd_init(ON); //Se enciende la pantalla
   glcd_text57(33,30,A5,1,ON); //se especifica y se imprime la posición x, y, vector char, tamaño (5x7), color (ON=negro, OFF=blanco)
   glcd_text57(49,30,A4,1,ON);
   glcd_text57(65,30,A3,1,ON);
   glcd_text57(81,30,A2,1,ON);
   glcd_text57(97,30,A1,1,ON);
   glcd_text57(113,30,A0,1,ON);
   glcd_text57(30,5,IN,2,ON);
   glcd_rect(32,40,46,60,NO,ON); //Se dibujan y se imprimen rectángulos: x1, y1, x2, y2, si está relleno o no, color
   glcd_rect(48,40,62,60,NO,ON);
   glcd_rect(64,40,78,60,NO,ON);
   glcd_rect(80,40,94,60,NO,ON);
   glcd_rect(96,40,110,60,NO,ON);
   glcd_rect(112,40,126,60,NO,ON);
}
