begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorselect.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on color_notebook module  * Copyright (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_SELECT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_SELECT_H__
define|#
directive|define
name|__GIMP_COLOR_SELECT_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
DECL|macro|GIMP_TYPE_COLOR_SELECT
define|#
directive|define
name|GIMP_TYPE_COLOR_SELECT
value|(gimp_color_select_get_type ())
DECL|macro|GIMP_COLOR_SELECT (obj)
define|#
directive|define
name|GIMP_COLOR_SELECT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_SELECT, GimpColorSelect))
DECL|macro|GIMP_IS_COLOR_SELECT (obj)
define|#
directive|define
name|GIMP_IS_COLOR_SELECT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_SELECT))
name|GType
name|gimp_color_select_get_type
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
comment|/* __GIMP_COLOR_SELECT_H__ */
end_comment

end_unit

