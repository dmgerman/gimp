begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolinfo.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_tool_info_class_init
parameter_list|(
name|GimpToolInfoClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_info_init
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_tool_info_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDataClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_tool_info_get_type (void)
name|gimp_tool_info_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_info_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_info_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpToolInfoClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_tool_info_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpToolInfo
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_tool_info_init
block|,       }
decl_stmt|;
name|tool_info_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DATA
argument_list|,
literal|"GimpToolInfo"
argument_list|,
operator|&
name|tool_info_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_info_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_info_class_init (GimpToolInfoClass * klass)
name|gimp_tool_info_class_init
parameter_list|(
name|GimpToolInfoClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tool_info_finalize
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_tool_info_get_new_preview
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_info_init (GimpToolInfo * tool_info)
name|gimp_tool_info_init
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|tool_info
operator|->
name|tool_type
operator|=
name|G_TYPE_NONE
expr_stmt|;
name|tool_info
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|help
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|menu_path
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|menu_accel
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|help_domain
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|help_data
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|stock_id
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|stock_pixbuf
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|tool_options
operator|=
name|NULL
expr_stmt|;
name|tool_info
operator|->
name|paint_info
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_info_finalize (GObject * object)
name|gimp_tool_info_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|tool_info
operator|=
name|GIMP_TOOL_INFO
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|blurb
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|help
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|help
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|blurb
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|menu_path
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|menu_path
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|menu_path
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|menu_accel
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|menu_accel
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|menu_accel
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|help_domain
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|help_domain
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help_domain
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|help_data
condition|)
block|{
name|g_free
argument_list|(
name|tool_info
operator|->
name|help_data
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help_data
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|stock_id
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|stock_id
argument_list|)
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|stock_id
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|tool_info
operator|->
name|stock_pixbuf
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|stock_pixbuf
argument_list|)
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|stock_pixbuf
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|temp_buf_new_from_pixbuf (GdkPixbuf * pixbuf,gint width,gint height)
name|temp_buf_new_from_pixbuf
parameter_list|(
name|GdkPixbuf
modifier|*
name|pixbuf
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|gint
name|pixbuf_width
decl_stmt|;
name|gint
name|pixbuf_height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|guchar
name|transparent
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|guchar
modifier|*
name|p_data
decl_stmt|;
name|guchar
modifier|*
name|t_data
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GDK_IS_PIXBUF
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixbuf_width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixbuf_height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf_width
operator|!=
name|width
operator|||
name|pixbuf_height
operator|!=
name|height
condition|)
block|{
name|GdkPixbuf
modifier|*
name|scaled_pixbuf
decl_stmt|;
name|scaled_pixbuf
operator|=
name|gdk_pixbuf_scale_simple
argument_list|(
name|pixbuf
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GDK_INTERP_BILINEAR
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|scaled_pixbuf
expr_stmt|;
block|}
else|else
block|{
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|bytes
operator|=
name|gdk_pixbuf_get_n_channels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|temp_buf
operator|=
name|temp_buf_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|bytes
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|transparent
argument_list|)
expr_stmt|;
name|p_data
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|t_data
operator|=
name|temp_buf_data
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|t_data
argument_list|,
name|p_data
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|p_data
operator|+=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|t_data
operator|+=
name|width
operator|*
name|bytes
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|temp_buf
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_tool_info_get_new_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_tool_info_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|tool_info
operator|=
name|GIMP_TOOL_INFO
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
return|return
name|temp_buf_new_from_pixbuf
argument_list|(
name|tool_info
operator|->
name|stock_pixbuf
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpToolInfo
modifier|*
DECL|function|gimp_tool_info_new (Gimp * gimp,GimpContext * context,GType tool_type,gboolean tool_context,const gchar * identifier,const gchar * blurb,const gchar * help,const gchar * menu_path,const gchar * menu_accel,const gchar * help_domain,const gchar * help_data,const gchar * paint_core_name,const gchar * stock_id,GdkPixbuf * stock_pixbuf)
name|gimp_tool_info_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GType
name|tool_type
parameter_list|,
name|gboolean
name|tool_context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_accel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|paint_core_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
name|GdkPixbuf
modifier|*
name|stock_pixbuf
parameter_list|)
block|{
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|identifier
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|blurb
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_path
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|paint_core_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|stock_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|stock_pixbuf
operator|||
name|GDK_IS_PIXBUF
argument_list|(
name|stock_pixbuf
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|paint_info
operator|=
operator|(
name|GimpPaintInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|paint_info_list
argument_list|,
name|paint_core_name
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PAINT_INFO
argument_list|(
name|paint_info
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_INFO
argument_list|,
literal|"name"
argument_list|,
name|identifier
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|paint_info
operator|=
name|paint_info
expr_stmt|;
if|if
condition|(
name|tool_context
condition|)
block|{
name|tool_info
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
name|gimp
argument_list|,
name|identifier
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
name|tool_info
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|tool_info
operator|->
name|tool_type
operator|=
name|tool_type
expr_stmt|;
name|tool_info
operator|->
name|blurb
operator|=
name|g_strdup
argument_list|(
name|blurb
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help
operator|=
name|g_strdup
argument_list|(
name|help
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|menu_path
operator|=
name|g_strdup
argument_list|(
name|menu_path
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|menu_accel
operator|=
name|g_strdup
argument_list|(
name|menu_accel
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help_domain
operator|=
name|g_strdup
argument_list|(
name|help_domain
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|help_data
operator|=
name|g_strdup
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|stock_id
operator|=
name|g_strdup
argument_list|(
name|stock_id
argument_list|)
expr_stmt|;
name|tool_info
operator|->
name|stock_pixbuf
operator|=
name|stock_pixbuf
expr_stmt|;
if|if
condition|(
name|stock_pixbuf
condition|)
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|stock_pixbuf
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|tool_info
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_info_set_standard (Gimp * gimp,GimpToolInfo * tool_info)
name|gimp_tool_info_set_standard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
operator|!
name|tool_info
operator|||
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|standard_tool_info
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|standard_tool_info
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp
operator|->
name|standard_tool_info
operator|=
name|tool_info
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|standard_tool_info
condition|)
block|{
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|standard_tool_info
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpToolInfo
modifier|*
DECL|function|gimp_tool_info_get_standard (Gimp * gimp)
name|gimp_tool_info_get_standard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp
operator|->
name|standard_tool_info
return|;
block|}
end_function

end_unit

