begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in-menu-path.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-menu-path.h"
end_include

begin_typedef
DECL|typedef|MenuPathMapping
typedef|typedef
name|struct
name|_MenuPathMapping
name|MenuPathMapping
typedef|;
end_typedef

begin_struct
DECL|struct|_MenuPathMapping
struct|struct
name|_MenuPathMapping
block|{
DECL|member|orig_path
specifier|const
name|gchar
modifier|*
name|orig_path
decl_stmt|;
DECL|member|label
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
DECL|member|mapped_path
specifier|const
name|gchar
modifier|*
name|mapped_path
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|menu_path_mappings
specifier|static
specifier|const
name|MenuPathMapping
name|menu_path_mappings
index|[]
init|=
block|{
block|{
literal|"<Image>/File/Acquire"
block|,
name|NULL
block|,
literal|"<Image>/File/Create/Acquire"
block|}
block|,
block|{
literal|"<Image>/File/New"
block|,
name|NULL
block|,
literal|"<Image>/File/Create"
block|}
block|,
block|{
literal|"<Image>/Image/Mode/Color Profile"
block|,
name|NULL
block|,
literal|"<Image>/Image/Color Management"
block|}
block|,
block|{
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|gchar
modifier|*
DECL|function|plug_in_menu_path_map (const gchar * menu_path,const gchar * menu_label)
name|plug_in_menu_path_map
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|)
block|{
specifier|const
name|MenuPathMapping
modifier|*
name|mapping
decl_stmt|;
name|gchar
modifier|*
name|stripped_label
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|menu_label
condition|)
name|stripped_label
operator|=
name|gimp_strip_uline
argument_list|(
name|menu_label
argument_list|)
expr_stmt|;
for|for
control|(
name|mapping
operator|=
name|menu_path_mappings
init|;
name|mapping
operator|->
name|orig_path
condition|;
name|mapping
operator|++
control|)
block|{
if|if
condition|(
name|g_str_has_prefix
argument_list|(
name|menu_path
argument_list|,
name|mapping
operator|->
name|orig_path
argument_list|)
condition|)
block|{
name|gint
name|orig_len
init|=
name|strlen
argument_list|(
name|mapping
operator|->
name|orig_path
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|mapped_path
decl_stmt|;
comment|/*  if the mapping has a label, only map if the passed label            *  is identical and the paths' lengths match exactly.            */
if|if
condition|(
name|mapping
operator|->
name|label
operator|&&
operator|(
operator|!
name|stripped_label
operator|||
name|strlen
argument_list|(
name|menu_path
argument_list|)
operator|!=
name|orig_len
operator|||
name|strcmp
argument_list|(
name|mapping
operator|->
name|label
argument_list|,
name|stripped_label
argument_list|)
operator|)
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|strlen
argument_list|(
name|menu_path
argument_list|)
operator|>
name|orig_len
condition|)
name|mapped_path
operator|=
name|g_strconcat
argument_list|(
name|mapping
operator|->
name|mapped_path
argument_list|,
name|menu_path
operator|+
name|orig_len
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|mapped_path
operator|=
name|g_strdup
argument_list|(
name|mapping
operator|->
name|mapped_path
argument_list|)
expr_stmt|;
if|#
directive|if
name|GIMP_UNSTABLE
block|{
name|gchar
modifier|*
name|orig
decl_stmt|;
name|gchar
modifier|*
name|mapped
decl_stmt|;
if|if
condition|(
name|menu_label
condition|)
block|{
name|orig
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/%s"
argument_list|,
name|menu_path
argument_list|,
name|stripped_label
argument_list|)
expr_stmt|;
name|mapped
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/%s"
argument_list|,
name|mapped_path
argument_list|,
name|stripped_label
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|orig
operator|=
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|mapped
operator|=
name|g_strdup
argument_list|(
name|mapped_path
argument_list|)
expr_stmt|;
block|}
name|g_printerr
argument_list|(
literal|" mapped '%s' to '%s'\n"
argument_list|,
name|orig
argument_list|,
name|mapped
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|orig
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|mapped
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|g_free
argument_list|(
name|stripped_label
argument_list|)
expr_stmt|;
return|return
name|mapped_path
return|;
block|}
block|}
name|g_free
argument_list|(
name|stripped_label
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
return|;
block|}
end_function

end_unit

