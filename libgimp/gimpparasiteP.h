begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasiteP.h  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_PARASITEP_H_
end_ifndef

begin_define
DECL|macro|_PARASITEP_H_
define|#
directive|define
name|_PARASITEP_H_
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_struct
DECL|struct|_Parasite
struct|struct
name|_Parasite
block|{
DECL|member|name
name|char
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
name|void
modifier|*
name|data
decl_stmt|;
comment|/* a pointer to the data.  plugin is              * 			 * responsible for tracking byte order            */
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _PARASITEP_H_ */
end_comment

end_unit

