begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EDIT_SELECTION_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EDIT_SELECTION_TOOL_H__
define|#
directive|define
name|__GIMP_EDIT_SELECTION_TOOL_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a2269090103
block|{
DECL|enumerator|EDIT_MASK_TRANSLATE
name|EDIT_MASK_TRANSLATE
block|,
DECL|enumerator|EDIT_MASK_TO_LAYER_TRANSLATE
name|EDIT_MASK_TO_LAYER_TRANSLATE
block|,
DECL|enumerator|EDIT_LAYER_TRANSLATE
name|EDIT_LAYER_TRANSLATE
block|,
DECL|enumerator|EDIT_FLOATING_SEL_TRANSLATE
name|EDIT_FLOATING_SEL_TRANSLATE
DECL|typedef|EditType
block|}
name|EditType
typedef|;
end_typedef

begin_function_decl
name|void
name|init_edit_selection
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|EditType
name|edit_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_EDIT_SELECTION_TOOL_H__  */
end_comment

end_unit

