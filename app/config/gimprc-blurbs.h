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
comment|/*  Not all strings defined here are used in the user interface  *  (the preferences dialog mainly) and only those that are should  *  be marked for translation.  */
end_comment

begin_define
DECL|macro|ACTIVATE_ON_FOCUS_BLURB
define|#
directive|define
name|ACTIVATE_ON_FOCUS_BLURB
define|\
value|N_("When enabled, an image will become the active image when its image " \    "window receives the focus. This is useful for window managers using " \    "\"click to focus\".")
end_define

begin_define
DECL|macro|BRUSH_PATH_BLURB
define|#
directive|define
name|BRUSH_PATH_BLURB
define|\
value|"Sets the brush search path."
end_define

begin_define
DECL|macro|BRUSH_PATH_WRITABLE_BLURB
define|#
directive|define
name|BRUSH_PATH_WRITABLE_BLURB
value|""
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
DECL|macro|CANVAS_PADDING_MODE_BLURB
define|#
directive|define
name|CANVAS_PADDING_MODE_BLURB
define|\
value|N_("Specifies how the area around the image should be drawn.")
end_define

begin_define
DECL|macro|COLOR_MANAGEMENT_BLURB
define|#
directive|define
name|COLOR_MANAGEMENT_BLURB
define|\
value|"Defines the color management behavior."
end_define

begin_define
DECL|macro|COLOR_PROFILE_POLICY_BLURB
define|#
directive|define
name|COLOR_PROFILE_POLICY_BLURB
define|\
value|N_("How to handle embedded color profiles when opening a file.")
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
DECL|macro|CURSOR_FORMAT_BLURB
define|#
directive|define
name|CURSOR_FORMAT_BLURB
define|\
value|N_("Sets the pixel format to use for mouse pointers.")
end_define

begin_define
DECL|macro|CURSOR_MODE_BLURB
define|#
directive|define
name|CURSOR_MODE_BLURB
define|\
value|N_("Sets the type of mouse pointers to use.")
end_define

begin_define
DECL|macro|CURSOR_UPDATING_BLURB
define|#
directive|define
name|CURSOR_UPDATING_BLURB
define|\
value|N_("Context-dependent mouse pointers are helpful.  They are enabled by " \    "default.  However, they require overhead that you may want to do without.")
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
DECL|macro|DEFAULT_DOT_FOR_DOT_BLURB
define|#
directive|define
name|DEFAULT_DOT_FOR_DOT_BLURB
define|\
value|N_("When enabled, this will ensure that each pixel of an image gets " \    "mapped to a pixel on the screen.")
end_define

begin_define
DECL|macro|DEFAULT_FONT_BLURB
define|#
directive|define
name|DEFAULT_FONT_BLURB
define|\
value|"Specify a default font."
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_BLURB
define|#
directive|define
name|DEFAULT_GRADIENT_BLURB
define|\
value|"Specify a default gradient."
end_define

begin_define
DECL|macro|DEFAULT_GRID_BLURB
define|#
directive|define
name|DEFAULT_GRID_BLURB
define|\
value|"Specify a default image grid."
end_define

begin_define
DECL|macro|DEFAULT_IMAGE_BLURB
define|#
directive|define
name|DEFAULT_IMAGE_BLURB
define|\
value|"Sets the default image in the \"File/New\" dialog."
end_define

begin_define
DECL|macro|DEFAULT_PATTERN_BLURB
define|#
directive|define
name|DEFAULT_PATTERN_BLURB
define|\
value|"Specify a default pattern."
end_define

begin_define
DECL|macro|DEFAULT_PALETTE_BLURB
define|#
directive|define
name|DEFAULT_PALETTE_BLURB
define|\
value|"Specify a default palette."
end_define

begin_define
DECL|macro|DEFAULT_SNAP_DISTANCE_BLURB
define|#
directive|define
name|DEFAULT_SNAP_DISTANCE_BLURB
define|\
value|N_("This is the distance in pixels where Guide and Grid snapping " \    "activates.")
end_define

begin_define
DECL|macro|DEFAULT_SNAP_TO_GUIDES_BLURB
define|#
directive|define
name|DEFAULT_SNAP_TO_GUIDES_BLURB
define|\
value|"Snap to guides by default in new image windows."
end_define

