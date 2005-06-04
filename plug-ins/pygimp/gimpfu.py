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

'''Simple interface to writing GIMP plugins in python.

Instead of worrying about all the user interaction, saving last used values
and everything, the gimpfu module can take care of it for you.  It provides
a simple register() function that will register your plugin if needed, and
cause your plugin function to be called when needed.

Gimpfu will also handle showing a user interface for editing plugin parameters
if the plugin is called interactively, and will also save the last used
parameters, so the RUN_WITH_LAST_VALUES run_type will work correctly.  It
will also make sure that the displays are flushed on completion if the plugin
was run interactively.

When registering the plugin, you do not need to worry about specifying
the run_type parameter.  And if the plugin is an image plugin (the menu
path starts with <Image>/), the image and drawable parameters are also
automatically added.

A typical gimpfu plugin would look like this:
  from gimpfu import *

  def plugin_func(image, drawable, args):
              #do what plugins do best
  register(
              "plugin_func",
              "blurb",
              "help message",
              "author",
              "copyright",
              "year",
              "<Image>/Somewhere/My plugin",
              "*",
              [(PF_STRING, "arg", "The argument", "default-value")],
              [],
              plugin_func)
  main()

The call to "from gimpfu import *" will import all the gimp constants into
the plugin namespace, and also import the symbols gimp, pdb, register and
main.  This should be just about all any plugin needs.  You can use any
of the PF_* constants below as parameter types, and an appropriate user
interface element will be displayed when the plugin is run in interactive
mode.  Note that the the PF_SPINNER and PF_SLIDER types expect a fifth
element in their description tuple -- a 3-tuple of the form (lower,upper,step),
which defines the limits for the slider or spinner.'''

import string as _string
import gimp, gimpenums
from gimpenums import *
pdb = gimp.pdb

class error(RuntimeError):pass
class CancelError(RuntimeError):pass

PF_INT8        = PDB_INT8
PF_INT16       = PDB_INT16
PF_INT32       = PDB_INT32
PF_INT         = PF_INT32
PF_FLOAT       = PDB_FLOAT
PF_STRING      = PDB_STRING
PF_VALUE       = PF_STRING
#PF_INT8ARRAY   = PDB_INT8ARRAY
#PF_INT16ARRAY  = PDB_INT16ARRAY
#PF_INT32ARRAY  = PDB_INT32ARRAY
#PF_INTARRAY    = PF_INT32ARRAY
#PF_FLOATARRAY  = PDB_FLOATARRAY
#PF_STRINGARRAY = PDB_STRINGARRAY
PF_COLOR       = PDB_COLOR
PF_COLOUR      = PF_COLOR
PF_REGION      = PDB_REGION
#PF_DISPLAY     = PDB_DISPLAY
PF_IMAGE       = PDB_IMAGE
PF_LAYER       = PDB_LAYER
PF_CHANNEL     = PDB_CHANNEL
PF_DRAWABLE    = PDB_DRAWABLE
#PF_SELECTION   = PDB_SELECTION
#PF_BOUNDARY    = PDB_BOUNDARY
#PF_PATH        = PDB_PATH
#PF_STATUS      = PDB_STATUS

PF_TOGGLE      = 1000
PF_BOOL        = PF_TOGGLE
PF_SLIDER      = 1001
PF_SPINNER     = 1002
PF_ADJUSTMENT  = PF_SPINNER

PF_FONT        = 1003
PF_FILE        = 1004
PF_BRUSH       = 1005
PF_PATTERN     = 1006
PF_GRADIENT    = 1007
PF_RADIO       = 1008
PF_TEXT        = 1009
PF_PALETTE     = 1010

