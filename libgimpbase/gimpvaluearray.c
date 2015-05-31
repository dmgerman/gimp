begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpvaluearray.c ported from GValueArray  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpvaluearray.h"
end_include

begin_comment
comment|/**  * SECTION:gimpvaluearray  * @short_description: A container structure to maintain an array of  *     generic values  * @see_also: #GValue, #GParamSpecValueArray, gimp_param_spec_value_array()  * @title: GimpValueArray  *  * The prime purpose of a #GimpValueArray is for it to be used as an  * object property that holds an array of values. A #GimpValueArray wraps  * an array of #GValue elements in order for it to be used as a boxed  * type through %GIMP_TYPE_VALUE_ARRAY.  */
end_comment

begin_define
DECL|macro|GROUP_N_VALUES
define|#
directive|define
name|GROUP_N_VALUES
value|(1)
end_define

begin_comment
DECL|macro|GROUP_N_VALUES
comment|/* power of 2 !! */
end_comment

begin_comment
comment|/**  * GimpValueArray:  *  * A #GimpValueArray contains an array of #GValue elements.  *  * Since: GIMP 2.10  */
end_comment

begin_struct
DECL|struct|_GimpValueArray
struct|struct
name|_GimpValueArray
block|{
DECL|member|n_values
name|gint
name|n_values
decl_stmt|;
DECL|member|values
name|GValue
modifier|*
name|values
decl_stmt|;
DECL|member|n_prealloced
name|gint
name|n_prealloced
decl_stmt|;
DECL|member|ref_count
name|gint
name|ref_count
decl_stmt|;
block|}
struct|;
end_struct

begin_macro
DECL|function|G_DEFINE_BOXED_TYPE (GimpValueArray,gimp_value_array,gimp_value_array_ref,gimp_value_array_unref)
name|G_DEFINE_BOXED_TYPE
argument_list|(
argument|GimpValueArray
argument_list|,
argument|gimp_value_array
argument_list|,
argument|gimp_value_array_ref
argument_list|,
argument|gimp_value_array_unref
argument_list|)
end_macro

begin_comment
comment|/**  * gimp_value_array_index:  * @value_array: #GimpValueArray to get a value from  * @index: index of the value of interest  *  * Return a pointer to the value at @index containd in @value_array.  *  * Returns: (transfer none): pointer to a value at @index in @value_array  *  * Since: GIMP 2.10  */
end_comment

