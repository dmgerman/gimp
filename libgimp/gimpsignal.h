begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  *  *  $Revision$  */
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

begin_comment
comment|/* A gimp-level interface to a Posix.1-compliant signal package lives here  * For 1.2, this gimp-level interface mostly passes through to posix calls  * without modification. Certain calls manipulate struct sigaction in  * ways useful to Gimp.  */
end_comment

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__EMX__
end_ifdef

begin_comment
comment|/* hope this is right for OS/2 */
end_comment

begin_define
DECL|macro|SA_RESTART
define|#
directive|define
name|SA_RESTART
value|SA_SYSV
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GimpSignalHandlerFunc is a reference to a (signal handler) function   * that takes a signal ID and returns void.   * signal(2) returns such references; so does gimp_signal_private.  */
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

begin_comment
comment|/* Internal implementation that can be DEFINEd into various flavors of  * signal(2) lookalikes.  */
end_comment

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

begin_comment
comment|/* the gimp_signal_syscallrestart() lookalike looks like signal(2) but  * quietly requests the restarting of system calls. Addresses #2742  */
end_comment

begin_define
DECL|macro|gimp_signal_syscallrestart (signum,handler)
define|#
directive|define
name|gimp_signal_syscallrestart
parameter_list|(
name|signum
parameter_list|,
name|handler
parameter_list|)
value|gimp_signal_private ((signum), (handler), SA_RESTART)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SIGNAL_H__ */
end_comment

end_unit

