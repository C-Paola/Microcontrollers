/*Leer dos entradas análogicas en el rango entre los 0V y 5V. Se debe mostrar en 
  una pantalla LCD diferentes avisos de acuerdo a los rangos como se describe a 
  continuación.
  |         ENTRADA 1           |        ENTRADA 2         |
  |  RANGO   |      MENSAJE     |   RANGO     |   MENSAJE  |
  |   0-2v   |    Baja señal    |   0-3.2v    |   Alerta   |
  |   2-4v   |        Ok        |  3.2-3.5v   |     Ok     |
  |   4-5v   |    Alta señal    |   3.5-5v    |   Detener  |
  
  Se debe encender un LED cuando la entrada 1 tenga baja señal o cuando la entrada
  2 sea "detener".*/
  
#include <16f877.h>
#device adc = 10
#fuses XT, NOWDT
#use delay(clock = 4MHz)
#include <lcd.c>
  
long senal1, senal2;
float sen1, sen2;

void main(){
   lcd_init();
   setup_port_a(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   while(TRUE){
      set_adc_channel(1);
      delay_us(20);
      senal1 = read_adc();
      sen1 = 5.0*senal1/1023.0;
      delay_ms(100);
      set_adc_channel(2);
      delay_us(20);
      senal2 = read_adc();
      sen2 = 5.0*senal2/1023.0;
      delay_ms(100);
      lcd_gotoxy(1,1);
      if (sen1>=0 && sen1<2){
         lcd_putc("\fSen1: Baja senal");
      } else if (sen1>=2 && sen1<4){
         lcd_putc("\fSen1: Ok");
      } else lcd_putc("\fSen1: Alta senal");
      lcd_gotoxy(1,2);
      if (sen2>=0 && sen2<3.2){
         lcd_putc("Sen2: Alerta");
      } else if (sen2>=3.2 && sen2<3.5){
         lcd_putc("Sen2: Ok");
      } else lcd_putc("Sen2: Detener");
      if ((sen1<2)||(sen2>=3.5)){
         output_high(PIN_B1);
      } else output_low(PIN_B1);
      delay_ms(100);
   }
}
