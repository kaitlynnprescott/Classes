#include "avr/io.h"
#include <avr/portpins.h>


.global loop
.global setup
.global five
.global two
.global red
.global yellow
.global green


setup:
  ldi r16, 0xFF
  sts DDRB, r16
  

loop:
  // red
  call red
  // green
  call green
  // yellow
  call yellow

  jmp loop


five:
  // this is the ten second delay for red
  ldi r17,250
  L001: ldi r18,255
  L002: ldi r19,255
  L003:
    NOP
    NOP
    DEC r19
    BRNE L003
    DEC r18
    BRNE L002
    DEC r17
    BRNE L001
  ret


two:
  // this is the two second delay for yellow
  ldi r17,250
  L004: ldi r18,175
  L005: ldi r19,175
  L006:
    NOP
    NOP
    DEC r19
    BRNE L006
    DEC r18
    BRNE L005
    DEC r17
    BRNE L004
  ret

red:
  // this turns on red for 10 seconds
  ldi r16, 0b00100000
  sts PORTB, r16
  call five
  call five
  ldi r17, 0x00
  sts PORTB, r17
ret

yellow:
  // this turns on yellow for 2 seconds
  ldi r16, 0b00001000
  sts PORTB, r16
  call two
  ldi r17, 0x00
  sts PORTB, r17
ret

green:
  // this turns on green for 7 seconds
  ldi r16, 0b00010000
  sts PORTB, r16
  call five
  call two
  ldi r17, 0x00
  sts PORTB, r17
ret


