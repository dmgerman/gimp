begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpintcombobox.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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
DECL|struct|_GimpIntComboBox
struct|struct
name|_GimpIntComboBox
block|{
DECL|member|parent_instance
name|GtkComboBox
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|priv
name|gpointer
name|priv
decl_stmt|;
comment|/* Padding for future expansion (should have gone to the class) */
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpIntComboBoxClass
struct|struct
name|_GimpIntComboBoxClass
block|{
DECL|member|parent_class
name|GtkComboBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpIntSensitivityFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpIntSensitivityFunc
function_decl|)
parameter_list|(
name|gint
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_int_combo_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_int_combo_box_new
argument_list|(
specifier|const
name|gchar
operator|*
name|first_label
argument_list|,
name|gint
name|first_value
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

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
name|void
name|gimp_int_combo_box_prepend
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_int_combo_box_append
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
modifier|...
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

begin_function_decl
name|gulong
name|gimp_int_combo_box_connect
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|gint
name|value
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_int_combo_box_set_sensitivity
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|GimpIntSensitivityFunc
name|func
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|GDestroyNotify
name|destroy
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

