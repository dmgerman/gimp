#!/usr/bin/env python

import string
import struct
import inspect
import os.path

import gimp
from gimpfu import *

escape_table = {
    '&': '&amp;',
    '<': '&lt;',
    '>': '&gt;',
    '"': '&quot;'
}

style_def = """body {
   width: 100%%;
   font-size: %dpx;
   background-color: #000000;
   color: #ffffff;
}
"""

preamble = """<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>css color html by The GIMP</title>
%s
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
</head>
<body>
<pre>
"""

postamble = """\n</pre>\n</html>\n"""

def python_colorhtml(img, drawable, filename, raw_filename,
                     source_type, characters, size, separate):
    width = drawable.width
    height = drawable.height
    bpp = drawable.bpp

    if not drawable.is_rgb or drawable.has_alpha:
        return

    gimp.tile_cache_ntiles(width / gimp.tile_width() + 1)

    html = file(filename, 'w')

    if separate:
        dirname, cssfile = os.path.split(filename)
        cssfile = os.path.splitext(cssfile)[0] + '.css'
        cssname = os.path.join(dirname, cssfile)

        css = file(cssname, 'w')

    if source_type == 0:
        chars = file(inspect.getsourcefile(python_colorhtml)).read()
    elif source_type == 1:
        chars = file(characters).read()
    elif source_type == 2:
        chars = characters

    allchars = string.maketrans('', '')

    goodchars = string.digits + string.ascii_letters + string.punctuation
    badchars = ''.join([c for c in allchars if c not in goodchars])

    chars = chars.translate(allchars, badchars)

    data = []

    for c in chars:
        data.append(escape_table.get(c, c))

    if data:
        data.reverse()
    else:
        data = list('X' * 80)

    pr = drawable.get_pixel_rgn(0, 0, width, height, FALSE, FALSE)

    gimp.progress_init("Saving '%s' as COLORHTML..." % filename)

    style = style_def % size

    if separate:
        ss = '<link rel="stylesheet" type="text/css" href="%s">' % cssfile
        css.write(style)
    else:
        ss = '<style type="text/css">\n%s</style>' % style

    html.write(preamble % ss)

    colors = {}
    chars = []

    for y in range(0, height):
        row = pr[0:width, y]

        while len(chars) < width:
            chars[0:0] = data

        for pixel in RowIterator(row, bpp):
            color = '%02x%02x%02x' % pixel
            style = 'background-color:black; color:#%s;' % color
            char = chars.pop()

            if separate:
                if color not in colors:
                    css.write('span.N%s { %s }\n' % (color, style))
                    colors[color] = 1

                html.write('<span class="N%s">%s</span>' % (color, char))

            else:
                html.write('<span style="%s">%s</span>' % (style, char))

        html.write('\n')

        gimp.progress_update(y / float(height))

    html.write(postamble)

    html.close()

    if separate:
        css.close()

def register_save():
    gimp.register_save_handler("file_colorhtml_save", "colorhtml", "")

class RowIterator:
    def __init__(self, row, bpp):
        self.row = row
        self.bpp = bpp

        self.start = 0
        self.stop = bpp

        self.length = len(row)
        self.fmt = 'B' * bpp

    def __iter__(self):
        return iter(self.get_pixel, None)

    def get_pixel(self):
        if self.stop > self.length:
            return None

        pixel = struct.unpack(self.fmt, self.row[self.start:self.stop])

        self.start += self.bpp
        self.stop += self.bpp

        return pixel

register(
    "file_colorhtml_save",
    "Saves the image as colored html text",
    "Saves the image as colored html text (based on perl version by Marc Lehmann)",
    "Manish Singh",
    "Manish Singh",
    "2003",
    "<Save>/COLORHTML",
    "RGB",
    [
        (PF_RADIO, "source", "Where to take the characters from", 0,
                   (("sourcecode", 0), ("textfile", 1), ("filename", 2))),
        (PF_FILE, "characters", "The filename to read or the characters to use",
                  ""),
        (PF_INT, "font_size", "The font size in pixels", 10),
        (PF_BOOL, "separate", "Separate CSS file", TRUE)
    ],
    [],
    python_colorhtml,
    on_query=register_save)

main()
