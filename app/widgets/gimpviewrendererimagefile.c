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

begin_ifdef
ifdef|#
directive|ifdef
name|ENABLE_FILE_SYSTEM_ICONS
end_ifdef

begin_define
DECL|macro|GTK_FILE_SYSTEM_ENABLE_UNSUPPORTED
define|#
directive|define
name|GTK_FILE_SYSTEM_ENABLE_UNSUPPORTED
end_define

begin_include
include|#
directive|include
file|<gtk/gtkfilesystem.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
block|{
ifdef|#
directive|ifdef
name|ENABLE_FILE_SYSTEM_ICONS
name|renderer
operator|->
name|file_system
operator|=
name|NULL
expr_stmt|;
endif|#
directive|endif
block|}
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
ifdef|#
directive|ifdef
name|ENABLE_FILE_SYSTEM_ICONS
if|if
condition|(
operator|!
name|pixbuf
operator|&&
name|GIMP_VIEW_RENDERER_IMAGEFILE
argument_list|(
name|renderer
argument_list|)
operator|->
name|file_system
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|GtkFileSystem
modifier|*
name|file_system
decl_stmt|;
name|GtkFilePath
modifier|*
name|path
decl_stmt|;
name|file_system
operator|=
name|GIMP_VIEW_RENDERER_IMAGEFILE
argument_list|(
name|renderer
argument_list|)
operator|->
name|file_system
expr_stmt|;
name|path
operator|=
name|gtk_file_system_uri_to_path
argument_list|(
name|file_system
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gtk_file_system_render_icon
argument_list|(
name|file_system
argument_list|,
name|path
argument_list|,
name|widget
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
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_file_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
comment|/* ENABLE_FILE_SYSTEM_ICONS */
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

end_unit