begin_define
DECL|macro|DEFAULT_SNAP_TO_GRID_BLURB
define|#
directive|define
name|DEFAULT_SNAP_TO_GRID_BLURB
define|\
value|"Snap to the grid by default in new image windows."
end_define

begin_define
DECL|macro|DEFAULT_SNAP_TO_CANVAS_BLURB
define|#
directive|define
name|DEFAULT_SNAP_TO_CANVAS_BLURB
define|\
value|"Snap to the canvas edge by default in new image windows."
end_define

begin_define
DECL|macro|DEFAULT_SNAP_TO_PATH_BLURB
define|#
directive|define
name|DEFAULT_SNAP_TO_PATH_BLURB
define|\
value|"Snap to the active path by default in new image windows."
end_define

begin_define
DECL|macro|DEFAULT_THRESHOLD_BLURB
define|#
directive|define
name|DEFAULT_THRESHOLD_BLURB
define|\
value|N_("Tools such as fuzzy-select and bucket fill find regions based on a " \    "seed-fill algorithm.  The seed fill starts at the initially selected " \    "pixel and progresses in all directions until the difference of pixel " \    "intensity from the original is greater than a specified threshold. " \    "This value represents the default threshold.")
end_define

begin_define
DECL|macro|DEFAULT_VIEW_BLURB
define|#
directive|define
name|DEFAULT_VIEW_BLURB
define|\
value|"Sets the default settings for the image view."
end_define

begin_define
DECL|macro|DEFAULT_FULLSCREEN_VIEW_BLURB
define|#
directive|define
name|DEFAULT_FULLSCREEN_VIEW_BLURB
define|\
value|"Sets the default settings used when an image is viewed in fullscreen mode."
end_define

begin_define
DECL|macro|DOCK_WINDOW_HINT_BLURB
define|#
directive|define
name|DOCK_WINDOW_HINT_BLURB
define|\
value|N_("The window type hint that is set on dock windows. This may affect " \    "the way your window manager decorates and handles dock windows.")
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
unit|"Sets the gamma correction value for the display. 1.0 corresponds to no " \ "gamma correction.  For most displays, gamma correction should be set " \ "to between 2.0 and 2.6. One important thing to keep in mind: Many images " \ "that you might get from outside sources will in all likelihood already " \ "be gamma-corrected.  In these cases, the image will look washed-out if " \ "GIMP has gamma-correction turned on.  If you are going to work with " \ "images of this sort, turn gamma correction off by setting the value to 1.0."
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
DECL|macro|GLOBAL_BRUSH_BLURB
define|#
directive|define
name|GLOBAL_BRUSH_BLURB
define|\
value|N_("When enabled, the selected brush will be used for all tools.")
end_define

begin_define
DECL|macro|GLOBAL_FONT_BLURB
define|#
directive|define
name|GLOBAL_FONT_BLURB
define|\
value|"When enabled, the selected font will be used for all tools."
end_define

begin_define
DECL|macro|GLOBAL_GRADIENT_BLURB
define|#
directive|define
name|GLOBAL_GRADIENT_BLURB
define|\
value|N_("When enabled, the selected gradient will be used for all tools.")
end_define

begin_define
DECL|macro|GLOBAL_PATTERN_BLURB
define|#
directive|define
name|GLOBAL_PATTERN_BLURB
define|\
value|N_("When enabled, the selected pattern will be used for all tools.")
end_define

begin_define
DECL|macro|GLOBAL_PALETTE_BLURB
define|#
directive|define
name|GLOBAL_PALETTE_BLURB
define|\
value|"When enabled, the selected palette will be used for all tools."
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
DECL|macro|GRADIENT_PATH_WRITABLE_BLURB
define|#
directive|define
name|GRADIENT_PATH_WRITABLE_BLURB
value|""
end_define

begin_define
DECL|macro|FONT_PATH_BLURB
define|#
directive|define
name|FONT_PATH_BLURB
define|\
value|"Where to look for fonts in addition to the system-wide installed fonts."
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
DECL|macro|HELP_LOCALES_BLURB
define|#
directive|define
name|HELP_LOCALES_BLURB
define|\
value|"Specifies the language preferences used by the help system. This is a " \ "colon-separated list of language identifiers with decreasing priority. " \ "If empty, the language is taken from the user's locale setting."
end_define