_type_mapping = {
    PF_INT8        : PDB_INT8,
    PF_INT16       : PDB_INT16,
    PF_INT32       : PDB_INT32,
    PF_FLOAT       : PDB_FLOAT,
    PF_STRING      : PDB_STRING,
    #PF_INT8ARRAY   : PDB_INT8ARRAY,
    #PF_INT16ARRAY  : PDB_INT16ARRAY,
    #PF_INT32ARRAY  : PDB_INT32ARRAY,
    #PF_FLOATARRAY  : PDB_FLOATARRAY,
    #PF_STRINGARRAY : PDB_STRINGARRAY,
    PF_COLOUR      : PDB_COLOR,
    PF_REGION      : PDB_REGION,
    PF_IMAGE       : PDB_IMAGE,
    PF_LAYER       : PDB_LAYER,
    PF_CHANNEL     : PDB_CHANNEL,
    PF_DRAWABLE    : PDB_DRAWABLE,

    PF_TOGGLE      : PDB_INT32,
    PF_SLIDER      : PDB_FLOAT,
    PF_SPINNER     : PDB_INT32,

    PF_FONT        : PDB_STRING,
    PF_FILE        : PDB_STRING,
    PF_BRUSH       : PDB_STRING,
    PF_PATTERN     : PDB_STRING,
    PF_GRADIENT    : PDB_STRING,
    PF_RADIO       : PDB_STRING,
    PF_TEXT        : PDB_STRING,
    PF_PALETTE     : PDB_STRING,
}

_registered_plugins_ = {}

def register(func_name, blurb, help, author, copyright, date, menupath,
                 imagetypes, params, results, function,
                 on_query=None, on_run=None):
    '''This is called to register a new plugin.'''

    # First perform some sanity checks on the data
    def letterCheck(str):
        allowed = _string.letters + _string.digits + '_'
        for ch in str:
            if not ch in allowed:
                    return 0
        else:
            return 1

    if not letterCheck(func_name):
        raise error, "function name contains illegal characters"

    for ent in params:
        if len(ent) < 4:
            raise error, ("parameter definition must contain at least 4 "
                        "elements (%s given: %s)" % (len(ent), ent))

        if type(ent[0]) != gimpenums.PDBArgType and \
           type(ent[0]) != int:
            raise error, "parameter types must be PDB argument types"

        if not letterCheck(ent[1]):
            raise error, "parameter name contains illegal characters"

    for ent in results:
        if len(ent) < 3:
            raise error, ("result definition must contain at least 3 elements "
                        "(%s given: %s)" % (len(ent), ent))

        if type(ent[0]) != type(42):
            raise error, "result types must be integers"

        if not letterCheck(ent[1]):
            raise error, "result name contains illegal characters"

    if menupath[:8] == '<Image>/' or \
       menupath[:7] == '<Load>/' or \
       menupath[:7] == '<Save>/' or \
       menupath[:10] == '<Toolbox>/':
        plugin_type = PLUGIN
    else:
        raise error, "Invalid menu path"

    if not func_name[:7] == 'python_' and \
       not func_name[:10] == 'extension_' and \
       not func_name[:8] == 'plug_in_' and \
       not func_name[:5] == 'file_':
           func_name = 'python_fu_' + func_name

    _registered_plugins_[func_name] = (blurb, help, author, copyright,
                                       date, menupath, imagetypes,
                                       plugin_type, params, results,
                                       function, on_query, on_run)

file_params = [(PDB_STRING, "filename", "The name of the file"),
               (PDB_STRING, "raw_filename", "The name of the file")]

def _query():
    for plugin in _registered_plugins_.keys():
        (blurb, help, author, copyright, date,
         menupath, imagetypes, plugin_type,
         params, results, function,
         on_query, on_run) = _registered_plugins_[plugin]

        def make_params(params):
            return [(_type_mapping[x[0]], x[1], x[2]) for x in params]

        params = make_params(params)
        # add the run mode argument ...
        params.insert(0, (PDB_INT32, "run_mode",
                                     "Interactive, Non-Interactive"))
        if plugin_type == PLUGIN:
            if menupath[:7] == '<Load>/':
                params[1:1] = file_params
            elif menupath[:10] != '<Toolbox>/':
                params.insert(1, (PDB_IMAGE, "image",
                                  "The image to work on"))
                params.insert(2, (PDB_DRAWABLE, "drawable",
                                  "The drawable to work on"))
                if menupath[:7] == '<Save>/':
                    params[3:3] = file_params

        results = make_params(results)
        gimp.install_procedure(plugin, blurb, help, author, copyright,
                               date, menupath, imagetypes, plugin_type,
                               params, results)
        if on_query:
            on_query()

