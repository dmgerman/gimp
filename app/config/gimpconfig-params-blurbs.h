begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_define
DECL|macro|TEMP_PATH_BLURB
define|#
directive|define
name|TEMP_PATH_BLURB
define|\
value|"Set the temporary storage directory. Files will appear here " \ "during the course of running the gimp.  Most files will disappear " \ "when the gimp exits, but some files are likely to remain, " \ "such as working palette files, so it is best if this directory " \ "not be one that is shared by other users or is cleared on machine " \ "reboot such as /tmp."
end_define

begin_define
DECL|macro|SWAP_PATH_BLURB
define|#
directive|define
name|SWAP_PATH_BLURB
define|\
value|"Set the swap file location. The gimp uses a tile based memory " \ "allocation scheme. The swap file is used to quickly and easily " \ "swap tiles out to disk and back in. Be aware that the swap file " \ "can easily get very large if the gimp is used with large images. " \ "Also, things can get horribly slow if the swap file is created on " \ "a directory that is mounted over NFS.  For these reasons, it may " \ "be desirable to put your swap file in \"/tmp\"."
end_define

begin_define
DECL|macro|BRUSH_PATH_BLURB
define|#
directive|define
name|BRUSH_PATH_BLURB
define|\
value|"Set the brush search path. This is a colon-separated list of " \ "directories to be searched for brushes."
end_define

begin_define
DECL|macro|PATTERN_PATH_BLURB
define|#
directive|define
name|PATTERN_PATH_BLURB
define|\
value|"Set the pattern search path.  This is a colon-separated list of " \ "directories to be searched for patterns."
end_define

begin_define
DECL|macro|PLUG_IN_PATH_BLURB
define|#
directive|define
name|PLUG_IN_PATH_BLURB
define|\
value|"Set the plug-in search path. This is a colon-separated list of " \ "directories which will be scanned at startup to register new plugins."
end_define

begin_define
DECL|macro|PALETTE_PATH_BLURB
define|#
directive|define
name|PALETTE_PATH_BLURB
define|\
value|"Set the palette search path.  This is a colon-separated list of " \ "directories to be searched for palettes."
end_define

begin_define
DECL|macro|GRADIENT_PATH_BLURB
define|#
directive|define
name|GRADIENT_PATH_BLURB
define|\
value|"Set the gradient search path.  This is a colon-separated list of " \ "directories to be searched for gradients."
end_define

begin_define
DECL|macro|MODULE_PATH_BLURB
define|#
directive|define
name|MODULE_PATH_BLURB
define|\
value|"Set the module search path. This is a colon-separated list of " \ "directories which will be scanned at startup for modules to be loaded."
end_define

begin_define
DECL|macro|DEFAULT_BRUSH_BLURB
define|#
directive|define
name|DEFAULT_BRUSH_BLURB
define|\
value|"Specify a default brush.  This doesn't actually do anything any more, " \ "since the default brush is set as part of the saved device status."
end_define

begin_define
DECL|macro|DEFAULT_PATTERN_BLURB
define|#
directive|define
name|DEFAULT_PATTERN_BLURB
define|\
value|"Specify a default pattern. The pattern is searched for in the " \ "specified pattern path."
end_define

begin_define
DECL|macro|DEFAULT_PALETTE_BLURB
define|#
directive|define
name|DEFAULT_PALETTE_BLURB
define|\
value|"Specify a default palette.  The palette is searched for in the " \ "specified palette path."
end_define

begin_define
DECL|macro|DEGAULT_GRADIENT_BLURB
define|#
directive|define
name|DEGAULT_GRADIENT_BLURB
define|\
value|"Specify a default gradient. The gradient is searched for in the " \ "specified gradient path."
end_define

begin_define
DECL|macro|GAMMA_CORRECTION_BLURB
define|#
directive|define
name|GAMMA_CORRECTION_BLURB
define|\
value|"Set the gamma correction value for the display.  1.0 corresponds to no " \ "gamma correction.  For most displays, gamma correction should be set " \ "to between 2.0 and 2.6 Run the utility \"gamma_correct\" to determine " \ "appropriate values for your display.  XXX is this valid info?  One " \ "important item to keep in mind: Many images that you might get from " \ "outside sources will in all likelihood already be gamma-corrected.  In " \ "these cases, the image will look washed-out if the gimp has " \ "gamma-correction turned on.  If you are going to work with images of " \ "this sort, turn gamma correction off by setting the value to 1.0."
end_define

