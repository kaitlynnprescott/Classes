;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Author: Kaitlynn Prescott											;;
;;  Assignment: Bonus													;;
;;  File: bonus_2.asm													;;
;;  Pledge: I pledge my honor that I have abided by						;;
;;          the Stevens Honor System.									;;
;;  Date: 24 Nov 2017													;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 2. Write an assembly program that will reverse a 10-element array	;;
;; stored in memory, using the stack. The elements should start at		;;
;; location 0x0100. Your program should start by loading 10 elements	;;
;; into memory.															;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.include "m328Pdef.inc" 

init:
	ldi r16, 1
	ldi r17, 2
	ldi r18, 3
	ldi r19, 4
	ldi r20, 5
	ldi r21, 6
	ldi r22, 7
	ldi r23, 8
	ldi r24, 9
	ldi r25, 10
	sts 0x0100, r16
	sts 0x0101, r17
	sts 0x0102, r18
	sts 0x0103, r19
	sts 0x0104, r20
	sts 0x0105, r21
	sts 0x0106, r22
	sts 0x0107, r23
	sts 0x0108, r24
	sts 0x0109, r25

main:
	init stack
	lds r1, 0x0100
	push r1
	lds r1, 0x0101
	push r1
	lds r1, 0x0102
	push r1
	lds r1, 0x0103
	push r1
	lds r1, 0x0104
	push r1
	lds r1, 0x0105
	push r1
	lds r1, 0x0106
	push r1
	lds r1, 0x0107
	push r1
	lds r1, 0x0108
	push r1
	lds r1, 0x0109
	push r1

	ser r16
	out DDRB, r16

	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16