;-------------------------------------------------------------------------------
; Motors.inc - Control 2 brushed DC motors with this macro library for the
; PIC16F8XXA range of microcontrollers.
; Written by: Travis Montoya
;
; Pinout is using a L293D, Enable pins are connected as follows:
; M1 = CCP1 = RC2
; M2 = CCP2 = RC1
; Control lines for Motor 1 and Motor 2 are as follows:
; M1 = 4A = RA0
;    = 3A = RA1
; M2 = 1A = RA2
;    = 2A = RA3
;-------------------------------------------------------------------------------

SetUpMotors MACRO
    BCF STATUS,RP0
    BCF STATUS,RP1 ; Bank 0
    CLRF PORTA     ; Clear output latches
    MOVLW 0x06     ; Turn off A2D
    MOVWF ADCON1   ;
    MOVLW 0x00     ; Output
    MOVWF TRISA    ;

;-------------------------------------------------------------------------------
; Here we actually set up the PWM now for CCP1 and CCP2
;-------------------------------------------------------------------------------

    MOVF CCP1CON,W ; Set CCP1 as PWM
    ANDLW 0xF0
    IORLW 0x0C
    MOVWF CCP1CON
    MOVF CCP2CON,W
    ANDLW 0xF0
    IORLW 0x0C
    MOVWF CCP2CON  ; Set CCP2 as PWM

    MOVLW 126      ; PWM value
    BSF STATUS,RP0 ; Bank 1
    MOVWF PR2
    BCF STATUS,RP0 ; Bank 0
    MOVF T2CON,W   ; 16 Prescaler
    ANDLW 0xF8     ; PWM at 2500Hz
    IORLW 0x02
    MOVWF T2CON

    MOVLW 0x00     ; Set PWM1 and PWM2 to 0 (OFF)
    MOVWF CCPR1L
    MOVLW 0x00
    MOVWF CCPR2L
    BSF T2CON,TMR2ON  ; Enable timer (Start PWM)
    RETURN

SetSpeed MACRO m1,m2