begin_define
DECL|macro|INSTALL_COLORMAP_BLURB
define|#
directive|define
name|INSTALL_COLORMAP_BLURB
define|\
value|"Install a private colormap by default - not actually used anymore since " \ "the introduction of GdkRgb."
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE_BLURB
define|#
directive|define
name|TILE_CACHE_SIZE_BLURB
define|\
value|"The tile cache is used to make sure the gimp doesn't thrash " \ "tiles between memory and disk. Setting this value higher will " \ "cause the gimp to use less swap space, but will also cause " \ "the gimp to use more memory. Conversely, a smaller cache size " \ "causes the gimp to use more swap space and less memory. " \ "Note: the gimp will still run even if `tile-cache-size' is " \ "set to 0. The actual size can contain a suffix of 'm', 'M', " \ "'k', 'K', 'b' or 'B', which makes the gimp interpret the " \ "size as being specified in megabytes, kilobytes and bytes " \ "respectively. If no suffix is specified the size defaults to " \ "being specified in kilobytes."
end_define

begin_define
DECL|macro|MARCHING_ANTS_SPEED
define|#
directive|define
name|MARCHING_ANTS_SPEED
define|\
value|"Speed of marching ants in the selection outline.  This value is in " \ "milliseconds (less time indicates faster marching)."
end_define

begin_define
DECL|macro|LAST_OPENED_SIZE_BLURB
define|#
directive|define
name|LAST_OPENED_SIZE_BLURB
define|\
value|"How many recently opened image filenames to keep on the File menu."
end_define

begin_define
DECL|macro|UNDO_LEVELS_BLURB
define|#
directive|define
name|UNDO_LEVELS_BLURB
define|\
value|"Set the number of operations kept on the undo stack."
end_define

begin_define
DECL|macro|TRANSPARENCY_TYPE_BLURB
define|#
directive|define
name|TRANSPARENCY_TYPE_BLURB
define|\
value|"Set the manner in which transparency is displayed in images. " \ "Transparency type can be one of 0 - Light Checks, 1 - Mid-Tone Checks, " \ "2 - Dark Checks, 3 - White Only, 4 - Gray Only, or 5 - Black Only."
end_define

begin_define
DECL|macro|TRANSPARENCY_SIZE_BLURB
define|#
directive|define
name|TRANSPARENCY_SIZE_BLURB
define|\
value|"Check size can be one of 0 - Small, 1 - Medium, or 2 - Large"
end_define

begin_define
DECL|macro|PERFECT_MOUSE_BLURB
define|#
directive|define
name|PERFECT_MOUSE_BLURB
define|\
value|"If set to true, the X server is queried for the mouse's current " \ "position on each motion event, rather than relying on the position " \ "hint.  This means painting with large brushes should be more accurate, " \ "but it may be slower.  Perversely, on some X servers turning on this " \ "option results in faster painting."
end_define

begin_define
DECL|macro|COLORMAP_CYCLING_BLURB
define|#
directive|define
name|COLORMAP_CYCLING_BLURB
define|\
value|"Specify that marching ants for selected regions will be drawn with " \ "colormap cycling as oposed to redrawing with different stipple masks. " \ "This color cycling option works only with 8-bit displays."
end_define

begin_define
DECL|macro|DEFAULT_THRESHOLD_BLURB
define|#
directive|define
name|DEFAULT_THRESHOLD_BLURB
define|\
value|"Tools such as fuzzy-select and bucket fill find regions based on a " \ "seed-fill algorithm.  The seed fill starts at the intially selected " \ "pixel and progresses in all directions until the difference of pixel " \ "intensity from the original is greater than a specified threshold. " \ "This value represents the default threshold."
end_define

