begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  *  * $Revision$  */
end_comment

begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_comment
comment|/**   * gimp_signal:   * @signum:   selects signal to be handled see man 5 signal  * @handler:  handler that maps to signum. Invoked by O/S.   *            handler gets signal that caused invocation.   * @sa_flags: preferences. OR'ed SA_<xxx>. See signal.h   *  * This function furnishes a workalike for signal(2) but  * which internally invokes sigaction(2) after certain  * sa_flags are set; these primarily to ensure restarting  * of interrupted system calls. See sigaction(2)  It is a   * aid to transition and not new development: that effort   * should employ sigaction directly. [<gosgood@idt.net> 18.04.2000]   *  * Cause handler to be run when signum is delivered.  We  * use sigaction(2) rather than signal(2) so that we can control the  * signal hander's environment completely via sa_flags: some signal(2)  * implementations differ in their sematics, so we need to nail down  * exactly what we want. [<austin@gimp.org> 06.04.2000]  *  * Returns: RetSigType (a reference to a signal handling function)    *  */
end_comment

begin_comment
comment|/* Courtesy of Austin Donnelly 06-04-2000 to address bug #2742 */
end_comment

begin_function
name|RetSigType
DECL|function|gimp_signal_private (gint signum,void (* gimp_sighandler)(int),gint sa_flags)
name|gimp_signal_private
parameter_list|(
name|gint
name|signum
parameter_list|,
name|void
function_decl|(
modifier|*
name|gimp_sighandler
function_decl|)
parameter_list|(
name|int
parameter_list|)
parameter_list|,
name|gint
name|sa_flags
parameter_list|)
block|{
name|int
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
comment|/* this field is a union of sa_sighandler.sa_sighandler1 and */
comment|/* sa_sigaction1 - don't set both at once...                 */
name|sa
operator|.
name|sa_handler
operator|=
name|gimp_sighandler
expr_stmt|;
comment|/* Mask all signals while handler runs to avoid re-entrancy    * problems. */
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
name|sa_flags
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
name|gimp_fatal_error
argument_list|(
literal|"unable to set handler for signal %d\n"
argument_list|,
name|signum
argument_list|)
expr_stmt|;
return|return
name|osa
operator|.
name|sa_handler
return|;
block|}
end_function

end_unit

