begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_CIRCLE_H
end_ifndef

begin_define
DECL|macro|_IMAP_CIRCLE_H
define|#
directive|define
name|_IMAP_CIRCLE_H
end_define

begin_include
include|#
directive|include
file|"imap_object.h"
end_include

begin_typedef
DECL|struct|__anon29d00e650108
typedef|typedef
struct|struct
block|{
DECL|member|obj
name|Object_t
name|obj
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|r
name|gint
name|r
decl_stmt|;
DECL|typedef|Circle_t
block|}
name|Circle_t
typedef|;
end_typedef

begin_define
DECL|macro|ObjectToCircle (obj)
define|#
directive|define
name|ObjectToCircle
parameter_list|(
name|obj
parameter_list|)
value|((Circle_t*) (obj))
end_define

begin_function_decl
name|Object_t
modifier|*
name|create_circle
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ObjectFactory_t
modifier|*
name|get_circle_factory
parameter_list|(
name|guint
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_CIRCLE_H */
end_comment

end_unit