begin_define
DECL|macro|IMAGE_MAP_TOOL_MAX_RECENT_BLURB
define|#
directive|define
name|IMAGE_MAP_TOOL_MAX_RECENT_BLURB
define|\
value|"How many recent settings to keep around in color correction tools"
end_define

begin_define
DECL|macro|IMAGE_STATUS_FORMAT_BLURB
define|#
directive|define
name|IMAGE_STATUS_FORMAT_BLURB
define|\
value|N_("Sets the text to appear in image window status bars.")
end_define

begin_define
DECL|macro|IMAGE_TITLE_FORMAT_BLURB
define|#
directive|define
name|IMAGE_TITLE_FORMAT_BLURB
define|\
value|N_("Sets the text to appear in image window titles.")
end_define

begin_define
DECL|macro|INITIAL_ZOOM_TO_FIT_BLURB
define|#
directive|define
name|INITIAL_ZOOM_TO_FIT_BLURB
define|\
value|N_("When enabled, this will ensure that the full image is visible after a " \    "file is opened, otherwise it will be displayed with a scale of 1:1.")
end_define

begin_define
DECL|macro|INSTALL_COLORMAP_BLURB
define|#
directive|define
name|INSTALL_COLORMAP_BLURB
define|\
value|N_("Install a private colormap; might be useful on 8-bit (256 colors) displays.")
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
DECL|macro|INTERPRETER_PATH_BLURB
define|#
directive|define
name|INTERPRETER_PATH_BLURB
define|\
value|"Sets the interpreter search path."
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
value|N_("Generally only a concern for 8-bit displays, this sets the minimum " \    "number of system colors allocated for GIMP.")
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
DECL|macro|MONITOR_RES_FROM_GDK_BLURB
define|#
directive|define
name|MONITOR_RES_FROM_GDK_BLURB
define|\
value|"When enabled, GIMP will use the monitor resolution from the windowing system."
end_define

begin_define
DECL|macro|MONITOR_XRESOLUTION_BLURB
define|#
directive|define
name|MONITOR_XRESOLUTION_BLURB
define|\
value|N_("Sets the monitor's horizontal resolution, in dots per inch.  If set to " \    "0, forces the X server to be queried for both horizontal and vertical " \    "resolution information.")
end_define

begin_define
DECL|macro|MONITOR_YRESOLUTION_BLURB
define|#
directive|define
name|MONITOR_YRESOLUTION_BLURB
define|\
value|N_("Sets the monitor's vertical resolution, in dots per inch.  If set to " \    "0, forces the X server to be queried for both horizontal and vertical " \    "resolution information.")
end_define

begin_define
DECL|macro|MOVE_TOOL_CHANGES_ACTIVE_BLURB
define|#
directive|define
name|MOVE_TOOL_CHANGES_ACTIVE_BLURB
define|\
value|N_("If enabled, the move tool sets the edited layer or path as active.  " \    "This used to be the default behaviour in older versions.")
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
value|N_("Sets how many processors GIMP should try to use simultaneously.")
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
DECL|macro|PALETTE_PATH_WRITABLE_BLURB
define|#
directive|define
name|PALETTE_PATH_WRITABLE_BLURB
value|""
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
DECL|macro|PATTERN_PATH_WRITABLE_BLURB
define|#
directive|define
name|PATTERN_PATH_WRITABLE_BLURB
value|""
end_define

begin_define
DECL|macro|PERFECT_MOUSE_BLURB
define|#
directive|define
name|PERFECT_MOUSE_BLURB
define|\
value|N_("When enabled, the X server is queried for the mouse's current position " \    "on each motion event, rather than relying on the position hint.  This " \    "means painting with large brushes should be more accurate, but it may " \    "be slower.  Conversely, on some X servers enabling this option results " \    "in faster painting.")
end_define

begin_define
DECL|macro|PLUG_IN_HISTORY_SIZE_BLURB
define|#
directive|define
name|PLUG_IN_HISTORY_SIZE_BLURB
define|\
value|"How many recently used plug-ins to keep on the Filters menu."
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
DECL|macro|LAYER_PREVIEWS_BLURB
define|#
directive|define
name|LAYER_PREVIEWS_BLURB
define|\
value|N_("Sets whether GIMP should create previews of layers and channels. " \    "Previews in the layers and channels dialog are nice to have but they " \    "can slow things down when working with large images.")
end_define

