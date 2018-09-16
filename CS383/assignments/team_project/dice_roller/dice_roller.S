#include "avr/io.h"
#include <avr/interrupt.h>
#include <avr/portpins.h>

.text
.global loop
.global setup
.global inc
.global num
.global timer
.global res
.global one
.global two
.global three
.global four
.global five
.global six

setup:
  ldi r25, 4 
  ldi 21, 1 // Change light
  clr r20 // status of pin13
  clr r16
  sts DDRD, r16 //input
  ser r16
  sts DDRB, r16 
  ldi r16, 0b00100000
  sts PORTB, r16
  sei
  ldi r16, 0b00000001
  sts EIMSK, r16  
  ldi r16, 0b00000011
  sts EICRA, r16 

loop:
   rjmp loop

inc:
  call timer
  dec r25
  cpi r25,0
  brne inc
  ret   

res:
  ldi r17, 0b00000000
  sts PORTB, r17
  ret

num:
    lds r20, PORTB
    cpi r21, 1    
    breq one
    cpi r21, 2    
    breq two
    cpi r21, 3    
    breq three
    cpi r21, 4    
    breq four
    cpi r21, 5   
    breq five
    cpi r21, 6    
    breq six
    clr r16
    sts PORTB, r16
    reti

one:
  ldi r17, 0b00000001
  sts PORTB, r17
  call inc
  call res
  rjmp setup

two:
  ldi r17, 0b00000010
  sts PORTB, r17
  call inc
  call res
  rjmp setup

three:
 ldi r17, 0b00000011
 sts PORTB, r17
 call inc
 call res
 rjmp setup

four:
  ldi r17, 0b00000110
  sts PORTB, r17
  call inc
  call res
  rjmp setup

five:
  ldi r17, 0b00000111
  sts PORTB, r17
  call inc
  call res
  rjmp setup

six:
  ldi r17, 0b00001111
  sts PORTB, r17
  call inc
  rjmp setup
  

timer:
  LDI R17, 32
  L4: LDI R23, 200
  L5: LDI R22, 250
  L6:
    NOP
    NOP
    DEC R19
    BRNE L6
    DEC R18
    BRNE L5
    DEC R17
    BRNE L4    
  ret

