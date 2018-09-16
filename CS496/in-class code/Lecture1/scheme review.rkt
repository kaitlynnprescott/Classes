#lang racket

;; num
(define l1
  '(1 2 3 4))

;; {num, num} -> num
(define (mult x y)
  (* x y))

;; num -> num
(define (succ x)
  (+ x 1))

;;
;;(define succ2
;;  )

;; 
;;(define succ3
;;  (lambda (x) (lambda (y)) (+ x y)) 1)

;; [a] -> a -> [a]
(define (snoc xs x)
  (append xs (list x)))

;; does not work as intended
(define (snoc2 xs x)
  (append xs x))

;; [a] -> (a -> [a])
(define snoc3 
  (lambda (xs)
    (lambda (x)
      (append xs (list x)))))

;; [a] -> num
(define (len xs)
  (length xs))

;; [num] -> [num]
(define (succL xs)
  (match xs
    ['() '()]
    [(cons h t) (cons (+ 1 h) (succL t))]
    [_ ( error "succL connot handle this case")]))