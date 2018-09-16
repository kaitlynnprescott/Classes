#lang racket

;; [num]
(define l
  '(1 2 3))

;; {[a],a} -> [a]
(define (snoc xs x)
  (append xs (list x)))

(define (snoc2 xs x)
  (append xs x))

;; num -> num
(define (succ n)
  (+ 1 n))

;; num -> num
(define succ2
  (lambda (n)
    (+ 1 n)))

;; num -> num
(define succ3
  ((lambda (x) (lambda (y) (+ x y))) 1))

;;  (num -> a) -> a 
(define f
  (lambda (g)
    (g 2)))

;; (num -> num) -> num 
(define f2
  (lambda (g)
    (+ 1 (g 2))))

;;  {num,num} -> num
(define (add x y)
  (+ x y))

;; num -> (num -> num)
(define add2
  (lambda (x)
    (lambda (y)
      (+ x y))))

;; [num] -> [num]
(define (succL xs)
  (match xs
    ['() '()]
    [(cons h t) (cons (+ h 1) (succL t))]))
 ;;   [_ (error "succL: cannot handle that case")]))

;; [num] -> num
(define (addL xs)
  (match xs
    ['() 0]
    [(cons h t) (+ h (addL t))]))

;; num -> num
(define (fact n)
  (match n
    [0 1]
    [n (* n (fact (- n 1)))]))

;; [a] -> a
(define (myCar xs)
  (match xs
    ['() (error "myCar: cannot compute the head of an empty list")]
    [(cons h t) h]))

;; { num, num } -> num
;; (num,num) -> num

;; (a,b) -> a
(define (fst p)
  (match p
    [(cons l r) l]))