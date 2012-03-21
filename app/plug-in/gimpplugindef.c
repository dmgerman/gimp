begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugindef.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugindef.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginprocedure.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_plug_in_def_finalize
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
name|gimp_plug_in_def_get_memsize
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
DECL|function|G_DEFINE_TYPE (GimpPlugInDef,gimp_plug_in_def,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPlugInDef
argument_list|,
argument|gimp_plug_in_def
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_plug_in_def_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_plug_in_def_class_init
parameter_list|(
name|GimpPlugInDefClass
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
name|object_class
operator|->
name|finalize
operator|=
name|gimp_plug_in_def_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_plug_in_def_get_memsize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_def_init (GimpPlugInDef * def)
name|gimp_plug_in_def_init
parameter_list|(
name|GimpPlugInDef
modifier|*
name|def
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_plug_in_def_finalize (GObject * object)
name|gimp_plug_in_def_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPlugInDef
modifier|*
name|plug_in_def
init|=
name|GIMP_PLUG_IN_DEF
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|prog
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|locale_domain_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|locale_domain_path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|help_domain_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|help_domain_uri
argument_list|)
expr_stmt|;
name|g_slist_free_full
argument_list|(
name|plug_in_def
operator|->
name|procedures
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
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
DECL|function|gimp_plug_in_def_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_plug_in_def_get_memsize
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
name|GimpPlugInDef
modifier|*
name|plug_in_def
init|=
name|GIMP_PLUG_IN_DEF
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
name|gimp_string_get_memsize
argument_list|(
name|plug_in_def
operator|->
name|prog
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|plug_in_def
operator|->
name|locale_domain_name
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|plug_in_def
operator|->
name|locale_domain_path
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|plug_in_def
operator|->
name|help_domain_name
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|plug_in_def
operator|->
name|help_domain_uri
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_g_slist_get_memsize
argument_list|(
name|plug_in_def
operator|->
name|procedures
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
comment|/*  public functions  */
end_comment

begin_function
name|GimpPlugInDef
modifier|*
DECL|function|gimp_plug_in_def_new (const gchar * prog)
name|gimp_plug_in_def_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|prog
parameter_list|)
block|{
name|GimpPlugInDef
modifier|*
name|plug_in_def
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|prog
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|plug_in_def
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PLUG_IN_DEF
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|prog
operator|=
name|g_strdup
argument_list|(
name|prog
argument_list|)
expr_stmt|;
return|return
name|plug_in_def
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_def_add_procedure (GimpPlugInDef * plug_in_def,GimpPlugInProcedure * proc)
name|gimp_plug_in_def_add_procedure
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|overridden
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
name|overridden
operator|=
name|gimp_plug_in_procedure_find
argument_list|(
name|plug_in_def
operator|->
name|procedures
argument_list|,
name|gimp_object_get_name
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|overridden
condition|)
name|gimp_plug_in_def_remove_procedure
argument_list|(
name|plug_in_def
argument_list|,
name|overridden
argument_list|)
expr_stmt|;
name|proc
operator|->
name|mtime
operator|=
name|plug_in_def
operator|->
name|mtime
expr_stmt|;
name|gimp_plug_in_procedure_set_locale_domain
argument_list|(
name|proc
argument_list|,
name|plug_in_def
operator|->
name|locale_domain_name
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_help_domain
argument_list|(
name|proc
argument_list|,
name|plug_in_def
operator|->
name|help_domain_name
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|procedures
operator|=
name|g_slist_append
argument_list|(
name|plug_in_def
operator|->
name|procedures
argument_list|,
name|g_object_ref
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_def_remove_procedure (GimpPlugInDef * plug_in_def,GimpPlugInProcedure * proc)
name|gimp_plug_in_def_remove_procedure
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_PROCEDURE
argument_list|(
name|proc
argument_list|)
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|procedures
operator|=
name|g_slist_remove
argument_list|(
name|plug_in_def
operator|->
name|procedures
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_def_set_locale_domain (GimpPlugInDef * plug_in_def,const gchar * domain_name,const gchar * domain_path)
name|gimp_plug_in_def_set_locale_domain
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_path
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|locale_domain_name
condition|)
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|locale_domain_name
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|locale_domain_name
operator|=
name|g_strdup
argument_list|(
name|domain_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|locale_domain_path
condition|)
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|locale_domain_path
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|locale_domain_path
operator|=
name|g_strdup
argument_list|(
name|domain_path
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|plug_in_def
operator|->
name|procedures
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|procedure
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_plug_in_procedure_set_locale_domain
argument_list|(
name|procedure
argument_list|,
name|plug_in_def
operator|->
name|locale_domain_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_def_set_help_domain (GimpPlugInDef * plug_in_def,const gchar * domain_name,const gchar * domain_uri)
name|gimp_plug_in_def_set_help_domain
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|help_domain_name
condition|)
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|help_domain_name
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|help_domain_name
operator|=
name|g_strdup
argument_list|(
name|domain_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|plug_in_def
operator|->
name|help_domain_uri
condition|)
name|g_free
argument_list|(
name|plug_in_def
operator|->
name|help_domain_uri
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|help_domain_uri
operator|=
name|g_strdup
argument_list|(
name|domain_uri
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|plug_in_def
operator|->
name|procedures
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|procedure
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_plug_in_procedure_set_help_domain
argument_list|(
name|procedure
argument_list|,
name|plug_in_def
operator|->
name|help_domain_name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_def_set_mtime (GimpPlugInDef * plug_in_def,time_t mtime)
name|gimp_plug_in_def_set_mtime
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|time_t
name|mtime
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|mtime
operator|=
name|mtime
expr_stmt|;
for|for
control|(
name|list
operator|=
name|plug_in_def
operator|->
name|procedures
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
init|=
name|list
operator|->
name|data
decl_stmt|;
name|proc
operator|->
name|mtime
operator|=
name|plug_in_def
operator|->
name|mtime
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_def_set_needs_query (GimpPlugInDef * plug_in_def,gboolean needs_query)
name|gimp_plug_in_def_set_needs_query
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|gboolean
name|needs_query
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|needs_query
operator|=
name|needs_query
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_def_set_has_init (GimpPlugInDef * plug_in_def,gboolean has_init)
name|gimp_plug_in_def_set_has_init
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|gboolean
name|has_init
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_DEF
argument_list|(
name|plug_in_def
argument_list|)
argument_list|)
expr_stmt|;
name|plug_in_def
operator|->
name|has_init
operator|=
name|has_init
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

end_unit

