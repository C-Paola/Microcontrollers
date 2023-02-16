/*Generar una señal PWM utilizando el módulo CCP. El ciclo de trabajo debe ser
  ingresado en porcentaje a través de un teclado matricial y además debe ser 
  visualizado en una LCD de doble línea. La frecuencia de la señal PWM debe ser 
  de 1kHz.*/

#include <16f877.h>
#fuses XT, NOWDT
#use delay(clock = 4MHz)
#include <lcd.c>
#include <kbd.c>

int32 duty = 512, uni, dec, n;
char k;

void main(){
   lcd_init();
   kbd_init();
   port_b_pullups(TRUE);
   setup_timer_2(T2_DIV_BY_4,250,1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(duty);
   setup_ccp2(CCP_COMPARE_RESET_TIMER);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   set_timer1(0);
   ccp_2 = 1000;
   lcd_putc("Duty(%): ");
   while(TRUE){
      k = kbd_getc();
      if(k!=0){
         lcd_putc("\fDuty(%): ");
         if(k=='*' || k=='#'){
            do{
            k = kbd_getc();
            } while(k==0 || k=='*' || k=='#');
         }
         lcd_putc(k);
         dec = k-48;
         do{
            k = kbd_getc();
         } while(k==0 || k=='*' || k=='#');
         lcd_putc(k);
         uni = k-48;
         n = 10*dec+uni;
         duty = (n*1000)/99;
         set_pwm1_duty(duty);
         printf(lcd_putc,"\nDuty: %ld",duty);}
   }
} 



