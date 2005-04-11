begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* base64.h - encode and decode base64 encoding according to RFC 1521  *  * Copyright (C) 2005, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|BASE64_H
end_ifndef

begin_define
DECL|macro|BASE64_H
define|#
directive|define
name|BASE64_H
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_function_decl
name|G_BEGIN_DECLS
name|gssize
name|base64_decode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src_b64
parameter_list|,
name|gsize
name|src_size
parameter_list|,
name|gchar
modifier|*
name|dest
parameter_list|,
name|gsize
name|dest_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gssize
name|base64_encode
parameter_list|(
specifier|const
name|gchar
modifier|*
name|src
parameter_list|,
name|gsize
name|src_size
parameter_list|,
name|gchar
modifier|*
name|dest_b64
parameter_list|,
name|gsize
name|dest_size
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* BASE64_H */
end_comment

end_unit

