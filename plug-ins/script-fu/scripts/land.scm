; The GIMP -- an image manipulation program
; Copyright (C) 1995 Spencer Kimball and Peter Mattis
; 
; Land --- create a pattern that resembles a Topographic map
; Copyright (C) 1997 Adrian Karstan Likins
; aklikins@eos.ncsu.edu
; 
;
;      This script works on the current gradient you have loaded. 
;      Some suggested gradients: 
;            Land                  (produces a earthlike map)
;            Brushed_aluminum      (looks like the moon)
;  
;
; Thanks to Quartic for helping me debug this thing. 
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



(define (script-fu-land width height seed detail landheight seadepth xscale yscale gradient)
  (let* (
	 (img (car (gimp-image-new width height RGB)))
	 (layer-one (car (gimp-layer-new img width height
					 RGB-IMAGE "Bottom" 100 NORMAL-MODE)))
	)
  (gimp-gradients-set-gradient gradient)
  (gimp-image-undo-disable img)
  (gimp-image-add-layer img layer-one 0)

  (plug-in-solid-noise 1 img layer-one TRUE FALSE seed detail xscale yscale)
  (plug-in-c-astretch 1 img layer-one)
  (set! layer-two (car (gimp-layer-copy layer-one TRUE)))
  (gimp-image-add-layer img layer-two -1)
  (gimp-image-set-active-layer img layer-two)

  (plug-in-gradmap 1 img layer-two)



  (gimp-by-color-select layer-one '(190 190 190) 55 CHANNEL-OP-REPLACE FALSE FALSE 0 FALSE)
  (plug-in-bump-map 1 img layer-two layer-one 135.0 35 landheight 0 0 0 0 TRUE FALSE 0)

  ;(plug-in-c-astretch 1 img layer-two)
  (gimp-selection-invert img)
  (plug-in-bump-map 1 img layer-two layer-one 135.0 35 seadepth 0 0 0 0 TRUE FALSE 0)

  ;(plug-in-c-astretch 1 img layer-two)

  ; uncomment the next line if you want to keep a selection of the "land"
  (gimp-selection-none img)

  (gimp-display-new img)
  (gimp-image-undo-enable img)
))

(script-fu-register "script-fu-land"
		    _"<Toolbox>/Xtns/Script-Fu/Patterns/_Land..."
		    "A Topgraphic map pattern"
		    "Adrian Likins <aklikins@eos.ncsu.edu>"
		    "Adrian Likins"
		    "1997"
		    ""
		    SF-ADJUSTMENT _"Image width" '(256 10 1000 1 10 0 1)
		    SF-ADJUSTMENT _"Image height" '(256 10 1000 1 10 0 1)
		    SF-ADJUSTMENT _"Random seed" '(32 0 15000000 1 10 0 1)
		    SF-ADJUSTMENT _"Detail level" '(4 1 15 1 5 0 0)
		    SF-ADJUSTMENT _"Land height" '(60 1 65 1 10 0 1)
		    SF-ADJUSTMENT _"Sea depth" '(4 1 65 1 10 0 1)
		    SF-ADJUSTMENT _"Scale X" '(4 0.1 16 1 5 0.1 0)
		    SF-ADJUSTMENT _"Scale Y" '(4 0.1 16 1 5 0.1 0)
		    SF-GRADIENT   _"Gradient" "Land 1")
