begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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
file|"brush_header.h"
end_include

begin_enum
DECL|enum|__anon28a17e0d0103
enum|enum
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
if|if
condition|(
name|brush
operator|->
name|filename
condition|)
name|g_free
argument_list|(
name|brush
operator|->
name|filename
argument_list|)
expr_stmt|;
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
name|gimp_brush_signals
index|[
name|DIRTY
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"dirty"
argument_list|,
literal|0
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
literal|0
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
name|mask
operator|=
name|NULL
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
DECL|function|gimp_brush_get_type (void)
name|GtkType
name|gimp_brush_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
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
name|NULL
block|,
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
DECL|function|gimp_brush_new (char * filename)
name|gimp_brush_new
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
init|=
name|GIMP_BRUSH
argument_list|(
name|gtk_type_new
argument_list|(
name|gimp_brush_get_type
argument_list|()
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_brush_load
argument_list|(
name|brush
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|brush
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
name|char
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
DECL|function|gimp_brush_set_name (GimpBrush * brush,char * name)
name|gimp_brush_set_name
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|char
modifier|*
name|name
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
name|void
DECL|function|gimp_brush_load (GimpBrush * brush,char * filename)
name|gimp_brush_load
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|FILE
modifier|*
name|fp
decl_stmt|;
name|int
name|bn_size
decl_stmt|;
name|unsigned
name|char
name|buf
index|[
name|sz_BrushHeader
index|]
decl_stmt|;
name|BrushHeader
name|header
decl_stmt|;
name|unsigned
name|int
modifier|*
name|hp
decl_stmt|;
name|int
name|i
decl_stmt|;
name|brush
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
comment|/*  Open the requested file  */
if|if
condition|(
operator|!
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
operator|)
condition|)
block|{
name|gimp_object_destroy
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  Read in the header size  */
if|if
condition|(
operator|(
name|fread
argument_list|(
name|buf
argument_list|,
literal|1
argument_list|,
name|sz_BrushHeader
argument_list|,
name|fp
argument_list|)
operator|)
operator|<
name|sz_BrushHeader
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_object_destroy
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  rearrange the bytes in each unsigned int  */
name|hp
operator|=
operator|(
name|unsigned
name|int
operator|*
operator|)
operator|&
name|header
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|(
name|sz_BrushHeader
operator|/
literal|4
operator|)
condition|;
name|i
operator|++
control|)
name|hp
index|[
name|i
index|]
operator|=
operator|(
name|buf
index|[
name|i
operator|*
literal|4
index|]
operator|<<
literal|24
operator|)
operator|+
operator|(
name|buf
index|[
name|i
operator|*
literal|4
operator|+
literal|1
index|]
operator|<<
literal|16
operator|)
operator|+
operator|(
name|buf
index|[
name|i
operator|*
literal|4
operator|+
literal|2
index|]
operator|<<
literal|8
operator|)
operator|+
operator|(
name|buf
index|[
name|i
operator|*
literal|4
operator|+
literal|3
index|]
operator|)
expr_stmt|;
comment|/*  Check for correct file format */
if|if
condition|(
name|header
operator|.
name|magic_number
operator|!=
name|GBRUSH_MAGIC
condition|)
block|{
comment|/*  One thing that can save this error is if the brush is version 1  */
if|if
condition|(
name|header
operator|.
name|version
operator|!=
literal|1
condition|)
block|{
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_object_destroy
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return;
block|}
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
name|fseek
argument_list|(
name|fp
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
name|sz_BrushHeader
operator|)
operator|)
condition|)
block|{
name|brush
operator|->
name|name
operator|=
operator|(
name|char
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
argument_list|)
operator|*
name|bn_size
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|fread
argument_list|(
name|brush
operator|->
name|name
argument_list|,
literal|1
argument_list|,
name|bn_size
argument_list|,
name|fp
argument_list|)
operator|)
operator|<
name|bn_size
condition|)
block|{
name|g_message
argument_list|(
literal|"Error in GIMP brush file...aborting."
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_object_destroy
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
else|else
name|brush
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
literal|"Unnamed"
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|header
operator|.
name|version
condition|)
block|{
case|case
literal|1
case|:
case|case
literal|2
case|:
comment|/*  Get a new brush mask  */
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
name|header
operator|.
name|bytes
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
name|spacing
operator|=
name|header
operator|.
name|spacing
expr_stmt|;
comment|/* set up spacing axis */
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
comment|/*  Read the brush mask data  */
if|if
condition|(
operator|(
name|fread
argument_list|(
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
argument_list|,
literal|1
argument_list|,
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
argument_list|,
name|fp
argument_list|)
operator|)
operator|<
name|header
operator|.
name|width
operator|*
name|header
operator|.
name|height
condition|)
name|g_message
argument_list|(
literal|"GIMP brush file appears to be truncated."
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
literal|"Unknown brush format version #%d in \"%s\"\n"
argument_list|,
name|header
operator|.
name|version
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_object_destroy
argument_list|(
name|brush
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  Clean up  */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
comment|/*  Swap the brush to disk (if we're being stingy with memory) */
if|if
condition|(
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
comment|/* Check if the current brush is the default one */
comment|/* lets see if it works with out this for now */
comment|/*  if (strcmp(default_brush, prune_filename(filename)) == 0) { 	  active_brush = brush; 	  have_default_brush = 1;   }*/
comment|/* if */
block|}
end_function

end_unit

