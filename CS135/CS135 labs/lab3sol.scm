#lang eopl

(define (nth n xs)
  (cond ((eqv? n 0) (car xs))
        (else (nth (- n 1) (cdr xs)))))

(define (graph f xs)
  (map (lambda (x) (list x (apply f x))) xs))

(define (dispLst xs)
  (cond ((null? (cdr xs)) (display (car xs)))
        (else (begin (display (car xs)) (newline) (dispLst (cdr xs))))))

(define (mapapp f xs) (map (lambda (x) (apply f x)) xs))


(define bVals1 '((#f) (#t)))

(define bVals2 '((#f #f) (#f #t) (#t #f) (#t #t)))

(define bVals3
  (append (map (lambda (x) (cons #f x)) bVals2)
          (map (lambda (x) (cons #t x)) bVals2)))


(define (xor x y)
  (and (or x y) (not (and x y))))
(define (impl x y)
  (or (not x) y))
(define (biimp x y)
  (eqv? x y))
(define (and2 x y)
  (and x y))
(define (or2 x y)
  (or x y))

(define (f1 x y z)
  (and (or (not x) y) z))
(define (f2 x y z)
  (and z (impl x y)))
(define (and3 x y z)
  (and x y z))
(define (or3 x y z)
  (or x y z))

(define (test-xor-commute x y)
  (biimp (xor x y) (xor y x)))
(define (test-and-absorp x y)
  (biimp (and x (or x y)) x))
(define (test-wrong-law x y)
  (biimp (impl x y) (impl y x)))

(define (test-not-or x y)
  (eqv? (not (or x y)) (and (not x) (not y))))

(define (test-and-over-or x y z)
  (eqv? (or x (and y z)) (and (or x y) (or x z))))

(define (test-not-impl x y)
  (eqv? (impl x y) (impl (not x) (not y))))
