;  Create a 3D sphere with optional shadow
;  The sphere's principle color will be the foreground
;  Parameters:
;   bg-color: background color
;   sphere-color: color of sphere
;   radius: radius of the sphere in pixels
;   light:  angle of light source in degrees
;   shadow: whather to create a shadow as well

(define (script-fu-sphere radius
			  light
			  shadow
			  bg-color
			  sphere-color)
  (let* ((width (* radius 3.75))
	 (height (* radius 2.5))
	 (img (car (gimp-image-new width height RGB)))
	 (drawable (car (gimp-layer-new img width height RGB-IMAGE
					"Sphere Layer" 100 NORMAL-MODE)))
	 (radians (/ (* light *pi*) 180))
	 (cx (/ width 2))
	 (cy (/ height 2))
	 (light-x (+ cx (* radius (* 0.6 (cos radians)))))
	 (light-y (- cy (* radius (* 0.6 (sin radians)))))
	 (light-end-x (+ cx (* radius (cos (+ *pi* radians)))))
	 (light-end-y (- cy (* radius (sin (+ *pi* radians)))))
	 (offset (* radius 0.1))
	 (old-fg (car (gimp-palette-get-foreground)))
	 (old-bg (car (gimp-palette-get-background))))

    (gimp-image-undo-disable img)
    (gimp-image-add-layer img drawable 0)
    (gimp-palette-set-foreground sphere-color)
    (gimp-palette-set-background bg-color)
    (gimp-edit-fill drawable BACKGROUND-FILL)
    (gimp-palette-set-background '(20 20 20))
    (if (and
	 (or (and (>= light 45) (<= light 75))
	     (and (<= light 135) (>= light 105)))
	 (= shadow TRUE))
	(let ((shadow-w (* (* radius 2.5) (cos (+ *pi* radians))))
	      (shadow-h (* radius 0.5))
	      (shadow-x cx)
	      (shadow-y (+ cy (* radius 0.65))))
	  (if (< shadow-w 0)
	      (prog1 (set! shadow-x (+ cx shadow-w))
		     (set! shadow-w (- shadow-w))))

	  (gimp-ellipse-select img shadow-x shadow-y shadow-w shadow-h
			       REPLACE TRUE TRUE 7.5)
	  (gimp-edit-bucket-fill drawable BG-BUCKET-FILL MULTIPLY 100 0 FALSE 0 0)))

    (gimp-ellipse-select img (- cx radius) (- cy radius)
			 (* 2 radius) (* 2 radius) REPLACE TRUE FALSE 0)

    (gimp-edit-blend drawable FG-BG-RGB-MODE NORMAL-MODE
		     GRADIENT-RADIAL 100 offset REPEAT-NONE FALSE
		     FALSE 0 0 TRUE
		     light-x light-y light-end-x light-end-y)

    (gimp-selection-none img)
    (gimp-palette-set-background old-bg)
    (gimp-palette-set-foreground old-fg)
    (gimp-image-undo-enable img)
    (gimp-display-new img)))

(script-fu-register "script-fu-sphere"
		    _"<Toolbox>/Xtns/Script-Fu/Misc/_Sphere..."
		    "Simple sphere with a drop shadow"
		    "Spencer Kimball"
		    "Spencer Kimball"
		    "1996"
		    ""
		    SF-ADJUSTMENT _"Radius (pixels)"    '(100 5 500 1 10 0 1)
		    SF-ADJUSTMENT _"Lighting (degrees)" '(45 0 360 1 10 0 0)
		    SF-TOGGLE     _"Shadow"             TRUE
		    SF-COLOR      _"Background Color"   '(255 255 255)
		    SF-COLOR      _"Sphere Color"       '(255 0 0))
