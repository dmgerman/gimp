begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpcolorscale.h  * Copyright (C) 2002  Sven Neumann<sven@gimp.org>  *                     Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This provides a color preview area. The preview  * can handle transparency by showing the checkerboard and  * handles drag'n'drop.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_SCALE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_SCALE_H__
define|#
directive|define
name|__GIMP_COLOR_SCALE_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkscale.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_COLOR_SCALE
define|#
directive|define
name|GIMP_TYPE_COLOR_SCALE
value|(gimp_color_scale_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_SCALE (obj)
define|#
directive|define
name|GIMP_COLOR_SCALE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_SCALE, GimpColorScale))
end_define

begin_define
DECL|macro|GIMP_COLOR_SCALE_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_SCALE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_SCALE, GimpColorScaleClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SCALE (obj)
define|#
directive|define
name|GIMP_IS_COLOR_SCALE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_SCALE))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SCALE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_SCALE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_SCALE))
end_define

begin_define
DECL|macro|GIMP_COLOR_SCALE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_SCALE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_SCALE, GimpColorScaleClass))
end_define

begin_typedef
DECL|typedef|GimpColorScaleClass
typedef|typedef
name|struct
name|_GimpColorScaleClass
name|GimpColorScaleClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorScale
struct|struct
name|_GimpColorScale
block|{
DECL|member|parent_instance
name|GtkScale
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|channel
name|GimpColorSelectorChannel
name|channel
decl_stmt|;
DECL|member|rgb
name|GimpRGB
name|rgb
decl_stmt|;
DECL|member|hsv
name|GimpHSV
name|hsv
decl_stmt|;
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
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorScaleClass
struct|struct
name|_GimpColorScaleClass
block|{
DECL|member|parent_class
name|GtkScaleClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_scale_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_scale_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_scale_set_channel
parameter_list|(
name|GimpColorScale
modifier|*
name|scale
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_scale_set_color
parameter_list|(
name|GimpColorScale
modifier|*
name|scale
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
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
comment|/* __GIMP_COLOR_SCALE_H__ */
end_comment

end_unit