def _get_defaults(func_name):
    import gimpshelf
    (blurb, help, author, copyright, date,
     menupath, imagetypes, plugin_type,
     params, results, function,
     on_query, on_run) = _registered_plugins_[func_name]

    key = "python-fu-save--" + func_name

    if gimpshelf.shelf.has_key(key):
        return gimpshelf.shelf[key]
    else:
        # return the default values
        return [x[3] for x in params]

def _set_defaults(func_name, defaults):
    import gimpshelf

    key = "python-fu-save--" + func_name
    gimpshelf.shelf[key] = defaults

def _interact(func_name, start_params):
    (blurb, help, author, copyright, date,
     menupath, imagetypes, plugin_type,
     params, results, function,
     on_query, on_run) = _registered_plugins_[func_name]

    def run_script(run_params):
        params = start_params + tuple(run_params)
        return apply(function, params)

    # short circuit for no parameters ...
    if len(params) == 0:
         return run_script([])

    import pygtk
    pygtk.require('2.0')

    import gtk
    import gimpui

    gtk.rc_parse(gimp.gtkrc())

    defaults = _get_defaults(func_name)

    class EntryValueError(Exception):
        pass

    def error_dialog(parent, msg):
        dlg = gtk.MessageDialog(parent, gtk.DIALOG_DESTROY_WITH_PARENT,
                                        gtk.MESSAGE_WARNING, gtk.BUTTONS_CLOSE,
                                        msg)
        dlg.run()
        dlg.destroy()

    # define a mapping of param types to edit objects ...
    class StringEntry(gtk.Entry):
        def __init__(self, default=''):
            gtk.Entry.__init__(self)
            self.set_text(str(default))

        def get_value(self):
            return self.get_text()

    class TextEntry(gtk.ScrolledWindow):
        def __init__ (self, default=''):
            gtk.ScrolledWindow.__init__(self)
            self.set_shadow_type(gtk.SHADOW_IN)
            
            self.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
            self.set_size_request(100, -1)

            self.view = gtk.TextView()
            self.add(self.view)
            self.view.show()

            self.buffer = self.view.get_buffer()

            self.set_value(str(default))
            
        def set_value(self, text):
            self.buffer.set_text(text)

        def get_value(self):
            return self.buffer.get_text(self.buffer.get_start_iter(),
                                        self.buffer.get_end_iter())

    class IntEntry(StringEntry):
        def get_value(self):
            try:
                return int(self.get_text())
            except ValueError, e:
                raise EntryValueError, e.args

    class FloatEntry(StringEntry):
            def get_value(self):
                try:
                    return float(self.get_text())
                except ValueError, e:
                    raise EntryValueError, e.args

