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
value|_("When enabled, an image will become the active image when its image " \   "window receives the focus. This is useful for window managers using " \   "\"click to focus\".")
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
DECL|macro|DYNAMICS_PATH_BLURB
define|#
directive|define
name|DYNAMICS_PATH_BLURB
define|\
value|_("Sets the dynamics search path.")
end_define

begin_define
DECL|macro|DYNAMICS_PATH_WRITABLE_BLURB
define|#
directive|define
name|DYNAMICS_PATH_WRITABLE_BLURB
value|""
end_define

begin_define
DECL|macro|TOOL_PRESET_PATH_BLURB
define|#
directive|define
name|TOOL_PRESET_PATH_BLURB
define|\
value|_("Sets the dynamics search path.")
end_define

begin_define
DECL|macro|TOOL_PRESET_PATH_WRITABLE_BLURB
define|#
directive|define
name|TOOL_PRESET_PATH_WRITABLE_BLURB
value|""
end_define

begin_define
DECL|macro|CANVAS_PADDING_COLOR_BLURB
define|#
directive|define
name|CANVAS_PADDING_COLOR_BLURB
define|\
value|_("Sets the canvas padding color used if the padding mode is set to " \   "custom color.")
end_define

begin_define
DECL|macro|CANVAS_PADDING_MODE_BLURB
define|#
directive|define
name|CANVAS_PADDING_MODE_BLURB
define|\
value|_("Specifies how the area around the image should be drawn.")
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
value|_("How to handle embedded color profiles when opening a file.")
end_define

begin_define
DECL|macro|CURSOR_MODE_BLURB
define|#
directive|define
name|CURSOR_MODE_BLURB
define|\
value|_("Sets the type of mouse pointers to use.")
end_define

begin_define
DECL|macro|CURSOR_HANDEDNESS_BLURB
define|#
directive|define
name|CURSOR_HANDEDNESS_BLURB
define|\
value|_("Sets the handedness for cursor positioning.")
end_define

begin_define
DECL|macro|CURSOR_UPDATING_BLURB
define|#
directive|define
name|CURSOR_UPDATING_BLURB
define|\
value|_("Context-dependent mouse pointers are helpful.  They are enabled by " \   "default.  However, they require overhead that you may want to do without.")
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
DECL|macro|DEFAULT_DYNAMICS_BLURB
define|#
directive|define
name|DEFAULT_DYNAMICS_BLURB
define|\
value|"Specify a default dynamics.  The dynamics is searched for in the " \ "specified dynamics path."
end_define

begin_define
DECL|macro|DEFAULT_TOOL_PRESET_BLURB
define|#
directive|define
name|DEFAULT_TOOL_PRESET_BLURB
define|\
value|"Specify a default tool preset.  The tool preset is searched for in the " \ "specified tool prests path."
end_define

begin_define
DECL|macro|DEFAULT_DOT_FOR_DOT_BLURB
define|#
directive|define
name|DEFAULT_DOT_FOR_DOT_BLURB
define|\
value|_("When enabled, this will ensure that each pixel of an image gets " \   "mapped to a pixel on the screen.")
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
DECL|macro|DEFAULT_MYPAINT_BRUSH_BLURB
define|#
directive|define
name|DEFAULT_MYPAINT_BRUSH_BLURB
define|\
value|"Specify a default MyPaint brush."
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
value|_("This is the distance in pixels where Guide and Grid snapping " \   "activates.")
end_define

begin_define
DECL|macro|SNAP_TO_GUIDES_BLURB
define|#
directive|define
name|SNAP_TO_GUIDES_BLURB
define|\
value|"Snap to guides by default in new image windows."
end_define

begin_define
DECL|macro|SNAP_TO_GRID_BLURB
define|#
directive|define
name|SNAP_TO_GRID_BLURB
define|\
value|"Snap to the grid by default in new image windows."
end_define

begin_define
DECL|macro|SNAP_TO_CANVAS_BLURB
define|#
directive|define
name|SNAP_TO_CANVAS_BLURB
define|\
value|"Snap to the canvas edges by default in new image windows."
end_define

begin_define
DECL|macro|SNAP_TO_PATH_BLURB
define|#
directive|define
name|SNAP_TO_PATH_BLURB
define|\
value|"Snap to the active path by default in new image windows."
end_define

begin_define
DECL|macro|DEFAULT_THRESHOLD_BLURB
define|#
directive|define
name|DEFAULT_THRESHOLD_BLURB
define|\
value|_("Tools such as fuzzy-select and bucket fill find regions based on a " \   "seed-fill algorithm.  The seed fill starts at the initially selected " \   "pixel and progresses in all directions until the difference of pixel " \   "intensity from the original is greater than a specified threshold. " \   "This value represents the default threshold.")
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
value|_("The window type hint that is set on dock windows and the toolbox " \   "window. This may affect the way your window manager decorates and " \   "handles these windows.")
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
value|_("When enabled, the selected brush will be used for all tools.")
end_define

