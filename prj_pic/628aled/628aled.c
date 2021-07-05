 // Copyright (C) 2015 Durali Kiraz
// PIC16F628A için hazırlandı.

#define NO_BIT_DEFINES
#include <pic14regs.h> //Mikrodenetleyici Ayar adreslerini ve seçenekleri içerir
#include <stdint.h> //uint16_t tanımı için gerekli

//Dahil osilatörü kullanacak ve osilatör portları giriş çıkış amaçlı kullanacağım
//Watch Dog Timer devredışı
//Düşük voltaj programlaması devre dışı.
// Bu ayarlanmış sigorta ayarlarının dışında kalanlar varsayılan ayarlar olacaktır.

//__code uint16_t __at _CONFIG __configword = _INTRC_OSC_NOCLKOUT && _WDTE_OFF && _LVP_OFF;
__code uint16_t __at (0x2007) __configword =  _WDTE_OFF && _LVP_OFF;

//Not: Yukardaki sigorta ayarları pic16f628a ya özel oluşturuldu.

#define LED1_PORT PORTBbits.RB1
#define LED1_TRIS TRISBbits.TRISB1


#define LED2_PORT PORTAbits.RA1
#define LED2_TRIS TRISAbits.TRISA1

// kalibrasyonsuz delay, sadece bir dizi döngü yinelemeleri için beklemeyi sağlar.
void delay(uint16_t milisaniye)
{
uint16_t i,j;
for (i = 0; i < milisaniye; i++)
{
// Döngüde optimizasyon için bu asm komutu eklenmiştir.
for (j=0; j < 4; j++)
__asm nop __endasm;
}
}

void main(void){

LED1_TRIS = 0; // Pin çıkış olarak ayarlandı
LED1_PORT = 0; // LED sönük

LED2_TRIS = 0; // Pin çıkış olarak ayarlandı
LED2_PORT = 0; // LED sönük
while(1)
{

LED1_PORT = ! LED2_PORT; // LED Yanıyor
LED2_PORT = ! LED1_PORT;
delay(11000);  // 4 sn bekle
LED1_PORT = 0; // LED Sönük
LED2_PORT = ! LED1_PORT;
delay(50000);  // 4 sn bekle
}

}
