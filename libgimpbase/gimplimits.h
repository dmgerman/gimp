begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball  *  * gimplimits.h  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LIMITS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LIMITS_H__
define|#
directive|define
name|__GIMP_LIMITS_H__
end_define

begin_comment
comment|/*  pixel sizes  */
end_comment

begin_define
DECL|macro|GIMP_MIN_IMAGE_SIZE
define|#
directive|define
name|GIMP_MIN_IMAGE_SIZE
value|1
end_define

begin_define
DECL|macro|GIMP_MAX_IMAGE_SIZE
define|#
directive|define
name|GIMP_MAX_IMAGE_SIZE
value|262144
end_define

begin_comment
DECL|macro|GIMP_MAX_IMAGE_SIZE
comment|/*  2^18  */
end_comment

begin_comment
comment|/*  dots per inch  */
end_comment

begin_define
DECL|macro|GIMP_MIN_RESOLUTION
define|#
directive|define
name|GIMP_MIN_RESOLUTION
value|5e-3
end_define

begin_comment
DECL|macro|GIMP_MIN_RESOLUTION
comment|/*  shouldn't display as 0.000  */
end_comment

begin_define
DECL|macro|GIMP_MAX_RESOLUTION
define|#
directive|define
name|GIMP_MAX_RESOLUTION
value|65536.0
end_define

begin_comment
comment|/*  memory sizes  */
end_comment

begin_define
DECL|macro|GIMP_MAX_MEMSIZE
define|#
directive|define
name|GIMP_MAX_MEMSIZE
value|((guint64) 1<< 42)
end_define

begin_comment
DECL|macro|GIMP_MAX_MEMSIZE
comment|/*  4 terabyte;                                         *  needs a 64bit variable                                         *  and must be< G_MAXDOUBLE                                         */
end_comment

begin_comment
comment|/*  the size of the checks which indicate transparency...  */
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
comment|/*  ...and their colors  */
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LIMITS_H__ */
end_comment

end_unit

