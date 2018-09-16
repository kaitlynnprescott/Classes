;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Author: Kaitlynn Prescott						;;
;;  Assignment: Assembly1						;;
;;  File: question2.asm							;;
;;  Pledge: I pledge my honor that I have abided by			;;
;;          the Stevens Honor System.					;;
;;  Date: 24 Oct 2017							;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 2. Store 10 numbers at data space 0x0100. Then retrieve the numbers  ;;
;; using the register z and outputs 10 numbers from the memory to	;;
;; Port B. (Points 15)							;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.include "m328Pdef.inc"
init: // defining variables
	.def i = r16
	.def n = r17
main: // loading variables
	ldi n, 9
	ldi zh, 0x01
	ldi zl, 0x00
loop:
	cpc zl, n // compare zl to n
	brge end // if zl >= n, go to end
	ld r22, z+
	out PortB, r22 // print r22
	rjmp loop
end: // end program
	ret