#    class ArrayEntry(StringEntry):
#            def get_value(self):
#                return eval(self.get_text(), {}, {})

    class SliderEntry(gtk.HScale):
        # bounds is (upper, lower, step)
        def __init__(self, default=0, bounds=(0, 100, 5)):
            self.adj = gtk.Adjustment(default, bounds[0],
                                      bounds[1], bounds[2],
                                      bounds[2], 0)
            gtk.HScale.__init__(self, self.adj)

        def get_value(self):
            return self.adj.value

    class SpinnerEntry(gtk.SpinButton):
        # bounds is (upper, lower, step)
        def __init__(self, default=0, bounds=(0, 100, 5)):
            self.adj = gtk.Adjustment(default, bounds[0],
                                        bounds[1], bounds[2],
                                        bounds[2], 0)
            gtk.SpinButton.__init__(self, self.adj, 1, 0)

        def get_value(self):
            try:
                return int(self.get_text())
            except ValueError, e:
                raise EntryValueError, e.args

    class ToggleEntry(gtk.ToggleButton):
        def __init__(self, default=0):
            gtk.ToggleButton.__init__(self)

            self.label = gtk.Label("No")
            self.add(self.label)
            self.label.show()

            self.connect("toggled", self.changed)

            self.set_active(default)

        def changed(self, tog):
            if tog.get_active():
                self.label.set_text("Yes")
            else:
                self.label.set_text("No")

        def get_value(self):
            return self.get_active()

    class RadioEntry(gtk.Frame):
        def __init__(self, default=0, items=(("Yes", 1), ("No", 0))):
            gtk.Frame.__init__(self)

            box = gtk.VBox(False, 5)
            self.add(box)
            box.show()

            button = None

            for (label, value) in items:
                button = gtk.RadioButton(button, label)
                box.pack_start(button)
                button.show()

                button.connect("toggled", self.changed, value)

                if value == default:
                    button.set_active(True)
                    self.active_value = value

        def changed(self, radio, value):
            if radio.get_active():
                self.active_value = value

        def get_value(self):
            return self.active_value

    _edit_mapping = {
            PF_INT8        : IntEntry,
            PF_INT16       : IntEntry,
            PF_INT32       : IntEntry,
            PF_FLOAT       : FloatEntry,
            PF_STRING      : StringEntry,
            #PF_INT8ARRAY   : ArrayEntry,
            #PF_INT16ARRAY  : ArrayEntry,
            #PF_INT32ARRAY  : ArrayEntry,
            #PF_FLOATARRAY  : ArrayEntry,
            #PF_STRINGARRAY : ArrayEntry,
            PF_COLOUR      : gimpui.ColourSelector,
            PF_REGION      : IntEntry,  # should handle differently ...
            PF_IMAGE       : gimpui.ImageSelector,
            PF_LAYER       : gimpui.LayerSelector,
            PF_CHANNEL     : gimpui.ChannelSelector,
            PF_DRAWABLE    : gimpui.DrawableSelector,

            PF_TOGGLE      : ToggleEntry,
            PF_SLIDER      : SliderEntry,
            PF_SPINNER     : SpinnerEntry,
            PF_RADIO       : RadioEntry,

            PF_FONT        : gimpui.FontSelector,
            PF_FILE        : gimpui.FileSelector,
            PF_BRUSH       : gimpui.BrushSelector,
            PF_PATTERN     : gimpui.PatternSelector,
            PF_GRADIENT    : gimpui.GradientSelector,
            PF_PALETTE     : gimpui.PaletteSelector,
            PF_TEXT        : TextEntry
    }

    if on_run:
        on_run()

    need_progress = menupath[:8] != '<Image>/'

    tooltips = gtk.Tooltips()

    dialog = gtk.Dialog(func_name, None, 0,
                        (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL,
                        gtk.STOCK_OK, gtk.RESPONSE_OK))

    hbox = gtk.HBox(False, 5)
    hbox.set_border_width(5)
    dialog.vbox.pack_start(hbox, expand=False)
    hbox.show()

    table = gtk.Table(len(params), 2, False)
    table.set_border_width(5)
    table.set_row_spacings(4)
    table.set_col_spacings(10)
    hbox.pack_end(table, expand=False)
    table.show()

    vbox = gtk.VBox(False, 10)
    hbox.pack_start(vbox, expand=False)
    vbox.show()

    pix = _get_logo()
    if pix:
        vbox.pack_start(pix, expand=False)
        pix.show()

    label = gtk.Label(blurb)
    label.set_line_wrap(True)
    label.set_justify(gtk.JUSTIFY_LEFT)
    label.set_size_request(100, -1)
    vbox.pack_start(label, expand=False)
    label.show()

    progress_callback = None

    def response(dlg, id):
        if id == gtk.RESPONSE_OK:
            params = []

            try:
                for wid in edit_wids:
                    params.append(wid.get_value())
            except EntryValueError:
                error_dialog(dialog, 'Invalid input for "%s"' % wid.desc)
            else:
                _set_defaults(func_name, params)
                dialog.res = run_script(params)

        if progress_callback:
            gimp.progress_uninstall(progress_callback)

        gtk.main_quit()

    dialog.connect("response", response)

    edit_wids = []
    for i in range(len(params)):
        pf_type = params[i][0]
        name = params[i][1]
        desc = params[i][2]
        def_val = defaults[i]

        label = gtk.Label(desc)
        label.set_alignment(1.0, 0.5)
        table.attach(label, 1,2, i,i+1, xoptions=gtk.FILL)
        label.show()

        if pf_type in (PF_SPINNER, PF_SLIDER, PF_RADIO):
            wid = _edit_mapping[pf_type](def_val, params[i][4])
        else:
            wid = _edit_mapping[pf_type](def_val)
        
        table.attach(wid, 2,3, i,i+1, yoptions=0)

        if pf_type != PF_TEXT:
            tooltips.set_tip(wid, desc, None)         
        else:
            #Attach tip to TextView, not to ScrolledWindow
            tooltips.set_tip(wid.view, desc, None)         
        wid.show()

        wid.desc = desc
        edit_wids.append(wid)

    if need_progress:
        frame = gtk.Frame("Script Progress")
        frame.set_border_width(5)
        dialog.vbox.pack_start(frame)
        frame.show()

        vbox = gtk.VBox(False, 5)
        vbox.set_border_width(5)
        frame.add(vbox)
        vbox.show()

        progress_label = gtk.Label("(none)")
        progress_label.set_alignment(0.0, 0.5)
        vbox.pack_start(progress_label)
        progress_label.show()

        progress = gtk.ProgressBar()
        progress.set_text(" ")
        vbox.pack_start(progress)
        progress.show()

        def progress_update(message=-1, fraction=None):
            if message == -1:
                pass
            elif message:
                progress.set_text(message)
            else:
                progress.set_text(" ")

            if fraction is not None:
		if fraction < 0:
		    progress.pulse()
		else:
		    progress.set_fraction(fraction)

            while gtk.events_pending():
                gtk.main_iteration()

        def progress_start(message, cancelable):
            progress_update(message, 0.0)

        def progress_end():
            progress_update(None, 0.0)

        def progress_text(message):
            progress_update(message)

        def progress_value(percentage):
            progress_update(fraction=percentage)

        progress_callback = gimp.progress_install(progress_start, progress_end,
                                                  progress_text, progress_value)

    tooltips.enable()
    dialog.show()

    gtk.main()

    if hasattr(dialog, 'res'):
        res = dialog.res
        dialog.destroy()
        return res
    else:
        dialog.destroy()
        raise CancelError

