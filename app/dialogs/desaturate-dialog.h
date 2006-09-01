begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DESATURATE_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__DESATURATE_DIALOG_H__
define|#
directive|define
name|__DESATURATE_DIALOG_H__
end_define

begin_typedef
DECL|typedef|DesaturateDialog
typedef|typedef
name|struct
name|_DesaturateDialog
name|DesaturateDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_DesaturateDialog
struct|struct
name|_DesaturateDialog
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|mode
name|GimpDesaturateMode
name|mode
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|DesaturateDialog
modifier|*
name|desaturate_dialog_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpDesaturateMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DESATURATE_DIALOG_H__ */
end_comment

end_unit

