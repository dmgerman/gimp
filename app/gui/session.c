begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Session-managment stuff   Copyright (C) 1998 Sven Neumann<sven@gimp.org>     I include a short description here on what is done and what problems     are left:     Since everything saved in sessionrc changes often (with each session?)     the whole file is rewritten each time the gimp exits. I don't see any    use in implementing a more flexible scheme like it is used for gimprc.     Right now session-managment is limited to window geometry. Restoring     openend images is planned, but I'm still not sure how to deal with dirty    images.     Dialogs are now reopened if the gimp is called with the command-line-option    --restore-session or if the related entry is set in gimprc.    Probably there should alternatively be a list of dialogs in the preferences     that should always be opened on start-up.      Please point me into the right direction to make this work with Gnome-SM.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"color-notebook.h"
end_include

begin_include
include|#
directive|include
file|"session.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|session_init (Gimp * gimp)
name|session_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"sessionrc"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimprc_parse_file
argument_list|(
name|filename
argument_list|)
condition|)
block|{
comment|/*  always show L&C&P, Tool Options and Brushes on first invocation  */
comment|/* TODO */
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|session_restore (Gimp * gimp)
name|session_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_dialog_factories_session_restore
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|session_save (Gimp * gimp)
name|session_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"sessionrc"
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"wt"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
return|return;
name|fprintf
argument_list|(
name|fp
argument_list|,
operator|(
literal|"# GIMP sessionrc\n"
literal|"# This file takes session-specific info (that is info,\n"
literal|"# you want to keep between two gimp-sessions). You are\n"
literal|"# not supposed to edit it manually, but of course you\n"
literal|"# can do. This file will be entirely rewritten every time\n"
literal|"# you quit the gimp. If this file isn't found, defaults\n"
literal|"# are used.\n\n"
operator|)
argument_list|)
expr_stmt|;
name|gimp_dialog_factories_session_save
argument_list|(
name|fp
argument_list|)
expr_stmt|;
comment|/* save last tip shown */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"(last-tip-shown %d)\n\n"
argument_list|,
name|gimprc
operator|.
name|last_tip
operator|+
literal|1
argument_list|)
expr_stmt|;
name|color_history_write
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

