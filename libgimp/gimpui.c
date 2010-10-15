begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_DISABLE_DEPRECATED
end_ifdef

begin_undef
undef|#
directive|undef
name|GDK_DISABLE_DEPRECATED
end_undef

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<gdk/gdkwin32.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_X11
end_ifdef

begin_include
include|#
directive|include
file|<gdk/gdkx.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_include
include|#
directive|include
file|<Cocoa/Cocoa.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets-private.h"
end_include

begin_comment
comment|/**  * SECTION: gimpui  * @title: gimpui  * @short_description: Common user interface functions. This header includes  *                     all other GIMP User Interface Library headers.  * @see_also: gtk_init(), gdk_set_use_xshm(), gtk_widget_set_default_visual().  *  * Common user interface functions. This header includes all other  * GIMP User Interface Library headers.  **/
end_comment

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_ui_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ensure_modules
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_window_transient_realized
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|GdkWindow
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_window_set_transient_for
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|GdkWindow
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_theme_changed
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_fix_pixbuf_style
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_ui_draw_pixbuf_layout
parameter_list|(
name|GtkStyle
modifier|*
name|style
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GtkStateType
name|state_type
parameter_list|,
name|gboolean
name|use_text
parameter_list|,
name|GdkRectangle
modifier|*
name|area
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|detail
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|PangoLayout
modifier|*
name|layout
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_ui_initialized
specifier|static
name|gboolean
name|gimp_ui_initialized
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_ui_init:  * @prog_name: The name of the plug-in which will be passed as argv[0] to  *             gtk_init(). It's a convention to use the name of the  *             executable and _not_ the PDB procedure name.  * @preview:   This parameter is unused and exists for historical  *             reasons only.  *  * This function initializes GTK+ with gtk_init() and initializes GDK's  * image rendering subsystem (GdkRGB) to follow the GIMP main program's  * colormap allocation/installation policy.  *  * It also sets up various other things so that the plug-in user looks  * and behaves like the GIMP core. This includes selecting the GTK+  * theme and setting up the help system as chosen in the GIMP  * preferences. Any plug-in that provides a user interface should call  * this function.  **/
end_comment

begin_function
name|void
DECL|function|gimp_ui_init (const gchar * prog_name,gboolean preview)
name|gimp_ui_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
name|gboolean
name|preview
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|display_name
decl_stmt|;
name|gchar
modifier|*
name|themerc
decl_stmt|;
name|GFileMonitor
modifier|*
name|rc_monitor
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|prog_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_ui_initialized
condition|)
return|return;
name|g_set_prgname
argument_list|(
name|prog_name
argument_list|)
expr_stmt|;
name|display_name
operator|=
name|gimp_display_name
argument_list|()
expr_stmt|;
if|if
condition|(
name|display_name
condition|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|GDK_WINDOWING_X11
argument_list|)
name|g_setenv
argument_list|(
literal|"DISPLAY"
argument_list|,
name|display_name
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|#
directive|else
name|g_setenv
argument_list|(
literal|"GDK_DISPLAY"
argument_list|,
name|display_name
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
if|if
condition|(
name|gimp_user_time
argument_list|()
condition|)
block|{
comment|/* Construct a fake startup ID as we only want to pass the        * interaction timestamp, see _gdk_windowing_set_default_display().        */
name|gchar
modifier|*
name|startup_id
init|=
name|g_strdup_printf
argument_list|(
literal|"_TIME%u"
argument_list|,
name|gimp_user_time
argument_list|()
argument_list|)
decl_stmt|;
name|g_setenv
argument_list|(
literal|"DESKTOP_STARTUP_ID"
argument_list|,
name|startup_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|startup_id
argument_list|)
expr_stmt|;
block|}
name|gtk_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|themerc
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"themerc"
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|themerc
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|themerc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|themerc
argument_list|)
expr_stmt|;
name|rc_monitor
operator|=
name|g_file_monitor
argument_list|(
name|file
argument_list|,
name|G_FILE_MONITOR_NONE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|rc_monitor
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_ui_theme_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_set_program_class
argument_list|(
name|gimp_wm_class
argument_list|()
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|gimp_get_icon_theme_dir
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_icons_set_icon_theme
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|gimp_widgets_init
argument_list|(
name|gimp_ui_help_func
argument_list|,
name|gimp_context_get_foreground
argument_list|,
name|gimp_context_get_background
argument_list|,
name|gimp_ensure_modules
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_show_tool_tips
argument_list|()
condition|)
name|gimp_help_disable_tooltips
argument_list|()
expr_stmt|;
name|gimp_dialogs_show_help_button
argument_list|(
name|gimp_show_help_button
argument_list|()
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
index|[
name|NSApp
name|activateIgnoringOtherApps
operator|:
name|YES
index|]
expr_stmt|;
endif|#
directive|endif
name|gimp_ui_fix_pixbuf_style
argument_list|()
expr_stmt|;
name|gimp_ui_initialized
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GdkWindow
modifier|*
DECL|function|gimp_ui_get_foreign_window (guint32 window)
name|gimp_ui_get_foreign_window
parameter_list|(
name|guint32
name|window
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|GDK_WINDOWING_X11
return|return
name|gdk_x11_window_foreign_new_for_display
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|,
name|window
argument_list|)
return|;
endif|#
directive|endif
ifdef|#
directive|ifdef
name|GDK_WINDOWING_WIN32
return|return
name|gdk_win32_window_foreign_new_for_display
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|,
name|window
argument_list|)
return|;
endif|#
directive|endif
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_get_display_window:  * @gdisp_ID: a #GimpDisplay ID.  *  * Returns the #GdkWindow of a display window. The purpose is to allow  * to make plug-in dialogs transient to the image display as explained  * with gdk_window_set_transient_for().  *  * You shouldn't have to call this function directly. Use  * gimp_window_set_transient_for_display() instead.  *  * Return value: A reference to a #GdkWindow or %NULL. You should  *               unref the window using g_object_unref() as soon as  *               you don't need it any longer.  *  * Since: 2.4  */
end_comment

begin_function
name|GdkWindow
modifier|*
DECL|function|gimp_ui_get_display_window (guint32 gdisp_ID)
name|gimp_ui_get_display_window
parameter_list|(
name|guint32
name|gdisp_ID
parameter_list|)
block|{
name|guint32
name|window
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_ui_initialized
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|window
operator|=
name|gimp_display_get_window_handle
argument_list|(
name|gdisp_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|window
condition|)
return|return
name|gimp_ui_get_foreign_window
argument_list|(
name|window
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_ui_get_progress_window:  *  * Returns the #GdkWindow of the window this plug-in's progress bar is  * shown in. Use it to make plug-in dialogs transient to this window  * as explained with gdk_window_set_transient_for().  *  * You shouldn't have to call this function directly. Use  * gimp_window_set_transient() instead.  *  * Return value: A reference to a #GdkWindow or %NULL. You should  *               unref the window using g_object_unref() as soon as  *               you don't need it any longer.  *  * Since: 2.4  */
end_comment

begin_function
name|GdkWindow
modifier|*
DECL|function|gimp_ui_get_progress_window (void)
name|gimp_ui_get_progress_window
parameter_list|(
name|void
parameter_list|)
block|{
name|guint32
name|window
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|gimp_ui_initialized
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|window
operator|=
name|gimp_progress_get_window_handle
argument_list|()
expr_stmt|;
if|if
condition|(
name|window
condition|)
return|return
name|gimp_ui_get_foreign_window
argument_list|(
name|window
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_function
specifier|static
name|void
DECL|function|gimp_window_transient_show (GtkWidget * window)
name|gimp_window_transient_show
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|window
argument_list|,
name|gimp_window_transient_show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
index|[
name|NSApp
name|arrangeInFront
operator|:
name|nil
index|]
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/**  * gimp_window_set_transient_for_display:  * @window:   the #GtkWindow that should become transient  * @gdisp_ID: display ID of the image window that should become the parent  *  * Indicates to the window manager that @window is a transient dialog  * associated with the GIMP image window that is identified by it's  * display ID.  See gdk_window_set_transient_for () for more information.  *  * Most of the time you will want to use the convenience function  * gimp_window_set_transient().  *  * Since: 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_window_set_transient_for_display (GtkWindow * window,guint32 gdisp_ID)
name|gimp_window_set_transient_for_display
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|guint32
name|gdisp_ID
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|gimp_ui_initialized
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_window_set_transient_for
argument_list|(
name|window
argument_list|,
name|gimp_ui_get_display_window
argument_list|(
name|gdisp_ID
argument_list|)
argument_list|)
condition|)
block|{
comment|/*  if setting the window transient failed, at least set        *  WIN_POS_CENTER, which will center the window on the screen        *  where the mouse is (see bug #684003).        */
name|gtk_window_set_position
argument_list|(
name|window
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
name|g_signal_connect
argument_list|(
name|window
argument_list|,
literal|"show"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_window_transient_show
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_window_set_transient:  * @window: the #GtkWindow that should become transient  *  * Indicates to the window manager that @window is a transient dialog  * associated with the GIMP window that the plug-in has been  * started from. See also gimp_window_set_transient_for_display().  *  * Since: 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_window_set_transient (GtkWindow * window)
name|gimp_window_set_transient
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|gimp_ui_initialized
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WINDOW
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_window_set_transient_for
argument_list|(
name|window
argument_list|,
name|gimp_ui_get_progress_window
argument_list|()
argument_list|)
condition|)
block|{
comment|/*  see above  */
name|gtk_window_set_position
argument_list|(
name|window
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
name|g_signal_connect
argument_list|(
name|window
argument_list|,
literal|"show"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_window_transient_show
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_ui_help_func (const gchar * help_id,gpointer help_data)
name|gimp_ui_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
block|{
name|gimp_help
argument_list|(
name|NULL
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ensure_modules (void)
name|gimp_ensure_modules
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpModuleDB
modifier|*
name|module_db
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|module_db
condition|)
block|{
name|gchar
modifier|*
name|load_inhibit
init|=
name|gimp_get_module_load_inhibit
argument_list|()
decl_stmt|;
name|gchar
modifier|*
name|module_path
init|=
name|gimp_gimprc_query
argument_list|(
literal|"module-path"
argument_list|)
decl_stmt|;
name|module_db
operator|=
name|gimp_module_db_new
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_module_db_set_load_inhibit
argument_list|(
name|module_db
argument_list|,
name|load_inhibit
argument_list|)
expr_stmt|;
name|gimp_module_db_load
argument_list|(
name|module_db
argument_list|,
name|module_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|module_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|load_inhibit
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_window_transient_realized (GtkWidget * window,GdkWindow * parent)
name|gimp_window_transient_realized
parameter_list|(
name|GtkWidget
modifier|*
name|window
parameter_list|,
name|GdkWindow
modifier|*
name|parent
parameter_list|)
block|{
if|if
condition|(
name|gtk_widget_get_realized
argument_list|(
name|window
argument_list|)
condition|)
name|gdk_window_set_transient_for
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|window
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_window_set_transient_for (GtkWindow * window,GdkWindow * parent)
name|gimp_window_set_transient_for
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|GdkWindow
modifier|*
name|parent
parameter_list|)
block|{
name|gtk_window_set_transient_for
argument_list|(
name|window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|GDK_WINDOWING_WIN32
name|g_signal_handlers_disconnect_matched
argument_list|(
name|window
argument_list|,
name|G_SIGNAL_MATCH_FUNC
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|gimp_window_transient_realized
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|gtk_widget_get_realized
argument_list|(
name|GTK_WIDGET
argument_list|(
name|window
argument_list|)
argument_list|)
condition|)
name|gdk_window_set_transient_for
argument_list|(
name|gtk_widget_get_window
argument_list|(
name|GTK_WIDGET
argument_list|(
name|window
argument_list|)
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|window
argument_list|,
literal|"realize"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_window_transient_realized
argument_list|)
argument_list|,
name|parent
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|parent
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
endif|#
directive|endif
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_theme_changed (void)
name|gimp_ui_theme_changed
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_rc_reparse_all
argument_list|()
expr_stmt|;
name|gimp_ui_fix_pixbuf_style
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_fix_pixbuf_style (void)
name|gimp_ui_fix_pixbuf_style
parameter_list|(
name|void
parameter_list|)
block|{
comment|/*  Same hack as in app/gui/themes.c, to be removed for GTK+ 3.x  */
specifier|static
name|GtkStyleClass
modifier|*
name|pixbuf_style_class
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|pixbuf_style_class
condition|)
block|{
name|GType
name|type
init|=
name|g_type_from_name
argument_list|(
literal|"PixbufStyle"
argument_list|)
decl_stmt|;
if|if
condition|(
name|type
condition|)
block|{
name|pixbuf_style_class
operator|=
name|g_type_class_ref
argument_list|(
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf_style_class
condition|)
name|pixbuf_style_class
operator|->
name|draw_layout
operator|=
name|gimp_ui_draw_pixbuf_layout
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_ui_draw_pixbuf_layout (GtkStyle * style,GdkWindow * window,GtkStateType state_type,gboolean use_text,GdkRectangle * area,GtkWidget * widget,const gchar * detail,gint x,gint y,PangoLayout * layout)
name|gimp_ui_draw_pixbuf_layout
parameter_list|(
name|GtkStyle
modifier|*
name|style
parameter_list|,
name|GdkWindow
modifier|*
name|window
parameter_list|,
name|GtkStateType
name|state_type
parameter_list|,
name|gboolean
name|use_text
parameter_list|,
name|GdkRectangle
modifier|*
name|area
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|detail
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|PangoLayout
modifier|*
name|layout
parameter_list|)
block|{
name|GdkGC
modifier|*
name|gc
decl_stmt|;
name|gc
operator|=
name|use_text
condition|?
name|style
operator|->
name|text_gc
index|[
name|state_type
index|]
else|:
name|style
operator|->
name|fg_gc
index|[
name|state_type
index|]
expr_stmt|;
if|if
condition|(
name|area
condition|)
name|gdk_gc_set_clip_rectangle
argument_list|(
name|gc
argument_list|,
name|area
argument_list|)
expr_stmt|;
if|if
condition|(
name|state_type
operator|==
name|GTK_STATE_INSENSITIVE
condition|)
block|{
name|GdkGC
modifier|*
name|copy
init|=
name|gdk_gc_new
argument_list|(
name|window
argument_list|)
decl_stmt|;
name|GdkGCValues
name|orig
decl_stmt|;
name|GdkColor
name|fore
decl_stmt|;
name|guint16
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gdk_gc_copy
argument_list|(
name|copy
argument_list|,
name|gc
argument_list|)
expr_stmt|;
name|gdk_gc_get_values
argument_list|(
name|gc
argument_list|,
operator|&
name|orig
argument_list|)
expr_stmt|;
name|r
operator|=
literal|0x40
operator|+
operator|(
operator|(
operator|(
name|orig
operator|.
name|foreground
operator|.
name|pixel
operator|>>
literal|16
operator|)
operator|&
literal|0xff
operator|)
operator|>>
literal|1
operator|)
expr_stmt|;
name|g
operator|=
literal|0x40
operator|+
operator|(
operator|(
operator|(
name|orig
operator|.
name|foreground
operator|.
name|pixel
operator|>>
literal|8
operator|)
operator|&
literal|0xff
operator|)
operator|>>
literal|1
operator|)
expr_stmt|;
name|b
operator|=
literal|0x40
operator|+
operator|(
operator|(
operator|(
name|orig
operator|.
name|foreground
operator|.
name|pixel
operator|>>
literal|0
operator|)
operator|&
literal|0xff
operator|)
operator|>>
literal|1
operator|)
expr_stmt|;
name|fore
operator|.
name|pixel
operator|=
operator|(
name|r
operator|<<
literal|16
operator|)
operator||
operator|(
name|g
operator|<<
literal|8
operator|)
operator||
name|b
expr_stmt|;
name|fore
operator|.
name|red
operator|=
name|r
operator|*
literal|257
expr_stmt|;
name|fore
operator|.
name|green
operator|=
name|g
operator|*
literal|257
expr_stmt|;
name|fore
operator|.
name|blue
operator|=
name|b
operator|*
literal|257
expr_stmt|;
name|gdk_gc_set_foreground
argument_list|(
name|copy
argument_list|,
operator|&
name|fore
argument_list|)
expr_stmt|;
name|gdk_draw_layout
argument_list|(
name|window
argument_list|,
name|copy
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|layout
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|copy
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdk_draw_layout
argument_list|(
name|window
argument_list|,
name|gc
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|layout
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|area
condition|)
name|gdk_gc_set_clip_rectangle
argument_list|(
name|gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

