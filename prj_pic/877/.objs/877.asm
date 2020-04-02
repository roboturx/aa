;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"877.c"
	list	p=16f877a
	radix dec
	include "p16f877a.inc"
;--------------------------------------------------------
; config word(s)
;--------------------------------------------------------
	__config 0x1
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_ADCON1
	extern	_TRISBbits
	extern	_TRISAbits
	extern	_PORTBbits
	extern	_PORTAbits
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0070
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_877_0	udata
r0x1000	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
;--------------------------------------------------------
; initialized absolute data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_877	code
;***
;  pBlock Stats: dbName = M
;***
;has an exit
;1 compiler assigned register :
;   r0x1000
;; Starting pCode block
S_877__main	code
_main:
; 2 exit points
;	.line	25; "877.c"	ADCON1 = 0x07; //PortA yi dijital olarak yönlendirdik.
	MOVLW	0x07
	BANKSEL	_ADCON1
	MOVWF	_ADCON1
;	.line	26; "877.c"	TRIS_A0 = 1; //A0 giriş olarak seçildi.
	BSF	_TRISAbits,0
;	.line	27; "877.c"	TRIS_B0 = 0; //B0 çıkış olarak seçildi.
	BCF	_TRISBbits,0
;	.line	29; "877.c"	LED_PORT = 0; // LED sönük
	BANKSEL	_PORTBbits
	BCF	_PORTBbits,0
;	.line	30; "877.c"	BUTON = 0; // Buton pasif
	BCF	_PORTAbits,0
_00106_DS_:
;	.line	34; "877.c"	LED_PORT = BUTON;
	BANKSEL	r0x1000
	CLRF	r0x1000
	BANKSEL	_PORTAbits
	BTFSS	_PORTAbits,0
	GOTO	_00001_DS_
	BANKSEL	r0x1000
	INCF	r0x1000,F
_00001_DS_:
	BANKSEL	r0x1000
	RRF	r0x1000,W
	BTFSC	STATUS,0
	GOTO	_00002_DS_
	BANKSEL	_PORTBbits
	BCF	_PORTBbits,0
_00002_DS_:
	BTFSS	STATUS,0
	GOTO	_00003_DS_
	BANKSEL	_PORTBbits
	BSF	_PORTBbits,0
_00003_DS_:
	GOTO	_00106_DS_
;	.line	37; "877.c"	}
	RETURN	
; exit point of _main


;	code size estimation:
;	   19+    8 =    27 instructions (   70 byte)

	end
