 // Copyright (C) 2015 Durali Kiraz
// PIC16F877A için hazırlandı.

#define NO_BIT_DEFINES
#include <pic14regs.h> //Mikrodenetleyici Ayar adreslerini ve seçenekleri içerir
//#include <stdint.h> //uint16_t tanımı için gerekliydi. Şimdi ise tipi kendimiz tanımladık.

typedef unsigned short int uint16_t;

//sigorta tanımlarımızı yapıyoruz.
__code uint16_t __at _CONFIG __configword =
_FOSC_XT &&
_WDT_OFF &&
_BOREN_OFF && //Brown Out Reset (BOR) Disable
_LVP_OFF;

#define LED_PORT PORTBbits.RB0
#define BUTON PORTAbits.RA0
#define TRIS_A0 TRISAbits.TRISA0
#define TRIS_B0 TRISBbits.TRISB0


void main(void)
{
   ADCON1 = 0x07; //PortA yi dijital olarak yönlendirdik.
   TRIS_A0 = 1; //A0 giriş olarak seçildi.
   TRIS_B0 = 0; //B0 çıkış olarak seçildi.

   LED_PORT = 0; // LED sönük
   BUTON = 0; // Buton pasif

   while(1)
   {
      LED_PORT = BUTON;
   }

}
