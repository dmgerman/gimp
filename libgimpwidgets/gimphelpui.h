begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelpui.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
name|void
name|gimp_help_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|void
name|gimp_help_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|void
name|gimp_help_enable_tooltips
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|void
name|gimp_help_disable_tooltips
parameter_list|(
name|void
parameter_list|)
function_decl|;
comment|/*  the standard gimp help function  *  (has different implementations in the main app and in libgimp)  */
name|void
name|gimp_standard_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
comment|/*  connect the help callback of a window  */
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
name|help_data
parameter_list|)
function_decl|;
comment|/*  set help data for non-window widgets  */
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
name|help_data
parameter_list|)
function_decl|;
comment|/*  activate the context help inspector  */
name|void
name|gimp_context_help
parameter_list|(
name|void
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
comment|/* __GIMP_HELP_UI_H__ */
end_comment

end_unit

