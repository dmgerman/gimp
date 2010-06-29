begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  *  * $Revision$  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_define
DECL|macro|_GNU_SOURCE
define|#
directive|define
name|_GNU_SOURCE
end_define

begin_comment
DECL|macro|_GNU_SOURCE
comment|/* for the sigaction stuff */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_comment
comment|/**  * SECTION: gimpsignal  * @title: gimpsignal  * @short_description: Portable signal handling.  * @see_also: signal(2), signal(5 or 7), sigaction(2).  *  * Portable signal handling.  **/
end_comment

begin_comment
comment|/* Courtesy of Austin Donnelly 06-04-2000 to address bug #2742 */
end_comment

begin_comment
comment|/**  * gimp_signal_private:  * @signum: Selects signal to be handled see man 5 signal (or man 7 signal)  * @handler: Handler that maps to signum. Invoked by O/S.  *           Handler gets signal that caused invocation. Corresponds  *           to the @sa_handler field of the @sigaction struct.  * @flags: Preferences. OR'ed SA_&lt;xxx&gt;. See man sigaction. Corresponds  *         to the @sa_flags field of the @sigaction struct.  *  * This function furnishes a workalike for signal(2) but  * which internally invokes sigaction(2) after certain  * sa_flags are set; these primarily to ensure restarting  * of interrupted system calls. See sigaction(2)  It is a  * aid to transition and not new development: that effort  * should employ sigaction directly. [gosgood 18.04.2000]  *  * Cause @handler to be run when @signum is delivered.  We  * use sigaction(2) rather than signal(2) so that we can control the  * signal handler's environment completely via @flags: some signal(2)  * implementations differ in their sematics, so we need to nail down  * exactly what we want. [austin 06.04.2000]  *  * Returns: A reference to the signal handling function which was  *          active before the call to gimp_signal_private().  */
end_comment

begin_function
name|GimpSignalHandlerFunc
DECL|function|gimp_signal_private (gint signum,GimpSignalHandlerFunc handler,gint flags)
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
block|{
ifndef|#
directive|ifndef
name|G_OS_WIN32
name|gint
name|ret
decl_stmt|;
name|struct
name|sigaction
name|sa
decl_stmt|;
name|struct
name|sigaction
name|osa
decl_stmt|;
comment|/*  The sa_handler (mandated by POSIX.1) and sa_sigaction (a    *  common extension) are often implemented by the OS as members    *  of a union.  This means you CAN NOT set both, you set one or    *  the other.  Caveat programmer!    */
comment|/*  Passing gimp_signal_private a gimp_sighandler of NULL is not    *  an error, and generally results in the action for that signal    *  being set to SIG_DFL (default behavior).  Many OSes define    *  SIG_DFL as (void (*)()0, so setting sa_handler to NULL is    *  the same thing as passing SIG_DFL to it.    */
name|sa
operator|.
name|sa_handler
operator|=
name|handler
expr_stmt|;
comment|/*  Mask all signals while handler runs to avoid re-entrancy    *  problems.    */
name|sigfillset
argument_list|(
operator|&
name|sa
operator|.
name|sa_mask
argument_list|)
expr_stmt|;
name|sa
operator|.
name|sa_flags
operator|=
name|flags
expr_stmt|;
name|ret
operator|=
name|sigaction
argument_list|(
name|signum
argument_list|,
operator|&
name|sa
argument_list|,
operator|&
name|osa
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret
operator|<
literal|0
condition|)
name|g_error
argument_list|(
literal|"unable to set handler for signal %d\n"
argument_list|,
name|signum
argument_list|)
expr_stmt|;
return|return
operator|(
name|GimpSignalHandlerFunc
operator|)
name|osa
operator|.
name|sa_handler
return|;
else|#
directive|else
return|return
name|NULL
return|;
comment|/* Or g_error()? Should all calls to                                  * this function really be inside                                  * #ifdef G_OS_UNIX?                                  */
endif|#
directive|endif
block|}
end_function

end_unit