begin_define
DECL|macro|LAYER_PREVIEW_SIZE_BLURB
define|#
directive|define
name|LAYER_PREVIEW_SIZE_BLURB
define|\
value|N_("Sets the preview size used for layers and channel previews in newly " \    "created dialogs.")
end_define

begin_define
DECL|macro|RESIZE_WINDOWS_ON_RESIZE_BLURB
define|#
directive|define
name|RESIZE_WINDOWS_ON_RESIZE_BLURB
define|\
value|N_("When enabled, the image window will automatically resize itself " \    "whenever the physical image size changes.")
end_define

begin_define
DECL|macro|RESIZE_WINDOWS_ON_ZOOM_BLURB
define|#
directive|define
name|RESIZE_WINDOWS_ON_ZOOM_BLURB
define|\
value|N_("When enabled, the image window will automatically resize itself " \    "when zooming into and out of images.")
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
DECL|macro|SAVE_DOCUMENT_HISTORY_BLURB
define|#
directive|define
name|SAVE_DOCUMENT_HISTORY_BLURB
define|\
value|N_("Keep a permanent record of all opened and saved files in the Recent " \    "Documents list.")
end_define

begin_define
DECL|macro|SAVE_SESSION_INFO_BLURB
define|#
directive|define
name|SAVE_SESSION_INFO_BLURB
define|\
value|N_("Save the positions and sizes of the main dialogs when GIMP exits.")
end_define

begin_define
DECL|macro|SAVE_TOOL_OPTIONS_BLURB
define|#
directive|define
name|SAVE_TOOL_OPTIONS_BLURB
define|\
value|N_("Save the tool options when GIMP exits.")
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
DECL|macro|SHOW_BRUSH_OUTLINE_BLURB
define|#
directive|define
name|SHOW_BRUSH_OUTLINE_BLURB
define|\
value|N_("When enabled, all paint tools will show a preview of the current " \    "brush's outline.")
end_define

begin_define
DECL|macro|SHOW_HELP_BUTTON_BLURB
define|#
directive|define
name|SHOW_HELP_BUTTON_BLURB
define|\
value|N_("When enabled, dialogs will show a help button that gives access to " \    "the related help page.  Without this button, the help page can still " \    "be reached by pressing F1.")
end_define

begin_define
DECL|macro|SHOW_PAINT_TOOL_CURSOR_BLURB
define|#
directive|define
name|SHOW_PAINT_TOOL_CURSOR_BLURB
define|\
value|N_("When enabled, the mouse pointer will be shown over the image while " \     "using a paint tool.")
end_define

begin_define
DECL|macro|SHOW_MENUBAR_BLURB
define|#
directive|define
name|SHOW_MENUBAR_BLURB
define|\
value|N_("When enabled, the menubar is visible by default. This can also be " \    "toggled with the \"View->Show Menubar\" command.")
end_define

begin_define
DECL|macro|SHOW_RULERS_BLURB
define|#
directive|define
name|SHOW_RULERS_BLURB
define|\
value|N_("When enabled, the rulers are visible by default. This can also be " \    "toggled with the \"View->Show Rulers\" command.")
end_define

begin_define
DECL|macro|SHOW_SCROLLBARS_BLURB
define|#
directive|define
name|SHOW_SCROLLBARS_BLURB
define|\
value|N_("When enabled, the scrollbars are visible by default. This can also be " \    "toggled with the \"View->Show Scrollbars\" command.")
end_define

begin_define
DECL|macro|SHOW_STATUSBAR_BLURB
define|#
directive|define
name|SHOW_STATUSBAR_BLURB
define|\
value|N_("When enabled, the statusbar is visible by default. This can also be " \    "toggled with the \"View->Show Statusbar\" command.")
end_define

begin_define
DECL|macro|SHOW_SELECTION_BLURB
define|#
directive|define
name|SHOW_SELECTION_BLURB
define|\
value|N_("When enabled, the selection is visible by default. This can also be " \    "toggled with the \"View->Show Selection\" command.")
end_define

