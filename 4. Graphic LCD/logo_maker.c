/*Realice una aplicación en un LCD gráfico que muestre una animación sencilla 
como preámbulo y posteriormente imprima en forma intermitente e indefinida el 
logo de la Universidad Francisco de Paula Santander.*/

#include <16f877.h> //Microcontrolador
#fuses HS,NOWDT,NOPROTECT,NOLVP //Características del PIC
#use delay(clock=20MHz) //Frecuencia
#include <HDM64GS12.c> //Librería de la LCD gráfica
#include <graphics.c> //Librería para dibujar en la pantalla

void intro(void); //Función de la intro
void logo(void); //Función para el logo

void main(){
   intro(); //Sellama la función de la intro
   while(TRUE){
   glcd_fillScreen(OFF); //Se limpia la pantalla (se rellena con color blanco)
   delay_ms(200); //Tiempo d visualización
   logo(); //Se llama la función del logo
   delay_ms(1000); //Tiempo de visualización
   }
}
void intro(void){
   signed int8 x1=59,y1=27,x2=69,y2=37; //Coordenadas para un cuadro en el centro de la pantalla
   glcd_init(ON); //Se inicializa la pantalla
   glcd_rect(x1,y1,x2,y2,YES,ON); //Se dibuja un cuadrado relleno
   while(y1>0) { //Se dibujan cuadrados solo dentro de la pantalla
      glcd_rect(x1,y1,x2,y2,NO,ON); //Se dibuja cuadrado sin relleno y negro
      delay_ms(100); //Tiempo de visualización
      x1=x1-2; //Se desplazan hacia la izquierda las coordenadas de la esquina superior izquierda
      y1=y1-2;
      x2=x2+2; //Se desplazan hacia la derecha las coordenadas de la esquina inferior derecha
      y2=y2+2;
   }
   x1=32,y1=0,x2=96,y2,64; //Coordenadas del máximo de cuadrados visualizados en la pantalla
   while(y1<32){ //Se eliminan los cuadrados hasta la mitad de la pantalla
      glcd_rect(x1,y1,x2,y2,NO,OFF); //Se sibuja un cuadrado sin relleno y blanco
      delay_ms(100); //Tiempo de visualización
      x1++; //Se desplazan hacia la derecha las coordenadas de la esquina superior izquierda
      y1++;
      x2--; //Se desplazan hacia la izquierda las coordenadas de la esquina inferior derecha
      y2--;  
   }
}
void logo(void) { //Función del logo
   glcd_rect(32,0,96,64,YES,ON);    //Se dibuja un cuadrado con relleno negro
   glcd_rect(37,5,40,27,YES,OFF);   //U
   glcd_rect(37,24,59,27,YES,OFF);  //U
   glcd_rect(56,5,59,27,YES,OFF);   //U
   glcd_rect(69,5,72,27,YES,OFF);   //F
   glcd_rect(69,5,91,8,YES,OFF);    //F
   glcd_rect(69,15,80,18,YES,OFF);  //F
   glcd_rect(37,37,59,40,YES,OFF);  //P
   glcd_rect(37,37,40,59,YES,OFF);  //P
   glcd_rect(37,47,59,50,YES,OFF);  //P
   glcd_rect(56,37,59,50,YES,OFF);  //P
   glcd_rect(69,37,91,40,YES,OFF);  //S
   glcd_rect(69,37,72,50,YES,OFF);  //S
   glcd_rect(69,47,91,50,YES,OFF);  //S
   glcd_rect(88,47,91,59,YES,OFF);  //S
   glcd_rect(69,56,91,59,YES,OFF);  //S
}
