begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppixmap.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimppixmap.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_pixmap_class_init
parameter_list|(
name|GimpPixmapClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pixmap_init
parameter_list|(
name|GimpPixmap
modifier|*
name|pixmap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pixmap_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pixmap_create_from_xpm_d
parameter_list|(
name|GimpPixmap
modifier|*
name|pixmap
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkImageClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_pixmap_get_type (void)
name|gimp_pixmap_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|pixmap_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|pixmap_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|pixmap_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPixmapClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_pixmap_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPixmap
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_pixmap_init
block|,       }
decl_stmt|;
name|pixmap_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_IMAGE
argument_list|,
literal|"GimpPixmap"
argument_list|,
operator|&
name|pixmap_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|pixmap_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pixmap_class_init (GimpPixmapClass * klass)
name|gimp_pixmap_class_init
parameter_list|(
name|GimpPixmapClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_pixmap_realize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pixmap_init (GimpPixmap * pixmap)
name|gimp_pixmap_init
parameter_list|(
name|GimpPixmap
modifier|*
name|pixmap
parameter_list|)
block|{
name|pixmap
operator|->
name|xpm_data
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixmap_new:  * @xpm_data: A pointer to a XPM data structure as found in XPM files.  *  * Creates a new #GimpPixmap widget.  *  * Returns: A pointer to the new #GimpPixmap widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_pixmap_new (gchar ** xpm_data)
name|gimp_pixmap_new
parameter_list|(
name|gchar
modifier|*
modifier|*
name|xpm_data
parameter_list|)
block|{
name|GimpPixmap
modifier|*
name|pixmap
init|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PIXMAP
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gimp_pixmap_set
argument_list|(
name|pixmap
argument_list|,
name|xpm_data
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|pixmap
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_pixmap_set:  * @pixmap: The pixmap widget you want to set the new xpm_data for.  * @xpm_data: A pointer to a XPM data structure as found in XPM files.  *  * Sets a new image for an existing #GimpPixmap widget.  **/
end_comment

begin_function
name|void
DECL|function|gimp_pixmap_set (GimpPixmap * pixmap,gchar ** xpm_data)
name|gimp_pixmap_set
parameter_list|(
name|GimpPixmap
modifier|*
name|pixmap
parameter_list|,
name|gchar
modifier|*
modifier|*
name|xpm_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PIXMAP
argument_list|(
name|pixmap
argument_list|)
argument_list|)
expr_stmt|;
name|pixmap
operator|->
name|xpm_data
operator|=
name|xpm_data
expr_stmt|;
name|GTK_WIDGET
argument_list|(
name|pixmap
argument_list|)
operator|->
name|requisition
operator|.
name|width
operator|=
literal|0
expr_stmt|;
name|GTK_WIDGET
argument_list|(
name|pixmap
argument_list|)
operator|->
name|requisition
operator|.
name|height
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_REALIZED
argument_list|(
name|GTK_WIDGET
argument_list|(
name|pixmap
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|xpm_data
condition|)
block|{
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
if|if
condition|(
name|sscanf
argument_list|(
name|xpm_data
index|[
literal|0
index|]
argument_list|,
literal|"%d %d"
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
operator|!=
literal|2
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: passed pointer is no XPM data"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GTK_WIDGET
argument_list|(
name|pixmap
argument_list|)
operator|->
name|requisition
operator|.
name|width
operator|=
name|width
operator|+
name|GTK_MISC
argument_list|(
name|pixmap
argument_list|)
operator|->
name|xpad
operator|*
literal|2
expr_stmt|;
name|GTK_WIDGET
argument_list|(
name|pixmap
argument_list|)
operator|->
name|requisition
operator|.
name|height
operator|=
name|height
operator|+
name|GTK_MISC
argument_list|(
name|pixmap
argument_list|)
operator|->
name|ypad
operator|*
literal|2
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|gimp_pixmap_create_from_xpm_d
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pixmap_realize (GtkWidget * widget)
name|gimp_pixmap_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gimp_pixmap_create_from_xpm_d
argument_list|(
name|GIMP_PIXMAP
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pixmap_create_from_xpm_d (GimpPixmap * pixmap)
name|gimp_pixmap_create_from_xpm_d
parameter_list|(
name|GimpPixmap
modifier|*
name|pixmap
parameter_list|)
block|{
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|GdkPixmap
modifier|*
name|gdk_pixmap
init|=
name|NULL
decl_stmt|;
name|GdkBitmap
modifier|*
name|mask
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|pixmap
operator|->
name|xpm_data
condition|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|widget
operator|=
name|GTK_WIDGET
argument_list|(
name|pixmap
argument_list|)
expr_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gdk_pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|pixmap
operator|->
name|xpm_data
argument_list|)
expr_stmt|;
block|}
name|gtk_image_set_from_pixmap
argument_list|(
name|GTK_IMAGE
argument_list|(
name|pixmap
argument_list|)
argument_list|,
name|gdk_pixmap
argument_list|,
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdk_pixmap
condition|)
name|g_object_unref
argument_list|(
name|gdk_pixmap
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask
condition|)
name|g_object_unref
argument_list|(
name|mask
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

