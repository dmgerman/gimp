begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpintcombobox.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_INT_COMBO_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_INT_COMBO_BOX_H__
define|#
directive|define
name|__GIMP_INT_COMBO_BOX_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkcombobox.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_INT_COMBO_BOX
define|#
directive|define
name|GIMP_TYPE_INT_COMBO_BOX
value|(gimp_int_combo_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_INT_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_INT_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_INT_COMBO_BOX, GimpIntComboBox))
end_define

begin_define
DECL|macro|GIMP_INT_COMBO_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_INT_COMBO_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_INT_COMBO_BOX, GimpIntComboBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_INT_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_IS_INT_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_INT_COMBO_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_INT_COMBO_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_INT_COMBO_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_INT_COMBO_BOX))
end_define

begin_define
DECL|macro|GIMP_INT_COMBO_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_INT_COMBO_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_INT_COMBO_BOX, GimpIntComboBoxClass))
end_define

begin_typedef
DECL|typedef|GimpIntComboBoxClass
typedef|typedef
name|struct
name|_GimpIntComboBoxClass
name|GimpIntComboBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpIntComboBoxClass
struct|struct
name|_GimpIntComboBoxClass
block|{
DECL|member|parent_instance
name|GtkComboBoxClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpIntComboBox
struct|struct
name|_GimpIntComboBox
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
name|gimp_int_combo_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_int_combo_box_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|first_label
parameter_list|,
name|gint
name|first_value
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_int_combo_box_new_valist
parameter_list|(
specifier|const
name|gchar
modifier|*
name|first_label
parameter_list|,
name|gint
name|first_value
parameter_list|,
name|va_list
name|values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_int_combo_box_new_array
parameter_list|(
name|gint
name|n_values
parameter_list|,
specifier|const
name|gchar
modifier|*
name|labels
index|[]
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_int_combo_box_set_active
parameter_list|(
name|GimpIntComboBox
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
name|gimp_int_combo_box_get_active
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|gint
modifier|*
name|value
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
comment|/* __GIMP_INT_COMBO_BOX_H__ */
end_comment

end_unit

