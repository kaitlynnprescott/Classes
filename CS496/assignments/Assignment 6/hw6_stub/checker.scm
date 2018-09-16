(module checker (lib "eopl.ss" "eopl")
  
  (require "drscheme-init.scm")
  (require "lang.scm")
  
  (provide type-of type-of-program)
  (provide global-adts)
  
  ;;;;;;;;;;;;;;;; Declared ADTs ;;;;;;;;;;;;;;;;
  
  (define global-adts '())
  
  (define-datatype adt adt?
    (adt-container
     (id-parent symbol?)
     (id symbol?)
     (args (list-of type?))))
    



  ;;;;;;;;;;;;;;;; Type Equality ;;;;;;;;;;;;;;;;
  ;; check-equal-type! : Type * Type * Exp -> Unspecified
  ;; Page: 242
  (define check-equal-type!
    (lambda (ty1 ty2 exp)
      (when (not (equal? ty1 ty2))
        (report-unequal-types ty1 ty2 exp))))
  
  ;; report-unequal-types : Type * Type * Exp -> Unspecified
  ;; Page: 243
  (define report-unequal-types
    (lambda (ty1 ty2 exp)
      (eopl:error 'check-equal-type!  
                  "Types didn't match: ~s != ~a in~%~a"
                  (type-to-external-form ty1)
                  (type-to-external-form ty2)
                  exp)))
  
  ;;;;;;;;;;;;;;;; The Type Checker ;;;;;;;;;;;;;;;;
  
  ;; type-of-program : Program -> Type
  ;; Page: 244
  (define type-of-program
    (lambda (pgm)
      (cases program pgm
        (a-program (exp1) (type-of exp1 (init-tenv))))))
  
  ;; type-of : Exp * Tenv -> Type
  ;; Page 244--246
  (define type-of
    (lambda (exp tenv)
      (cases expression exp
        
        ;; \commentbox{\hastype{\tenv}{\mv{num}}{\mathtt{int}}}
        (const-exp (num) (int-type))
        
        ;; \commentbox{\hastype{\tenv}{\var{}}{\tenv{}(\var{})}}
        (var-exp (var) (apply-tenv tenv var))
        
        ;; \commentbox{\diffrule}
        (diff-exp (exp1 exp2)
                  (let ((ty1 (type-of exp1 tenv))
                        (ty2 (type-of exp2 tenv)))
                    (check-equal-type! ty1 (int-type) exp1)
                    (check-equal-type! ty2 (int-type) exp2)
                    (int-type)))
        
        ;; \commentbox{\zerorule}
        (zero?-exp (exp1)
                   (let ((ty1 (type-of exp1 tenv)))
                     (check-equal-type! ty1 (int-type) exp1)
                     (bool-type)))
        
        ;; \commentbox{\condrule}
        (if-exp (exp1 exp2 exp3)
                (let ((ty1 (type-of exp1 tenv))
                      (ty2 (type-of exp2 tenv))
                      (ty3 (type-of exp3 tenv)))
                  (check-equal-type! ty1 (bool-type) exp1)
                  (check-equal-type! ty2 ty3 exp)
                  ty2))
        
        ;; \commentbox{\letrule}
        (let-exp (var exp1 body)
                 (let ((exp1-type (type-of exp1 tenv)))
                   (type-of body
                            (extend-tenv var exp1-type tenv))))
        
        ;; \commentbox{\procrulechurch}
        (proc-exp (var var-type body)
                  (let ((result-type
                         (type-of body
                                  (extend-tenv var var-type tenv))))
                    (proc-type var-type result-type)))
        
        ;; \commentbox{\apprule}
        (call-exp (rator rand) 
                  (let ((rator-type (type-of rator tenv))
                        (rand-type  (type-of rand tenv)))
                    (cases type rator-type
                      (proc-type (arg-type result-type)
                                 (begin
                                   (check-equal-type! arg-type rand-type rand)
                                   result-type))
                      (else
                       (report-rator-not-a-proc-type rator-type rator)))))
        
        ;; \commentbox{\letrecrule}
        (letrec-exp (p-result-type p-name b-var b-var-type p-body
                                   letrec-body)
                    (let ((tenv-for-letrec-body
                           (extend-tenv p-name
                                        (proc-type b-var-type p-result-type)
                                        tenv)))
                      (let ((p-body-type 
                             (type-of p-body
                                      (extend-tenv b-var b-var-type
                                                   tenv-for-letrec-body)))) 
                        (check-equal-type!
                         p-body-type p-result-type p-body)
                        (type-of letrec-body tenv-for-letrec-body))))
        
        (showstore-exp ()
                       (unit-type))
        
        (begin-exp (e exps)
                   (if (null? exps)
                       (type-of e tenv)
                       (type-of (car (reverse exps)) tenv)))
        
        (newref-exp (e)
                    (let ((t1 (type-of e tenv)))
                      (ref-type t1)))
        
        (deref-exp (e)
                   (let ((t1 (type-of e tenv)))
                     (cases type t1
                       (ref-type (arg-type) arg-type)
                       (else (report-deref-not-aref e)))))
        
        (setref-exp (id exp)
                    (let ((t1 (type-of id tenv)))
                      (cases type t1
                        (ref-type (arg-type) (unit-type))
                        (else (report-setref-not-aref id)))))
        
        (for-exp (id lb up body)
                 (type-of body (extend-tenv id (int-type) tenv)))

        (unit-exp ()
                  (unit-type))
        
        ;; HOMEWORK 6
        (type-exp (id cs ds)
                  (let ((tid (type-helper id cs ds)))
                    (set! global-adts (append global-adts tid)))
                  (var-type id))
                        
        
        (constr-exp (id args)
                    (var-type id))
        
        (case-exp (e bs)
                  ;;(pretty-print e)
                  ;;(pretty-print bs)
                  (let ((ty (type-of e tenv)))
                    (let ((tye (case-helper ty bs tenv)))
                      (let ((tenv_cases (extenv-helper (ty bs tenv))))
                          (if (and (left-side ty bs tenv_cases) (right-side ty bs tenv_cases))
                              #t
                              (eopl:error "Types of left and right branches not equal!")))
                          ;;check the left side first
                        (eopl:error "Not of same type"))))
                      
                  ;;(eopl:error "not-implemented"))
                  ;;(let ((ty (type-of e tenv)))
                    ;;(let ((branches (type-of bs tenv)))
                     ;; (case-helper e (car bs))
                     ;; (case-exp (e (cdr bs))))))
                    ;;(map (lambda (i)
                      ;;(case-helper bs))
                      ;;(bs)))
                    ;;check args in right side of branch against ty
                    ;;then do left side
        
        )))


  (define (explode-branch branchy)
        (cases caseBranch branchy
          (a-branch (e ln rn) e)
          (else (eopl:error "Not a branch!!!!!!"))))
        

  (define (case-helper ty bs tenv)
    ;;(pretty-print (car bs))
    (if (null? bs)
        ty
        (if (equal? ty (type-of (explode-branch(car bs)) tenv))
            (case-helper ty (cdr bs) tenv)
            (eopl:error "Not of same type"))))

   (define (extenv-helper ty bs tenv)
     (if (null? bs)
         tenv
         (if (null? (cdr bs))
             (extend-tenv (car bs) ty tenv)
             (extenv-helper ty (cdr bs) (extend-tenv (car bs) ty tenv)))))

  
   (define (left-side ty bs tenv_cases)
     (if (null? bs)
         #t
         (if (equal? ty (type-of (car bs)))
             (left-side ty (cdr bs) tenv_cases)
             #f)))

    (define (right-side ty bs tenv_cases)
      (if (null? bs)
          #t
          (if (equal? ty (type-of (car bs)))
              (right-side ty (cdr bs) tenv_cases)
              #f)))
              
     

   ;;(define (rnode-helper tv)

  ;; (define (tynode-helper tv)
   ;;  (let ((tyn (type-of tv tenv)))
    ;;   (cases type tyn
     ;;    ())))
      
    

  (define (type-helper id cs ds)
    (if (and (null? cs) (null? ds))
        '()
        (append (list (adt-container id (car cs) (car ds)))
                (type-helper id (cdr cs) (cdr ds)))))
  
  
  (define report-deref-not-aref
    (lambda (arg)
      (eopl:error 'type-of-expression
                  "Address of deref is not ref-type: ~% ~s"
                  arg)))
  
  (define report-setref-not-aref
    (lambda (arg)
      (eopl:error 'type-of-expression
                  "Address of setref is not a ref-type: ~% ~s"
                  arg)))
  
  (define report-rator-not-a-proc-type
    (lambda (rator-type rator)
      (eopl:error 'type-of-expression
                  "Rator not a proc type:~%~s~%had rator type ~s"   
                  rator 
                  (type-to-external-form rator-type))))
  
  ;;;;;;;;;;;;;;;; type environments ;;;;;;;;;;;;;;;;
  
  (define-datatype type-environment type-environment?
    (empty-tenv-record)
    (extended-tenv-record
     (sym symbol?)
     (type type?)
     (tenv type-environment?)))
  
  (define empty-tenv empty-tenv-record)
  (define extend-tenv extended-tenv-record)
  
  (define apply-tenv 
    (lambda (tenv sym)
      (cases type-environment tenv
        (empty-tenv-record ()
                           (eopl:error 'apply-tenv "Unbound variable ~s" sym))
        (extended-tenv-record (sym1 val1 old-env)
                              (if (eqv? sym sym1) 
                                  val1
                                  (apply-tenv old-env sym))))))
  
  (define init-tenv
    (lambda ()
      (extend-tenv 'x (int-type) 
                   (extend-tenv 'v (int-type)
                                (extend-tenv 'i (int-type)
                                             (empty-tenv))))))
  
  )
