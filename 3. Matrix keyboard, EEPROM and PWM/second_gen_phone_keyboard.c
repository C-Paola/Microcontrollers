/*Realice una aplicación con un teclado matricial y un LCD de doble línea que 
permita escribir texto en el LCD de la misma forma como se escribía texto en los
celulares de segunda generación (también debe tener la opción de escribir números). 
Cuando se escriba "clc" se debe borrar el display. Cuando llegue al final de la 
primera línea, debe seguir escribiendo en la segunda línea. Cuando llegue al final
de la segunda línea debe sobreescribir lo que esté en la primera línea. */

#include <16f877.h> //Microcontrolador
#fuses XT,NOWDT,NOPROTECT,NOLVP //Características del PIC
#use delay(clock=4Mhz) //Frecuencia del PIC
#include <lcd.c> //Librería de la LCD
#include <kbd.c> //librería del teclado matricial

int1 cont=0;         //Variable que verifica que haya pasado un segundo
int1 Inicio=0;       //Variable que el código se haya ejecutado una vez
int pulso=0;         //Variable que recorre cada vector
char k, aux, aux1, aux2, aux3, last;  //Variables para manipular los caracteres
int x=1, xaux=0;     //Variables de posición
int y=1;
int1 flag=0, reset=0;  //Banderas

void clc(void);      //Función que elimina la pantalla

#INT_TIMER1
void temp1s(void){   //Función que se ejecuta cuando se desborda el timer
   if(cont==1){      //Se ejecuta cuando pasa un segundo
      pulso = 0;     //Reinicia el recorrido de los vectores
      if(flag == 1){ //Lleva el control de si se ha pulsado una tecla
         x++;          
         flag = 0;   
         clc();
      }
   }
   set_timer1(3036);    //El timer solo cuenta un segundo
   cont++;
}

char uno[1] = {'1'}; //declaracion de caracteres
char dos[4] = {'A','B','C','2'};
char tres[4] = {'D','E','F','3'};
char cuatro[4] = {'G','H','I','4'};
char cinco[4] = {'J','K','L','5'};
char seis[4] = {'M','N','O','6'};
char siete[5] = {'P','Q','R','S','7'};
char ocho[4] = {'T','U','V','8'};
char nueve[5] = {'W','X','Y','Z','9'};
char cero[2] = {' ','0'};
char asterisco[1] = {'*'};
char numeral[1] = {'#'};

void t1(void); //declaración de funciones
void t2(void);
void t3(void);
void t4(void);
void t5(void);
void t6(void);
void t7(void);
void t8(void);
void t9(void);
void t0(void);
void tasterisco(void);
void tnumeral(void);

void main (){
   lcd_init(); //Enciende la LCD
   kbd_init(); //Inicializa el teclado
   port_b_pullups(TRUE); //Activa los botones en el puerto B
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); //Inicialización del timer
   set_timer1(3036); //El timer solo cuenta un segundo
   enable_interrupts(INT_TIMER1);  //Activación de las interrupciones del timer
   enable_interrupts(GLOBAL);      //Activaci+on de las interrupciones globales
   
   while(TRUE) {
      k = kbd_getc(); //Recibe el caracter del teclado
     
      if (k!=0){ //Solo sucede cuando se oprime una tecla
         set_timer1(3036);
         cont=0;
         flag = 1;
         if(aux!=k && Inicio == 1) {   //Se ejecuta a partir del segundo ciclo y cuando la tecla presionada sea diferente a la anterior
            pulso = 0;     //resetea la variable que recorre los vectores
            if(x = xaux) {   //Si la posición en X actual es igual a la posición en X anterior, es decir, el último caracter permanece estable
               x++;
               clc();
            }
         }
         Inicio = 1;   //Indica que se ejecutó una vez el código
         if(reset==1) x=1, y=1, reset=0;   //Si se hizo CLC se reinicia la posición
         if(x==17 && y==1) y=2, x=1, pulso=0;  //Condiciones para cuando los caracteres en la pantalla llegan a los bordes
         if(x==17 && y==2) y=1, x=1, pulso=0;
         lcd_gotoxy(x,y); //Va a la posición X,Y
         switch(k){   //Menú para imprimir la tecla correspondiente
            case '1':
               t1();
               break;
            case '2':
               t2();
               break;
            case '3':
               t3();
               break;
            case '4':
               t4();
               break;
            case '5':
               t5();
               break;
            case '6':
               t6();
               break;
            case '7':
               t7();
               break;
            case '8':
               t8();
               break;
            case '9':
               t9();
               break;
            case '0':
               t0();
               break;
            case '*':
               tasterisco();
               break;
            case '#':
               tnumeral();
               break;
         }
      
         aux = k; //Almacena el último caracter
         xaux = x;  //Almacena la última posición en X
      }
      
   }
}

