begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpdisplay_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_PDB_H__
define|#
directive|define
name|__GIMP_DISPLAY_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_display_is_valid
parameter_list|(
name|gint32
name|display_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_display_new
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_display_delete
parameter_list|(
name|gint32
name|display_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_display_get_window_handle
parameter_list|(
name|gint32
name|display_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_displays_flush
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_displays_reconnect
parameter_list|(
name|gint32
name|old_image_ID
parameter_list|,
name|gint32
name|new_image_ID
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
comment|/* __GIMP_DISPLAY_PDB_H__ */
end_comment

end_unit

