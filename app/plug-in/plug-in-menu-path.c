begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in-menu-path.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"glib-object.h"
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
literal|"<Toolbox>/Xtns/Languages"
block|,
literal|"<Image>/Filters/Languages"
block|}
block|,
block|{
literal|"<Toolbox>/Xtns"
block|,
literal|"<Image>/Xtns"
block|}
block|,
block|{
literal|"<Toolbox>/Help"
block|,
literal|"<Image>/Help"
block|}
block|,
block|{
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
DECL|function|plug_in_menu_path_map (const gchar * menu_path)
name|plug_in_menu_path_map
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
block|{
specifier|const
name|MenuPathMapping
modifier|*
name|mapping
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
literal|0
block|g_printerr ("%s: mapped %s to %s\n", G_STRFUNC,                       menu_path, mapped_path);
endif|#
directive|endif
return|return
name|mapped_path
return|;
block|}
block|}
return|return
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
return|;
block|}
end_function

end_unit

