begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"image_new.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"file_new_dialog.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager_pvt.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/parasite.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/wilber2.xpm"
end_include

begin_decl_stmt
DECL|variable|image_base_type_names
specifier|static
name|GList
modifier|*
name|image_base_type_names
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fill_type_names
specifier|static
name|GList
modifier|*
name|fill_type_names
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|last_values
specifier|static
name|GimpImageNewValues
name|last_values
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|current_cut_buffer
specifier|static
name|gboolean
name|current_cut_buffer
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|TileManager
modifier|*
name|global_buf
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|image_new_init (void)
name|image_new_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gboolean
name|image_new_inited
init|=
name|FALSE
decl_stmt|;
name|GimpImageBaseTypeName
modifier|*
name|new_type
decl_stmt|;
name|GimpFillTypeName
modifier|*
name|new_fill_type
decl_stmt|;
if|if
condition|(
name|image_new_inited
condition|)
return|return;
else|else
name|image_new_inited
operator|=
name|TRUE
expr_stmt|;
comment|/* Available Image Base Types */
name|new_type
operator|=
name|g_new
argument_list|(
name|GimpImageBaseTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_type
operator|->
name|type
operator|=
name|RGB
expr_stmt|;
name|new_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"RGB"
argument_list|)
expr_stmt|;
name|image_base_type_names
operator|=
name|g_list_append
argument_list|(
name|image_base_type_names
argument_list|,
name|new_type
argument_list|)
expr_stmt|;
name|new_type
operator|=
name|g_new
argument_list|(
name|GimpImageBaseTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_type
operator|->
name|type
operator|=
name|GRAY
expr_stmt|;
name|new_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Grayscale"
argument_list|)
expr_stmt|;
name|image_base_type_names
operator|=
name|g_list_append
argument_list|(
name|image_base_type_names
argument_list|,
name|new_type
argument_list|)
expr_stmt|;
comment|/* Available Fill Types */
name|new_fill_type
operator|=
name|g_new
argument_list|(
name|GimpFillTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_fill_type
operator|->
name|type
operator|=
name|FOREGROUND_FILL
expr_stmt|;
name|new_fill_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Foreground"
argument_list|)
expr_stmt|;
name|fill_type_names
operator|=
name|g_list_append
argument_list|(
name|fill_type_names
argument_list|,
name|new_fill_type
argument_list|)
expr_stmt|;
name|new_fill_type
operator|=
name|g_new
argument_list|(
name|GimpFillTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_fill_type
operator|->
name|type
operator|=
name|BACKGROUND_FILL
expr_stmt|;
name|new_fill_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Background"
argument_list|)
expr_stmt|;
name|fill_type_names
operator|=
name|g_list_append
argument_list|(
name|fill_type_names
argument_list|,
name|new_fill_type
argument_list|)
expr_stmt|;
name|new_fill_type
operator|=
name|g_new
argument_list|(
name|GimpFillTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_fill_type
operator|->
name|type
operator|=
name|WHITE_FILL
expr_stmt|;
name|new_fill_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"White"
argument_list|)
expr_stmt|;
name|fill_type_names
operator|=
name|g_list_append
argument_list|(
name|fill_type_names
argument_list|,
name|new_fill_type
argument_list|)
expr_stmt|;
name|new_fill_type
operator|=
name|g_new
argument_list|(
name|GimpFillTypeName
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|new_fill_type
operator|->
name|type
operator|=
name|TRANSPARENT_FILL
expr_stmt|;
name|new_fill_type
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Transparent"
argument_list|)
expr_stmt|;
name|fill_type_names
operator|=
name|g_list_append
argument_list|(
name|fill_type_names
argument_list|,
name|new_fill_type
argument_list|)
expr_stmt|;
comment|/* Set the last values used to default values. */
name|last_values
operator|.
name|width
operator|=
name|default_width
expr_stmt|;
name|last_values
operator|.
name|height
operator|=
name|default_height
expr_stmt|;
name|last_values
operator|.
name|unit
operator|=
name|default_units
expr_stmt|;
name|last_values
operator|.
name|xresolution
operator|=
name|default_xresolution
expr_stmt|;
name|last_values
operator|.
name|yresolution
operator|=
name|default_yresolution
expr_stmt|;
name|last_values
operator|.
name|res_unit
operator|=
name|default_resolution_units
expr_stmt|;
name|last_values
operator|.
name|type
operator|=
name|default_type
expr_stmt|;
name|last_values
operator|.
name|fill_type
operator|=
name|BACKGROUND_FILL
expr_stmt|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|image_new_get_image_base_type_names (void)
name|image_new_get_image_base_type_names
parameter_list|(
name|void
parameter_list|)
block|{
name|image_new_init
argument_list|()
expr_stmt|;
return|return
name|image_base_type_names
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|image_new_get_fill_type_names (void)
name|image_new_get_fill_type_names
parameter_list|(
name|void
parameter_list|)
block|{
name|image_new_init
argument_list|()
expr_stmt|;
return|return
name|fill_type_names
return|;
block|}
end_function

begin_function
name|void
DECL|function|image_new_create_window (const GimpImageNewValues * create_values,const GimpImage * image)
name|image_new_create_window
parameter_list|(
specifier|const
name|GimpImageNewValues
modifier|*
name|create_values
parameter_list|,
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpImageNewValues
modifier|*
name|values
decl_stmt|;
name|image_new_init
argument_list|()
expr_stmt|;
name|values
operator|=
name|image_new_values_new
argument_list|(
name|create_values
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|values
operator|->
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|values
operator|->
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|values
operator|->
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|values
operator|->
name|xresolution
argument_list|,
operator|&
name|values
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|values
operator|->
name|type
operator|=
name|gimp_image_base_type
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|values
operator|->
name|type
operator|==
name|INDEXED
condition|)
name|values
operator|->
name|type
operator|=
name|RGB
expr_stmt|;
comment|/* no indexed images */
block|}
comment|/*  If a cut buffer exists, default to using its size for the new image    *  also check to see if a new_image has been opened    */
if|if
condition|(
name|global_buf
operator|&&
name|current_cut_buffer
condition|)
block|{
name|values
operator|->
name|width
operator|=
name|global_buf
operator|->
name|width
expr_stmt|;
name|values
operator|->
name|height
operator|=
name|global_buf
operator|->
name|height
expr_stmt|;
block|}
name|ui_new_image_window_create
argument_list|(
name|values
argument_list|)
expr_stmt|;
name|image_new_values_free
argument_list|(
name|values
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|image_new_set_default_values (const GimpImageNewValues * values)
name|image_new_set_default_values
parameter_list|(
specifier|const
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|image_new_init
argument_list|()
expr_stmt|;
name|memcpy
argument_list|(
operator|&
name|last_values
argument_list|,
name|values
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpImageNewValues
argument_list|)
argument_list|)
expr_stmt|;
name|current_cut_buffer
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|GimpImageNewValues
modifier|*
DECL|function|image_new_values_new (const GimpImageNewValues * src_values)
name|image_new_values_new
parameter_list|(
specifier|const
name|GimpImageNewValues
modifier|*
name|src_values
parameter_list|)
block|{
name|GimpImageNewValues
modifier|*
name|values
decl_stmt|;
name|image_new_init
argument_list|()
expr_stmt|;
name|values
operator|=
name|g_new
argument_list|(
name|GimpImageNewValues
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_values
condition|)
name|memcpy
argument_list|(
name|values
argument_list|,
name|src_values
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpImageNewValues
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|memcpy
argument_list|(
name|values
argument_list|,
operator|&
name|last_values
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpImageNewValues
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|values
return|;
block|}
end_function

begin_function
name|void
DECL|function|image_new_values_free (GimpImageNewValues * values)
name|image_new_values_free
parameter_list|(
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|values
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|image_new_rotate_the_shield_harmonics (GDisplay * display)
name|image_new_rotate_the_shield_harmonics
parameter_list|(
name|GDisplay
modifier|*
name|display
parameter_list|)
block|{
specifier|static
name|GdkPixmap
modifier|*
name|pixmap
init|=
name|NULL
decl_stmt|;
specifier|static
name|GdkBitmap
modifier|*
name|mask
init|=
name|NULL
decl_stmt|;
specifier|static
name|gint
name|width
init|=
literal|0
decl_stmt|;
specifier|static
name|gint
name|height
init|=
literal|0
decl_stmt|;
while|while
condition|(
name|gtk_events_pending
argument_list|()
condition|)
name|gtk_main_iteration
argument_list|()
expr_stmt|;
if|if
condition|(
name|pixmap
operator|==
name|NULL
condition|)
block|{
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|display
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|display
operator|->
name|canvas
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
name|wilber2_xpm
argument_list|)
expr_stmt|;
name|gdk_window_get_size
argument_list|(
name|pixmap
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|display
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|width
operator|>=
name|width
operator|&&
name|display
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|height
operator|>=
name|height
condition|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
operator|(
name|display
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|width
operator|-
name|width
operator|)
operator|/
literal|2
expr_stmt|;
name|y
operator|=
operator|(
name|display
operator|->
name|canvas
operator|->
name|allocation
operator|.
name|height
operator|-
name|height
operator|)
operator|/
literal|2
expr_stmt|;
name|gdk_gc_set_clip_mask
argument_list|(
name|display
operator|->
name|canvas
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|mask
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_origin
argument_list|(
name|display
operator|->
name|canvas
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gdk_draw_pixmap
argument_list|(
name|display
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|display
operator|->
name|canvas
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|pixmap
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_mask
argument_list|(
name|display
operator|->
name|canvas
operator|->
name|style
operator|->
name|black_gc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_gc_set_clip_origin
argument_list|(
name|display
operator|->
name|canvas
operator|->
name|style
operator|->
name|black_gc
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|image_new_create_image (const GimpImageNewValues * values)
name|image_new_create_image
parameter_list|(
specifier|const
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GDisplay
modifier|*
name|display
decl_stmt|;
name|Layer
modifier|*
name|layer
decl_stmt|;
name|GimpImageType
name|type
decl_stmt|;
name|GimpParasite
modifier|*
name|comment_parasite
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|values
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|image_new_set_default_values
argument_list|(
name|values
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|values
operator|->
name|fill_type
condition|)
block|{
case|case
name|FOREGROUND_FILL
case|:
case|case
name|BACKGROUND_FILL
case|:
case|case
name|WHITE_FILL
case|:
name|type
operator|=
operator|(
name|values
operator|->
name|type
operator|==
name|RGB
operator|)
condition|?
name|RGB_GIMAGE
else|:
name|GRAY_GIMAGE
expr_stmt|;
break|break;
case|case
name|TRANSPARENT_FILL
case|:
name|type
operator|=
operator|(
name|values
operator|->
name|type
operator|==
name|RGB
operator|)
condition|?
name|RGBA_GIMAGE
else|:
name|GRAYA_GIMAGE
expr_stmt|;
break|break;
default|default:
name|type
operator|=
name|RGB_GIMAGE
expr_stmt|;
break|break;
block|}
name|image
operator|=
name|gimage_new
argument_list|(
name|values
operator|->
name|width
argument_list|,
name|values
operator|->
name|height
argument_list|,
name|values
operator|->
name|type
argument_list|)
expr_stmt|;
name|gimp_image_set_resolution
argument_list|(
name|image
argument_list|,
name|values
operator|->
name|xresolution
argument_list|,
name|values
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|image
argument_list|,
name|values
operator|->
name|unit
argument_list|)
expr_stmt|;
if|if
condition|(
name|default_comment
condition|)
block|{
name|comment_parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-comment"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|default_comment
argument_list|)
operator|+
literal|1
argument_list|,
operator|(
name|gpointer
operator|)
name|default_comment
argument_list|)
expr_stmt|;
name|gimp_image_parasite_attach
argument_list|(
name|image
argument_list|,
name|comment_parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|comment_parasite
argument_list|)
expr_stmt|;
block|}
comment|/*  Make the background (or first) layer  */
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|layer
operator|=
name|layer_new
argument_list|(
name|image
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|type
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
block|{
comment|/*  add the new layer to the gimage  */
name|gimp_image_undo_disable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|drawable_fill
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
name|values
operator|->
name|fill_type
argument_list|)
expr_stmt|;
name|gimp_image_clean_all
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|display
operator|=
name|gdisplay_new
argument_list|(
name|image
argument_list|,
literal|0x0101
argument_list|)
expr_stmt|;
name|gimp_context_set_display
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|double_speed
condition|)
name|gtk_idle_add
argument_list|(
operator|(
name|GtkFunction
operator|)
name|image_new_rotate_the_shield_harmonics
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gdouble
DECL|function|image_new_calculate_size (GimpImageNewValues * values)
name|image_new_calculate_size
parameter_list|(
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
block|{
name|gdouble
name|width
decl_stmt|,
name|height
decl_stmt|,
name|size
decl_stmt|;
name|width
operator|=
operator|(
name|gdouble
operator|)
name|values
operator|->
name|width
expr_stmt|;
name|height
operator|=
operator|(
name|gdouble
operator|)
name|values
operator|->
name|height
expr_stmt|;
name|size
operator|=
name|width
operator|*
name|height
operator|*
operator|(
operator|(
name|values
operator|->
name|type
operator|==
name|RGB
condition|?
literal|3
else|:
literal|1
operator|)
operator|+
comment|/* bytes per pixel */
operator|(
name|values
operator|->
name|fill_type
operator|==
name|TRANSPARENT_FILL
condition|?
literal|1
else|:
literal|0
operator|)
operator|)
expr_stmt|;
comment|/* alpha channel */
return|return
name|size
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|image_new_get_size_string (gdouble size)
name|image_new_get_size_string
parameter_list|(
name|gdouble
name|size
parameter_list|)
block|{
if|if
condition|(
name|size
operator|<
literal|4096
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d Bytes"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|size
argument_list|)
return|;
elseif|else
if|if
condition|(
name|size
operator|<
literal|1024
operator|*
literal|10
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.2f KB"
argument_list|)
argument_list|,
name|size
operator|/
literal|1024
argument_list|)
return|;
elseif|else
if|if
condition|(
name|size
operator|<
literal|1024
operator|*
literal|100
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.1f KB"
argument_list|)
argument_list|,
name|size
operator|/
literal|1024
argument_list|)
return|;
elseif|else
if|if
condition|(
name|size
operator|<
literal|1024
operator|*
literal|1024
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d KB"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|size
operator|/
literal|1024
argument_list|)
return|;
elseif|else
if|if
condition|(
name|size
operator|<
literal|1024
operator|*
literal|1024
operator|*
literal|10
condition|)
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.2f MB"
argument_list|)
argument_list|,
name|size
operator|/
literal|1024
operator|/
literal|1024
argument_list|)
return|;
else|else
return|return
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%.1f MB"
argument_list|)
argument_list|,
name|size
operator|/
literal|1024
operator|/
literal|1024
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|image_new_reset_current_cut_buffer (void)
name|image_new_reset_current_cut_buffer
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* This function just changes the status of current_cut_buffer      if there hass been a cut/copy since the last file new */
name|current_cut_buffer
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

end_unit

