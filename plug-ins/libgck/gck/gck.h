begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/***************************************************************************/
end_comment

begin_comment
comment|/* GCK - The General Convenience Kit. Generally useful conveniece routines */
end_comment

begin_comment
comment|/* for GIMP plug-in writers and users of the GDK/GTK libraries.            */
end_comment

begin_comment
comment|/* Copyright (C) 1996 Tom Bech                                             */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is free software; you can redistribute it and/or modify    */
end_comment

begin_comment
comment|/* it under the terms of the GNU General Public License as published by    */
end_comment

begin_comment
comment|/* the Free Software Foundation; either version 2 of the License, or       */
end_comment

begin_comment
comment|/* (at your option) any later version.                                     */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* This program is distributed in the hope that it will be useful,         */
end_comment

begin_comment
comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
end_comment

begin_comment
comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
end_comment

begin_comment
comment|/* GNU General Public License for more details.                            */
end_comment

begin_comment
comment|/*                                                                         */
end_comment

begin_comment
comment|/* You should have received a copy of the GNU General Public License       */
end_comment

begin_comment
comment|/* along with this program; if not, write to the Free Software             */
end_comment

begin_comment
comment|/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,   */
end_comment

begin_comment
comment|/* USA.                                                                    */
end_comment

begin_comment
comment|/***************************************************************************/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GCK_H__
end_ifndef

begin_define
DECL|macro|__GCK_H__
define|#
directive|define
name|__GCK_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdk.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
DECL|macro|g_function_enter (fname)
define|#
directive|define
name|g_function_enter
parameter_list|(
name|fname
parameter_list|)
DECL|macro|g_function_leave (fname)
define|#
directive|define
name|g_function_leave
parameter_list|(
name|fname
parameter_list|)
include|#
directive|include
file|<gck/gckcommon.h>
include|#
directive|include
file|<gck/gcktypes.h>
include|#
directive|include
file|<gck/gckcolor.h>
include|#
directive|include
file|<gck/gckmath.h>
include|#
directive|include
file|<gck/gckvector.h>
include|#
directive|include
file|<gck/gckui.h>
include|#
directive|include
file|<gck/gcklistbox.h>
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

end_unit