begin_define
DECL|macro|GLOBAL_DYNAMICS_BLURB
define|#
directive|define
name|GLOBAL_DYNAMICS_BLURB
define|\
value|_("When enabled, the selected dynamics will be used for all tools.")
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
value|_("When enabled, the selected gradient will be used for all tools.")
end_define

begin_define
DECL|macro|GLOBAL_PATTERN_BLURB
define|#
directive|define
name|GLOBAL_PATTERN_BLURB
define|\
value|_("When enabled, the selected pattern will be used for all tools.")
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
value|_("Sets the browser used by the help system.")
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
DECL|macro|FILTER_TOOL_MAX_RECENT_BLURB
define|#
directive|define
name|FILTER_TOOL_MAX_RECENT_BLURB
define|\
value|"How many recent settings to keep around in filter tools"
end_define

begin_define
DECL|macro|IMAGE_STATUS_FORMAT_BLURB
define|#
directive|define
name|IMAGE_STATUS_FORMAT_BLURB
define|\
value|_("Sets the text to appear in image window status bars.")
end_define

begin_define
DECL|macro|IMAGE_TITLE_FORMAT_BLURB
define|#
directive|define
name|IMAGE_TITLE_FORMAT_BLURB
define|\
value|_("Sets the text to appear in image window titles.")
end_define

begin_define
DECL|macro|IMPORT_PROMOTE_FLOAT_BLURB
define|#
directive|define
name|IMPORT_PROMOTE_FLOAT_BLURB
define|\
value|_("Promote imported images to floating point precision. Does not apply " \   "to indexed images.")
end_define

begin_define
DECL|macro|IMPORT_PROMOTE_DITHER_BLURB
define|#
directive|define
name|IMPORT_PROMOTE_DITHER_BLURB
define|\
value|_("When promoting imported images to floating point precision, also add " \   "minimal noise in order do distribute color values a bit.")
end_define

begin_define
DECL|macro|IMPORT_ADD_ALPHA_BLURB
define|#
directive|define
name|IMPORT_ADD_ALPHA_BLURB
define|\
value|_("Add an alpha channel to all layers of imported images.")
end_define

begin_define
DECL|macro|INITIAL_ZOOM_TO_FIT_BLURB
define|#
directive|define
name|INITIAL_ZOOM_TO_FIT_BLURB
define|\
value|_("When enabled, this will ensure that the full image is visible after a " \   "file is opened, otherwise it will be displayed with a scale of 1:1.")
end_define

begin_define
DECL|macro|INTERPOLATION_TYPE_BLURB
define|#
directive|define
name|INTERPOLATION_TYPE_BLURB
define|\
value|_("Sets the level of interpolation used for scaling and other " \   "transformations.")
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
DECL|macro|LANGUAGE_BLURB
define|#
directive|define
name|LANGUAGE_BLURB
define|\
value|_("Specifies the language to use for the user interface.")
end_define

begin_define
DECL|macro|LAST_OPENED_SIZE_BLURB
define|#
directive|define
name|LAST_OPENED_SIZE_BLURB
define|\
value|_("How many recently opened image filenames to keep on the File menu.")
end_define

begin_define
DECL|macro|MARCHING_ANTS_SPEED_BLURB
define|#
directive|define
name|MARCHING_ANTS_SPEED_BLURB
define|\
value|_("Speed of marching ants in the selection outline.  This value is in " \   "milliseconds (less time indicates faster marching).")
end_define

begin_define
DECL|macro|MAX_NEW_IMAGE_SIZE_BLURB
define|#
directive|define
name|MAX_NEW_IMAGE_SIZE_BLURB
define|\
value|_("GIMP will warn the user if an attempt is made to create an image that " \   "would take more memory than the size specified here.")
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
value|_("Sets the monitor's horizontal resolution, in dots per inch.  If set to " \   "0, forces the X server to be queried for both horizontal and vertical " \   "resolution information.")
end_define

begin_define
DECL|macro|MONITOR_YRESOLUTION_BLURB
define|#
directive|define
name|MONITOR_YRESOLUTION_BLURB
define|\
value|_("Sets the monitor's vertical resolution, in dots per inch.  If set to " \   "0, forces the X server to be queried for both horizontal and vertical " \   "resolution information.")
end_define

begin_define
DECL|macro|MOVE_TOOL_CHANGES_ACTIVE_BLURB
define|#
directive|define
name|MOVE_TOOL_CHANGES_ACTIVE_BLURB
define|\
value|_("If enabled, the move tool sets the edited layer or path as active.  " \   "This used to be the default behaviour in older versions.")
end_define

begin_define
DECL|macro|MYPAINT_BRUSH_PATH_BLURB
define|#
directive|define
name|MYPAINT_BRUSH_PATH_BLURB
define|\
value|"Sets the brush search path."
end_define

