;  Nova Starscape
;  Create a text effect that simulates an eerie alien glow around text

(define (find-blend-coords w h)
  (let* ((denom (+ (/ w h) (/ h w)))
	 (bx    (/ (* -2 h) denom))
	 (by    (/ (* -2 w) denom)))
    (cons bx by)))

(define (find-nova-x-coord drawable x1 x2 y)
  (let* ((x 0)
	 (alpha 3)
	 (range (- x2 x1))
	 (min-clearance 5)
	 (val '())
	 (val-left '())
	 (val-right '())
	 (val-top '())
	 (val-bottom '())
	 (limit 100)
	 (clearance 0))
    (while (and (= clearance 0) (> limit 0))
	   (set! x (+ (rand range) x1))
	   (set! val (cadr (gimp-drawable-get-pixel drawable x y)))
	   (set! val-left (cadr (gimp-drawable-get-pixel drawable (- x min-clearance) y)))
	   (set! val-right (cadr (gimp-drawable-get-pixel drawable (+ x min-clearance) y)))
	   (set! val-top (cadr (gimp-drawable-get-pixel drawable x (- y min-clearance))))
	   (set! val-bottom (cadr (gimp-drawable-get-pixel drawable x (+ y min-clearance))))
	   (if (and (= (aref val alpha) 0) (= (aref val-left alpha) 0) (= (aref val-right alpha) 0)
		    (= (aref val-top alpha) 0) (= (aref val-bottom alpha) 0))
	       (set! clearance 1) (set! limit (- limit 1))))
    x))

(define (apply-starscape-logo-effect img
				     logo-layer
				     size
				     glow-color)
  (let* ((border (/ size 4))
	 (grow (/ size 30))
	 (offx (* size 0.03))
	 (offy (* size 0.02))
	 (feather (/ size 4))
	 (shadow-feather (/ size 25))
	 (width (car (gimp-drawable-width logo-layer)))
	 (height (car (gimp-drawable-height logo-layer)))
	 (w (* (/ (- width (* border 2)) 2.0) 0.75))
	 (h (* (/ (- height (* border 2)) 2.0) 0.75))
	 (novay (* height 0.3))
	 (novax (find-nova-x-coord logo-layer (* width 0.2) (* width 0.8) novay))
	 (novaradius (/ (min height width) 7.0))
	 (cx (/ width 2.0))
	 (cy (/ height 2.0))
	 (bx (+ cx (car (find-blend-coords w h))))
	 (by (+ cy (cdr (find-blend-coords w h))))
	 (bg-layer (car (gimp-layer-new img width height RGB_IMAGE "Background" 100 NORMAL)))
	 (glow-layer (car (gimp-layer-new img width height RGBA_IMAGE "Glow" 100 NORMAL)))
	 (shadow-layer (car (gimp-layer-new img width height RGBA_IMAGE "Drop Shadow" 100 NORMAL)))
	 (bump-channel (car (gimp-channel-new img width height "Bump Map" 50 '(0 0 0))))
	 (old-pattern (car (gimp-patterns-get-pattern)))
	 (old-fg (car (gimp-palette-get-foreground)))
	 (old-bg (car (gimp-palette-get-background))))
    (gimp-selection-none img)
    (script-fu-util-image-resize-from-layer img logo-layer)
    (gimp-image-add-layer img bg-layer 1)
    (gimp-image-add-layer img glow-layer 1)
    (gimp-image-add-layer img shadow-layer 1)
    (gimp-image-add-channel img bump-channel 0)
    (gimp-layer-set-preserve-trans logo-layer TRUE)

    (gimp-palette-set-background '(0 0 0))
    (gimp-edit-fill bg-layer BG-IMAGE-FILL)
    (gimp-edit-clear shadow-layer)
    (gimp-edit-clear glow-layer)

    (gimp-selection-layer-alpha logo-layer)
    (gimp-selection-grow img grow)
    (gimp-selection-feather img feather)
    (gimp-palette-set-background glow-color)
    (gimp-selection-feather img feather)
    (gimp-edit-fill glow-layer BG-IMAGE-FILL)

    (gimp-selection-layer-alpha logo-layer)
    (gimp-selection-feather img shadow-feather)
    (gimp-palette-set-background '(0 0 0))
    (gimp-selection-translate img offx offy)
    (gimp-edit-fill shadow-layer BG-IMAGE-FILL)

    (gimp-selection-none img)
    (gimp-palette-set-background '(31 31 31))
    (gimp-palette-set-foreground '(255 255 255))
    (gimp-blend logo-layer FG-BG-RGB NORMAL BILINEAR 100 0 REPEAT-NONE FALSE 0 0 TRUE cx cy bx by)

    (plug-in-nova 1 img glow-layer novax novay glow-color novaradius 100 0)

    (gimp-selection-all img)
    (gimp-patterns-set-pattern "Stone")
    (gimp-bucket-fill bump-channel PATTERN-BUCKET-FILL NORMAL 100 0 FALSE 0 0)
    (plug-in-bump-map 1 img logo-layer bump-channel 135.0 45.0 4 0 0 0 0 FALSE FALSE 0)
    (gimp-image-remove-channel img bump-channel)
    (gimp-selection-none img)

    (gimp-patterns-set-pattern old-pattern)
    (gimp-palette-set-background old-bg)
    (gimp-palette-set-foreground old-fg)))


(define (script-fu-starscape-logo-alpha img
					logo-layer
					size
					glow-color)
  (begin
    (gimp-undo-push-group-start img)
    (apply-starscape-logo-effect img logo-layer size glow-color)
    (gimp-undo-push-group-end img)
    (gimp-displays-flush)))

(script-fu-register "script-fu-starscape-logo-alpha"
		    _"<Image>/Script-Fu/Alpha to Logo/Starscape..."
		    "Starscape using the Nova plug-in"
		    "Spencer Kimball"
		    "Spencer Kimball"
		    "1997"
		    "RGBA"
                    SF-IMAGE      "Image" 0
                    SF-DRAWABLE   "Drawable" 0
		    SF-ADJUSTMENT _"Effect Size (pixels * 4)" '(150 1 1000 1 10 0 1)
		    SF-COLOR      _"Glow Color" '(28 65 188)
		    )


(define (script-fu-starscape-logo text
				  size
				  fontname
				  glow-color)
  (let* ((img (car (gimp-image-new 256 256 RGB)))
	 (border (/ size 4))
	 (text-layer (car (gimp-text-fontname img -1 0 0 text border TRUE size PIXELS fontname))))
    (gimp-image-undo-disable img)
    (gimp-layer-set-name text-layer text)
    (apply-starscape-logo-effect img text-layer size glow-color)
    (gimp-image-undo-enable img)
    (gimp-display-new img)))

(script-fu-register "script-fu-starscape-logo"
		    _"<Toolbox>/Xtns/Script-Fu/Logos/Starscape..."
		    "Starscape using the Nova plug-in"
		    "Spencer Kimball"
		    "Spencer Kimball"
		    "1997"
		    ""
		    SF-STRING     _"Text" "Nova"
		    SF-ADJUSTMENT _"Font Size (pixels)" '(150 1 1000 1 10 0 1)
            SF-FONT       _"Font" "Engraver"
		    SF-COLOR      _"Glow Color" '(28 65 188)
		    )
