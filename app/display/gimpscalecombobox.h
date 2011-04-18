begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpscalecombobox.h  * Copyright (C) 2004, 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SCALE_COMBO_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SCALE_COMBO_BOX_H__
define|#
directive|define
name|__GIMP_SCALE_COMBO_BOX_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_SCALE_COMBO_BOX
define|#
directive|define
name|GIMP_TYPE_SCALE_COMBO_BOX
value|(gimp_scale_combo_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_SCALE_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_SCALE_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SCALE_COMBO_BOX, GimpScaleComboBox))
end_define

begin_define
DECL|macro|GIMP_SCALE_COMBO_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_SCALE_COMBO_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SCALE_COMBO_BOX, GimpScaleComboBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_SCALE_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_IS_SCALE_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SCALE_COMBO_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_SCALE_COMBO_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SCALE_COMBO_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SCALE_COMBO_BOX))
end_define

begin_define
DECL|macro|GIMP_SCALE_COMBO_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SCALE_COMBO_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SCALE_COMBO_BOX, GimpScaleComboBoxClass))
end_define

begin_typedef
DECL|typedef|GimpScaleComboBoxClass
typedef|typedef
name|struct
name|_GimpScaleComboBoxClass
name|GimpScaleComboBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpScaleComboBoxClass
struct|struct
name|_GimpScaleComboBoxClass
block|{
DECL|member|parent_instance
name|GtkComboBoxClass
name|parent_instance
decl_stmt|;
DECL|member|entry_activated
name|void
function_decl|(
modifier|*
name|entry_activated
function_decl|)
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpScaleComboBox
struct|struct
name|_GimpScaleComboBox
block|{
DECL|member|parent_instance
name|GtkComboBox
name|parent_instance
decl_stmt|;
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
DECL|member|last_path
name|GtkTreePath
modifier|*
name|last_path
decl_stmt|;
DECL|member|mru
name|GList
modifier|*
name|mru
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_scale_combo_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_scale_combo_box_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scale_combo_box_set_scale
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_scale_combo_box_get_scale
parameter_list|(
name|GimpScaleComboBox
modifier|*
name|combo_box
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SCALE_COMBO_BOX_H__ */
end_comment

end_unit

