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
file|<glib-object.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_define
DECL|macro|F_OK
define|#
directive|define
name|F_OK
value|0
end_define

begin_define
DECL|macro|W_OK
define|#
directive|define
name|W_OK
value|2
end_define

begin_define
DECL|macro|R_OK
define|#
directive|define
name|R_OK
value|4
end_define

begin_define
DECL|macro|X_OK
define|#
directive|define
name|X_OK
value|0
end_define

begin_comment
DECL|macro|X_OK
comment|/* not really */
end_comment

begin_define
DECL|macro|access (f,p)
define|#
directive|define
name|access
parameter_list|(
name|f
parameter_list|,
name|p
parameter_list|)
value|_access(f,p)
end_define

begin_endif
endif|#
directive|endif
end_endif

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

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c765e480103
block|{
DECL|enumerator|DIRTY
name|DIRTY
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
parameter_list|,
name|GimpDataClass
modifier|*
name|data_class
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
name|gint64
name|gimp_data_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
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
name|gimp_data_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|name_changed
operator|=
name|gimp_data_name_changed
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_data_get_memsize
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
DECL|function|gimp_data_init (GimpData * data,GimpDataClass * data_class)
name|gimp_data_init
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
name|GimpDataClass
modifier|*
name|data_class
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
name|writable
operator|=
name|TRUE
expr_stmt|;
name|data
operator|->
name|deletable
operator|=
name|TRUE
expr_stmt|;
name|data
operator|->
name|dirty
operator|=
name|TRUE
expr_stmt|;
name|data
operator|->
name|internal
operator|=
name|FALSE
expr_stmt|;
name|data
operator|->
name|freeze_count
operator|=
literal|0
expr_stmt|;
comment|/*  look at the passed class pointer, not at GIMP_DATA_GET_CLASS(data)    *  here, because the latter is always GimpDataClass itself    */
if|if
condition|(
operator|!
name|data_class
operator|->
name|save
condition|)
name|data
operator|->
name|writable
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
init|=
name|GIMP_DATA
argument_list|(
name|object
argument_list|)
decl_stmt|;
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
specifier|static
name|gint64
DECL|function|gimp_data_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_data_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpData
modifier|*
name|data
init|=
name|GIMP_DATA
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|data
operator|->
name|filename
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|data
operator|->
name|filename
argument_list|)
operator|+
literal|1
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
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

