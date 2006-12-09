begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_FRAME_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_FRAME_H__
define|#
directive|define
name|__GIMP_COLOR_FRAME_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkframe.h>
end_include

begin_define
DECL|macro|GIMP_COLOR_FRAME_ROWS
define|#
directive|define
name|GIMP_COLOR_FRAME_ROWS
value|5
end_define

begin_define
DECL|macro|GIMP_TYPE_COLOR_FRAME
define|#
directive|define
name|GIMP_TYPE_COLOR_FRAME
value|(gimp_color_frame_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_FRAME (obj)
define|#
directive|define
name|GIMP_COLOR_FRAME
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_FRAME, GimpColorFrame))
end_define

begin_define
DECL|macro|GIMP_COLOR_FRAME_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_FRAME_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_FRAME, GimpColorFrameClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_FRAME (obj)
define|#
directive|define
name|GIMP_IS_COLOR_FRAME
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_FRAME))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_FRAME_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_FRAME_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_FRAME))
end_define

begin_define
DECL|macro|GIMP_COLOR_FRAME_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_FRAME_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_FRAME, GimpColorFrameClass))
end_define

begin_typedef
DECL|typedef|GimpColorFrameClass
typedef|typedef
name|struct
name|_GimpColorFrameClass
name|GimpColorFrameClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorFrame
struct|struct
name|_GimpColorFrame
block|{
DECL|member|parent_instance
name|GimpFrame
name|parent_instance
decl_stmt|;
DECL|member|sample_valid
name|gboolean
name|sample_valid
decl_stmt|;
DECL|member|sample_type
name|GimpImageType
name|sample_type
decl_stmt|;
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|member|color_index
name|gint
name|color_index
decl_stmt|;
DECL|member|frame_mode
name|GimpColorFrameMode
name|frame_mode
decl_stmt|;
DECL|member|has_number
name|gboolean
name|has_number
decl_stmt|;
DECL|member|number
name|gint
name|number
decl_stmt|;
DECL|member|has_color_area
name|gboolean
name|has_color_area
decl_stmt|;
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
DECL|member|number_label
name|GtkWidget
modifier|*
name|number_label
decl_stmt|;
DECL|member|color_area
name|GtkWidget
modifier|*
name|color_area
decl_stmt|;
DECL|member|name_labels
name|GtkWidget
modifier|*
name|name_labels
index|[
name|GIMP_COLOR_FRAME_ROWS
index|]
decl_stmt|;
DECL|member|value_labels
name|GtkWidget
modifier|*
name|value_labels
index|[
name|GIMP_COLOR_FRAME_ROWS
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorFrameClass
struct|struct
name|_GimpColorFrameClass
block|{
DECL|member|parent_class
name|GimpFrameClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_frame_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_frame_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_frame_set_mode
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|,
name|GimpColorFrameMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_frame_set_has_number
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|,
name|gboolean
name|has_number
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_frame_set_number
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|,
name|gint
name|number
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_frame_set_has_color_area
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|,
name|gboolean
name|has_color_area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_frame_set_color
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|,
name|GimpImageType
name|sample_type
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_frame_set_invalid
parameter_list|(
name|GimpColorFrame
modifier|*
name|frame
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COLOR_FRAME_H__  */
end_comment

end_unit

