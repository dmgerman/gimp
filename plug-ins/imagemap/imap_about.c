begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2002 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"imap_about.h"
end_include

begin_include
include|#
directive|include
file|"imap_default_dialog.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_function
name|void
DECL|function|do_about_dialog (void)
name|do_about_dialog
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|DefaultDialog_t
modifier|*
name|dialog
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
condition|)
block|{
name|dialog
operator|=
name|make_default_dialog
argument_list|(
name|_
argument_list|(
literal|"About"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_hide_cancel_button
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|default_dialog_hide_apply_button
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|default_dialog_hide_help_button
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|default_dialog_set_label
argument_list|(
name|dialog
argument_list|,
name|_
argument_list|(
literal|"Imagemap plug-in 2.0"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_set_label
argument_list|(
name|dialog
argument_list|,
name|_
argument_list|(
literal|"Copyright(c) 1999 by Maurits Rijk"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_set_label
argument_list|(
name|dialog
argument_list|,
name|_
argument_list|(
literal|"lpeek.mrijk@consunet.nl"
argument_list|)
argument_list|)
expr_stmt|;
name|default_dialog_set_label
argument_list|(
name|dialog
argument_list|,
name|_
argument_list|(
literal|"  Released under the GNU General Public License  "
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|default_dialog_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

