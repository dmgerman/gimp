begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald  *  * GtkVWrapBox: Vertical wrapping box widget  * Copyright (C) 1999 Tim Janik  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
comment|/* __cplusplus */
comment|/* --- type macros --- */
DECL|macro|GTK_TYPE_VWRAP_BOX
define|#
directive|define
name|GTK_TYPE_VWRAP_BOX
value|(gtk_vwrap_box_get_type ())
DECL|macro|GTK_VWRAP_BOX (obj)
define|#
directive|define
name|GTK_VWRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GTK_TYPE_VWRAP_BOX, GtkVWrapBox))
DECL|macro|GTK_VWRAP_BOX_CLASS (klass)
define|#
directive|define
name|GTK_VWRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GTK_TYPE_VWRAP_BOX, GtkVWrapBoxClass))
DECL|macro|GTK_IS_VWRAP_BOX (obj)
define|#
directive|define
name|GTK_IS_VWRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GTK_TYPE_VWRAP_BOX))
DECL|macro|GTK_IS_VWRAP_BOX_CLASS (klass)
define|#
directive|define
name|GTK_IS_VWRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GTK_TYPE_VWRAP_BOX))
DECL|macro|GTK_VWRAP_BOX_GET_CLASS (obj)
define|#
directive|define
name|GTK_VWRAP_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(GTK_VWRAP_BOX_CLASS (((GtkObject*) (obj))->klass))
comment|/* --- typedefs --- */
DECL|typedef|GtkVWrapBox
typedef|typedef
name|struct
name|_GtkVWrapBox
name|GtkVWrapBox
typedef|;
DECL|typedef|GtkVWrapBoxClass
typedef|typedef
name|struct
name|_GtkVWrapBoxClass
name|GtkVWrapBoxClass
typedef|;
comment|/* --- GtkVWrapBox --- */
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
name|guint16
name|max_child_width
decl_stmt|;
DECL|member|max_child_height
name|guint16
name|max_child_height
decl_stmt|;
comment|/*<h2v-on>*/
block|}
struct|;
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
comment|/* --- prototypes --- */
name|GtkType
name|gtk_vwrap_box_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gtk_vwrap_box_new
parameter_list|(
name|gboolean
name|homogeneous
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GTK_VWRAP_BOX_H__ */
end_comment

end_unit

