begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprogress.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b5d579e0108
block|{
DECL|member|progress_callback
name|gchar
modifier|*
name|progress_callback
decl_stmt|;
DECL|member|vtable
name|GimpProgressVtable
name|vtable
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
DECL|member|data_destroy
name|GDestroyNotify
name|data_destroy
decl_stmt|;
DECL|typedef|GimpProgressData
block|}
name|GimpProgressData
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_progress_data_free
parameter_list|(
name|GimpProgressData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|gimp_temp_progress_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|gimp_progress_current
specifier|static
name|gdouble
name|gimp_progress_current
init|=
literal|0.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimp_progress_step
specifier|static
specifier|const
name|gdouble
name|gimp_progress_step
init|=
operator|(
literal|1.0
operator|/
literal|256.0
operator|)
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_progress_install_vtable:  * @vtable:            a pointer to a @GimpProgressVtable.  * @user_data:         a pointer that is passed as user_data to all vtable  *                     functions.  * @user_data_destroy: (nullable): destroy function for @user_data, or %NULL.  *  * Returns: the name of the temporary procedure that's been installed  *  * Since: 2.4  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_progress_install_vtable (const GimpProgressVtable * vtable,gpointer user_data,GDestroyNotify user_data_destroy)
name|gimp_progress_install_vtable
parameter_list|(
specifier|const
name|GimpProgressVtable
modifier|*
name|vtable
parameter_list|,
name|gpointer
name|user_data
parameter_list|,
name|GDestroyNotify
name|user_data_destroy
parameter_list|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|gchar
modifier|*
name|progress_callback
decl_stmt|;
name|GimpProgressData
modifier|*
name|progress_data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vtable
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vtable
operator|->
name|start
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vtable
operator|->
name|end
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vtable
operator|->
name|set_text
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|vtable
operator|->
name|set_value
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|plug_in
operator|=
name|gimp_get_plug_in
argument_list|()
expr_stmt|;
name|progress_callback
operator|=
name|gimp_pdb_temp_procedure_name
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|)
expr_stmt|;
name|progress_data
operator|=
name|g_slice_new0
argument_list|(
name|GimpProgressData
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
name|vtable
operator|.
name|start
operator|=
name|vtable
operator|->
name|start
expr_stmt|;
name|progress_data
operator|->
name|vtable
operator|.
name|end
operator|=
name|vtable
operator|->
name|end
expr_stmt|;
name|progress_data
operator|->
name|vtable
operator|.
name|set_text
operator|=
name|vtable
operator|->
name|set_text
expr_stmt|;
name|progress_data
operator|->
name|vtable
operator|.
name|set_value
operator|=
name|vtable
operator|->
name|set_value
expr_stmt|;
name|progress_data
operator|->
name|vtable
operator|.
name|pulse
operator|=
name|vtable
operator|->
name|pulse
expr_stmt|;
name|progress_data
operator|->
name|vtable
operator|.
name|get_window
operator|=
name|vtable
operator|->
name|get_window
expr_stmt|;
name|progress_data
operator|->
name|data
operator|=
name|user_data
expr_stmt|;
name|progress_data
operator|->
name|data_destroy
operator|=
name|user_data_destroy
expr_stmt|;
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|progress_callback
argument_list|,
name|GIMP_TEMPORARY
argument_list|,
name|gimp_temp_progress_run
argument_list|,
name|progress_data
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_progress_data_free
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_ENUM
argument_list|(
name|procedure
argument_list|,
literal|"command"
argument_list|,
literal|"Command"
argument_list|,
literal|"The progress command"
argument_list|,
name|GIMP_TYPE_PROGRESS_COMMAND
argument_list|,
name|GIMP_PROGRESS_COMMAND_START
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_STRING
argument_list|(
name|procedure
argument_list|,
literal|"text"
argument_list|,
literal|"Text"
argument_list|,
literal|"The progress text"
argument_list|,
name|NULL
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"value"
argument_list|,
literal|"Vakue"
argument_list|,
literal|"The progress value"
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_VAL_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"value"
argument_list|,
literal|"Vakue"
argument_list|,
literal|"The progress value"
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|gimp_plug_in_add_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
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
comment|/* Allow callbacks to be watched */
name|gimp_plug_in_extension_enable
argument_list|(
name|plug_in
argument_list|)
expr_stmt|;
return|return
name|progress_callback
return|;
block|}
name|gimp_plug_in_remove_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_uninstall:  * @progress_callback: the name of the temporary procedure to uninstall  *  * Uninstalls a temporary progress procedure that was installed using  * gimp_progress_install().  *  * Since: 2.2  **/
end_comment

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
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_get_plug_in
argument_list|()
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|progress_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_remove_temp_procedure
argument_list|(
name|plug_in
argument_list|,
name|progress_callback
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_init:  * @message: Message to use in the progress dialog.  *  * Initializes the progress bar for the current plug-in.  *  * Initializes the progress bar for the current plug-in. It is only  * valid to call this procedure from a plug-in.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_progress_init (const gchar * message)
name|gimp_progress_init
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|gimp_default_display
argument_list|()
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|gimp_progress_current
operator|=
literal|0.0
expr_stmt|;
name|success
operator|=
name|_gimp_progress_init
argument_list|(
name|message
argument_list|,
name|display
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_init_printf:  * @format: a standard printf() format string  * @...: arguments for @format  *  * Initializes the progress bar for the current plug-in.  *  * Initializes the progress bar for the current plug-in. It is only  * valid to call this procedure from a plug-in.  *  * Returns: %TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_progress_init_printf (const gchar * format,...)
name|gimp_progress_init_printf
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|gchar
modifier|*
name|text
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_progress_init
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_set_text_printf:  * @format: a standard printf() format string  * @...: arguments for @format  *  * Changes the text in the progress bar for the current plug-in.  *  * This function changes the text in the progress bar for the current  * plug-in. Unlike gimp_progress_init() it does not change the  * displayed value.  *  * Returns: %TRUE on success.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_progress_set_text_printf (const gchar * format,...)
name|gimp_progress_set_text_printf
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|gchar
modifier|*
name|text
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|format
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|retval
operator|=
name|gimp_progress_set_text
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_progress_update:  * @percentage: Percentage of progress completed (in the range from 0.0 to 1.0).  *  * Updates the progress bar for the current plug-in.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_progress_update (gdouble percentage)
name|gimp_progress_update
parameter_list|(
name|gdouble
name|percentage
parameter_list|)
block|{
name|gboolean
name|changed
decl_stmt|;
if|if
condition|(
name|percentage
operator|<=
literal|0.0
condition|)
block|{
name|changed
operator|=
operator|(
name|gimp_progress_current
operator|!=
literal|0.0
operator|)
expr_stmt|;
name|percentage
operator|=
literal|0.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|percentage
operator|>=
literal|1.0
condition|)
block|{
name|changed
operator|=
operator|(
name|gimp_progress_current
operator|!=
literal|1.0
operator|)
expr_stmt|;
name|percentage
operator|=
literal|1.0
expr_stmt|;
block|}
else|else
block|{
name|changed
operator|=
operator|(
name|fabs
argument_list|(
name|gimp_progress_current
operator|-
name|percentage
argument_list|)
operator|>
name|gimp_progress_step
operator|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
if|if
condition|(
operator|!
name|changed
condition|)
block|{
specifier|static
name|gboolean
name|warned
init|=
name|FALSE
decl_stmt|;
specifier|static
name|gint
name|count
init|=
literal|0
decl_stmt|;
name|count
operator|++
expr_stmt|;
if|if
condition|(
name|count
operator|>
literal|3
operator|&&
operator|!
name|warned
condition|)
block|{
name|g_printerr
argument_list|(
literal|"%s is updating the progress too often\n"
argument_list|,
name|g_get_prgname
argument_list|()
argument_list|)
expr_stmt|;
name|warned
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
endif|#
directive|endif
block|}
comment|/*  Suppress the update if the change was only marginal.  */
if|if
condition|(
operator|!
name|changed
condition|)
return|return
name|TRUE
return|;
name|gimp_progress_current
operator|=
name|percentage
expr_stmt|;
return|return
name|_gimp_progress_update
argument_list|(
name|gimp_progress_current
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_progress_data_free (GimpProgressData * data)
name|gimp_progress_data_free
parameter_list|(
name|GimpProgressData
modifier|*
name|data
parameter_list|)
block|{
name|_gimp_progress_uninstall
argument_list|(
name|data
operator|->
name|progress_callback
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|data
operator|->
name|progress_callback
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|data_destroy
condition|)
name|data
operator|->
name|data_destroy
argument_list|(
name|data
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpProgressData
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gimp_temp_progress_run (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|gimp_temp_progress_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpProgressData
modifier|*
name|progress_data
init|=
name|run_data
decl_stmt|;
name|GimpProgressCommand
name|command
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|text
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|command
operator|=
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|text
operator|=
name|GIMP_VALUES_GET_STRING
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|value
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|command
condition|)
block|{
case|case
name|GIMP_PROGRESS_COMMAND_START
case|:
name|progress_data
operator|->
name|vtable
operator|.
name|start
argument_list|(
name|text
argument_list|,
name|value
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
name|GIMP_PROGRESS_COMMAND_END
case|:
name|progress_data
operator|->
name|vtable
operator|.
name|end
argument_list|(
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PROGRESS_COMMAND_SET_TEXT
case|:
name|progress_data
operator|->
name|vtable
operator|.
name|set_text
argument_list|(
name|text
argument_list|,
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PROGRESS_COMMAND_SET_VALUE
case|:
name|progress_data
operator|->
name|vtable
operator|.
name|set_value
argument_list|(
name|value
argument_list|,
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PROGRESS_COMMAND_PULSE
case|:
if|if
condition|(
name|progress_data
operator|->
name|vtable
operator|.
name|pulse
condition|)
name|progress_data
operator|->
name|vtable
operator|.
name|pulse
argument_list|(
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
else|else
name|progress_data
operator|->
name|vtable
operator|.
name|set_value
argument_list|(
operator|-
literal|1
argument_list|,
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PROGRESS_COMMAND_GET_WINDOW
case|:
block|{
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|guint32
name|window_id
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|progress_data
operator|->
name|vtable
operator|.
name|get_window
condition|)
name|window_id
operator|=
name|progress_data
operator|->
name|vtable
operator|.
name|get_window
argument_list|(
name|progress_data
operator|->
name|data
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_VALUES_SET_DOUBLE
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|,
name|window_id
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
break|break;
default|default:
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_CALLING_ERROR
argument_list|,
name|NULL
argument_list|)
return|;
block|}
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

