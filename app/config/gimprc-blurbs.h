begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  gimprc-blurbs.h  --  descriptions for gimprc properties  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RC_BLURBS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RC_BLURBS_H__
define|#
directive|define
name|__GIMP_RC_BLURBS_H__
end_define

begin_comment
comment|/*  Not all strings defined here are used in the user interface  *  and only those that are should be marked for translation.  */
end_comment

begin_define
DECL|macro|BRUSH_PATH_BLURB
define|#
directive|define
name|BRUSH_PATH_BLURB
define|\
value|"Sets the brush search path."
end_define

begin_define
DECL|macro|CANVAS_PADDING_MODE_BLURB
define|#
directive|define
name|CANVAS_PADDING_MODE_BLURB
define|\
value|N_("Specifies how the area around the image should be drawn.")
end_define

begin_define
DECL|macro|CANVAS_PADDING_COLOR_BLURB
define|#
directive|define
name|CANVAS_PADDING_COLOR_BLURB
define|\
value|N_("Sets the canvas padding color used if the padding mode is set to " \    "custom color.")
end_define

begin_define
DECL|macro|COLORMAP_CYCLING_BLURB
define|#
directive|define
name|COLORMAP_CYCLING_BLURB
define|\
value|N_("Specify that marching ants for selected regions will be drawn with " \    "colormap cycling as opposed to be drawn as animated lines.  This color " \    "cycling option works only with 8-bit displays.")
end_define

begin_define
DECL|macro|CONFIRM_ON_CLOSE_BLURB
define|#
directive|define
name|CONFIRM_ON_CLOSE_BLURB
define|\
value|N_("Ask for confirmation before closing an image without saving.")
end_define

begin_define
DECL|macro|CURSOR_MODE_BLURB
define|#
directive|define
name|CURSOR_MODE_BLURB
define|\
value|N_("Sets the mode of cursor the GIMP will use.")
end_define

begin_define
DECL|macro|CURSOR_UPDATING_BLURB
define|#
directive|define
name|CURSOR_UPDATING_BLURB
define|\
value|N_("Context-dependent cursors are cool.  They are enabled by default. " \    "However, they require overhead that you may want to do without.")
end_define

begin_define
DECL|macro|DEFAULT_BRUSH_BLURB
define|#
directive|define
name|DEFAULT_BRUSH_BLURB
define|\
value|"Specify a default brush.  The brush is searched for in the " \ "specified brush path."
end_define

begin_define
DECL|macro|DEFAULT_COMMENT_BLURB
define|#
directive|define
name|DEFAULT_COMMENT_BLURB
define|\
value|"Sets the default comment."
end_define

begin_define
DECL|macro|DEFAULT_DOT_FOR_DOT_BLURB
define|#
directive|define
name|DEFAULT_DOT_FOR_DOT_BLURB
define|\
value|N_("When set to yes, this will ensure that each pixel of an image gets " \    "mapped to a pixel on the screen.")
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_BLURB
define|#
directive|define
name|DEFAULT_GRADIENT_BLURB
define|\
value|"Specify a default gradient.  The gradient is searched for in the " \ "specified gradient path."
end_define

begin_define
DECL|macro|DEFAULT_IMAGE_WIDTH_BLURB
define|#
directive|define
name|DEFAULT_IMAGE_WIDTH_BLURB
define|\
value|"Sets the default image width in the File/New dialog."
end_define

begin_define
DECL|macro|DEFAULT_IMAGE_HEIGHT_BLURB
define|#
directive|define
name|DEFAULT_IMAGE_HEIGHT_BLURB
define|\
value|"Sets the default image height in the File/New dialog."
end_define

begin_define
DECL|macro|DEFAULT_IMAGE_TYPE_BLURB
define|#
directive|define
name|DEFAULT_IMAGE_TYPE_BLURB
define|\
value|"Sets the default image type in the File/New dialog."
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
DECL|macro|DEFAULT_RESOLUTION_UNIT_BLURB
define|#
directive|define
name|DEFAULT_RESOLUTION_UNIT_BLURB
define|\
value|"Sets the units for the display of the default resolution in the " \ "File/New dialog."
end_define