begin_comment
comment|/**  * gimp_data_save:  * @data:  object whose contents are to be saved.  * @error: return location for errors or %NULL  *  * Save the object.  If the object is marked as "internal", nothing happens.  * Otherwise, it is saved to disk, using the file name set by  * gimp_data_set_filename().  If the save is successful, the  * object is marked as not dirty.  If not, an error message is returned  * using the @error argument.  *  * Returns: %TRUE if the object is internal or the save is successful.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_data_save (GimpData * data,GError ** error)
name|gimp_data_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|g_return_val_if_fail
argument_list|(
name|data
operator|->
name|writable
operator|==
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|internal
condition|)
block|{
name|data
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
return|return
name|TRUE
return|;
block|}
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
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|save
condition|)
name|success
operator|=
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|save
argument_list|(
name|data
argument_list|,
name|error
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

begin_comment
comment|/**  * gimp_data_dirty:  * @data: a #GimpData object.  *  * Marks @data as dirty.  Unless the object is frozen, this causes  * its preview to be invalidated, and emits a "dirty" signal.  If the  * object is frozen, the function has no effect.  **/
end_comment

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
if|if
condition|(
name|data
operator|->
name|freeze_count
operator|==
literal|0
condition|)
name|g_signal_emit
argument_list|(
name|data
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

begin_comment
comment|/**  * gimp_data_freeze:  * @data: a #GimpData object.  *  * Increments the freeze count for the object.  A positive freeze count  * prevents the object from being treated as dirty.  Any call to this  * function must be followed eventually by a call to gimp_data_thaw().  **/
end_comment

begin_function
name|void
DECL|function|gimp_data_freeze (GimpData * data)
name|gimp_data_freeze
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
name|data
operator|->
name|freeze_count
operator|++
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_thaw:  * @data: a #GimpData object.  *  * Decrements the freeze count for the object.  If the freeze count  * drops to zero, the object is marked as dirty, and the "dirty"  * signal is emitted.  It is an error to call this function without  * having previously called gimp_data_freeze().  **/
end_comment

begin_function
name|void
DECL|function|gimp_data_thaw (GimpData * data)
name|gimp_data_thaw
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
name|g_return_if_fail
argument_list|(
name|data
operator|->
name|freeze_count
operator|>
literal|0
argument_list|)
expr_stmt|;
name|data
operator|->
name|freeze_count
operator|--
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|freeze_count
operator|==
literal|0
condition|)
name|gimp_data_dirty
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_delete_from_disk:  * @data:  a #GimpData object.  * @error: return location for errors or %NULL  *  * Deletes the object from disk.  If the object is marked as "internal",  * nothing happens.  Otherwise, if the file exists whose name has been  * set by gimp_data_set_filename(), it is deleted.  Obviously this is  * a potentially dangerous function, which should be used with care.  *  * Returns: %TRUE if the object is internal to Gimp, or the deletion is  *          successful.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_data_delete_from_disk (GimpData * data,GError ** error)
name|gimp_data_delete_from_disk
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|g_return_val_if_fail
argument_list|(
name|data
operator|->
name|deletable
operator|==
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|internal
condition|)
return|return
name|TRUE
return|;
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
name|g_set_error
argument_list|(
name|error
argument_list|,
name|GIMP_DATA_ERROR
argument_list|,
name|GIMP_DATA_ERROR_DELETE
argument_list|,
name|_
argument_list|(
literal|"Could not delete '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|data
operator|->
name|filename
argument_list|)
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
if|if
condition|(
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|get_extension
condition|)
return|return
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|get_extension
argument_list|(
name|data
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_set_filename:  * @data:     A #GimpData object  * @filename: File name to assign to @data.  * @writable: %TRUE if we want to be able to write to this file.  *  * This function assigns a file name to @data, and sets some flags  * according to the properties of the file.  If @writable is %TRUE,  * and the user has permission to write or overwrite the requested file  * name, and a "save" method exists for @data's object type, then  * @data is marked as writable.  **/
end_comment

begin_function
name|void
DECL|function|gimp_data_set_filename (GimpData * data,const gchar * filename,gboolean writable)
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
parameter_list|,
name|gboolean
name|writable
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
name|g_return_if_fail
argument_list|(
name|filename
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_path_is_absolute
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|internal
condition|)
return|return;
if|if
condition|(
name|data
operator|->
name|filename
condition|)
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
name|data
operator|->
name|writable
operator|=
name|FALSE
expr_stmt|;
name|data
operator|->
name|deletable
operator|=
name|FALSE
expr_stmt|;
comment|/*  if the data is supposed to be writable, still check if it really is  */
if|if
condition|(
name|writable
condition|)
block|{
name|gchar
modifier|*
name|dirname
init|=
name|g_path_get_dirname
argument_list|(
name|filename
argument_list|)
decl_stmt|;
if|if
condition|(
operator|(
name|access
argument_list|(
name|filename
argument_list|,
name|F_OK
argument_list|)
operator|==
literal|0
operator|&&
comment|/* check if the file exists    */
name|access
argument_list|(
name|filename
argument_list|,
name|W_OK
argument_list|)
operator|==
literal|0
operator|)
operator|||
comment|/* and is writable             */
operator|(
name|access
argument_list|(
name|filename
argument_list|,
name|F_OK
argument_list|)
operator|!=
literal|0
operator|&&
comment|/* OR doesn't exist            */
name|access
argument_list|(
name|dirname
argument_list|,
name|W_OK
argument_list|)
operator|==
literal|0
operator|)
condition|)
comment|/* and we can write to its dir */
block|{
name|data
operator|->
name|writable
operator|=
name|TRUE
expr_stmt|;
name|data
operator|->
name|deletable
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_free
argument_list|(
name|dirname
argument_list|)
expr_stmt|;
comment|/*  if we can't save, we are not writable  */
if|if
condition|(
operator|!
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|save
condition|)
name|data
operator|->
name|writable
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_data_create_filename:  * @data:     a #Gimpdata object.  * @dest_dir: directory in which to create a file name.  *  * This function creates a unique file name to be used for saving  * a representation of @data in the directory @dest_dir.  If the  * user does not have write permission in @dest_dir, then @data  * is marked as "not writable", so you should check on this before  * assuming that @data can be saved.  **/
end_comment

begin_function
name|void
DECL|function|gimp_data_create_filename (GimpData * data,const gchar * dest_dir)
name|gimp_data_create_filename
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dest_dir
parameter_list|)
block|{
name|gchar
modifier|*
name|safename
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|fullpath
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|unum
init|=
literal|1
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
name|dest_dir
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_path_is_absolute
argument_list|(
name|dest_dir
argument_list|)
argument_list|)
expr_stmt|;
name|safename
operator|=
name|g_filename_from_utf8
argument_list|(
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|safename
index|[
literal|0
index|]
operator|==
literal|'.'
condition|)
name|safename
index|[
literal|0
index|]
operator|=
literal|'-'
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|safename
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|safename
index|[
name|i
index|]
operator|==
name|G_DIR_SEPARATOR
operator|||
name|g_ascii_isspace
argument_list|(
name|safename
index|[
name|i
index|]
argument_list|)
condition|)
name|safename
index|[
name|i
index|]
operator|=
literal|'-'
expr_stmt|;
name|filename
operator|=
name|g_strconcat
argument_list|(
name|safename
argument_list|,
name|gimp_data_get_extension
argument_list|(
name|data
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|fullpath
operator|=
name|g_build_filename
argument_list|(
name|dest_dir
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_file_test
argument_list|(
name|fullpath
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|fullpath
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-%d%s"
argument_list|,
name|safename
argument_list|,
name|unum
operator|++
argument_list|,
name|gimp_data_get_extension
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|fullpath
operator|=
name|g_build_filename
argument_list|(
name|dest_dir
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|safename
argument_list|)
expr_stmt|;
name|gimp_data_set_filename
argument_list|(
name|data
argument_list|,
name|fullpath
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|fullpath
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_duplicate:  * @data:              a #GimpData object  * @stingy_memory_use: if %TRUE, use the disk rather than RAM  *                     where possible.  *  * Creates a copy of @data, if possible.  Only the object data is  * copied:  the newly created object is not automatically given an  * object name, file name, preview, etc.  *  * Returns: the newly created copy, or %NULL if @data cannot be copied.  **/
end_comment

begin_function
name|GimpData
modifier|*
DECL|function|gimp_data_duplicate (GimpData * data,gboolean stingy_memory_use)
name|gimp_data_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
name|gboolean
name|stingy_memory_use
parameter_list|)
block|{
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
if|if
condition|(
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|duplicate
condition|)
return|return
name|GIMP_DATA_GET_CLASS
argument_list|(
name|data
argument_list|)
operator|->
name|duplicate
argument_list|(
name|data
argument_list|,
name|stingy_memory_use
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_make_internal:  * @data: a #GimpData object.  *  * Mark @data as "internal" to Gimp, which means that it will not be  * saved to disk.  Note that if you do this, later calls to  * gimp_data_save() and gimp_data_delete_from_disk() will  * automatically return successfully without giving any warning.  **/
end_comment

begin_function
name|void
DECL|function|gimp_data_make_internal (GimpData * data)
name|gimp_data_make_internal
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
name|data
operator|->
name|internal
operator|=
name|TRUE
expr_stmt|;
name|data
operator|->
name|writable
operator|=
name|FALSE
expr_stmt|;
name|data
operator|->
name|deletable
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_name_compare:  * @data1: a #GimpData object.  * @data2: another #GimpData object.  *  * Compares the names of the two objects for use in sorting; see  * gimp_object_name_collate() for the method.  Objects marked as  * "internal" are considered to come before any objects that are not.  *  * Return value: -1 if @data1 compares before @data2,  *                0 if they compare equal,  *                1 if @data1 compares after @data2.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_data_name_compare (GimpData * data1,GimpData * data2)
name|gimp_data_name_compare
parameter_list|(
name|GimpData
modifier|*
name|data1
parameter_list|,
name|GimpData
modifier|*
name|data2
parameter_list|)
block|{
comment|/*  move the internal objects (like the FG -> BG) gradient) to the top  */
if|if
condition|(
name|data1
operator|->
name|internal
operator|!=
name|data2
operator|->
name|internal
condition|)
return|return
name|data1
operator|->
name|internal
condition|?
operator|-
literal|1
else|:
literal|1
return|;
return|return
name|gimp_object_name_collate
argument_list|(
operator|(
name|GimpObject
operator|*
operator|)
name|data1
argument_list|,
operator|(
name|GimpObject
operator|*
operator|)
name|data2
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_data_error_quark:  *  * This function is used to implement the GIMP_DATA_ERROR macro. It  * shouldn't be called directly.  *  * Return value: the #GQuark to identify error in the GimpData error domain.  **/
end_comment

begin_function
name|GQuark
DECL|function|gimp_data_error_quark (void)
name|gimp_data_error_quark
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GQuark
name|quark
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|quark
condition|)
name|quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-data-error-quark"
argument_list|)
expr_stmt|;
return|return
name|quark
return|;
block|}
end_function

end_unit

