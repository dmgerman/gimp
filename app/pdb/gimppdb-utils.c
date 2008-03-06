begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimppdberror.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_pdb_get_brush (Gimp * gimp,const gchar * name,gboolean writable,GError ** error)
name|gimp_pdb_get_brush
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|writable
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
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
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Invalid empty brush name"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|brush
operator|=
operator|(
name|GimpBrush
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|brush
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Brush '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|writable
operator|&&
operator|!
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
operator|->
name|writable
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Brush '%s' is not editable"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|brush
return|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_pdb_get_generated_brush (Gimp * gimp,const gchar * name,gboolean writable,GError ** error)
name|gimp_pdb_get_generated_brush
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|writable
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
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
name|brush
operator|=
name|gimp_pdb_get_brush
argument_list|(
name|gimp
argument_list|,
name|name
argument_list|,
name|writable
argument_list|,
name|error
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
if|if
condition|(
operator|!
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Brush '%s' is not a generated brush"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|brush
return|;
block|}
end_function

begin_function
name|GimpPattern
modifier|*
DECL|function|gimp_pdb_get_pattern (Gimp * gimp,const gchar * name,GError ** error)
name|gimp_pdb_get_pattern
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
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
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Invalid empty pattern name"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|pattern
operator|=
operator|(
name|GimpPattern
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pattern
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Pattern '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|pattern
return|;
block|}
end_function

begin_function
name|GimpGradient
modifier|*
DECL|function|gimp_pdb_get_gradient (Gimp * gimp,const gchar * name,gboolean writable,GError ** error)
name|gimp_pdb_get_gradient
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|writable
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
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
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Invalid empty gradient name"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|gradient
operator|=
operator|(
name|GimpGradient
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gradient
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Gradient '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|writable
operator|&&
operator|!
name|GIMP_DATA
argument_list|(
name|gradient
argument_list|)
operator|->
name|writable
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Gradient '%s' is not editable"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|gradient
return|;
block|}
end_function

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_pdb_get_palette (Gimp * gimp,const gchar * name,gboolean writable,GError ** error)
name|gimp_pdb_get_palette
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|writable
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
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
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Invalid empty palette name"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|palette
operator|=
operator|(
name|GimpPalette
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|palette_factory
operator|->
name|container
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|palette
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Palette '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|writable
operator|&&
operator|!
name|GIMP_DATA
argument_list|(
name|palette
argument_list|)
operator|->
name|writable
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Palette '%s' is not editable"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|palette
return|;
block|}
end_function

begin_function
name|GimpFont
modifier|*
DECL|function|gimp_pdb_get_font (Gimp * gimp,const gchar * name,GError ** error)
name|gimp_pdb_get_font
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpFont
modifier|*
name|font
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
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
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Invalid empty font name"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|font
operator|=
operator|(
name|GimpFont
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|fonts
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Font '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|font
return|;
block|}
end_function

begin_function
name|GimpBuffer
modifier|*
DECL|function|gimp_pdb_get_buffer (Gimp * gimp,const gchar * name,GError ** error)
name|gimp_pdb_get_buffer
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
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
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Invalid empty buffer name"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|buffer
operator|=
operator|(
name|GimpBuffer
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|named_buffers
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|buffer
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Named buffer '%s' not found"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|buffer
return|;
block|}
end_function

begin_function
name|GimpPaintInfo
modifier|*
DECL|function|gimp_pdb_get_paint_info (Gimp * gimp,const gchar * name,GError ** error)
name|gimp_pdb_get_paint_info
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
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
if|if
condition|(
operator|!
name|name
operator|||
operator|!
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Invalid empty paint method name"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|paint_info
operator|=
operator|(
name|GimpPaintInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paint_info
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Paint method '%s' does not exist"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|paint_info
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_pdb_item_is_attached (GimpItem * item,GError ** error)
name|gimp_pdb_item_is_attached
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|,
name|FALSE
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
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_item_is_attached
argument_list|(
name|item
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Item '%s' (%d) cannot be used because it has not "
literal|"been added to an image"
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|)
argument_list|,
name|gimp_item_get_ID
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|GimpStroke
modifier|*
DECL|function|gimp_pdb_get_vectors_stroke (GimpVectors * vectors,gint stroke_ID,GError ** error)
name|gimp_pdb_get_vectors_stroke
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|gint
name|stroke_ID
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
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
name|stroke
operator|=
name|gimp_vectors_stroke_get_by_ID
argument_list|(
name|vectors
argument_list|,
name|stroke_ID
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|stroke
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_PDB_ERROR
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|_
argument_list|(
literal|"Vectors object %d does not contain stroke with ID %d"
argument_list|)
argument_list|,
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|)
argument_list|,
name|stroke_ID
argument_list|)
expr_stmt|;
block|}
return|return
name|stroke
return|;
block|}
end_function

end_unit