begin_define
DECL|macro|MYPAINT_BRUSH_PATH_WRITABLE_BLURB
define|#
directive|define
name|MYPAINT_BRUSH_PATH_WRITABLE_BLURB
value|""
end_define

begin_define
DECL|macro|NAVIGATION_PREVIEW_SIZE_BLURB
define|#
directive|define
name|NAVIGATION_PREVIEW_SIZE_BLURB
define|\
value|_("Sets the size of the navigation preview available in the lower right " \   "corner of the image window.")
end_define

begin_define
DECL|macro|NUM_PROCESSORS_BLURB
define|#
directive|define
name|NUM_PROCESSORS_BLURB
define|\
value|_("Sets how many processors GIMP should try to use simultaneously.")
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
DECL|macro|FILTER_HISTORY_SIZE_BLURB
define|#
directive|define
name|FILTER_HISTORY_SIZE_BLURB
define|\
value|"How many recently used filters and plug-ins to keep on the Filters menu."
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
value|_("Sets whether GIMP should create previews of layers and channels. " \   "Previews in the layers and channels dialog are nice to have but they " \   "can slow things down when working with large images.")
end_define

begin_define
DECL|macro|LAYER_PREVIEW_SIZE_BLURB
define|#
directive|define
name|LAYER_PREVIEW_SIZE_BLURB
define|\
value|_("Sets the preview size used for layers and channel previews in newly " \   "created dialogs.")
end_define

begin_define
DECL|macro|QUICK_MASK_COLOR_BLURB
define|#
directive|define
name|QUICK_MASK_COLOR_BLURB
define|\
value|_("Sets the default quick mask color.")
end_define

begin_define
DECL|macro|RESIZE_WINDOWS_ON_RESIZE_BLURB
define|#
directive|define
name|RESIZE_WINDOWS_ON_RESIZE_BLURB
define|\
value|_("When enabled, the image window will automatically resize itself " \   "whenever the physical image size changes. This setting only takes " \   "effect in multi-window mode.")
end_define

begin_define
DECL|macro|RESIZE_WINDOWS_ON_ZOOM_BLURB
define|#
directive|define
name|RESIZE_WINDOWS_ON_ZOOM_BLURB
define|\
value|_("When enabled, the image window will automatically resize itself " \   "when zooming into and out of images. This setting only takes " \   "effect in multi-window mode.")
end_define

begin_define
DECL|macro|RESTORE_SESSION_BLURB
define|#
directive|define
name|RESTORE_SESSION_BLURB
define|\
value|_("Let GIMP try to restore your last saved session on each startup.")
end_define

begin_define
DECL|macro|RESTORE_MONITOR_BLURB
define|#
directive|define
name|RESTORE_MONITOR_BLURB
define|\
value|_("When enabled, GIMP will try to restore windows on the monitor they " \   "were open before.  When disabled, windows will appear on the currently " \   "used monitor.")
end_define

begin_define
DECL|macro|SAVE_DEVICE_STATUS_BLURB
define|#
directive|define
name|SAVE_DEVICE_STATUS_BLURB
define|\
value|_("Remember the current tool, pattern, color, and brush across GIMP " \   "sessions.")
end_define

begin_define
DECL|macro|DEVICES_SHARE_TOOL_BLURB
define|#
directive|define
name|DEVICES_SHARE_TOOL_BLURB
define|\
value|_("When enabled, the same tool and tool options will be used for all " \   "input devices. No tool switching will occur when the input device " \   "changes.")
end_define

begin_define
DECL|macro|SAVE_DOCUMENT_HISTORY_BLURB
define|#
directive|define
name|SAVE_DOCUMENT_HISTORY_BLURB
define|\
value|_("Keep a permanent record of all opened and saved files in the Recent " \   "Documents list.")
end_define

begin_define
DECL|macro|SAVE_SESSION_INFO_BLURB
define|#
directive|define
name|SAVE_SESSION_INFO_BLURB
define|\
value|_("Save the positions and sizes of the main dialogs when GIMP exits.")
end_define

begin_define
DECL|macro|SAVE_TOOL_OPTIONS_BLURB
define|#
directive|define
name|SAVE_TOOL_OPTIONS_BLURB
define|\
value|_("Save the tool options when GIMP exits.")
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
value|_("When enabled, all paint tools will show a preview of the current " \   "brush's outline.")
end_define

begin_define
DECL|macro|SHOW_HELP_BUTTON_BLURB
define|#
directive|define
name|SHOW_HELP_BUTTON_BLURB
define|\
value|_("When enabled, dialogs will show a help button that gives access to " \   "the related help page.  Without this button, the help page can still " \   "be reached by pressing F1.")
end_define