begin_define
DECL|macro|DEFAULT_THRESHOLD_BLURB
define|#
directive|define
name|DEFAULT_THRESHOLD_BLURB
define|\
value|N_("Tools such as fuzzy-select and bucket fill find regions based on a " \    "seed-fill algorithm.  The seed fill starts at the intially selected " \    "pixel and progresses in all directions until the difference of pixel " \    "intensity from the original is greater than a specified threshold. " \    "This value represents the default threshold.")
end_define

begin_define
DECL|macro|DEFAULT_UNIT_BLURB
define|#
directive|define
name|DEFAULT_UNIT_BLURB
define|\
value|"Sets the default unit for new images and for the File/New dialog. " \ "This units will be used for coordinate display when not in dot-for-dot " \ "mode."
end_define

begin_define
DECL|macro|DEFAULT_XRESOLUTION_BLURB
define|#
directive|define
name|DEFAULT_XRESOLUTION_BLURB
define|\
value|"Sets the default horizontal resolution for new images and for the " \ "File/New dialog. This value is always in dpi (dots per inch)."
end_define

begin_define
DECL|macro|DEFAULT_YRESOLUTION_BLURB
define|#
directive|define
name|DEFAULT_YRESOLUTION_BLURB
define|\
value|"Sets the default vertical resolution for new images and for the " \ "File/New dialog. This value is always in dpi (dots per inch)."
end_define

begin_define
DECL|macro|ENVIRON_PATH_BLURB
define|#
directive|define
name|ENVIRON_PATH_BLURB
define|\
value|"Sets the environ search path."
end_define

begin_define
DECL|macro|FRACTALEXPLORER_PATH_BLURB
define|#
directive|define
name|FRACTALEXPLORER_PATH_BLURB
define|\
value|"Where to search for fractals used by the Fractal Explorer plug-in."
end_define

begin_define
DECL|macro|GAMMA_CORRECTION_BLURB
define|#
directive|define
name|GAMMA_CORRECTION_BLURB
define|\
value|"This setting is ignored."
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|"Sets the gamma correction value for the display. 1.0 corresponds to no " \ "gamma correction.  For most displays, gamma correction should be set " \ "to between 2.0 and 2.6. One important thing to keep in mind: Many images " \ "that you might get from outside sources will in all likelihood already " \ "be gamma-corrected.  In these cases, the image will look washed-out if " \ "the GIMP has gamma-correction turned on.  If you are going to work with " \ "images of this sort, turn gamma correction off by setting the value to 1.0."
endif|#
directive|endif
end_endif

begin_define
DECL|macro|GFIG_PATH_BLURB
define|#
directive|define
name|GFIG_PATH_BLURB
define|\
value|"Where to search for Gfig figures used by the Gfig plug-in."
end_define

begin_define
DECL|macro|GFLARE_PATH_BLURB
define|#
directive|define
name|GFLARE_PATH_BLURB
define|\
value|"Where to search for gflares used by the GFlare plug-in."
end_define

begin_define
DECL|macro|GIMPRESSIONIST_PATH_BLURB
define|#
directive|define
name|GIMPRESSIONIST_PATH_BLURB
define|\
value|"Where to search for data used by the Gimpressionist plug-in."
end_define

begin_define
DECL|macro|GRADIENT_PATH_BLURB
define|#
directive|define
name|GRADIENT_PATH_BLURB
define|\
value|"Sets the gradient search path."
end_define

begin_define
DECL|macro|HELP_BROWSER_BLURB
define|#
directive|define
name|HELP_BROWSER_BLURB
define|\
value|N_("Sets the browser used by the help system.")
end_define

begin_define
DECL|macro|IMAGE_STATUS_FORMAT_BLURB
define|#
directive|define
name|IMAGE_STATUS_FORMAT_BLURB
define|\
value|"Sets the text to appear in image window status bars. See " \ "image-title-format for the list of possible % sequences."
end_define

