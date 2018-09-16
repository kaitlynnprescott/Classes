#lang eopl

(define (expo n i)
  (cond
    [(eq? i 0) 1]
    [else (* n (expo n (- i 1)))]))

(define test-expo
  (and (eqv? (expo 2 3) 8)
       (eqv? (expo 2 4) 16)
       (eqv? (expo 3 3) 27)
       (eqv? (expo 4 3) 64)))
