begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfont.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *                    Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FONT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FONT_H__
define|#
directive|define
name|__GIMP_FONT_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpdata.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FONT
define|#
directive|define
name|GIMP_TYPE_FONT
value|(gimp_font_get_type ())
end_define

begin_define
DECL|macro|GIMP_FONT (obj)
define|#
directive|define
name|GIMP_FONT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FONT, GimpFont))
end_define

begin_define
DECL|macro|GIMP_FONT_CLASS (klass)
define|#
directive|define
name|GIMP_FONT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FONT, GimpFontClass))
end_define

begin_define
DECL|macro|GIMP_IS_FONT (obj)
define|#
directive|define
name|GIMP_IS_FONT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FONT))
end_define

begin_define
DECL|macro|GIMP_IS_FONT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FONT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FONT))
end_define

begin_define
DECL|macro|GIMP_FONT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FONT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FONT, GimpFontClass))
end_define

begin_typedef
DECL|typedef|GimpFontClass
typedef|typedef
name|struct
name|_GimpFontClass
name|GimpFontClass
typedef|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_font_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpFont
modifier|*
name|gimp_font_get_standard
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FONT_H__ */
end_comment

end_unit

