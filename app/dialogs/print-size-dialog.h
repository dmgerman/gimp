begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PRINT_SIZE_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__PRINT_SIZE_DIALOG_H__
define|#
directive|define
name|__PRINT_SIZE_DIALOG_H__
end_define

begin_typedef
DECL|typedef|GimpResolutionCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpResolutionCallback
function_decl|)
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|,
name|GimpUnit
name|resolution_unit
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|print_size_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|role
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpResolutionCallback
name|callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __PRINT_SIZE_DIALOG_H__  */
end_comment

end_unit

