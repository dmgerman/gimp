begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpcontext_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
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

begin_comment
comment|/**  * gimp_context_push:  *  * Pushes a context to the top of the plug-in's context stack.  *  * This procedure creates a new context by copying the current context.  * This copy becomes the new current context for the calling plug-in  * until it is popped again using gimp_context_pop().  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_push (void)
name|gimp_context_push
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-push"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_pop:  *  * Pops the topmost context from the plug-in's context stack.  *  * This procedure removes the topmost context from the plug-in's  * context stack. The context that was active before the corresponding  * call to gimp_context_push() becomes the new current context of the  * plug-in.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_pop (void)
name|gimp_context_pop
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-pop"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_list_paint_methods:  * @num_paint_methods: The number of the available paint methods.  * @paint_methods: The names of the available paint methods.  *  * Lists the available paint methods.  *  * This procedure lists the names of the available paint methods. Any  * of the results can be used for gimp_context_set_paint_method().  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_list_paint_methods (gint * num_paint_methods,gchar *** paint_methods)
name|gimp_context_list_paint_methods
parameter_list|(
name|gint
modifier|*
name|num_paint_methods
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|paint_methods
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-list-paint-methods"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
operator|*
name|num_paint_methods
operator|=
literal|0
expr_stmt|;
operator|*
name|paint_methods
operator|=
name|NULL
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
operator|*
name|num_paint_methods
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|paint_methods
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|num_paint_methods
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|num_paint_methods
condition|;
name|i
operator|++
control|)
operator|(
operator|*
name|paint_methods
operator|)
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_stringarray
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_paint_method:  *  * Retrieve the currently active paint method.  *  * This procedure returns the name of the currently active paint  * method.  *  * Returns: The name of the active paint method.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_context_get_paint_method (void)
name|gimp_context_get_paint_method
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-paint-method"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_paint_method:  * @name: The name of the paint method.  *  * Set the specified paint method as the active paint method.  *  * This procedure allows the active paint method to be set by  * specifying its name. The name is simply a string which corresponds  * to one of the names of the available paint methods. If there is no  * matching method found, this procedure will return an error.  * Otherwise, the specified method becomes active and will be used in  * all subsequent paint operations.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_paint_method (const gchar * name)
name|gimp_context_set_paint_method
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-paint-method"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_foreground:  * @foreground: The foreground color.  *  * Get the current GIMP foreground color.  *  * This procedure returns the current GIMP foreground color. The  * foreground color is used in a variety of tools such as paint tools,  * blending, and bucket fill.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_get_foreground (GimpRGB * foreground)
name|gimp_context_get_foreground
parameter_list|(
name|GimpRGB
modifier|*
name|foreground
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-foreground"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|success
condition|)
operator|*
name|foreground
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_color
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_foreground:  * @foreground: The foreground color.  *  * Set the current GIMP foreground color.  *  * This procedure sets the current GIMP foreground color. After this is  * set, operations which use foreground such as paint tools, blending,  * and bucket fill will use the new value.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_foreground (const GimpRGB * foreground)
name|gimp_context_set_foreground
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|foreground
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-foreground"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_COLOR
argument_list|,
name|foreground
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_background:  * @background: The background color.  *  * Get the current GIMP background color.  *  * This procedure returns the current GIMP background color. The  * background color is used in a variety of tools such as blending,  * erasing (with non-alpha images), and image filling.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_get_background (GimpRGB * background)
name|gimp_context_get_background
parameter_list|(
name|GimpRGB
modifier|*
name|background
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-background"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
if|if
condition|(
name|success
condition|)
operator|*
name|background
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_color
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_background:  * @background: The background color.  *  * Set the current GIMP background color.  *  * This procedure sets the current GIMP background color. After this is  * set, operations which use background such as blending, filling  * images, clearing, and erasing (in non-alpha images) will use the new  * value.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_background (const GimpRGB * background)
name|gimp_context_set_background
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|background
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-background"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_COLOR
argument_list|,
name|background
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_default_colors:  *  * Set the current GIMP foreground and background colors to black and  * white.  *  * This procedure sets the current GIMP foreground and background  * colors to their initial default values, black and white.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_default_colors (void)
name|gimp_context_set_default_colors
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-default-colors"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_swap_colors:  *  * Swap the current GIMP foreground and background colors.  *  * This procedure swaps the current GIMP foreground and background  * colors, so that the new foreground color becomes the old background  * color and vice versa.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_swap_colors (void)
name|gimp_context_swap_colors
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-swap-colors"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_opacity:  *  * Get the opacity.  *  * This procedure returns the opacity setting. The return value is a  * floating point number between 0 and 100.  *  * Returns: The opacity.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gdouble
DECL|function|gimp_context_get_opacity (void)
name|gimp_context_get_opacity
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gdouble
name|opacity
init|=
literal|0.0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-opacity"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|opacity
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|opacity
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_opacity:  * @opacity: The opacity.  *  * Set the opacity.  *  * This procedure modifies the opacity setting. The value should be a  * floating point number between 0 and 100.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_opacity (gdouble opacity)
name|gimp_context_set_opacity
parameter_list|(
name|gdouble
name|opacity
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-opacity"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|opacity
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_paint_mode:  *  * Get the paint mode.  *  * This procedure returns the paint-mode setting. The return value is  * an integer which corresponds to the values listed in the argument  * description.  *  * Returns: The paint mode.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|GimpLayerModeEffects
DECL|function|gimp_context_get_paint_mode (void)
name|gimp_context_get_paint_mode
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|GimpLayerModeEffects
name|paint_mode
init|=
literal|0
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-paint-mode"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|paint_mode
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|paint_mode
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_paint_mode:  * @paint_mode: The paint mode.  *  * Set the paint mode.  *  * This procedure modifies the paint_mode setting.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_paint_mode (GimpLayerModeEffects paint_mode)
name|gimp_context_set_paint_mode
parameter_list|(
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-paint-mode"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paint_mode
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_brush:  *  * Retrieve the currently active brush.  *  * This procedure returns the name of the currently active brush. All  * paint operations and stroke operations use this brush to control the  * application of paint to the image.  *  * Returns: The name of the active brush.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_context_get_brush (void)
name|gimp_context_get_brush
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-brush"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_brush:  * @name: The name of the brush.  *  * Set the specified brush as the active brush.  *  * This procedure allows the active brush to be set by specifying its  * name. The name is simply a string which corresponds to one of the  * names of the installed brushes. If there is no matching brush found,  * this procedure will return an error. Otherwise, the specified brush  * becomes active and will be used in all subsequent paint operations.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_brush (const gchar * name)
name|gimp_context_set_brush
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-brush"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_pattern:  *  * Retrieve the currently active pattern.  *  * This procedure returns name of the the currently active pattern. All  * clone and bucket-fill operations with patterns will use this pattern  * to control the application of paint to the image.  *  * Returns: The name of the active pattern.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_context_get_pattern (void)
name|gimp_context_get_pattern
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-pattern"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_pattern:  * @name: The name of the pattern.  *  * Set the specified pattern as the active pattern.  *  * This procedure allows the active pattern to be set by specifying its  * name. The name is simply a string which corresponds to one of the  * names of the installed patterns. If there is no matching pattern  * found, this procedure will return an error. Otherwise, the specified  * pattern becomes active and will be used in all subsequent paint  * operations.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_pattern (const gchar * name)
name|gimp_context_set_pattern
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-pattern"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_gradient:  *  * Retrieve the currently active gradient.  *  * This procedure returns the name of the currently active gradient.  *  * Returns: The name of the active gradient.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_context_get_gradient (void)
name|gimp_context_get_gradient
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-gradient"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_gradient:  * @name: The name of the gradient.  *  * Sets the specified gradient as the active gradient.  *  * This procedure lets you set the specified gradient as the active or  * \"current\" one. The name is simply a string which corresponds to  * one of the loaded gradients. If no matching gradient is found, this  * procedure will return an error. Otherwise, the specified gradient  * will become active and will be used for subsequent custom gradient  * operations.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_gradient (const gchar * name)
name|gimp_context_set_gradient
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-gradient"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_palette:  *  * Retrieve the currently active palette.  *  * This procedure returns the name of the the currently active palette.  *  * Returns: The name of the active palette.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_context_get_palette (void)
name|gimp_context_get_palette
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-palette"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_palette:  * @name: The name of the palette.  *  * Set the specified palette as the active palette.  *  * This procedure allows the active palette to be set by specifying its  * name. The name is simply a string which corresponds to one of the  * names of the installed palettes. If no matching palette is found,  * this procedure will return an error. Otherwise, the specified  * palette becomes active and will be used in all subsequent palette  * operations.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_palette (const gchar * name)
name|gimp_context_set_palette
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-palette"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_get_font:  *  * Retrieve the currently active font.  *  * This procedure returns the name of the currently active font.  *  * Returns: The name of the active font.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_context_get_font (void)
name|gimp_context_get_font
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|NULL
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-get-font"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|name
operator|=
name|g_strdup
argument_list|(
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_context_set_font:  * @name: The name of the font.  *  * Set the specified font as the active font.  *  * This procedure allows the active font to be set by specifying its  * name. The name is simply a string which corresponds to one of the  * names of the installed fonts. If no matching font is found, this  * procedure will return an error. Otherwise, the specified font  * becomes active and will be used in all subsequent font operations.  *  * Returns: TRUE on success.  *  * Since: GIMP 2.2  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_context_set_font (const gchar * name)
name|gimp_context_set_font
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp-context-set-font"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|success
operator|=
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

