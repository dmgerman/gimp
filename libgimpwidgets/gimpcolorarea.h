begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpcolorarea.h  * Copyright (C) 2001 Sven Neumann  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<gtk/gtkpreview.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|macro|GIMP_TYPE_COLOR_AREA
define|#
directive|define
name|GIMP_TYPE_COLOR_AREA
value|(gimp_color_area_get_type ())
DECL|macro|GIMP_COLOR_AREA (obj)
define|#
directive|define
name|GIMP_COLOR_AREA
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_COLOR_AREA, GimpColorArea))
DECL|macro|GIMP_COLOR_AREA_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_AREA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_AREA, GimpColorAreaClass))
DECL|macro|GIMP_IS_COLOR_AREA (obj)
define|#
directive|define
name|GIMP_IS_COLOR_AREA
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_COLOR_AREA))
DECL|macro|GIMP_IS_COLOR_AREA_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_AREA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_AREA))
typedef|typedef
enum|enum
DECL|enum|__anon29bef2910103
block|{
DECL|enumerator|GIMP_COLOR_AREA_FLAT
name|GIMP_COLOR_AREA_FLAT
init|=
literal|0
block|,
DECL|enumerator|GIMP_COLOR_AREA_SMALL_CHECKS
name|GIMP_COLOR_AREA_SMALL_CHECKS
block|,
DECL|enumerator|GIMP_COLOR_AREA_LARGE_CHECKS
name|GIMP_COLOR_AREA_LARGE_CHECKS
DECL|typedef|GimpColorAreaType
block|}
name|GimpColorAreaType
typedef|;
DECL|typedef|GimpColorAreaClass
typedef|typedef
name|struct
name|_GimpColorAreaClass
name|GimpColorAreaClass
typedef|;
DECL|struct|_GimpColorArea
struct|struct
name|_GimpColorArea
block|{
DECL|member|preview
name|GtkPreview
name|preview
decl_stmt|;
comment|/*< private>*/
DECL|member|type
name|GimpColorAreaType
name|type
decl_stmt|;
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpColorAreaClass
struct|struct
name|_GimpColorAreaClass
block|{
DECL|member|parent_class
name|GtkPreviewClass
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
name|gca
parameter_list|)
function_decl|;
block|}
struct|;
name|GtkType
name|gimp_color_area_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
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
name|void
name|gimp_color_area_set_color
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
name|void
name|gimp_color_area_get_color
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
name|gboolean
name|gimp_color_area_has_alpha
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|)
function_decl|;
name|void
name|gimp_color_area_set_type
parameter_list|(
name|GimpColorArea
modifier|*
name|gca
parameter_list|,
name|GimpColorAreaType
name|type
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_AREA_H__ */
end_comment

end_unit