begin_define
DECL|macro|SHOW_PAINT_TOOL_CURSOR_BLURB
define|#
directive|define
name|SHOW_PAINT_TOOL_CURSOR_BLURB
define|\
value|_("When enabled, the mouse pointer will be shown over the image while " \   "using a paint tool.")
end_define

begin_define
DECL|macro|SHOW_MENUBAR_BLURB
define|#
directive|define
name|SHOW_MENUBAR_BLURB
define|\
value|_("When enabled, the menubar is visible by default. This can also be " \   "toggled with the \"View->Show Menubar\" command.")
end_define

begin_define
DECL|macro|SHOW_RULERS_BLURB
define|#
directive|define
name|SHOW_RULERS_BLURB
define|\
value|_("When enabled, the rulers are visible by default. This can also be " \   "toggled with the \"View->Show Rulers\" command.")
end_define

begin_define
DECL|macro|SHOW_SCROLLBARS_BLURB
define|#
directive|define
name|SHOW_SCROLLBARS_BLURB
define|\
value|_("When enabled, the scrollbars are visible by default. This can also be " \   "toggled with the \"View->Show Scrollbars\" command.")
end_define

begin_define
DECL|macro|SHOW_STATUSBAR_BLURB
define|#
directive|define
name|SHOW_STATUSBAR_BLURB
define|\
value|_("When enabled, the statusbar is visible by default. This can also be " \   "toggled with the \"View->Show Statusbar\" command.")
end_define

begin_define
DECL|macro|SHOW_SELECTION_BLURB
define|#
directive|define
name|SHOW_SELECTION_BLURB
define|\
value|_("When enabled, the selection is visible by default. This can also be " \   "toggled with the \"View->Show Selection\" command.")
end_define

begin_define
DECL|macro|SHOW_LAYER_BOUNDARY_BLURB
define|#
directive|define
name|SHOW_LAYER_BOUNDARY_BLURB
define|\
value|_("When enabled, the layer boundary is visible by default. This can also " \   "be toggled with the \"View->Show Layer Boundary\" command.")
end_define

begin_define
DECL|macro|SHOW_GUIDES_BLURB
define|#
directive|define
name|SHOW_GUIDES_BLURB
define|\
value|_("When enabled, the guides are visible by default. This can also be " \   "toggled with the \"View->Show Guides\" command.")
end_define

begin_define
DECL|macro|SHOW_GRID_BLURB
define|#
directive|define
name|SHOW_GRID_BLURB
define|\
value|_("When enabled, the grid is visible by default. This can also be toggled " \   "with the \"View->Show Grid\" command.")
end_define

begin_define
DECL|macro|SHOW_SAMPLE_POINTS_BLURB
define|#
directive|define
name|SHOW_SAMPLE_POINTS_BLURB
define|\
value|_("When enabled, the sample points are visible by default. This can also be " \   "toggled with the \"View->Show Sample Points\" command.")
end_define

begin_define
DECL|macro|SHOW_TOOLTIPS_BLURB
define|#
directive|define
name|SHOW_TOOLTIPS_BLURB
define|\
value|_("Show a tooltip when the pointer hovers over an item.")
end_define

begin_define
DECL|macro|SINGLE_WINDOW_MODE_BLURB
define|#
directive|define
name|SINGLE_WINDOW_MODE_BLURB
define|\
value|_("Use GIMP in a single-window mode.")
end_define

begin_define
DECL|macro|HIDE_DOCKS_BLURB
define|#
directive|define
name|HIDE_DOCKS_BLURB
define|\
value|_("Hide docks and other windows, leaving only image windows.")
end_define

begin_define
DECL|macro|PLAYGROUND_NPD_TOOL_BLURB
define|#
directive|define
name|PLAYGROUND_NPD_TOOL_BLURB
define|\
value|_("Enable the N-Point Deformation tool.")
end_define

begin_define
DECL|macro|PLAYGROUND_HANDLE_TRANSFORM_TOOL_BLURB
define|#
directive|define
name|PLAYGROUND_HANDLE_TRANSFORM_TOOL_BLURB
define|\
value|_("Enable the Handle Transform tool.")
end_define

begin_define
DECL|macro|PLAYGROUND_SYMMETRY_BLURB
define|#
directive|define
name|PLAYGROUND_SYMMETRY_BLURB
define|\
value|_("Enable symmetry on painting.")
end_define

begin_define
DECL|macro|PLAYGROUND_MYBRUSH_TOOL_BLURB
define|#
directive|define
name|PLAYGROUND_MYBRUSH_TOOL_BLURB
define|\
value|_("Enable the MyPaint Brush tool.")
end_define

begin_define
DECL|macro|PLAYGROUND_SEAMLESS_CLONE_TOOL_BLURB
define|#
directive|define
name|PLAYGROUND_SEAMLESS_CLONE_TOOL_BLURB
define|\
value|_("Enable the Seamless Clone tool.")
end_define

