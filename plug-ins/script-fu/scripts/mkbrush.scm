; The GIMP -- an image manipulation program
; Copyright (C) 1995 Spencer Kimball and Peter Mattis
;
; Make-Brush - a script for the script-fu program
; by Seth Burgess 1997 <sjburges@ou.edu>
;
; 18-Dec-2000 fixed to work with the new convention (not inverted) of
;             gbr saver (jtl@gimp.org)
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


(define (script-fu-make-brush-rectangular description width height spacing )
    (begin
        (let* (
            (img (car (gimp-image-new width height GRAY)))
             (drawable (car (gimp-layer-new img width height GRAY-IMAGE "MakeBrush" 100 NORMAL-MODE)))

     ; Save old foregound and background colors

     (old-fg-color (car (gimp-palette-get-foreground)))
     (old-bg-color (car (gimp-palette-get-background)))

     ; construct variables 

     (data-dir (car (gimp-gimprc-query "gimp_dir")))
     (filename (string-append data-dir
               "/brushes/r"
               (number->string width)
               "x"
               (number->string height)
               ".gbr")
               )
     (desc (string-append description " "
                  (number->string width)
                  "x"
                  (number->string height)
                  )
      )
    )

    (gimp-image-undo-disable img)
    (gimp-image-add-layer img drawable 0)

; Actual code starts...
    (gimp-palette-set-background '(255 255 255))
    (gimp-drawable-fill drawable BACKGROUND-FILL)
    (gimp-palette-set-background '(0 0 0))
    (gimp-rect-select img 0 0 width height REPLACE FALSE 0)
    
    (gimp-edit-fill    drawable BACKGROUND-FILL)
    (file-gbr-save 1 img drawable filename "" spacing desc)
    
    (gimp-brushes-refresh)
    (gimp-brushes-set-brush desc)

; Terminate, restoring old bg.

    (gimp-selection-none img)
    (gimp-palette-set-foreground old-fg-color)
    (gimp-palette-set-background old-bg-color)
    (gimp-image-undo-enable img)
    (gimp-image-delete img)
    )
  )
)

; Register with the PDB

(script-fu-register "script-fu-make-brush-rectangular"
            _"<Toolbox>/Xtns/Script-Fu/Make Brush/_Rectangular..."
            "Create size of brush"
            "Seth Burgess <sjburges@ou.edu>"
            "Seth Burgess"
            "1997"
            ""
            SF-STRING     _"Description" "Rectangle"
            SF-ADJUSTMENT _"Width" '(20 1 200 1 10 0 1)
            SF-ADJUSTMENT _"Height" '(20 1 200 1 10 0 1)
            SF-ADJUSTMENT _"Spacing" '(25 1 100 1 10 1 0)
            )


(define (script-fu-make-brush-rectangular-feathered description width height feathering spacing)
    (begin
        (let* (
            (widthplus (+ width feathering))
            (heightplus (+ height feathering))
            (img (car (gimp-image-new widthplus heightplus GRAY)))
             (drawable (car (gimp-layer-new img widthplus heightplus GRAY-IMAGE "MakeBrush" 100 NORMAL-MODE)))

     ; Save old foregound and background colors

     (old-fg-color (car (gimp-palette-get-foreground)))
     (old-bg-color (car (gimp-palette-get-background)))
     
    (data-dir (car (gimp-gimprc-query "gimp_dir")))
    (filename (string-append data-dir
               "/brushes/r"
               (number->string width)
               "x"
               (number->string height)
               "f"
               (number->string feathering)
               ".gbr")
               )
     (desc (string-append description " "
                  (number->string width)
                  "x"
                  (number->string height)
                  ","
                  (number->string feathering)
                  )
      )
    )

    (gimp-image-undo-disable img)
    (gimp-image-add-layer img drawable 0)

; Actual code starts...
    (gimp-palette-set-background '(255 255 255))
    (gimp-drawable-fill drawable BACKGROUND-FILL)
    (gimp-palette-set-background '(0 0 0))
    (cond ((< 0 feathering)
           (gimp-rect-select img (/ feathering 2) (/ feathering 2) width height REPLACE TRUE feathering))
          ((>= 0 feathering)
           (gimp-rect-select img 0 0 width height REPLACE FALSE 0))
          )
    (gimp-edit-fill    drawable BACKGROUND-FILL)
    (file-gbr-save 1 img drawable filename "" spacing desc)
    
    (gimp-brushes-refresh)
    (gimp-brushes-set-brush desc)

; Terminate, restoring old bg.

    (gimp-selection-none img)
    (gimp-palette-set-foreground old-fg-color)
    (gimp-palette-set-background old-bg-color)
    (gimp-image-undo-enable img)
    (gimp-image-delete img)
    )
  )
)

; Register with the PDB

(script-fu-register "script-fu-make-brush-rectangular-feathered"
            _"<Toolbox>/Xtns/Script-Fu/Make Brush/Re_ctangular, Feathered..."
            "Create size of brush"
            "Seth Burgess <sjburges@ou.edu>"
            "Seth Burgess"
            "1997"
            ""
            SF-STRING     _"Description" "Rectangle"
            SF-ADJUSTMENT _"Width" '(20 1 200 1 10 0 1)
            SF-ADJUSTMENT _"Height" '(20 1 200 1 10 0 1)
            SF-ADJUSTMENT _"Feathering" '(4 1 100 1 10 0 1)
            SF-ADJUSTMENT _"Spacing" '(25 1 100 1 10 1 0)
            )

(define (script-fu-make-brush-elliptical description width height spacing)
    (begin
        (let* (
            (img (car (gimp-image-new width height GRAY)))
             (drawable (car (gimp-layer-new img width height GRAY-IMAGE "MakeBrush" 100 NORMAL-MODE)))

     ; Save old foregound and background colors

     (old-fg-color (car (gimp-palette-get-foreground)))
     (old-bg-color (car (gimp-palette-get-background)))

     ; Construct variables...

     (data-dir (car (gimp-gimprc-query "gimp_dir")))
     (filename (string-append data-dir
			      "/brushes/e"
			      (number->string width)
			      "x"
			      (number->string height)
			      ".gbr"))
     (desc (string-append description " "
			  (number->string width)
			  "x"
			  (number->string height)
			  )
	   )
     )
	  ; End of variables.  Couple of necessary things here.

    (gimp-image-undo-disable img)
    (gimp-image-add-layer img drawable 0)

; Actual code starts...
    (gimp-palette-set-background '(255 255 255))
    (gimp-drawable-fill drawable BACKGROUND-FILL)
    (gimp-palette-set-background '(0 0 0))
    (gimp-ellipse-select img 0 0 width height REPLACE TRUE FALSE 0)
    
    (gimp-edit-fill    drawable BACKGROUND-FILL)
    (file-gbr-save 1 img drawable filename "" spacing desc)
    
    (gimp-brushes-refresh)
    (gimp-brushes-set-brush desc)

; Terminate, restoring old bg.

    (gimp-selection-none img)
    (gimp-palette-set-foreground old-fg-color)
    (gimp-palette-set-background old-bg-color)
    (gimp-image-undo-enable img)
    (gimp-image-delete img)
    )
  )
)

; Register with the PDB

(script-fu-register "script-fu-make-brush-elliptical"
            _"<Toolbox>/Xtns/Script-Fu/Make Brush/_Elliptical..."
            "Create size of brush"
            "Seth Burgess <sjburges@ou.edu>"
            "Seth Burgess"
            "1997"
            ""
            SF-STRING _"Description" "Ellipse"
            SF-ADJUSTMENT _"Width" '(20 1 200 1 10 0 1)
            SF-ADJUSTMENT _"Height" '(20 1 200 1 10 0 1)
            SF-ADJUSTMENT _"Spacing" '(25 1 100 1 10 1 0)
            )


(define (script-fu-make-brush-elliptical-feathered description width height feathering spacing)
    (begin
        (let* (
	    (widthplus (+ feathering width)) ; add 3 for blurring
            (heightplus (+ feathering height))
            (img (car (gimp-image-new widthplus heightplus GRAY)))
             (drawable (car (gimp-layer-new img widthplus heightplus GRAY-IMAGE "MakeBrush" 100 NORMAL-MODE)))

     ; Save old foregound and background colors

     (old-fg-color (car (gimp-palette-get-foreground)))
     (old-bg-color (car (gimp-palette-get-background)))

     ; Construct variables...
     (data-dir (car (gimp-gimprc-query "gimp_dir")))
     (filename (string-append data-dir
			      "/brushes/e"
			      (number->string width)
			      "x"
			      (number->string height)
			      "f"
			      (number->string feathering)
			      ".gbr"))
     (desc (string-append description " "
			  (number->string width)
			  "x"
			  (number->string height)
			  " f"
			  (number->string feathering)
			  )
	   )
     
     )
; End of variables.  Couple of necessary things here.

    (gimp-image-undo-disable img)
    (gimp-image-add-layer img drawable 0)

; Actual code starts...
    (gimp-palette-set-background '(255 255 255))
    (gimp-drawable-fill drawable BACKGROUND-FILL)
    (gimp-palette-set-background '(0 0 0))
    (cond ((> feathering 0)   ; keep from taking out gimp with stupid entry. 
        (gimp-ellipse-select img (/ feathering 2) (/ feathering 2) width height REPLACE TRUE TRUE feathering))
          ((<= feathering 0)
        (gimp-ellipse-select img 0 0 width height REPLACE TRUE FALSE 0))
	)
    (gimp-edit-fill    drawable BACKGROUND-FILL)
    (file-gbr-save 1 img drawable filename "" spacing desc)
    
    (gimp-brushes-refresh)
    (gimp-brushes-set-brush desc)

; Terminate, restoring old bg.

    (gimp-selection-none img)
    (gimp-palette-set-foreground old-fg-color)
    (gimp-palette-set-background old-bg-color)
    (gimp-image-undo-enable img)
    (gimp-image-delete img)
    )
  )
)

; Register with the PDB

(script-fu-register "script-fu-make-brush-elliptical-feathered"
            _"<Toolbox>/Xtns/Script-Fu/Make Brush/Elli_ptical, Feathered..."
            "Makes a feathered elliptical brush of specified size"
            "Seth Burgess <sjburges@ou.edu>"
            "Seth Burgess"
            "1997"
            ""
            SF-STRING _"Description" "Ellipse"
            SF-ADJUSTMENT _"Width" '(20 1 200 1 10 0 1)
            SF-ADJUSTMENT _"Height" '(20 1 200 1 10 0 1)
            SF-ADJUSTMENT _"Feathering" '(4 1 100 1 10 0 1)
            SF-ADJUSTMENT _"Spacing" '(25 1 100 1 10 1 0)
            )
