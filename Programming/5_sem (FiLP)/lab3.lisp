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

;task #9
(defun 
)
(inpredfix '(8 * 10))