begin_define
DECL|macro|SPACE_BAR_ACTION_BLURB
define|#
directive|define
name|SPACE_BAR_ACTION_BLURB
define|\
value|_("What to do when the space bar is pressed in the image window.")
end_define

begin_define
DECL|macro|SWAP_PATH_BLURB
define|#
directive|define
name|SWAP_PATH_BLURB
define|\
value|_("Sets the swap file location. GIMP uses a tile based memory allocation " \   "scheme. The swap file is used to quickly and easily swap tiles out to " \   "disk and back in. Be aware that the swap file can easily get very large " \   "if GIMP is used with large images. " \   "Also, things can get horribly slow if the swap file is created on " \   "a folder that is mounted over NFS.  For these reasons, it may be " \   "desirable to put your swap file in \"/tmp\".")
end_define

begin_define
DECL|macro|TEAROFF_MENUS_BLURB
define|#
directive|define
name|TEAROFF_MENUS_BLURB
define|\
value|_("When enabled, menus can be torn off.")
end_define

begin_define
DECL|macro|CAN_CHANGE_ACCELS_BLURB
define|#
directive|define
name|CAN_CHANGE_ACCELS_BLURB
define|\
value|_("When enabled, you can change keyboard shortcuts for menu items " \   "by hitting a key combination while the menu item is highlighted.")
end_define

begin_define
DECL|macro|SAVE_ACCELS_BLURB
define|#
directive|define
name|SAVE_ACCELS_BLURB
define|\
value|_("Save changed keyboard shortcuts when GIMP exits.")
end_define

begin_define
DECL|macro|RESTORE_ACCELS_BLURB
define|#
directive|define
name|RESTORE_ACCELS_BLURB
define|\
value|_("Restore saved keyboard shortcuts on each GIMP startup.")
end_define

begin_define
DECL|macro|TEMP_PATH_BLURB
define|#
directive|define
name|TEMP_PATH_BLURB
define|\
value|_("Sets the folder for temporary storage. Files will appear here " \   "during the course of running GIMP.  Most files will disappear " \   "when GIMP exits, but some files are likely to remain, so it " \   "is best if this folder not be one that is shared by other users.")
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
DECL|macro|ICON_THEME_BLURB
define|#
directive|define
name|ICON_THEME_BLURB
define|\
value|"The name of the icon theme to use."
end_define

begin_define
DECL|macro|ICON_SIZE_BLURB
define|#
directive|define
name|ICON_SIZE_BLURB
define|\
value|"The size of the icons to use."
end_define

begin_define
DECL|macro|ICON_THEME_PATH_BLURB
define|#
directive|define
name|ICON_THEME_PATH_BLURB
define|\
value|"Sets the icon theme search path."
end_define

