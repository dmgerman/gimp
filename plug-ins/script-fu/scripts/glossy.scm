; glossy-patterned-shadowed-and-bump-mapped-logo
; creates anything you can create with it :)
; (use it wisely, use it in peace...) 
;
; The GIMP -- an image manipulation program
; Copyright (C) 1995 Spencer Kimball and Peter Mattis
;
; glossy gives a glossy outlook to your fonts (unlogical name, isn't it?)
; Copyright (C) 1998 Hrvoje Horvat
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

(define (apply-glossy-logo-effect img
				  logo-layer
				  blend-gradient-text
				  blend-gradient-outline
				  grow-size
				  bg-color
				  use-pattern-text
				  pattern-text
				  use-pattern-outline
				  pattern-outline
				  use-pattern-overlay
				  pattern-overlay
				  noninteractive
				  shadow-toggle
				  s-offset-x
				  s-offset-y)
  (let* ((width (car (gimp-drawable-width logo-layer)))
         (height (car (gimp-drawable-height logo-layer)))
         (bg-layer (car (gimp-layer-new img width height RGB_IMAGE "Background" 100 NORMAL)))
         (grow-me (car (gimp-layer-copy logo-layer TRUE)))

         (old-gradient (car (gimp-gradients-get-gradient)))
         (old-patterns (car (gimp-patterns-get-pattern)))
         (old-fg (car (gimp-palette-get-foreground)))
         (old-bg (car (gimp-palette-get-background))))

    (gimp-image-resize img width height 0 0)
    (gimp-layer-set-name grow-me "Grow-me")
    (gimp-image-add-layer img grow-me 1)
    (gimp-image-add-layer img bg-layer 2)

    (gimp-palette-set-background bg-color)
    (gimp-selection-all img)
    (gimp-bucket-fill bg-layer BG-BUCKET-FILL NORMAL 100 0 FALSE 0 0)
    (gimp-selection-none img)
    (gimp-palette-set-background old-bg)

    (gimp-selection-layer-alpha logo-layer)

; if we are going to use transparent gradients for text, we will (maybe) need to uncomment this
; this clears black letters first so you don't end up with black where the transparent should be
;    (gimp-edit-clear img logo-layer)

    (if (= use-pattern-text TRUE)
      (begin
        (gimp-patterns-set-pattern pattern-text)
        (gimp-bucket-fill logo-layer PATTERN-BUCKET-FILL NORMAL 100 0 FALSE 0 0)
        (gimp-patterns-set-pattern old-patterns)))

    (if (= use-pattern-text FALSE)
      (begin
        (gimp-gradients-set-gradient blend-gradient-text)
        (gimp-blend logo-layer CUSTOM NORMAL LINEAR 100 0 REPEAT-NONE FALSE 0 0 0 0 0 (+ height 5))))

    (gimp-selection-none img)

    (gimp-selection-layer-alpha grow-me)
    (gimp-selection-grow img grow-size)

; if we are going to use transparent gradients for outline, we will (maybe) need to uncomment this
; I didn't put it in the options because there are already enough settings there and anyway, transparent
; gradients will be used very rarely (if ever)
;    (gimp-edit-clear img grow-me)

    (if (= use-pattern-outline TRUE)
      (begin
        (gimp-patterns-set-pattern pattern-outline)
        (gimp-bucket-fill grow-me PATTERN-BUCKET-FILL NORMAL 100 0 FALSE 0 0)
        (gimp-patterns-set-pattern old-patterns)))

    (if (= use-pattern-outline FALSE)
      (begin
        (gimp-gradients-set-gradient blend-gradient-outline)
        (gimp-blend grow-me CUSTOM NORMAL LINEAR 100 0 REPEAT-NONE FALSE 0 0 0 0 0 (+ height 5))))

    (gimp-selection-none img)

    (plug-in-bump-map noninteractive img grow-me logo-layer 110.0 45.0 3 0 0 0 0 TRUE FALSE 0)
    (gimp-layer-set-mode logo-layer SCREEN)

    (if (= use-pattern-overlay TRUE)
      (begin
        (gimp-selection-layer-alpha grow-me)
        (gimp-patterns-set-pattern pattern-overlay)
        (gimp-bucket-fill grow-me PATTERN-BUCKET-FILL OVERLAY 100 0 FALSE 0 0)
        (gimp-patterns-set-pattern old-patterns)
        (gimp-selection-none img)))
   
    (if (= shadow-toggle TRUE)
      (begin
	(gimp-selection-layer-alpha logo-layer)
	(set! dont-drop-me (car (script-fu-drop-shadow img logo-layer s-offset-x s-offset-y 15 '(0 0 0) 80 TRUE)))
        (set! width (car (gimp-image-width img)))
        (set! height (car (gimp-image-height img)))
        (gimp-selection-none img)))

  (gimp-gradients-set-gradient old-gradient)
  (gimp-palette-set-background old-bg)
  (gimp-palette-set-foreground old-fg)))


(define (script-fu-glossy-logo-alpha img
				     logo-layer
				     blend-gradient-text
				     blend-gradient-outline
				     grow-size
				     bg-color
				     use-pattern-text
				     pattern-text
				     use-pattern-outline
				     pattern-outline
				     use-pattern-overlay
				     pattern-overlay
				     noninteractive
				     shadow-toggle
				     s-offset-x
				     s-offset-y)
  (begin
    (gimp-undo-push-group-start img)
    (apply-glossy-logo-effect img logo-layer blend-gradient-text
			      blend-gradient-outline grow-size bg-color
			      use-pattern-text pattern-text
			      use-pattern-outline pattern-outline
			      use-pattern-overlay pattern-overlay
			      noninteractive shadow-toggle
			      s-offset-x s-offset-y)
    (gimp-undo-push-group-end img)
    (gimp-displays-flush)))


(script-fu-register "script-fu-glossy-logo-alpha"
                    _"<Image>/Script-Fu/Alpha to Logo/Glossy..."
                    "Creates anything you can create with it :)"
                    "Hrvoje Horvat (hhorvat@open.hr)"
                    "Hrvoje Horvat"
                    "14/04/1998"
		    "RGBA"
                    SF-IMAGE      "Image" 0
                    SF-DRAWABLE   "Drawable" 0
                    SF-GRADIENT   _"Blend Gradient (Text)" "Shadows_2"
                    SF-GRADIENT   _"Blend Gradient (Outline)" "Shadows_2"
                    SF-ADJUSTMENT _"Outline Size" '(5 0 250 1 10 0 1)
		    SF-COLOR      _"Background Color" '(255 255 255)
		    SF-TOGGLE     _"Use Pattern for Text instead of Gradient" FALSE
		    SF-PATTERN    _"Pattern (Text)" "Electric Blue"
		    SF-TOGGLE     _"Use Pattern for Outline instead of Gradient" FALSE
		    SF-PATTERN    _"Pattern (Outline)" "Electric Blue"
		    SF-TOGGLE     _"Use Pattern Overlay" FALSE
		    SF-PATTERN    _"Pattern (Overlay)" "Parque #1"
		    SF-TOGGLE     _"Default Bumpmap Settings" TRUE
		    SF-TOGGLE     _"Shadow" TRUE
		    SF-ADJUSTMENT _"Shadow X Offset" '(8 0 100 1 10 0 1)
                    SF-ADJUSTMENT _"Shadow Y Offset" '(8 0 100 1 10 0 1)
		    )


(define (script-fu-glossy-logo text
			       size
			       font
			       blend-gradient-text
			       blend-gradient-outline
			       grow-size
			       bg-color
			       use-pattern-text
			       pattern-text
			       use-pattern-outline
			       pattern-outline
			       use-pattern-overlay
			       pattern-overlay
			       noninteractive
			       shadow-toggle
			       s-offset-x
			       s-offset-y)
  (let* ((img (car (gimp-image-new 256 256 RGB)))
	 (text-layer (car (gimp-text-fontname img -1 0 0 text 30 TRUE size PIXELS font))))
    (gimp-image-undo-disable img)
    (gimp-layer-set-name text-layer text)
    (apply-glossy-logo-effect img text-layer blend-gradient-text
			      blend-gradient-outline grow-size bg-color
			      use-pattern-text pattern-text
			      use-pattern-outline pattern-outline
			      use-pattern-overlay pattern-overlay
			      noninteractive shadow-toggle
			      s-offset-x s-offset-y)
    (gimp-image-undo-enable img)
    (gimp-display-new img)))

(script-fu-register "script-fu-glossy-logo"
                    _"<Toolbox>/Xtns/Script-Fu/Logos/Glossy..."
                    "Creates anything you can create with it :)"
                    "Hrvoje Horvat (hhorvat@open.hr)"
                    "Hrvoje Horvat"
                    "14/04/1998"
                    ""
                    SF-STRING     _"Text" "Galaxy"
                    SF-ADJUSTMENT _"Font Size (pixels)" '(100 2 1000 1 10 0 1)
                    SF-FONT       _"Font" "-*-Eras-*-r-*-*-24-*-*-*-p-*-*-*"
                    SF-GRADIENT   _"Blend Gradient (Text)" "Shadows_2"
                    SF-GRADIENT   _"Blend Gradient (Outline)" "Shadows_2"
                    SF-ADJUSTMENT _"Outline Size" '(5 0 250 1 10 0 1)
		    SF-COLOR      _"Background Color" '(255 255 255)
		    SF-TOGGLE     _"Use Pattern for Text instead of Gradient" FALSE
		    SF-PATTERN    _"Pattern (Text)" "Electric Blue"
		    SF-TOGGLE     _"Use Pattern for Outline instead of Gradient" FALSE
		    SF-PATTERN    _"Pattern (Outline)" "Electric Blue"
		    SF-TOGGLE     _"Use Pattern Overlay" FALSE
		    SF-PATTERN    _"Pattern (Overlay)" "Parque #1"
		    SF-TOGGLE     _"Default Bumpmap Settings" TRUE
		    SF-TOGGLE     _"Shadow" TRUE
		    SF-ADJUSTMENT _"Shadow X Offset" '(8 0 100 1 10 0 1)
                    SF-ADJUSTMENT _"Shadow Y Offset" '(8 0 100 1 10 0 1)
		    )
