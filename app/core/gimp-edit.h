begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_EDIT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_EDIT_H__
define|#
directive|define
name|__GIMP_EDIT_H__
end_define

begin_function_decl
specifier|const
name|GimpBuffer
modifier|*
name|gimp_edit_cut
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpBuffer
modifier|*
name|gimp_edit_copy
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpBuffer
modifier|*
name|gimp_edit_copy_visible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_edit_paste
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBuffer
modifier|*
name|paste
parameter_list|,
name|gboolean
name|paste_into
parameter_list|,
name|gint
name|viewport_x
parameter_list|,
name|gint
name|viewport_y
parameter_list|,
name|gint
name|viewport_width
parameter_list|,
name|gint
name|viewport_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_edit_paste_as_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpBuffer
modifier|*
name|paste
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_edit_named_cut
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_edit_named_copy
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_edit_named_copy_visible
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_edit_clear
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_edit_fill
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpFillType
name|fill_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_edit_fade
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_EDIT_H__  */
end_comment

end_unit