void t1(void){  //Imprime 'uno' y se almacena el caracter en la variable 'last'
   lcd_putc(uno[0]);
   last = uno[pulso];
}
void t2(void){  //Imprime 'dos' y se almacena el caracter en la variable 'last'
   lcd_putc(dos[pulso]);
   last = dos[pulso];
   pulso++; //Se recorre el vector 'dos'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t3(void){  //Imprime 'tres' y se almacena el caracter en la variable 'last'
   lcd_putc(tres[pulso]);
   last = tres[pulso];
   pulso++; //Se recorre el vector 'tres'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
}
void t4(void){  //Imprime 'cuatro' y se almacena el caracter en la variable 'last'
   lcd_putc(cuatro[pulso]);
   last = cuatro[pulso];
   pulso++; //Se recorre el vector 'cuatro'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t5(void){  //Imprime 'cinco' y se almacena el caracter en la variable 'last'
   lcd_putc(cinco[pulso]);
   last = cinco[pulso];
   pulso++; //Se recorre el vector 'cinco'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t6(void){  //Imprime 'seis' y se almacena el caracter en la variable 'last'
   lcd_putc(seis[pulso]);
   last = seis[pulso];
   pulso++; //Se recorre el vector 'seis'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t7(void){  //Imprime 'siete' y se almacena el caracter en la variable 'last'
   lcd_putc(siete[pulso]);
   last = siete[pulso];
   pulso++; //Se recorre el vector 'siete'
   if(pulso==5) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t8(void){  //Imprime 'ocho' y se almacena el caracter en la variable 'last'
   lcd_putc(ocho[pulso]);
   last = ocho[pulso];
   pulso++; //Se recorre el vector 'ocho'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t9(void){  //Imprime 'nueve' y se almacena el caracter en la variable 'last'
   lcd_putc(nueve[pulso]);
   last = nueve[pulso];
   pulso++; //Se recorre el vector 'nueve'
   if(pulso==5) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t0(void){  //Imprime 'cero' y se almacena el caracter en la variable 'last'
   lcd_putc(cero[pulso]);
   last = cero[pulso];
   pulso++; //Se recorre el vector 'cero'
   if(pulso==2) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void tasterisco(void){  //Imprime 'asterisco' y se almacena el caracter en la variable 'last'
   lcd_putc(asterisco[0]);
   last = asterisco[pulso];
}
void tnumeral(void){  //Imprime 'numeral' y se almacena el caracter en la variable 'last'
   lcd_putc(numeral[0]);
   last = numeral[pulso];
}
void clc(void){
   aux3 = aux2;  //Almacenan los tres últimos caracteres
   aux2 = aux1;
   aux1 = last;
   if(aux3 == 'C' &&  //Si los últimos 3 caracteres almacenados corresponden a 'CLC' se borra la pantalla
      aux2 == 'L' &&
      aux1 == 'C'){
      lcd_putc("\fBorrando...");
      delay_ms(500);
      lcd_putc('\f');
      reset=1;   //Se resetea a la posición inicial para escribir nuevamente;
   }
}
