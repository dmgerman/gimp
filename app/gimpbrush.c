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

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"brush_header.h"
end_include

begin_include
include|#
directive|include
file|"patterns.h"
end_include

begin_include
include|#
directive|include
file|"pattern_header.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushlist.h"
end_include

begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2ad746640103
block|{
DECL|enumerator|DIRTY
name|DIRTY
block|,
DECL|enumerator|RENAME
name|RENAME
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GimpBrush
modifier|*
name|gimp_brush_select_brush
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_want_null_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_brush_signals
specifier|static
name|guint
name|gimp_brush_signals
index|[
name|LAST_SIGNAL
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_brush_destroy (GtkObject * object)
name|gimp_brush_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|brush
operator|->
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|brush
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|mask
condition|)
name|temp_buf_free
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkType
name|type
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gimp_object_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|type
operator|=
name|object_class
operator|->
name|type
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_brush_destroy
expr_stmt|;
name|klass
operator|->
name|select_brush
operator|=
name|gimp_brush_select_brush
expr_stmt|;
name|klass
operator|->
name|want_null_motion
operator|=
name|gimp_brush_want_null_motion
expr_stmt|;
name|gimp_brush_signals
index|[
name|DIRTY
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"dirty"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|type
argument_list|,
literal|0
argument_list|,
name|gimp_sigtype_void
argument_list|)
expr_stmt|;
name|gimp_brush_signals
index|[
name|RENAME
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"rename"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|type
argument_list|,
literal|0
argument_list|,
name|gimp_sigtype_void
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_brush_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
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
name|filename
operator|=
name|NULL
expr_stmt|;
name|brush
operator|->
name|name
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
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_brush_get_type (void)
name|gimp_brush_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GtkTypeInfo
name|info
init|=
block|{
literal|"GimpBrush"
block|,
sizeof|sizeof
argument_list|(
name|GimpBrush
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_brush_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_brush_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|gimp_object_get_type
argument_list|()
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_load (gchar * filename)
name|gimp_brush_load
parameter_list|(
name|gchar
modifier|*
name|filename
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
return|return
name|NULL
return|;
name|brush
operator|=
name|gimp_brush_load_brush
argument_list|(
name|fd
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|close
argument_list|(
name|fd
argument_list|)
expr_stmt|;
name|brush
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
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
return|return
name|brush
return|;
block|}
end_function

begin_function
specifier|static
name|GimpBrush
modifier|*
DECL|function|gimp_brush_select_brush (PaintCore * paint_core)
name|gimp_brush_select_brush
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|)
block|{
return|return
name|paint_core
operator|->
name|brush
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_want_null_motion (PaintCore * paint_core)
name|gimp_brush_want_null_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
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
DECL|function|gimp_brush_get_mask (GimpBrush * brush)
name|gimp_brush_get_mask
parameter_list|(
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
DECL|function|gimp_brush_get_pixmap (GimpBrush * brush)
name|gimp_brush_get_pixmap
parameter_list|(
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
name|gchar
modifier|*
DECL|function|gimp_brush_get_name (GimpBrush * brush)
name|gimp_brush_get_name
parameter_list|(
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
name|name
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_set_name (GimpBrush * brush,gchar * name)
name|gimp_brush_set_name
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|brush
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
name|strcmp
argument_list|(
name|brush
operator|->
name|name
argument_list|,
name|name
argument_list|)
operator|==
literal|0
condition|)
return|return;
if|if
condition|(
name|brush
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|brush
operator|->
name|name
argument_list|)
expr_stmt|;
name|brush
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
name|gimp_brush_signals
index|[
name|RENAME
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_brush_get_spacing (GimpBrush * brush)
name|gimp_brush_get_spacing
parameter_list|(
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
literal|0
argument_list|)
expr_stmt|;
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
name|brush
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|brush
operator|->
name|spacing
operator|=
name|spacing
expr_stmt|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_load_brush (gint fd,gchar * filename)
name|gimp_brush_load_brush
parameter_list|(
name|gint
name|fd
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|GPattern
modifier|*
name|pattern
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
return|return
name|NULL
return|;
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unknown brush format version #%d in \"%s\"."
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error in GIMP brush file \"%s\"."
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
block|}
else|else
block|{
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
block|}
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
name|gtk_type_new
argument_list|(
name|gimp_brush_get_type
argument_list|()
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"GIMP brush file appears to be truncated: \"%s\"."
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
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
comment|/*  For backwards-compatibility, check if a pattern follows. 	  The obsolete .gpb format did it this way.  */
name|pattern
operator|=
name|pattern_load
argument_list|(
name|fd
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|pattern
condition|)
block|{
if|if
condition|(
name|pattern
operator|->
name|mask
operator|&&
name|pattern
operator|->
name|mask
operator|->
name|bytes
operator|==
literal|3
condition|)
block|{
name|brush
operator|->
name|pixmap
operator|=
name|pattern
operator|->
name|mask
expr_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
block|}
name|pattern_free
argument_list|(
name|pattern
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  rewind to make brush pipe loader happy  */
if|if
condition|(
name|lseek
argument_list|(
name|fd
argument_list|,
operator|-
operator|(
operator|(
name|off_t
operator|)
sizeof|sizeof
argument_list|(
name|PatternHeader
argument_list|)
operator|)
argument_list|,
name|SEEK_CUR
argument_list|)
operator|<
literal|0
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"GIMP brush file appears to be corrupted: \"%s\"."
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
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
break|break;
case|case
literal|4
case|:
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|gtk_type_new
argument_list|(
name|gimp_brush_get_type
argument_list|()
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
name|g_message
argument_list|(
name|_
argument_list|(
literal|"GIMP brush file appears to be truncated: \"%s\"."
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
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
break|break;
default|default:
name|g_message
argument_list|(
literal|"Unsupported brush depth: %d\n in file \"%s\"\nGIMP Brushes must be GRAY or RGBA\n"
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
name|brush
operator|->
name|name
operator|=
name|name
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

