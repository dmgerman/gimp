;; font-select
;; Spencer Kimball

(define (max-font-width text use-name font-list font-size)
  (let* ((list     font-list)
	 (width    0)
	 (maxwidth 0)
	 (font     "")
	 (extents  '()))
    (while list
	   (set! font (car list))
	   (set! list (cdr list))
	   (if (= use-name TRUE)
	       (set! text font))
	   (set! extents (gimp-text-get-extents-fontname text
							 font-size PIXELS
							 font))
	   (set! width (nth 0 extents))
	   (if (> width maxwidth)
	       (set! maxwidth width)))
    maxwidth))


(define (max-font-height text use-name font-list font-size)
  (let* ((list      font-list)
	 (height    0)
	 (maxheight 0)
	 (font      "")
	 (extents   '()))
    (while list
	   (set! font (car list))
	   (set! list (cdr list))
	   (if (= use-name TRUE)
	       (set! text font))
	   (set! extents (gimp-text-get-extents-fontname text
							 font-size PIXELS
							 font))
	   (set! height (nth 1 extents))
	   (if (> height maxheight)
	       (set! maxheight height)))
    maxheight))


(define (script-fu-font-map text use-name labels font-filter font-size border)
  (let* ((font        "")
	 (count       0)
         (font-list  (cadr (gimp-fonts-get-list font-filter)))
	 (num-fonts  (length font-list))
	 (label-size (/ font-size 2))
	 (border     (+ border (* labels (/ label-size 2))))
	 (y           border)
	 (maxheight  (max-font-height text use-name font-list font-size))
	 (maxwidth   (max-font-width  text use-name font-list font-size))
	 (width      (+ maxwidth (* 2 border)))
	 (height     (+ (+ (* maxheight num-fonts) (* 2 border))
			(* labels (* label-size num-fonts))))
	 (img        (car (gimp-image-new width height GRAY)))
	 (drawable   (car (gimp-layer-new img width height GRAY-IMAGE
					  "Background" 100 NORMAL-MODE))))
    (gimp-image-undo-disable img)
    (gimp-edit-clear drawable)
    (gimp-image-add-layer img drawable 0)

    (if (= labels TRUE)
	(begin
	  (set! drawable (car (gimp-layer-new img width height GRAYA-IMAGE
					      "Labels" 100 NORMAL-MODE)))
	  (gimp-edit-clear drawable)
	  (gimp-image-add-layer img drawable -1)))

    (while font-list
	   (set! font (car font-list))
	   (set! font-list (cdr font-list))

	   (if (= use-name TRUE)
	       (set! text font))

	   (gimp-text-fontname img -1
			       border
			       y
			       text
			       0 TRUE font-size PIXELS
			       font)

	   (set! y (+ y maxheight))

	   (if (= labels TRUE)
	       (begin
		 (gimp-floating-sel-anchor (car (gimp-text-fontname img drawable
								    (- border
								       (/ label-size 2))
								    (- y
								       (/ label-size 2))
								    font
								    0 TRUE
								    label-size PIXELS
								    "Sans")))
		(set! y (+ y label-size))))


	   (set! count (+ count 1)))

    (gimp-image-set-active-layer img drawable)
    (gimp-image-undo-enable img)
    (gimp-display-new img)))

(script-fu-register "script-fu-font-map"
		    _"<Toolbox>/Xtns/Script-Fu/Utils/_Font Map..."
		    "Generate a listing of fonts matching a filter"
		    "Spencer Kimball"
		    "Spencer Kimball"
		    "1997"
		    ""
		    SF-STRING     _"Text" "How quickly daft jumping zebras vex."
		    SF-TOGGLE     _"Use Font Name as Text" FALSE
		    SF-TOGGLE     _"Labels"                TRUE
		    SF-STRING     _"Filter (regexp)"       "Sans"
		    SF-ADJUSTMENT _"Font Size (pixels)"    '(32 2 1000 1 10 0 1)
		    SF-ADJUSTMENT _"Border (pixels)"       '(10 0  200 1 10 0 1))
