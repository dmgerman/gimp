;  CHROME-LOGOS

(define (script-fu-chrome-logo text size font bg-color)
  (let* ((img (car (gimp-image-new 256 256 RGB)))
	 (b-size (* size 0.2))
	 (offx1 (* size 0.04))
	 (offy1 (* size 0.03))
	 (offx2 (* size (- 0.04)))
	 (offy2 (* size (- 0.03)))
	 (feather (* size 0.05))
	 (text-layer (car (gimp-text-fontname img -1 0 0 text b-size TRUE size PIXELS font)))
	 (width (car (gimp-drawable-width text-layer)))
	 (height (car (gimp-drawable-height text-layer)))
	 (layer1 (car (gimp-layer-new img width height RGBA_IMAGE "Layer 1" 100 DIFFERENCE)))
	 (layer2 (car (gimp-layer-new img width height RGBA_IMAGE "Layer 2" 100 DIFFERENCE)))
	 (layer3 (car (gimp-layer-new img width height RGBA_IMAGE "Layer 3" 100 NORMAL)))
	 (shadow (car (gimp-layer-new img width height RGBA_IMAGE "Drop Shadow" 100 NORMAL)))
	 (background (car (gimp-layer-new img width height RGB_IMAGE "Background" 100 NORMAL)))
	 (layer-mask (car (gimp-layer-create-mask layer1 BLACK-MASK)))
	 (old-fg (car (gimp-palette-get-foreground)))
	 (old-bg (car (gimp-palette-get-background))))
    (gimp-image-disable-undo img)
    (gimp-image-resize img width height 0 0)
    (gimp-image-add-layer img background 1)
    (gimp-image-add-layer img shadow 1)
    (gimp-image-add-layer img layer3 1)
    (gimp-image-add-layer img layer2 1)
    (gimp-image-add-layer img layer1 1)
    (gimp-palette-set-background '(255 255 255))
    (gimp-selection-none img)
    (gimp-edit-fill layer1)
    (gimp-edit-fill layer2)
    (gimp-edit-fill layer3)
    (gimp-edit-clear shadow)
    (gimp-selection-layer-alpha text-layer)
    (gimp-layer-set-visible text-layer FALSE)
    (gimp-layer-set-visible shadow FALSE)
    (gimp-layer-set-visible background FALSE)
    (gimp-palette-set-background '(0 0 0))
    (gimp-edit-fill layer1)
    (gimp-selection-translate img offx1 offy1)
    (gimp-selection-feather img feather)
    (gimp-edit-fill layer2)
    (gimp-selection-translate img (* 2 offx2) (* 2 offy2))
    (gimp-edit-fill layer3)
    (gimp-selection-none img)
    (set! layer1 (car (gimp-image-merge-visible-layers img CLIP-TO-IMAGE)))
    (gimp-invert layer1)
    (gimp-image-add-layer-mask img layer1 layer-mask)
    (gimp-selection-layer-alpha text-layer)
    (gimp-palette-set-background '(255 255 255))
    (gimp-selection-feather img feather)
    (gimp-edit-fill layer-mask)
    (gimp-palette-set-background '(0 0 0))
    (gimp-selection-translate img offx1 offy1)
    (gimp-edit-fill shadow)
    (gimp-selection-none img)
    (gimp-palette-set-background bg-color)
    (gimp-edit-fill background)
    (gimp-image-remove-layer img text-layer)
    (gimp-layer-set-visible shadow TRUE)
    (gimp-layer-set-visible background TRUE)
    (gimp-layer-set-name layer1 text)
    (gimp-palette-set-foreground old-fg)
    (gimp-palette-set-background old-bg)
    (gimp-image-enable-undo img)
    (gimp-display-new img)))

(script-fu-register "script-fu-chrome-logo"
		    "<Toolbox>/Xtns/Script-Fu/Logos/Chrome"
		    "Somewhat simplistic, but cool chromed logos"
		    "Spencer Kimball"
		    "Spencer Kimball & Peter Mattis"
		    "1997"
		    ""
		    SF-STRING "Text String" "The GIMP"
		    SF-ADJUSTMENT "Font Size (pixels)" '(100 2 1000 1 10 0 1)
		    SF-FONT "Font" "-*-Bodoni-*-r-*-*-24-*-*-*-p-*-*-*"
		    SF-COLOR "Background Color" '(191 191 191))
