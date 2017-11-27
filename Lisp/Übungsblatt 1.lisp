;Sascha Betzwieser 1512670
;Jonas Lagaude 1430596

;Aufgabe 1
;a)
(defun rotiere(liste)
(cond
  ((null (cdr liste)) liste)
  (t
   (cons (first (last liste))
           (append (butlast (rest liste))
                   (list (first liste)))))
  ))

  ;b)
(defun neues-vorletztes (x liste)
    (append (reverse (cdr (reverse liste)))
  	(list x) (list (car (reverse liste)))))

;c)
(defun my-length (liste)
    (cond
      ((null liste) 0)
      (t
       (+ 1 (my-length (cdr liste))))
      )
  )

;d)
(defun my-lengthR (liste)
    (cond ((null liste) 0)
        ((listp (car liste))
            (+ (my-lengthR (car liste)) (my-lengthR (cdr liste))))
        (t
         (+ 1 (my-lengthR (cdr liste))))))

;e)
(defun my-reverse (liste)
    (cond
        ((null liste)'())
        (t
            (append (my-reverse (cdr liste))
            (list (car liste))))))

;f)
(defun my-reverseR (liste)
    (cond
        ((null liste) nil)
        ((listp (car liste))
            (append (my-reverseR (cdr liste)) (list (my-reverseR (car liste)))))
        (t
            (append (my-reverseR (cdr liste))
            (list (car liste))))))


;Aufgabe 2
;a)
;Um einen Binärbaum in einer Liste darzustellen beginnt man mit der Wurzel bzw. dem Elternknoten,
; gefolgt von zwei Listen die jeweils den linken und rechten Kindknoten darstellen.
; Dieses Prinzip setzt sich bei den Kindknoten fort.
;Darstellung Binärbaum:
;(1 (2 (4) (5)) (3 (6) (7 () (8))))
;(Wurzel (linker Knoten)  (rechter Knoten))

;2b)
;links: cadr (car (cdr tree))
;rechts: caddr (car (cdr (cdr tree)))
;Inorder
(defun inorder (tree)
  (cond ((null tree) nil)
      (t (inorder (cadr tree))
          (print (car tree))
          (inorder (caddr tree))))
  )


;Preorder
(defun preorder (tree)
  (cond ((null tree) nil)
        (t (print (car tree))
           (preorder (cadr tree))
           (preorder (caddr tree)))))


;Postorder
(defun postorder (tree)
  (cond ((null tree) nil)
        (t (postorder (cadr tree))
           (postorder (caddr tree))
           (print (car tree)))))
