begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HANDLE_BAR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HANDLE_BAR_H__
define|#
directive|define
name|__GIMP_HANDLE_BAR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_HANDLE_BAR
define|#
directive|define
name|GIMP_TYPE_HANDLE_BAR
value|(gimp_handle_bar_get_type ())
end_define

begin_define
DECL|macro|GIMP_HANDLE_BAR (obj)
define|#
directive|define
name|GIMP_HANDLE_BAR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HANDLE_BAR, GimpHandleBar))
end_define

begin_define
DECL|macro|GIMP_HANDLE_BAR_CLASS (klass)
define|#
directive|define
name|GIMP_HANDLE_BAR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HANDLE_BAR, GimpHandleBarClass))
end_define

begin_define
DECL|macro|GIMP_IS_HANDLE_BAR (obj)
define|#
directive|define
name|GIMP_IS_HANDLE_BAR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HANDLE_BAR))
end_define

begin_define
DECL|macro|GIMP_IS_HANDLE_BAR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HANDLE_BAR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HANDLE_BAR))
end_define

begin_define
DECL|macro|GIMP_HANDLE_BAR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HANDLE_BAR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HANDLE_BAR, GimpHandleBarClass))
end_define

begin_typedef
DECL|typedef|GimpHandleBarClass
typedef|typedef
name|struct
name|_GimpHandleBarClass
name|GimpHandleBarClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHandleBar
struct|struct
name|_GimpHandleBar
block|{
DECL|member|parent_class
name|GtkEventBox
name|parent_class
decl_stmt|;
DECL|member|orientation
name|GtkOrientation
name|orientation
decl_stmt|;
DECL|member|slider_adj
name|GtkAdjustment
modifier|*
name|slider_adj
index|[
literal|3
index|]
decl_stmt|;
DECL|member|lower
name|gdouble
name|lower
decl_stmt|;
DECL|member|upper
name|gdouble
name|upper
decl_stmt|;
DECL|member|slider_pos
name|gint
name|slider_pos
index|[
literal|3
index|]
decl_stmt|;
DECL|member|active_slider
name|gint
name|active_slider
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHandleBarClass
struct|struct
name|_GimpHandleBarClass
block|{
DECL|member|parent_class
name|GtkEventBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_handle_bar_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_handle_bar_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_handle_bar_set_adjustment
parameter_list|(
name|GimpHandleBar
modifier|*
name|bar
parameter_list|,
name|gint
name|handle_no
parameter_list|,
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_handle_bar_connect_events
parameter_list|(
name|GimpHandleBar
modifier|*
name|bar
parameter_list|,
name|GtkWidget
modifier|*
name|event_source
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_HANDLE_BAR_H__  */
end_comment

end_unit

