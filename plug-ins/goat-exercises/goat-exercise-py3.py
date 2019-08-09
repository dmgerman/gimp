#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#    This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

import gi
gi.require_version('Gimp', '3.0')
from gi.repository import Gimp
gi.require_version('Gegl', '0.4')
from gi.repository import Gegl
from gi.repository import GObject
from gi.repository import GLib
from gi.repository import Gio
import sys, os

import gettext
_ = gettext.gettext
def N_(message): return message

class Goat (Gimp.PlugIn):
    ## Parameter: run-mode ##
    @GObject.Property(type=Gimp.RunMode,
                      default=Gimp.RunMode.NONINTERACTIVE,
                      nick="Run mode", blurb="The run mode")
    def run_mode(self):
        """Read-write integer property."""
        return self._run_mode

    @run_mode.setter
    def run_mode(self, run_mode):
        self._run_mode = run_mode

    ## Parameter: image ##
    #@GObject.Property(type=Gimp.ImageID.__gtype__,
    @GObject.Property(type=int,
                      default=0,
                      nick= _("Image"),
                      blurb= _("The input image"))
    def image(self):
        return self._image

    @image.setter
    def image(self, image):
        self._image = image

    ## Parameter: drawable ##
    #@GObject.Property(type=Gimp.DrawableID.__gtype__,
    @GObject.Property(type=int,
                      default=0,
                      nick= _("Drawable"),
                      blurb= _("The input drawable"))
    def drawable(self):
        return self._drawable

    @drawable.setter
    def drawable(self, drawable):
        self._drawable = drawable

    ## GimpPlugIn virtual methods ##
    def do_query_procedures(self):
        # Localization
        self.set_translation_domain("gimp30-python",
                                    Gio.file_new_for_path(Gimp.locale_directory()))

        return [ "goat-exercise-python" ]

    def do_create_procedure(self, name):
        procedure = Gimp.Procedure.new(self, name,
                                       Gimp.PDBProcType.PLUGIN,
                                       self.run, None)
        procedure.set_image_types("RGB*, INDEXED*, GRAY*");
        procedure.set_menu_label("Exercise a goat and a python");
        procedure.set_documentation("Exercise a goat in the Python 3 language",
                                    "Takes a goat for a walk in Python 3",
                                    "");
        procedure.add_menu_path('<Image>/Filters/Development/Goat exercises/');
        procedure.set_attribution("Jehan", "Jehan", "2019");
        procedure.add_argument_from_property(self, "run-mode")
        procedure.add_argument_from_property(self, "image")
        procedure.add_argument_from_property(self, "drawable")

        return procedure

    def run(self, procedure, args, data):
        runmode = args.index(0)

        if runmode == Gimp.RunMode.INTERACTIVE:
            gi.require_version('Gtk', '3.0')
            from gi.repository import Gtk
            gi.require_version('Gdk', '3.0')
            from gi.repository import Gdk

            Gimp.ui_init("palette-offset.py", False)

            dialog = Gimp.Dialog(use_header_bar=True,
                                 title=_("Exercise a goat (Python 3)"),
                                 role="goat-exercise-Python3")

            dialog.add_button("_Cancel", Gtk.ResponseType.CANCEL)
            dialog.add_button("_Source", Gtk.ResponseType.APPLY)
            dialog.add_button("_OK", Gtk.ResponseType.OK)

            geometry = Gdk.Geometry();
            geometry.min_aspect = 0.5;
            geometry.max_aspect = 1.0;
            dialog.set_geometry_hints(None, geometry, Gdk.WindowHints.ASPECT);

            box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=2)
            dialog.get_content_area().add(box)
            box.show()

            # XXX We use printf-style string for sharing the localized
            # string. You may just use recommended Python format() or
            # any style you like in your plug-ins.
            head_text=("This plug-in is an exercise in '%s' to "
                       "demo plug-in creation.\nCheck out the last "
                       "version of the source code online by clicking "
                       "the \"Source\" button." % ("Python 3"))
            label = Gtk.Label(label=head_text)
            box.pack_start(label, False, False, 1)
            label.show()

            contents = None
            # Get the file contents Python-style instead of using
            # GLib.file_get_contents() which returns bytes result, and
            # when converting to string, get newlines as text contents.
            # Rather than wasting time to figure this out, use Python
            # core API!
            with open(os.path.realpath(__file__), 'r') as f:
                contents = f.read()

            if contents is not None:
                scrolled = Gtk.ScrolledWindow()
                scrolled.set_vexpand (True)
                box.pack_start(scrolled, True, True, 1)
                scrolled.show()

                view = Gtk.TextView()
                view.set_wrap_mode(Gtk.WrapMode.WORD)
                view.set_editable(False)
                buffer = view.get_buffer()
                buffer.set_text(contents, -1)
                scrolled.add(view)
                view.show()

            while (True):
                response = dialog.run()
                if response == Gtk.ResponseType.OK:
                    dialog.destroy()
                    break
                elif response == Gtk.ResponseType.APPLY:
                    Gio.app_info_launch_default_for_uri(url, None)
                    continue
                else:
                    dialog.destroy()
                    return procedure.new_return_values(Gimp.PDBStatusType.CANCEL,
                                                       GLib.Error())

        # Parameters are not working fine yet because properties should
        # be Gimp.ImageID/Gimp.DrawableID but we can't make these with
        # pygobject. Until I figure out how to make it work, you could
        # uncomment the following lines instead of using the args value.
        #images = Gimp.image_list()
        #image_id = images[0]
        #drawable_id = Gimp.image_get_active_drawable(image_id)
        drawable_id = args.index(2)

        success, x, y, width, height = Gimp.drawable_mask_intersect(drawable_id);
        if success:
            Gegl.init(None);

            buffer = Gimp.drawable_get_buffer(drawable_id)
            shadow_buffer = Gimp.drawable_get_shadow_buffer(drawable_id)

            graph = Gegl.Node()
            input = graph.create_child("gegl:buffer-source")
            input.set_property("buffer", buffer)
            invert = graph.create_child("gegl:invert")
            output = graph.create_child("gegl:write-buffer")
            output.set_property("buffer", shadow_buffer)
            input.link(invert)
            invert.link(output)
            output.process()

            # This is extremely important in bindings, since we don't
            # unref buffers. If we don't explicitly flush a buffer, we
            # may left hanging forever. This step is usually done
            # during an unref().
            shadow_buffer.flush()

            Gimp.drawable_merge_shadow(drawable_id, True)
            Gimp.drawable_update(drawable_id, x, y, width, height)
            Gimp.displays_flush()
        else:
            retval = procedure.new_return_values(Gimp.PDBStatusType.CALLING_ERROR,
                                                 GLib.Error("No pixels to process in the selected area."))

        return procedure.new_return_values(Gimp.PDBStatusType.SUCCESS, GLib.Error())

Gimp.main(Goat.__gtype__, sys.argv)
