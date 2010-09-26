begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorarea.h  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* This provides a color preview area. The preview  * can handle transparency by showing the checkerboard and  * handles drag'n'drop.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_AREA_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_AREA_H__
define|#
directive|define
name|__GIMP_COLOR_AREA_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_COLOR_AREA
define|#
directive|define
name|GIMP_TYPE_COLOR_AREA
value|(gimp_color_area_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_AREA (obj)
define|#
directive|define
name|GIMP_COLOR_AREA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_AREA, GimpColorArea))
end_define

begin_define
DECL|macro|GIMP_COLOR_AREA_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_AREA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_AREA, GimpColorAreaClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_AREA (obj)
define|#
directive|define
name|GIMP_IS_COLOR_AREA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_AREA))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_AREA_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_AREA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_AREA))
end_define

begin_define
DECL|macro|GIMP_COLOR_AREA_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_AREA_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_AREA, GimpColorAreaClass))
end_define

begin_typedef
DECL|typedef|GimpColorAreaClass
typedef|typedef
name|struct
name|_GimpColorAreaClass
name|GimpColorAreaClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorArea
struct|struct
name|_GimpColorArea
block|{
DECL|member|parent_instance
name|GtkDrawingArea
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|buf
name|guchar
modifier|*
name|buf
decl_stmt|;
DECL|member|width
name|guint
name|width
decl_stmt|;
DECL|member|height
name|guint
name|height
decl_stmt|;
DECL|member|rowstride
name|guint
name|rowstride
decl_stmt|;
DECL|member|type
name|GimpColorAreaType
name|type
decl_stmt|;
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|member|draw_border
name|guint
name|draw_border
range|:
literal|1
decl_stmt|;
DECL|member|needs_render
name|guint
name|needs_render
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorAreaClass
struct|struct
name|_GimpColorAreaClass
block|{
DECL|member|parent_class
name|GtkDrawingAreaClass
name|parent_class
decl_stmt|;
DECL|member|color_changed
name|void
function_decl|(
modifier|*
name|color_changed
function_decl|)
parameter_list|(
name|GimpColorArea
modifier|*
name|area
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_area_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_area_new
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|,
name|GdkModifierType
name|drag_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_area_set_color
parameter_list|(
name|GimpColorArea
modifier|*
name|area
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
name|gimp_color_area_get_color
parameter_list|(
name|GimpColorArea
modifier|*
name|area
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_area_has_alpha
parameter_list|(
name|GimpColorArea
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_area_set_type
parameter_list|(
name|GimpColorArea
modifier|*
name|area
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_area_set_draw_border
parameter_list|(
name|GimpColorArea
modifier|*
name|area
parameter_list|,
name|gboolean
name|draw_border
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_AREA_H__ */
end_comment

end_unit

