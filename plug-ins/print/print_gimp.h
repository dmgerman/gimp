begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * "$Id$"  *  *   Print plug-in for the GIMP.  *  *   Copyright 1997-2000 Michael Sweet (mike@easysw.com),  *	Robert Krawitz (rlk@alum.mit.edu). and Steve Miller (smiller@rni.net  *  *   This program is free software; you can redistribute it and/or modify it  *   under the terms of the GNU General Public License as published by the Free  *   Software Foundation; either version 2 of the License, or (at your option)  *   any later version.  *  *   This program is distributed in the hope that it will be useful, but  *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  *   for more details.  *  *   You should have received a copy of the GNU General Public License  *   along with this program; if not, write to the Free Software  *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  *  * Revision History:  *  *   See ChangeLog  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|PRINT_GIMP_HEADER
end_ifndef

begin_define
DECL|macro|PRINT_GIMP_HEADER
define|#
directive|define
name|PRINT_GIMP_HEADER
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"print.h"
end_include

begin_comment
comment|/*  * All Gimp-specific code is in this file.  */
end_comment

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"3.0.10 - 01 Apr 2000"
end_define

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"Print"
end_define

begin_comment
comment|/*  * Constants for GUI...  */
end_comment

begin_define
DECL|macro|PREVIEW_SIZE_VERT
define|#
directive|define
name|PREVIEW_SIZE_VERT
value|240
end_define

begin_comment
DECL|macro|PREVIEW_SIZE_VERT
comment|/* Assuming max media size of 24" A2 */
end_comment

begin_define
DECL|macro|PREVIEW_SIZE_HORIZ
define|#
directive|define
name|PREVIEW_SIZE_HORIZ
value|240
end_define

begin_comment
DECL|macro|PREVIEW_SIZE_HORIZ
comment|/* Assuming max media size of 24" A2 */
end_comment

begin_define
DECL|macro|MAX_PLIST
define|#
directive|define
name|MAX_PLIST
value|100
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit

