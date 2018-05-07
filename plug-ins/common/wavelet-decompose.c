begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  *  Wavelet decompose plug-in by Miroslav Talasek, miroslav.talasek@seznam.cz  */
end_comment

begin_comment
comment|/*  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-wavelet-decompose"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-wavelet-decompose"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"wavelet-decompose"
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|120
end_define

begin_define
DECL|macro|ENTRY_WIDTH
define|#
directive|define
name|ENTRY_WIDTH
value|5
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d347690108
block|{
DECL|member|scales
name|gint
name|scales
decl_stmt|;
DECL|member|create_group
name|gint
name|create_group
decl_stmt|;
DECL|member|create_masks
name|gint
name|create_masks
decl_stmt|;
DECL|typedef|WaveletDecomposeParams
block|}
name|WaveletDecomposeParams
typedef|;
end_typedef

begin_comment
comment|/* Declare local functions.  */
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
name|void
name|wavelet_blur
parameter_list|(
name|gint32
name|drawable_id
parameter_list|,
name|gint
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|wavelet_decompose_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* create a few globals, set default values */
end_comment

begin_decl_stmt
DECL|variable|wavelet_params
specifier|static
name|WaveletDecomposeParams
name|wavelet_params
init|=
block|{
literal|5
block|,
comment|/* default scales */
literal|1
block|,
comment|/* create group */
literal|0
comment|/* do not add mask by default */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
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
literal|"run-mode"
block|,
literal|"The run mode { RUN-INTERACTIVE (0), "
literal|"RUN-NONINTERACTIVE (1) }"
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
name|GIMP_PDB_INT32
block|,
literal|"scales"
block|,
literal|"Number of scales (1-7)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"create-group"
block|,
literal|"Create a layer group to store the "
literal|"decomposition"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"create-masks"
block|,
literal|"Add a layer mask to each scales "
literal|"layers"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Wavelet decompose"
argument_list|)
argument_list|,
literal|"Compute and render wavelet scales"
argument_list|,
literal|"Miroslav Talasek<miroslav.talasek@seznam.cz>"
argument_list|,
literal|"Miroslav Talasek<miroslav.talasek@seznam.cz>"
argument_list|,
literal|"19january 2017"
argument_list|,
name|N_
argument_list|(
literal|"_Wavelet-decompose..."
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
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
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Filters/Enhance"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint32
name|image_id
decl_stmt|;
name|gint32
name|drawable_id
decl_stmt|;
name|GimpRunMode
name|run_mode
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
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
name|status
expr_stmt|;
name|image_id
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
name|drawable_id
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|wavelet_params
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|wavelet_decompose_dialog
argument_list|()
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|6
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|wavelet_params
operator|.
name|scales
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|wavelet_params
operator|.
name|create_group
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|wavelet_params
operator|.
name|create_masks
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|wavelet_params
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gint32
modifier|*
name|scale_ids
decl_stmt|;
name|gint32
name|new_scale_id
decl_stmt|;
name|gint32
name|parent_id
decl_stmt|;
name|GimpLayerMode
name|grain_extract_mode
init|=
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
decl_stmt|;
name|GimpLayerMode
name|grain_merge_mode
init|=
name|GIMP_LAYER_MODE_GRAIN_MERGE
decl_stmt|;
name|gint
name|id
decl_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Wavelet-Decompose"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|gimp_image_freeze_layers
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|wavelet_params
operator|.
name|create_group
condition|)
block|{
name|gint32
name|group_id
init|=
name|gimp_layer_group_new
argument_list|(
name|image_id
argument_list|)
decl_stmt|;
name|gimp_item_set_name
argument_list|(
name|group_id
argument_list|,
name|_
argument_list|(
literal|"Decomposition"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|group_id
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image_id
argument_list|,
name|group_id
argument_list|,
name|gimp_item_get_parent
argument_list|(
name|drawable_id
argument_list|)
argument_list|,
name|gimp_image_get_item_position
argument_list|(
name|image_id
argument_list|,
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
name|parent_id
operator|=
name|group_id
expr_stmt|;
block|}
else|else
name|parent_id
operator|=
operator|-
literal|1
expr_stmt|;
name|scale_ids
operator|=
name|g_new
argument_list|(
name|gint32
argument_list|,
name|wavelet_params
operator|.
name|scales
argument_list|)
expr_stmt|;
name|new_scale_id
operator|=
name|gimp_layer_copy
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image_id
argument_list|,
name|new_scale_id
argument_list|,
name|parent_id
argument_list|,
name|gimp_image_get_item_position
argument_list|(
name|image_id
argument_list|,
name|drawable_id
argument_list|)
argument_list|)
expr_stmt|;
comment|/* the exact result of the grain-extract and grain-merge modes depends on        * the choice of (gamma-corrected) midpoint intensity value.  for the        * non-legacy modes, the midpoint value is 0.5, which isn't representable        * exactly using integer precision.  for the legacy modes, the midpoint        * value is 128/255 (i.e., 0x80), which is representable exactly using        * (gamma-corrected) integer precision.  we therefore use the legacy        * modes when the input image precision is integer, and only use the        * (preferable) non-legacy modes when the input image precision is        * floating point.        *        * this avoids imperfect reconstruction of the image when using integer        * precision.  see bug #786844.        */
switch|switch
condition|(
name|gimp_image_get_precision
argument_list|(
name|image_id
argument_list|)
condition|)
block|{
case|case
name|GIMP_PRECISION_U8_LINEAR
case|:
case|case
name|GIMP_PRECISION_U8_GAMMA
case|:
case|case
name|GIMP_PRECISION_U16_LINEAR
case|:
case|case
name|GIMP_PRECISION_U16_GAMMA
case|:
case|case
name|GIMP_PRECISION_U32_LINEAR
case|:
case|case
name|GIMP_PRECISION_U32_GAMMA
case|:
name|grain_extract_mode
operator|=
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
expr_stmt|;
name|grain_merge_mode
operator|=
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
expr_stmt|;
break|break;
case|case
name|GIMP_PRECISION_HALF_LINEAR
case|:
case|case
name|GIMP_PRECISION_HALF_GAMMA
case|:
case|case
name|GIMP_PRECISION_FLOAT_LINEAR
case|:
case|case
name|GIMP_PRECISION_FLOAT_GAMMA
case|:
case|case
name|GIMP_PRECISION_DOUBLE_LINEAR
case|:
case|case
name|GIMP_PRECISION_DOUBLE_GAMMA
case|:
name|grain_extract_mode
operator|=
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
expr_stmt|;
name|grain_merge_mode
operator|=
name|GIMP_LAYER_MODE_GRAIN_MERGE
expr_stmt|;
break|break;
block|}
for|for
control|(
name|id
operator|=
literal|0
init|;
name|id
operator|<
name|wavelet_params
operator|.
name|scales
condition|;
operator|++
name|id
control|)
block|{
name|gint32
name|blur_id
decl_stmt|,
name|tmp_id
decl_stmt|;
name|gchar
name|scale_name
index|[
literal|20
index|]
decl_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|id
operator|/
operator|(
name|gdouble
operator|)
name|wavelet_params
operator|.
name|scales
argument_list|)
expr_stmt|;
name|scale_ids
index|[
name|id
index|]
operator|=
name|new_scale_id
expr_stmt|;
name|g_snprintf
argument_list|(
name|scale_name
argument_list|,
sizeof|sizeof
argument_list|(
name|scale_name
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Scale %d"
argument_list|)
argument_list|,
name|id
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_item_set_name
argument_list|(
name|new_scale_id
argument_list|,
name|scale_name
argument_list|)
expr_stmt|;
name|tmp_id
operator|=
name|gimp_layer_copy
argument_list|(
name|new_scale_id
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image_id
argument_list|,
name|tmp_id
argument_list|,
name|parent_id
argument_list|,
name|gimp_image_get_item_position
argument_list|(
name|image_id
argument_list|,
name|new_scale_id
argument_list|)
argument_list|)
expr_stmt|;
name|wavelet_blur
argument_list|(
name|tmp_id
argument_list|,
name|pow
argument_list|(
literal|2.0
argument_list|,
name|id
argument_list|)
argument_list|)
expr_stmt|;
name|blur_id
operator|=
name|gimp_layer_copy
argument_list|(
name|tmp_id
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image_id
argument_list|,
name|blur_id
argument_list|,
name|parent_id
argument_list|,
name|gimp_image_get_item_position
argument_list|(
name|image_id
argument_list|,
name|tmp_id
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_layer_set_mode
argument_list|(
name|tmp_id
argument_list|,
name|grain_extract_mode
argument_list|)
expr_stmt|;
name|new_scale_id
operator|=
name|gimp_image_merge_down
argument_list|(
name|image_id
argument_list|,
name|tmp_id
argument_list|,
name|GIMP_EXPAND_AS_NECESSARY
argument_list|)
expr_stmt|;
name|scale_ids
index|[
name|id
index|]
operator|=
name|new_scale_id
expr_stmt|;
name|gimp_item_set_visible
argument_list|(
name|new_scale_id
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|new_scale_id
operator|=
name|blur_id
expr_stmt|;
block|}
name|gimp_item_set_name
argument_list|(
name|new_scale_id
argument_list|,
name|_
argument_list|(
literal|"Residual"
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|id
operator|=
literal|0
init|;
name|id
operator|<
name|wavelet_params
operator|.
name|scales
condition|;
name|id
operator|++
control|)
block|{
name|gimp_image_reorder_item
argument_list|(
name|image_id
argument_list|,
name|scale_ids
index|[
name|id
index|]
argument_list|,
name|parent_id
argument_list|,
name|gimp_image_get_item_position
argument_list|(
name|image_id
argument_list|,
name|new_scale_id
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_layer_set_mode
argument_list|(
name|scale_ids
index|[
name|id
index|]
argument_list|,
name|grain_merge_mode
argument_list|)
expr_stmt|;
if|if
condition|(
name|wavelet_params
operator|.
name|create_masks
condition|)
block|{
name|gint32
name|mask_id
init|=
name|gimp_layer_create_mask
argument_list|(
name|scale_ids
index|[
name|id
index|]
argument_list|,
name|GIMP_ADD_MASK_WHITE
argument_list|)
decl_stmt|;
name|gimp_layer_add_mask
argument_list|(
name|scale_ids
index|[
name|id
index|]
argument_list|,
name|mask_id
argument_list|)
expr_stmt|;
block|}
name|gimp_item_set_visible
argument_list|(
name|scale_ids
index|[
name|id
index|]
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|wavelet_params
operator|.
name|create_group
condition|)
name|gimp_item_set_visible
argument_list|(
name|parent_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|scale_ids
argument_list|)
expr_stmt|;
name|gimp_image_thaw_layers
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
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
name|gimp_displays_flush
argument_list|()
expr_stmt|;
comment|/* set data for next use of filter */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|wavelet_params
argument_list|,
sizeof|sizeof
argument_list|(
name|WaveletDecomposeParams
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gegl_exit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|wavelet_blur (gint32 drawable_id,gint radius)
name|wavelet_blur
parameter_list|(
name|gint32
name|drawable_id
parameter_list|,
name|gint
name|radius
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
if|if
condition|(
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable_id
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
init|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable_id
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|shadow
init|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawable_id
argument_list|)
decl_stmt|;
name|gegl_render_op
argument_list|(
name|buffer
argument_list|,
name|shadow
argument_list|,
literal|"gegl:wavelet-blur"
argument_list|,
literal|"radius"
argument_list|,
operator|(
name|gdouble
operator|)
name|radius
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_buffer_flush
argument_list|(
name|shadow
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable_id
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable_id
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shadow
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|wavelet_decompose_dialog (void)
name|wavelet_decompose_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Wavelet decompose"
argument_list|)
argument_list|,
name|PLUG_IN_ROLE
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_OK"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|main_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/* scales */
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Scales:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
name|ENTRY_WIDTH
argument_list|,
name|wavelet_params
operator|.
name|scales
argument_list|,
literal|1.0
argument_list|,
literal|7.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|wavelet_params
operator|.
name|scales
argument_list|)
expr_stmt|;
comment|/* create group layer */
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Create a layer group to store the decomposition"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|wavelet_params
operator|.
name|create_group
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|wavelet_params
operator|.
name|create_group
argument_list|)
expr_stmt|;
comment|/* create layer masks */
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Add a layer mask to each scales layers"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|wavelet_params
operator|.
name|create_masks
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|wavelet_params
operator|.
name|create_masks
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

