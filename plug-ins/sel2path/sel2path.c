begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Plugin to convert a selection to a path.  *  * Copyright (C) 1999 Andy Thomas  alt@gimp.org  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *   */
end_comment

begin_comment
comment|/* Change log:-  * 0.1 First version.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_empty
empty|#
end_empty

begin_include
include|#
directive|include
file|"global.h"
end_include

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_include
include|#
directive|include
file|"pxl-outline.h"
end_include

begin_include
include|#
directive|include
file|"fit.h"
end_include

begin_include
include|#
directive|include
file|"spline.h"
end_include

begin_include
include|#
directive|include
file|"sel2path.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|MID_POINT
define|#
directive|define
name|MID_POINT
value|127
end_define

begin_comment
comment|/***** Magic numbers *****/
end_comment

begin_comment
comment|/* Variables set in dialog box */
end_comment

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|gint
name|sel2path_dialog
parameter_list|(
name|SELVALS
modifier|*
name|sels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|sel2path_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|sel2path_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|dialog_print_selVals
parameter_list|(
name|SELVALS
modifier|*
name|sels
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|do_sel2path
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sel_x1
DECL|variable|sel_y1
DECL|variable|sel_x2
DECL|variable|sel_y2
specifier|static
name|gint
name|sel_x1
decl_stmt|,
name|sel_y1
decl_stmt|,
name|sel_x2
decl_stmt|,
name|sel_y2
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|has_sel
DECL|variable|sel_width
DECL|variable|sel_height
specifier|static
name|gint
name|has_sel
decl_stmt|,
name|sel_width
decl_stmt|,
name|sel_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selVals
specifier|static
name|SELVALS
name|selVals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|selection_rgn
name|GimpPixelRgn
name|selection_rgn
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|retVal
name|gboolean
name|retVal
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|retVal
comment|/* Toggle if cancle button clicked */
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query_2
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (unused)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"align_threshold"
block|,
literal|"align_threshold"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"corner_always_threshold"
block|,
literal|"corner_always_threshold"
block|}
block|,
block|{
name|GIMP_PDB_INT8
block|,
literal|"corner_surround"
block|,
literal|"corner_surround"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"corner_threshold"
block|,
literal|"corner_threshold"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"error_threshold"
block|,
literal|"error_threshold"
block|}
block|,
block|{
name|GIMP_PDB_INT8
block|,
literal|"filter_alternative_surround"
block|,
literal|"filter_alternative_surround"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"filter_epsilon"
block|,
literal|"filter_epsilon"
block|}
block|,
block|{
name|GIMP_PDB_INT8
block|,
literal|"filter_iteration_count"
block|,
literal|"filter_iteration_count"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"filter_percent"
block|,
literal|"filter_percent"
block|}
block|,
block|{
name|GIMP_PDB_INT8
block|,
literal|"filter_secondary_surround"
block|,
literal|"filter_secondary_surround"
block|}
block|,
block|{
name|GIMP_PDB_INT8
block|,
literal|"filter_surround"
block|,
literal|"filter_surround"
block|}
block|,
block|{
name|GIMP_PDB_INT8
block|,
literal|"keep_knees"
block|,
literal|"{1-Yes, 0-No}"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"line_reversion_threshold"
block|,
literal|"line_reversion_threshold"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"line_threshold"
block|,
literal|"line_threshold"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"reparameterize_improvement"
block|,
literal|"reparameterize_improvement"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"reparameterize_threshold"
block|,
literal|"reparameterize_threshold"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"subdivide_search"
block|,
literal|"subdivide_search"
block|}
block|,
block|{
name|GIMP_PDB_INT8
block|,
literal|"subdivide_surround"
block|,
literal|"subdivide_surround"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"subdivide_threshold"
block|,
literal|"subdivide_threshold"
block|}
block|,
block|{
name|GIMP_PDB_INT8
block|,
literal|"tangent_surround"
block|,
literal|"tangent_surround"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GimpParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
specifier|static
name|int
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_sel2path_advanced"
argument_list|,
literal|"Converts a selection to a path (with advanced user menu)"
argument_list|,
literal|"Converts a selection to a path (with advanced user menu)"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"1999"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*, INDEXED*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
name|nreturn_vals
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|query (void)
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (unused)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GimpParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
specifier|static
name|int
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_sel2path"
argument_list|,
literal|"Converts a selection to a path"
argument_list|,
literal|"Converts a selection to a path"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"1999"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Select/To Path"
argument_list|)
argument_list|,
literal|"RGB*, INDEXED*, GRAY*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
name|nreturn_vals
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
name|query_2
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
name|drawable_ID
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gboolean
name|no_dialog
init|=
name|FALSE
decl_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_sel2path"
argument_list|)
condition|)
block|{
name|no_dialog
operator|=
name|TRUE
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
block|}
else|else
name|INIT_I18N_UI
argument_list|()
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
name|status
expr_stmt|;
name|drawable_ID
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|image_ID
operator|=
name|gimp_drawable_image_id
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_selection_is_empty
argument_list|(
name|image_ID
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"No selection to convert"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return;
block|}
name|fit_set_default_params
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|no_dialog
condition|)
block|{
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
if|if
condition|(
name|gimp_get_data_size
argument_list|(
literal|"plug_in_sel2path_advanced"
argument_list|)
operator|>
literal|0
condition|)
block|{
name|gimp_get_data
argument_list|(
literal|"plug_in_sel2path_advanced"
argument_list|,
operator|&
name|selVals
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|sel2path_dialog
argument_list|(
operator|&
name|selVals
argument_list|)
condition|)
block|{
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* Get the current settings */
name|fit_set_params
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|23
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|selVals
operator|.
name|align_threshold
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|corner_always_threshold
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|corner_surround
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
name|selVals
operator|.
name|corner_threshold
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|error_threshold
operator|=
name|param
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|filter_alternative_surround
operator|=
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
name|selVals
operator|.
name|filter_epsilon
operator|=
name|param
index|[
literal|9
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|filter_iteration_count
operator|=
name|param
index|[
literal|10
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
name|selVals
operator|.
name|filter_percent
operator|=
name|param
index|[
literal|11
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|filter_secondary_surround
operator|=
name|param
index|[
literal|12
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
name|selVals
operator|.
name|filter_surround
operator|=
name|param
index|[
literal|13
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
name|selVals
operator|.
name|keep_knees
operator|=
name|param
index|[
literal|14
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
name|selVals
operator|.
name|line_reversion_threshold
operator|=
name|param
index|[
literal|15
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|line_threshold
operator|=
name|param
index|[
literal|16
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|reparameterize_improvement
operator|=
name|param
index|[
literal|17
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|reparameterize_threshold
operator|=
name|param
index|[
literal|18
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|subdivide_search
operator|=
name|param
index|[
literal|19
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|subdivide_surround
operator|=
name|param
index|[
literal|20
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
name|selVals
operator|.
name|subdivide_threshold
operator|=
name|param
index|[
literal|21
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|selVals
operator|.
name|tangent_surround
operator|=
name|param
index|[
literal|22
index|]
operator|.
name|data
operator|.
name|d_int8
expr_stmt|;
name|fit_set_params
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
if|if
condition|(
name|gimp_get_data_size
argument_list|(
literal|"plug_in_sel2path_advanced"
argument_list|)
operator|>
literal|0
condition|)
block|{
name|gimp_get_data
argument_list|(
literal|"plug_in_sel2path_advanced"
argument_list|,
operator|&
name|selVals
argument_list|)
expr_stmt|;
comment|/* Set up the last values */
name|fit_set_params
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
name|do_sel2path
argument_list|(
name|drawable_ID
argument_list|,
name|image_ID
argument_list|)
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
name|status
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|dialog_print_selVals
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|&&
operator|!
name|no_dialog
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_sel2path_advanced"
argument_list|,
operator|&
name|selVals
argument_list|,
sizeof|sizeof
argument_list|(
name|SELVALS
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialog_print_selVals (SELVALS * sels)
name|dialog_print_selVals
parameter_list|(
name|SELVALS
modifier|*
name|sels
parameter_list|)
block|{
if|#
directive|if
literal|0
block|printf ("selVals.align_threshold %g\n",             selVals.align_threshold);   printf ("selVals.corner_always_threshol %g\n",      selVals.corner_always_threshold);   printf ("selVals.corner_surround %g\n",             selVals.corner_surround);   printf ("selVals.corner_threshold %g\n",            selVals.corner_threshold);   printf ("selVals.error_threshold %g\n",             selVals.error_threshold);   printf ("selVals.filter_alternative_surround %g\n", selVals.filter_alternative_surround);   printf ("selVals.filter_epsilon %g\n",              selVals.filter_epsilon);   printf ("selVals.filter_iteration_count %g\n",      selVals.filter_iteration_count);   printf ("selVals.filter_percent %g\n",              selVals.filter_percent);   printf ("selVals.filter_secondary_surround %g\n",   selVals.filter_secondary_surround);   printf ("selVals.filter_surround %g\n",             selVals.filter_surround);   printf ("selVals.keep_knees %d\n",                  selVals.keep_knees);   printf ("selVals.line_reversion_threshold %g\n",    selVals.line_reversion_threshold);   printf ("selVals.line_threshold %g\n",              selVals.line_threshold);   printf ("selVals.reparameterize_improvement %g\n",  selVals.reparameterize_improvement);   printf ("selVals.reparameterize_threshold %g\n",    selVals.reparameterize_threshold);   printf ("selVals.subdivide_search %g\n"             selVals.subdivide_search);   printf ("selVals.subdivide_surround %g\n",          selVals.subdivide_surround);   printf ("selVals.subdivide_threshold %g\n",         selVals.subdivide_threshold);   printf ("selVals.tangent_surround %g\n",            selVals.tangent_surround);
endif|#
directive|endif
comment|/* 0 */
block|}
end_function

begin_comment
comment|/* Build the dialog up. This was the hard part! */
end_comment

begin_function
specifier|static
name|gint
DECL|function|sel2path_dialog (SELVALS * sels)
name|sel2path_dialog
parameter_list|(
name|SELVALS
modifier|*
name|sels
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|retVal
operator|=
name|FALSE
expr_stmt|;
name|gimp_ui_init
argument_list|(
literal|"sel2path"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Sel2Path Advanced Settings"
argument_list|)
argument_list|,
literal|"sel2path"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/sel2path.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Reset"
argument_list|)
argument_list|,
name|sel2path_reset_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|sel2path_ok_callback
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|table
operator|=
name|dialog_create_selection_area
argument_list|(
name|sels
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
name|retVal
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|sel2path_ok_callback (GtkWidget * widget,gpointer data)
name|sel2path_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|retVal
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|sel2path_reset_callback (GtkWidget * widget,gpointer data)
name|sel2path_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|reset_adv_dialog
argument_list|()
expr_stmt|;
name|fit_set_params
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guchar
DECL|function|sel_pixel_value (gint row,gint col)
name|sel_pixel_value
parameter_list|(
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
block|{
name|guchar
name|ret
decl_stmt|;
if|if
condition|(
name|col
operator|>
name|sel_width
operator|||
name|row
operator|>
name|sel_height
condition|)
block|{
name|g_warning
argument_list|(
literal|"sel_pixel_value [%d,%d] out of bounds"
argument_list|,
name|col
argument_list|,
name|row
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
name|gimp_pixel_rgn_get_pixel
argument_list|(
operator|&
name|selection_rgn
argument_list|,
operator|&
name|ret
argument_list|,
name|col
operator|+
name|sel_x1
argument_list|,
name|row
operator|+
name|sel_y1
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|sel_pixel_is_white (gint row,gint col)
name|sel_pixel_is_white
parameter_list|(
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
block|{
if|if
condition|(
name|sel_pixel_value
argument_list|(
name|row
argument_list|,
name|col
argument_list|)
operator|<
name|MID_POINT
condition|)
return|return
name|TRUE
return|;
else|else
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gint
DECL|function|sel_get_width (void)
name|sel_get_width
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|sel_width
return|;
block|}
end_function

begin_function
name|gint
DECL|function|sel_get_height (void)
name|sel_get_height
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|sel_height
return|;
block|}
end_function

begin_function
name|gint
DECL|function|sel_valid_pixel (gint row,gint col)
name|sel_valid_pixel
parameter_list|(
name|gint
name|row
parameter_list|,
name|gint
name|col
parameter_list|)
block|{
return|return
operator|(
literal|0
operator|<=
operator|(
name|row
operator|)
operator|&&
operator|(
name|row
operator|)
operator|<
name|sel_get_height
argument_list|()
operator|&&
literal|0
operator|<=
operator|(
name|col
operator|)
operator|&&
operator|(
name|col
operator|)
operator|<
name|sel_get_width
argument_list|()
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gen_anchor (gdouble * p,gdouble x,gdouble y,gboolean is_newcurve)
name|gen_anchor
parameter_list|(
name|gdouble
modifier|*
name|p
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gboolean
name|is_newcurve
parameter_list|)
block|{
comment|/*   printf("TYPE: %s X: %d Y: %d\n",  */
comment|/* 	 (is_newcurve)?"3":"1",  */
comment|/* 	 sel_x1+(int)RINT(x),  */
comment|/* 	 sel_y1 + sel_height - (int)RINT(y)+1); */
operator|*
name|p
operator|++
operator|=
operator|(
name|sel_x1
operator|+
operator|(
name|gint
operator|)
name|RINT
argument_list|(
name|x
argument_list|)
operator|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|sel_y1
operator|+
name|sel_height
operator|-
operator|(
name|gint
operator|)
name|RINT
argument_list|(
name|y
argument_list|)
operator|+
literal|1
expr_stmt|;
operator|*
name|p
operator|++
operator|=
operator|(
name|is_newcurve
operator|)
condition|?
literal|3.0
else|:
literal|1.0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gen_control (gdouble * p,gdouble x,gdouble y)
name|gen_control
parameter_list|(
name|gdouble
modifier|*
name|p
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
comment|/*   printf("TYPE: 2 X: %d Y: %d\n",  */
comment|/*  	 sel_x1+(int)RINT(x),  */
comment|/*  	 sel_y1 + sel_height - (int)RINT(y)+1);  */
operator|*
name|p
operator|++
operator|=
name|sel_x1
operator|+
operator|(
name|gint
operator|)
name|RINT
argument_list|(
name|x
argument_list|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|sel_y1
operator|+
name|sel_height
operator|-
operator|(
name|gint
operator|)
name|RINT
argument_list|(
name|y
argument_list|)
operator|+
literal|1
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|2.0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|do_points (spline_list_array_type in_splines,gint32 image_ID)
name|do_points
parameter_list|(
name|spline_list_array_type
name|in_splines
parameter_list|,
name|gint32
name|image_ID
parameter_list|)
block|{
name|unsigned
name|this_list
decl_stmt|;
name|gint
name|seg_count
init|=
literal|0
decl_stmt|;
name|gint
name|point_count
init|=
literal|0
decl_stmt|;
name|gdouble
name|last_x
decl_stmt|,
name|last_y
decl_stmt|;
name|gdouble
modifier|*
name|parray
decl_stmt|;
name|gdouble
modifier|*
name|cur_parray
decl_stmt|;
name|gint
name|path_point_count
decl_stmt|;
for|for
control|(
name|this_list
operator|=
literal|0
init|;
name|this_list
operator|<
name|SPLINE_LIST_ARRAY_LENGTH
argument_list|(
name|in_splines
argument_list|)
condition|;
name|this_list
operator|++
control|)
block|{
name|spline_list_type
name|in_list
init|=
name|SPLINE_LIST_ARRAY_ELT
argument_list|(
name|in_splines
argument_list|,
name|this_list
argument_list|)
decl_stmt|;
comment|/* Ignore single points that are on their own */
if|if
condition|(
name|SPLINE_LIST_LENGTH
argument_list|(
name|in_list
argument_list|)
operator|<
literal|2
condition|)
continue|continue;
name|point_count
operator|+=
name|SPLINE_LIST_LENGTH
argument_list|(
name|in_list
argument_list|)
expr_stmt|;
block|}
comment|/*   printf("Name SEL2PATH\n"); */
comment|/*   printf("#POINTS: %d\n",point_count*3); */
comment|/*   printf("CLOSED: 1\n"); */
comment|/*   printf("DRAW: 0\n"); */
comment|/*   printf("STATE: 4\n"); */
name|path_point_count
operator|=
name|point_count
operator|*
literal|9
expr_stmt|;
name|cur_parray
operator|=
operator|(
name|gdouble
operator|*
operator|)
name|g_new0
argument_list|(
name|gdouble
argument_list|,
name|point_count
operator|*
literal|9
argument_list|)
expr_stmt|;
name|parray
operator|=
name|cur_parray
expr_stmt|;
name|point_count
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|this_list
operator|=
literal|0
init|;
name|this_list
operator|<
name|SPLINE_LIST_ARRAY_LENGTH
argument_list|(
name|in_splines
argument_list|)
condition|;
name|this_list
operator|++
control|)
block|{
name|unsigned
name|this_spline
decl_stmt|;
name|spline_list_type
name|in_list
init|=
name|SPLINE_LIST_ARRAY_ELT
argument_list|(
name|in_splines
argument_list|,
name|this_list
argument_list|)
decl_stmt|;
comment|/*       if(seg_count> 0&& point_count> 0)   */
comment|/* 	gen_anchor(last_x,last_y,0);   */
name|point_count
operator|=
literal|0
expr_stmt|;
comment|/* Ignore single points that are on their own */
if|if
condition|(
name|SPLINE_LIST_LENGTH
argument_list|(
name|in_list
argument_list|)
operator|<
literal|2
condition|)
continue|continue;
for|for
control|(
name|this_spline
operator|=
literal|0
init|;
name|this_spline
operator|<
name|SPLINE_LIST_LENGTH
argument_list|(
name|in_list
argument_list|)
condition|;
name|this_spline
operator|++
control|)
block|{
name|spline_type
name|s
init|=
name|SPLINE_LIST_ELT
argument_list|(
name|in_list
argument_list|,
name|this_spline
argument_list|)
decl_stmt|;
if|if
condition|(
name|SPLINE_DEGREE
argument_list|(
name|s
argument_list|)
operator|==
name|LINEAR
condition|)
block|{
name|gen_anchor
argument_list|(
name|cur_parray
argument_list|,
name|START_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|x
argument_list|,
name|START_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|y
argument_list|,
name|seg_count
operator|&&
operator|!
name|point_count
argument_list|)
expr_stmt|;
name|cur_parray
operator|+=
literal|3
expr_stmt|;
name|gen_control
argument_list|(
name|cur_parray
argument_list|,
name|START_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|x
argument_list|,
name|START_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|y
argument_list|)
expr_stmt|;
name|cur_parray
operator|+=
literal|3
expr_stmt|;
name|gen_control
argument_list|(
name|cur_parray
argument_list|,
name|END_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|x
argument_list|,
name|END_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|y
argument_list|)
expr_stmt|;
name|cur_parray
operator|+=
literal|3
expr_stmt|;
name|last_x
operator|=
name|END_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|x
expr_stmt|;
name|last_y
operator|=
name|END_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|SPLINE_DEGREE
argument_list|(
name|s
argument_list|)
operator|==
name|CUBIC
condition|)
block|{
name|gen_anchor
argument_list|(
name|cur_parray
argument_list|,
name|START_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|x
argument_list|,
name|START_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|y
argument_list|,
name|seg_count
operator|&&
operator|!
name|point_count
argument_list|)
expr_stmt|;
name|cur_parray
operator|+=
literal|3
expr_stmt|;
name|gen_control
argument_list|(
name|cur_parray
argument_list|,
name|CONTROL1
argument_list|(
name|s
argument_list|)
operator|.
name|x
argument_list|,
name|CONTROL1
argument_list|(
name|s
argument_list|)
operator|.
name|y
argument_list|)
expr_stmt|;
name|cur_parray
operator|+=
literal|3
expr_stmt|;
name|gen_control
argument_list|(
name|cur_parray
argument_list|,
name|CONTROL2
argument_list|(
name|s
argument_list|)
operator|.
name|x
argument_list|,
name|CONTROL2
argument_list|(
name|s
argument_list|)
operator|.
name|y
argument_list|)
expr_stmt|;
name|cur_parray
operator|+=
literal|3
expr_stmt|;
name|last_x
operator|=
name|END_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|x
expr_stmt|;
name|last_y
operator|=
name|END_POINT
argument_list|(
name|s
argument_list|)
operator|.
name|y
expr_stmt|;
block|}
else|else
name|g_message
argument_list|(
name|_
argument_list|(
literal|"print_spline: strange degree (%d)"
argument_list|)
argument_list|,
name|SPLINE_DEGREE
argument_list|(
name|s
argument_list|)
argument_list|)
expr_stmt|;
name|point_count
operator|++
expr_stmt|;
block|}
name|seg_count
operator|++
expr_stmt|;
block|}
name|gimp_path_set_points
argument_list|(
name|image_ID
argument_list|,
name|_
argument_list|(
literal|"selection_to_path"
argument_list|)
argument_list|,
literal|1
argument_list|,
name|path_point_count
argument_list|,
name|parray
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|do_sel2path (gint32 drawable_ID,gint32 image_ID)
name|do_sel2path
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint32
name|image_ID
parameter_list|)
block|{
name|gint32
name|selection_ID
decl_stmt|;
name|GimpDrawable
modifier|*
name|sel_drawable
decl_stmt|;
name|pixel_outline_list_type
name|olt
decl_stmt|;
name|spline_list_array_type
name|splines
decl_stmt|;
name|gimp_selection_bounds
argument_list|(
name|image_ID
argument_list|,
operator|&
name|has_sel
argument_list|,
operator|&
name|sel_x1
argument_list|,
operator|&
name|sel_y1
argument_list|,
operator|&
name|sel_x2
argument_list|,
operator|&
name|sel_y2
argument_list|)
expr_stmt|;
name|sel_width
operator|=
name|sel_x2
operator|-
name|sel_x1
expr_stmt|;
name|sel_height
operator|=
name|sel_y2
operator|-
name|sel_y1
expr_stmt|;
comment|/* Now get the selection channel */
name|selection_ID
operator|=
name|gimp_image_get_selection
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection_ID
operator|<
literal|0
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"gimp_image_get_selection failed"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|sel_drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|selection_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_bpp
argument_list|(
name|selection_ID
argument_list|)
operator|!=
literal|1
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Internal error. Selection bpp> 1"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|selection_rgn
argument_list|,
name|sel_drawable
argument_list|,
name|sel_x1
argument_list|,
name|sel_y1
argument_list|,
name|sel_width
argument_list|,
name|sel_height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
name|sel_drawable
operator|->
name|width
operator|+
name|gimp_tile_width
argument_list|()
operator|-
literal|1
operator|)
operator|/
name|gimp_tile_width
argument_list|()
argument_list|)
expr_stmt|;
name|olt
operator|=
name|find_outline_pixels
argument_list|()
expr_stmt|;
name|splines
operator|=
name|fitted_splines
argument_list|(
name|olt
argument_list|)
expr_stmt|;
name|gimp_selection_none
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
name|do_points
argument_list|(
name|splines
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|safe_free (address * item)
name|safe_free
parameter_list|(
name|address
modifier|*
name|item
parameter_list|)
block|{
if|if
condition|(
name|item
operator|==
name|NULL
operator|||
operator|*
name|item
operator|==
name|NULL
condition|)
block|{
name|g_warning
argument_list|(
literal|"safe_free: Attempt to free a null item."
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
operator|*
name|item
argument_list|)
expr_stmt|;
operator|*
name|item
operator|=
name|NULL
expr_stmt|;
block|}
end_function

end_unit

