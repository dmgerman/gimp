; The GIMP -- an image manipulation program
; Copyright (C) 1995 Spencer Kimball and Peter Mattis
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
;
; "Copy Visible"  version 0.11 01/24/98
;     by Adrian Likins <adrian@gimp.org>
;   _heavily_ based on:
;        cyn-merge.scm   version 0.02   10/10/97
;        Copyright (C) 1997 Sven Neumann (neumanns@uni-duesseldorf.de)
; 

(define (script-fu-copy-visible image
			     drawable)
  (let* ((layers (gimp-image-get-layers image))
	 (num-layers (car layers))
	 (num-visi-layers 0)
	 (curlayer (car (gimp-image-get-active-layer image)))
	 (layer-array (cadr layers)))
  
  (if (= curlayer -1)
      (set! curlayer (car (gimp-image-get-active-channel image))))
  
  (gimp-image-undo-group-start image)
	
  ; copy all visible layers and make them invisible
  (set! layer-count 1)
  (set! visi-array (cons-array num-layers))
  (while (<= layer-count num-layers)
	 (set! layer (aref layer-array (- num-layers layer-count)))
	 (aset visi-array (- num-layers layer-count)
	                  (car (gimp-drawable-get-visible layer)))
	 (if (= TRUE (car (gimp-drawable-get-visible layer)))
	     (begin
	       (set! copy (car (gimp-layer-copy layer TRUE)))
	       (gimp-image-add-layer image copy -1)
	       (gimp-drawable-set-visible copy TRUE)
	       (gimp-drawable-set-visible layer FALSE)
	       (set! num-visi-layers (+ num-visi-layers 1))))
	 (set! layer-count (+ layer-count 1)))
  
  ; merge all visible layers
  (if (> num-visi-layers 1)
      (set! merged-layer (car (gimp-image-merge-visible-layers image
                                                               EXPAND-AS-NECESSARY)))
      (if (> num-visi-layers 0)
	  (set! merged-layer copy)))

  (if (> num-visi-layers 0)
      (begin
	(gimp-edit-copy merged-layer)
	(gimp-image-remove-layer image merged-layer)))

  ; restore the layers visibilty
  (set! layer-count 0)
  (while (< layer-count num-layers)
	 (set! layer (aref layer-array layer-count))
	 (gimp-drawable-set-visible layer (aref visi-array layer-count))
	 (set! layer-count (+ layer-count 1)))
  
  (if (= (car (gimp-drawable-is-layer curlayer)) 1)
      (gimp-image-set-active-layer image curlayer)
      (gimp-image-set-active-channel image curlayer))

  (gimp-image-undo-group-end image)
  (gimp-displays-flush)))

(script-fu-register "script-fu-copy-visible"
		    _"<Image>/Edit/Copy _Visible"
		    "Copy the visible selection"
		    "Sven Neumann <sven@gimp.org>, Adrian Likins <adrian@gimp.org>"
		    "Sven Neumann, Adrian Likins"
		    "01/24/1998"
		    "RGB* INDEXED* GRAY*"
		    SF-IMAGE    "Image"    0
		    SF-DRAWABLE "Drawable" 0)
