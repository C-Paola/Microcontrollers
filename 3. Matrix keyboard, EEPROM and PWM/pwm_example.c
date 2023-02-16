/*A trav�s de un teclado, introducir los datos de velocidad de un motor y generar 
una se�al modulada en ancho de pulso proporcional al dato de la velocidad. */

#include <16f877.h> //Microcontrolador
#fuses XT, NOWDT //Caracter�sticas del PIC
#use delay(clock = 4MHz) //Frecuencia
#use standard_io(B) //Define autom�ticamente el puerto B (Entradas o salidas)
#use standard_io(A) //Define autom�ticamente el puerto A (Entradas o salidas)
#include <kbd.c> //Librer�a del teclado

void main(){
   char k,aux='0'; //Define una variable para el almacenamiento de los caracteres y una variable auxiliar
   int veloc; //Variable velocidad
   long PWML, PWMH; //Tiempo en el que estar� en alto o bajo el pulso
   kbd_init(); //Inicializa el teclado
   port_b_pullups(true); //Define los pines del puerto B para usar botones
   while(true){
      k = kbd_getc(); //Recibe el caracter y lo almacena (solo el �ltimo)
      if(k==0) k=aux; //Si no se presiona nada k es igual al �ltimo d�gito seleccionado
      if(k == '*' || k == '#') k = '0'; //Si se oprime '#' o '*' eso equivale a '0' tambi�n
      aux=k; //Almacena el �ltimo d�gito presionado
      veloc=k-48; //C�lculo de la velocidad (de char a ascii)
      PWMH=(long)veloc*111; //C�lculo de tiempo en high (dependiendo de las gr�ficas)
      PWML=1000-PWMH; //Tiempo en low
      output_high(PIN_A0); //Env�a un 1 l�gico al osciloscopio
      delay_us(PWMH); //Tiempo de high
      output_low(PIN_A0); //Env�a un cero l�gico al osciloscopio
      delay_us(PWML); //Tiempo de low
   }
}
