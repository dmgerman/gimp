begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald  *  * GtkHWrapBox: Horizontal wrapping box widget  * Copyright (C) 1999 Tim Janik  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GTK_HWRAP_BOX_H__
end_ifndef

begin_define
DECL|macro|__GTK_HWRAP_BOX_H__
define|#
directive|define
name|__GTK_HWRAP_BOX_H__
end_define

begin_include
include|#
directive|include
file|"gtkwrapbox.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* --- type macros --- */
end_comment

begin_define
DECL|macro|GTK_TYPE_HWRAP_BOX
define|#
directive|define
name|GTK_TYPE_HWRAP_BOX
value|(gtk_hwrap_box_get_type ())
end_define

begin_define
DECL|macro|GTK_HWRAP_BOX (obj)
define|#
directive|define
name|GTK_HWRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_HWRAP_BOX, GtkHWrapBox))
end_define

begin_define
DECL|macro|GTK_HWRAP_BOX_CLASS (klass)
define|#
directive|define
name|GTK_HWRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_HWRAP_BOX, GtkHWrapBoxClass))
end_define

begin_define
DECL|macro|GTK_IS_HWRAP_BOX (obj)
define|#
directive|define
name|GTK_IS_HWRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_HWRAP_BOX))
end_define

begin_define
DECL|macro|GTK_IS_HWRAP_BOX_CLASS (klass)
define|#
directive|define
name|GTK_IS_HWRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_HWRAP_BOX))
end_define

begin_define
DECL|macro|GTK_HWRAP_BOX_GET_CLASS (obj)
define|#
directive|define
name|GTK_HWRAP_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_HWRAP_BOX, GtkHWrapBoxClass))
end_define

begin_comment
comment|/* --- typedefs --- */
end_comment

begin_typedef
DECL|typedef|GtkHWrapBox
typedef|typedef
name|struct
name|_GtkHWrapBox
name|GtkHWrapBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GtkHWrapBoxClass
typedef|typedef
name|struct
name|_GtkHWrapBoxClass
name|GtkHWrapBoxClass
typedef|;
end_typedef

begin_comment
comment|/* --- GtkHWrapBox --- */
end_comment

begin_struct
DECL|struct|_GtkHWrapBox
struct|struct
name|_GtkHWrapBox
block|{
DECL|member|parent_widget
name|GtkWrapBox
name|parent_widget
decl_stmt|;
comment|/*<h2v-off>*/
DECL|member|max_child_width
name|guint
name|max_child_width
decl_stmt|;
DECL|member|max_child_height
name|guint
name|max_child_height
decl_stmt|;
comment|/*<h2v-on>*/
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GtkHWrapBoxClass
struct|struct
name|_GtkHWrapBoxClass
block|{
DECL|member|parent_class
name|GtkWrapBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* --- prototypes --- */
end_comment

begin_decl_stmt
name|GType
name|gtk_hwrap_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_hwrap_box_new
parameter_list|(
name|gboolean
name|homogeneous
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GTK_HWRAP_BOX_H__ */
end_comment

end_unit

