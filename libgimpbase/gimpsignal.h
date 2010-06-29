begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SIGNAL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SIGNAL_H__
define|#
directive|define
name|__GIMP_SIGNAL_H__
end_define

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * GimpSignalHandlerFunc:  * @signum: The number of the signal. Useful if different signals are  *          handled by a single handler.  *  * A prototype for a reference to a signal handler functions. Note  * that each function which takes or returns a variable of this type  * also accepts or may return special values defined by your system's  * signal.h header file (like @SIG_DFL or @SIG_IGN).  **/
end_comment

begin_typedef
DECL|typedef|GimpSignalHandlerFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSignalHandlerFunc
function_decl|)
parameter_list|(
name|gint
name|signum
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|GimpSignalHandlerFunc
name|gimp_signal_private
parameter_list|(
name|gint
name|signum
parameter_list|,
name|GimpSignalHandlerFunc
name|handler
parameter_list|,
name|gint
name|flags
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
comment|/* __GIMP_SIGNAL_H__ */
end_comment

end_unit

