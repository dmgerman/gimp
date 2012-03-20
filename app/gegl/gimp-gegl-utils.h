begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-gegl-utils.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GEGL_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GEGL_UTILS_H__
define|#
directive|define
name|__GIMP_GEGL_UTILS_H__
end_define

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_comment
comment|/* temp hack */
end_comment

begin_decl_stmt
specifier|const
name|Babl
modifier|*
name|gimp_bpp_to_babl_format
argument_list|(
name|guint
name|bpp
argument_list|,
name|gboolean
name|linear
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|Babl
modifier|*
name|gimp_bpp_to_babl_format_with_alpha
argument_list|(
name|guint
name|bpp
argument_list|,
name|gboolean
name|linear
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_layer_mode_to_gegl_operation
argument_list|(
name|GimpLayerModeEffects
name|mode
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_interpolation_to_gegl_filter
argument_list|(
name|GimpInterpolationType
name|interpolation
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_gegl_buffer_new
parameter_list|(
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_tile_manager_create_buffer
parameter_list|(
name|TileManager
modifier|*
name|tm
parameter_list|,
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gboolean
name|write
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_gegl_buffer_get_tiles
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gimp_pixbuf_create_buffer
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gegl_buffer_refetch_tiles
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglColor
modifier|*
name|gimp_gegl_color_new
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GEGL_UTILS_H__ */
end_comment

end_unit

