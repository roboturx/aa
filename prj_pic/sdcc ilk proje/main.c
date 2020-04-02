 #include "16f877.h"
typedef unsigned int config;
// PIC konfigurasyonları yapılıyor.
config at 0x2007 __CONFIG =_RC_OSC & _PWRTE_ON & _BODEN_OFF
& _WDT_OFF & _LVP_OFF;

void main( ) // ana fonksiyonumuz
{
    TRISB2 = 1 ; // B portunun 2.pini dijital giriş olarak ayarlandı.
    TRISB1 = 0 ; // B portunun 1 pini dijital çıkış olarak ayarlandı.
    while(1) // Sonsuz döngüye giriliyor.
   {
        RB1 =RB2 ; // RB1,RB2 'ye eşitleniyor
   }
}
