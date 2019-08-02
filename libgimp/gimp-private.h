begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp-private.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PRIVATE_H__
define|#
directive|define
name|__GIMP_PRIVATE_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
include|#
directive|include
file|"libgimpbase/gimpwire.h"
specifier|extern
name|GIOChannel
modifier|*
name|_gimp_readchannel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GIOChannel
modifier|*
name|_gimp_writechannel
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|_gimp_config
parameter_list|(
name|GPConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_loop
parameter_list|(
name|GimpRunProc
name|run_proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_read_expect_msg
parameter_list|(
name|GimpWireMessage
modifier|*
name|msg
parameter_list|,
name|gint
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_process_message
parameter_list|(
name|GimpWireMessage
modifier|*
name|msg
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
comment|/* __GIMP_PRIVATE_H__ */
end_comment

end_unit

