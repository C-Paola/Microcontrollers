/*Realizar una aplicación con dos microcontroldores PIC16F877. Cada PIC debe tener 
  un teclado matricial y un LCD de doble línea. La aplicación debe permitir la 
  transmisión bidireccional de datos a través del USART en modo asíncrono. A través
  del teclado matricial se debe ingresar un caracter (usar la metología de los 
  teléfonos móviles de 2G). En la primera línea del LCD se debe mostrar el caracter
  ingresado (solo mostrar un caracter, sobreescribir el caracter anterior); cuando
  se presione la tecla '#' se debe transmitir el dato e imprimirlo en la segunda 
  línea del LCD del PIC receptor.*/

#include <16f877.h>
#fuses XT, NOWDT
#use delay(clock=4MHz)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7,bits=8)
#include <lcd.c>
#include <kbd.c>

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

int recibido, pulso=0;
char k, kaux, last;
int1 read = 0;

void lectura(char k);

#int_RDA
void RDA(){
   recibido=getc();
   read = 1; 
}

void main(){
   set_tris_c(0x80);
   lcd_init();
   kbd_init();
   port_b_pullups(TRUE);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   printf(lcd_putc,"Transmitido: \nRecibido: ");
   while(TRUE){
      k=kbd_getc();
      if(k!=0){
         if(k=='#'){
            putc(last);  
         }
         if(k!='#'){
            if(k!=kaux) pulso=0;
            lectura(k);
            lcd_gotoxy(14,1);
            lcd_putc(last);
            kaux=k;
         }
      }
      if(read==1) {
         lcd_gotoxy(11,2);
         lcd_putc(recibido);
         read=0;
      }
   }
}

void lectura(char k ){
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
   }
}

void t1(void){  //Imprime 'uno' y se almacena el caracter en la variable 'last'
   last = uno[pulso];
}
void t2(void){  //Imprime 'dos' y se almacena el caracter en la variable 'last'
   last = dos[pulso];
   pulso++; //Se recorre el vector 'dos'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t3(void){  //Imprime 'tres' y se almacena el caracter en la variable 'last'
   last = tres[pulso];
   pulso++; //Se recorre el vector 'tres'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
}
void t4(void){  //Imprime 'cuatro' y se almacena el caracter en la variable 'last'
   last = cuatro[pulso];
   pulso++; //Se recorre el vector 'cuatro'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t5(void){  //Imprime 'cinco' y se almacena el caracter en la variable 'last'
   last = cinco[pulso];
   pulso++; //Se recorre el vector 'cinco'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t6(void){  //Imprime 'seis' y se almacena el caracter en la variable 'last'
   last = seis[pulso];
   pulso++; //Se recorre el vector 'seis'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t7(void){  //Imprime 'siete' y se almacena el caracter en la variable 'last'
   last = siete[pulso];
   pulso++; //Se recorre el vector 'siete'
   if(pulso==5) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t8(void){  //Imprime 'ocho' y se almacena el caracter en la variable 'last'
   last = ocho[pulso];
   pulso++; //Se recorre el vector 'ocho'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t9(void){  //Imprime 'nueve' y se almacena el caracter en la variable 'last'
   last = nueve[pulso];
   pulso++; //Se recorre el vector 'nueve'
   if(pulso==5) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t0(void){  //Imprime 'cero' y se almacena el caracter en la variable 'last'
   last = cero[pulso];
   pulso++; //Se recorre el vector 'cero'
   if(pulso==2) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void tasterisco(void){  //Imprime 'asterisco' y se almacena el caracter en la variable 'last'
   last = asterisco[pulso];
}
