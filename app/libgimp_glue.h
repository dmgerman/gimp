begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LIBGIMP_GLUE_H__
end_ifndef

begin_define
DECL|macro|__LIBGIMP_GLUE_H__
define|#
directive|define
name|__LIBGIMP_GLUE_H__
end_define

begin_comment
comment|/*  This files lets various libgimp files link against the application.  *  *  NEVER include this header, it's only here for documentation.  */
end_comment

begin_function_decl
name|gboolean
name|gimp_palette_set_foreground
parameter_list|(
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_get_foreground
parameter_list|(
name|guchar
modifier|*
name|r
parameter_list|,
name|guchar
modifier|*
name|g
parameter_list|,
name|guchar
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_set_foreground_rgb
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_get_foreground_rgb
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_set_background
parameter_list|(
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_get_background
parameter_list|(
name|guchar
modifier|*
name|r
parameter_list|,
name|guchar
modifier|*
name|g
parameter_list|,
name|guchar
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_set_background_rgb
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_palette_get_background_rgb
parameter_list|(
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LIBGIMP_GLUE_H__ */
end_comment

end_unit

