;  HIGHLIGHT-DROP-SHADOW-LOGO
;  draw the specified text over a background with a drop shadow and a highlight

(define (color-highlight color)
  (let ((r (car color))
	(g (cadr color))
	(b (caddr color)))

    (set! r (+ r (* (- 255 r) 0.75)))
    (set! g (+ g (* (- 255 g) 0.75)))
    (set! b (+ b (* (- 255 b) 0.75)))
    (list r g b)))

(define (apply-basic2-logo-effect img
				  logo-layer
				  bg-color
				  text-color)
  (let* ((width (car (gimp-drawable-width logo-layer)))
	 (height (car (gimp-drawable-height logo-layer)))
	 (posx (- (car (gimp-drawable-offsets logo-layer))))
	 (posy (- (cadr (gimp-drawable-offsets logo-layer))))
	 (bg-layer (car (gimp-layer-new img width height RGB_IMAGE "Background" 100 NORMAL)))
	 (highlight-layer (car (gimp-layer-copy logo-layer TRUE)))
	 (shadow-layer (car (gimp-layer-new img width height RGBA_IMAGE "Shadow" 100 MULTIPLY)))
	 (old-fg (car (gimp-palette-get-foreground)))
	 (old-bg (car (gimp-palette-get-background))))

    (gimp-selection-none img)
    (script-fu-util-image-resize-from-layer img logo-layer)
    (gimp-image-add-layer img bg-layer 1)
    (gimp-image-add-layer img shadow-layer 1)
    (gimp-image-add-layer img highlight-layer 1)
    (gimp-palette-set-foreground text-color)
    (gimp-layer-set-preserve-trans logo-layer TRUE)
    (gimp-edit-fill logo-layer FG-IMAGE-FILL)
    (gimp-edit-clear shadow-layer)
    (gimp-palette-set-foreground (color-highlight text-color))
    (gimp-layer-set-preserve-trans highlight-layer TRUE)
    (gimp-edit-fill highlight-layer FG-IMAGE-FILL)
    (gimp-palette-set-background bg-color)
    (gimp-drawable-fill bg-layer BG-IMAGE-FILL)
    (gimp-selection-layer-alpha logo-layer)
    (gimp-palette-set-background '(0 0 0))
    (gimp-selection-feather img 7.5)
    (gimp-edit-fill shadow-layer BG-IMAGE-FILL)
    (gimp-selection-none img)
    (gimp-palette-set-foreground '(255 255 255))

    (gimp-blend logo-layer FG-BG-RGB MULTIPLY
		RADIAL 100 20 REPEAT-NONE FALSE
		FALSE 0 0 TRUE
		0 0 width height)

    (gimp-layer-translate shadow-layer 3 3)
    (gimp-layer-translate highlight-layer (- posx 2) (- posy 2))
    (gimp-layer-set-name highlight-layer "Highlight")
    (gimp-palette-set-background old-bg)
    (gimp-palette-set-foreground old-fg)))

(define (script-fu-basic2-logo-alpha img
				     logo-layer
				     bg-color
				     text-color)
  (begin
    (gimp-undo-push-group-start img)
    (apply-basic2-logo-effect img logo-layer bg-color text-color)
    (gimp-undo-push-group-end img)
    (gimp-displays-flush)))

(script-fu-register "script-fu-basic2-logo-alpha"
		    _"<Image>/Script-Fu/Alpha to Logo/Basic II..."
		    "Creates a simple logo with a shadow and a highlight"
		    "Spencer Kimball"
		    "Spencer Kimball"
		    "1996"
		    "RGBA"
                    SF-IMAGE      "Image" 0
                    SF-DRAWABLE   "Drawable" 0
       		    SF-COLOR      _"Background Color" '(255 255 255)
		    SF-COLOR      _"Text Color" '(206 6 50))

(define (script-fu-basic2-logo text
			       size
			       font
			       bg-color
			       text-color)
  (let* ((img (car (gimp-image-new 256 256 RGB)))
	 (text-layer (car (gimp-text-fontname img -1 0 0 text 10 TRUE size PIXELS font))))

    (gimp-image-undo-disable img)
    (gimp-layer-set-name text-layer text)
    (apply-basic2-logo-effect img text-layer bg-color text-color)
    (gimp-image-undo-enable img)
    (gimp-display-new img)))

(script-fu-register "script-fu-basic2-logo"
		    _"<Toolbox>/Xtns/Script-Fu/Logos/Basic II..."
		    "Creates a simple logo with a shadow and a highlight"
		    "Spencer Kimball"
		    "Spencer Kimball"
		    "1996"
		    ""
		    SF-STRING     _"Text"               "SCRIPT-FU"
		    SF-ADJUSTMENT _"Font Size (pixels)" '(150 2 1000 1 10 0 1)
		    SF-FONT       _"Font"               "Futura_Poster"
		    SF-COLOR      _"Background Color"   '(255 255 255)
		    SF-COLOR      _"Text Color"         '(206 6 50))
