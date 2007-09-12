begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpcontainer-filter.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_GLIBC_REGEX
end_ifdef

begin_include
include|#
directive|include
file|<regex.h>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|"regexrepl/regex.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer-filter.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b2f620b0108
block|{
DECL|member|filter
name|GimpObjectFilterFunc
name|filter
decl_stmt|;
DECL|member|container
name|GimpContainer
modifier|*
name|container
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|typedef|GimpContainerFilterContext
block|}
name|GimpContainerFilterContext
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|gimp_container_filter_foreach_func (GimpObject * object,GimpContainerFilterContext * context)
name|gimp_container_filter_foreach_func
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|GimpContainerFilterContext
modifier|*
name|context
parameter_list|)
block|{
if|if
condition|(
name|context
operator|->
name|filter
argument_list|(
name|object
argument_list|,
name|context
operator|->
name|user_data
argument_list|)
condition|)
name|gimp_container_add
argument_list|(
name|context
operator|->
name|container
argument_list|,
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_container_filter:  * @container: a #GimpContainer to filter  * @filter: a #GimpObjectFilterFunc  * @user_data: a pointer passed to @filter  *  * Calls the supplied @filter function on each object in @container.  * A return value of %TRUE is interpreted as a match.  *  * Returns: a weak #GimpContainer filled with matching objects.  **/
end_comment

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_container_filter (const GimpContainer * container,GimpObjectFilterFunc filter,gpointer user_data)
name|gimp_container_filter
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObjectFilterFunc
name|filter
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|result
decl_stmt|;
name|GimpContainerFilterContext
name|context
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|filter
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|result
operator|=
name|g_object_new
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|container
argument_list|)
argument_list|,
literal|"children-type"
argument_list|,
name|gimp_container_children_type
argument_list|(
name|container
argument_list|)
argument_list|,
literal|"policy"
argument_list|,
name|GIMP_CONTAINER_POLICY_WEAK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|context
operator|.
name|filter
operator|=
name|filter
expr_stmt|;
name|context
operator|.
name|container
operator|=
name|result
expr_stmt|;
name|context
operator|.
name|user_data
operator|=
name|user_data
expr_stmt|;
name|gimp_container_foreach
argument_list|(
name|container
argument_list|,
operator|(
name|GFunc
operator|)
name|gimp_container_filter_foreach_func
argument_list|,
operator|&
name|context
argument_list|)
expr_stmt|;
comment|/*  This is somewhat ugly, but it keeps lists in the same order.  */
if|if
condition|(
name|GIMP_IS_LIST
argument_list|(
name|result
argument_list|)
condition|)
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|result
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_object_filter_by_name (const GimpObject * object,const regex_t * regex)
name|gimp_object_filter_by_name
parameter_list|(
specifier|const
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|regex_t
modifier|*
name|regex
parameter_list|)
block|{
return|return
operator|(
name|regexec
argument_list|(
name|regex
argument_list|,
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
operator|!=
name|REG_NOMATCH
operator|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_container_filter_by_name:  * @container: a #GimpContainer to filter  * @regexp: a regular expression (as a %NULL-terminated string)  * @error: error location to report errors or %NULL  *  * This function performs a case-insensitive regular expression search  * on the names of the GimpObjects in @container.  *  * Returns: a weak #GimpContainer filled with matching objects.  **/
end_comment

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_container_filter_by_name (const GimpContainer * container,const gchar * regexp,GError ** error)
name|gimp_container_filter_by_name
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|regexp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|result
decl_stmt|;
name|gint
name|ret
decl_stmt|;
name|regex_t
name|regex
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|regexp
operator|!=
name|NULL
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
name|ret
operator|=
name|regcomp
argument_list|(
operator|&
name|regex
argument_list|,
name|regexp
argument_list|,
name|REG_EXTENDED
operator||
name|REG_ICASE
operator||
name|REG_NOSUB
argument_list|)
expr_stmt|;
if|if
condition|(
name|ret
condition|)
block|{
name|gsize
name|error_len
decl_stmt|;
name|gchar
modifier|*
name|error_buf
decl_stmt|;
name|error_len
operator|=
name|regerror
argument_list|(
name|ret
argument_list|,
operator|&
name|regex
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|error_buf
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|error_len
argument_list|)
expr_stmt|;
name|regerror
argument_list|(
name|ret
argument_list|,
operator|&
name|regex
argument_list|,
name|error_buf
argument_list|,
name|error_len
argument_list|)
expr_stmt|;
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|error_buf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|error_buf
argument_list|)
expr_stmt|;
name|regfree
argument_list|(
operator|&
name|regex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|result
operator|=
name|gimp_container_filter
argument_list|(
name|container
argument_list|,
operator|(
name|GimpObjectFilterFunc
operator|)
name|gimp_object_filter_by_name
argument_list|,
operator|&
name|regex
argument_list|)
expr_stmt|;
name|regfree
argument_list|(
operator|&
name|regex
argument_list|)
expr_stmt|;
return|return
name|result
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_container_get_filtered_name_array (const GimpContainer * container,const gchar * regexp,gint * length)
name|gimp_container_get_filtered_name_array
parameter_list|(
specifier|const
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|regexp
parameter_list|,
name|gint
modifier|*
name|length
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|weak
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|length
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|regexp
operator|==
name|NULL
operator|||
name|strlen
argument_list|(
name|regexp
argument_list|)
operator|==
literal|0
condition|)
return|return
operator|(
name|gimp_container_get_name_array
argument_list|(
name|container
argument_list|,
name|length
argument_list|)
operator|)
return|;
name|weak
operator|=
name|gimp_container_filter_by_name
argument_list|(
name|container
argument_list|,
name|regexp
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|weak
condition|)
block|{
name|gchar
modifier|*
modifier|*
name|retval
init|=
name|gimp_container_get_name_array
argument_list|(
name|weak
argument_list|,
name|length
argument_list|)
decl_stmt|;
name|g_object_unref
argument_list|(
name|weak
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
else|else
block|{
name|g_warning
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
operator|*
name|length
operator|=
literal|0
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
end_function

end_unit

