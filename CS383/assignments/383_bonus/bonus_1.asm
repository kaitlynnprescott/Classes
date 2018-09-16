;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Author: Kaitlynn Prescott											;;
;;  Assignment: Bonus													;;
;;  File: bonus_2.asm													;;
;;  Pledge: I pledge my honor that I have abided by						;;
;;          the Stevens Honor System.									;;
;;  Date: 24 Nov 2017													;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 1. Calculate the absolute value of two numbers’ difference. The		;;
;; number is stored at r16 and r17 (aka. |r16-r17|). Store the result	;;
;; to register r20. In the program, you are not allowed to use compare	;;
;; instruction (cp).													;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.include "m328Pdef.inc"

init:
	ser r16
	out DDRB, r16
	
	ldi r16, 2
	ldi r17, 4

main:
	sub r16, r17

	cdq
	xor r16, r18
	sub r16, r18