begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfontselect.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FONT_SELECT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FONT_SELECT_H__
define|#
directive|define
name|__GIMP_FONT_SELECT_H__
end_define

begin_include
include|#
directive|include
file|"gimppdbdialog.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_FONT_SELECT
define|#
directive|define
name|GIMP_TYPE_FONT_SELECT
value|(gimp_font_select_get_type ())
end_define

begin_define
DECL|macro|GIMP_FONT_SELECT (obj)
define|#
directive|define
name|GIMP_FONT_SELECT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FONT_SELECT, GimpFontSelect))
end_define

begin_define
DECL|macro|GIMP_FONT_SELECT_CLASS (klass)
define|#
directive|define
name|GIMP_FONT_SELECT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FONT_SELECT, GimpFontSelectClass))
end_define

begin_define
DECL|macro|GIMP_IS_FONT_SELECT (obj)
define|#
directive|define
name|GIMP_IS_FONT_SELECT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FONT_SELECT))
end_define

begin_define
DECL|macro|GIMP_IS_FONT_SELECT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FONT_SELECT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FONT_SELECT))
end_define

begin_define
DECL|macro|GIMP_FONT_SELECT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FONT_SELECT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FONT_SELECT, GimpFontSelectClass))
end_define

begin_typedef
DECL|typedef|GimpFontSelectClass
typedef|typedef
name|struct
name|_GimpFontSelectClass
name|GimpFontSelectClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFontSelect
struct|struct
name|_GimpFontSelect
block|{
DECL|member|parent_instance
name|GimpPdbDialog
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFontSelectClass
struct|struct
name|_GimpFontSelectClass
block|{
DECL|member|parent_class
name|GimpPdbDialogClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_font_select_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FONT_SELECT_H__ */
end_comment

end_unit

