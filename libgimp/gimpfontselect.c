begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpfontselect.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
DECL|typedef|GimpFontData
typedef|typedef
name|struct
name|_GimpFontData
name|GimpFontData
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFontData
struct|struct
name|_GimpFontData
block|{
DECL|member|font_callback
name|gchar
modifier|*
name|font_callback
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|font_name
name|gchar
modifier|*
name|font_name
decl_stmt|;
DECL|member|callback
name|GimpRunFontCallback
name|callback
decl_stmt|;
DECL|member|closing
name|gboolean
name|closing
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
name|gimp_temp_font_run
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

begin_function_decl
specifier|static
name|gboolean
name|gimp_temp_font_run_idle
parameter_list|(
name|GimpFontData
modifier|*
name|font_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|gimp_font_select_ht
specifier|static
name|GHashTable
modifier|*
name|gimp_font_select_ht
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
DECL|function|gimp_font_select_new (const gchar * title,const gchar * font_name,GimpRunFontCallback callback,gpointer data)
name|gimp_font_select_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|,
name|GimpRunFontCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"str"
block|,
literal|"String"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"dialog status"
block|,
literal|"If the dialog was closing "
literal|"[0 = No, 1 = Yes]"
block|}
block|,   }
decl_stmt|;
name|gchar
modifier|*
name|font_callback
init|=
name|gimp_procedural_db_temp_name
argument_list|()
decl_stmt|;
name|gimp_install_temp_proc
argument_list|(
name|font_callback
argument_list|,
literal|"Temporary font popup callback procedure"
argument_list|,
literal|""
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"1997"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*, GRAY*"
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
name|gimp_temp_font_run
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_fonts_popup
argument_list|(
name|font_callback
argument_list|,
name|title
argument_list|,
name|font_name
argument_list|)
condition|)
block|{
name|GimpFontData
modifier|*
name|font_data
decl_stmt|;
name|gimp_extension_enable
argument_list|()
expr_stmt|;
comment|/* Allow callbacks to be watched */
comment|/* Now add to hash table so we can find it again */
if|if
condition|(
operator|!
name|gimp_font_select_ht
condition|)
name|gimp_font_select_ht
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
name|font_data
operator|=
name|g_new0
argument_list|(
name|GimpFontData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|font_data
operator|->
name|font_callback
operator|=
name|font_callback
expr_stmt|;
name|font_data
operator|->
name|callback
operator|=
name|callback
expr_stmt|;
name|font_data
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|gimp_font_select_ht
argument_list|,
name|font_callback
argument_list|,
name|font_data
argument_list|)
expr_stmt|;
return|return
name|font_callback
return|;
block|}
name|gimp_uninstall_temp_proc
argument_list|(
name|font_callback
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|font_callback
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_font_select_destroy (const gchar * font_callback)
name|gimp_font_select_destroy
parameter_list|(
specifier|const
name|gchar
modifier|*
name|font_callback
parameter_list|)
block|{
name|GimpFontData
modifier|*
name|font_data
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|font_callback
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimp_font_select_ht
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|font_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp_font_select_ht
argument_list|,
name|font_callback
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font_data
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't find internal font data"
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|font_data
operator|->
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|font_data
operator|->
name|idle_id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|font_data
operator|->
name|font_name
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|font_data
operator|->
name|font_callback
condition|)
name|gimp_fonts_close_popup
argument_list|(
name|font_data
operator|->
name|font_callback
argument_list|)
expr_stmt|;
name|gimp_uninstall_temp_proc
argument_list|(
name|font_callback
argument_list|)
expr_stmt|;
name|g_hash_table_remove
argument_list|(
name|gimp_font_select_ht
argument_list|,
name|font_callback
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
DECL|function|gimp_temp_font_run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|gimp_temp_font_run
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
name|GimpFontData
modifier|*
name|font_data
decl_stmt|;
name|font_data
operator|=
name|g_hash_table_lookup
argument_list|(
name|gimp_font_select_ht
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|font_data
condition|)
block|{
name|g_warning
argument_list|(
literal|"Can't find internal font data"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|font_data
operator|->
name|font_name
argument_list|)
expr_stmt|;
name|font_data
operator|->
name|font_name
operator|=
name|g_strdup
argument_list|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|font_data
operator|->
name|closing
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
operator|!
name|font_data
operator|->
name|idle_id
condition|)
name|font_data
operator|->
name|idle_id
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_temp_font_run_idle
argument_list|,
name|font_data
argument_list|)
expr_stmt|;
block|}
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

begin_function
specifier|static
name|gboolean
DECL|function|gimp_temp_font_run_idle (GimpFontData * font_data)
name|gimp_temp_font_run_idle
parameter_list|(
name|GimpFontData
modifier|*
name|font_data
parameter_list|)
block|{
name|font_data
operator|->
name|idle_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|font_data
operator|->
name|callback
condition|)
name|font_data
operator|->
name|callback
argument_list|(
name|font_data
operator|->
name|font_name
argument_list|,
name|font_data
operator|->
name|closing
argument_list|,
name|font_data
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|font_data
operator|->
name|closing
condition|)
block|{
name|gchar
modifier|*
name|font_callback
init|=
name|font_data
operator|->
name|font_callback
decl_stmt|;
name|font_data
operator|->
name|font_callback
operator|=
name|NULL
expr_stmt|;
name|gimp_font_select_destroy
argument_list|(
name|font_callback
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