begin_define
DECL|macro|SHOW_LAYER_BOUNDARY_BLURB
define|#
directive|define
name|SHOW_LAYER_BOUNDARY_BLURB
define|\
value|N_("When enabled, the layer boundary is visible by default. This can also " \    "be toggled with the \"View->Show Layer Boundary\" command.")
end_define

begin_define
DECL|macro|SHOW_GUIDES_BLURB
define|#
directive|define
name|SHOW_GUIDES_BLURB
define|\
value|N_("When enabled, the guides are visible by default. This can also be " \    "toggled with the \"View->Show Guides\" command.")
end_define

begin_define
DECL|macro|SHOW_GRID_BLURB
define|#
directive|define
name|SHOW_GRID_BLURB
define|\
value|N_("When enabled, the grid is visible by default. This can also be toggled " \    "with the \"View->Show Grid\" command.")
end_define

begin_define
DECL|macro|SHOW_SAMPLE_POINTS_BLURB
define|#
directive|define
name|SHOW_SAMPLE_POINTS_BLURB
define|\
value|N_("When enabled, the sample points are visible by default. This can also be " \    "toggled with the \"View->Show Sample Points\" command.")
end_define

begin_define
DECL|macro|SHOW_TOOLTIPS_BLURB
define|#
directive|define
name|SHOW_TOOLTIPS_BLURB
define|\
value|N_("Show a tooltip when the pointer hovers over an item.")
end_define

begin_define
DECL|macro|SPACE_BAR_ACTION_BLURB
define|#
directive|define
name|SPACE_BAR_ACTION_BLURB
define|\
value|N_("What to do when the space bar is pressed in the image window.")
end_define

begin_define
DECL|macro|SWAP_PATH_BLURB
define|#
directive|define
name|SWAP_PATH_BLURB
define|\
value|N_("Sets the swap file location. GIMP uses a tile based memory allocation " \    "scheme. The swap file is used to quickly and easily swap tiles out to " \    "disk and back in. Be aware that the swap file can easily get very large " \    "if GIMP is used with large images. " \    "Also, things can get horribly slow if the swap file is created on " \    "a folder that is mounted over NFS.  For these reasons, it may be " \    "desirable to put your swap file in \"/tmp\".")
end_define

begin_define
DECL|macro|TEAROFF_MENUS_BLURB
define|#
directive|define
name|TEAROFF_MENUS_BLURB
define|\
value|N_("When enabled, menus can be torn off.")
end_define

begin_define
DECL|macro|CAN_CHANGE_ACCELS_BLURB
define|#
directive|define
name|CAN_CHANGE_ACCELS_BLURB
define|\
value|N_("When enabled, you can change keyboard shortcuts for menu items " \    "by hitting a key combination while the menu item is highlighted.")
end_define

begin_define
DECL|macro|SAVE_ACCELS_BLURB
define|#
directive|define
name|SAVE_ACCELS_BLURB
define|\
value|N_("Save changed keyboard shortcuts when GIMP exits.")
end_define

begin_define
DECL|macro|RESTORE_ACCELS_BLURB
define|#
directive|define
name|RESTORE_ACCELS_BLURB
define|\
value|N_("Restore saved keyboard shortcuts on each GIMP startup.")
end_define

begin_define
DECL|macro|TEMP_PATH_BLURB
define|#
directive|define
name|TEMP_PATH_BLURB
define|\
value|N_("Sets the folder for temporary storage. Files will appear here " \    "during the course of running GIMP.  Most files will disappear " \    "when GIMP exits, but some files are likely to remain, so it " \    "is best if this folder not be one that is shared by other users.")
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
value|N_("Sets the size of the thumbnail shown in the Open dialog.")
end_define

begin_define
DECL|macro|THUMBNAIL_FILESIZE_LIMIT_BLURB
define|#
directive|define
name|THUMBNAIL_FILESIZE_LIMIT_BLURB
define|\
value|N_("The thumbnail in the Open dialog will be automatically updated " \    "if the file being previewed is smaller than the size set here.")
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE_BLURB
define|#
directive|define
name|TILE_CACHE_SIZE_BLURB
define|\
value|N_("When the amount of pixel data exceeds this limit, GIMP will start to " \    "swap tiles to disk.  This is a lot slower but it makes it possible to " \    "work on images that wouldn't fit into memory otherwise.  If you have a " \    "lot of RAM, you may want to set this to a higher value.")
end_define

