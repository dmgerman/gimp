; The GIMP -- an image manipulation program
; Copyright (C) 1995 Spencer Kimball and Peter Mattis
; 
; Selection to Image
; Copyright (c) 1997 Adrian Likins
; aklikins@eos.ncsu.edu
;
; Takes the Current selection and saves it as a seperate image.
;
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


(define (script-fu-selection-to-image image drawable)
  (let* (
	 (draw-type (car (gimp-drawable-type-with-alpha drawable)))
	 (image-type (car (gimp-image-base-type image)))
	 (old-bg (car (gimp-palette-get-background))))

    (set! selection-bounds (gimp-selection-bounds image))
    (set! select-offset-x (cadr selection-bounds))
    (set! select-offset-y (caddr selection-bounds))
    (set! selection-width (- (cadr (cddr selection-bounds)) select-offset-x))
    (set! selection-height (- (caddr (cddr selection-bounds)) select-offset-y))

    (gimp-image-undo-disable image)
    
    (if (= (car (gimp-selection-is-empty image)) TRUE)
	(begin
	  (gimp-selection-layer-alpha drawable)
	  (set! active-selection (car (gimp-selection-save image)))
	  (set! from-selection FALSE))
	(begin
	  (set! from-selection TRUE)
	  (set! active-selection (car (gimp-selection-save image)))))

    (gimp-edit-copy drawable)

    (set! new-image (car (gimp-image-new selection-width selection-height image-type)))
    (set! new-draw (car (gimp-layer-new new-image selection-width selection-height draw-type "Selection" 100 NORMAL)))
    (gimp-image-add-layer new-image new-draw 0)
    (gimp-drawable-fill new-draw BG-IMAGE-FILL)

    (let ((floating-sel (car (gimp-edit-paste new-draw FALSE))))
      (gimp-floating-sel-anchor floating-sel)
      )

    (gimp-palette-set-background old-bg)
    (gimp-image-undo-enable image)
    (gimp-image-set-active-layer image drawable)
    (gimp-display-new new-image)
    (gimp-displays-flush)))

(script-fu-register "script-fu-selection-to-image"
		    _"<Image>/Script-Fu/Selection/To _Image"
		    "Convert a selection to an image"
		    "Adrian Likins <adrian@gimp.org>"
		    "Adrian Likins"
		    "10/07/97"
		    "RGB* GRAY*"
		    SF-IMAGE "Image" 0
		    SF-DRAWABLE "Drawable" 0)
