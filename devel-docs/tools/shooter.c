begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gdk/gdkx.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<X11/extensions/shape.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
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

begin_include
include|#
directive|include
file|"shadow.h"
end_include

begin_include
include|#
directive|include
file|"units.h"
end_include

begin_include
include|#
directive|include
file|"widgets.h"
end_include

begin_function
specifier|static
name|Window
DECL|function|find_toplevel_window (Display * display,Window xid)
name|find_toplevel_window
parameter_list|(
name|Display
modifier|*
name|display
parameter_list|,
name|Window
name|xid
parameter_list|)
block|{
name|Window
name|root
decl_stmt|,
name|parent
decl_stmt|,
modifier|*
name|children
decl_stmt|;
name|guint
name|nchildren
decl_stmt|;
do|do
block|{
if|if
condition|(
name|XQueryTree
argument_list|(
name|display
argument_list|,
name|xid
argument_list|,
operator|&
name|root
argument_list|,
operator|&
name|parent
argument_list|,
operator|&
name|children
argument_list|,
operator|&
name|nchildren
argument_list|)
operator|==
literal|0
condition|)
block|{
name|g_warning
argument_list|(
literal|"Couldn't find window manager window"
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
if|if
condition|(
name|root
operator|==
name|parent
condition|)
return|return
name|xid
return|;
name|xid
operator|=
name|parent
expr_stmt|;
block|}
do|while
condition|(
name|TRUE
condition|)
do|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|add_border_to_shot (GdkPixbuf * pixbuf)
name|add_border_to_shot
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|retval
decl_stmt|;
name|retval
operator|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|TRUE
argument_list|,
literal|8
argument_list|,
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
operator|+
literal|2
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
operator|+
literal|2
argument_list|)
expr_stmt|;
comment|/* Fill with solid black */
name|gdk_pixbuf_fill
argument_list|(
name|retval
argument_list|,
literal|0x000000FF
argument_list|)
expr_stmt|;
name|gdk_pixbuf_copy_area
argument_list|(
name|pixbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|retval
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|remove_shaped_area (GdkPixbuf * pixbuf,Window window)
name|remove_shaped_area
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|Window
name|window
parameter_list|)
block|{
name|Display
modifier|*
name|display
decl_stmt|;
name|GdkPixbuf
modifier|*
name|retval
decl_stmt|;
name|XRectangle
modifier|*
name|rectangles
decl_stmt|;
name|gint
name|rectangle_count
decl_stmt|,
name|rectangle_order
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|retval
operator|=
name|gdk_pixbuf_new
argument_list|(
name|GDK_COLORSPACE_RGB
argument_list|,
name|TRUE
argument_list|,
literal|8
argument_list|,
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
expr_stmt|;
name|gdk_pixbuf_fill
argument_list|(
name|retval
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|display
operator|=
name|gdk_x11_display_get_xdisplay
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|)
expr_stmt|;
name|rectangles
operator|=
name|XShapeGetRectangles
argument_list|(
name|display
argument_list|,
name|window
argument_list|,
name|ShapeBounding
argument_list|,
operator|&
name|rectangle_count
argument_list|,
operator|&
name|rectangle_order
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|rectangle_count
condition|;
name|i
operator|++
control|)
block|{
name|int
name|y
decl_stmt|,
name|x
decl_stmt|;
for|for
control|(
name|y
operator|=
name|rectangles
index|[
name|i
index|]
operator|.
name|y
init|;
name|y
operator|<
name|rectangles
index|[
name|i
index|]
operator|.
name|y
operator|+
name|rectangles
index|[
name|i
index|]
operator|.
name|height
condition|;
name|y
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|src_pixels
decl_stmt|;
name|guchar
modifier|*
name|dest_pixels
decl_stmt|;
name|src_pixels
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
operator|+
name|y
operator|*
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
operator|+
name|rectangles
index|[
name|i
index|]
operator|.
name|x
operator|*
operator|(
name|gdk_pixbuf_get_has_alpha
argument_list|(
name|pixbuf
argument_list|)
condition|?
literal|4
else|:
literal|3
operator|)
expr_stmt|;
name|dest_pixels
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|retval
argument_list|)
operator|+
name|y
operator|*
name|gdk_pixbuf_get_rowstride
argument_list|(
name|retval
argument_list|)
operator|+
name|rectangles
index|[
name|i
index|]
operator|.
name|x
operator|*
literal|4
expr_stmt|;
for|for
control|(
name|x
operator|=
name|rectangles
index|[
name|i
index|]
operator|.
name|x
init|;
name|x
operator|<
name|rectangles
index|[
name|i
index|]
operator|.
name|x
operator|+
name|rectangles
index|[
name|i
index|]
operator|.
name|width
condition|;
name|x
operator|++
control|)
block|{
operator|*
name|dest_pixels
operator|++
operator|=
operator|*
name|src_pixels
operator|++
expr_stmt|;
operator|*
name|dest_pixels
operator|++
operator|=
operator|*
name|src_pixels
operator|++
expr_stmt|;
operator|*
name|dest_pixels
operator|++
operator|=
operator|*
name|src_pixels
operator|++
expr_stmt|;
operator|*
name|dest_pixels
operator|++
operator|=
literal|255
expr_stmt|;
if|if
condition|(
name|gdk_pixbuf_get_has_alpha
argument_list|(
name|pixbuf
argument_list|)
condition|)
name|src_pixels
operator|++
expr_stmt|;
block|}
block|}
block|}
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|take_window_shot (Window child,gboolean include_decoration)
name|take_window_shot
parameter_list|(
name|Window
name|child
parameter_list|,
name|gboolean
name|include_decoration
parameter_list|)
block|{
name|GdkDisplay
modifier|*
name|display
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|Window
name|xid
decl_stmt|;
name|gint
name|x_orig
decl_stmt|,
name|y_orig
decl_stmt|;
name|gint
name|x
init|=
literal|0
decl_stmt|,
name|y
init|=
literal|0
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|GdkPixbuf
modifier|*
name|tmp
decl_stmt|,
modifier|*
name|tmp2
decl_stmt|;
name|GdkPixbuf
modifier|*
name|retval
decl_stmt|;
name|display
operator|=
name|gdk_display_get_default
argument_list|()
expr_stmt|;
name|screen
operator|=
name|gdk_screen_get_default
argument_list|()
expr_stmt|;
if|if
condition|(
name|include_decoration
condition|)
name|xid
operator|=
name|find_toplevel_window
argument_list|(
name|gdk_x11_display_get_xdisplay
argument_list|(
name|display
argument_list|)
argument_list|,
name|child
argument_list|)
expr_stmt|;
else|else
name|xid
operator|=
name|child
expr_stmt|;
name|window
operator|=
name|gdk_window_foreign_new_for_display
argument_list|(
name|display
argument_list|,
name|xid
argument_list|)
expr_stmt|;
name|gdk_drawable_get_size
argument_list|(
name|window
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|gdk_window_get_origin
argument_list|(
name|window
argument_list|,
operator|&
name|x_orig
argument_list|,
operator|&
name|y_orig
argument_list|)
expr_stmt|;
if|if
condition|(
name|x_orig
operator|<
literal|0
condition|)
block|{
name|x
operator|=
operator|-
name|x_orig
expr_stmt|;
name|width
operator|=
name|width
operator|+
name|x_orig
expr_stmt|;
name|x_orig
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|y_orig
operator|<
literal|0
condition|)
block|{
name|y
operator|=
operator|-
name|y_orig
expr_stmt|;
name|height
operator|=
name|height
operator|+
name|y_orig
expr_stmt|;
name|y_orig
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|x_orig
operator|+
name|width
operator|>
name|gdk_screen_get_width
argument_list|(
name|screen
argument_list|)
condition|)
name|width
operator|=
name|gdk_screen_get_width
argument_list|(
name|screen
argument_list|)
operator|-
name|x_orig
expr_stmt|;
if|if
condition|(
name|y_orig
operator|+
name|height
operator|>
name|gdk_screen_get_height
argument_list|(
name|screen
argument_list|)
condition|)
name|height
operator|=
name|gdk_screen_get_height
argument_list|(
name|screen
argument_list|)
operator|-
name|y_orig
expr_stmt|;
name|tmp
operator|=
name|gdk_pixbuf_get_from_drawable
argument_list|(
name|NULL
argument_list|,
name|window
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|include_decoration
condition|)
name|tmp2
operator|=
name|remove_shaped_area
argument_list|(
name|tmp
argument_list|,
name|xid
argument_list|)
expr_stmt|;
else|else
name|tmp2
operator|=
name|add_border_to_shot
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|retval
operator|=
name|create_shadowed_pixbuf
argument_list|(
name|tmp2
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tmp2
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|shooter_get_foreground (GimpRGB * color)
name|shooter_get_foreground
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|color
operator|->
name|r
operator|=
name|color
operator|->
name|g
operator|=
name|color
operator|->
name|b
operator|=
literal|0.0
expr_stmt|;
name|color
operator|->
name|a
operator|=
literal|1.0
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|shooter_get_background (GimpRGB * color)
name|shooter_get_background
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|color
operator|->
name|r
operator|=
name|color
operator|->
name|g
operator|=
name|color
operator|->
name|b
operator|=
literal|1.0
expr_stmt|;
name|color
operator|->
name|a
operator|=
literal|1.0
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|shooter_standard_help (const gchar * help_id,gpointer help_data)
name|shooter_standard_help
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|shooter_ensure_modules (void)
name|shooter_ensure_modules
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
name|config
init|=
name|gimp_config_build_plug_in_path
argument_list|(
literal|"modules"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|path
init|=
name|gimp_config_path_expand
argument_list|(
name|config
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|module_db
operator|=
name|gimp_module_db_new
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_module_db_load
argument_list|(
name|module_db
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|config
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|int
DECL|function|main (int argc,char ** argv)
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|screenshot
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|toplevels
decl_stmt|;
name|GList
modifier|*
name|node
decl_stmt|;
name|g_set_application_name
argument_list|(
literal|"GIMP documention shooter"
argument_list|)
expr_stmt|;
comment|/* If there's no DISPLAY, we silently error out.    * We don't want to break headless builds.    */
if|if
condition|(
operator|!
name|gtk_init_check
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
condition|)
return|return
name|EXIT_SUCCESS
return|;
name|gtk_rc_add_default_file
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
name|units_init
argument_list|()
expr_stmt|;
name|gimp_widgets_init
argument_list|(
name|shooter_standard_help
argument_list|,
name|shooter_get_foreground
argument_list|,
name|shooter_get_background
argument_list|,
name|shooter_ensure_modules
argument_list|)
expr_stmt|;
name|toplevels
operator|=
name|get_all_widgets
argument_list|()
expr_stmt|;
for|for
control|(
name|node
operator|=
name|toplevels
init|;
name|node
condition|;
name|node
operator|=
name|g_list_next
argument_list|(
name|node
argument_list|)
control|)
block|{
name|GdkWindow
modifier|*
name|window
decl_stmt|;
name|WidgetInfo
modifier|*
name|info
decl_stmt|;
name|XID
name|xid
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|info
operator|=
name|node
operator|->
name|data
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|info
operator|->
name|window
argument_list|)
expr_stmt|;
name|window
operator|=
name|info
operator|->
name|window
operator|->
name|window
expr_stmt|;
name|gtk_widget_show_now
argument_list|(
name|info
operator|->
name|window
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|info
operator|->
name|window
argument_list|)
expr_stmt|;
while|while
condition|(
name|gtk_events_pending
argument_list|()
condition|)
block|{
name|gtk_main_iteration
argument_list|()
expr_stmt|;
block|}
name|sleep
argument_list|(
literal|1
argument_list|)
expr_stmt|;
while|while
condition|(
name|gtk_events_pending
argument_list|()
condition|)
block|{
name|gtk_main_iteration
argument_list|()
expr_stmt|;
block|}
name|xid
operator|=
name|gdk_x11_drawable_get_xid
argument_list|(
name|GDK_DRAWABLE
argument_list|(
name|window
argument_list|)
argument_list|)
expr_stmt|;
name|screenshot
operator|=
name|take_window_shot
argument_list|(
name|xid
argument_list|,
name|info
operator|->
name|include_decorations
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s.png"
argument_list|,
name|info
operator|->
name|name
argument_list|)
expr_stmt|;
name|gdk_pixbuf_save
argument_list|(
name|screenshot
argument_list|,
name|filename
argument_list|,
literal|"png"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|info
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

end_unit