begin_define
DECL|macro|STINGY_MEMORY_USE_BLURB
define|#
directive|define
name|STINGY_MEMORY_USE_BLURB
define|\
value|"There is always a tradeoff between memory usage and speed.  In most " \ "cases, the GIMP opts for speed over memory.  However, if memory is a " \ "big issue, set stingy-memory-use."
end_define

begin_define
DECL|macro|RESIZE_WINDOWS_ON_ZOOM_BLURB
define|#
directive|define
name|RESIZE_WINDOWS_ON_ZOOM_BLURB
define|\
value|"When zooming into and out of images, this option enables the automatic " \ "resizing of windows. " \  #define RESIZE_WINDOWS_ON_RESIZE_BLURB \ "When the physical image size changes, this option enables the automatic " \ "resizing of windows."
end_define

begin_define
DECL|macro|CURSOR_UPDATING_BLURB
define|#
directive|define
name|CURSOR_UPDATING_BLURB
define|\
value|"Context-dependent cursors are cool.  They are enabled by default. " \ "However, they require overhead that you may want to do without."
end_define

begin_define
DECL|macro|PREVIEW_SIZE_BLURB
define|#
directive|define
name|PREVIEW_SIZE_BLURB
define|\
value|"Set the layer preview size."
end_define

begin_define
DECL|macro|SHOW_RULERS_BLURB
define|#
directive|define
name|SHOW_RULERS_BLURB
define|\
value|"Set the ruler visibility. The default behavior is for rulers to be on. " \ "This can also be toggled with the View->Toggle Rulers command or " \ "shift+control+r."
end_define

begin_define
DECL|macro|SHOW_STATUSBAR_BLURB
define|#
directive|define
name|SHOW_STATUSBAR_BLURB
define|\
value|"Controlling statusbar visibility. The default behavior is to show the " \ "statusbar.  This can also be toggled with the View->Toggle Statusbar " \ "command or shift+control+s."
end_define

begin_define
DECL|macro|INTERPOLATION_MODE_BLURB
define|#
directive|define
name|INTERPOLATION_MODE_BLURB
define|\
value|"Set the level of interpolation.  If set, this option enables cubic " \ "interpolation when scaling or transforming.  By default, GIMP uses " \ "linear interpolation, which is faster, but has poorer quality."
end_define

begin_define
DECL|macro|CONFIRM_ON_CLOSE_BLURB
define|#
directive|define
name|CONFIRM_ON_CLOSE_BLURB
define|\
value|"Ask for confirmation before closing an image without saving. This is " \ "the default."
end_define

begin_define
DECL|macro|SAVE_SESSION_INFO_BLURB
define|#
directive|define
name|SAVE_SESSION_INFO_BLURB
define|\
value|"Remember the positions and sizes of the main dialogs and asks your " \ "window-manager to place them there again the next time you use the " \ "GIMP."
end_define

begin_define
DECL|macro|SAVE_DEVICE_STATUS_BLURB
define|#
directive|define
name|SAVE_DEVICE_STATUS_BLURB
define|\
value|"Remember the current tool, pattern, color, and brush across GIMP " \ "sessions."
end_define

begin_define
DECL|macro|ALWAYS_RESTORE_SESSION_BLURB
define|#
directive|define
name|ALWAYS_RESTORE_SESSION_BLURB
define|\
value|"Let GIMP try to restore your last saved session."
end_define

begin_define
DECL|macro|SHOW_TIPS_BLURB
define|#
directive|define
name|SHOW_TIPS_BLURB
define|\
value|"Set to display a handy GIMP tip on startup."
end_define

begin_define
DECL|macro|SHOW_TOOL_TIPS_BLURB
define|#
directive|define
name|SHOW_TOOL_TIPS_BLURB
define|\
value|"Set to display tooltips."
end_define

begin_define
DECL|macro|DEFAULT_IMAGE_SIZE_BLURB
define|#
directive|define
name|DEFAULT_IMAGE_SIZE_BLURB
define|\
value|"Set the default image size in the File/New dialog."
end_define

begin_define
DECL|macro|DEFAULT_IMAGE_WIDTH_BLURB
define|#
directive|define
name|DEFAULT_IMAGE_WIDTH_BLURB
define|\
value|"Set the default image type in the File/New dialog."
end_define

