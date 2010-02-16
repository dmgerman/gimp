begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CLIPBOARD_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CLIPBOARD_H__
define|#
directive|define
name|__GIMP_CLIPBOARD_H__
end_define

begin_function_decl
name|void
name|gimp_clipboard_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_clipboard_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_clipboard_has_buffer
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_clipboard_has_svg
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_clipboard_has_curve
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBuffer
modifier|*
name|gimp_clipboard_get_buffer
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_clipboard_get_svg
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gsize
modifier|*
name|svg_length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCurve
modifier|*
name|gimp_clipboard_get_curve
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_clipboard_set_buffer
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_clipboard_set_svg
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|svg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_clipboard_set_text
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_clipboard_set_curve
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpCurve
modifier|*
name|curve
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CLIPBOARD_H__ */
end_comment

end_unit

