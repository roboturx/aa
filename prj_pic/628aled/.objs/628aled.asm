;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"628aled.c"
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
	extern	_TRISBbits
	extern	_TRISAbits
	extern	_PORTBbits
	extern	_PORTAbits
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
UDL_628aled_0	udata
r0x1001	res	1
r0x1000	res	1
r0x1002	res	1
r0x1003	res	1
r0x1004	res	1
r0x1005	res	1
r0x1006	res	1
r0x1007	res	1
r0x1008	res	1
r0x1009	res	1
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
code_628aled	code
;***
;  pBlock Stats: dbName = M
;***
;has an exit
;functions called:
;   _delay
;   _delay
;   _delay
;   _delay
;3 compiler assigned registers:
;   r0x1008
;   r0x1009
;   STK00
;; Starting pCode block
S_628aled__main	code
_main:
; 2 exit points
;	.line	39; "628aled.c"	LED1_TRIS = 0; // Pin çıkış olarak ayarlandı
	BANKSEL	_TRISBbits
	BCF	_TRISBbits,1
;	.line	40; "628aled.c"	LED1_PORT = 0; // LED sönük
	BANKSEL	_PORTBbits
	BCF	_PORTBbits,1
;	.line	42; "628aled.c"	LED2_TRIS = 0; // Pin çıkış olarak ayarlandı
	BANKSEL	_TRISAbits
	BCF	_TRISAbits,1
;	.line	43; "628aled.c"	LED2_PORT = 0; // LED sönük
	BANKSEL	_PORTAbits
	BCF	_PORTAbits,1
_00138_DS_:
;	.line	47; "628aled.c"	LED1_PORT = ! LED2_PORT; // LED Yanıyor
	BANKSEL	r0x1008
	CLRF	r0x1008
	BANKSEL	_PORTAbits
	BTFSS	_PORTAbits,1
	GOTO	_00001_DS_
	BANKSEL	r0x1008
	INCF	r0x1008,F
_00001_DS_:
	BANKSEL	r0x1008
	MOVF	r0x1008,W
	MOVLW	0x00
	BTFSC	STATUS,2
	MOVLW	0x01
	MOVWF	r0x1009
	MOVWF	r0x1008
	RRF	r0x1008,W
	BTFSC	STATUS,0
	GOTO	_00002_DS_
	BANKSEL	_PORTBbits
	BCF	_PORTBbits,1
_00002_DS_:
	BTFSS	STATUS,0
	GOTO	_00003_DS_
	BANKSEL	_PORTBbits
	BSF	_PORTBbits,1
_00003_DS_:
;	.line	48; "628aled.c"	LED2_PORT = ! LED1_PORT;
	BANKSEL	r0x1008
	CLRF	r0x1008
	BANKSEL	_PORTBbits
	BTFSS	_PORTBbits,1
	GOTO	_00004_DS_
	BANKSEL	r0x1008
	INCF	r0x1008,F
_00004_DS_:
	BANKSEL	r0x1008
	MOVF	r0x1008,W
	MOVLW	0x00
	BTFSC	STATUS,2
	MOVLW	0x01
	MOVWF	r0x1009
	MOVWF	r0x1008
	RRF	r0x1008,W
	BTFSC	STATUS,0
	GOTO	_00005_DS_
	BANKSEL	_PORTAbits
	BCF	_PORTAbits,1
_00005_DS_:
	BTFSS	STATUS,0
	GOTO	_00006_DS_
	BANKSEL	_PORTAbits
	BSF	_PORTAbits,1
_00006_DS_:
;	.line	49; "628aled.c"	delay(11000);  // 4 sn bekle
	MOVLW	0xf8
	MOVWF	STK00
	MOVLW	0x2a
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	50; "628aled.c"	LED1_PORT = 0; // LED Sönük
	BANKSEL	_PORTBbits
	BCF	_PORTBbits,1
;	.line	51; "628aled.c"	LED2_PORT = ! LED1_PORT;
	BANKSEL	r0x1008
	CLRF	r0x1008
	BANKSEL	_PORTBbits
	BTFSS	_PORTBbits,1
	GOTO	_00007_DS_
	BANKSEL	r0x1008
	INCF	r0x1008,F
_00007_DS_:
	BANKSEL	r0x1008
	MOVF	r0x1008,W
	MOVLW	0x00
	BTFSC	STATUS,2
	MOVLW	0x01
	MOVWF	r0x1009
	MOVWF	r0x1008
	RRF	r0x1008,W
	BTFSC	STATUS,0
	GOTO	_00008_DS_
	BANKSEL	_PORTAbits
	BCF	_PORTAbits,1
_00008_DS_:
	BTFSS	STATUS,0
	GOTO	_00009_DS_
	BANKSEL	_PORTAbits
	BSF	_PORTAbits,1
_00009_DS_:
;	.line	52; "628aled.c"	delay(50000);  // 4 sn bekle
	MOVLW	0x50
	MOVWF	STK00
	MOVLW	0xc3
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
	GOTO	_00138_DS_
;	.line	55; "628aled.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;9 compiler assigned registers:
;   r0x1000
;   STK00
;   r0x1001
;   r0x1002
;   r0x1003
;   r0x1004
;   r0x1005
;   r0x1006
;   r0x1007
;; Starting pCode block
S_628aled__delay	code
_delay:
; 2 exit points
;	.line	26; "628aled.c"	void delay(uint16_t milisaniye)
	BANKSEL	r0x1000
	MOVWF	r0x1000
	MOVF	STK00,W
	MOVWF	r0x1001
;	.line	29; "628aled.c"	for (i = 0; i < milisaniye; i++)
	CLRF	r0x1002
	CLRF	r0x1003
_00111_DS_:
	BANKSEL	r0x1000
	MOVF	r0x1000,W
	SUBWF	r0x1003,W
	BTFSS	STATUS,2
	GOTO	_00132_DS_
	MOVF	r0x1001,W
	SUBWF	r0x1002,W
_00132_DS_:
	BTFSC	STATUS,0
	GOTO	_00113_DS_
;;genSkipc:3307: created from rifx:0x7ffd6633f3b0
;	.line	32; "628aled.c"	for (j=0; j < 4; j++)
	MOVLW	0x04
	BANKSEL	r0x1004
	MOVWF	r0x1004
	CLRF	r0x1005
_00109_DS_:
	nop	
	MOVLW	0xff
	BANKSEL	r0x1004
	ADDWF	r0x1004,W
	MOVWF	r0x1006
	MOVLW	0xff
	MOVWF	r0x1007
	MOVLW	0x00
	BTFSC	STATUS,0
	INCFSZ	r0x1005,W
	ADDWF	r0x1007,F
	MOVF	r0x1006,W
	MOVWF	r0x1004
	MOVF	r0x1007,W
	MOVWF	r0x1005
;	.line	32; "628aled.c"	for (j=0; j < 4; j++)
	MOVF	r0x1007,W
	IORWF	r0x1006,W
	BTFSS	STATUS,2
	GOTO	_00109_DS_
;	.line	29; "628aled.c"	for (i = 0; i < milisaniye; i++)
	INCF	r0x1002,F
	BTFSC	STATUS,2
	INCF	r0x1003,F
	GOTO	_00111_DS_
_00113_DS_:
;	.line	35; "628aled.c"	}
	RETURN	
; exit point of _delay


;	code size estimation:
;	  104+   31 =   135 instructions (  332 byte)

	end