begin_function
name|GValue
modifier|*
name|gimp_value_array_index
parameter_list|(
specifier|const
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|index
operator|<
name|value_array
operator|->
name|n_values
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|value_array
operator|->
name|values
operator|+
name|index
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|value_array_grow (GimpValueArray * value_array,gint n_values,gboolean zero_init)
name|value_array_grow
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|n_values
parameter_list|,
name|gboolean
name|zero_init
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
operator|(
name|guint
operator|)
name|n_values
operator|>=
operator|(
name|guint
operator|)
name|value_array
operator|->
name|n_values
argument_list|)
expr_stmt|;
name|value_array
operator|->
name|n_values
operator|=
name|n_values
expr_stmt|;
if|if
condition|(
name|value_array
operator|->
name|n_values
operator|>
name|value_array
operator|->
name|n_prealloced
condition|)
block|{
name|gint
name|i
init|=
name|value_array
operator|->
name|n_prealloced
decl_stmt|;
name|value_array
operator|->
name|n_prealloced
operator|=
operator|(
name|value_array
operator|->
name|n_values
operator|+
name|GROUP_N_VALUES
operator|-
literal|1
operator|)
operator|&
operator|~
operator|(
name|GROUP_N_VALUES
operator|-
literal|1
operator|)
expr_stmt|;
name|value_array
operator|->
name|values
operator|=
name|g_renew
argument_list|(
name|GValue
argument_list|,
name|value_array
operator|->
name|values
argument_list|,
name|value_array
operator|->
name|n_prealloced
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|zero_init
condition|)
name|i
operator|=
name|value_array
operator|->
name|n_values
expr_stmt|;
name|memset
argument_list|(
name|value_array
operator|->
name|values
operator|+
name|i
argument_list|,
literal|0
argument_list|,
operator|(
name|value_array
operator|->
name|n_prealloced
operator|-
name|i
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|value_array
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|value_array_shrink (GimpValueArray * value_array)
name|value_array_shrink
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|)
block|{
if|if
condition|(
name|value_array
operator|->
name|n_prealloced
operator|>=
name|value_array
operator|->
name|n_values
operator|+
name|GROUP_N_VALUES
condition|)
block|{
name|value_array
operator|->
name|n_prealloced
operator|=
operator|(
name|value_array
operator|->
name|n_values
operator|+
name|GROUP_N_VALUES
operator|-
literal|1
operator|)
operator|&
operator|~
operator|(
name|GROUP_N_VALUES
operator|-
literal|1
operator|)
expr_stmt|;
name|value_array
operator|->
name|values
operator|=
name|g_renew
argument_list|(
name|GValue
argument_list|,
name|value_array
operator|->
name|values
argument_list|,
name|value_array
operator|->
name|n_prealloced
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_value_array_new:  * @n_prealloced: number of values to preallocate space for  *  * Allocate and initialize a new #GimpValueArray, optionally preserve space  * for @n_prealloced elements. New arrays always contain 0 elements,  * regardless of the value of @n_prealloced.  *  * Returns: a newly allocated #GimpValueArray with 0 values  *  * Since: GIMP 2.10  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_value_array_new (gint n_prealloced)
name|gimp_value_array_new
parameter_list|(
name|gint
name|n_prealloced
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|value_array
init|=
name|g_slice_new
argument_list|(
name|GimpValueArray
argument_list|)
decl_stmt|;
name|value_array
operator|->
name|n_values
operator|=
literal|0
expr_stmt|;
name|value_array
operator|->
name|n_prealloced
operator|=
literal|0
expr_stmt|;
name|value_array
operator|->
name|values
operator|=
name|NULL
expr_stmt|;
name|value_array_grow
argument_list|(
name|value_array
argument_list|,
name|n_prealloced
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|value_array
operator|->
name|n_values
operator|=
literal|0
expr_stmt|;
name|value_array
operator|->
name|ref_count
operator|=
literal|1
expr_stmt|;
return|return
name|value_array
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_value_array_ref:  * @value_array: #GimpValueArray to ref  *  * Adds a reference to a #GimpValueArray.  *  * Return value: the same @value_array  *  * Since: GIMP 2.10  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_value_array_ref (GimpValueArray * value_array)
name|gimp_value_array_ref
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|value_array
operator|->
name|ref_count
operator|++
expr_stmt|;
return|return
name|value_array
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_value_array_unref:  * @value_array: #GimpValueArray to unref  *  * Unref a #GimpValueArray. If the reference count drops to zero, the  * array including its contents are freed.  *  * Since: GIMP 2.10  */
end_comment

begin_function
name|void
DECL|function|gimp_value_array_unref (GimpValueArray * value_array)
name|gimp_value_array_unref
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|value_array
operator|->
name|ref_count
operator|--
expr_stmt|;
if|if
condition|(
name|value_array
operator|->
name|ref_count
operator|<
literal|1
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|value_array
operator|->
name|n_values
condition|;
name|i
operator|++
control|)
block|{
name|GValue
modifier|*
name|value
init|=
name|value_array
operator|->
name|values
operator|+
name|i
decl_stmt|;
if|if
condition|(
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
operator|!=
literal|0
condition|)
comment|/* we allow unset values in the array */
name|g_value_unset
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|value_array
operator|->
name|values
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpValueArray
argument_list|,
name|value_array
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gimp_value_array_length (const GimpValueArray * value_array)
name|gimp_value_array_length
parameter_list|(
specifier|const
name|GimpValueArray
modifier|*
name|value_array
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|value_array
operator|->
name|n_values
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_value_array_prepend:  * @value_array: #GimpValueArray to add an element to  * @value: (allow-none): #GValue to copy into #GimpValueArray, or %NULL  *  * Insert a copy of @value as first element of @value_array. If @value is  * %NULL, an uninitialized value is prepended.  *  * Returns: (transfer none): the #GimpValueArray passed in as @value_array  *  * Since: GIMP 2.10  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_value_array_prepend (GimpValueArray * value_array,const GValue * value)
name|gimp_value_array_prepend
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_value_array_insert
argument_list|(
name|value_array
argument_list|,
literal|0
argument_list|,
name|value
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_value_array_append:  * @value_array: #GimpValueArray to add an element to  * @value: (allow-none): #GValue to copy into #GimpValueArray, or %NULL  *  * Insert a copy of @value as last element of @value_array. If @value is  * %NULL, an uninitialized value is appended.  *  * Returns: (transfer none): the #GimpValueArray passed in as @value_array  *  * Since: GIMP 2.10  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_value_array_append (GimpValueArray * value_array,const GValue * value)
name|gimp_value_array_append
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_value_array_insert
argument_list|(
name|value_array
argument_list|,
name|value_array
operator|->
name|n_values
argument_list|,
name|value
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_value_array_insert:  * @value_array: #GimpValueArray to add an element to  * @index: insertion position, must be&lt;= gimp_value_array_length()  * @value: (allow-none): #GValue to copy into #GimpValueArray, or %NULL  *  * Insert a copy of @value at specified position into @value_array. If @value  * is %NULL, an uninitialized value is inserted.  *  * Returns: (transfer none): the #GimpValueArray passed in as @value_array  *  * Since: GIMP 2.10  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_value_array_insert (GimpValueArray * value_array,gint index,const GValue * value)
name|gimp_value_array_insert
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|index
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|index
operator|<=
name|value_array
operator|->
name|n_values
argument_list|,
name|value_array
argument_list|)
expr_stmt|;
name|i
operator|=
name|value_array
operator|->
name|n_values
expr_stmt|;
name|value_array_grow
argument_list|(
name|value_array
argument_list|,
name|value_array
operator|->
name|n_values
operator|+
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|+
literal|1
operator|<
name|value_array
operator|->
name|n_values
condition|)
name|memmove
argument_list|(
name|value_array
operator|->
name|values
operator|+
name|index
operator|+
literal|1
argument_list|,
name|value_array
operator|->
name|values
operator|+
name|index
argument_list|,
operator|(
name|i
operator|-
name|index
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|value_array
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|value_array
operator|->
name|values
operator|+
name|index
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|value_array
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
name|g_value_init
argument_list|(
name|value_array
operator|->
name|values
operator|+
name|index
argument_list|,
name|G_VALUE_TYPE
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
name|g_value_copy
argument_list|(
name|value
argument_list|,
name|value_array
operator|->
name|values
operator|+
name|index
argument_list|)
expr_stmt|;
block|}
return|return
name|value_array
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_value_array_remove:  * @value_array: #GimpValueArray to remove an element from  * @index: position of value to remove, which must be less than  *         gimp_value_array_length()  *  * Remove the value at position @index from @value_array.  *  * Returns: (transfer none): the #GimpValueArray passed in as @value_array  *  * Since: GIMP 2.10  */
end_comment

begin_function
name|GimpValueArray
modifier|*
DECL|function|gimp_value_array_remove (GimpValueArray * value_array,gint index)
name|gimp_value_array_remove
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|index
operator|<
name|value_array
operator|->
name|n_values
argument_list|,
name|value_array
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_VALUE_TYPE
argument_list|(
name|value_array
operator|->
name|values
operator|+
name|index
argument_list|)
operator|!=
literal|0
condition|)
name|g_value_unset
argument_list|(
name|value_array
operator|->
name|values
operator|+
name|index
argument_list|)
expr_stmt|;
name|value_array
operator|->
name|n_values
operator|--
expr_stmt|;
if|if
condition|(
name|index
operator|<
name|value_array
operator|->
name|n_values
condition|)
name|memmove
argument_list|(
name|value_array
operator|->
name|values
operator|+
name|index
argument_list|,
name|value_array
operator|->
name|values
operator|+
name|index
operator|+
literal|1
argument_list|,
operator|(
name|value_array
operator|->
name|n_values
operator|-
name|index
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|value_array
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|value_array_shrink
argument_list|(
name|value_array
argument_list|)
expr_stmt|;
if|if
condition|(
name|value_array
operator|->
name|n_prealloced
operator|>
name|value_array
operator|->
name|n_values
condition|)
name|memset
argument_list|(
name|value_array
operator|->
name|values
operator|+
name|value_array
operator|->
name|n_values
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|value_array
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|value_array
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_value_array_truncate (GimpValueArray * value_array,gint n_values)
name|gimp_value_array_truncate
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|gint
name|n_values
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|value_array
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|n_values
operator|>
literal|0
operator|&&
name|n_values
operator|<=
name|value_array
operator|->
name|n_values
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|value_array
operator|->
name|n_values
init|;
name|i
operator|>
name|n_values
condition|;
name|i
operator|--
control|)
name|gimp_value_array_remove
argument_list|(
name|value_array
argument_list|,
name|i
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * GIMP_TYPE_PARAM_VALUE_ARRAY  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_param_value_array_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_value_array_init
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_value_array_finalize
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_param_value_array_set_default
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_param_value_array_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_param_value_array_values_cmp
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value1
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value2
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|GType
DECL|function|gimp_param_value_array_get_type (void)
name|gimp_param_value_array_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GParamSpecClass
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_param_value_array_class_init
block|,
name|NULL
block|,
name|NULL
block|,
sizeof|sizeof
argument_list|(
name|GimpParamSpecValueArray
argument_list|)
block|,
literal|0
block|,
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_param_value_array_init
block|}
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_PARAM_BOXED
argument_list|,
literal|"GimpParamValueArray"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_value_array_class_init (GParamSpecClass * klass)
name|gimp_param_value_array_class_init
parameter_list|(
name|GParamSpecClass
modifier|*
name|klass
parameter_list|)
block|{
name|klass
operator|->
name|value_type
operator|=
name|GIMP_TYPE_VALUE_ARRAY
expr_stmt|;
name|klass
operator|->
name|finalize
operator|=
name|gimp_param_value_array_finalize
expr_stmt|;
name|klass
operator|->
name|value_set_default
operator|=
name|gimp_param_value_array_set_default
expr_stmt|;
name|klass
operator|->
name|value_validate
operator|=
name|gimp_param_value_array_validate
expr_stmt|;
name|klass
operator|->
name|values_cmp
operator|=
name|gimp_param_value_array_values_cmp
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_value_array_init (GParamSpec * pspec)
name|gimp_param_value_array_init
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpParamSpecValueArray
modifier|*
name|aspec
init|=
name|GIMP_PARAM_SPEC_VALUE_ARRAY
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|aspec
operator|->
name|element_spec
operator|=
name|NULL
expr_stmt|;
name|aspec
operator|->
name|fixed_n_elements
operator|=
literal|0
expr_stmt|;
comment|/* disable */
block|}
end_function

begin_function
specifier|static
specifier|inline
name|guint
DECL|function|gimp_value_array_ensure_size (GimpValueArray * value_array,guint fixed_n_elements)
name|gimp_value_array_ensure_size
parameter_list|(
name|GimpValueArray
modifier|*
name|value_array
parameter_list|,
name|guint
name|fixed_n_elements
parameter_list|)
block|{
name|guint
name|changed
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|fixed_n_elements
condition|)
block|{
while|while
condition|(
name|gimp_value_array_length
argument_list|(
name|value_array
argument_list|)
operator|<
name|fixed_n_elements
condition|)
block|{
name|gimp_value_array_append
argument_list|(
name|value_array
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|changed
operator|++
expr_stmt|;
block|}
while|while
condition|(
name|gimp_value_array_length
argument_list|(
name|value_array
argument_list|)
operator|>
name|fixed_n_elements
condition|)
block|{
name|gimp_value_array_remove
argument_list|(
name|value_array
argument_list|,
name|gimp_value_array_length
argument_list|(
name|value_array
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|changed
operator|++
expr_stmt|;
block|}
block|}
return|return
name|changed
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_value_array_finalize (GParamSpec * pspec)
name|gimp_param_value_array_finalize
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpParamSpecValueArray
modifier|*
name|aspec
init|=
name|GIMP_PARAM_SPEC_VALUE_ARRAY
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|GParamSpecClass
modifier|*
name|parent_class
init|=
name|g_type_class_peek
argument_list|(
name|g_type_parent
argument_list|(
name|GIMP_TYPE_PARAM_VALUE_ARRAY
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|aspec
operator|->
name|element_spec
condition|)
block|{
name|g_param_spec_unref
argument_list|(
name|aspec
operator|->
name|element_spec
argument_list|)
expr_stmt|;
name|aspec
operator|->
name|element_spec
operator|=
name|NULL
expr_stmt|;
block|}
name|parent_class
operator|->
name|finalize
argument_list|(
name|pspec
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_param_value_array_set_default (GParamSpec * pspec,GValue * value)
name|gimp_param_value_array_set_default
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpParamSpecValueArray
modifier|*
name|aspec
init|=
name|GIMP_PARAM_SPEC_VALUE_ARRAY
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
operator|&&
name|aspec
operator|->
name|fixed_n_elements
condition|)
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
operator|=
name|gimp_value_array_new
argument_list|(
name|aspec
operator|->
name|fixed_n_elements
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
condition|)
block|{
comment|/* g_value_reset (value);  already done */
name|gimp_value_array_ensure_size
argument_list|(
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
argument_list|,
name|aspec
operator|->
name|fixed_n_elements
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_param_value_array_validate (GParamSpec * pspec,GValue * value)
name|gimp_param_value_array_validate
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
block|{
name|GimpParamSpecValueArray
modifier|*
name|aspec
init|=
name|GIMP_PARAM_SPEC_VALUE_ARRAY
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|GimpValueArray
modifier|*
name|value_array
init|=
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
decl_stmt|;
name|guint
name|changed
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
operator|&&
name|aspec
operator|->
name|fixed_n_elements
condition|)
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
operator|=
name|gimp_value_array_new
argument_list|(
name|aspec
operator|->
name|fixed_n_elements
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
condition|)
block|{
comment|/* ensure array size validity */
name|changed
operator|+=
name|gimp_value_array_ensure_size
argument_list|(
name|value_array
argument_list|,
name|aspec
operator|->
name|fixed_n_elements
argument_list|)
expr_stmt|;
comment|/* ensure array values validity against a present element spec */
if|if
condition|(
name|aspec
operator|->
name|element_spec
condition|)
block|{
name|GParamSpec
modifier|*
name|element_spec
init|=
name|aspec
operator|->
name|element_spec
decl_stmt|;
name|gint
name|length
init|=
name|gimp_value_array_length
argument_list|(
name|value_array
argument_list|)
decl_stmt|;
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|length
condition|;
name|i
operator|++
control|)
block|{
name|GValue
modifier|*
name|element
init|=
name|gimp_value_array_index
argument_list|(
name|value_array
argument_list|,
name|i
argument_list|)
decl_stmt|;
comment|/* need to fixup value type, or ensure that the array                * value is initialized at all                */
if|if
condition|(
operator|!
name|g_value_type_compatible
argument_list|(
name|G_VALUE_TYPE
argument_list|(
name|element
argument_list|)
argument_list|,
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|element_spec
argument_list|)
argument_list|)
condition|)
block|{
if|if
condition|(
name|G_VALUE_TYPE
argument_list|(
name|element
argument_list|)
operator|!=
literal|0
condition|)
name|g_value_unset
argument_list|(
name|element
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
name|element
argument_list|,
name|G_PARAM_SPEC_VALUE_TYPE
argument_list|(
name|element_spec
argument_list|)
argument_list|)
expr_stmt|;
name|g_param_value_set_default
argument_list|(
name|element_spec
argument_list|,
name|element
argument_list|)
expr_stmt|;
name|changed
operator|++
expr_stmt|;
block|}
comment|/* validate array value against element_spec */
name|changed
operator|+=
name|g_param_value_validate
argument_list|(
name|element_spec
argument_list|,
name|element
argument_list|)
expr_stmt|;
block|}
block|}
block|}
return|return
name|changed
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|gimp_param_value_array_values_cmp (GParamSpec * pspec,const GValue * value1,const GValue * value2)
name|gimp_param_value_array_values_cmp
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value1
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value2
parameter_list|)
block|{
name|GimpParamSpecValueArray
modifier|*
name|aspec
init|=
name|GIMP_PARAM_SPEC_VALUE_ARRAY
argument_list|(
name|pspec
argument_list|)
decl_stmt|;
name|GimpValueArray
modifier|*
name|value_array1
init|=
name|value1
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
decl_stmt|;
name|GimpValueArray
modifier|*
name|value_array2
init|=
name|value2
operator|->
name|data
index|[
literal|0
index|]
operator|.
name|v_pointer
decl_stmt|;
name|gint
name|length1
decl_stmt|;
name|gint
name|length2
decl_stmt|;
if|if
condition|(
operator|!
name|value_array1
operator|||
operator|!
name|value_array2
condition|)
return|return
name|value_array2
condition|?
operator|-
literal|1
else|:
name|value_array1
operator|!=
name|value_array2
return|;
name|length1
operator|=
name|gimp_value_array_length
argument_list|(
name|value_array1
argument_list|)
expr_stmt|;
name|length2
operator|=
name|gimp_value_array_length
argument_list|(
name|value_array2
argument_list|)
expr_stmt|;
if|if
condition|(
name|length1
operator|!=
name|length2
condition|)
block|{
return|return
name|length1
operator|<
name|length2
condition|?
operator|-
literal|1
else|:
literal|1
return|;
block|}
elseif|else
if|if
condition|(
operator|!
name|aspec
operator|->
name|element_spec
condition|)
block|{
comment|/* we need an element specification for comparisons, so there's        * not much to compare here, try to at least provide stable        * lesser/greater result        */
return|return
name|length1
operator|<
name|length2
condition|?
operator|-
literal|1
else|:
name|length1
operator|>
name|length2
return|;
block|}
else|else
comment|/* length1 == length2 */
block|{
name|guint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|length1
condition|;
name|i
operator|++
control|)
block|{
name|GValue
modifier|*
name|element1
init|=
name|gimp_value_array_index
argument_list|(
name|value_array1
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|GValue
modifier|*
name|element2
init|=
name|gimp_value_array_index
argument_list|(
name|value_array2
argument_list|,
name|i
argument_list|)
decl_stmt|;
name|gint
name|cmp
decl_stmt|;
comment|/* need corresponding element types, provide stable result            * otherwise            */
if|if
condition|(
name|G_VALUE_TYPE
argument_list|(
name|element1
argument_list|)
operator|!=
name|G_VALUE_TYPE
argument_list|(
name|element2
argument_list|)
condition|)
return|return
name|G_VALUE_TYPE
argument_list|(
name|element1
argument_list|)
operator|<
name|G_VALUE_TYPE
argument_list|(
name|element2
argument_list|)
condition|?
operator|-
literal|1
else|:
literal|1
return|;
name|cmp
operator|=
name|g_param_values_cmp
argument_list|(
name|aspec
operator|->
name|element_spec
argument_list|,
name|element1
argument_list|,
name|element2
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmp
condition|)
return|return
name|cmp
return|;
block|}
return|return
literal|0
return|;
block|}
block|}
end_function

begin_function
name|GParamSpec
modifier|*
DECL|function|gimp_param_spec_value_array (const gchar * name,const gchar * nick,const gchar * blurb,GParamSpec * element_spec,GParamFlags flags)
name|gimp_param_spec_value_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|nick
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
name|GParamSpec
modifier|*
name|element_spec
parameter_list|,
name|GParamFlags
name|flags
parameter_list|)
block|{
name|GimpParamSpecValueArray
modifier|*
name|aspec
decl_stmt|;
if|if
condition|(
name|element_spec
condition|)
name|g_return_val_if_fail
argument_list|(
name|G_IS_PARAM_SPEC
argument_list|(
name|element_spec
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|aspec
operator|=
name|g_param_spec_internal
argument_list|(
name|GIMP_TYPE_PARAM_VALUE_ARRAY
argument_list|,
name|name
argument_list|,
name|nick
argument_list|,
name|blurb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|element_spec
condition|)
block|{
name|aspec
operator|->
name|element_spec
operator|=
name|g_param_spec_ref
argument_list|(
name|element_spec
argument_list|)
expr_stmt|;
name|g_param_spec_sink
argument_list|(
name|element_spec
argument_list|)
expr_stmt|;
block|}
return|return
name|G_PARAM_SPEC
argument_list|(
name|aspec
argument_list|)
return|;
block|}
end_function

end_unit

