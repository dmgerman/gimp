;  FROZEN-TEXT effect
;  Thanks to Ed Mackey for this one
;   Written by Spencer Kimball

(define (apply-frosty-logo-effect img
				  logo-layer
				  size
				  bg-color)
  (let* ((border (/ size 5))
	 (width (car (gimp-drawable-width logo-layer)))
	 (height (car (gimp-drawable-height logo-layer)))
	 (logo-layer-mask (car (gimp-layer-create-mask logo-layer ADD-BLACK-MASK)))
	 (sparkle-layer (car (gimp-layer-new img width height RGBA-IMAGE "Sparkle" 100 NORMAL-MODE)))
	 (matte-layer (car (gimp-layer-new img width height RGBA-IMAGE "Matte" 100 NORMAL-MODE)))
	 (shadow-layer (car (gimp-layer-new img width height RGBA-IMAGE "Shadow" 90 MULTIPLY-MODE)))
	 (bg-layer (car (gimp-layer-new img width height RGB-IMAGE "Background" 100 NORMAL-MODE)))
	 (selection 0)
	 (old-fg (car (gimp-palette-get-foreground)))
	 (old-bg (car (gimp-palette-get-background)))
	 (old-brush (car (gimp-brushes-get-brush)))
	 (old-paint-mode (car (gimp-brushes-get-paint-mode))))
    (gimp-layer-add-mask logo-layer logo-layer-mask)
    (script-fu-util-image-resize-from-layer img logo-layer)
    (gimp-image-add-layer img sparkle-layer 2)
    (gimp-image-add-layer img matte-layer 3)
    (gimp-image-add-layer img shadow-layer 4)
    (gimp-image-add-layer img bg-layer 5)
    (gimp-selection-none img)
    (gimp-edit-clear sparkle-layer)
    (gimp-edit-clear matte-layer)
    (gimp-edit-clear shadow-layer)
    (gimp-selection-layer-alpha logo-layer)
    (set! selection (car (gimp-selection-save img)))
    (gimp-selection-feather img border)
    (gimp-palette-set-background '(0 0 0))
    (gimp-edit-fill sparkle-layer BACKGROUND-FILL)
    (plug-in-noisify 1 img sparkle-layer FALSE 0.2 0.2 0.2 0.0)
    (plug-in-c-astretch 1 img sparkle-layer)
    (gimp-selection-none img)
    (plug-in-sparkle 1 img sparkle-layer 0.03 0.5 (/ (min width height) 2) 6 15 1.0 0.0 0.0 0.0 FALSE FALSE FALSE 0)
    (gimp-levels sparkle-layer 1 0 255 0.2 0 255)
    (gimp-levels sparkle-layer 2 0 255 0.7 0 255)
    (gimp-selection-layer-alpha sparkle-layer)
    (gimp-palette-set-foreground '(0 0 0))
    (gimp-brushes-set-brush "Circle Fuzzy (11)")
    (gimp-edit-stroke matte-layer)
    (gimp-selection-feather img border)
    (gimp-edit-fill shadow-layer BACKGROUND-FILL)
    (gimp-selection-none img)
    (gimp-palette-set-background bg-color)
    (gimp-edit-fill bg-layer BACKGROUND-FILL)
    (gimp-palette-set-background '(0 0 0))
    (gimp-edit-fill logo-layer BACKGROUND-FILL)
;    (gimp-layer-add-mask logo-layer logo-layer-mask)
    (gimp-selection-load selection)
    (gimp-palette-set-background '(255 255 255))
    (gimp-edit-fill logo-layer-mask BACKGROUND-FILL)
    (gimp-selection-feather img border)
    (gimp-selection-translate img (/ border 2) (/ border 2))
    (gimp-edit-fill logo-layer BACKGROUND-FILL)
    (gimp-layer-remove-mask logo-layer 0)
    (gimp-selection-load selection)
    (gimp-brushes-set-brush "Circle Fuzzy (07)")
    (gimp-brushes-set-paint-mode BEHIND-MODE)
    (gimp-palette-set-foreground '(186 241 255))
    (gimp-edit-stroke logo-layer)
    (gimp-selection-none img)
    (gimp-image-remove-channel img selection)
    (gimp-layer-translate shadow-layer border border)
    (gimp-palette-set-foreground old-fg)
    (gimp-palette-set-background old-bg)
    (gimp-brushes-set-brush old-brush)
    (gimp-brushes-set-paint-mode old-paint-mode)))

(define (script-fu-frosty-logo-alpha img
				     logo-layer
				     size
				     bg-color)
  (begin
    (gimp-image-undo-group-start img)
    (apply-frosty-logo-effect img logo-layer size bg-color)
    (gimp-image-undo-group-end img)
    (gimp-displays-flush)))


(script-fu-register "script-fu-frosty-logo-alpha"
		    _"<Image>/Script-Fu/Alpha to Logo/_Frosty..."
		    "Frozen logos with drop shadows"
		    "Spencer Kimball & Ed Mackey"
		    "Spencer Kimball & Ed Mackey"
		    "1997"
		    "RGBA"
                    SF-IMAGE      "Image" 0
                    SF-DRAWABLE   "Drawable" 0
		    SF-ADJUSTMENT _"Effect Size (pixels)" '(100 2 1000 1 10 0 1)
		    SF-COLOR  _"Background Color" '(255 255 255)
		    )

(define (script-fu-frosty-logo text
			       size
			       font
			       bg-color)
  (let* ((img (car (gimp-image-new 256 256 RGB)))
	 (border (/ size 5))
	 (text-layer (car (gimp-text-fontname img -1 0 0 text (* border 2) TRUE size PIXELS font))))
    (gimp-image-undo-disable img)
    (gimp-drawable-set-name text-layer text)
    (apply-frosty-logo-effect img text-layer size bg-color)
    (gimp-image-undo-enable img)
    (gimp-display-new img)))

(script-fu-register "script-fu-frosty-logo"
		    _"<Toolbox>/Xtns/Script-Fu/Logos/_Frosty..."
		    "Frozen logos with drop shadows"
		    "Spencer Kimball & Ed Mackey"
		    "Spencer Kimball & Ed Mackey"
		    "1997"
		    ""
		    SF-STRING _"Text" "The GIMP"
		    SF-ADJUSTMENT _"Font Size (pixels)" '(100 2 1000 1 10 0 1)
		    SF-FONT   _"Font" "Becker"
		    SF-COLOR  _"Background Color" '(255 255 255)
		    )
