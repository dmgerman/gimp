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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatalist.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"palette_select.h"
end_include

begin_include
include|#
directive|include
file|"palettes.h"
end_include

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|global_palette_list
name|GimpContainer
modifier|*
name|global_palette_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|palettes_init (gboolean no_data)
name|palettes_init
parameter_list|(
name|gboolean
name|no_data
parameter_list|)
block|{
if|if
condition|(
name|global_palette_list
condition|)
name|palettes_free
argument_list|()
expr_stmt|;
else|else
name|global_palette_list
operator|=
name|GIMP_CONTAINER
argument_list|(
name|gimp_data_list_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|palette_path
operator|!=
name|NULL
operator|&&
operator|!
name|no_data
condition|)
block|{
name|palette_select_freeze_all
argument_list|()
expr_stmt|;
name|gimp_data_list_load
argument_list|(
name|GIMP_DATA_LIST
argument_list|(
name|global_palette_list
argument_list|)
argument_list|,
name|palette_path
argument_list|,
operator|(
name|GimpDataObjectLoaderFunc
operator|)
name|gimp_palette_load
argument_list|,
name|GIMP_PALETTE_FILE_EXTENSION
argument_list|,
operator|(
name|GimpDataObjectLoaderFunc
operator|)
name|gimp_palette_load
argument_list|,
name|NULL
comment|/* legacy loader */
argument_list|)
expr_stmt|;
name|palette_select_thaw_all
argument_list|()
expr_stmt|;
block|}
name|gimp_context_refresh_palettes
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palettes_free (void)
name|palettes_free
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|global_palette_list
condition|)
return|return;
name|palette_select_freeze_all
argument_list|()
expr_stmt|;
name|gimp_data_list_save_and_clear
argument_list|(
name|GIMP_DATA_LIST
argument_list|(
name|global_palette_list
argument_list|)
argument_list|,
name|palette_path
argument_list|,
name|GIMP_PALETTE_FILE_EXTENSION
argument_list|)
expr_stmt|;
name|palette_select_thaw_all
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|GimpPalette
modifier|*
DECL|function|palettes_get_standard_palette (void)
name|palettes_get_standard_palette
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpPalette
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
name|GIMP_PALETTE
argument_list|(
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|standard_palette
argument_list|)
argument_list|,
literal|"Standard"
argument_list|)
expr_stmt|;
block|}
return|return
name|standard_palette
return|;
block|}
end_function

end_unit

