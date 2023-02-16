/*Realizar un menú de control mediante un pulsador. El programa debe mostrar en un 
  displaY LCD (2X16) un menú de 3 funciones. Mediante el pulsador se debe seleccionar
  uno de los 3 elementos y con otro ejecutar la función (encender un led)*/
#include <16f877.h> // Microcontrolador
#fuses XT, NOWDT // características del microcontrolador
#use delay(clock = 4MHz) // Frecuencia de trabajo
#include <lcd.c> // Librería de la LCD
#use standard_io(C) //se ajusta el registro TRIS automáticamente, (seleccionar automáticamente las entradas y salidas)
#use standard_io(A) //se ajusta el registro TRIS automáticamente, (seleccionar automáticamente las entradas y salidas)

void run_func(int numfunc); //Inicializa la función que corre las funciones de abajo
void medir(void); //inicializa la función medir (No retorna ni recibe nada, solo encender un LED)
void calibrar(void); //inicializa la función calibrar (No retorna ni recibe nada, solo encender un LED)
void inicializar(void); //inicializa la función inicializar (No retorna ni recibe nada, solo encender un LED)

void main(){
   int item = 1; //la selección comienza en 1 (medir, calibrar inicializar)
   lcd_init(); //Enciende la LCD
   while (TRUE) {
      if(input(PIN_A0) == 1){ //Cuando se presiona el botón se pasa a la posición siguiente
         item++; //suma posiciones
         delay_ms(200); //tiempo de espera entre cada cambio
         lcd_putc('\f'); //elimina lo que hay antes de cada cambio en la pantalla de la LCD
      }
      if(item == 4)  item = 1; //Cuando se haya seleccionado la ultima función vuelve a la primera.
      
      switch(item){  //Menú
         case 1: printf(lcd_putc,"MEDIR"); //Se visualiza "MEDIR" en la LCD
                 lcd_gotoxy(1,1); //Posición en la que se muestra "MEDIR"
                 break;
         case 2: printf(lcd_putc,"CALIBRAR"); //Se visualiza "CALIBRAR" en la LCD
                 lcd_gotoxy(1,1); //Posición en la que se muestra "CALIBRAR"
                 break;
         case 3: printf(lcd_putc,"INICIALIZAR"); //Se visualiza "INICIALIZAR" en la LCD
                 lcd_gotoxy(1,1); //Posición en la que se muestra "INICIALIZAR"
                 break;
      }
      if(input(PIN_A1)==1){  //Se activa el otro pulsador
         delay_ms(200); //Tiempo de espera
         run_func(item); //Se ejecuta la función que controla item
      }
   }
}

void run_func(item){ //Función que ejecuta las funciones medir, calibrar e inicializar
   switch(item){ //se crea un menú
      case 1: medir(); //llama a la función medir
              break;
      case 2: calibrar(); //llama a la función calibrar
              break;
      case 3: inicializar(); //llama a la función inicilizar
              break;
   }
}

void medir(void){ //función medir
   output_toggle(PIN_C0); //Enciende un led conectado al pin C0
}
void calibrar(void){ //función calibrar
   output_toggle(PIN_C1); //Enciende un led conectado al pin C1
}
void inicializar(void){ //función inicializar
   output_toggle(PIN_C2); //Enciende un led conectado al pin C2
}
