#lang eopl ; Katie Prescott, Lab 2

(define atom?
  (lambda (x)
    (and (not (pair? x)) (not (null? x)))))

(define (xor x y)
  (and (or x y) (not (and x y))))
(define (impl x y)
  (or (not x) y))

(define (test-xor-commute x y)
  (eqv? (xor x y) (xor y x)))

(define (test-and-absorp x y)
  (eqv? (and x (or x y)) x))
(define t1
  (test-and-absorp #f #f))
(define t2
  (test-and-absorp #f #t))
(define t3
  (test-and-absorp #t #f))
(define t4
  (test-and-absorp #t #t))

(define t1234
  (and t1 t2 t3 t4))

(define (test-or-idem x)
  (eqv? (or x x) x))
(define u1
  (test-or-idem #t))
(define u2
  (test-or-idem #f))


(define u12
  (and u1 u2))

(define (test-impl-commute x y)
  (eqv? (impl x y) (impl y x)))
(define w1
  (test-impl-commute #t #t))
(define w2
  (test-impl-commute #t #f))
(define w3
  (test-impl-commute #f #t))
(define w4
  (test-impl-commute #f #f))

(define w1234
  (and w1 w2 w3 w4))

(define (f x y z)
  (and (not (and x y z)) (or (and x y) (and y z) (and x z))))

(define f1
  (f #t #t #t))
(define f2
  (f #t #t #f))
(define f3
  (f #t #f #t))
(define f4
  (f #t #f #f))
(define f5
  (f #f #t #t))
(define f6
  (f #f #t #f))
(define f7
  (f #f #f #t))
(define f8
  (f #f #f #f))