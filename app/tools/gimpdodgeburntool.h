begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DODGEBURN_H__
end_ifndef

begin_define
DECL|macro|__DODGEBURN_H__
define|#
directive|define
name|__DODGEBURN_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29fb5a510103
block|{
DECL|enumerator|DODGE
name|DODGE
block|,
DECL|enumerator|BURN
name|BURN
DECL|typedef|DodgeBurnType
block|}
name|DodgeBurnType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29fb5a510203
block|{
DECL|enumerator|DODGEBURN_HIGHLIGHTS
name|DODGEBURN_HIGHLIGHTS
block|,
DECL|enumerator|DODGEBURN_MIDTONES
name|DODGEBURN_MIDTONES
block|,
DECL|enumerator|DODGEBURN_SHADOWS
name|DODGEBURN_SHADOWS
DECL|typedef|DodgeBurnMode
block|}
name|DodgeBurnMode
typedef|;
end_typedef

begin_function_decl
name|gboolean
name|dodgeburn_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|exposure
parameter_list|,
name|DodgeBurnType
name|type
parameter_list|,
name|DodgeBurnMode
name|mode
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
name|gdouble
modifier|*
name|stroke_array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|dodgeburn_non_gui_default
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
name|gdouble
modifier|*
name|stroke_array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Tool
modifier|*
name|tools_new_dodgeburn
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_dodgeburn
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __DODGEBURN_H__  */
end_comment

end_unit

