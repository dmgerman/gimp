; The GIMP -- an image manipulation program
; Copyright (C) 1995 Spencer Kimball and Peter Mattis
; 
; script-fu-paste-as-brush
; Based on select-to-brush by Copyright (c) 1997 Adrian Likins
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


(define (script-fu-paste-as-brush name
				  filename
				  spacing)

    (set! brush-image (car (gimp-edit-paste-as-new)))
    (set! brush-draw (car (gimp-image-get-active-drawable brush-image)))
    (set! type (car (gimp-drawable-type brush-draw)))

    (if (= type GRAYA-IMAGE)
        (begin
	  (gimp-context-push)
          (gimp-context-set-background '(255 255 255))
          (set! brush-draw (car (gimp-image-flatten brush-image)))
	  (gimp-context-pop))
        ())

    (set! path (string-append gimp-directory
			      "/brushes/"
			      filename
			      (number->string brush-image)
			      ".gbr"))

    (file-gbr-save 1 brush-image brush-draw path "" spacing name)

    (gimp-image-delete brush-image)

    (gimp-brushes-refresh)
    (gimp-context-set-brush name))

(script-fu-register "script-fu-paste-as-brush"
		    _"New _Brush..."
		    "Pastes the clipboard into a new brush"
		    "Michael Natterer <mitch@gimp.org>"
		    "Michael Natterer"
		    "2005-09-25"
		    ""
		    SF-STRING     _"Brush name"  "My Brush"
		    SF-STRING     _"File name"   "mybrush"
		    SF-ADJUSTMENT _"Spacing"     '(25 0 1000 1 1 1 0))

(script-fu-menu-register "script-fu-paste-as-brush"
			 "<Image>/Edit/Paste as")
