/*Realizar una aplicaci�n con un LCD gr�fico que dibuje en pantalla una cuadr�cula 
de dos filas por cuatro columnas. Se debe mostrar un c�rculo relleno en una de las 
8 casillas. El c�rculo indica la ubicaci�n del cursor. Con un pulsador se debe
desplazar el cursor de una casilla a la otra.*/

#include <16f877.h> //Microcontrolador
#fuses HS,NOWDT,NOPROTECT,NOLVP //Caracter�sticas del PIC
#use delay(clock=20MHz) //Frecuencia
#include <HDM64GS12.c> //Librer�a de la LCD gr�fica
#include <graphics.c> //Librer�a para dibujar en la pantalla
#use standard_io(a)

void cuadricula(void); //Funci�n que imprime la cuadr�cula

void main() {
   int x=22, y=18; //Valores del centro del c�rculo de la primera cuadr�cula
   glcd_init(ON); //Se inicializa la pantalla
   cuadricula(); //Se llama la funci�n de la cuadr�cula
   glcd_circle(x,y,10,YES,ON); //Se dibuja un c�rculo negro en la primera posici�n de la cuadr�cula
   while (TRUE) { 
   if(input(PIN_A0)==1){ //Si se presiona el bot�n de avanzar a la izquierda
      glcd_circle(x,y,10,YES,OFF); //Se imprime un c�rculo blanco para eliminar el c�rculo negro
      if(x==22) x=134; //Condici�n para ir del inicio al final otra vez
      x=x-28;  //Mueve el c�rculo a la izquierda
      glcd_circle(x,y,10,YES,ON);  //Se imprime el nuevo c�rculo negro
      delay_ms(200); //Anti rebote
   } 
   if(input(PIN_A1)==1){ //Si se presiona el bot�n de avanzar a la derecha
      glcd_circle(x,y,10,YES,OFF); //Se imprime un c�rculo blanco para eliminar el c�rculo negro
      if(x==106) x=-6; //Condici�n para ir del final al inicio otra vez
      x=x+28;  //Mueve el c�rculo a la derecha 
      glcd_circle(x,y,10,YES,ON);  //Se imprime el nuevo c�rculo negro
      delay_ms(200); //Anti rebote
   } 
   if(input(PIN_A2)==1){ //Si se presiona el bot�n de arriba/abajo
      glcd_circle(x,y,10,YES,OFF); //Se imprime un c�rculo blanco para eliminar el c�rculo negro
      if(y==18) y=46; //Condici�n para ir de arriba a abajo
      else y=18; //Condici�n para ir de abaja a arriba
      glcd_circle(x,y,10,YES,ON);  //Se imprime el nuevo c�rculo negro
      delay_ms(200); //Anti rebote
   } 
   }
}

void cuadricula(void) { //Funci�n que define la cuadr�cula (un rect�ngulo y cuatro l�neas)
   glcd_rect(8,4,120,60,NO,ON); 
   glcd_line(36,4,36,60,ON);
   glcd_line(64,4,64,60,ON);
   glcd_line(92,4,92,60,ON);
   glcd_line(8,32,120,32,ON);
}
