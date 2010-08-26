begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelpui.h  * Copyright (C) 2000-2003 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HELP_UI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HELP_UI_H__
define|#
directive|define
name|__GIMP_HELP_UI_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|void
name|gimp_help_enable_tooltips
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help_disable_tooltips
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  the standard gimp help function  */
end_comment

begin_function_decl
name|void
name|gimp_standard_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  connect the help callback of a window  */
end_comment

begin_function_decl
name|void
name|gimp_help_connect
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  set help data for non-window widgets  */
end_comment

begin_function_decl
name|void
name|gimp_help_set_help_data
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  set help data with markup for non-window widgets  */
end_comment

begin_function_decl
name|void
name|gimp_help_set_help_data_with_markup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  activate the context help inspector  */
end_comment

begin_function_decl
name|void
name|gimp_context_help
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * GIMP_HELP_ID:  *  * The #GQuark used to attach GIMP help IDs to widgets.  *  * Since: GIMP 2.2  **/
end_comment

begin_define
DECL|macro|GIMP_HELP_ID
define|#
directive|define
name|GIMP_HELP_ID
value|(gimp_help_id_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_help_id_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HELP_UI_H__ */
end_comment

end_unit

