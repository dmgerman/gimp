begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* xmp-encode.h - generate XMP metadata from the tree model  *  * Copyright (C) 2005, RaphaÃ«l Quinet<raphael@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|XMP_ENCODE_H
end_ifndef

begin_define
DECL|macro|XMP_ENCODE_H
define|#
directive|define
name|XMP_ENCODE_H
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"xmp-schemas.h"
end_include

begin_include
include|#
directive|include
file|"xmp-model.h"
end_include

begin_function_decl
name|G_BEGIN_DECLS
name|void
name|xmp_generate_packet
parameter_list|(
name|XMPModel
modifier|*
name|xmp_model
parameter_list|,
name|GString
modifier|*
name|buffer
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
comment|/* XMP_ENCODE_H */
end_comment

end_unit

