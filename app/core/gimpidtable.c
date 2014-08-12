begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpidtable.c  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-memsize.h"
end_include

begin_include
include|#
directive|include
file|"gimpidtable.h"
end_include

begin_define
DECL|macro|GIMP_ID_TABLE_START_ID
define|#
directive|define
name|GIMP_ID_TABLE_START_ID
value|1
end_define

begin_define
DECL|macro|GIMP_ID_TABLE_END_ID
define|#
directive|define
name|GIMP_ID_TABLE_END_ID
value|G_MAXINT
end_define

begin_struct
DECL|struct|_GimpIdTablePriv
struct|struct
name|_GimpIdTablePriv
block|{
DECL|member|id_table
name|GHashTable
modifier|*
name|id_table
decl_stmt|;
DECL|member|next_id
name|gint
name|next_id
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_id_table_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_id_table_get_memsize
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpIdTable,gimp_id_table,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpIdTable
argument_list|,
argument|gimp_id_table
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_id_table_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_id_table_class_init
parameter_list|(
name|GimpIdTableClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpIdTableClass
modifier|*
name|gimp_id_table_class
init|=
name|GIMP_ID_TABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_id_table_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_id_table_get_memsize
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|gimp_id_table_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpIdTablePriv
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_id_table_init (GimpIdTable * id_table)
name|gimp_id_table_init
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|)
block|{
name|id_table
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|id_table
argument_list|,
name|GIMP_TYPE_ID_TABLE
argument_list|,
name|GimpIdTablePriv
argument_list|)
expr_stmt|;
name|id_table
operator|->
name|priv
operator|->
name|id_table
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|id_table
operator|->
name|priv
operator|->
name|next_id
operator|=
name|GIMP_ID_TABLE_START_ID
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_id_table_finalize (GObject * object)
name|gimp_id_table_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpIdTable
modifier|*
name|id_table
init|=
name|GIMP_ID_TABLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|id_table
operator|->
name|priv
operator|->
name|id_table
condition|)
block|{
name|g_hash_table_unref
argument_list|(
name|id_table
operator|->
name|priv
operator|->
name|id_table
argument_list|)
expr_stmt|;
name|id_table
operator|->
name|priv
operator|->
name|id_table
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
name|gint64
DECL|function|gimp_id_table_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_id_table_get_memsize
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
name|GimpIdTable
modifier|*
name|id_table
init|=
name|GIMP_ID_TABLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_g_hash_table_get_memsize
argument_list|(
name|id_table
operator|->
name|priv
operator|->
name|id_table
argument_list|,
literal|0
argument_list|)
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

begin_comment
comment|/**  * gimp_id_table_new:  *  * Returns: A new #GimpIdTable.  **/
end_comment

begin_function
name|GimpIdTable
modifier|*
DECL|function|gimp_id_table_new (void)
name|gimp_id_table_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_ID_TABLE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_id_table_insert:  * @id_table: A #GimpIdTable  * @data: Data to insert and assign an id to  *  * Insert data in the id table. The data will get an, in this table,  * unused ID assigned to it that can be used to later lookup the data.  *  * Returns: The assigned ID.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_id_table_insert (GimpIdTable * id_table,gpointer data)
name|gimp_id_table_insert
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gint
name|new_id
decl_stmt|;
name|gint
name|start_id
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ID_TABLE
argument_list|(
name|id_table
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|start_id
operator|=
name|id_table
operator|->
name|priv
operator|->
name|next_id
expr_stmt|;
do|do
block|{
name|new_id
operator|=
name|id_table
operator|->
name|priv
operator|->
name|next_id
operator|++
expr_stmt|;
if|if
condition|(
name|id_table
operator|->
name|priv
operator|->
name|next_id
operator|==
name|GIMP_ID_TABLE_END_ID
condition|)
name|id_table
operator|->
name|priv
operator|->
name|next_id
operator|=
name|GIMP_ID_TABLE_START_ID
expr_stmt|;
if|if
condition|(
name|start_id
operator|==
name|id_table
operator|->
name|priv
operator|->
name|next_id
condition|)
block|{
comment|/* We looped once over all used ids. Very unlikely to happen.              And if it does, there is probably not much to be done.              It is just good design not to allow a theoretical infinite loop. */
name|g_error
argument_list|(
literal|"%s: out of ids!"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
do|while
condition|(
name|gimp_id_table_lookup
argument_list|(
name|id_table
argument_list|,
name|new_id
argument_list|)
condition|)
do|;
return|return
name|gimp_id_table_insert_with_id
argument_list|(
name|id_table
argument_list|,
name|new_id
argument_list|,
name|data
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_id_table_insert_with_id:  * @id_table: An #GimpIdTable  * @id: The ID to use. Must be greater than 0.  * @data: The data to associate with the id  *  * Insert data in the id table with a specific ID. If data already  * exsts with the given ID, this function fails.  *  * Returns: The used ID if successful, -1 if it was already in use.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_id_table_insert_with_id (GimpIdTable * id_table,gint id,gpointer data)
name|gimp_id_table_insert_with_id
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gint
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ID_TABLE
argument_list|(
name|id_table
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|id
operator|>
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_id_table_lookup
argument_list|(
name|id_table
argument_list|,
name|id
argument_list|)
condition|)
return|return
operator|-
literal|1
return|;
name|g_hash_table_insert
argument_list|(
name|id_table
operator|->
name|priv
operator|->
name|id_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|id
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|id
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_id_table_replace:  * @id_table: An #GimpIdTable  * @id: The ID to use. Must be greater than 0.  * @data: The data to insert/replace  *  * Replaces (if an item with the given ID exists) or inserts a new  * entry in the id table.  **/
end_comment

begin_function
name|void
DECL|function|gimp_id_table_replace (GimpIdTable * id_table,gint id,gpointer data)
name|gimp_id_table_replace
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gint
name|id
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ID_TABLE
argument_list|(
name|id_table
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|id
operator|>
literal|0
argument_list|)
expr_stmt|;
name|g_hash_table_replace
argument_list|(
name|id_table
operator|->
name|priv
operator|->
name|id_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|id
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_id_table_lookup:  * @id_table: An #GimpIdTable  * @id: The ID of the data to lookup  *  * Lookup data based on ID.  *  * Returns: The data, or NULL if no data with the given ID was found.  **/
end_comment

begin_function
name|gpointer
DECL|function|gimp_id_table_lookup (GimpIdTable * id_table,gint id)
name|gimp_id_table_lookup
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gint
name|id
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ID_TABLE
argument_list|(
name|id_table
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_hash_table_lookup
argument_list|(
name|id_table
operator|->
name|priv
operator|->
name|id_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|id
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_id_table_remove:  * @id_table: An #GimpIdTable  * @id: The ID of the data to remove.  *  * Remove the data from the table with the given ID.  *  * Returns: %TRUE if data with the ID existed and was successfully  *          removed, %FALSE otherwise.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_id_table_remove (GimpIdTable * id_table,gint id)
name|gimp_id_table_remove
parameter_list|(
name|GimpIdTable
modifier|*
name|id_table
parameter_list|,
name|gint
name|id
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_ID_TABLE
argument_list|(
name|id_table
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|id_table
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|g_hash_table_remove
argument_list|(
name|id_table
operator|->
name|priv
operator|->
name|id_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|id
argument_list|)
argument_list|)
return|;
block|}
end_function

end_unit

