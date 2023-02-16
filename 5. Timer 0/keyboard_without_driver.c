/*Mostrar en un LCD la entrada de usuario. No utilizar el driver del teclado matricial.
  Cuando se llene la primera línea, se debe seguir imprimiendo en la segunda línea. 
  Cuando se llene tood el display, se debe comenzar a sobreescribir la primera línea.*/

#include <16f877.h> //Microcontrolador
#fuses XT, NOWDT, NOPROTECT, NOLVP  //Características del PIC
#use delay(clock=4Mhz)  //Frecuencia
#include <lcd.c>  //Librería de la LCD
#use standard_io(A) //Definición del comportamiento de los puertos (Puerto A son las filas)
#use standard_io(E) //Puerto E son las columnas

char leerChar(void);  //Declaración de la función que lee el caracter

void main(){
   char k;    //Variable que almacena los caracteres
   int cont=0;  //Variable contador (posición en x)
   lcd_init();   //Inicializa la LCD
   while(TRUE){
      k=leerChar();   
      if(k!=0){   //Si se detecta pulsación
         lcd_putc(k);
         cont++;   
         delay_ms(300);
      }
      if(cont==16) lcd_gotoxy(1,2);   //Si la posición en X llega al borde pasa a la segunda línea
      if(cont==32){    //Si llega al final se reinicia la posición
         cont=0;       //Se reinicia el contador
         lcd_gotoxy(1,1);
      }
   }
}

char leerChar(void){     //Función que detecta los caracteres
   output_A(0x01);       //Enciende la primera fila
   if(input(PIN_E0)==1){  //Identifica la columna
      output_A(0x00);     //Evita el rebote
      return '1';
   }
   if(input(PIN_E1)==1){
      output_A(0x00);
      return '2';
   }
   if(input(PIN_E2)==1){
      output_A(0x00);
      return '3';
   }
   output_A(0x02);        //Enciende la segunda fila
   if(input(PIN_E0)==1){
      output_A(0x00);
      return '4';
   }
   if(input(PIN_E1)==1){
      output_A(0x00);
      return '5';
   }
   if(input(PIN_E2)==1){
      output_A(0x00);
      return '6';
   }
   output_A(0x04);       //Enciende la tercera fila
   if(input(PIN_E0)==1){
      output_A(0x00);
      return '7';
   }
   if(input(PIN_E1)==1){
      output_A(0x00);
      return '8';
   }
   if(input(PIN_E2)==1){
      output_A(0x00);
      return '9';
   }
   output_A(0x08);        //Enciende la cuarta fila
   if(input(PIN_E0)==1){
      output_A(0x00);
      return '*';
   }
   if(input(PIN_E1)==1){
      output_A(0x00);
      return '0';
   }
   if(input(PIN_E2)==1){
      output_A(0x00);
      return '#';
   }
   return '\0';        //Si no se pulsa nada retorna a cero
}