begin_define
DECL|macro|IMAGE_CONVERT_PROFILE_INTENT_BLURB
define|#
directive|define
name|IMAGE_CONVERT_PROFILE_INTENT_BLURB
define|\
value|_("Sets the default rendering intent for the 'Convert to Color Profile' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_PROFILE_BPC_BLURB
define|#
directive|define
name|IMAGE_CONVERT_PROFILE_BPC_BLURB
define|\
value|_("Sets the default 'Black Point Compensation' state for the " \   "'Convert to Color Profile' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_PRECISION_LAYER_DITHER_METHOD_BLURB
define|#
directive|define
name|IMAGE_CONVERT_PRECISION_LAYER_DITHER_METHOD_BLURB
define|\
value|_("Sets the default layer dithering method for the 'Convert Precision' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_PRECISION_TEXT_LAYER_DITHER_METHOD_BLURB
define|#
directive|define
name|IMAGE_CONVERT_PRECISION_TEXT_LAYER_DITHER_METHOD_BLURB
define|\
value|_("Sets the default text layer dithering method for the 'Convert Precision' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_PRECISION_CHANNEL_DITHER_METHOD_BLURB
define|#
directive|define
name|IMAGE_CONVERT_PRECISION_CHANNEL_DITHER_METHOD_BLURB
define|\
value|_("Sets the default channel dithering method for the 'Convert Precision' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_INDEXED_PALETTE_TYPE_BLURB
define|#
directive|define
name|IMAGE_CONVERT_INDEXED_PALETTE_TYPE_BLURB
define|\
value|_("Sets the default palette type for the 'Convert to Indexed' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_INDEXED_MAX_COLORS_BLURB
define|#
directive|define
name|IMAGE_CONVERT_INDEXED_MAX_COLORS_BLURB
define|\
value|_("Sets the default maximum number of colors for the 'Convert to Indexed' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_INDEXED_REMOVE_DUPLICATES_BLURB
define|#
directive|define
name|IMAGE_CONVERT_INDEXED_REMOVE_DUPLICATES_BLURB
define|\
value|_("Sets the default 'Remove duplicate colors' state for the 'Convert to Indexed' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_INDEXED_DITHER_TYPE_BLURB
define|#
directive|define
name|IMAGE_CONVERT_INDEXED_DITHER_TYPE_BLURB
define|\
value|_("Sets the default dithering type for the 'Convert to Indexed' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_INDEXED_DITHER_ALPHA_BLURB
define|#
directive|define
name|IMAGE_CONVERT_INDEXED_DITHER_ALPHA_BLURB
define|\
value|_("Sets the default 'Dither alpha' state for the 'Convert to Indexed' dialog.")
end_define

begin_define
DECL|macro|IMAGE_CONVERT_INDEXED_DITHER_TEXT_LAYERS_BLURB
define|#
directive|define
name|IMAGE_CONVERT_INDEXED_DITHER_TEXT_LAYERS_BLURB
define|\
value|_("Sets the default 'Dither text layers' state for the 'Convert to Indexed' dialog.")
end_define

begin_define
DECL|macro|IMAGE_RESIZE_FILL_TYPE_BLURB
define|#
directive|define
name|IMAGE_RESIZE_FILL_TYPE_BLURB
define|\
value|_("Sets the default fill type for the 'Canvas Size' dialog.")
end_define

begin_define
DECL|macro|IMAGE_RESIZE_LAYER_SET_BLURB
define|#
directive|define
name|IMAGE_RESIZE_LAYER_SET_BLURB
define|\
value|_("Sets the default set of layers to resize for the 'Canvas Size' dialog.")
end_define

begin_define
DECL|macro|IMAGE_RESIZE_RESIZE_TEXT_LAYERS_BLURB
define|#
directive|define
name|IMAGE_RESIZE_RESIZE_TEXT_LAYERS_BLURB
define|\
value|_("Sets the default 'Resize text layers' state for the 'Canvas Size' dialog.")
end_define

begin_define
DECL|macro|LAYER_NEW_NAME_BLURB
define|#
directive|define
name|LAYER_NEW_NAME_BLURB
define|\
value|_("Sets the default layer name for the 'New Layer' dialog.")
end_define

begin_define
DECL|macro|LAYER_NEW_MODE_BLURB
define|#
directive|define
name|LAYER_NEW_MODE_BLURB
define|\
value|_("Sets the default mode for the 'New Layer' dialog.")
end_define

begin_define
DECL|macro|LAYER_NEW_BLEND_SPACE_BLURB
define|#
directive|define
name|LAYER_NEW_BLEND_SPACE_BLURB
define|\
value|_("Sets the default blend space for the 'New Layer' dialog.")
end_define

begin_define
DECL|macro|LAYER_NEW_COMPOSITE_SPACE_BLURB
define|#
directive|define
name|LAYER_NEW_COMPOSITE_SPACE_BLURB
define|\
value|_("Sets the default composite space for the 'New Layer' dialog.")
end_define

begin_define
DECL|macro|LAYER_NEW_COMPOSITE_MODE_BLURB
define|#
directive|define
name|LAYER_NEW_COMPOSITE_MODE_BLURB
define|\
value|_("Sets the default composite mode for the 'New Layer' dialog.")
end_define

begin_define
DECL|macro|LAYER_NEW_OPACITY_BLURB
define|#
directive|define
name|LAYER_NEW_OPACITY_BLURB
define|\
value|_("Sets the default opacity for the 'New Layer' dialog.")
end_define

begin_define
DECL|macro|LAYER_NEW_FILL_TYPE_BLURB
define|#
directive|define
name|LAYER_NEW_FILL_TYPE_BLURB
define|\
value|_("Sets the default fill type for the 'New Layer' dialog.")
end_define

begin_define
DECL|macro|LAYER_RESIZE_FILL_TYPE_BLURB
define|#
directive|define
name|LAYER_RESIZE_FILL_TYPE_BLURB
define|\
value|_("Sets the default fill type for the 'Layer Boundary Size' dialog.")
end_define

begin_define
DECL|macro|LAYER_ADD_MASK_TYPE_BLURB
define|#
directive|define
name|LAYER_ADD_MASK_TYPE_BLURB
define|\
value|_("Sets the default mask for the 'Add Layer Mask' dialog.")
end_define

begin_define
DECL|macro|LAYER_ADD_MASK_INVERT_BLURB
define|#
directive|define
name|LAYER_ADD_MASK_INVERT_BLURB
define|\
value|_("Sets the default 'invert mask' state for the 'Add Layer Mask' dialog.")
end_define

begin_define
DECL|macro|LAYER_MERGE_TYPE_BLURB
define|#
directive|define
name|LAYER_MERGE_TYPE_BLURB
define|\
value|_("Sets the default merge type for the 'Merge Visible Layers' dialog.")
end_define

begin_define
DECL|macro|LAYER_MERGE_ACTIVE_GROUP_ONLY_BLURB
define|#
directive|define
name|LAYER_MERGE_ACTIVE_GROUP_ONLY_BLURB
define|\
value|_("Sets the default 'Active group only' for the 'Merge Visible Layers' dialog.")
end_define

begin_define
DECL|macro|LAYER_MERGE_DISCARD_INVISIBLE_BLURB
define|#
directive|define
name|LAYER_MERGE_DISCARD_INVISIBLE_BLURB
define|\
value|_("Sets the default 'Discard invisible' for the 'Merge Visible Layers' dialog.")
end_define

begin_define
DECL|macro|CHANNEL_NEW_NAME_BLURB
define|#
directive|define
name|CHANNEL_NEW_NAME_BLURB
define|\
value|_("Sets the default channel name for the 'New Channel' dialog.")
end_define

begin_define
DECL|macro|CHANNEL_NEW_COLOR_BLURB
define|#
directive|define
name|CHANNEL_NEW_COLOR_BLURB
define|\
value|_("Sets the default color and opacity for the 'New Channel' dialog.")
end_define

begin_define
DECL|macro|VECTORS_NEW_NAME_BLURB
define|#
directive|define
name|VECTORS_NEW_NAME_BLURB
define|\
value|_("Sets the default path name for the 'New Path' dialog.")
end_define

begin_define
DECL|macro|VECTORS_EXPORT_PATH_BLURB
define|#
directive|define
name|VECTORS_EXPORT_PATH_BLURB
define|\
value|_("Sets the default folder path for the 'Export Path' dialog.")
end_define

begin_define
DECL|macro|VECTORS_EXPORT_ACTIVE_ONLY_BLURB
define|#
directive|define
name|VECTORS_EXPORT_ACTIVE_ONLY_BLURB
define|\
value|_("Sets the default 'Export the active path' state for the 'Export Path' dialog.")
end_define

begin_define
DECL|macro|VECTORS_IMPORT_PATH_BLURB
define|#
directive|define
name|VECTORS_IMPORT_PATH_BLURB
define|\
value|_("Sets the default folder path for the 'Import Path' dialog.")
end_define

begin_define
DECL|macro|VECTORS_IMPORT_MERGE_BLURB
define|#
directive|define
name|VECTORS_IMPORT_MERGE_BLURB
define|\
value|_("Sets the default 'Merge imported paths' state for the 'Import Path' dialog.")
end_define

begin_define
DECL|macro|VECTORS_IMPORT_SCALE_BLURB
define|#
directive|define
name|VECTORS_IMPORT_SCALE_BLURB
define|\
value|_("Sets the default 'Scale imported paths to fit size' state for the 'Import Path' dialog.")
end_define

begin_define
DECL|macro|SELECTION_FEATHER_RADIUS_BLURB
define|#
directive|define
name|SELECTION_FEATHER_RADIUS_BLURB
define|\
value|_("Sets the default feather radius for the 'Feather Selection' dialog.")
end_define

begin_define
DECL|macro|SELECTION_GROW_RADIUS_BLURB
define|#
directive|define
name|SELECTION_GROW_RADIUS_BLURB
define|\
value|_("Sets the default grow radius for the 'Grow Selection' dialog.")
end_define

begin_define
DECL|macro|SELECTION_SHRINK_RADIUS_BLURB
define|#
directive|define
name|SELECTION_SHRINK_RADIUS_BLURB
define|\
value|_("Sets the default shrink radius for the 'Shrink Selection' dialog.")
end_define

begin_define
DECL|macro|SELECTION_SHRINK_EDGE_LOCK_BLURB
define|#
directive|define
name|SELECTION_SHRINK_EDGE_LOCK_BLURB
define|\
value|_("Sets the default 'Selected areas continue outside the image' setting " \   "for the 'Shrink Selection' dialog.")
end_define

begin_define
DECL|macro|SELECTION_BORDER_RADIUS_BLURB
define|#
directive|define
name|SELECTION_BORDER_RADIUS_BLURB
define|\
value|_("Sets the default border radius for the 'Border Selection' dialog.")
end_define

begin_define
DECL|macro|SELECTION_BORDER_EDGE_LOCK_BLURB
define|#
directive|define
name|SELECTION_BORDER_EDGE_LOCK_BLURB
define|\
value|_("Sets the default 'Selected areas continue outside the image' setting " \   "for the 'Border Selection' dialog.")
end_define

begin_define
DECL|macro|SELECTION_BORDER_STYLE_BLURB
define|#
directive|define
name|SELECTION_BORDER_STYLE_BLURB
define|\
value|_("Sets the default border style for the 'Border Selection' dialog.")
end_define

begin_define
DECL|macro|FILL_OPTIONS_BLURB
define|#
directive|define
name|FILL_OPTIONS_BLURB
define|\
value|"The default fill options for the fill dialogs."
end_define

begin_define
DECL|macro|STROKE_OPTIONS_BLURB
define|#
directive|define
name|STROKE_OPTIONS_BLURB
define|\
value|"The default stroke options for the stroke dialogs."
end_define

begin_define
DECL|macro|THUMBNAIL_SIZE_BLURB
define|#
directive|define
name|THUMBNAIL_SIZE_BLURB
define|\
value|_("Sets the size of the thumbnail shown in the Open dialog.")
end_define

begin_define
DECL|macro|THUMBNAIL_FILESIZE_LIMIT_BLURB
define|#
directive|define
name|THUMBNAIL_FILESIZE_LIMIT_BLURB
define|\
value|_("The thumbnail in the Open dialog will be automatically updated " \   "if the file being previewed is smaller than the size set here.")
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE_BLURB
define|#
directive|define
name|TILE_CACHE_SIZE_BLURB
define|\
value|_("When the amount of pixel data exceeds this limit, GIMP will start to " \   "swap tiles to disk.  This is a lot slower but it makes it possible to " \   "work on images that wouldn't fit into memory otherwise.  If you have a " \   "lot of RAM, you may want to set this to a higher value.")
end_define

begin_define
DECL|macro|TOOLBOX_COLOR_AREA_BLURB
define|#
directive|define
name|TOOLBOX_COLOR_AREA_BLURB
define|\
value|_("Show the current foreground and background colors in the toolbox.")
end_define

begin_define
DECL|macro|TOOLBOX_FOO_AREA_BLURB
define|#
directive|define
name|TOOLBOX_FOO_AREA_BLURB
define|\
value|_("Show the currently selected brush, pattern and gradient in the toolbox.")
end_define

begin_define
DECL|macro|TOOLBOX_IMAGE_AREA_BLURB
define|#
directive|define
name|TOOLBOX_IMAGE_AREA_BLURB
define|\
value|_("Show the currently active image in the toolbox.")
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
DECL|macro|TRANSPARENCY_TYPE_BLURB
define|#
directive|define
name|TRANSPARENCY_TYPE_BLURB
define|\
value|_("Sets the manner in which transparency is displayed in images.")
end_define

begin_define
DECL|macro|TRANSPARENCY_SIZE_BLURB
define|#
directive|define
name|TRANSPARENCY_SIZE_BLURB
define|\
value|_("Sets the size of the checkerboard used to display transparency.")
end_define

begin_define
DECL|macro|TRUST_DIRTY_FLAG_BLURB
define|#
directive|define
name|TRUST_DIRTY_FLAG_BLURB
define|\
value|_("When enabled, GIMP will not save an image if it has not been changed " \   "since it was opened.")
end_define

begin_define
DECL|macro|UNDO_LEVELS_BLURB
define|#
directive|define
name|UNDO_LEVELS_BLURB
define|\
value|_("Sets the minimal number of operations that can be undone. More undo " \   "levels are kept available until the undo-size limit is reached.")
end_define

begin_define
DECL|macro|UNDO_SIZE_BLURB
define|#
directive|define
name|UNDO_SIZE_BLURB
define|\
value|_("Sets an upper limit to the memory that is used per image to keep " \   "operations on the undo stack. Regardless of this setting, at least " \   "as many undo-levels as configured can be undone.")
end_define

begin_define
DECL|macro|UNDO_PREVIEW_SIZE_BLURB
define|#
directive|define
name|UNDO_PREVIEW_SIZE_BLURB
define|\
value|_("Sets the size of the previews in the Undo History.")
end_define

begin_define
DECL|macro|USE_HELP_BLURB
define|#
directive|define
name|USE_HELP_BLURB
define|\
value|_("When enabled, pressing F1 will open the help browser.")
end_define

begin_define
DECL|macro|USE_OPENCL_BLURB
define|#
directive|define
name|USE_OPENCL_BLURB
define|\
value|_("When enabled, uses OpenCL for some operations.")
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
DECL|macro|ZOOM_QUALITY_BLURB
define|#
directive|define
name|ZOOM_QUALITY_BLURB
define|\
value|"There's a tradeoff between speed and quality of the zoomed-out display."
end_define

begin_define
DECL|macro|DEFAULT_USE_EVENT_HISTORY_BLURB
define|#
directive|define
name|DEFAULT_USE_EVENT_HISTORY_BLURB
define|\
value|"Bugs in event history buffer are frequent so in case of cursor " \ "offset problems turning it off helps."
end_define

begin_define
DECL|macro|SEARCH_SHOW_UNAVAILABLE_BLURB
define|#
directive|define
name|SEARCH_SHOW_UNAVAILABLE_BLURB
define|\
value|"When enabled, a search of actions will also return inactive actions."
end_define

begin_define
DECL|macro|ACTION_HISTORY_SIZE_BLURB
define|#
directive|define
name|ACTION_HISTORY_SIZE_BLURB
define|\
value|"The maximum number of actions saved in history."
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RC_BLURBS_H__ */
end_comment

end_unit