begin_define
DECL|macro|IMAGE_TITLE_FORMAT_BLURB
define|#
directive|define
name|IMAGE_TITLE_FORMAT_BLURB
define|\
value|"Sets the text to appear in image window titles.  Certain % character " \ "sequences are recognised and expanded as follows:\n" \ "\n" \ "%%  literal percent sign\n" \ "%f  bare filename, or \"Untitled\"\n" \ "%F  full path to file, or \"Untitled\"\n" \ "%p  PDB image id\n" \ "%i  view instance number\n" \ "%t  image type (RGB, grayscale, indexed)\n" \ "%z  zoom factor as a percentage\n" \ "%s  source scale factor\n" \ "%d  destination scale factor\n" \ "%Dx expands to x if the image is dirty, the empty string otherwise\n" \ "%Cx expands to x if the image is clean, the empty string otherwise\n" \ "%m  memory used by the image\n" \ "%l  the number of layers\n" \ "%L  the name of the active layer/channel\n" \ "%w  image width in pixels\n" \ "%W  image width in real-world units\n" \ "%h  image height in pixels\n" \ "%H  image height in real-world units\n" \ "%u  unit symbol\n" \ "%U  unit abbreviation\n\n"
end_define

begin_define
DECL|macro|INFO_WINDOW_PER_DISPLAY_BLURB
define|#
directive|define
name|INFO_WINDOW_PER_DISPLAY_BLURB
define|\
value|N_("When set to yes, the GIMP will use a different info window per image " \    "view.")
end_define

begin_define
DECL|macro|INSTALL_COLORMAP_BLURB
define|#
directive|define
name|INSTALL_COLORMAP_BLURB
define|\
value|N_("Install a private colormap; might be useful on pseudocolor visuals.")
end_define

begin_define
DECL|macro|INTERPOLATION_TYPE_BLURB
define|#
directive|define
name|INTERPOLATION_TYPE_BLURB
define|\
value|N_("Sets the level of interpolation used for scaling and other " \    "transformations.")
end_define

begin_define
DECL|macro|LAST_OPENED_SIZE_BLURB
define|#
directive|define
name|LAST_OPENED_SIZE_BLURB
define|\
value|N_("How many recently opened image filenames to keep on the File menu.")
end_define

begin_define
DECL|macro|MARCHING_ANTS_SPEED_BLURB
define|#
directive|define
name|MARCHING_ANTS_SPEED_BLURB
define|\
value|N_("Speed of marching ants in the selection outline.  This value is in " \    "milliseconds (less time indicates faster marching).")
end_define

begin_define
DECL|macro|MAX_NEW_IMAGE_SIZE_BLURB
define|#
directive|define
name|MAX_NEW_IMAGE_SIZE_BLURB
define|\
value|N_("GIMP will warn the user if an attempt is made to create an image that " \    "would take more memory than the size specified here.")
end_define

begin_define
DECL|macro|MIN_COLORS_BLURB
define|#
directive|define
name|MIN_COLORS_BLURB
define|\
value|N_("Generally only a concern for 8-bit displays, this sets the minimum " \    "number of system colors allocated for the GIMP.")
end_define

begin_define
DECL|macro|MODULE_PATH_BLURB
define|#
directive|define
name|MODULE_PATH_BLURB
define|\
value|"Sets the module search path."
end_define

begin_define
DECL|macro|MODULE_LOAD_INHIBIT_BLURB
define|#
directive|define
name|MODULE_LOAD_INHIBIT_BLURB
define|\
value|"To inhibit loading of a module, add its name here."
end_define

begin_define
DECL|macro|MONITOR_RES_FROM_GDK_BLURB
define|#
directive|define
name|MONITOR_RES_FROM_GDK_BLURB
define|\
value|"Set to yes if the GIMP should use the monitor resolution from " \ "the windowing system."
end_define

begin_define
DECL|macro|MONITOR_XRESOLUTION_BLURB
define|#
directive|define
name|MONITOR_XRESOLUTION_BLURB
define|\
value|"Sets the monitor's horizontal resolution, in dots per inch.  If set to " \ "0, forces the X server to be queried for both horizontal and vertical " \ "resolution information."
end_define

begin_define
DECL|macro|MONITOR_YRESOLUTION_BLURB
define|#
directive|define
name|MONITOR_YRESOLUTION_BLURB
define|\
value|"Sets the monitor's vertical resolution, in dots per inch.  If set to " \ "0, forces the X server to be queried for both horizontal and vertical " \ "resolution information."
end_define

begin_define
DECL|macro|NAVIGATION_PREVIEW_SIZE_BLURB
define|#
directive|define
name|NAVIGATION_PREVIEW_SIZE_BLURB
define|\
value|N_("Sets the size of the navigation preview available in the lower right " \    "corner of the image window.")
end_define

