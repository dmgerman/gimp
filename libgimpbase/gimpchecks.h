begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHECKS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHECKS_H__
define|#
directive|define
name|__GIMP_CHECKS_H__
end_define

begin_comment
comment|/*  the default size of the checks which indicate transparency ...  */
end_comment

begin_define
DECL|macro|GIMP_CHECK_SIZE
define|#
directive|define
name|GIMP_CHECK_SIZE
value|8
end_define

begin_define
DECL|macro|GIMP_CHECK_SIZE_SM
define|#
directive|define
name|GIMP_CHECK_SIZE_SM
value|4
end_define

begin_comment
comment|/*  ... and their default shades  */
end_comment

begin_define
DECL|macro|GIMP_CHECK_DARK
define|#
directive|define
name|GIMP_CHECK_DARK
value|0.4
end_define

begin_define
DECL|macro|GIMP_CHECK_LIGHT
define|#
directive|define
name|GIMP_CHECK_LIGHT
value|0.6
end_define

begin_function_decl
name|void
name|gimp_checks_get_shades
parameter_list|(
name|GimpCheckType
name|type
parameter_list|,
name|guchar
modifier|*
name|light
parameter_list|,
name|guchar
modifier|*
name|dark
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CHECKS_H__ */
end_comment

end_unit

