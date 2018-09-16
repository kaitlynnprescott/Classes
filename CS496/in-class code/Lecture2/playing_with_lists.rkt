#lang racket

;; tree a
;;
;; a) (empty)
;; b) (node n l r) where n is a value of type a and l and r are expressions of type tree a

;; Type of binary trees holding values of type a
;; Eg. tree num

;; example of an empty tree

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

;; {} -> tree num
(define mkEmpty
  (lambda ()
    '(empty)))

;; examples of functions on trees
;; num -> tree num
(define (mkLeaf n)
  (list 'node n '(empty) '(empty)))

;; num -> tree num -> tree num -> tree num
(define (mkNode n l r)
  (list 'node n l r))

;; tree num -> bool
(define (isEmpty t)
  (match t
    [(list 'empty) #t]
    [(list 'node n l r) #f]))

;; tree num -> num
(define (root t)
  (match t
    [(list 'empty) (error "root: and empty tree has no root")]
    [(list 'node n l r) n]))

;; tree num -> num
(define (sumT t)
  (match t
    [(list 'empty) 0]
    [(list 'node n l r) (+ n (sumT l) (sumT r))]))

;; tree num -> tree num
(define (succT t)
  (match t
    [(list 'empty) '(empty)]
    [(list 'node n l r) (list 'node (+ 1 n) (succT l) (succT r))]))

;; tree num -> tree bool
(define (evenT? t)
  (match t
    [(list 'empty) '(empty)]
    [(list 'node n l r) (list 'node (even? n) (evenT? l) (evenT? r))]))

;; { a -> b, tree a} -> tree b
(define (mapT f t)
  (match t
    [(list 'empty) '(empty)]
    [(list 'node n l r) (list 'node (f n) (mapT f l) (mapT f r))]))

;; tree num -> tree num
(define (succT2 t)
  (mapT (lambda (x) (+ x 1)) t))

;; tree num -> tree bool
(define (evenT2? t)
  (mapT even? t))

;; tree a -> tree num
(define (resetT t)
  (mapT (lambda (x) 0) t))

;; tree a -> tree num
(define resetT2
  ((curry mapT) (lambda (x) 0)))