begin_define
DECL|macro|NUM_PROCESSORS_BLURB
define|#
directive|define
name|NUM_PROCESSORS_BLURB
define|\
value|N_("On multiprocessor machines, if GIMP has been compiled with --enable-mp " \    "this sets how many processors GIMP should use simultaneously.")
end_define

begin_define
DECL|macro|PALETTE_PATH_BLURB
define|#
directive|define
name|PALETTE_PATH_BLURB
define|\
value|"Sets the palette search path."
end_define

begin_define
DECL|macro|PATTERN_PATH_BLURB
define|#
directive|define
name|PATTERN_PATH_BLURB
define|\
value|"Sets the pattern search path."
end_define

begin_define
DECL|macro|PERFECT_MOUSE_BLURB
define|#
directive|define
name|PERFECT_MOUSE_BLURB
define|\
value|N_("When set to yes, the X server is queried for the mouse's current " \    "position on each motion event, rather than relying on the position " \    "hint.  This means painting with large brushes should be more accurate, " \    "but it may be slower.  Perversely, on some X servers turning on this " \    "option results in faster painting.")
end_define

begin_define
DECL|macro|PLUG_IN_PATH_BLURB
define|#
directive|define
name|PLUG_IN_PATH_BLURB
define|\
value|"Sets the plug-in search path."
end_define

begin_define
DECL|macro|PLUGINRC_PATH_BLURB
define|#
directive|define
name|PLUGINRC_PATH_BLURB
define|\
value|"Sets the pluginrc search path."
end_define

begin_define
DECL|macro|PREVIEW_SIZE_BLURB
define|#
directive|define
name|PREVIEW_SIZE_BLURB
define|\
value|N_("Sets the default preview size.")
end_define

begin_define
DECL|macro|RESIZE_WINDOWS_ON_RESIZE_BLURB
define|#
directive|define
name|RESIZE_WINDOWS_ON_RESIZE_BLURB
define|\
value|N_("When the physical image size changes, setting this option to yes " \    "enables the automatic resizing of windows.")
end_define

begin_define
DECL|macro|RESIZE_WINDOWS_ON_ZOOM_BLURB
define|#
directive|define
name|RESIZE_WINDOWS_ON_ZOOM_BLURB
define|\
value|N_("When zooming into and out of images, setting this option to yes " \    "enables the automatic resizing of windows.")
end_define

begin_define
DECL|macro|RESTORE_SESSION_BLURB
define|#
directive|define
name|RESTORE_SESSION_BLURB
define|\
value|N_("Let GIMP try to restore your last saved session on each startup.")
end_define

begin_define
DECL|macro|SAVE_DEVICE_STATUS_BLURB
define|#
directive|define
name|SAVE_DEVICE_STATUS_BLURB
define|\
value|N_("Remember the current tool, pattern, color, and brush across GIMP " \    "sessions.")
end_define

begin_define
DECL|macro|SAVE_SESSION_INFO_BLURB
define|#
directive|define
name|SAVE_SESSION_INFO_BLURB
define|\
value|N_("Save the positions and sizes of the main dialogs when the GIMP exits.")
end_define

begin_define
DECL|macro|SCRIPT_FU_PATH_BLURB
define|#
directive|define
name|SCRIPT_FU_PATH_BLURB
define|\
value|"This path will be searched for scripts when the Script-Fu plug-in is run."
end_define

begin_define
DECL|macro|SHOW_MENUBAR_BLURB
define|#
directive|define
name|SHOW_MENUBAR_BLURB
define|\
value|N_("Sets the default menubar visibility. This can also be toggled with the "\    "View->Toggle Menubar command.")
end_define

begin_define
DECL|macro|SHOW_RULERS_BLURB
define|#
directive|define
name|SHOW_RULERS_BLURB
define|\
value|N_("Sets the default ruler visibility. This can also be toggled with the " \    "View->Toggle Rulers command.")
end_define

begin_define
DECL|macro|SHOW_STATUSBAR_BLURB
define|#
directive|define
name|SHOW_STATUSBAR_BLURB
define|\
value|N_("Set to yes to make the statusbar visible by default. This can also be " \    "toggled with the View->Toggle Statusbar command.")
end_define

begin_define
DECL|macro|SHOW_TIPS_BLURB
define|#
directive|define
name|SHOW_TIPS_BLURB
define|\
value|N_("To display a handy GIMP tip on startup, set to yes.")
end_define

