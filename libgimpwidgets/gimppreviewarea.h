begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREVIEW_AREA_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREVIEW_AREA_H__
define|#
directive|define
name|__GIMP_PREVIEW_AREA_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdrawingarea.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_PREVIEW_AREA
define|#
directive|define
name|GIMP_TYPE_PREVIEW_AREA
value|(gimp_preview_area_get_type ())
end_define

begin_define
DECL|macro|GIMP_PREVIEW_AREA (obj)
define|#
directive|define
name|GIMP_PREVIEW_AREA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PREVIEW_AREA, GimpPreviewArea))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_AREA_CLASS (klass)
define|#
directive|define
name|GIMP_PREVIEW_AREA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREVIEW_AREA, GimpPreviewAreaClass))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_AREA (obj)
define|#
directive|define
name|GIMP_IS_PREVIEW_AREA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PREVIEW_AREA))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_AREA_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREVIEW_AREA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREVIEW_AREA))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_AREA_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PREVIEW_AREA_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PREVIEW_AREA, GimpPreviewArea))
end_define

begin_typedef
DECL|typedef|GimpPreviewAreaClass
typedef|typedef
name|struct
name|_GimpPreviewAreaClass
name|GimpPreviewAreaClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPreviewArea
struct|struct
name|_GimpPreviewArea
block|{
DECL|member|parent_instance
name|GtkDrawingArea
name|parent_instance
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|rowstride
name|gint
name|rowstride
decl_stmt|;
DECL|member|dither_x
name|gint
name|dither_x
decl_stmt|;
DECL|member|dither_y
name|gint
name|dither_y
decl_stmt|;
DECL|member|buf
name|guchar
modifier|*
name|buf
decl_stmt|;
DECL|member|cmap
name|guchar
modifier|*
name|cmap
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPreviewAreaClass
struct|struct
name|_GimpPreviewAreaClass
block|{
DECL|member|parent_class
name|GtkDrawingAreaClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_preview_area_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_preview_area_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_area_draw
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageType
name|type
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buf
parameter_list|,
name|gint
name|rowstride
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_area_fill
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_area_set_cmap
parameter_list|(
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
specifier|const
name|guchar
modifier|*
name|cmap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PREVIEW_AREA_H__ */
end_comment

end_unit

