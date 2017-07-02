begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimppropgui.h  * Copyright (C) 2002-2017 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROP_GUI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROP_GUI_H__
define|#
directive|define
name|__GIMP_PROP_GUI_H__
end_define

begin_comment
comment|/*  A view on all of an object's properties  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2af15f6b0103
block|{
DECL|enumerator|GIMP_CONTROLLER_TYPE_LINE
name|GIMP_CONTROLLER_TYPE_LINE
DECL|typedef|GimpControllerType
block|}
name|GimpControllerType
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpControllerLineCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpControllerLineCallback
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpCreatePickerFunc
typedef|typedef
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|GimpCreatePickerFunc
function_decl|)
parameter_list|(
name|gpointer
name|creator
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
name|gboolean
name|pick_abyss
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpCreateControllerFunc
typedef|typedef
name|GCallback
function_decl|(
modifier|*
name|GimpCreateControllerFunc
function_decl|)
parameter_list|(
name|gpointer
name|creator
parameter_list|,
name|GimpControllerType
name|controller_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gpointer
modifier|*
name|set_func_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_widget_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpCreatePickerFunc
name|create_picker
parameter_list|,
name|GimpCreateControllerFunc
name|create_controller
parameter_list|,
name|gpointer
name|creator
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_widget_new_from_pspec
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpCreatePickerFunc
name|create_picker
parameter_list|,
name|GimpCreateControllerFunc
name|create_controller
parameter_list|,
name|gpointer
name|creator
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prop_gui_new
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GType
name|owner_type
parameter_list|,
name|GParamFlags
name|flags
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpCreatePickerFunc
name|create_picker
parameter_list|,
name|GimpCreateControllerFunc
name|create_controller
parameter_list|,
name|gpointer
name|creator
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_prop_gui_bind_container
parameter_list|(
name|GtkWidget
modifier|*
name|source
parameter_list|,
name|GtkWidget
modifier|*
name|target
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_prop_gui_bind_label
parameter_list|(
name|GtkWidget
modifier|*
name|source
parameter_list|,
name|GtkWidget
modifier|*
name|target
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_prop_gui_bind_tooltip
parameter_list|(
name|GtkWidget
modifier|*
name|source
parameter_list|,
name|GtkWidget
modifier|*
name|target
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROP_GUI_H__ */
end_comment

end_unit

