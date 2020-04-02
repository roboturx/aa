 // Copyright (C) 2015 Durali Kiraz

#define NO_BIT_DEFINES
#include <pic14regs.h> //Mikrodenetleyici Ayar adreslerini ve seçenekleri içerir
#include <stdint.h> //uint16_t tanımı için gerekli

// Osilatör seçme bitleri (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN),
// dahili osilatör kullanılacak
// wacthdog timer devredışı
// düşük voltaj programlama devredışı
// Bu tanımların dışında kalan Sigortaların kalanı varsayılan olarak bırakılır.

__code uint16_t __at (_CONFIG1) __configword = _INTRC_OSC_NOCLKOUT && _WDTE_OFF && _LVP_OFF;

#define LED_PORT PORTBbits.RB0
#define LED_TRIS TRISBbits.TRISB0

// kalibrasyonsuz delay, sadece bir dizi döngü yinelemeleri için beklemeyi sağlar.
void delay(uint16_t milisaniye)
{
    uint16_t i;
    for (i = 0; i < milisaniye; i++)
    {
      // Döngüde optimizasyon için bu asm komutu eklenmiştir.
       __asm nop __endasm;
    }
}

void main(void)
{
    LED_TRIS = 0; // Pin çıkış olarak ayarlandı
   LED_PORT = 0; // LED sönük
   while(1)
   {
      LED_PORT = 1; // LED Yanıyor
      delay(30000); // ~500ms @ 4MHz 3 sn bekle
      LED_PORT = 0; // LED Sönük
      delay(30000); // ~500ms @ 4MHz 3 sn bekle
   }
}
