begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_NOTEBOOK_H__
end_ifndef

begin_define
DECL|macro|__COLOR_NOTEBOOK_H__
define|#
directive|define
name|__COLOR_NOTEBOOK_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon296d34590103
block|{
DECL|enumerator|COLOR_NOTEBOOK_OK
name|COLOR_NOTEBOOK_OK
block|,
DECL|enumerator|COLOR_NOTEBOOK_CANCEL
name|COLOR_NOTEBOOK_CANCEL
block|,
DECL|enumerator|COLOR_NOTEBOOK_UPDATE
name|COLOR_NOTEBOOK_UPDATE
DECL|typedef|ColorNotebookState
block|}
name|ColorNotebookState
typedef|;
end_typedef

begin_typedef
DECL|typedef|ColorNotebookCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|ColorNotebookCallback
function_decl|)
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|ColorNotebookState
name|state
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ColorSelectorInstance
typedef|typedef
name|struct
name|_ColorSelectorInstance
name|ColorSelectorInstance
typedef|;
end_typedef

begin_function_decl
name|ColorNotebook
modifier|*
name|color_notebook_new
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|ColorNotebookCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gboolean
name|wants_update
parameter_list|,
name|gboolean
name|show_aplha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_notebook_show
parameter_list|(
name|ColorNotebook
modifier|*
name|cnb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_notebook_hide
parameter_list|(
name|ColorNotebook
modifier|*
name|cnb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_notebook_free
parameter_list|(
name|ColorNotebook
modifier|*
name|cnb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_notebook_set_color
parameter_list|(
name|ColorNotebook
modifier|*
name|cnb
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __COLOR_NOTEBOOK_H__ */
end_comment

end_unit

