#lang racket
;(define counter
;  (let ((state 0))
;    (lambda ()
;      (let ((dummy (set! state (+ state 1))))
;        state))))

(define counter
  (let ((state 0))
    (lambda (op)
      (match op
        ['lookup state]
        ['inc (set! state (+ state 1))]
        ['reset (set! state 0)]))))



(define const3
  (lambda ()
    3))
; (define (const3) 3)



(define e1 2)
(define e2 (let ((x 2)) x))
(define e3 (let ((x 2)) (lambda () x)))
(define y 2)
(define e4 (lambda () y))