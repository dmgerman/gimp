begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpparasiteP.h  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PARASITE_P_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PARASITE_P_H__
define|#
directive|define
name|__GIMP_PARASITE_P_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|struct|_GimpParasite
struct|struct
name|_GimpParasite
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* The name of the parasite. USE A UNIQUE PREFIX! */
DECL|member|flags
name|guint32
name|flags
decl_stmt|;
comment|/* save Parasite in XCF file, etc.                */
DECL|member|size
name|guint32
name|size
decl_stmt|;
comment|/* amount of data                                 */
DECL|member|data
name|gpointer
name|data
decl_stmt|;
comment|/* a pointer to the data.  plugin is              * 			 * responsible for tracking byte order            */
block|}
struct|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PARASITE_P_H__ */
end_comment

end_unit

