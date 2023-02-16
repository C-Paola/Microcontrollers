/*Realizar una aplicación con un LCD gráfico que dibuje en pantalla una cuadrícula 
de dos filas por cuatro columnas. Se debe mostrar un círculo relleno en una de las 
8 casillas. El círculo indica la ubicación del cursor. Con un pulsador se debe
desplazar el cursor de una casilla a la otra.*/

#include <16f877.h> //Microcontrolador
#fuses HS,NOWDT,NOPROTECT,NOLVP //Características del PIC
#use delay(clock=20MHz) //Frecuencia
#include <HDM64GS12.c> //Librería de la LCD gráfica
#include <graphics.c> //Librería para dibujar en la pantalla
#use standard_io(a)

void cuadricula(void); //Función que imprime la cuadrícula

void main() {
   int x=22, y=18; //Valores del centro del círculo de la primera cuadrícula
   glcd_init(ON); //Se inicializa la pantalla
   cuadricula(); //Se llama la función de la cuadrícula
   glcd_circle(x,y,10,YES,ON); //Se dibuja un círculo negro en la primera posición de la cuadrícula
   while (TRUE) { 
   if(input(PIN_A0)==1){ //Si se presiona el botón de avanzar a la izquierda
      glcd_circle(x,y,10,YES,OFF); //Se imprime un círculo blanco para eliminar el círculo negro
      if(x==22) x=134; //Condición para ir del inicio al final otra vez
      x=x-28;  //Mueve el círculo a la izquierda
      glcd_circle(x,y,10,YES,ON);  //Se imprime el nuevo círculo negro
      delay_ms(200); //Anti rebote
   } 
   if(input(PIN_A1)==1){ //Si se presiona el botón de avanzar a la derecha
      glcd_circle(x,y,10,YES,OFF); //Se imprime un círculo blanco para eliminar el círculo negro
      if(x==106) x=-6; //Condición para ir del final al inicio otra vez
      x=x+28;  //Mueve el círculo a la derecha 
      glcd_circle(x,y,10,YES,ON);  //Se imprime el nuevo círculo negro
      delay_ms(200); //Anti rebote
   } 
   if(input(PIN_A2)==1){ //Si se presiona el botón de arriba/abajo
      glcd_circle(x,y,10,YES,OFF); //Se imprime un círculo blanco para eliminar el círculo negro
      if(y==18) y=46; //Condición para ir de arriba a abajo
      else y=18; //Condición para ir de abaja a arriba
      glcd_circle(x,y,10,YES,ON);  //Se imprime el nuevo círculo negro
      delay_ms(200); //Anti rebote
   } 
   }
}

void cuadricula(void) { //Función que define la cuadrícula (un rectángulo y cuatro líneas)
   glcd_rect(8,4,120,60,NO,ON); 
   glcd_line(36,4,36,60,ON);
   glcd_line(64,4,64,60,ON);
   glcd_line(92,4,92,60,ON);
   glcd_line(8,32,120,32,ON);
}
