begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpenumcombobox.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ENUM_COMBO_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ENUM_COMBO_BOX_H__
define|#
directive|define
name|__GIMP_ENUM_COMBO_BOX_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkcombobox.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_ENUM_COMBO_BOX
define|#
directive|define
name|GIMP_TYPE_ENUM_COMBO_BOX
value|(gimp_enum_combo_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_ENUM_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_ENUM_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ENUM_COMBO_BOX, GimpEnumComboBox))
end_define

begin_define
DECL|macro|GIMP_ENUM_COMBO_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_ENUM_COMBO_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ENUM_COMBO_BOX, GimpEnumComboBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_ENUM_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_IS_ENUM_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ENUM_COMBO_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_ENUM_COMBO_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ENUM_COMBO_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ENUM_COMBO_BOX))
end_define

begin_define
DECL|macro|GIMP_ENUM_COMBO_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ENUM_COMBO_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ENUM_COMBO_BOX, GimpEnumComboBoxClass))
end_define

begin_typedef
DECL|typedef|GimpEnumComboBoxClass
typedef|typedef
name|struct
name|_GimpEnumComboBoxClass
name|GimpEnumComboBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEnumComboBoxClass
struct|struct
name|_GimpEnumComboBoxClass
block|{
DECL|member|parent_instance
name|GtkComboBoxClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEnumComboBox
struct|struct
name|_GimpEnumComboBox
block|{
DECL|member|parent_instance
name|GtkComboBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_enum_combo_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_enum_combo_box_new
parameter_list|(
name|GType
name|enum_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_enum_combo_box_new_with_model
parameter_list|(
name|GimpEnumStore
modifier|*
name|enum_store
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_enum_combo_box_set_active
parameter_list|(
name|GimpEnumComboBox
modifier|*
name|combo_box
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_enum_combo_box_get_active
parameter_list|(
name|GimpEnumComboBox
modifier|*
name|combo_box
parameter_list|,
name|gint
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_enum_combo_box_set_stock_prefix
parameter_list|(
name|GimpEnumComboBox
modifier|*
name|combo_box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_prefix
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ENUM_COMBO_BOX_H__ */
end_comment

end_unit

