begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpiconpicker.h  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *               2012 Daniel Sabo  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ICON_PICKER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ICON_PICKER_H__
define|#
directive|define
name|__GIMP_ICON_PICKER_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_ICON_PICKER
define|#
directive|define
name|GIMP_TYPE_ICON_PICKER
value|(gimp_icon_picker_get_type ())
end_define

begin_define
DECL|macro|GIMP_ICON_PICKER (obj)
define|#
directive|define
name|GIMP_ICON_PICKER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ICON_PICKER, GimpIconPicker))
end_define

begin_define
DECL|macro|GIMP_ICON_PICKER_CLASS (klass)
define|#
directive|define
name|GIMP_ICON_PICKER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ICON_PICKER, GimpIconPickerClass))
end_define

begin_define
DECL|macro|GIMP_IS_ICON_PICKER (obj)
define|#
directive|define
name|GIMP_IS_ICON_PICKER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ICON_PICKER))
end_define

begin_define
DECL|macro|GIMP_IS_ICON_PICKER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ICON_PICKER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ICON_PICKER))
end_define

begin_define
DECL|macro|GIMP_ICON_PICKER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ICON_PICKER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ICON_PICKER, GimpIconPickerClass))
end_define

begin_typedef
DECL|typedef|GimpIconPickerClass
typedef|typedef
name|struct
name|_GimpIconPickerClass
name|GimpIconPickerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpIconPicker
struct|struct
name|_GimpIconPicker
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpIconPickerClass
struct|struct
name|_GimpIconPickerClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_icon_picker_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_icon_picker_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_icon_picker_get_icon_name
parameter_list|(
name|GimpIconPicker
modifier|*
name|picker
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_icon_picker_set_icon_name
parameter_list|(
name|GimpIconPicker
modifier|*
name|picker
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_icon_picker_get_icon_pixbuf
parameter_list|(
name|GimpIconPicker
modifier|*
name|picker
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_icon_picker_set_icon_pixbuf
parameter_list|(
name|GimpIconPicker
modifier|*
name|picker
parameter_list|,
name|GdkPixbuf
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ICON_PICKER_H__  */
end_comment

end_unit