def _run(func_name, params):
    run_mode = params[0]
    plugin_type = _registered_plugins_[func_name][7]
    menupath = _registered_plugins_[func_name][5]
    func = _registered_plugins_[func_name][10]

    if plugin_type == PLUGIN and menupath[:10] != '<Toolbox>/':
        if menupath[:7] == '<Save>/':
            end = 5
        else:
            end = 3

        start_params = params[1:end]
        extra_params = params[end:]
    else:
        start_params = ()
        extra_params = params[1:]

    if run_mode == RUN_INTERACTIVE:
        try:
            res = _interact(func_name, start_params)
        except CancelError:
            return
    else:
        if run_mode == RUN_WITH_LAST_VALS:
            extra_params = _get_defaults(func_name)

        params = start_params + tuple(extra_params)
        res = apply(func, params)

    if run_mode != RUN_NONINTERACTIVE:
        gimp.displays_flush()

    return res

def main():
    '''This should be called after registering the plugin.'''
    gimp.main(None, None, _query, _run)

def fail(msg):
    '''Display and error message and quit'''
    gimp.message(msg)
    raise error, msg

def _get_logo():
    import gtk, gobject

    import os.path
    logofile = os.path.join(os.path.dirname(__file__), 'pygimp-logo.png')

    try:
        pixbuf = gtk.gdk.pixbuf_new_from_file(logofile)
    except gobject.GError, e:
        return None

    image = gtk.Image()
    image.set_from_pixbuf(pixbuf)

    return image
