;  CRYSTAL
;  Create a text effect that simulates crystal

(define (set-pt a index x y)
  (prog1
   (aset a (* index 2) x)
   (aset a (+ (* index 2) 1) y)))

(define (spline1)
  (let* ((a (cons-array 18 'byte)))
    (set-pt a 0 0 0)
    (set-pt a 1 31 235)
    (set-pt a 2 63 23)
    (set-pt a 3 95 230)
    (set-pt a 4 127 25)
    (set-pt a 5 159 210)
    (set-pt a 6 191 20)
    (set-pt a 7 223 240)
    (set-pt a 8 255 31)
    a))

(define (crystal-brush brush-size)
  (cond ((<= brush-size 5) "Circle (05)")
	((<= brush-size 7) "Circle (07)")
	((<= brush-size 9) "Circle (09)")
	((<= brush-size 11) "Circle (11)")
	((<= brush-size 13) "Circle (13)")
	((<= brush-size 15) "Circle (15)")
	((<= brush-size 17) "Circle (17)")
	(else "Circle Fuzzy (19)")))

(define (shadows val)
  (/ (* 0.96 val) 2.55))

(define (midtones val)
  (/ val 2.55))

(define (highlights val)
  (/ (* 1.108 val) 2.55))

(define (rval col)
  (car col))

(define (gval col)
  (cadr col))

(define (bval col)
  (caddr col))

(define (sota-scale val scale chrome-factor)
  (* (sqrt val) (* scale chrome-factor)))

(define (copy-layer-crystal dest-image dest-drawable source-image source-drawable)
  (gimp-selection-all dest-image)
  (gimp-edit-clear dest-image dest-drawable)
  (gimp-selection-none dest-image)
  (gimp-selection-all source-image)
  (gimp-edit-copy source-image source-drawable)
      (let ((floating-sel (car (gimp-edit-paste dest-image dest-drawable FALSE))))
	(gimp-floating-sel-anchor floating-sel)))

(define (script-fu-crystal-logo chrome-factor text size font bg-img env-map)
  (let* ((img (car (gimp-image-new 256 256 GRAY)))
	 (back-img (car (gimp-file-load 1 bg-img bg-img)))
	 (back-layer (car (gimp-image-active-drawable back-img)))
	 (banding-img (car (gimp-file-load 1 env-map env-map)))
	 (banding-layer (car (gimp-image-active-drawable banding-img)))
	 (banding-height (car (gimp-drawable-height banding-layer)))
	 (banding-width (car (gimp-drawable-width banding-layer)))
	 (banding-type (car (gimp-drawable-type banding-layer)))
	 (b-size (sota-scale size 2 chrome-factor))
	 (offx1 (sota-scale size 0.33 chrome-factor))
	 (offy1 (sota-scale size 0.25 chrome-factor))
	 (offx2 (sota-scale size (- 0.33) chrome-factor))
	 (offy2 (sota-scale size (- 0.25) chrome-factor))
	 (feather (sota-scale size 0.5 chrome-factor))
	 (blur (sota-scale size 0.5 chrome-factor))
	 (displace (sota-scale size 0.25 chrome-factor))
	 (brush-size (sota-scale size 0.5 chrome-factor))
	 (text-layer (car (gimp-text img -1 0 0 text b-size TRUE size PIXELS "*" font "*" "*" "*" "*")))
	 (width (car (gimp-drawable-width text-layer)))
	 (height (car (gimp-drawable-height text-layer)))
	 (tile-ret (plug-in-tile 1 back-img back-layer width height TRUE))
	 (tile-img (car tile-ret))
	 (tile-layer (cadr tile-ret))
	 (tile-width (car (gimp-drawable-width tile-layer)))
	 (tile-height (car (gimp-drawable-height tile-layer)))
	 (tile-type (car (gimp-drawable-type tile-layer)))
	 (bg-layer (car (gimp-layer-new img tile-width tile-height tile-type "BG-Layer" 100 NORMAL)))
	 (layer1 (car (gimp-layer-new img banding-width banding-height banding-type "Layer1" 100 NORMAL)))
	 (layer2 (car (gimp-layer-new img width height GRAYA_IMAGE "Layer 2" 100 DIFFERENCE)))
	 (layer3 (car (gimp-layer-new img width height GRAYA_IMAGE "Layer 3" 100 NORMAL)))
	 (layer-mask 0)
	 (layer-mask2 0)
	 (disp-map 0)
	 (old-fg (car (gimp-palette-get-foreground)))
	 (old-bg (car (gimp-palette-get-background)))
	 (old-brush (car (gimp-brushes-get-brush))))
    (gimp-image-delete back-img)
    (gimp-image-disable-undo img)
    (gimp-image-resize img width height 0 0)
    (gimp-image-add-layer img layer3 0)
    (gimp-image-add-layer img layer2 0)
    (gimp-palette-set-background '(255 255 255))
    (gimp-selection-none img)
    (gimp-edit-fill img layer2)
    (gimp-edit-fill img layer3)
    (gimp-layer-set-visible text-layer FALSE)

    (gimp-selection-layer-alpha img text-layer)
    (gimp-palette-set-background '(0 0 0))
    (gimp-selection-translate img offx1 offy1)
    (gimp-selection-feather img feather)
    (gimp-edit-fill img layer2)
    (gimp-selection-translate img (* 2 offx2) (* 2 offy2))
    (gimp-edit-fill img layer3)
    (gimp-selection-none img)
    (set! layer2 (car (gimp-image-merge-visible-layers img CLIP-TO-IMAGE)))
    (gimp-invert img layer2)

    (copy-layer-crystal img layer1 banding-img banding-layer)
    (gimp-image-delete banding-img)
    (gimp-image-add-layer img layer1 0)
    (gimp-layer-scale layer1 width height FALSE)
    (plug-in-gauss-iir 1 img layer1 10 TRUE TRUE)
    (gimp-layer-set-opacity layer1 50)
    (set! layer1 (car (gimp-image-merge-visible-layers img CLIP-TO-IMAGE)))
    (gimp-curves-spline img layer1 0 18 (spline1))

    (set! layer-mask (car (gimp-layer-create-mask layer1 BLACK-MASK)))
    (gimp-image-add-layer-mask img layer1 layer-mask)
    (gimp-selection-layer-alpha img text-layer)
    (gimp-palette-set-background '(255 255 255))
    (gimp-edit-fill img layer-mask)

    (set! disp-map (car (gimp-selection-save img)))
    (gimp-brushes-set-brush (crystal-brush brush-size))
    (gimp-palette-set-foreground '(0 0 0))
    (gimp-edit-stroke img disp-map)
    (gimp-selection-none img)

    (plug-in-gauss-rle 1 img disp-map blur TRUE TRUE)
    (gimp-levels img disp-map 0 0 255 1.0 96 255)

    (if (= (car (gimp-drawable-color bg-layer)) 1)
	(gimp-convert-rgb img))

   

    (copy-layer-crystal img bg-layer tile-img tile-layer)
    (gimp-image-delete tile-img)
    (gimp-image-add-layer img bg-layer 2)
    (set! layer2 (car (gimp-layer-copy bg-layer TRUE)))
    (gimp-image-add-layer img layer2 1)

    (plug-in-displace 1 img layer2 displace displace TRUE TRUE disp-map disp-map 0)
    (set! layer-mask2 (car (gimp-layer-create-mask layer2 BLACK-MASK)))
    (gimp-image-add-layer-mask img layer2 layer-mask2)
    (gimp-selection-layer-alpha img text-layer)
    (gimp-palette-set-background '(255 255 255))
    (gimp-edit-fill img layer-mask2)

    (gimp-selection-none img)
    (gimp-levels img layer2 0 0 200 1.5 50 255)
    (gimp-layer-set-mode layer1 OVERLAY)

    (plug-in-gauss-rle 1 img text-layer blur TRUE TRUE)
    (gimp-layer-set-preserve-trans text-layer TRUE)
    (gimp-palette-set-background '(0 0 0))
    (gimp-edit-fill img text-layer)
    (gimp-layer-set-mode text-layer OVERLAY)
    (gimp-layer-translate text-layer offx1 offy1)

    (gimp-image-remove-channel img disp-map)

    (gimp-layer-set-visible text-layer TRUE)
    (gimp-layer-set-name layer1 "Crystal")
    (gimp-layer-set-name layer2 "Interior")
    (gimp-layer-set-name bg-layer "Background")
    (gimp-layer-set-name text-layer "Shadow")

    (gimp-palette-set-foreground old-fg)
    (gimp-palette-set-background old-bg)
    (gimp-brushes-set-brush old-brush)
    (gimp-image-enable-undo img)
    (gimp-display-new img)))


(script-fu-register "script-fu-crystal-logo"
		    "<Toolbox>/Xtns/Script-Fu/Logos/Crystal"
		    "Crystal/Gel effect which displaces the image underneath"
		    "Spencer Kimball"
		    "Spencer Kimball"
		    "1997"
		    ""
		    SF-VALUE "Chrome Factor" "1.0"
		    SF-STRING "Text String" "Crystal"
		    SF-VALUE "Font Size (in pixels)" "150"
		    SF-STRING "Font" "Engraver"
		    SF-STRING "Background Img" (string-append "" gimp-data-dir "/scripts/texture1.jpg")
		    SF-STRING "Environment Map" (string-append "" gimp-data-dir "/scripts/beavis.jpg"))
