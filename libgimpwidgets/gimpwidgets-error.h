begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgets-error.h  * Copyright (C) 2008  Martin Nordholts<martinn@svn.gnome.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WIDGETS_ERROR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIDGETS_ERROR_H__
define|#
directive|define
name|__GIMP_WIDGETS_ERROR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon289d292d0103
block|{
DECL|enumerator|GIMP_WIDGETS_PARSE_ERROR
name|GIMP_WIDGETS_PARSE_ERROR
DECL|typedef|GimpWidgetsError
block|}
name|GimpWidgetsError
typedef|;
end_typedef

begin_comment
comment|/**  * GIMP_WIDGETS_ERROR:  *  * The GIMP widgets error domain.  *  * Since: GIMP 2.8  */
end_comment

begin_define
DECL|macro|GIMP_WIDGETS_ERROR
define|#
directive|define
name|GIMP_WIDGETS_ERROR
value|(gimp_widgets_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_widgets_error_quark
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
comment|/* __GIMP_WIDGETS_ERROR_H__ */
end_comment

end_unit

