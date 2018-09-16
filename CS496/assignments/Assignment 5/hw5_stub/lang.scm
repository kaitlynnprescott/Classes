(module lang (lib "eopl.ss" "eopl")                

  ;; language for EXPLICIT-REFS
  
  (require "drscheme-init.scm")
  
  (provide (all-defined-out))

  ;;;;;;;;;;;;;;;; grammatical specification ;;;;;;;;;;;;;;;;
  
  (define the-lexical-spec
    '((whitespace (whitespace) skip)
      (comment ("%" (arbno (not #\newline))) skip)
      (identifier
       (letter (arbno (or letter digit "_" "-" "?")))
       symbol)
      (number (digit (arbno digit)) number)
      (number ("-" digit (arbno digit)) number)
      ))
  
  (define the-grammar
    '((program (expression) a-program)


      (expression
       ("showstore")
       showstore-exp)

      (expression (number) const-exp)
      (expression
       ("-" "(" expression "," expression ")")
       diff-exp)
      
      (expression
       ("zero?" "(" expression ")")
       zero?-exp)

      (expression
       ("if" expression "then" expression "else" expression)
       if-exp)

      (expression (identifier) var-exp)

      (expression
       ("let" identifier "=" expression "in" expression)
       let-exp)   

      (expression
       ("proc" "(" identifier ":" type ")" expression)
       proc-exp)

      (expression
       ("(" expression expression ")")
       call-exp)

      (expression
       ("letrec"
        type identifier "(" identifier ":" type ")" "=" expression
        "in" expression)
       letrec-exp)

      
      ;; new for explicit-refs

      (expression
       ("begin" expression (arbno ";" expression) "end")
       begin-exp)

      (expression
       ("newref" "(" expression ")")
       newref-exp)

      (expression
       ("deref" "(" expression ")")
       deref-exp)

      (expression
       ("setref" "(" expression "," expression ")")
       setref-exp)

      (expression
       ("for" identifier "=" expression "to" expression "(" expression ")")
       for-exp)

      ;; pairs
      
      (expression
       ("pair" "(" expression "," expression ")")
       pair-exp)

      (expression
       ("unpair" "(" identifier "," identifier ")" "=" expression "in" expression)
       unpair-exp)

      ;; adapting type checker to EXPLICIT-REFS
      (expression
       ("unitE")
       unit-exp)

      ;; lists
      (expression
       ("emptylist" type)
       emptylist-exp)

      (expression
       ("cons" "(" expression "," expression ")")
       cons-exp)

      (expression
       ("null?" "(" expression ")")
       null?-exp)

      (expression
       ("car" "(" expression ")")
       car-exp)

      (expression
       ("cdr" "(" expression ")")
       cdr-exp)

      ;; trees
      (expression
       ("emptytree" type)
       emptytree-exp)

      (expression
       ("node" "(" expression "," expression "," expression ")")
       node-exp)

      (expression
       ("nullT?" "(" expression ")")
       nullT?-exp)

      (expression
       ("getData" "(" expression ")")
       getData-exp)

      (expression
       ("getLST" "(" expression ")")
       getLST-exp)

      (expression
       ("getRST" "(" expression ")")
       getRST-exp)

      ;; types
      (type
       ("int")
       int-type)
      
      (type
       ("bool")
       bool-type)

      (type
       ("(" type "->" type ")")
       proc-type)

      ;; pair type
      (type
       ("<" type "*" type ">")
       pair-type)

      ;; EXPLICIT-REFS types
      (type
       ("unit")
       unit-type)

      (type
       ("ref" "(" type ")")
       ref-type)

      ;; list type
      (type
       ("list" "(" type ")")
       list-type)

      ;; tree type
      (type
       ("tree" "(" type ")")
       tree-type)
      
      ))


  
  ;;;;;;;;;;;;;;;; sllgen boilerplate ;;;;;;;;;;;;;;;;
  
  (sllgen:make-define-datatypes the-lexical-spec the-grammar)
  
  (define show-the-datatypes
    (lambda () (sllgen:list-define-datatypes the-lexical-spec the-grammar)))
  
  (define scan&parse
    (sllgen:make-string-parser the-lexical-spec the-grammar))
  
  (define just-scan
    (sllgen:make-string-scanner the-lexical-spec the-grammar))

  ;;;;;;;;;;;;;;;; type-to-external-form ;;;;;;;;;;;;;;;;

  ;; type-to-external-form : Type -> List
  ;; Page: 243
  (define type-to-external-form
    (lambda (ty)
      (cases type ty
        (int-type () 'int)
        (bool-type () 'bool)
        (proc-type (arg-type result-type)
                   (list
                    (type-to-external-form arg-type)
                    '->
                    (type-to-external-form result-type)))
        (pair-type (fst-type snd-type)
                   (list
                    '<
                    (type-to-external-form fst-type)
                    '*
                    (type-to-external-form snd-type)
                    '>))
        (unit-type () 'unit)
        (ref-type (store-type)
                  (list
                    'ref
                    (list (type-to-external-form store-type))))
        (list-type (data-type)
                   (list
                    'list
                    (list (type-to-external-form data-type))))
        (tree-type (data-type)
                   (list
                    'tree
                    (list (type-to-external-form data-type))))
        )))
  
  )
