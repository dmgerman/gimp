begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PALETTE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PALETTE_H__
define|#
directive|define
name|__GIMP_PALETTE_H__
end_define

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PALETTE
define|#
directive|define
name|GIMP_TYPE_PALETTE
value|(gimp_palette_get_type ())
end_define

begin_define
DECL|macro|GIMP_PALETTE (obj)
define|#
directive|define
name|GIMP_PALETTE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PALETTE, GimpPalette))
end_define

begin_define
DECL|macro|GIMP_PALETTE_CLASS (klass)
define|#
directive|define
name|GIMP_PALETTE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PALETTE, GimpPaletteClass))
end_define

begin_define
DECL|macro|GIMP_IS_PALETTE (obj)
define|#
directive|define
name|GIMP_IS_PALETTE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PALETTE))
end_define

begin_define
DECL|macro|GIMP_IS_PALETTE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PALETTE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PALETTE))
end_define

begin_define
DECL|macro|GIMP_PALETTE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PALETTE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PALETTE, GimpPaletteClass))
end_define

begin_struct
DECL|struct|_GimpPaletteEntry
struct|struct
name|_GimpPaletteEntry
block|{
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* EEK */
DECL|member|position
name|gint
name|position
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpPaletteClass
typedef|typedef
name|struct
name|_GimpPaletteClass
name|GimpPaletteClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPalette
struct|struct
name|_GimpPalette
block|{
DECL|member|parent_instance
name|GimpData
name|parent_instance
decl_stmt|;
DECL|member|colors
name|GList
modifier|*
name|colors
decl_stmt|;
DECL|member|n_colors
name|gint
name|n_colors
decl_stmt|;
DECL|member|n_columns
name|gint
name|n_columns
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaletteClass
struct|struct
name|_GimpPaletteClass
block|{
DECL|member|parent_class
name|GimpDataClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_palette_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpData
modifier|*
name|gimp_palette_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpData
modifier|*
name|gimp_palette_get_standard
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_palette_get_colors
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_palette_get_n_colors
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPaletteEntry
modifier|*
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
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_set_entry
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
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_set_entry_color
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|gint
name|position
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_set_entry_name
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPaletteEntry
modifier|*
name|gimp_palette_get_entry
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_palette_set_columns
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|,
name|gint
name|columns
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_palette_get_columns
parameter_list|(
name|GimpPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPaletteEntry
modifier|*
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PALETTE_H__ */
end_comment

end_unit

