begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1999 Peter Mattis and Spencer Kimball                  *  * gimplimits.h  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
value|65536
end_define

begin_comment
comment|/*  dots per inch  */
end_comment

begin_define
DECL|macro|GIMP_MIN_RESOLUTION
define|#
directive|define
name|GIMP_MIN_RESOLUTION
value|(1.0 / 65536.0)
end_define

begin_define
DECL|macro|GIMP_MAX_RESOLUTION
define|#
directive|define
name|GIMP_MAX_RESOLUTION
value|65536.0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LIMITS_H__ */
end_comment

end_unit

