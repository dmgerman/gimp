; The GIMP -- an image manipulation program
; Copyright (C) 1995 Spencer Kimball and Peter Mattis
; 
; Alien Glow themed arrows for web pages
; Copyright (c) 1997 Adrian Likins
; aklikins@eos.ncsu.edu
;
;
; Based on code from
; Federico Mena Quintero
; federico@nuclecu.unam.mx
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

(define (make-point x
		    y)
  (cons x y))

(define (point-x p)
  (car p))

(define (point-y p)
  (cdr p))

(define (point-list->double-array point-list)
  (define (convert points array pos)
    (if (not (null? points))
	(begin
	  (aset array (* 2 pos) (point-x (car points)))
	  (aset array (+ 1 (* 2 pos)) (point-y (car points)))
	  (convert (cdr points) array (+ pos 1)))))

  (let* ((how-many (length point-list))
	 (a (cons-array (* 2 how-many) 'double)))
    (convert point-list a 0)
    a))

(define (make-arrow size
		    offset)
  (list (make-point offset offset)
	(make-point (- size offset) (/ size 2))
	(make-point offset (- size offset))))


(define (rotate-points points
		       size
		       orientation)
  (if (null? points)
      '()
      (let* ((p (car points))
	     (px (point-x p))
	     (py (point-y p)))
	(cons (cond (= orientation 0) (make-point px py))           ; right
	      (= orientation 1) (make-point (- size px) py))  ; left
		    (= orientation 2) (make-point py (- size px)))  ; up
		    (= orientation 3) (make-point py px))           ; down
  (rotate-points (cdr points) size orientation))


(define (script-fu-alien-glow-right-arrow size
					  orientation
					  glow-color
					  bg-color
					  flatten)
  (let* ((img (car (gimp-image-new size size RGB)))
	 (grow-amount (/ size 12))
	 (blur-radius (/ size 3))
	 (offset (/ size 6))
	 (ruler-layer (car (gimp-layer-new img size size  RGBA_IMAGE "Ruler" 100 NORMAL)))
	 (glow-layer (car (gimp-layer-new img size size  RGBA_IMAGE "Alien Glow" 100 NORMAL)))
	 (bg-layer (car (gimp-layer-new img size size  RGB_IMAGE "Back" 100 NORMAL)))
	 (big-arrow (point-list->double-array (rotate-points (make-arrow size offset) size orientation)))
	 (old-fg (car (gimp-palette-get-foreground)))
	 (old-bg (car (gimp-palette-get-background))))


    (gimp-image-undo-disable img)
    ;(gimp-image-resize img (+ length height) (+ height height) 0 0)
    (gimp-image-add-layer img bg-layer 1)
    (gimp-image-add-layer img glow-layer -1)
    (gimp-image-add-layer img ruler-layer -1)
    
    (gimp-edit-clear glow-layer)
    (gimp-edit-clear ruler-layer)

    (gimp-free-select img 6 big-arrow REPLACE TRUE FALSE 0)

    (gimp-palette-set-foreground '(103 103 103))
    (gimp-palette-set-background '(0 0 0))

    (gimp-blend ruler-layer FG-BG-RGB NORMAL
		SHAPEBURST-ANGULAR 100 0 REPEAT-NONE FALSE
		FALSE 0 0 TRUE
		0 0 size size)
    
    (gimp-selection-grow img grow-amount)
    (gimp-palette-set-foreground glow-color)
    (gimp-edit-fill glow-layer FG-IMAGE-FILL)

    (gimp-selection-none img)


    (plug-in-gauss-rle 1 img glow-layer blur-radius TRUE TRUE)

    (gimp-palette-set-background bg-color)
    (gimp-edit-fill bg-layer BG-IMAGE-FILL)
    
    (gimp-palette-set-background old-bg)
    (gimp-palette-set-foreground old-fg)

    (if (= flatten TRUE)
	(gimp-image-flatten img))
    (gimp-image-undo-enable img)
    (gimp-display-new img)))

(script-fu-register "script-fu-alien-glow-right-arrow"
		    _"<Toolbox>/Xtns/Script-Fu/Web Page Themes/Alien Glow/_Arrow..."
		    "Create an X-file deal"
		    "Adrian Likins"
		    "Adrian Likins"
		    "1997"
		    ""
		    SF-ADJUSTMENT _"Size"            '(32 5 150 1 10 0 1)
		    SF-OPTION     _"Orientation"     '(_"Right" 
							_"Left" 
							_"Up" 
							_"Down")
		    SF-COLOR      _"Glow Color"       '(63 252 0)
		    SF-COLOR      _"Background Color" '(0 0 0)
		    SF-TOGGLE     _"Flatten Image"    TRUE)
