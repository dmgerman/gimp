begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwin32-io.h  * Compatibilty defines, you mostly need this as unistd.h replacement  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WIN32_IO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIN32_IO_H__
define|#
directive|define
name|__GIMP_WIN32_IO_H__
end_define

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_include
include|#
directive|include
file|<direct.h>
end_include

begin_expr_stmt
name|G_BEGIN_DECLS
DECL|macro|mkdir (n,a)
define|#
directive|define
name|mkdir
parameter_list|(
name|n
parameter_list|,
name|a
parameter_list|)
value|_mkdir(n)
DECL|macro|chmod (n,f)
define|#
directive|define
name|chmod
parameter_list|(
name|n
parameter_list|,
name|f
parameter_list|)
value|_chmod(n,f)
DECL|macro|access (f,p)
define|#
directive|define
name|access
parameter_list|(
name|f
parameter_list|,
name|p
parameter_list|)
value|_access(f,p)
ifndef|#
directive|ifndef
name|S_ISREG
DECL|macro|S_ISREG (m)
define|#
directive|define
name|S_ISREG
parameter_list|(
name|m
parameter_list|)
value|(((m)& _S_IFMT) == _S_IFREG)
endif|#
directive|endif
ifndef|#
directive|ifndef
name|S_ISDIR
DECL|macro|S_ISDIR (m)
define|#
directive|define
name|S_ISDIR
parameter_list|(
name|m
parameter_list|)
value|(((m)& _S_IFMT) == _S_IFDIR)
endif|#
directive|endif
ifndef|#
directive|ifndef
name|S_IRUSR
DECL|macro|S_IRUSR
define|#
directive|define
name|S_IRUSR
value|_S_IREAD
endif|#
directive|endif
ifndef|#
directive|ifndef
name|S_IWUSR
DECL|macro|S_IWUSR
define|#
directive|define
name|S_IWUSR
value|_S_IWRITE
endif|#
directive|endif
ifndef|#
directive|ifndef
name|S_IXUSR
DECL|macro|S_IXUSR
define|#
directive|define
name|S_IXUSR
value|_S_IEXEC
endif|#
directive|endif
ifndef|#
directive|ifndef
name|_O_BINARY
DECL|macro|_O_BINARY
define|#
directive|define
name|_O_BINARY
value|0
endif|#
directive|endif
ifndef|#
directive|ifndef
name|_O_TEMPORARY
DECL|macro|_O_TEMPORARY
define|#
directive|define
name|_O_TEMPORARY
value|0
endif|#
directive|endif
ifndef|#
directive|ifndef
name|F_OK
DECL|macro|F_OK
define|#
directive|define
name|F_OK
value|0
endif|#
directive|endif
ifndef|#
directive|ifndef
name|W_OK
DECL|macro|W_OK
define|#
directive|define
name|W_OK
value|2
endif|#
directive|endif
ifndef|#
directive|ifndef
name|R_OK
DECL|macro|R_OK
define|#
directive|define
name|R_OK
value|4
endif|#
directive|endif
ifndef|#
directive|ifndef
name|X_OK
DECL|macro|X_OK
define|#
directive|define
name|X_OK
value|0
comment|/* not really */
endif|#
directive|endif
name|G_END_DECLS
end_expr_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WIN32_IO_H__ */
end_comment

end_unit

