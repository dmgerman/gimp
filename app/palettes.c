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
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
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
file|"palettes.h"
end_include

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
name|palettes_free
argument_list|()
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
name|gimp_data_list_load
argument_list|(
name|GIMP_DATA_LIST
argument_list|(
name|global_palette_factory
operator|->
name|container
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
block|}
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
name|gimp_container_num_children
argument_list|(
name|global_palette_factory
operator|->
name|container
argument_list|)
operator|==
literal|0
condition|)
return|return;
name|gimp_data_list_save_and_clear
argument_list|(
name|GIMP_DATA_LIST
argument_list|(
name|global_palette_factory
operator|->
name|container
argument_list|)
argument_list|,
name|palette_path
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

