begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
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
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_comment
comment|/* gets defined by glib.h */
end_comment

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|_O_BINARY
end_ifndef

begin_define
DECL|macro|_O_BINARY
define|#
directive|define
name|_O_BINARY
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/brush-scale.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush-header.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a348ba10103
block|{
DECL|enumerator|SPACING_CHANGED
name|SPACING_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_brush_class_init
parameter_list|(
name|GimpBrushClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_init
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gsize
name|gimp_brush_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_brush_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_brush_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpBrush
modifier|*
name|gimp_brush_real_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_real_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|brush_signals
specifier|static
name|guint
name|brush_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDataClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_brush_get_type (void)
name|gimp_brush_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|brush_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|brush_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|brush_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpBrushClass
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
name|gimp_brush_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpBrush
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_brush_init
block|,       }
decl_stmt|;
name|brush_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DATA
argument_list|,
literal|"GimpBrush"
argument_list|,
operator|&
name|brush_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|brush_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_class_init (GimpBrushClass * klass)
name|gimp_brush_class_init
parameter_list|(
name|GimpBrushClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|GimpDataClass
modifier|*
name|data_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|data_class
operator|=
name|GIMP_DATA_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|brush_signals
index|[
name|SPACING_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"spacing_changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpBrushClass
argument_list|,
name|spacing_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_brush_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_brush_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|get_popup_size
operator|=
name|gimp_brush_get_popup_size
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_brush_get_new_preview
expr_stmt|;
name|data_class
operator|->
name|get_extension
operator|=
name|gimp_brush_get_extension
expr_stmt|;
name|klass
operator|->
name|select_brush
operator|=
name|gimp_brush_real_select_brush
expr_stmt|;
name|klass
operator|->
name|want_null_motion
operator|=
name|gimp_brush_real_want_null_motion
expr_stmt|;
name|klass
operator|->
name|spacing_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_init (GimpBrush * brush)
name|gimp_brush_init
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|brush
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
name|brush
operator|->
name|pixmap
operator|=
name|NULL
expr_stmt|;
name|brush
operator|->
name|spacing
operator|=
literal|20
expr_stmt|;
name|brush
operator|->
name|x_axis
operator|.
name|x
operator|=
literal|15.0
expr_stmt|;
name|brush
operator|->
name|x_axis
operator|.
name|y
operator|=
literal|0.0
expr_stmt|;
name|brush
operator|->
name|y_axis
operator|.
name|x
operator|=
literal|0.0
expr_stmt|;
name|brush
operator|->
name|y_axis
operator|.
name|y
operator|=
literal|15.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_finalize (GObject * object)
name|gimp_brush_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|mask
condition|)
block|{
name|temp_buf_free
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
name|brush
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|brush
operator|->
name|pixmap
condition|)
block|{
name|temp_buf_free
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|)
expr_stmt|;
name|brush
operator|->
name|pixmap
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gsize
DECL|function|gimp_brush_get_memsize (GimpObject * object)
name|gimp_brush_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|mask
condition|)
name|memsize
operator|+=
name|temp_buf_get_memsize
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|pixmap
condition|)
name|memsize
operator|+=
name|temp_buf_get_memsize
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_get_popup_size (GimpViewable * viewable,gint width,gint height,gboolean dot_for_dot,gint * popup_width,gint * popup_height)
name|gimp_brush_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|>
name|width
operator|||
name|brush
operator|->
name|mask
operator|->
name|height
operator|>
name|height
condition|)
block|{
operator|*
name|popup_width
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
operator|*
name|popup_height
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_brush_get_new_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_brush_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|gint
name|brush_width
decl_stmt|;
name|gint
name|brush_height
decl_stmt|;
name|TempBuf
modifier|*
name|mask_buf
init|=
name|NULL
decl_stmt|;
name|TempBuf
modifier|*
name|pixmap_buf
init|=
name|NULL
decl_stmt|;
name|TempBuf
modifier|*
name|return_buf
init|=
name|NULL
decl_stmt|;
name|guchar
name|transp
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|guchar
modifier|*
name|mask
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gboolean
name|scale
init|=
name|FALSE
decl_stmt|;
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|mask_buf
operator|=
name|gimp_brush_get_mask
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|pixmap_buf
operator|=
name|gimp_brush_get_pixmap
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|brush_width
operator|=
name|mask_buf
operator|->
name|width
expr_stmt|;
name|brush_height
operator|=
name|mask_buf
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|brush_width
operator|>
name|width
operator|||
name|brush_height
operator|>
name|height
condition|)
block|{
name|gdouble
name|ratio_x
init|=
operator|(
name|gdouble
operator|)
name|brush_width
operator|/
name|width
decl_stmt|;
name|gdouble
name|ratio_y
init|=
operator|(
name|gdouble
operator|)
name|brush_height
operator|/
name|height
decl_stmt|;
name|brush_width
operator|=
operator|(
name|gdouble
operator|)
name|brush_width
operator|/
name|MAX
argument_list|(
name|ratio_x
argument_list|,
name|ratio_y
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|brush_height
operator|=
operator|(
name|gdouble
operator|)
name|brush_height
operator|/
name|MAX
argument_list|(
name|ratio_x
argument_list|,
name|ratio_y
argument_list|)
operator|+
literal|0.5
expr_stmt|;
name|mask_buf
operator|=
name|brush_scale_mask
argument_list|(
name|mask_buf
argument_list|,
name|brush_width
argument_list|,
name|brush_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap_buf
condition|)
block|{
comment|/* TODO: the scale function should scale the pixmap and the 	   *  mask in one run 	   */
name|pixmap_buf
operator|=
name|brush_scale_pixmap
argument_list|(
name|pixmap_buf
argument_list|,
name|brush_width
argument_list|,
name|brush_height
argument_list|)
expr_stmt|;
block|}
name|scale
operator|=
name|TRUE
expr_stmt|;
block|}
name|return_buf
operator|=
name|temp_buf_new
argument_list|(
name|brush_width
argument_list|,
name|brush_height
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|transp
argument_list|)
expr_stmt|;
name|mask
operator|=
name|temp_buf_data
argument_list|(
name|mask_buf
argument_list|)
expr_stmt|;
name|buf
operator|=
name|temp_buf_data
argument_list|(
name|return_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap_buf
condition|)
block|{
name|guchar
modifier|*
name|pixmap
init|=
name|temp_buf_data
argument_list|(
name|pixmap_buf
argument_list|)
decl_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|brush_height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|brush_width
condition|;
name|x
operator|++
control|)
block|{
operator|*
name|buf
operator|++
operator|=
operator|*
name|pixmap
operator|++
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
operator|*
name|pixmap
operator|++
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
operator|*
name|pixmap
operator|++
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
operator|*
name|mask
operator|++
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|brush_height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|brush_width
condition|;
name|x
operator|++
control|)
block|{
operator|*
name|buf
operator|++
operator|=
literal|0
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
literal|0
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
literal|0
expr_stmt|;
operator|*
name|buf
operator|++
operator|=
operator|*
name|mask
operator|++
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|scale
condition|)
block|{
name|temp_buf_free
argument_list|(
name|mask_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixmap_buf
condition|)
name|temp_buf_free
argument_list|(
name|pixmap_buf
argument_list|)
expr_stmt|;
block|}
return|return
name|return_buf
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_brush_get_extension (GimpData * data)
name|gimp_brush_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|GIMP_BRUSH_FILE_EXTENSION
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_brush_new (const gchar * name,gboolean stingy_memory_use)
name|gimp_brush_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|stingy_memory_use
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|gimp_brush_generated_new
argument_list|(
literal|5.0
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
name|stingy_memory_use
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_brush_get_standard (void)
name|gimp_brush_get_standard
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpBrush
modifier|*
name|standard_brush
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_brush
condition|)
block|{
name|standard_brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|gimp_brush_generated_new
argument_list|(
literal|5.0
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|standard_brush
argument_list|)
argument_list|,
literal|"Standard"
argument_list|)
expr_stmt|;
comment|/*  set ref_count to 2 --> never swap the standard brush  */
name|g_object_ref
argument_list|(
name|standard_brush
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_DATA
argument_list|(
name|standard_brush
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_brush_load (const gchar * filename,gboolean stingy_memory_use,GError ** error)
name|gimp_brush_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|stingy_memory_use
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|gint
name|fd
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fd
operator|=
name|open
argument_list|(
name|filename
argument_list|,
name|O_RDONLY
operator||
name|_O_BINARY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_OPEN
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|brush
operator|=
name|gimp_brush_load_brush
argument_list|(
name|fd
argument_list|,
name|filename
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|brush
condition|)
return|return
name|NULL
return|;
name|gimp_data_set_filename
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/*  Swap the brush to disk (if we're being stingy with memory) */
if|if
condition|(
name|stingy_memory_use
condition|)
block|{
name|temp_buf_swap
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|pixmap
condition|)
name|temp_buf_swap
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|)
expr_stmt|;
block|}
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_select_brush (GimpBrush * brush,GimpCoords * last_coords,GimpCoords * cur_coords)
name|gimp_brush_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|last_coords
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cur_coords
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_BRUSH_GET_CLASS
argument_list|(
name|brush
argument_list|)
operator|->
name|select_brush
argument_list|(
name|brush
argument_list|,
name|last_coords
argument_list|,
name|cur_coords
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_brush_want_null_motion (GimpBrush * brush,GimpCoords * last_coords,GimpCoords * cur_coords)
name|gimp_brush_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|last_coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|cur_coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GIMP_BRUSH_GET_CLASS
argument_list|(
name|brush
argument_list|)
operator|->
name|want_null_motion
argument_list|(
name|brush
argument_list|,
name|last_coords
argument_list|,
name|cur_coords
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpBrush
modifier|*
DECL|function|gimp_brush_real_select_brush (GimpBrush * brush,GimpCoords * last_coords,GimpCoords * cur_coords)
name|gimp_brush_real_select_brush
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
block|{
return|return
name|brush
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_real_want_null_motion (GimpBrush * brush,GimpCoords * last_coords,GimpCoords * cur_coords)
name|gimp_brush_real_want_null_motion
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpCoords
modifier|*
name|last_coords
parameter_list|,
name|GimpCoords
modifier|*
name|cur_coords
parameter_list|)
block|{
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_get_mask (const GimpBrush * brush)
name|gimp_brush_get_mask
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|brush
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|mask
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_brush_get_pixmap (const GimpBrush * brush)
name|gimp_brush_get_pixmap
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|brush
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|pixmap
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_brush_get_spacing (const GimpBrush * brush)
name|gimp_brush_get_spacing
parameter_list|(
specifier|const
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|spacing
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_set_spacing (GimpBrush * brush,gint spacing)
name|gimp_brush_set_spacing
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gint
name|spacing
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|spacing
operator|!=
name|spacing
condition|)
block|{
name|brush
operator|->
name|spacing
operator|=
name|spacing
expr_stmt|;
name|gimp_brush_spacing_changed
argument_list|(
name|brush
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_spacing_changed (GimpBrush * brush)
name|gimp_brush_spacing_changed
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|brush
argument_list|,
name|brush_signals
index|[
name|SPACING_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_load_brush (gint fd,const gchar * filename,GError ** error)
name|gimp_brush_load_brush
parameter_list|(
name|gint
name|fd
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|gint
name|bn_size
decl_stmt|;
name|BrushHeader
name|header
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|fd
operator|!=
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Read in the header size  */
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
operator|&
name|header
argument_list|,
sizeof|sizeof
argument_list|(
name|header
argument_list|)
argument_list|)
operator|!=
sizeof|sizeof
argument_list|(
name|header
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Could not read %d bytes from '%s': %s"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
sizeof|sizeof
argument_list|(
name|header
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  rearrange the bytes in each unsigned int  */
name|header
operator|.
name|header_size
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|header_size
argument_list|)
expr_stmt|;
name|header
operator|.
name|version
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|version
argument_list|)
expr_stmt|;
name|header
operator|.
name|width
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|width
argument_list|)
expr_stmt|;
name|header
operator|.
name|height
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|height
argument_list|)
expr_stmt|;
name|header
operator|.
name|bytes
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|bytes
argument_list|)
expr_stmt|;
name|header
operator|.
name|magic_number
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|magic_number
argument_list|)
expr_stmt|;
name|header
operator|.
name|spacing
operator|=
name|g_ntohl
argument_list|(
name|header
operator|.
name|spacing
argument_list|)
expr_stmt|;
comment|/*  Check for correct file format */
comment|/*  It looks as if version 1 did not have the same magic number.  (neo)  */
if|if
condition|(
name|header
operator|.
name|version
operator|!=
literal|1
operator|&&
operator|(
name|header
operator|.
name|magic_number
operator|!=
name|GBRUSH_MAGIC
operator|||
name|header
operator|.
name|version
operator|!=
literal|2
operator|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parsing error (unknown version %d):\n"
literal|"Brush file '%s'"
argument_list|)
argument_list|,
name|header
operator|.
name|version
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|header
operator|.
name|version
operator|==
literal|1
condition|)
block|{
comment|/*  If this is a version 1 brush, set the fp back 8 bytes  */
name|lseek
argument_list|(
name|fd
argument_list|,
operator|-
literal|8
argument_list|,
name|SEEK_CUR
argument_list|)
expr_stmt|;
name|header
operator|.
name|header_size
operator|+=
literal|8
expr_stmt|;
comment|/*  spacing is not defined in version 1  */
name|header
operator|.
name|spacing
operator|=
literal|25
expr_stmt|;
block|}
comment|/*  Read in the brush name  */
if|if
condition|(
operator|(
name|bn_size
operator|=
operator|(
name|header
operator|.
name|header_size
operator|-
sizeof|sizeof
argument_list|(
name|header
argument_list|)
operator|)
operator|)
condition|)
block|{
name|name
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|bn_size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|read
argument_list|(
name|fd
argument_list|,
name|name
argument_list|,
name|bn_size
argument_list|)
operator|)
operator|<
name|bn_size
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parsing error:\n"
literal|"Brush file '%s' appears truncated."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Invalid UTF-8 string in brush file '%s'."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|name
operator|=
name|NULL
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|name
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|header
operator|.
name|bytes
condition|)
block|{
case|case
literal|1
case|:
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|brush
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
name|header
operator|.
name|width
argument_list|,
name|header
operator|.
name|height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
argument_list|,
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
argument_list|)
operator|<
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parsing error:\n"
literal|"Brush file '%s' appears truncated."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
break|break;
case|case
literal|4
case|:
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|brush
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
name|header
operator|.
name|width
argument_list|,
name|header
operator|.
name|height
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|brush
operator|->
name|pixmap
operator|=
name|temp_buf_new
argument_list|(
name|header
operator|.
name|width
argument_list|,
name|header
operator|.
name|height
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
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
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|read
argument_list|(
name|fd
argument_list|,
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|pixmap
argument_list|)
operator|+
name|i
operator|*
literal|3
argument_list|,
literal|3
argument_list|)
operator|!=
literal|3
operator|||
name|read
argument_list|(
name|fd
argument_list|,
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
operator|+
name|i
argument_list|,
literal|1
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Fatal parsing error:\n"
literal|"Brush file '%s' appears truncated."
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
break|break;
default|default:
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_READ
argument_list|,
name|_
argument_list|(
literal|"Unsupported brush depth %d\n"
literal|"in file '%s'.\n"
literal|"GIMP brushes must be GRAY or RGBA."
argument_list|)
argument_list|,
name|header
operator|.
name|bytes
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|brush
operator|->
name|spacing
operator|=
name|header
operator|.
name|spacing
expr_stmt|;
name|brush
operator|->
name|x_axis
operator|.
name|x
operator|=
name|header
operator|.
name|width
operator|/
literal|2.0
expr_stmt|;
name|brush
operator|->
name|x_axis
operator|.
name|y
operator|=
literal|0.0
expr_stmt|;
name|brush
operator|->
name|y_axis
operator|.
name|x
operator|=
literal|0.0
expr_stmt|;
name|brush
operator|->
name|y_axis
operator|.
name|y
operator|=
name|header
operator|.
name|height
operator|/
literal|2.0
expr_stmt|;
return|return
name|brush
return|;
block|}
end_function

end_unit

