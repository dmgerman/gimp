begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpcolor/gimpcolor.h"
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
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette-load.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette-save.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|1e-10
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_palette_finalize
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
name|gimp_palette_get_memsize
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
name|void
name|gimp_palette_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|popup
parameter_list|,
name|gboolean
name|dot_for_dot
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
name|gboolean
name|gimp_palette_get_popup_size
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
name|gimp_palette_get_new_preview
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
name|gimp_palette_get_description
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
name|gimp_palette_get_extension
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
name|gimp_palette_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_palette_entry_free
parameter_list|(
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_palette_entry_get_memsize
parameter_list|(
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPalette,gimp_palette,GIMP_TYPE_DATA)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPalette
argument_list|,
argument|gimp_palette
argument_list|,
argument|GIMP_TYPE_DATA
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_palette_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_palette_class_init
parameter_list|(
name|GimpPaletteClass
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
name|gimp_palette_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_palette_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gtk-select-color"
expr_stmt|;
name|viewable_class
operator|->
name|get_preview_size
operator|=
name|gimp_palette_get_preview_size
expr_stmt|;
name|viewable_class
operator|->
name|get_popup_size
operator|=
name|gimp_palette_get_popup_size
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_palette_get_new_preview
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_palette_get_description
expr_stmt|;
name|data_class
operator|->
name|save
operator|=
name|gimp_palette_save
expr_stmt|;
name|data_class
operator|->
name|get_extension
operator|=
name|gimp_palette_get_extension
expr_stmt|;
name|data_class
operator|->
name|duplicate
operator|=
name|gimp_palette_duplicate
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_init (GimpPalette * palette)
name|gimp_palette_init
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|)
block|{
name|palette
operator|->
name|colors
operator|=
name|NULL
expr_stmt|;
name|palette
operator|->
name|n_colors
operator|=
literal|0
expr_stmt|;
name|palette
operator|->
name|n_columns
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_finalize (GObject * object)
name|gimp_palette_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|palette
operator|->
name|colors
condition|)
block|{
name|g_list_foreach
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_palette_entry_free
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|palette
operator|->
name|colors
argument_list|)
expr_stmt|;
name|palette
operator|->
name|colors
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
DECL|function|gimp_palette_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_palette_get_memsize
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
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
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
name|gimp_g_list_get_memsize_foreach
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
operator|(
name|GimpMemsizeFunc
operator|)
name|gimp_palette_entry_get_memsize
argument_list|,
name|gui_size
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
name|void
DECL|function|gimp_palette_get_preview_size (GimpViewable * viewable,gint size,gboolean popup,gboolean dot_for_dot,gint * width,gint * height)
name|gimp_palette_get_preview_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|popup
parameter_list|,
name|gboolean
name|dot_for_dot
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
operator|*
name|width
operator|=
name|size
expr_stmt|;
operator|*
name|height
operator|=
literal|1
operator|+
name|size
operator|/
literal|2
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_palette_get_popup_size (GimpViewable * viewable,gint width,gint height,gboolean dot_for_dot,gint * popup_width,gint * popup_height)
name|gimp_palette_get_popup_size
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
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|gint
name|p_width
decl_stmt|;
name|gint
name|p_height
decl_stmt|;
if|if
condition|(
operator|!
name|palette
operator|->
name|n_colors
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|palette
operator|->
name|n_columns
condition|)
name|p_width
operator|=
name|palette
operator|->
name|n_columns
expr_stmt|;
else|else
name|p_width
operator|=
name|MIN
argument_list|(
name|palette
operator|->
name|n_colors
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|p_height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|palette
operator|->
name|n_colors
operator|/
name|p_width
argument_list|)
expr_stmt|;
if|if
condition|(
name|p_width
operator|*
literal|4
operator|>
name|width
operator|||
name|p_height
operator|*
literal|4
operator|>
name|height
condition|)
block|{
operator|*
name|popup_width
operator|=
name|p_width
operator|*
literal|4
expr_stmt|;
operator|*
name|popup_height
operator|=
name|p_height
operator|*
literal|4
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
DECL|function|gimp_palette_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_palette_get_new_preview
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
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|guchar
modifier|*
name|buf
decl_stmt|;
name|guchar
modifier|*
name|b
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|guchar
name|white
index|[
literal|3
index|]
init|=
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|}
decl_stmt|;
name|gint
name|columns
decl_stmt|;
name|gint
name|rows
decl_stmt|;
name|gint
name|cell_size
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|white
argument_list|)
expr_stmt|;
if|if
condition|(
name|palette
operator|->
name|n_columns
operator|>
literal|1
condition|)
name|cell_size
operator|=
name|MAX
argument_list|(
literal|4
argument_list|,
name|width
operator|/
name|palette
operator|->
name|n_columns
argument_list|)
expr_stmt|;
else|else
name|cell_size
operator|=
literal|4
expr_stmt|;
name|columns
operator|=
name|width
operator|/
name|cell_size
expr_stmt|;
name|rows
operator|=
name|height
operator|/
name|cell_size
expr_stmt|;
name|buf
operator|=
name|temp_buf_data
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|b
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|list
operator|=
name|palette
operator|->
name|colors
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|rows
operator|&&
name|list
condition|;
name|y
operator|++
control|)
block|{
name|gint
name|i
decl_stmt|;
name|memset
argument_list|(
name|b
argument_list|,
literal|255
argument_list|,
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|columns
operator|&&
name|list
condition|;
name|x
operator|++
control|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|entry
operator|->
name|color
argument_list|,
operator|&
name|b
index|[
name|x
operator|*
name|cell_size
operator|*
literal|3
operator|+
literal|0
index|]
argument_list|,
operator|&
name|b
index|[
name|x
operator|*
name|cell_size
operator|*
literal|3
operator|+
literal|1
index|]
argument_list|,
operator|&
name|b
index|[
name|x
operator|*
name|cell_size
operator|*
literal|3
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|cell_size
condition|;
name|i
operator|++
control|)
block|{
name|b
index|[
operator|(
name|x
operator|*
name|cell_size
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
name|b
index|[
operator|(
name|x
operator|*
name|cell_size
operator|)
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
name|b
index|[
operator|(
name|x
operator|*
name|cell_size
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|b
index|[
operator|(
name|x
operator|*
name|cell_size
operator|)
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|b
index|[
operator|(
name|x
operator|*
name|cell_size
operator|+
name|i
operator|)
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
name|b
index|[
operator|(
name|x
operator|*
name|cell_size
operator|)
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
block|}
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cell_size
condition|;
name|i
operator|++
control|)
name|memcpy
argument_list|(
name|buf
operator|+
operator|(
operator|(
name|y
operator|*
name|cell_size
operator|+
name|i
operator|)
operator|*
name|width
operator|)
operator|*
literal|3
argument_list|,
name|b
argument_list|,
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|b
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
DECL|function|gimp_palette_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_palette_get_description
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
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s (%d)"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|palette
argument_list|)
operator|->
name|name
argument_list|,
name|palette
operator|->
name|n_colors
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_palette_new (const gchar * name)
name|gimp_palette_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|*
name|name
operator|!=
literal|'\0'
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_palette_get_standard (void)
name|gimp_palette_get_standard
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpData
modifier|*
name|standard_palette
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|standard_palette
condition|)
block|{
name|standard_palette
operator|=
name|gimp_palette_new
argument_list|(
literal|"Standard"
argument_list|)
expr_stmt|;
name|standard_palette
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|standard_palette
argument_list|,
literal|"gimp-palette-standard"
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|standard_palette
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_palette
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_palette_get_extension (GimpData * data)
name|gimp_palette_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|GIMP_PALETTE_FILE_EXTENSION
return|;
block|}
end_function

begin_function
specifier|static
name|GimpData
modifier|*
DECL|function|gimp_palette_duplicate (GimpData * data)
name|gimp_palette_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpPalette
modifier|*
name|new
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|new
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new
operator|->
name|n_columns
operator|=
name|palette
operator|->
name|n_columns
expr_stmt|;
for|for
control|(
name|list
operator|=
name|palette
operator|->
name|colors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|new
argument_list|,
operator|-
literal|1
argument_list|,
name|entry
operator|->
name|name
argument_list|,
operator|&
name|entry
operator|->
name|color
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_DATA
argument_list|(
name|new
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPaletteEntry
modifier|*
DECL|function|gimp_palette_add_entry (GimpPalette * palette,gint position,const gchar * name,const GimpRGB * color)
name|gimp_palette_add_entry
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|gint
name|position
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|=
name|g_slice_new0
argument_list|(
name|GimpPaletteEntry
argument_list|)
expr_stmt|;
name|entry
operator|->
name|color
operator|=
operator|*
name|color
expr_stmt|;
name|entry
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
condition|?
name|name
else|:
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|position
operator|<
literal|0
operator|||
name|position
operator|>=
name|palette
operator|->
name|n_colors
condition|)
block|{
name|entry
operator|->
name|position
operator|=
name|palette
operator|->
name|n_colors
expr_stmt|;
name|palette
operator|->
name|colors
operator|=
name|g_list_append
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|entry
operator|->
name|position
operator|=
name|position
expr_stmt|;
name|palette
operator|->
name|colors
operator|=
name|g_list_insert
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|entry
argument_list|,
name|position
argument_list|)
expr_stmt|;
comment|/* renumber the displaced entries */
for|for
control|(
name|list
operator|=
name|g_list_nth
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|position
operator|+
literal|1
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry2
init|=
name|list
operator|->
name|data
decl_stmt|;
name|entry2
operator|->
name|position
operator|+=
literal|1
expr_stmt|;
block|}
block|}
name|palette
operator|->
name|n_colors
operator|+=
literal|1
expr_stmt|;
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|entry
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_palette_delete_entry (GimpPalette * palette,GimpPaletteEntry * entry)
name|gimp_palette_delete_entry
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|pos
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|entry
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_list_find
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|entry
argument_list|)
condition|)
block|{
name|pos
operator|=
name|entry
operator|->
name|position
expr_stmt|;
name|gimp_palette_entry_free
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|palette
operator|->
name|colors
operator|=
name|g_list_remove
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|palette
operator|->
name|n_colors
operator|--
expr_stmt|;
for|for
control|(
name|list
operator|=
name|g_list_nth
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|pos
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|entry
operator|->
name|position
operator|=
name|pos
operator|++
expr_stmt|;
block|}
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_palette_set_columns (GimpPalette * palette,gint columns)
name|gimp_palette_set_columns
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|gint
name|columns
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|columns
operator|=
name|CLAMP
argument_list|(
name|columns
argument_list|,
literal|0
argument_list|,
literal|64
argument_list|)
expr_stmt|;
if|if
condition|(
name|palette
operator|->
name|n_columns
operator|!=
name|columns
condition|)
block|{
name|palette
operator|->
name|n_columns
operator|=
name|columns
expr_stmt|;
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gimp_palette_get_columns (GimpPalette * palette)
name|gimp_palette_get_columns
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|palette
operator|->
name|n_columns
return|;
block|}
end_function

begin_function
name|GimpPaletteEntry
modifier|*
DECL|function|gimp_palette_find_entry (GimpPalette * palette,const GimpRGB * color,GimpPaletteEntry * start_from)
name|gimp_palette_find_entry
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpPaletteEntry
modifier|*
name|start_from
parameter_list|)
block|{
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|start_from
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
comment|/* search from the start */
for|for
control|(
name|list
operator|=
name|palette
operator|->
name|colors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gimp_rgb_distance
argument_list|(
operator|&
name|entry
operator|->
name|color
argument_list|,
name|color
argument_list|)
operator|<
name|EPSILON
condition|)
return|return
name|entry
return|;
block|}
block|}
elseif|else
if|if
condition|(
name|gimp_rgb_distance
argument_list|(
operator|&
name|start_from
operator|->
name|color
argument_list|,
name|color
argument_list|)
operator|<
name|EPSILON
condition|)
block|{
return|return
name|start_from
return|;
block|}
else|else
block|{
name|GList
modifier|*
name|old
init|=
name|g_list_find
argument_list|(
name|palette
operator|->
name|colors
argument_list|,
name|start_from
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|next
decl_stmt|;
name|GList
modifier|*
name|prev
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|old
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|next
operator|=
name|old
operator|->
name|next
expr_stmt|;
name|prev
operator|=
name|old
operator|->
name|prev
expr_stmt|;
comment|/* proximity-based search */
while|while
condition|(
name|next
operator|||
name|prev
condition|)
block|{
if|if
condition|(
name|next
condition|)
block|{
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|next
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gimp_rgb_distance
argument_list|(
operator|&
name|entry
operator|->
name|color
argument_list|,
name|color
argument_list|)
operator|<
name|EPSILON
condition|)
return|return
name|entry
return|;
name|next
operator|=
name|next
operator|->
name|next
expr_stmt|;
block|}
if|if
condition|(
name|prev
condition|)
block|{
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|prev
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gimp_rgb_distance
argument_list|(
operator|&
name|entry
operator|->
name|color
argument_list|,
name|color
argument_list|)
operator|<
name|EPSILON
condition|)
return|return
name|entry
return|;
name|prev
operator|=
name|prev
operator|->
name|prev
expr_stmt|;
block|}
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_palette_entry_free (GimpPaletteEntry * entry)
name|gimp_palette_entry_free
parameter_list|(
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|entry
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entry
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpPaletteEntry
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|gimp_palette_entry_get_memsize (GimpPaletteEntry * entry,gint64 * gui_size)
name|gimp_palette_entry_get_memsize
parameter_list|(
name|GimpPaletteEntry
modifier|*
name|entry
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|gint64
name|memsize
init|=
sizeof|sizeof
argument_list|(
name|GimpPaletteEntry
argument_list|)
decl_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|entry
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|memsize
return|;
block|}
end_function

end_unit

