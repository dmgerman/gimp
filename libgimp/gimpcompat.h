begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcompat.h  * Compatibility defines to ease migration from the GIMP-1.2 API  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPAT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPAT_H__
define|#
directive|define
name|__GIMP_COMPAT_H__
end_define

begin_expr_stmt
name|G_BEGIN_DECLS
comment|/* This file contains aliases that are kept for historical  * reasons, because a wide code base depends on them.  *  * These defines will be removed in the next development cycle.   */
DECL|macro|GimpRunModeType
define|#
directive|define
name|GimpRunModeType
value|GimpRunMode
name|G_END_DECLS
end_expr_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COMPAT_H__ */
end_comment

end_unit

