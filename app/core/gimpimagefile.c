begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfileimage.c  *  * Copyright (C) 2001-2003  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpthumb/gimpthumb.h"
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
file|"config/gimpcoreconfig.h"
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
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29490b3c0103
block|{
DECL|enumerator|INFO_CHANGED
name|INFO_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_imagefile_class_init
parameter_list|(
name|GimpImagefileClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_imagefile_init
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_imagefile_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_imagefile_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_imagefile_info_changed
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_imagefile_notify_thumbnail
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_imagefile_get_new_preview
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

begin_function_decl
specifier|static
name|TempBuf
modifier|*
name|gimp_imagefile_load_thumb
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_imagefile_save_thumb
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|size
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_imagefile_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_imagefile_signals
specifier|static
name|guint
name|gimp_imagefile_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpViewableClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_imagefile_get_type (void)
name|gimp_imagefile_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|imagefile_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|imagefile_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|imagefile_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpImagefileClass
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
name|gimp_imagefile_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpImagefile
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_imagefile_init
block|,       }
decl_stmt|;
name|imagefile_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEWABLE
argument_list|,
literal|"GimpImagefile"
argument_list|,
operator|&
name|imagefile_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|imagefile_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_imagefile_class_init (GimpImagefileClass * klass)
name|gimp_imagefile_class_init
parameter_list|(
name|GimpImagefileClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|gchar
modifier|*
name|creator
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
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
name|gimp_imagefile_signals
index|[
name|INFO_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"info_changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpImagefileClass
argument_list|,
name|info_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_imagefile_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|name_changed
operator|=
name|gimp_imagefile_name_changed
expr_stmt|;
name|viewable_class
operator|->
name|name_changed_signal
operator|=
literal|"info_changed"
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_imagefile_get_new_preview
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_imagefile_get_description
expr_stmt|;
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_IMAGE_TYPE
argument_list|)
expr_stmt|;
name|creator
operator|=
name|g_strdup_printf
argument_list|(
literal|"gimp-%d.%d"
argument_list|,
name|GIMP_MAJOR_VERSION
argument_list|,
name|GIMP_MINOR_VERSION
argument_list|)
expr_stmt|;
name|gimp_thumb_init
argument_list|(
name|creator
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|creator
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_imagefile_init (GimpImagefile * imagefile)
name|gimp_imagefile_init
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
block|{
name|imagefile
operator|->
name|gimp
operator|=
name|NULL
expr_stmt|;
name|imagefile
operator|->
name|thumbnail
operator|=
name|gimp_thumbnail_new
argument_list|()
expr_stmt|;
name|imagefile
operator|->
name|description
operator|=
name|NULL
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_imagefile_notify_thumbnail
argument_list|)
argument_list|,
name|imagefile
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_imagefile_finalize (GObject * object)
name|gimp_imagefile_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
init|=
name|GIMP_IMAGEFILE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|imagefile
operator|->
name|description
condition|)
block|{
if|if
condition|(
operator|!
name|imagefile
operator|->
name|static_desc
condition|)
name|g_free
argument_list|(
name|imagefile
operator|->
name|description
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|description
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|imagefile
operator|->
name|thumbnail
condition|)
block|{
name|g_object_unref
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|thumbnail
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
name|GimpImagefile
modifier|*
DECL|function|gimp_imagefile_new (Gimp * gimp,const gchar * uri)
name|gimp_imagefile_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
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
name|imagefile
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGEFILE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
if|if
condition|(
name|uri
condition|)
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
return|return
name|imagefile
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_imagefile_update (GimpImagefile * imagefile)
name|gimp_imagefile_update
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
block|{
name|gchar
modifier|*
name|uri
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGEFILE
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|,
literal|"image-uri"
argument_list|,
operator|&
name|uri
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
block|{
name|GimpImagefile
modifier|*
name|documents_imagefile
init|=
operator|(
name|GimpImagefile
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|imagefile
operator|->
name|gimp
operator|->
name|documents
argument_list|,
name|uri
argument_list|)
decl_stmt|;
if|if
condition|(
name|documents_imagefile
operator|!=
name|imagefile
operator|&&
name|GIMP_IS_IMAGEFILE
argument_list|(
name|documents_imagefile
argument_list|)
condition|)
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|documents_imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_imagefile_create_thumbnail (GimpImagefile * imagefile,gint size)
name|gimp_imagefile_create_thumbnail
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGEFILE
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|imagefile
operator|->
name|gimp
operator|->
name|config
operator|->
name|layer_previews
condition|)
return|return;
if|if
condition|(
name|size
operator|<
literal|1
condition|)
return|return;
name|gimp_thumbnail_set_uri
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_thumbnail_peek_image
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|)
operator|>=
name|GIMP_THUMB_STATE_EXISTS
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpPDBStatusType
name|dummy
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimage
operator|=
name|file_open_image
argument_list|(
name|imagefile
operator|->
name|gimp
argument_list|,
name|imagefile
operator|->
name|thumbnail
operator|->
name|image_uri
argument_list|,
name|imagefile
operator|->
name|thumbnail
operator|->
name|image_uri
argument_list|,
name|NULL
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
operator|&
name|dummy
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|success
operator|=
name|gimp_imagefile_save_thumb
argument_list|(
name|imagefile
argument_list|,
name|gimage
argument_list|,
name|size
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|gimp_thumbnail_save_failure
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|,
literal|"The GIMP "
name|GIMP_VERSION
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|success
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_imagefile_save_thumbnail (GimpImagefile * imagefile,GimpImage * gimage)
name|gimp_imagefile_save_thumbnail
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|gboolean
name|success
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGEFILE
argument_list|(
name|imagefile
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_imagefile_save_thumb
argument_list|(
name|imagefile
argument_list|,
name|gimage
argument_list|,
name|gimage
operator|->
name|gimp
operator|->
name|config
operator|->
name|thumbnail_size
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|success
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
return|return
name|success
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_imagefile_name_changed (GimpObject * object)
name|gimp_imagefile_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
init|=
name|GIMP_IMAGEFILE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|name_changed
condition|)
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|name_changed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_viewable_set_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|imagefile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_thumbnail_set_uri
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|,
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_imagefile_info_changed (GimpImagefile * imagefile)
name|gimp_imagefile_info_changed
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
block|{
if|if
condition|(
name|imagefile
operator|->
name|description
condition|)
block|{
if|if
condition|(
operator|!
name|imagefile
operator|->
name|static_desc
condition|)
name|g_free
argument_list|(
name|imagefile
operator|->
name|description
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|description
operator|=
name|NULL
expr_stmt|;
block|}
name|g_signal_emit
argument_list|(
name|imagefile
argument_list|,
name|gimp_imagefile_signals
index|[
name|INFO_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_imagefile_notify_thumbnail (GimpImagefile * imagefile,GParamSpec * pspec)
name|gimp_imagefile_notify_thumbnail
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"image-state"
argument_list|)
operator|==
literal|0
operator|||
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"thumb-state"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gimp_imagefile_info_changed
argument_list|(
name|imagefile
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_imagefile_get_new_preview (GimpViewable * viewable,gint width,gint height)
name|gimp_imagefile_get_new_preview
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
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
decl_stmt|;
name|imagefile
operator|=
name|GIMP_IMAGEFILE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
operator|->
name|name
condition|)
return|return
name|NULL
return|;
name|temp_buf
operator|=
name|gimp_imagefile_load_thumb
argument_list|(
name|imagefile
argument_list|,
name|MAX
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|temp_buf
condition|)
block|{
name|gint
name|preview_width
decl_stmt|;
name|gint
name|preview_height
decl_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|temp_buf
operator|->
name|width
argument_list|,
name|temp_buf
operator|->
name|height
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
operator|&
name|preview_width
argument_list|,
operator|&
name|preview_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview_width
operator|<
name|temp_buf
operator|->
name|width
operator|&&
name|preview_height
operator|<
name|temp_buf
operator|->
name|height
condition|)
block|{
name|TempBuf
modifier|*
name|scaled_buf
decl_stmt|;
name|scaled_buf
operator|=
name|temp_buf_scale
argument_list|(
name|temp_buf
argument_list|,
name|preview_width
argument_list|,
name|preview_height
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|temp_buf
operator|=
name|scaled_buf
expr_stmt|;
block|}
name|gimp_viewable_set_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|imagefile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|imagefile
operator|->
name|thumbnail
operator|->
name|image_state
operator|==
name|GIMP_THUMB_STATE_REMOTE
condition|)
block|{
name|gimp_viewable_set_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|imagefile
argument_list|)
argument_list|,
literal|"gtk-network"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|imagefile
operator|->
name|thumbnail
operator|->
name|image_state
operator|==
name|GIMP_THUMB_STATE_FOLDER
condition|)
block|{
name|gimp_viewable_set_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|imagefile
argument_list|)
argument_list|,
literal|"gtk-open"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|imagefile
operator|->
name|thumbnail
operator|->
name|image_state
operator|==
name|GIMP_THUMB_STATE_SPECIAL
condition|)
block|{
name|gimp_viewable_set_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|imagefile
argument_list|)
argument_list|,
literal|"gtk-harddisk"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_viewable_set_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|imagefile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|temp_buf
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_imagefile_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_imagefile_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|GimpThumbnail
modifier|*
name|thumbnail
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|imagefile
operator|=
name|GIMP_IMAGEFILE
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|thumbnail
operator|=
name|imagefile
operator|->
name|thumbnail
expr_stmt|;
if|if
condition|(
operator|!
name|thumbnail
operator|->
name|image_uri
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|tooltip
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|thumbnail
operator|->
name|image_uri
argument_list|)
expr_stmt|;
name|desc
operator|=
name|gimp_imagefile_get_desc_string
argument_list|(
name|imagefile
argument_list|)
expr_stmt|;
if|if
condition|(
name|desc
condition|)
block|{
operator|*
name|tooltip
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s\n%s"
argument_list|,
name|filename
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|tooltip
operator|=
name|filename
expr_stmt|;
block|}
block|}
name|basename
operator|=
name|file_utils_uri_to_utf8_basename
argument_list|(
name|thumbnail
operator|->
name|image_uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|thumbnail
operator|->
name|image_width
operator|>
literal|0
operator|&&
name|thumbnail
operator|->
name|image_height
operator|>
literal|0
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|basename
decl_stmt|;
name|basename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s (%d x %d)"
argument_list|,
name|tmp
argument_list|,
name|thumbnail
operator|->
name|image_width
argument_list|,
name|thumbnail
operator|->
name|image_height
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
return|return
name|basename
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_imagefile_get_desc_string (GimpImagefile * imagefile)
name|gimp_imagefile_get_desc_string
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
block|{
name|GimpThumbnail
modifier|*
name|thumbnail
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGEFILE
argument_list|(
name|imagefile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|imagefile
operator|->
name|description
condition|)
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|imagefile
operator|->
name|description
return|;
name|thumbnail
operator|=
name|imagefile
operator|->
name|thumbnail
expr_stmt|;
switch|switch
condition|(
name|thumbnail
operator|->
name|image_state
condition|)
block|{
case|case
name|GIMP_THUMB_STATE_UNKNOWN
case|:
name|imagefile
operator|->
name|description
operator|=
name|NULL
expr_stmt|;
name|imagefile
operator|->
name|static_desc
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_THUMB_STATE_REMOTE
case|:
name|imagefile
operator|->
name|description
operator|=
name|_
argument_list|(
literal|"Remote image"
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|static_desc
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_THUMB_STATE_FOLDER
case|:
name|imagefile
operator|->
name|description
operator|=
name|_
argument_list|(
literal|"Folder"
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|static_desc
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_THUMB_STATE_SPECIAL
case|:
name|imagefile
operator|->
name|description
operator|=
name|_
argument_list|(
literal|"Special File"
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|static_desc
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_THUMB_STATE_NOT_FOUND
case|:
name|imagefile
operator|->
name|description
operator|=
name|_
argument_list|(
literal|"Could not open"
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|static_desc
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
block|{
name|GString
modifier|*
name|str
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|thumbnail
operator|->
name|image_filesize
operator|>
literal|0
condition|)
block|{
name|gchar
modifier|*
name|size
init|=
name|gimp_memsize_to_string
argument_list|(
name|thumbnail
operator|->
name|image_filesize
argument_list|)
decl_stmt|;
name|g_string_append
argument_list|(
name|str
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size
argument_list|)
expr_stmt|;
name|g_string_append_c
argument_list|(
name|str
argument_list|,
literal|'\n'
argument_list|)
expr_stmt|;
block|}
switch|switch
condition|(
name|thumbnail
operator|->
name|thumb_state
condition|)
block|{
case|case
name|GIMP_THUMB_STATE_NOT_FOUND
case|:
name|g_string_append
argument_list|(
name|str
argument_list|,
name|_
argument_list|(
literal|"No preview available"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_THUMB_STATE_EXISTS
case|:
name|g_string_append
argument_list|(
name|str
argument_list|,
name|_
argument_list|(
literal|"Loading preview ..."
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_THUMB_STATE_OLD
case|:
name|g_string_append
argument_list|(
name|str
argument_list|,
name|_
argument_list|(
literal|"Preview is out of date"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_THUMB_STATE_FAILED
case|:
name|g_string_append
argument_list|(
name|str
argument_list|,
name|_
argument_list|(
literal|"Cannot create preview"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_THUMB_STATE_OK
case|:
block|{
if|if
condition|(
name|thumbnail
operator|->
name|image_width
operator|>
literal|0
operator|&&
name|thumbnail
operator|->
name|image_height
operator|>
literal|0
condition|)
block|{
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
name|_
argument_list|(
literal|"%d x %d pixels"
argument_list|)
argument_list|,
name|thumbnail
operator|->
name|image_width
argument_list|,
name|thumbnail
operator|->
name|image_height
argument_list|)
expr_stmt|;
name|g_string_append_c
argument_list|(
name|str
argument_list|,
literal|'\n'
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|thumbnail
operator|->
name|image_type
condition|)
name|g_string_append
argument_list|(
name|str
argument_list|,
name|gettext
argument_list|(
name|thumbnail
operator|->
name|image_type
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|thumbnail
operator|->
name|image_num_layers
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|thumbnail
operator|->
name|image_type
condition|)
name|g_string_append_len
argument_list|(
name|str
argument_list|,
literal|", "
argument_list|,
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
name|thumbnail
operator|->
name|image_num_layers
operator|==
literal|1
condition|)
name|g_string_append
argument_list|(
name|str
argument_list|,
name|_
argument_list|(
literal|"1 Layer"
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|g_string_append_printf
argument_list|(
name|str
argument_list|,
name|_
argument_list|(
literal|"%d Layers"
argument_list|)
argument_list|,
name|thumbnail
operator|->
name|image_num_layers
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
default|default:
break|break;
block|}
name|imagefile
operator|->
name|description
operator|=
name|g_string_free
argument_list|(
name|str
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|imagefile
operator|->
name|static_desc
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|imagefile
operator|->
name|description
return|;
block|}
end_function

begin_function
specifier|static
name|TempBuf
modifier|*
DECL|function|gimp_imagefile_load_thumb (GimpImagefile * imagefile,gint size)
name|gimp_imagefile_load_thumb
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
name|GimpThumbnail
modifier|*
name|thumbnail
decl_stmt|;
name|TempBuf
modifier|*
name|temp_buf
init|=
name|NULL
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|thumbnail
operator|=
name|imagefile
operator|->
name|thumbnail
expr_stmt|;
if|if
condition|(
name|gimp_thumbnail_peek_thumb
argument_list|(
name|thumbnail
argument_list|,
name|size
argument_list|)
operator|<
name|GIMP_THUMB_STATE_EXISTS
condition|)
return|return
name|NULL
return|;
name|pixbuf
operator|=
name|gimp_thumbnail_load_thumb
argument_list|(
name|thumbnail
argument_list|,
name|size
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
block|{
if|if
condition|(
name|error
condition|)
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Could not open thumbnail '%s': %s"
argument_list|)
argument_list|,
name|thumbnail
operator|->
name|thumb_filename
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
goto|goto
name|cleanup
goto|;
block|}
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
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
name|NULL
argument_list|)
expr_stmt|;
name|dest
operator|=
name|temp_buf_data
argument_list|(
name|temp_buf
argument_list|)
expr_stmt|;
name|src
operator|=
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
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
name|dest
argument_list|,
name|src
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|width
operator|*
name|bytes
expr_stmt|;
name|src
operator|+=
name|gdk_pixbuf_get_rowstride
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
block|}
name|cleanup
label|:
if|if
condition|(
name|pixbuf
condition|)
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|temp_buf
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_imagefile_save_thumb (GimpImagefile * imagefile,GimpImage * gimage,gint size,GError ** error)
name|gimp_imagefile_save_thumb
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|size
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GimpImageType
name|type
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|type_str
decl_stmt|;
name|gint
name|num_layers
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|size
operator|<
literal|1
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
name|gimage
operator|->
name|width
operator|<=
name|size
operator|&&
name|gimage
operator|->
name|height
operator|<=
name|size
condition|)
block|{
name|width
operator|=
name|gimage
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|gimage
operator|->
name|height
expr_stmt|;
name|size
operator|=
name|MIN
argument_list|(
name|size
argument_list|,
name|MAX
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimage
operator|->
name|width
operator|<
name|gimage
operator|->
name|height
condition|)
block|{
name|height
operator|=
name|size
expr_stmt|;
name|width
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
operator|(
name|size
operator|*
name|gimage
operator|->
name|width
operator|)
operator|/
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|width
operator|=
name|size
expr_stmt|;
name|height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
operator|(
name|size
operator|*
name|gimage
operator|->
name|height
operator|)
operator|/
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
block|}
block|}
name|pixbuf
operator|=
name|gimp_viewable_get_new_preview_pixbuf
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
comment|/*  when layer previews are disabled, we won't get a pixbuf  */
if|if
condition|(
operator|!
name|pixbuf
condition|)
return|return
name|TRUE
return|;
name|type
operator|=
name|GIMP_IMAGE_TYPE_FROM_BASE_TYPE
argument_list|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_has_alpha
argument_list|(
name|gimage
argument_list|)
condition|)
name|type
operator|=
name|GIMP_IMAGE_TYPE_WITH_ALPHA
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_IMAGE_TYPE
argument_list|)
expr_stmt|;
name|type_str
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|type
argument_list|)
operator|->
name|value_name
expr_stmt|;
name|num_layers
operator|=
name|gimp_container_num_children
argument_list|(
name|gimage
operator|->
name|layers
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|,
literal|"image-width"
argument_list|,
name|gimage
operator|->
name|width
argument_list|,
literal|"image-height"
argument_list|,
name|gimage
operator|->
name|height
argument_list|,
literal|"image-type"
argument_list|,
name|type_str
argument_list|,
literal|"image-num-layers"
argument_list|,
name|num_layers
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_thumbnail_save_thumb
argument_list|(
name|imagefile
operator|->
name|thumbnail
argument_list|,
name|pixbuf
argument_list|,
literal|"The GIMP "
name|GIMP_VERSION
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp_imagefile_update
argument_list|(
name|imagefile
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

