begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald  *  * GtkWrapBox: Wrapping box widget  * Copyright (C) 1999 Tim Janik  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GTK_WRAP_BOX_H__
end_ifndef

begin_define
DECL|macro|__GTK_WRAP_BOX_H__
define|#
directive|define
name|__GTK_WRAP_BOX_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* --- type macros --- */
end_comment

begin_define
DECL|macro|GTK_TYPE_WRAP_BOX
define|#
directive|define
name|GTK_TYPE_WRAP_BOX
value|(gtk_wrap_box_get_type ())
end_define

begin_define
DECL|macro|GTK_WRAP_BOX (obj)
define|#
directive|define
name|GTK_WRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_WRAP_BOX, GtkWrapBox))
end_define

begin_define
DECL|macro|GTK_WRAP_BOX_CLASS (klass)
define|#
directive|define
name|GTK_WRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_WRAP_BOX, GtkWrapBoxClass))
end_define

begin_define
DECL|macro|GTK_IS_WRAP_BOX (obj)
define|#
directive|define
name|GTK_IS_WRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_WRAP_BOX))
end_define

begin_define
DECL|macro|GTK_IS_WRAP_BOX_CLASS (klass)
define|#
directive|define
name|GTK_IS_WRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WRAP_BOX))
end_define

begin_define
DECL|macro|GTK_WRAP_BOX_GET_CLASS (obj)
define|#
directive|define
name|GTK_WRAP_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_WRAP_BOX, GtkWrapBoxClass))
end_define

begin_comment
comment|/* --- typedefs --- */
end_comment

begin_typedef
DECL|typedef|GtkWrapBox
typedef|typedef
name|struct
name|_GtkWrapBox
name|GtkWrapBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GtkWrapBoxClass
typedef|typedef
name|struct
name|_GtkWrapBoxClass
name|GtkWrapBoxClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GtkWrapBoxChild
typedef|typedef
name|struct
name|_GtkWrapBoxChild
name|GtkWrapBoxChild
typedef|;
end_typedef

begin_comment
comment|/* --- GtkWrapBox --- */
end_comment

begin_struct
DECL|struct|_GtkWrapBox
struct|struct
name|_GtkWrapBox
block|{
DECL|member|container
name|GtkContainer
name|container
decl_stmt|;
DECL|member|homogeneous
name|guint
name|homogeneous
range|:
literal|1
decl_stmt|;
DECL|member|justify
name|guint
name|justify
range|:
literal|4
decl_stmt|;
DECL|member|line_justify
name|guint
name|line_justify
range|:
literal|4
decl_stmt|;
DECL|member|hspacing
name|guint8
name|hspacing
decl_stmt|;
DECL|member|vspacing
name|guint8
name|vspacing
decl_stmt|;
DECL|member|n_children
name|guint16
name|n_children
decl_stmt|;
DECL|member|children
name|GtkWrapBoxChild
modifier|*
name|children
decl_stmt|;
DECL|member|aspect_ratio
name|gfloat
name|aspect_ratio
decl_stmt|;
comment|/* 1/256..256 */
DECL|member|child_limit
name|guint
name|child_limit
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GtkWrapBoxClass
struct|struct
name|_GtkWrapBoxClass
block|{
DECL|member|parent_class
name|GtkContainerClass
name|parent_class
decl_stmt|;
DECL|member|rlist_line_children
name|GSList
modifier|*
function_decl|(
modifier|*
name|rlist_line_children
function_decl|)
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWrapBoxChild
modifier|*
modifier|*
name|child_p
parameter_list|,
name|GtkAllocation
modifier|*
name|area
parameter_list|,
name|guint
modifier|*
name|max_child_size
parameter_list|,
name|gboolean
modifier|*
name|expand_line
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GtkWrapBoxChild
struct|struct
name|_GtkWrapBoxChild
block|{
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
DECL|member|hexpand
name|guint
name|hexpand
range|:
literal|1
decl_stmt|;
DECL|member|hfill
name|guint
name|hfill
range|:
literal|1
decl_stmt|;
DECL|member|vexpand
name|guint
name|vexpand
range|:
literal|1
decl_stmt|;
DECL|member|vfill
name|guint
name|vfill
range|:
literal|1
decl_stmt|;
DECL|member|wrapped
name|guint
name|wrapped
range|:
literal|1
decl_stmt|;
DECL|member|next
name|GtkWrapBoxChild
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GTK_JUSTIFY_TOP
define|#
directive|define
name|GTK_JUSTIFY_TOP
value|GTK_JUSTIFY_LEFT
end_define

begin_define
DECL|macro|GTK_JUSTIFY_BOTTOM
define|#
directive|define
name|GTK_JUSTIFY_BOTTOM
value|GTK_JUSTIFY_RIGHT
end_define

begin_comment
comment|/* --- prototypes --- */
end_comment

begin_decl_stmt
name|GType
name|gtk_wrap_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gtk_wrap_box_set_homogeneous
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|gboolean
name|homogeneous
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_set_hspacing
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|guint
name|hspacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_set_vspacing
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|guint
name|vspacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_set_justify
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkJustification
name|justify
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_set_line_justify
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkJustification
name|line_justify
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_set_aspect_ratio
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|gfloat
name|aspect_ratio
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_pack
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gboolean
name|hexpand
parameter_list|,
name|gboolean
name|hfill
parameter_list|,
name|gboolean
name|vexpand
parameter_list|,
name|gboolean
name|vfill
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_pack_wrapped
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gboolean
name|hexpand
parameter_list|,
name|gboolean
name|hfill
parameter_list|,
name|gboolean
name|vexpand
parameter_list|,
name|gboolean
name|vfill
parameter_list|,
name|gboolean
name|wrapped
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_reorder_child
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_query_child_packing
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gboolean
modifier|*
name|hexpand
parameter_list|,
name|gboolean
modifier|*
name|hfill
parameter_list|,
name|gboolean
modifier|*
name|vexpand
parameter_list|,
name|gboolean
modifier|*
name|vfill
parameter_list|,
name|gboolean
modifier|*
name|wrapped
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_wrap_box_set_child_packing
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|GtkWidget
modifier|*
name|child
parameter_list|,
name|gboolean
name|hexpand
parameter_list|,
name|gboolean
name|hfill
parameter_list|,
name|gboolean
name|vexpand
parameter_list|,
name|gboolean
name|vfill
parameter_list|,
name|gboolean
name|wrapped
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint
modifier|*
name|gtk_wrap_box_query_line_lengths
parameter_list|(
name|GtkWrapBox
modifier|*
name|wbox
parameter_list|,
name|guint
modifier|*
name|n_lines
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
comment|/* __GTK_WRAP_BOX_H__ */
end_comment

end_unit

