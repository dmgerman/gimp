begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SMUDGE_H__
end_ifndef

begin_define
DECL|macro|__SMUDGE_H__
define|#
directive|define
name|__SMUDGE_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a11abf40103
block|{
DECL|enumerator|SMUDGE_TYPE_SMUDGE
name|SMUDGE_TYPE_SMUDGE
block|,
DECL|enumerator|SMUDGE_TYPE_STREAK
name|SMUDGE_TYPE_STREAK
DECL|typedef|SmudgeType
block|}
name|SmudgeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2a11abf40203
block|{
DECL|enumerator|SMUDGE_MODE_HIGHLIGHTS
name|SMUDGE_MODE_HIGHLIGHTS
block|,
DECL|enumerator|SMUDGE_MODE_MIDTONES
name|SMUDGE_MODE_MIDTONES
block|,
DECL|enumerator|SMUDGE_MODE_SHADOWS
name|SMUDGE_MODE_SHADOWS
DECL|typedef|SmudgeMode
block|}
name|SmudgeMode
typedef|;
end_typedef

begin_function_decl
name|gboolean
name|smudge_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|rate
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
name|smudge_non_gui_default
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
name|tools_new_smudge
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_free_smudge
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
comment|/*  __SMUDGE_H__  */
end_comment

end_unit

