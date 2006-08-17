#!/usr/bin/env python

#   Gimp-Python - allows the writing of Gimp plugins in Python.
#   Copyright (C) 1997  James Henstridge <james@daa.com.au>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

import math
from gimpfu import *

def sphere(radius, light, shadow, bg_colour, sphere_colour):
    if radius < 1:
        radius = 1

    width = int(radius * 3.75)
    height = int(radius * 2.5)

    img = gimp.Image(width, height, RGB)

    drawable = gimp.Layer(img, "Sphere Layer", width, height,
                          RGB_IMAGE, 100, NORMAL_MODE)

    radians = light * math.pi / 180

    cx = width / 2
    cy = height / 2

    light_x = cx + radius * 0.6 * math.cos(radians)
    light_y = cy - radius * 0.6 * math.sin(radians)

    light_end_x = cx + radius * math.cos(math.pi + radians)
    light_end_y = cy - radius * math.sin(math.pi + radians)

    offset = radius * 0.1

    old_fg = gimp.get_foreground()
    old_bg = gimp.get_background()

    img.disable_undo()
    img.add_layer(drawable, 0)

    gimp.set_foreground(sphere_colour)

    gimp.set_background(bg_colour)
    pdb.gimp_edit_fill(drawable, BACKGROUND_FILL)

    gimp.set_background(20, 20, 20)

    if (light >= 45 and light <= 75 or light <= 135 and
        light >= 105) and shadow:
        shadow_w = radius * 2.5 * math.cos(math.pi + radians)
        shadow_h = radius * 0.5
        shadow_x = cx
        shadow_y = cy + radius * 0.65

        if shadow_w < 0:
            shadow_x = cx + shadow_w
            shadow_w = -shadow_w

        pdb.gimp_ellipse_select(img, shadow_x, shadow_y, shadow_w, shadow_h,
                                CHANNEL_OP_REPLACE, True, True, 7.5)
        pdb.gimp_edit_bucket_fill(drawable, BG_BUCKET_FILL,
                                  MULTIPLY_MODE, 100, 0, False, 0, 0)

    pdb.gimp_ellipse_select(img, cx - radius, cy - radius, 2 * radius,
                            2 * radius, CHANNEL_OP_REPLACE, True, False, 0)
    pdb.gimp_edit_blend(drawable, FG_BG_RGB_MODE, NORMAL_MODE, GRADIENT_RADIAL,
                        100, offset, REPEAT_NONE, False, False, 0, 0, True,
                        light_x, light_y, light_end_x, light_end_y)

    pdb.gimp_selection_none(img)

    gimp.set_background(old_bg)
    gimp.set_foreground(old_fg)

    img.enable_undo()

    disp = gimp.Display(img)

register(
    "python-fu-sphere",
    "Simple spheres with drop shadows",
    "Simple spheres with drop shadows (based on script-fu version)",
    "James Henstridge",
    "James Henstridge",
    "1997-1999",
    "<Toolbox>/Xtns/Languages/Python-Fu/Test/_Sphere",
    "",
    [
        (PF_INT, "radius", "Radius for sphere", 100),
        (PF_SLIDER, "light", "Light angle", 45, (0,360,1)),
        (PF_TOGGLE, "shadow", "Shadow?", 1),
        (PF_COLOR, "bg-color", "Background", (255,255,255)),
        (PF_COLOR, "sphere-color", "Sphere", (255,0,0))
    ],
    [],
    sphere)

main()
