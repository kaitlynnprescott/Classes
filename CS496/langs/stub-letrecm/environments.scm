(module environments (lib "eopl.ss" "eopl") 
  
  ;; builds environment interface, using data structures defined in
  ;; data-structures.scm. 

  (require "data-structures.scm")

  (provide init-env empty-env extend-env apply-env)

;;;;;;;;;;;;;;;; initial environment ;;;;;;;;;;;;;;;;
  
  ;; init-env : () -> Env
  ;; usage: (init-env) = [i=1, v=5, x=10]
  ;; (init-env) builds an environment in which i is bound to the
  ;; expressed value 1, v is bound to the expressed value 5, and x is
  ;; bound to the expressed value 10.
  ;; Page: 69

  (define init-env 
    (lambda ()
      (extend-env 
       'i (num-val 1)
       (extend-env
        'v (num-val 5)
        (extend-env
         'x (num-val 10)
         (empty-env))))))

;;;;;;;;;;;;;;;; environment constructors and observers ;;;;;;;;;;;;;;;;

  (define (belongsTo? x theList)
    (if (equal? (member x theList) #f)
        #f
        #t))
  (define (searcher target names vars bodies)
    (if (eq? (car names) target)
        (cons (car vars) (car bodies))
        (searcher target (cdr names) (cdr vars) (cdr bodies))))



  
  ;; Page: 86
  (define apply-env
    (lambda (env search-sym)
      (cases environment env
        (empty-env ()
          (eopl:error 'apply-env "No binding for ~s" search-sym))
        (extend-env (var val saved-env)
	  (if (eqv? search-sym var)
	    val
	    (apply-env saved-env search-sym)))
;        (extend-env-rec (p-name b-var p-body saved-env)
;          (if (eqv? search-sym p-name)
;            (proc-val (procedure b-var p-body env))          
;            (apply-env saved-env search-sym)))
         (extend-env-rec* (p-names b-vars p-bodies saved-env)
           (cond [(belongsTo? search-sym p-names)
                  (define fnvals
                    (searcher search-sym p-names b-vars p-bodies))
                  (proc-val
                    (procedure (car fnvals) (cdr fnvals) env))]
                 [else (apply-env saved-env search-sym)]))
        )))

    
  )