begin_define
DECL|macro|SHOW_TOOL_TIPS_BLURB
define|#
directive|define
name|SHOW_TOOL_TIPS_BLURB
define|\
value|N_("To display tooltips, set to yes.")
end_define

begin_define
DECL|macro|STINGY_MEMORY_USE_BLURB
define|#
directive|define
name|STINGY_MEMORY_USE_BLURB
define|\
value|N_("There is always a tradeoff between memory usage and speed.  In most " \    "cases, the GIMP opts for speed over memory.  However, if memory is a " \    "big issue, try to enable this setting.")
end_define

begin_define
DECL|macro|SWAP_PATH_BLURB
define|#
directive|define
name|SWAP_PATH_BLURB
define|\
value|N_("Sets the swap file location. The gimp uses a tile based memory " \    "allocation scheme. The swap file is used to quickly and easily " \    "swap tiles out to disk and back in. Be aware that the swap file " \    "can easily get very large if the GIMP is used with large images. " \    "Also, things can get horribly slow if the swap file is created on " \    "a directory that is mounted over NFS.  For these reasons, it may " \    "be desirable to put your swap file in \"/tmp\".")
end_define

begin_define
DECL|macro|TEAROFF_MENUS_BLURB
define|#
directive|define
name|TEAROFF_MENUS_BLURB
define|\
value|N_("When set to yes, enables tear off menus.")
end_define

begin_define
DECL|macro|TEMP_PATH_BLURB
define|#
directive|define
name|TEMP_PATH_BLURB
define|\
value|N_("Sets the temporary storage directory. Files will appear here " \    "during the course of running the GIMP.  Most files will disappear " \    "when the GIMP exits, but some files are likely to remain, so it is" \    "best if this directory not be one that is shared by other users.")
end_define

begin_define
DECL|macro|THEME_BLURB
define|#
directive|define
name|THEME_BLURB
define|\
value|"The name of the theme to use."
end_define

begin_define
DECL|macro|THEME_PATH_BLURB
define|#
directive|define
name|THEME_PATH_BLURB
define|\
value|"Sets the theme search path."
end_define

begin_define
DECL|macro|THUMBNAIL_SIZE_BLURB
define|#
directive|define
name|THUMBNAIL_SIZE_BLURB
define|\
value|N_("Sets the size of the thumbnail saved with each image.")
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE_BLURB
define|#
directive|define
name|TILE_CACHE_SIZE_BLURB
define|\
value|N_("The tile cache is used to make sure the GIMP doesn't thrash " \    "tiles between memory and disk. Setting this value higher will " \    "cause the GIMP to use less swap space, but will also cause " \    "the GIMP to use more memory. Conversely, a smaller cache size " \    "causes the GIMP to use more swap space and less memory.")
end_define

begin_define
DECL|macro|TOOL_PLUG_IN_PATH_BLURB
define|#
directive|define
name|TOOL_PLUG_IN_PATH_BLURB
define|\
value|"Sets the tool-plug-in search path."
end_define

begin_define
DECL|macro|TRANSPARENCY_TYPE_BLURB
define|#
directive|define
name|TRANSPARENCY_TYPE_BLURB
define|\
value|N_("Sets the manner in which transparency is displayed in images.")
end_define

begin_define
DECL|macro|TRANSPARENCY_SIZE_BLURB
define|#
directive|define
name|TRANSPARENCY_SIZE_BLURB
define|\
value|N_("Sets the size of the checkerboard used to display transparency.")
end_define

begin_define
DECL|macro|TRUST_DIRTY_FLAG_BLURB
define|#
directive|define
name|TRUST_DIRTY_FLAG_BLURB
define|\
value|N_("When set to yes, the GIMP will not save if the image is unchanged since " \    "opening it.")
end_define

begin_define
DECL|macro|UNDO_LEVELS_BLURB
define|#
directive|define
name|UNDO_LEVELS_BLURB
define|\
value|N_("Sets the number of operations kept on the undo stack.")
end_define

begin_define
DECL|macro|USE_HELP_BLURB
define|#
directive|define
name|USE_HELP_BLURB
define|\
value|N_("When set to no the F1 help binding will be disabled.")
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RC_BLURBS_H__ */
end_comment

end_unit

