begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewrendererimagefile.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpthumb/gimpthumb.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrendererimagefile.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer-frame.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_view_renderer_imagefile_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GdkPixbuf
modifier|*
name|gimp_view_renderer_imagefile_get_icon
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpViewRendererImagefile,gimp_view_renderer_imagefile,GIMP_TYPE_VIEW_RENDERER)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpViewRendererImagefile
argument_list|,
argument|gimp_view_renderer_imagefile
argument_list|,
argument|GIMP_TYPE_VIEW_RENDERER
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_view_renderer_imagefile_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_view_renderer_imagefile_class_init
parameter_list|(
name|GimpViewRendererImagefileClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpViewRendererClass
modifier|*
name|renderer_class
init|=
name|GIMP_VIEW_RENDERER_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|renderer_class
operator|->
name|render
operator|=
name|gimp_view_renderer_imagefile_render
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_imagefile_init (GimpViewRendererImagefile * renderer)
name|gimp_view_renderer_imagefile_init
parameter_list|(
name|GimpViewRendererImagefile
modifier|*
name|renderer
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_view_renderer_imagefile_render (GimpViewRenderer * renderer,GtkWidget * widget)
name|gimp_view_renderer_imagefile_render
parameter_list|(
name|GimpViewRenderer
modifier|*
name|renderer
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|gimp_view_renderer_get_frame_pixbuf
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|renderer
operator|->
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
init|=
name|GIMP_IMAGEFILE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|pixbuf
operator|=
name|gimp_view_renderer_imagefile_get_icon
argument_list|(
name|imagefile
argument_list|,
name|MIN
argument_list|(
name|renderer
operator|->
name|width
argument_list|,
name|renderer
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pixbuf
condition|)
block|{
name|gimp_view_renderer_render_pixbuf
argument_list|(
name|renderer
argument_list|,
name|pixbuf
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|stock_id
init|=
name|gimp_viewable_get_stock_id
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
decl_stmt|;
name|gimp_view_renderer_default_render_stock
argument_list|(
name|renderer
argument_list|,
name|widget
argument_list|,
name|stock_id
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* The code to get an icon for a mime-type is lifted from GtkRecentManager. */
end_comment

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|get_icon_for_mime_type (const char * mime_type,gint pixel_size)
name|get_icon_for_mime_type
parameter_list|(
specifier|const
name|char
modifier|*
name|mime_type
parameter_list|,
name|gint
name|pixel_size
parameter_list|)
block|{
name|GtkIconTheme
modifier|*
name|icon_theme
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|separator
decl_stmt|;
name|GString
modifier|*
name|icon_name
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|separator
operator|=
name|strchr
argument_list|(
name|mime_type
argument_list|,
literal|'/'
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|separator
condition|)
return|return
name|NULL
return|;
name|icon_theme
operator|=
name|gtk_icon_theme_get_default
argument_list|()
expr_stmt|;
comment|/* try with the three icon name variants for MIME types */
comment|/* canonicalize MIME type: foo/x-bar -> foo-x-bar */
name|icon_name
operator|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|g_string_append_len
argument_list|(
name|icon_name
argument_list|,
name|mime_type
argument_list|,
name|separator
operator|-
name|mime_type
argument_list|)
expr_stmt|;
name|g_string_append_c
argument_list|(
name|icon_name
argument_list|,
literal|'-'
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|icon_name
argument_list|,
name|separator
operator|+
literal|1
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gtk_icon_theme_load_icon
argument_list|(
name|icon_theme
argument_list|,
name|icon_name
operator|->
name|str
argument_list|,
name|pixel_size
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|icon_name
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
return|return
name|pixbuf
return|;
comment|/* canonicalize MIME type, and prepend "gnome-mime-" */
name|icon_name
operator|=
name|g_string_new
argument_list|(
literal|"gnome-mime-"
argument_list|)
expr_stmt|;
name|g_string_append_len
argument_list|(
name|icon_name
argument_list|,
name|mime_type
argument_list|,
name|separator
operator|-
name|mime_type
argument_list|)
expr_stmt|;
name|g_string_append_c
argument_list|(
name|icon_name
argument_list|,
literal|'-'
argument_list|)
expr_stmt|;
name|g_string_append
argument_list|(
name|icon_name
argument_list|,
name|separator
operator|+
literal|1
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gtk_icon_theme_load_icon
argument_list|(
name|icon_theme
argument_list|,
name|icon_name
operator|->
name|str
argument_list|,
name|pixel_size
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|icon_name
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
return|return
name|pixbuf
return|;
comment|/* try the MIME family icon */
name|icon_name
operator|=
name|g_string_new
argument_list|(
literal|"gnome-mime-"
argument_list|)
expr_stmt|;
name|g_string_append_len
argument_list|(
name|icon_name
argument_list|,
name|mime_type
argument_list|,
name|separator
operator|-
name|mime_type
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gtk_icon_theme_load_icon
argument_list|(
name|icon_theme
argument_list|,
name|icon_name
operator|->
name|str
argument_list|,
name|pixel_size
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|icon_name
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|pixbuf
return|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|get_icon_fallback (const gchar * icon_name,gint size)
name|get_icon_fallback
parameter_list|(
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
return|return
name|gtk_icon_theme_load_icon
argument_list|(
name|gtk_icon_theme_get_default
argument_list|()
argument_list|,
name|icon_name
argument_list|,
name|size
argument_list|,
name|GTK_ICON_LOOKUP_USE_BUILTIN
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GdkPixbuf
modifier|*
DECL|function|gimp_view_renderer_imagefile_get_icon (GimpImagefile * imagefile,gint size)
name|gimp_view_renderer_imagefile_get_icon
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|retval
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|imagefile
operator|->
name|thumbnail
operator|->
name|image_mimetype
condition|)
block|{
name|retval
operator|=
name|get_icon_for_mime_type
argument_list|(
name|imagefile
operator|->
name|thumbnail
operator|->
name|image_mimetype
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|retval
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|icon_name
init|=
name|GTK_STOCK_FILE
decl_stmt|;
if|if
condition|(
name|imagefile
operator|->
name|thumbnail
operator|->
name|image_state
operator|==
name|GIMP_THUMB_STATE_FOLDER
condition|)
name|icon_name
operator|=
name|GTK_STOCK_DIRECTORY
expr_stmt|;
name|retval
operator|=
name|gtk_icon_theme_load_icon
argument_list|(
name|gtk_icon_theme_get_default
argument_list|()
argument_list|,
name|icon_name
argument_list|,
name|size
argument_list|,
name|GTK_ICON_LOOKUP_USE_BUILTIN
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
end_function

end_unit