begin_define
DECL|macro|TOOLBOX_COLOR_AREA_BLURB
define|#
directive|define
name|TOOLBOX_COLOR_AREA_BLURB
define|\
value|N_("Show the current foreground and background colors in the toolbox.")
end_define

begin_define
DECL|macro|TOOLBOX_FOO_AREA_BLURB
define|#
directive|define
name|TOOLBOX_FOO_AREA_BLURB
define|\
value|N_("Show the currently selected brush, pattern and gradient in the toolbox.")
end_define

begin_define
DECL|macro|TOOLBOX_IMAGE_AREA_BLURB
define|#
directive|define
name|TOOLBOX_IMAGE_AREA_BLURB
define|\
value|N_("Show the currently active image in the toolbox.")
end_define

begin_define
DECL|macro|TOOLBOX_WILBER_BLURB
define|#
directive|define
name|TOOLBOX_WILBER_BLURB
define|\
value|"Show the GIMP mascot at the top of the toolbox."
end_define

begin_define
DECL|macro|TOOLBOX_WINDOW_HINT_BLURB
define|#
directive|define
name|TOOLBOX_WINDOW_HINT_BLURB
define|\
value|N_("The window type hint that is set on the toolbox. This may affect " \    "how your window manager decorates and handles the toolbox window.")
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
value|N_("When enabled, GIMP will not save an image if it has not been changed " \    "since it was opened.")
end_define

begin_define
DECL|macro|UNDO_LEVELS_BLURB
define|#
directive|define
name|UNDO_LEVELS_BLURB
define|\
value|N_("Sets the minimal number of operations that can be undone. More undo " \    "levels are kept available until the undo-size limit is reached.")
end_define

begin_define
DECL|macro|UNDO_SIZE_BLURB
define|#
directive|define
name|UNDO_SIZE_BLURB
define|\
value|N_("Sets an upper limit to the memory that is used per image to keep " \    "operations on the undo stack. Regardless of this setting, at least " \    "as many undo-levels as configured can be undone.")
end_define

begin_define
DECL|macro|UNDO_PREVIEW_SIZE_BLURB
define|#
directive|define
name|UNDO_PREVIEW_SIZE_BLURB
define|\
value|N_("Sets the size of the previews in the Undo History.")
end_define

begin_define
DECL|macro|USE_HELP_BLURB
define|#
directive|define
name|USE_HELP_BLURB
define|\
value|N_("When enabled, pressing F1 will open the help browser.")
end_define

begin_define
DECL|macro|USER_MANUAL_ONLINE_BLURB
define|#
directive|define
name|USER_MANUAL_ONLINE_BLURB
define|\
value|"When enabled, the online user manual will be used by the help system. " \ "Otherwise the locally installed copy is used."
end_define

begin_define
DECL|macro|USER_MANUAL_ONLINE_URI_BLURB
define|#
directive|define
name|USER_MANUAL_ONLINE_URI_BLURB
define|\
value|"The location of the online user manual. This is used if " \ "'user-manual-online' is enabled."
end_define

begin_define
DECL|macro|WEB_BROWSER_BLURB
define|#
directive|define
name|WEB_BROWSER_BLURB
define|\
value|N_("Sets the external web browser to be used.  This can be an absolute " \    "path or the name of an executable to search for in the user's PATH. " \    "If the command contains '%s' it will be replaced with the URL, otherwise " \    "the URL will be appended to the command with a space separating the " \    "two.")
end_define

begin_define
DECL|macro|XOR_COLOR_BLURB
define|#
directive|define
name|XOR_COLOR_BLURB
define|\
value|"Sets the color that is used for XOR drawing. This setting only exists as " \ "a workaround for buggy display drivers. If lines on the canvas are not " \ "correctly undrawn, try to set this to white."
end_define

begin_define
DECL|macro|ZOOM_QUALITY_BLURB
define|#
directive|define
name|ZOOM_QUALITY_BLURB
define|\
value|"There's a tradeoff between speed and quality of the zoomed-out display."
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RC_BLURBS_H__ */
end_comment

end_unit

