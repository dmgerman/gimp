begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UI_H__
define|#
directive|define
name|__GIMP_UI_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpchainbutton.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbutton.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpexport.h"
end_include

begin_include
include|#
directive|include
file|"gimpfileselection.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpui.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenu.h"
end_include

begin_include
include|#
directive|include
file|"gimppatheditor.h"
end_include

begin_include
include|#
directive|include
file|"gimppixmap.h"
end_include

begin_include
include|#
directive|include
file|"gimpquerybox.h"
end_include

begin_include
include|#
directive|include
file|"gimpsizeentry.h"
end_include

begin_include
include|#
directive|include
file|"gimpunitmenu.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UI_H__ */
end_comment

end_unit

