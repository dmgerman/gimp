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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcoreconfig.h"
end_include

begin_decl_stmt
DECL|variable|static_core_config
specifier|static
name|GimpCoreConfig
name|static_core_config
init|=
block|{
comment|/* plug_in_path             */
name|NULL
block|,
comment|/* module_path              */
name|NULL
block|,
comment|/* brush_path               */
name|NULL
block|,
comment|/* pattern_path             */
name|NULL
block|,
comment|/* palette_path             */
name|NULL
block|,
comment|/* gradient_path            */
name|NULL
block|,
comment|/* default_brush            */
name|NULL
block|,
comment|/* default_pattern          */
name|NULL
block|,
comment|/* default_palette          */
name|NULL
block|,
comment|/* default_gradient         */
name|NULL
block|,
comment|/* default_comment          */
name|NULL
block|,
comment|/* default_type             */
name|RGB
block|,
comment|/* default_width            */
literal|256
block|,
comment|/* default_height           */
literal|256
block|,
comment|/* default_units            */
name|GIMP_UNIT_INCH
block|,
comment|/* default_xresolution      */
literal|72.0
block|,
comment|/* default_yresolution      */
literal|72.0
block|,
comment|/* default_resolution_units */
name|GIMP_UNIT_INCH
block|,
comment|/* levels_of_undo           */
literal|5
block|,
comment|/* pluginrc_path            */
name|NULL
block|,
comment|/* module_db_load_inhibit   */
name|NULL
block|,
comment|/* thumbnail_mode           */
literal|1
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|core_config
name|GimpCoreConfig
modifier|*
name|core_config
init|=
operator|&
name|static_core_config
decl_stmt|;
end_decl_stmt

end_unit

