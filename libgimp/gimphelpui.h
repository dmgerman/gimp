begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelpui.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_typedef
DECL|typedef|GimpHelpFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHelpFunc
function_decl|)
parameter_list|(
name|gchar
modifier|*
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|void
name|gimp_help_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
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
comment|/*  connect the "F1" accelerator of a window  */
end_comment

begin_function_decl
name|void
name|gimp_help_connect_help_accel
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
name|gchar
modifier|*
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
name|gchar
modifier|*
name|tool_tip
parameter_list|,
name|gchar
modifier|*
name|help_data
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
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HELP_UI_H__ */
end_comment

end_unit

