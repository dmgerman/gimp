begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdata.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29db1f0e0103
block|{
DECL|enumerator|DIRTY
name|DIRTY
block|,
DECL|enumerator|SAVE
name|SAVE
block|,
DECL|enumerator|GET_EXTENSION
name|GET_EXTENSION
block|,
DECL|enumerator|DUPLICATE
name|DUPLICATE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_data_class_init
parameter_list|(
name|GimpDataClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_init
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_data_finalize
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
name|gimp_data_name_changed
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
name|gimp_data_real_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|data_signals
specifier|static
name|guint
name|data_signals
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
DECL|function|gimp_data_get_type (void)
name|gimp_data_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|data_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|data_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|data_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpDataClass
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
name|gimp_data_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpData
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_data_init
block|,       }
decl_stmt|;
name|data_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_VIEWABLE
argument_list|,
literal|"GimpData"
argument_list|,
operator|&
name|data_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|data_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_class_init (GimpDataClass * klass)
name|gimp_data_class_init
parameter_list|(
name|GimpDataClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|data_signals
index|[
name|DIRTY
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"dirty"
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
name|GimpDataClass
argument_list|,
name|dirty
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|data_signals
index|[
name|SAVE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"save"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpDataClass
argument_list|,
name|save
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_BOOLEAN__VOID
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|data_signals
index|[
name|GET_EXTENSION
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"get_extension"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpDataClass
argument_list|,
name|get_extension
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_POINTER__VOID
argument_list|,
name|G_TYPE_POINTER
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|data_signals
index|[
name|DUPLICATE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"duplicate"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_LAST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpDataClass
argument_list|,
name|duplicate
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_cclosure_marshal_POINTER__VOID
argument_list|,
name|G_TYPE_POINTER
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_data_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|name_changed
operator|=
name|gimp_data_name_changed
expr_stmt|;
name|klass
operator|->
name|dirty
operator|=
name|gimp_data_real_dirty
expr_stmt|;
name|klass
operator|->
name|save
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_extension
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|duplicate
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_init (GimpData * data)
name|gimp_data_init
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|data
operator|->
name|filename
operator|=
name|NULL
expr_stmt|;
name|data
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_data_finalize (GObject * object)
name|gimp_data_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|filename
condition|)
block|{
name|g_free
argument_list|(
name|data
operator|->
name|filename
argument_list|)
expr_stmt|;
name|data
operator|->
name|filename
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
name|void
DECL|function|gimp_data_name_changed (GimpObject * object)
name|gimp_data_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
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
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_data_save (GimpData * data)
name|gimp_data_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|data
operator|->
name|filename
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s(): can't save data with NULL filename"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|data_signals
index|[
name|SAVE
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|data
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_dirty (GimpData * data)
name|gimp_data_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|data_signals
index|[
name|DIRTY
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
DECL|function|gimp_data_real_dirty (GimpData * data)
name|gimp_data_real_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|data
operator|->
name|dirty
operator|=
name|TRUE
expr_stmt|;
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_data_delete_from_disk (GimpData * data)
name|gimp_data_delete_from_disk
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|data
operator|->
name|filename
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|unlink
argument_list|(
name|data
operator|->
name|filename
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|g_message
argument_list|(
literal|"%s(): could not unlink() %s: %s"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|,
name|data
operator|->
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_data_get_extension (GimpData * data)
name|gimp_data_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|extension
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|data_signals
index|[
name|GET_EXTENSION
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|extension
argument_list|)
expr_stmt|;
return|return
name|extension
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_set_filename (GimpData * data,const gchar * filename)
name|gimp_data_set_filename
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|filename
argument_list|)
expr_stmt|;
name|data
operator|->
name|filename
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_data_create_filename (GimpData * data,const gchar * basename,const gchar * data_path)
name|gimp_data_create_filename
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|basename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|data_path
parameter_list|)
block|{
name|GList
modifier|*
name|path
decl_stmt|;
name|gchar
modifier|*
name|dir
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|safe_name
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|unum
init|=
literal|1
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DATA
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|basename
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|data_path
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|path
operator|=
name|gimp_path_parse
argument_list|(
name|data_path
argument_list|,
literal|16
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dir
operator|=
name|gimp_path_get_user_writable_dir
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|gimp_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dir
condition|)
return|return;
name|safe_name
operator|=
name|g_strdup
argument_list|(
name|basename
argument_list|)
expr_stmt|;
if|if
condition|(
name|safe_name
index|[
literal|0
index|]
operator|==
literal|'.'
condition|)
name|safe_name
index|[
literal|0
index|]
operator|=
literal|'_'
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|safe_name
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|safe_name
index|[
name|i
index|]
operator|==
name|G_DIR_SEPARATOR
operator|||
name|isspace
argument_list|(
name|safe_name
index|[
name|i
index|]
argument_list|)
condition|)
name|safe_name
index|[
name|i
index|]
operator|=
literal|'_'
expr_stmt|;
name|filename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s%s%s"
argument_list|,
name|dir
argument_list|,
name|safe_name
argument_list|,
name|gimp_data_get_extension
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|file
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"r"
argument_list|)
operator|)
condition|)
block|{
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s%s_%d%s"
argument_list|,
name|dir
argument_list|,
name|safe_name
argument_list|,
name|unum
argument_list|,
name|gimp_data_get_extension
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|unum
operator|++
expr_stmt|;
block|}
name|g_free
argument_list|(
name|dir
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|safe_name
argument_list|)
expr_stmt|;
name|gimp_data_set_filename
argument_list|(
name|data
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpData
modifier|*
DECL|function|gimp_data_duplicate (GimpData * data)
name|gimp_data_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpData
modifier|*
name|new_data
init|=
name|NULL
decl_stmt|;
name|g_signal_emit
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|data_signals
index|[
name|DUPLICATE
index|]
argument_list|,
literal|0
argument_list|,
operator|&
name|new_data
argument_list|)
expr_stmt|;
return|return
name|new_data
return|;
block|}
end_function

end_unit

