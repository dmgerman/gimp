begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_BAR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_BAR_H__
define|#
directive|define
name|__GIMP_COLOR_BAR_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkmisc.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_BAR
define|#
directive|define
name|GIMP_TYPE_COLOR_BAR
value|(gimp_color_bar_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_BAR (obj)
define|#
directive|define
name|GIMP_COLOR_BAR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_BAR, GimpColorBar))
end_define

begin_define
DECL|macro|GIMP_COLOR_BAR_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_BAR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_BAR, GimpColorBarClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_BAR (obj)
define|#
directive|define
name|GIMP_IS_COLOR_BAR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_BAR))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_BAR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_BAR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_BAR))
end_define

begin_define
DECL|macro|GIMP_COLOR_BAR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_BAR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_BAR, GimpColorBarClass))
end_define

begin_typedef
DECL|typedef|GimpColorBarClass
typedef|typedef
name|struct
name|_GimpColorBarClass
name|GimpColorBarClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorBar
struct|struct
name|_GimpColorBar
block|{
DECL|member|parent_class
name|GtkMisc
name|parent_class
decl_stmt|;
DECL|member|orientation
name|GtkOrientation
name|orientation
decl_stmt|;
DECL|member|buf
name|guchar
name|buf
index|[
literal|3
operator|*
literal|256
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorBarClass
struct|struct
name|_GimpColorBarClass
block|{
DECL|member|parent_class
name|GtkMiscClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_bar_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_bar_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_bar_set_color
parameter_list|(
name|GimpColorBar
modifier|*
name|bar
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
name|gimp_color_bar_set_channel
parameter_list|(
name|GimpColorBar
modifier|*
name|bar
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_bar_set_buffers
parameter_list|(
name|GimpColorBar
modifier|*
name|bar
parameter_list|,
specifier|const
name|guchar
modifier|*
name|red
parameter_list|,
specifier|const
name|guchar
modifier|*
name|green
parameter_list|,
specifier|const
name|guchar
modifier|*
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COLOR_BAR_H__  */
end_comment

end_unit

