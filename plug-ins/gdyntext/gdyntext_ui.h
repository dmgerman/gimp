begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GDYNTEXT_UI_H_
end_ifndef

begin_define
DECL|macro|_GDYNTEXT_UI_H_
define|#
directive|define
name|_GDYNTEXT_UI_H_
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gdyntext.h"
end_include

begin_include
include|#
directive|include
file|"font_selection.h"
end_include

begin_include
include|#
directive|include
file|"charmap.h"
end_include

begin_include
include|#
directive|include
file|"charmap_window.h"
end_include

begin_include
include|#
directive|include
file|"message_window.h"
end_include

begin_function_decl
name|gboolean
name|gdt_create_ui
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _GDYNTEXT_UI_H_ */
end_comment

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit

