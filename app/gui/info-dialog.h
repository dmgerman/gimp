begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__INFO_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__INFO_DIALOG_H__
define|#
directive|define
name|__INFO_DIALOG_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27596bc00103
block|{
DECL|enumerator|INFO_LABEL
name|INFO_LABEL
block|,
DECL|enumerator|INFO_ENTRY
name|INFO_ENTRY
block|,
DECL|enumerator|INFO_SCALE
name|INFO_SCALE
block|,
DECL|enumerator|INFO_SPINBUTTON
name|INFO_SPINBUTTON
block|,
DECL|enumerator|INFO_SIZEENTRY
name|INFO_SIZEENTRY
DECL|typedef|InfoFieldType
block|}
name|InfoFieldType
typedef|;
end_typedef

begin_typedef
DECL|typedef|InfoField
typedef|typedef
name|struct
name|_InfoField
name|InfoField
typedef|;
end_typedef

begin_struct
DECL|struct|_InfoField
struct|struct
name|_InfoField
block|{
DECL|member|field_type
name|InfoFieldType
name|field_type
decl_stmt|;
DECL|member|obj
name|GtkObject
modifier|*
name|obj
decl_stmt|;
DECL|member|value_ptr
name|gpointer
name|value_ptr
decl_stmt|;
DECL|member|callback
name|GCallback
name|callback
decl_stmt|;
DECL|member|callback_data
name|gpointer
name|callback_data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_InfoDialog
struct|struct
name|_InfoDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|info_table
name|GtkWidget
modifier|*
name|info_table
decl_stmt|;
DECL|member|info_notebook
name|GtkWidget
modifier|*
name|info_notebook
decl_stmt|;
DECL|member|field_list
name|GSList
modifier|*
name|field_list
decl_stmt|;
DECL|member|nfields
name|guint
name|nfields
decl_stmt|;
DECL|member|user_data
name|void
modifier|*
name|user_data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Info Dialog functions  */
end_comment

begin_function_decl
name|InfoDialog
modifier|*
name|info_dialog_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|InfoDialog
modifier|*
name|info_dialog_notebook_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_free
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_popup
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_popdown
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|info_dialog_update
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|info_dialog_add_label
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|text_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|info_dialog_add_entry
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
name|text_ptr
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|info_dialog_add_scale
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
modifier|*
name|value_ptr
parameter_list|,
name|gfloat
name|lower
parameter_list|,
name|gfloat
name|upper
parameter_list|,
name|gfloat
name|step_increment
parameter_list|,
name|gfloat
name|page_increment
parameter_list|,
name|gfloat
name|page_size
parameter_list|,
name|gint
name|digits
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|info_dialog_add_spinbutton
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
modifier|*
name|value_ptr
parameter_list|,
name|gfloat
name|lower
parameter_list|,
name|gfloat
name|upper
parameter_list|,
name|gfloat
name|step_increment
parameter_list|,
name|gfloat
name|page_increment
parameter_list|,
name|gfloat
name|page_size
parameter_list|,
name|gfloat
name|climb_rate
parameter_list|,
name|gint
name|digits
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|info_dialog_add_sizeentry
parameter_list|(
name|InfoDialog
modifier|*
name|idialog
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
modifier|*
name|value_ptr
parameter_list|,
name|gint
name|nfields
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gchar
modifier|*
name|unit_format
parameter_list|,
name|gboolean
name|menu_show_pixels
parameter_list|,
name|gboolean
name|menu_show_percent
parameter_list|,
name|gboolean
name|show_refval
parameter_list|,
name|GimpSizeEntryUpdatePolicy
name|update_policy
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __INFO_DIALOG_H__  */
end_comment

end_unit

