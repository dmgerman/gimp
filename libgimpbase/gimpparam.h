begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PARAM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PARAM_H__
define|#
directive|define
name|__GIMP_PARAM_H__
end_define

begin_comment
comment|/**  * SECTION: gimpparam  * @title: gimpparam  * @short_description: Definitions of useful #GParamFlags.  *  * Definitions of useful #GParamFlags.  **/
end_comment

begin_comment
comment|/**  * GIMP_PARAM_STATIC_STRINGS:  *  * Since: GIMP 2.4  **/
end_comment

begin_define
DECL|macro|GIMP_PARAM_STATIC_STRINGS
define|#
directive|define
name|GIMP_PARAM_STATIC_STRINGS
value|(G_PARAM_STATIC_NAME | \                                    G_PARAM_STATIC_NICK | \                                    G_PARAM_STATIC_BLURB)
end_define

begin_comment
comment|/**  * GIMP_PARAM_READABLE:  *  * Since: GIMP 2.4  **/
end_comment

begin_define
DECL|macro|GIMP_PARAM_READABLE
define|#
directive|define
name|GIMP_PARAM_READABLE
value|(G_PARAM_READABLE    | \                                    GIMP_PARAM_STATIC_STRINGS)
end_define

begin_comment
comment|/**  * GIMP_PARAM_WRITABLE:  *  * Since: GIMP 2.4  **/
end_comment

begin_define
DECL|macro|GIMP_PARAM_WRITABLE
define|#
directive|define
name|GIMP_PARAM_WRITABLE
value|(G_PARAM_WRITABLE    | \                                    GIMP_PARAM_STATIC_STRINGS)
end_define

begin_comment
comment|/**  * GIMP_PARAM_READWRITE:  *  * Since: GIMP 2.4  **/
end_comment

begin_define
DECL|macro|GIMP_PARAM_READWRITE
define|#
directive|define
name|GIMP_PARAM_READWRITE
value|(G_PARAM_READWRITE   | \                                    GIMP_PARAM_STATIC_STRINGS)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PARAM_H__  */
end_comment

end_unit

