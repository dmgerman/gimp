begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpfontselection-dialog.h  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FONT_SELECTION_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FONT_SELECTION_DIALOG_H__
define|#
directive|define
name|__GIMP_FONT_SELECTION_DIALOG_H__
end_define

begin_function_decl
name|GimpFontSelectionDialog
modifier|*
name|gimp_font_selection_dialog_new
parameter_list|(
name|GimpFontSelection
modifier|*
name|fontsel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_font_selection_dialog_destroy
parameter_list|(
name|GimpFontSelectionDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_font_selection_dialog_show
parameter_list|(
name|GimpFontSelectionDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_font_selection_dialog_set_font_desc
parameter_list|(
name|GimpFontSelectionDialog
modifier|*
name|dialog
parameter_list|,
name|PangoFontDescription
modifier|*
name|new_desc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FONT_SELECTION_DIALOG_H__ */
end_comment

end_unit

