begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DND_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DND_H__
define|#
directive|define
name|__GIMP_DND_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2965b9750103
block|{
DECL|enumerator|GIMP_DND_TYPE_URI_LIST
name|GIMP_DND_TYPE_URI_LIST
block|,
DECL|enumerator|GIMP_DND_TYPE_TEXT_PLAIN
name|GIMP_DND_TYPE_TEXT_PLAIN
block|,
DECL|enumerator|GIMP_DND_TYPE_NETSCAPE_URL
name|GIMP_DND_TYPE_NETSCAPE_URL
block|,
DECL|enumerator|GIMP_DND_TYPE_IMAGE
name|GIMP_DND_TYPE_IMAGE
block|,
DECL|enumerator|GIMP_DND_TYPE_LAYER
name|GIMP_DND_TYPE_LAYER
block|,
DECL|enumerator|GIMP_DND_TYPE_CHANNEL
name|GIMP_DND_TYPE_CHANNEL
block|,
DECL|enumerator|GIMP_DND_TYPE_LAYER_MASK
name|GIMP_DND_TYPE_LAYER_MASK
block|,
DECL|enumerator|GIMP_DND_TYPE_COMPONENT
name|GIMP_DND_TYPE_COMPONENT
block|,
DECL|enumerator|GIMP_DND_TYPE_PATH
name|GIMP_DND_TYPE_PATH
block|,
DECL|enumerator|GIMP_DND_TYPE_COLOR
name|GIMP_DND_TYPE_COLOR
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TARGET_URI_LIST
define|#
directive|define
name|GIMP_TARGET_URI_LIST
define|\
value|{ "text/uri-list", 0, GIMP_DND_TYPE_URI_LIST }
end_define

begin_define
DECL|macro|GIMP_TARGET_TEXT_PLAIN
define|#
directive|define
name|GIMP_TARGET_TEXT_PLAIN
define|\
value|{ "text/plain", 0, GIMP_DND_TYPE_TEXT_PLAIN }
end_define

begin_define
DECL|macro|GIMP_TARGET_NETSCAPE_URL
define|#
directive|define
name|GIMP_TARGET_NETSCAPE_URL
define|\
value|{ "_NETSCAPE_URL", 0, GIMP_DND_TYPE_NETSCAPE_URL }
end_define

begin_define
DECL|macro|GIMP_TARGET_IMAGE
define|#
directive|define
name|GIMP_TARGET_IMAGE
define|\
value|{ "GIMP_IMAGE", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_IMAGE }
end_define

begin_define
DECL|macro|GIMP_TARGET_LAYER
define|#
directive|define
name|GIMP_TARGET_LAYER
define|\
value|{ "GIMP_LAYER", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_LAYER }
end_define

begin_define
DECL|macro|GIMP_TARGET_CHANNEL
define|#
directive|define
name|GIMP_TARGET_CHANNEL
define|\
value|{ "GIMP_CHANNEL", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_CHANNEL }
end_define

begin_define
DECL|macro|GIMP_TARGET_LAYER_MASK
define|#
directive|define
name|GIMP_TARGET_LAYER_MASK
define|\
value|{ "GIMP_LAYER_MASK", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_LAYER_MASK }
end_define

begin_define
DECL|macro|GIMP_TARGET_COMPONENT
define|#
directive|define
name|GIMP_TARGET_COMPONENT
define|\
value|{ "GIMP_COMPONENT", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_COMPONENT }
end_define

begin_define
DECL|macro|GIMP_TARGET_PATH
define|#
directive|define
name|GIMP_TARGET_PATH
define|\
value|{ "GIMP_PATH", GTK_TARGET_SAME_APP, GIMP_DND_TYPE_PATH }
end_define

begin_define
DECL|macro|GIMP_TARGET_COLOR
define|#
directive|define
name|GIMP_TARGET_COLOR
define|\
value|{ "application/x-color", 0, GIMP_DND_TYPE_COLOR }
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2965b9750203
block|{
DECL|enumerator|GIMP_DROP_NONE
name|GIMP_DROP_NONE
block|,
DECL|enumerator|GIMP_DROP_ABOVE
name|GIMP_DROP_ABOVE
block|,
DECL|enumerator|GIMP_DROP_BELOW
name|GIMP_DROP_BELOW
DECL|typedef|GimpDropType
block|}
name|GimpDropType
typedef|;
end_typedef

begin_function_decl
name|void
name|gimp_dnd_set_drawable_preview_icon
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GdkGC
modifier|*
name|gc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DND_H__ */
end_comment

end_unit

