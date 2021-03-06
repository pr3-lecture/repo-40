;Sascha Betzwieser 1512670
;Jonas Lagaude 1430596


(defun left-branch (tree)
(cadr tree))


(defun right-branch (tree)
(caddr tree))

(defun make-tree (entry left right)
(list entry left right))

(defun insert (tree val)
  (cond
    ((null tree) (make-tree val nil nil))
    ((= val (car tree)) tree)
    ((< val (car tree)) (make-tree (car tree) (insert (left-branch tree) val) (right-branch tree)))
    ((> val (car tree)) (make-tree (car tree) (left-branch tree) (insert (right-branch tree) val)))))

(defun insert-from-file (tree filename)
  (with-open-file (stream filename)
  (loop for line = (read stream nil)
        while line
        do (setq tree (insert tree line)))
    tree))

(defun contains (tree val)
  (cond
    ((null tree) nil)
    ((listp (car tree)) (or (contains (car tree) val) (contains (cdr tree) val)))
    ((equal (car tree) val) T)
    (t (contains (cdr tree) val)))
)

(defun size (tree)
  (cond
    ((null tree) 0)
    (t (+ 1 (size (left-branch tree))(size (right-branch tree))))))

(setf x (insert-from-file nil "list.txt"))
(print x)
(setf y (size x))
(print y)

(defun height (tree)
  (cond
    ((null tree) 0)
    (t (+ 1 (max (height (left-branch tree)) (height (right-branch tree)))))))

(setf z (height x))
(print z)

(defun getMax (tree)
  (cond
    ((null tree) nil)
    ((null (right-branch tree)) (car tree))
    (t (getMax (right-branch tree)))))

(setf a (getMax x))
(print a)

(defun getMin (tree)
  (cond
    ((null tree) nil)
    ((null (left-branch tree)) (car tree))
    (t (getMin (left-branch tree)))))

(setf b (getMin x))
(print b)



(defun removeVal (tree v)
  (cond
		((null (car tree))
        nil)
    ((and (= v (car tree)) (= (height tree) 1))
        nil)
    ((and (= v (car tree)) (null (caddr tree)) )
        (list (getMax (cadr tree)) (removeVal (cadr tree) (getMax (cadr tree))) nil))
			((= v (car tree))
        (list (getMin (caddr tree)) (cadr tree) (removeVal (caddr tree) (getMin (caddr tree)))))
    ((< val (car tree))
        (list (car tree) (removeVal (cadr tree) v) (caddr tree)))
    ((> val (car tree))
        (list (car tree) (cadr tree) (removeVal (caddr tree) v)))))


(defun isEmpty (tree)
  (null (car tree)))


	(defun addAll (tree otherTree)
	  (setq otherTree (printLevelorder otherTree))
	  (loop
	    (setq tree (insert tree (car otherTree)))
	    (setq otherTree (cdr otherTree))
	    (when (endp otherTree) (return tree))
	  )
	)


(setf c (insert-from-file nil "list2.txt"))
(print c)
(setf d (add-all x c))
(print d)



;LEVELORDER
(defun printLevel (tree level)
    (if (null tree)
        NIL
        (cond
            ((= level 1)
                (if (not (null tree))
                (print (if (listp tree) (car tree) tree))))
            ((> level 1)
                (if  (listp tree)
                    (printLevel (cadr tree) (- level 1)))
                (if  (listp tree)
                    (printLevel (caddr tree) (- level 1)))))))

(defun printLevelorder (tree)
    (loop for x from 1 to (+ 1 (height tree))
         do (printLevel tree x)))
