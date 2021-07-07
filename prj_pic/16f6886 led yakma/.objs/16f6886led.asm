;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"16f6886led.c"
	list	p=16f877a
	radix dec
	include "p16f877a.inc"
;--------------------------------------------------------
; config word(s)
;--------------------------------------------------------
	__config 0x0
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_TRISBbits
	extern	_PORTBbits
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main
	global	_delay

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
UDL_16f6886led_0	udata
r0x1001	res	1
r0x1000	res	1
r0x1002	res	1
r0x1003	res	1
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
code_16f6886led	code
;***
;  pBlock Stats: dbName = M
;***
;has an exit
;functions called:
;   _delay
;   _delay
;   _delay
;   _delay
;1 compiler assigned register :
;   STK00
;; Starting pCode block
S_16f6886led__main	code
_main:
; 2 exit points
;	.line	31; "16f6886led.c"	LED_TRIS = 0; // Pin çıkış olarak ayarlandı
	BANKSEL	_TRISBbits
	BCF	_TRISBbits,0
;	.line	32; "16f6886led.c"	LED_PORT = 0; // LED sönük
	BANKSEL	_PORTBbits
	BCF	_PORTBbits,0
_00126_DS_:
;	.line	35; "16f6886led.c"	LED_PORT = 1; // LED Yanıyor
	BANKSEL	_PORTBbits
	BSF	_PORTBbits,0
;	.line	36; "16f6886led.c"	delay(30000); // ~500ms @ 4MHz 3 sn bekle
	MOVLW	0x30
	MOVWF	STK00
	MOVLW	0x75
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	37; "16f6886led.c"	LED_PORT = 0; // LED Sönük
	BANKSEL	_PORTBbits
	BCF	_PORTBbits,0
;	.line	38; "16f6886led.c"	delay(30000); // ~500ms @ 4MHz 3 sn bekle
	MOVLW	0x30
	MOVWF	STK00
	MOVLW	0x75
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
	GOTO	_00126_DS_
;	.line	40; "16f6886led.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;5 compiler assigned registers:
;   r0x1000
;   STK00
;   r0x1001
;   r0x1002
;   r0x1003
;; Starting pCode block
S_16f6886led__delay	code
_delay:
; 2 exit points
;	.line	19; "16f6886led.c"	void delay(uint16_t milisaniye)
	BANKSEL	r0x1000
	MOVWF	r0x1000
	MOVF	STK00,W
	MOVWF	r0x1001
;	.line	22; "16f6886led.c"	for (i = 0; i < milisaniye; i++)
	CLRF	r0x1002
	CLRF	r0x1003
_00107_DS_:
	BANKSEL	r0x1000
	MOVF	r0x1000,W
	SUBWF	r0x1003,W
	BTFSS	STATUS,2
	GOTO	_00120_DS_
	MOVF	r0x1001,W
	SUBWF	r0x1002,W
_00120_DS_:
	BTFSC	STATUS,0
	GOTO	_00109_DS_
;;genSkipc:3307: created from rifx:0x7ffe052b1310
	nop	
;	.line	22; "16f6886led.c"	for (i = 0; i < milisaniye; i++)
	BANKSEL	r0x1002
	INCF	r0x1002,F
	BTFSC	STATUS,2
	INCF	r0x1003,F
	GOTO	_00107_DS_
_00109_DS_:
;	.line	27; "16f6886led.c"	}
	RETURN	
; exit point of _delay


;	code size estimation:
;	   32+   11 =    43 instructions (  108 byte)

	end
