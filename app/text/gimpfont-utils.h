begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfont-utils.h  * Copyright (C) 2005 Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FONT_UTILS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FONT_UTILS_H__
define|#
directive|define
name|__GIMP_FONT_UTILS_H__
end_define

begin_comment
comment|/* This is solely to workaround pango bug #166540, by tacking on a ',' to  * font names that end in numbers, so pango_font_description_from_string  * doesn't interpret it as a size. Note that this doesn't fully workaround  * problems pango has with font name serialization, just only the bad size  * interpretation. Family names that end with style names are still  * processed wrongly.  */
end_comment

begin_function_decl
name|gchar
modifier|*
name|gimp_font_util_pango_font_description_to_string
parameter_list|(
specifier|const
name|PangoFontDescription
modifier|*
name|desc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_FONT_UTILS_H__  */
end_comment

end_unit

