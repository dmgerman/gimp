begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdialog.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DIALOG_H__
define|#
directive|define
name|__GIMP_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|<libgimp/gimphelpui.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
name|GtkWidget
modifier|*
name|gimp_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|wmclass_name
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|,
name|GtkWindowPosition
name|position
parameter_list|,
name|gint
name|allow_shrink
parameter_list|,
name|gint
name|allow_grow
parameter_list|,
name|gint
name|auto_shrink
parameter_list|,
comment|/* specify action area buttons 					      * as va_list: 					      *  gchar          *label, 					      *  GtkSignalFunc   callback, 					      *  gpointer        data, 					      *  GtkObject      *slot_object, 					      *  GtkWidget     **widget_ptr, 					      *  gboolean        default_action, 					      *  gboolean        connect_delete, 					      */
modifier|...
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_dialog_newv
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|wmclass_name
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|,
name|GtkWindowPosition
name|position
parameter_list|,
name|gint
name|allow_shrink
parameter_list|,
name|gint
name|allow_grow
parameter_list|,
name|gint
name|auto_shrink
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
name|void
name|gimp_dialog_set_icon
parameter_list|(
name|GtkWindow
modifier|*
name|dialog
parameter_list|)
function_decl|;
name|void
name|gimp_dialog_create_action_area
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
comment|/* specify action area buttons 					      * as va_list: 					      *  gchar          *label, 					      *  GtkSignalFunc   callback, 					      *  gpointer        data, 					      *  GtkObject      *slot_object, 					      *  GtkWidget     **widget_ptr, 					      *  gboolean        default_action, 					      *  gboolean        connect_delete, 					      */
modifier|...
parameter_list|)
function_decl|;
name|void
name|gimp_dialog_create_action_areav
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DIALOG_H__ */
end_comment

end_unit

