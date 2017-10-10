; task #2
(defun equ (l1 l2)
	(cond
		((and (null l1) (null l2))
			t
		)
		((member (car l1) l2)
			(equ (remove (car l1) l1) (remove (car l1) l2))
		)
		(t
			nil
		)
	)
)
(equ '(0 9 3 6 3) '(0 3 3 6 9))

;task #6
(defun compl (l1 l2)
	(cond
		((or (null l1) (null l2))
			l1
		)
		((member (car l1) l2)
			(compl (remove (car l1) l1) (remove (car l1) l2))
		)
		(t
			(cons (car l1) (compl (remove (car l1) l1) (remove (car l1) l2)))
		)
	)
)
(compl '(0 12 9 3 6 3 4 10 (5 6)) '(0 3 10 3 6 9 5 6))

;task #9
(defun func (p l)
	(cond
		((null l)
			l
		)
		((funcall p (car l))
			(append '(*)  (list (car l)) (func p (cdr l)))
		)
		(t
			(append (list (car l)) (func p (cdr l)))
		)
	)
)
(func (lambda (x) (>= x 0)) '(0 9 -3 6 -3))
(func 'evenp '(0 9 3 6 3))