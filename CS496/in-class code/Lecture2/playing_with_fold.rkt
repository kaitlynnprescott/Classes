#lang racket

;; { a -> b, tree a} -> tree b
(define (mapT f t)
  (match t
    [(list 'empty) '(empty)]
    [(list 'node n l r) (list 'node (f n) (mapT f l) (mapT f r))]))

;;
(define (succT2 t)
  (mapT (lambda (x) (+ x 1)) t))

;;
(define (evenT2? t)
  (mapT even? t))

;;
(define (resetT t)
  (mapT (lambda (x) 0) t))

;;
(define resetT2
  ((curry mapT) (lambda (x) 0)))

;; 1. Motivate fold with examples
;; 2. Define fold itself (foldr)
;; 3. Redefine the operations used to motivate fold, using foldr

;; { {a, b} -> b, b, [a]} -> b
(define (foldr2 f e xs)
  (match xs
    ['() e]
    [(cons h t) (f h (foldr2 f e t))]))

;; (foldr2 f e '(x1 x2 x3))
;;
;; (f x1 (f x2 (f x3 e)))
;; (+ x1 (+ x2 (+ x3 0)))
;; (* x1 (* x2 (* x3 1)))
;;
;;

;; { {a, b}-> b, b, [a]} -> b
(define (foldl2 f e xs)
  (match xs
    ['() e]
    [(cons h t) (foldl2 f (f e h) t)]))

;; (fold rl f e '(x1 x2 x3))
;;
;; (f (f (f e x1) x2) x3)
;; (+ (+ (+ 0 x1) x2) x3)
;; (* (* (* 1 x1) x2) x3)
;;

;; [num] -> num
(define (sumL xs)
  (match xs
    ['() 0]
    [(cons h ys) (+ h (sumL ys))]))

;; [num] -> num
(define (sumL2 xs)
  (foldr2 (lambda (h r) (+ h r)) 0 xs))

;; [num -> bool
(define (evenL? xs)
  (match xs
    ['() #t]
    [(cons h ys) (and (even? h) (evenL? ys))]))

;; [num] -> bool
(define (evenL2? xs)
  (foldr2 (lambda (h r) (and (even? h) r)) #t xs))

;; [[a]] -> [a]
(define (concat xss)
  (match xss
    ['() '()]
    [(cons h ys) (append h (concat ys))]))

(concat '((1 2 3) (2 3) (4)))

;;
;;(define (concat2 xss)
;;  (foldr2 (lambda (h r) (append h r) aBaseCase xss))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Video 4 - Fold for tree a
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; tree a
(define t1
  '(empty))

;; examples of trees
;; tree num
(define t2
  '(node 1 (empty) (empty)))

;; tree num
(define t3 '(node 1 (node 2 (empty) (empty))
                    (node 3 (empty) (empty))))


;; tree num -> num
(define (sumT t)
  (match t
    [(list 'empty) 0]
    [(list 'node n l r) (+ n (sumT l) (sumT r))]))

;; tree string -> string
(define (appendT t)
  (match t
    [(list 'empty) ""]
    [(list 'node s l r) (string-append s (appendT l) (appendT r))]))

(define t4
  '(node "a" (node "b" (empty) (empty))
              (node "c" (empty) (empty))))

;; { {a, b, b} -> b, b, tree a} -> b
(define (foldT f e t)
  (match t
    [(list 'empty) e]
    [(list 'node d l r) (f d (foldT f e l) (foldT f e r))]))

;; tree num -> num
(define (sumT2 t)
  (foldT (lambda (d rl rr) (+ d rl rr)) 0 t))

;; tree string -> string
(define (appendT2 t)
  (foldT (lambda (d rl rr) (string-append d rl rr)) "" t))

;; tree num -> tree num
(define (incT2 t)
  (foldT (lambda (d rl rr) (list 'node (+ d 1) rl rr)) '(empty) t))

