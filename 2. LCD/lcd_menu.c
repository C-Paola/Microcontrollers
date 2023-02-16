/*Realizar un men� de control mediante un pulsador. El programa debe mostrar en un 
  displaY LCD (2X16) un men� de 3 funciones. Mediante el pulsador se debe seleccionar
  uno de los 3 elementos y con otro ejecutar la funci�n (encender un led)*/
#include <16f877.h> // Microcontrolador
#fuses XT, NOWDT // caracter�sticas del microcontrolador
#use delay(clock = 4MHz) // Frecuencia de trabajo
#include <lcd.c> // Librer�a de la LCD
#use standard_io(C) //se ajusta el registro TRIS autom�ticamente, (seleccionar autom�ticamente las entradas y salidas)
#use standard_io(A) //se ajusta el registro TRIS autom�ticamente, (seleccionar autom�ticamente las entradas y salidas)

void run_func(int numfunc); //Inicializa la funci�n que corre las funciones de abajo
void medir(void); //inicializa la funci�n medir (No retorna ni recibe nada, solo encender un LED)
void calibrar(void); //inicializa la funci�n calibrar (No retorna ni recibe nada, solo encender un LED)
void inicializar(void); //inicializa la funci�n inicializar (No retorna ni recibe nada, solo encender un LED)

void main(){
   int item = 1; //la selecci�n comienza en 1 (medir, calibrar inicializar)
   lcd_init(); //Enciende la LCD
   while (TRUE) {
      if(input(PIN_A0) == 1){ //Cuando se presiona el bot�n se pasa a la posici�n siguiente
         item++; //suma posiciones
         delay_ms(200); //tiempo de espera entre cada cambio
         lcd_putc('\f'); //elimina lo que hay antes de cada cambio en la pantalla de la LCD
      }
      if(item == 4)  item = 1; //Cuando se haya seleccionado la ultima funci�n vuelve a la primera.
      
      switch(item){  //Men�
         case 1: printf(lcd_putc,"MEDIR"); //Se visualiza "MEDIR" en la LCD
                 lcd_gotoxy(1,1); //Posici�n en la que se muestra "MEDIR"
                 break;
         case 2: printf(lcd_putc,"CALIBRAR"); //Se visualiza "CALIBRAR" en la LCD
                 lcd_gotoxy(1,1); //Posici�n en la que se muestra "CALIBRAR"
                 break;
         case 3: printf(lcd_putc,"INICIALIZAR"); //Se visualiza "INICIALIZAR" en la LCD
                 lcd_gotoxy(1,1); //Posici�n en la que se muestra "INICIALIZAR"
                 break;
      }
      if(input(PIN_A1)==1){  //Se activa el otro pulsador
         delay_ms(200); //Tiempo de espera
         run_func(item); //Se ejecuta la funci�n que controla item
      }
   }
}

void run_func(item){ //Funci�n que ejecuta las funciones medir, calibrar e inicializar
   switch(item){ //se crea un men�
      case 1: medir(); //llama a la funci�n medir
              break;
      case 2: calibrar(); //llama a la funci�n calibrar
              break;
      case 3: inicializar(); //llama a la funci�n inicilizar
              break;
   }
}

void medir(void){ //funci�n medir
   output_toggle(PIN_C0); //Enciende un led conectado al pin C0
}
void calibrar(void){ //funci�n calibrar
   output_toggle(PIN_C1); //Enciende un led conectado al pin C1
}
void inicializar(void){ //funci�n inicializar
   output_toggle(PIN_C2); //Enciende un led conectado al pin C2
}
