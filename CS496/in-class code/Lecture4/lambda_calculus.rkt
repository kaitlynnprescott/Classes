#lang racket

;; Identity function in lambda calculus
;; \l .x x

;; encoding in scheme using list
(define idt
  (list 'lambda (list 'x) 'x))

(define-datatype expression expression?
   (var-exp
     (id symbol?))
   (lambda-exp
     (id symbol?)
     (body expression?))
   (app-exp
     (rator expression?)
     (rand expression?)))