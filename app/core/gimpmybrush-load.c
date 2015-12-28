begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmybrush-load.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<mypaint-brush.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrush-load.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrush-private.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_mybrush_load (GimpContext * context,GFile * file,GInputStream * input,GError ** error)
name|gimp_mybrush_load
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|GInputStream
modifier|*
name|input
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpMybrush
modifier|*
name|brush
init|=
name|NULL
decl_stmt|;
name|MyPaintBrush
modifier|*
name|mypaint_brush
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|GFileInfo
modifier|*
name|info
decl_stmt|;
name|guint64
name|size
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|preview_filename
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_FILE
argument_list|(
name|file
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|G_IS_INPUT_STREAM
argument_list|(
name|input
argument_list|)
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
name|info
operator|=
name|g_file_query_info
argument_list|(
name|file
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_SIZE
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|info
condition|)
return|return
name|NULL
return|;
name|size
operator|=
name|g_file_info_get_attribute_uint64
argument_list|(
name|info
argument_list|,
name|G_FILE_ATTRIBUTE_STANDARD_SIZE
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|>
literal|32768
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
literal|"MyPaint brush file is unreasonably large, skipping."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|buffer
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|size
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_input_stream_read_all
argument_list|(
name|input
argument_list|,
name|buffer
argument_list|,
name|size
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|mypaint_brush
operator|=
name|mypaint_brush_new
argument_list|()
expr_stmt|;
name|mypaint_brush_from_defaults
argument_list|(
name|mypaint_brush
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mypaint_brush_from_string
argument_list|(
name|mypaint_brush
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|buffer
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
literal|"Failed to deserialize MyPaint brush."
argument_list|)
argument_list|)
expr_stmt|;
name|mypaint_brush_unref
argument_list|(
name|mypaint_brush
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|path
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_strndup
argument_list|(
name|path
argument_list|,
name|strlen
argument_list|(
name|path
argument_list|)
operator|-
literal|4
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|preview_filename
operator|=
name|g_strconcat
argument_list|(
name|basename
argument_list|,
literal|"_prev.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_file_at_size
argument_list|(
name|preview_filename
argument_list|,
literal|48
argument_list|,
literal|48
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|preview_filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
block|{
name|mypaint_brush_unref
argument_list|(
name|mypaint_brush
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|basename
operator|=
name|g_file_get_basename
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|brush
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_MYBRUSH
argument_list|,
literal|"name"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|basename
argument_list|)
argument_list|,
literal|"mime-type"
argument_list|,
literal|"image/x-gimp-myb"
argument_list|,
literal|"icon-pixbuf"
argument_list|,
name|pixbuf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|brush
operator|->
name|priv
operator|->
name|brush_json
operator|=
operator|(
name|gchar
operator|*
operator|)
name|buffer
expr_stmt|;
name|brush
operator|->
name|priv
operator|->
name|radius
operator|=
name|mypaint_brush_get_base_value
argument_list|(
name|mypaint_brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC
argument_list|)
expr_stmt|;
name|brush
operator|->
name|priv
operator|->
name|opaque
operator|=
name|mypaint_brush_get_base_value
argument_list|(
name|mypaint_brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_OPAQUE
argument_list|)
expr_stmt|;
name|brush
operator|->
name|priv
operator|->
name|hardness
operator|=
name|mypaint_brush_get_base_value
argument_list|(
name|mypaint_brush
argument_list|,
name|MYPAINT_BRUSH_SETTING_HARDNESS
argument_list|)
expr_stmt|;
name|mypaint_brush_unref
argument_list|(
name|mypaint_brush
argument_list|)
expr_stmt|;
return|return
name|g_list_prepend
argument_list|(
name|NULL
argument_list|,
name|brush
argument_list|)
return|;
block|}
end_function

end_unit

