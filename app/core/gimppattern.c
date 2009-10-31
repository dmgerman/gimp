begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<glib-object.h>
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
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern-load.h"
end_include

begin_include
include|#
directive|include
file|"gimptagged.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_pattern_tagged_iface_init
parameter_list|(
name|GimpTaggedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pattern_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_pattern_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_pattern_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_pattern_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
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
name|gimp_pattern_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_pattern_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpData
modifier|*
name|gimp_pattern_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_pattern_get_checksum
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpPattern,gimp_pattern,GIMP_TYPE_DATA,G_IMPLEMENT_INTERFACE (GIMP_TYPE_TAGGED,gimp_pattern_tagged_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpPattern
argument_list|,
argument|gimp_pattern
argument_list|,
argument|GIMP_TYPE_DATA
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_TAGGED,                                                 gimp_pattern_tagged_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_pattern_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_pattern_class_init
parameter_list|(
name|GimpPatternClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpDataClass
modifier|*
name|data_class
init|=
name|GIMP_DATA_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_pattern_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_pattern_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gimp-tool-bucket-fill"
expr_stmt|;
name|viewable_class
operator|->
name|get_size
operator|=
name|gimp_pattern_get_size
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_pattern_get_new_preview
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_pattern_get_description
expr_stmt|;
name|data_class
operator|->
name|get_extension
operator|=
name|gimp_pattern_get_extension
expr_stmt|;
name|data_class
operator|->
name|duplicate
operator|=
name|gimp_pattern_duplicate
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_tagged_iface_init (GimpTaggedInterface * iface)
name|gimp_pattern_tagged_iface_init
parameter_list|(
name|GimpTaggedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|get_checksum
operator|=
name|gimp_pattern_get_checksum
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_init (GimpPattern * pattern)
name|gimp_pattern_init
parameter_list|(
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
block|{
name|pattern
operator|->
name|mask
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pattern_finalize (GObject * object)
name|gimp_pattern_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|pattern
operator|->
name|mask
condition|)
block|{
name|temp_buf_free
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|mask
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
name|gint64
DECL|function|gimp_pattern_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_pattern_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|temp_buf_get_memsize
argument_list|(
name|pattern
operator|->
name|mask
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
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_pattern_get_size (GimpViewable * viewable,gint * width,gint * height)
name|gimp_pattern_get_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
operator|*
name|width
operator|=
name|pattern
operator|->
name|mask
operator|->
name|width
expr_stmt|;
operator|*
name|height
operator|=
name|pattern
operator|->
name|mask
operator|->
name|height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_pattern_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_pattern_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|gint
name|copy_width
decl_stmt|;
name|gint
name|copy_height
decl_stmt|;
name|copy_width
operator|=
name|MIN
argument_list|(
name|width
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|)
expr_stmt|;
name|copy_height
operator|=
name|MIN
argument_list|(
name|height
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|)
expr_stmt|;
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|copy_width
argument_list|,
name|copy_height
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|temp_buf_copy_area
argument_list|(
name|pattern
operator|->
name|mask
argument_list|,
name|temp_buf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|copy_width
argument_list|,
name|copy_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|temp_buf
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_pattern_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_pattern_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%d Ã %d)"
argument_list|,
name|gimp_object_get_name
argument_list|(
name|pattern
argument_list|)
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|width
argument_list|,
name|pattern
operator|->
name|mask
operator|->
name|height
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_pattern_get_extension (GimpData * data)
name|gimp_pattern_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|GIMP_PATTERN_FILE_EXTENSION
return|;
block|}
end_function

begin_function
specifier|static
name|GimpData
modifier|*
DECL|function|gimp_pattern_duplicate (GimpData * data)
name|gimp_pattern_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|temp_buf_copy
argument_list|(
name|GIMP_PATTERN
argument_list|(
name|data
argument_list|)
operator|->
name|mask
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_DATA
argument_list|(
name|pattern
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_pattern_get_checksum (GimpTagged * tagged)
name|gimp_pattern_get_checksum
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
name|GIMP_PATTERN
argument_list|(
name|tagged
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|checksum_string
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|pattern
operator|->
name|mask
condition|)
block|{
name|GChecksum
modifier|*
name|checksum
init|=
name|g_checksum_new
argument_list|(
name|G_CHECKSUM_MD5
argument_list|)
decl_stmt|;
name|g_checksum_update
argument_list|(
name|checksum
argument_list|,
name|temp_buf_get_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
argument_list|,
name|temp_buf_get_data_size
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
argument_list|)
expr_stmt|;
name|checksum_string
operator|=
name|g_strdup
argument_list|(
name|g_checksum_get_string
argument_list|(
name|checksum
argument_list|)
argument_list|)
expr_stmt|;
name|g_checksum_free
argument_list|(
name|checksum
argument_list|)
expr_stmt|;
block|}
return|return
name|checksum_string
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_pattern_new (const gchar * name)
name|gimp_pattern_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
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
name|pattern
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pattern
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
literal|32
argument_list|,
literal|32
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
name|data
operator|=
name|temp_buf_get_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|pattern
operator|->
name|mask
operator|->
name|height
condition|;
name|row
operator|++
control|)
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|pattern
operator|->
name|mask
operator|->
name|width
condition|;
name|col
operator|++
control|)
block|{
name|memset
argument_list|(
name|data
argument_list|,
operator|(
name|col
operator|%
literal|2
operator|)
operator|&&
operator|(
name|row
operator|%
literal|2
operator|)
condition|?
literal|255
else|:
literal|0
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|data
operator|+=
literal|3
expr_stmt|;
block|}
return|return
name|GIMP_DATA
argument_list|(
name|pattern
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_pattern_get_standard (void)
name|gimp_pattern_get_standard
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpData
modifier|*
name|standard_pattern
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_pattern
condition|)
block|{
name|standard_pattern
operator|=
name|gimp_pattern_new
argument_list|(
literal|"Standard"
argument_list|)
expr_stmt|;
name|gimp_data_clean
argument_list|(
name|standard_pattern
argument_list|)
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|standard_pattern
argument_list|,
literal|"gimp-pattern-standard"
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|standard_pattern
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_pattern
return|;
block|}
end_function

begin_function
name|TempBuf
modifier|*
DECL|function|gimp_pattern_get_mask (const GimpPattern * pattern)
name|gimp_pattern_get_mask
parameter_list|(
specifier|const
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PATTERN
argument_list|(
name|pattern
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|pattern
operator|->
name|mask
return|;
block|}
end_function

end_unit

