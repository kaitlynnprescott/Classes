#lang racket

(require eopl/eopl)

(define-datatype BTree BTree?
  (leaf-t
   (data number?))
  (node-t
   (data number?)
   (left BTree?)
   (right BTree?)))
;; An example of a BTree
(define ex
  (node-t 2
          (node-t 12 (leaf-t 7) (leaf-t 11))
          (node-t 4 (leaf-t 1) (leaf-t 9))))

;; btree -> bool
(define (isLeaf t)
  (cases BTree t
    (leaf-t (n) #t)
    (node-t (d l r)  #f)))

(define (btree-product t)
  (cases BTree t
    (leaf-t (n) n)
    (node-t (d l r) (* d (* (btree-product l) (btree-product r))))))

;(define (btree-element num t)

(define (btree-bimap fLeaf fNode t)
  (cases BTree t
    (leaf-t (n) (leaf-t (fLeaf n)))
    (node-t (d l r) (node-t (fNode d) (btree-bimap fLeaf fNode l) (btree-bimap fLeaf fNode r)))))

(define (btree->number t)
  (cases BTree t
    (leaf-t (n) n)
    (node-t (d l r) d)))

(define ex2
  (node-t 4 (leaf-t 1) (leaf-t 9)))
    

(define ex1
  (leaf-t 5))