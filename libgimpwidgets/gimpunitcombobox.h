begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * gimpunitcombobox.h  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_UNIT_COMBO_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UNIT_COMBO_BOX_H__
define|#
directive|define
name|__GIMP_UNIT_COMBO_BOX_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_UNIT_COMBO_BOX
define|#
directive|define
name|GIMP_TYPE_UNIT_COMBO_BOX
value|(gimp_unit_combo_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_UNIT_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_UNIT_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UNIT_COMBO_BOX, GimpUnitComboBox))
end_define

begin_define
DECL|macro|GIMP_UNIT_COMBO_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_UNIT_COMBO_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_UNIT_COMBO_BOX, GimpUnitComboBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_UNIT_COMBO_BOX (obj)
define|#
directive|define
name|GIMP_IS_UNIT_COMBO_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_UNIT_COMBO_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_UNIT_COMBO_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_UNIT_COMBO_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_UNIT_COMBO_BOX))
end_define

begin_define
DECL|macro|GIMP_UNIT_COMBO_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_UNIT_COMBO_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_UNIT_COMBO_BOX, GimpUnitComboBoxClass))
end_define

begin_typedef
DECL|typedef|GimpUnitComboBoxClass
typedef|typedef
name|struct
name|_GimpUnitComboBoxClass
name|GimpUnitComboBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUnitComboBoxClass
struct|struct
name|_GimpUnitComboBoxClass
block|{
DECL|member|parent_instance
name|GtkComboBoxClass
name|parent_instance
decl_stmt|;
comment|/* Padding for future expansion */
DECL|member|_gtk_reserved1
name|void
function_decl|(
modifier|*
name|_gtk_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved2
name|void
function_decl|(
modifier|*
name|_gtk_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved3
name|void
function_decl|(
modifier|*
name|_gtk_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved4
name|void
function_decl|(
modifier|*
name|_gtk_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpUnitComboBox
struct|struct
name|_GimpUnitComboBox
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
name|gimp_unit_combo_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_unit_combo_box_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_unit_combo_box_new_with_model
parameter_list|(
name|GimpUnitStore
modifier|*
name|model
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_unit_combo_box_get_active
parameter_list|(
name|GimpUnitComboBox
modifier|*
name|combo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unit_combo_box_set_active
parameter_list|(
name|GimpUnitComboBox
modifier|*
name|combo
parameter_list|,
name|GimpUnit
name|unit
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
comment|/* __GIMP_UNIT_COMBO_BOX_H__ */
end_comment

end_unit