begin_define
DECL|macro|DEFAULT_UNIT_BLURB
define|#
directive|define
name|DEFAULT_UNIT_BLURB
define|\
value|"Set the default units for new images and for the File/New dialog. " \ "This units will be used for coordinate display when not in dot-for-dot " \ "mode. The default units can be one of inches , millimeters, points or " \ "picas or the identifier of one of the units defined in your user units " \ "database. The default is inches."
end_define

begin_define
DECL|macro|DEFAULT_XRESOLUTION_BLURB
define|#
directive|define
name|DEFAULT_XRESOLUTION_BLURB
define|\
value|"Set the default horizontal resolution for new images and for the " \ "File/New dialog. This value is always in dpi (dots per inch)."
end_define

begin_define
DECL|macro|DEFAULT_YRESOLUTION_BLURB
define|#
directive|define
name|DEFAULT_YRESOLUTION_BLURB
define|\
value|"Set the default vertical resolution for new images and for the " \ "File/New dialog. This value is always in dpi (dots per inch)."
end_define

begin_define
DECL|macro|DEFAULT_RESOLUTION_UNIT
define|#
directive|define
name|DEFAULT_RESOLUTION_UNIT
define|\
value|"Set the units for the display of the default resolution in the " \ "File/New dialog. The default resolution units can be one of inches, " \ "millimeters, points or picas or the identifier of one of the units " \ "defined in your user unit database. The default is inches."
end_define

begin_define
DECL|macro|MONITOR_XRESOLUTION_BLURB
define|#
directive|define
name|MONITOR_XRESOLUTION_BLURB
define|\
value|"Set the monitor's horizontal resolution, in dots per inch.  If set to " \ "0, forces the X server to be queried for both horizontal and vertical " \ "resolution information."
end_define

begin_define
DECL|macro|MONITOR_YRESOLUTION_BLURB
define|#
directive|define
name|MONITOR_YRESOLUTION_BLURB
define|\
value|"Set the monitor's vertical resolution, in dots per inch.  If set to " \ "0, forces the X server to be queried for both horizontal and vertical " \ "resolution information."
end_define

begin_define
DECL|macro|NUM_PROCESSORS_BLURB
define|#
directive|define
name|NUM_PROCESSORS_BLURB
define|\
value|"On multiprocessor machines, if GIMP has been compiled with --enable-mp " \ "this sets how many processors GIMP should use simultaneously."
end_define

begin_define
DECL|macro|IMAGE_TITLE_FORMAT_BLURB
define|#
directive|define
name|IMAGE_TITLE_FORMAT_BLURB
define|\
value|"Set the text to appear in image window titles.  Certain % character " \ "sequences are recognised and expanded as follows:\n" \ "\n" \ "%%  literal percent sign\n" \ "%f  bare filename, or \"Untitled\"\n" \ "%F  full path to file, or \"Untitled\"\n" \ "%p  PDB image id\n" \ "%i  view instance number\n" \ "%t  image type (RGB, indexed, greyscale)\n" \ "%z  zoom factor as a percentage\n" \ "%s  source scale factor\n" \ "%d  destination scale factor\n" \ "%Dx expands to x if the image is dirty, the empty string " \ "otherwise.  The x can be any character, eg %D*.\n" \ "%Cx expands to x if the image is clean, the empty string " \ "otherwise.  The x can be any character, eg %Co.\n" \ "%m  memory used by the image\n" \ "%l  the number of layers\n" \ "%L  the name of the active layer/channel\n" \ "%w  image width in pixels\n" \ "%W  image width in real-world units\n" \ "%h  image height in pixels\n" \ "%H  image height in real-world units\n" \ "%u  unit symbol\n" \ "%U  unit abbreviation\n" \ "The default title format string is \"%f-%p.%i (%t)\"."
end_define

begin_define
DECL|macro|IMAGE_STATUS_FORMAT_BLURB
define|#
directive|define
name|IMAGE_STATUS_FORMAT_BLURB
define|\
value|"Set the text to appear in image window status bars.  See image-title-format " \ "for the list of possible % sequences.\n" \ "\n" \ "The default status format string is \"%f-%p.%i (%t)\"."
end_define

end_unit

