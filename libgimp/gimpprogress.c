begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprogress.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_typedef
DECL|typedef|GimpProgressData
typedef|typedef
name|struct
name|_GimpProgressData
name|GimpProgressData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProgressData
struct|struct
name|_GimpProgressData
block|{
DECL|member|progress_callback
name|gchar
modifier|*
name|progress_callback
decl_stmt|;
if|#
directive|if
literal|0
block|guint                      idle_id;
endif|#
directive|endif
DECL|member|start_callback
name|GimpProgressStartCallback
name|start_callback
decl_stmt|;
DECL|member|end_callback
name|GimpProgressEndCallback
name|end_callback
decl_stmt|;
DECL|member|text_callback
name|GimpProgressTextCallback
name|text_callback
decl_stmt|;
DECL|member|value_callback
name|GimpProgressValueCallback
name|value_callback
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_temp_progress_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static gboolean  gimp_temp_progress_run_idle (GimpProgressData  *progress_data);
endif|#
directive|endif
end_endif

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|gimp_progress_ht
specifier|static
name|GHashTable
modifier|*
name|gimp_progress_ht
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_progress_install (GimpProgressStartCallback start_callback,GimpProgressEndCallback end_callback,GimpProgressTextCallback text_callback,GimpProgressValueCallback value_callback,gpointer user_data)
name|gimp_progress_install
parameter_list|(
name|GimpProgressStartCallback
name|start_callback
parameter_list|,
name|GimpProgressEndCallback
name|end_callback
parameter_list|,
name|GimpProgressTextCallback
name|text_callback
parameter_list|,
name|GimpProgressValueCallback
name|value_callback
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"command"
block|,
literal|""
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"text"
block|,
literal|""
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"value"
block|,
literal|""
block|}
block|}
decl_stmt|;
name|gchar
modifier|*
name|progress_callback
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|start_callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|end_callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|text_callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|value_callback
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|progress_callback
operator|=
name|gimp_procedural_db_temp_name
argument_list|()
expr_stmt|;
name|gimp_install_temp_proc
argument_list|(
name|progress_callback
argument_list|,
literal|"Temporary progress callback procedure"
argument_list|,
literal|""
argument_list|,
literal|"Michael Natterer<mitch@gimp.org>"
argument_list|,
literal|"Michael Natterer"
argument_list|,
literal|"2004"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|,
name|gimp_temp_progress_run
argument_list|)
expr_stmt|;
if|if
condition|(
name|_gimp_progress_install
argument_list|(
name|progress_callback
argument_list|)
condition|)
block|{
name|GimpProgressData
modifier|*
name|progress_data
decl_stmt|;
name|gimp_extension_enable
argument_list|()
expr_stmt|;
comment|/* Allow callbacks to be watched */
comment|/* Now add to hash table so we can find it again */
if|if
condition|(
operator|!
name|gimp_progress_ht
condition|)
name|gimp_progress_ht
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|progress_data
operator|=
name|g_new0
argument_list|(
name|GimpProgressData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|progress_data
operator|->
name|progress_callback
operator|=
name|progress_callback
expr_stmt|;
name|progress_data
operator|->
name|start_callback
operator|=
name|start_callback
expr_stmt|;
name|progress_data
operator|->
name|end_callback
operator|=
name|end_callback
expr_stmt|;
name|progress_data
operator|->
name|text_callback
operator|=
name|text_callback
expr_stmt|;
name|progress_data
operator|->
name|value_callback
operator|=
name|value_callback
expr_stmt|;
name|progress_data
operator|->
name|data
operator|=
name|user_data
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|gimp_progress_ht
argument_list|,
name|progress_callback
argument_list|,
name|progress_data
argument_list|)
expr_stmt|;
return|return
name|progress_callback
return|;
block|}
name|gimp_uninstall_temp_proc
argument_list|(
name|progress_callback
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|progress_callback
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_progress_uninstall (const gchar * progress_callback)
name|gimp_progress_uninstall
parameter_list|(
specifier|const
name|gchar
modifier|*
name|progress_callback
parameter_list|)
block|{
name|GimpProgressData
modifier|*
name|progress_data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|progress_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_progress_ht
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|progress_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp_progress_ht
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|progress_data
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't find internal progress data"
argument_list|)
expr_stmt|;
return|return;
block|}
if|#
directive|if
literal|0
block|if (progress_data->idle_id)     g_source_remove (progress_data->idle_id);
endif|#
directive|endif
name|_gimp_progress_uninstall
argument_list|(
name|progress_callback
argument_list|)
expr_stmt|;
name|gimp_uninstall_temp_proc
argument_list|(
name|progress_callback
argument_list|)
expr_stmt|;
name|g_hash_table_remove
argument_list|(
name|gimp_progress_ht
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_temp_progress_run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|gimp_temp_progress_run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpProgressData
modifier|*
name|progress_data
decl_stmt|;
name|progress_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp_progress_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|progress_data
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't find internal progress data"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|#
directive|if
literal|0
block|if (! progress_data->idle_id)         progress_data->idle_id =           g_idle_add ((GSourceFunc) gimp_temp_progress_run_idle,                       progress_data);
endif|#
directive|endif
name|g_print
argument_list|(
literal|"%s: command = %d, text = %s, value = %f\n"
argument_list|,
name|G_STRFUNC
argument_list|,
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_float
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
condition|)
block|{
case|case
literal|0
case|:
name|progress_data
operator|->
name|start_callback
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_float
operator|!=
literal|0.0
argument_list|,
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|progress_data
operator|->
name|end_callback
argument_list|(
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|progress_data
operator|->
name|text_callback
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
literal|3
case|:
name|progress_data
operator|->
name|value_callback
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_float
argument_list|,
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"Unknown command passed to progress callback"
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|g_print
argument_list|(
literal|"%s: callback finished\n"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static gboolean gimp_temp_progress_run_idle (GimpProgressData *progress_data) {   progress_data->idle_id = 0;    if (progress_data->callback)     progress_data->callback (progress_data->progress_name,                              progress_data->closing,                              progress_data->data);    if (progress_data->closing)     {       gchar *progress_callback = progress_data->progress_callback;        progress_data->progress_callback = NULL;       gimp_progress_select_destroy (progress_callback);     }    return FALSE; }
endif|#
directive|endif
end_endif

end_unit

