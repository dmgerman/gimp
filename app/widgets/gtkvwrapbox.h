begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald  *  * GtkVWrapBox: Vertical wrapping box widget  * Copyright (C) 1999 Tim Janik  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GTK_VWRAP_BOX_H__
end_ifndef

begin_define
DECL|macro|__GTK_VWRAP_BOX_H__
define|#
directive|define
name|__GTK_VWRAP_BOX_H__
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
DECL|macro|GTK_TYPE_VWRAP_BOX
define|#
directive|define
name|GTK_TYPE_VWRAP_BOX
value|(gtk_vwrap_box_get_type ())
end_define

begin_define
DECL|macro|GTK_VWRAP_BOX (obj)
define|#
directive|define
name|GTK_VWRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_VWRAP_BOX, GtkVWrapBox))
end_define

begin_define
DECL|macro|GTK_VWRAP_BOX_CLASS (klass)
define|#
directive|define
name|GTK_VWRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_VWRAP_BOX, GtkVWrapBoxClass))
end_define

begin_define
DECL|macro|GTK_IS_VWRAP_BOX (obj)
define|#
directive|define
name|GTK_IS_VWRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_VWRAP_BOX))
end_define

begin_define
DECL|macro|GTK_IS_VWRAP_BOX_CLASS (klass)
define|#
directive|define
name|GTK_IS_VWRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_VWRAP_BOX))
end_define

begin_define
DECL|macro|GTK_VWRAP_BOX_GET_CLASS (obj)
define|#
directive|define
name|GTK_VWRAP_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_VWRAP_BOX, GtkVWrapBoxClass))
end_define

begin_comment
comment|/* --- typedefs --- */
end_comment

begin_typedef
DECL|typedef|GtkVWrapBox
typedef|typedef
name|struct
name|_GtkVWrapBox
name|GtkVWrapBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GtkVWrapBoxClass
typedef|typedef
name|struct
name|_GtkVWrapBoxClass
name|GtkVWrapBoxClass
typedef|;
end_typedef

begin_comment
comment|/* --- GtkVWrapBox --- */
end_comment

begin_struct
DECL|struct|_GtkVWrapBox
struct|struct
name|_GtkVWrapBox
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
DECL|struct|_GtkVWrapBoxClass
struct|struct
name|_GtkVWrapBoxClass
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
name|gtk_vwrap_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_vwrap_box_new
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
comment|/* __GTK_VWRAP_BOX_H__ */
end_comment

end_unit

