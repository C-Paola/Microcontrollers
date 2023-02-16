/*Diseñar una aplicación con un LCD gráfico y un teclado matricial. La aplicación
  debe permitir la visualización de texto en el LCD de acuerdo a la entrada del
  usuario. El ingreso de texto debe hacerse de la misma manera que se hace en los
  teléfonos móviles de 2da generación.*/

#include <16f877A.h>
#fuses HS, NOWDT, NOPROTECT, NOLVP
#use delay (clock=20MHz)
#include <HDM64GS12.c>
#include <graphics.c>

#use standard_io(A)
#use standard_io(E)

int x = 0, xaux = 0; //Variable de posición en el eje X
int y = 0; //Variable de posición en el eje Y
int pulso = 0; //Variable que recorre cada vector
int cont = 0;
int1 flag = 0, inicio = 0; //Banderas
char k, aux; //Variable que almacena las letras
char temp[] = " "; //Vector de caracter temporal para la LCD gráfica

#INT_TIMER1
void temp1s(void){   //Función que se ejecuta cuando se desborda el timer
   if(cont>=10){      //Se ejecuta cuando pasa un segundo, T = 0.1 Seg
      pulso = 0;     //Reinicia el recorrido de los vectores
      if(flag == 1){ //Lleva el control de si se ha pulsado una tecla
         x = x + 7;          
         flag = 0;
      }
   }
   set_timer1(3036);    //El timer solo cuenta un segundo
   cont++;
}

char uno[1] = {'1'}; //Declaracion de caracteres
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

void t1(void); //Declaración de funciones
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

char leerChar(void); //Función del driver del teclado

void main(){
   glcd_init(ON); //Enciende la LCD gráfica
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); //Inicialización del timer
   set_timer1(3036); //El timer solo cuenta un segundo
   enable_interrupts(INT_TIMER1);  //Activación de las interrupciones del timer
   enable_interrupts(GLOBAL);      //Activación de las interrupciones globales
   
   while(TRUE){
      k = leerChar(); //Lee el caracter utilizando el nuevo driver del teclado
      delay_ms(50); //Delay necesario para la ejecución
      if(k!=0){
         set_timer1(3036);
         cont = 0;
         flag = 1;
         if(aux!=k && inicio == 1){
            pulso = 0;
            if(xaux == x) x = x + 7;
         }
         inicio = 1; //Indica que el código ya se ejecutó una vez
         if(x>=120){ //Limitador de los bordes de la pantalla
            x = 0;
            y = y + 8;
         }
         if(y>=60){ //Borra la pantalla si se ha llenado de caracteres
            x = 0;
            y = 0;
            glcd_fillScreen(OFF);
         }
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
         aux = k; //Almacena el último dígito oprimido del teclado
         xaux = x; //Almacena la última posición en X
         glcd_rect(x,y,(x+5),(y+7),YES,OFF);
         glcd_text57(x,y,temp,1,ON);
      }
   }
}

void t1(void){  //Imprime 'uno'
   temp[0] = uno[0];
}
void t2(void){  //Imprime 'dos' 
   temp[0] = dos[pulso];
   pulso++; //Se recorre el vector 'dos'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t3(void){  //Imprime 'tres'
   temp[0] = tres[pulso];
   pulso++; //Se recorre el vector 'tres'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
}
void t4(void){  //Imprime 'cuatro'
   temp[0] = cuatro[pulso];
   pulso++; //Se recorre el vector 'cuatro'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t5(void){  //Imprime 'cinco'
   temp[0] = cinco[pulso];
   pulso++; //Se recorre el vector 'cinco'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t6(void){  //Imprime 'seis'
   temp[0] = seis[pulso];
   pulso++; //Se recorre el vector 'seis'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t7(void){  //Imprime 'siete'
   temp[0] = siete[pulso];
   pulso++; //Se recorre el vector 'siete'
   if(pulso==5) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t8(void){  //Imprime 'ocho'
   temp[0] = ocho[pulso];
   pulso++; //Se recorre el vector 'ocho'
   if(pulso==4) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t9(void){  //Imprime 'nueve'
   temp[0] = nueve[pulso];
   pulso++; //Se recorre el vector 'nueve'
   if(pulso==5) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void t0(void){  //Imprime 'cero'
   temp[0] = cero[pulso];
   pulso++; //Se recorre el vector 'cero'
   if(pulso==2) pulso = 0;  //Si llega al límite del vector se reinicia
} 
void tasterisco(void){  //Imprime 'asterisco'
   temp[0] = asterisco[pulso];
}
void tnumeral(void){  //Imprime 'numeral'
   temp[0] = numeral[pulso];
}


//DRIVER DEL TECLADO

char leerChar(void){     //Función que detecta los caracteres
   output_A(0x01);       //Enciende la primera fila
   if (input(PIN_E0)==1){   //Identifica la columna
      while(input(PIN_E0)==1);  //Antirebote
      output_A(0x00);
      return '1';
   }
   if (input(PIN_E1)==1){
      while(input(PIN_E1)==1);  //Antirebote
      output_A(0x00);      
      return '2';
   }
   if (input(PIN_E2)==1){
      while(input(PIN_E2)==1);  //Antirebote
      output_A(0x00);
      return '3';
   }
   output_A(0x02); //Enciende la segunda fila
   if (input(PIN_E0)==1){
      while(input(PIN_E0)==1);  //Antirebote
      output_A(0x00);
      return '4';
   }
   if (input(PIN_E1)==1){
      while(input(PIN_E1)==1);  //Antirebote
      output_A(0x00);
      return '5';
   }
   if (input(PIN_E2)==1){
      while(input(PIN_E2)==1);  //Antirebote
      output_A(0x00);
      return '6';
   }
   output_A(0x04); //Enciende la tercera fila
   if (input(PIN_E0)==1){
      while(input(PIN_E0)==1);  //Antirebote
      output_A(0x00);
      return '7';
   }
   if (input(PIN_E1)==1){
      while(input(PIN_E1)==1);  //Antirebote
      output_A(0x00);
      return '8';
   }
   if (input(PIN_E2)==1){
      while(input(PIN_E2)==1);  //Antirebote
      output_A(0x00);
      return '9';
   }
   output_A(0x08); //Enciende la cuarta fila
   if (input(PIN_E0)==1){
      while(input(PIN_E0)==1);  //Antirebote
      output_A(0x00);
      return '*';
   }
   if (input(PIN_E1)==1){
      while(input(PIN_E1)==1);  //Antirebote
      output_A(0x00);
      return '0';
   }
   if (input(PIN_E2)==1){
      while(input(PIN_E2)==1);  //Antirebote
      output_A(0x00);
      return '#';
   }
   return '\0'; //Si no se pulsa nada retorna a cero
}
