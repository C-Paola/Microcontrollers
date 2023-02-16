/*A través de un teclado, introducir los datos de velocidad de un motor y generar 
una señal modulada en ancho de pulso proporcional al dato de la velocidad. */

#include <16f877.h> //Microcontrolador
#fuses XT, NOWDT //Características del PIC
#use delay(clock = 4MHz) //Frecuencia
#use standard_io(B) //Define automáticamente el puerto B (Entradas o salidas)
#use standard_io(A) //Define automáticamente el puerto A (Entradas o salidas)
#include <kbd.c> //Librería del teclado

void main(){
   char k,aux='0'; //Define una variable para el almacenamiento de los caracteres y una variable auxiliar
   int veloc; //Variable velocidad
   long PWML, PWMH; //Tiempo en el que estará en alto o bajo el pulso
   kbd_init(); //Inicializa el teclado
   port_b_pullups(true); //Define los pines del puerto B para usar botones
   while(true){
      k = kbd_getc(); //Recibe el caracter y lo almacena (solo el último)
      if(k==0) k=aux; //Si no se presiona nada k es igual al último dígito seleccionado
      if(k == '*' || k == '#') k = '0'; //Si se oprime '#' o '*' eso equivale a '0' también
      aux=k; //Almacena el último dígito presionado
      veloc=k-48; //Cálculo de la velocidad (de char a ascii)
      PWMH=(long)veloc*111; //Cálculo de tiempo en high (dependiendo de las gráficas)
      PWML=1000-PWMH; //Tiempo en low
      output_high(PIN_A0); //Envía un 1 lógico al osciloscopio
      delay_us(PWMH); //Tiempo de high
      output_low(PIN_A0); //Envía un cero lógico al osciloscopio
      delay_us(PWML); //Tiempo de low
   }
}
