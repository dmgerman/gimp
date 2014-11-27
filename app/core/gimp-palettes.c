begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others  *  * gimp-gradients.c  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-palettes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppalettemru.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|COLOR_HISTORY_KEY
define|#
directive|define
name|COLOR_HISTORY_KEY
value|"gimp-palette-color-history"
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpPalette
modifier|*
name|gimp_palettes_add_palette
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
specifier|const
name|gchar
modifier|*
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_palettes_init (Gimp * gimp)
name|gimp_palettes_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|palette
operator|=
name|gimp_palettes_add_palette
argument_list|(
name|gimp
argument_list|,
name|_
argument_list|(
literal|"Color History"
argument_list|)
argument_list|,
name|COLOR_HISTORY_KEY
argument_list|)
expr_stmt|;
name|gimp_context_set_palette
argument_list|(
name|gimp
operator|->
name|user_context
argument_list|,
name|palette
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_palettes_load (Gimp * gimp)
name|gimp_palettes_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|palette
operator|=
name|gimp_palettes_get_color_history
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
literal|"colorrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_palette_mru_load
argument_list|(
name|GIMP_PALETTE_MRU
argument_list|(
name|palette
argument_list|)
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_palettes_save (Gimp * gimp)
name|gimp_palettes_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|palette
operator|=
name|gimp_palettes_get_color_history
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
literal|"colorrc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_palette_mru_save
argument_list|(
name|GIMP_PALETTE_MRU
argument_list|(
name|palette
argument_list|)
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpPalette
modifier|*
DECL|function|gimp_palettes_get_color_history (Gimp * gimp)
name|gimp_palettes_get_color_history
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
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
return|return
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|COLOR_HISTORY_KEY
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpPalette
modifier|*
DECL|function|gimp_palettes_add_palette (Gimp * gimp,const gchar * name,const gchar * id)
name|gimp_palettes_add_palette
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
specifier|const
name|gchar
modifier|*
name|id
parameter_list|)
block|{
name|GimpData
modifier|*
name|palette
decl_stmt|;
name|palette
operator|=
name|gimp_palette_mru_new
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gimp_data_make_internal
argument_list|(
name|palette
argument_list|,
name|id
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|palette_factory
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|palette
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|id
argument_list|,
name|palette
argument_list|)
expr_stmt|;
return|return
name|GIMP_PALETTE
argument_list|(
name|palette
argument_list|)
return|;
block|}
end_function

end_unit

