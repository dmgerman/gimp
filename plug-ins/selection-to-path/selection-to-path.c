begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Plugin to convert a selection to a path.  *  * Copyright (C) 1999 Andy Thomas  alt@gimp.org  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
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
file|"selection-to-path.h"
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
value|"plug-in-sel2path"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"selection-to-path"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-selection-to-path"
end_define

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_define
DECL|macro|MID_POINT
define|#
directive|define
name|MID_POINT
value|127
end_define

begin_typedef
DECL|typedef|Sel2path
typedef|typedef
name|struct
name|_Sel2path
name|Sel2path
typedef|;
end_typedef

begin_typedef
DECL|typedef|Sel2pathClass
typedef|typedef
name|struct
name|_Sel2pathClass
name|Sel2pathClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Sel2path
struct|struct
name|_Sel2path
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_Sel2pathClass
struct|struct
name|_Sel2pathClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|SEL2PATH_TYPE
define|#
directive|define
name|SEL2PATH_TYPE
value|(sel2path_get_type ())
end_define

begin_define
DECL|macro|SEL2PATH
define|#
directive|define
name|SEL2PATH
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SEL2PATH_TYPE, Sel2path))
end_define

begin_decl_stmt
name|GType
name|sel2path_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|GList
modifier|*
name|sel2path_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProcedure
modifier|*
name|sel2path_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|sel2path_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
name|sel2path_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
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
specifier|static
name|gboolean
name|sel2path
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|Sel2path
argument_list|,
argument|sel2path
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|SEL2PATH_TYPE
argument_list|)
end_macro

begin_decl_stmt
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
DECL|variable|sel_sampler
specifier|static
name|GeglSampler
modifier|*
name|sel_sampler
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|retVal
specifier|static
name|gboolean
name|retVal
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|retVal
comment|/* Toggle if cancel button clicked */
end_comment

begin_function
specifier|static
name|void
DECL|function|sel2path_class_init (Sel2pathClass * klass)
name|sel2path_class_init
parameter_list|(
name|Sel2pathClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPlugInClass
modifier|*
name|plug_in_class
init|=
name|GIMP_PLUG_IN_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|plug_in_class
operator|->
name|query_procedures
operator|=
name|sel2path_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|sel2path_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|sel2path_init (Sel2path * sel2path)
name|sel2path_init
parameter_list|(
name|Sel2path
modifier|*
name|sel2path
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|sel2path_query_procedures (GimpPlugIn * plug_in)
name|sel2path_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
return|return
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|g_strdup
argument_list|(
name|PLUG_IN_PROC
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|sel2path_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|sel2path_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_image_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_PROC_TYPE_PLUGIN
argument_list|,
name|sel2path_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_image_types
argument_list|(
name|procedure
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Converts a selection to a path"
argument_list|,
literal|"Converts a selection to a path"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"Andy Thomas"
argument_list|,
literal|"1999"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"align-threshold"
argument_list|,
literal|"Align threshold"
argument_list|,
literal|"Align threshold"
argument_list|,
literal|0.2
argument_list|,
literal|2.0
argument_list|,
literal|0.5
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"corner-always-threshold"
argument_list|,
literal|"Corner always threshold"
argument_list|,
literal|"Corner always threshold"
argument_list|,
literal|30
argument_list|,
literal|180
argument_list|,
literal|60.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"corner-surround"
argument_list|,
literal|"Corner surround"
argument_list|,
literal|"Corner surround"
argument_list|,
literal|3
argument_list|,
literal|8
argument_list|,
literal|4
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"corner-threshold"
argument_list|,
literal|"Corner threshold"
argument_list|,
literal|"Corner threshold"
argument_list|,
literal|0
argument_list|,
literal|180
argument_list|,
literal|100.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"error-threshold"
argument_list|,
literal|"Error threshold"
argument_list|,
literal|"Error threshold"
argument_list|,
literal|0.2
argument_list|,
literal|10
argument_list|,
literal|0.4
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"filter-alternative-surround"
argument_list|,
literal|"Filter alternative surround"
argument_list|,
literal|"Filter alternative surround"
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|1
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"filter-epsilon"
argument_list|,
literal|"Filter epsilon"
argument_list|,
literal|"Filter epsilon"
argument_list|,
literal|5
argument_list|,
literal|40
argument_list|,
literal|10.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"filter-iteration-count"
argument_list|,
literal|"Filter iteration count"
argument_list|,
literal|"Filter iteration count"
argument_list|,
literal|4
argument_list|,
literal|70
argument_list|,
literal|4
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"filter-percent"
argument_list|,
literal|"Filter percent"
argument_list|,
literal|"Filter percent"
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.33
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"filter-secondary-surround"
argument_list|,
literal|"Filter secondary surround"
argument_list|,
literal|"Filter secondary surround"
argument_list|,
literal|3
argument_list|,
literal|10
argument_list|,
literal|3
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"filter-surround"
argument_list|,
literal|"Filter surround"
argument_list|,
literal|"Filter surround"
argument_list|,
literal|2
argument_list|,
literal|10
argument_list|,
literal|2
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"keep-knees"
argument_list|,
literal|"Keep knees"
argument_list|,
literal|"Keep knees"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"line-reversion-threshold"
argument_list|,
literal|"Line reversion threshold"
argument_list|,
literal|"Line reversion threshold"
argument_list|,
literal|0.01
argument_list|,
literal|0.2
argument_list|,
literal|0.01
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"line-threshold"
argument_list|,
literal|"Line threshold"
argument_list|,
literal|"Line threshold"
argument_list|,
literal|0.2
argument_list|,
literal|4
argument_list|,
literal|0.5
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"reparametrize-improvement"
argument_list|,
literal|"Reparametrize improvement"
argument_list|,
literal|"Reparametrize improvement"
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.01
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"reparametrize-threshold"
argument_list|,
literal|"Reparametrize threshold"
argument_list|,
literal|"Reparametrize threshold"
argument_list|,
literal|1
argument_list|,
literal|50
argument_list|,
literal|1.0
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"subdivide-search"
argument_list|,
literal|"Subdivide search"
argument_list|,
literal|"Subdivide search"
argument_list|,
literal|0.05
argument_list|,
literal|1
argument_list|,
literal|0.1
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"subdivide-surround"
argument_list|,
literal|"Subdivide surround"
argument_list|,
literal|"Subdivide surround"
argument_list|,
literal|2
argument_list|,
literal|10
argument_list|,
literal|4
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"subdivide-threshold"
argument_list|,
literal|"Subdivide threshold"
argument_list|,
literal|"Subdivide threshold"
argument_list|,
literal|0.01
argument_list|,
literal|1
argument_list|,
literal|0.03
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"tangent-surround"
argument_list|,
literal|"Tangent surround"
argument_list|,
literal|"Tangent surround"
argument_list|,
literal|2
argument_list|,
literal|10
argument_list|,
literal|3
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|sel2path_run (GimpProcedure * procedure,GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,const GimpValueArray * args,gpointer run_data)
name|sel2path_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
if|if
condition|(
name|gimp_selection_is_empty
argument_list|(
name|image
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
name|fit_set_default_params
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
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
name|PLUG_IN_PROC
argument_list|)
operator|>
literal|0
condition|)
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|selVals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sel2path_dialog
argument_list|(
operator|&
name|selVals
argument_list|)
condition|)
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_CANCEL
argument_list|,
name|NULL
argument_list|)
return|;
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
name|selVals
operator|.
name|align_threshold
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|corner_always_threshold
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|corner_surround
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|corner_threshold
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|error_threshold
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|filter_alternative_surround
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|filter_epsilon
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|filter_iteration_count
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|filter_percent
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|filter_secondary_surround
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|filter_surround
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|keep_knees
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|line_reversion_threshold
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|line_threshold
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|13
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|reparameterize_improvement
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|reparameterize_threshold
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|subdivide_search
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|subdivide_surround
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|subdivide_threshold
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|18
argument_list|)
expr_stmt|;
name|selVals
operator|.
name|tangent_surround
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|19
argument_list|)
expr_stmt|;
name|fit_set_params
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
if|if
condition|(
name|gimp_get_data_size
argument_list|(
name|PLUG_IN_PROC
argument_list|)
operator|>
literal|0
condition|)
block|{
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
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
if|if
condition|(
operator|!
name|sel2path
argument_list|(
name|image
argument_list|)
condition|)
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|NULL
argument_list|)
return|;
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
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
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
name|PLUG_IN_BINARY
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Selection to Path Advanced Settings"
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
literal|"_Reset"
argument_list|)
argument_list|,
name|RESPONSE_RESET
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
name|gimp_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
argument_list|,
name|RESPONSE_RESET
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
name|dlg
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dlg
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|sel2path_response
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dlg
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
name|dlg
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|table
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
DECL|function|sel2path_response (GtkWidget * widget,gint response_id,gpointer data)
name|sel2path_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|RESPONSE_RESET
case|:
name|reset_adv_dialog
argument_list|()
expr_stmt|;
name|fit_set_params
argument_list|(
operator|&
name|selVals
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
name|retVal
operator|=
name|TRUE
expr_stmt|;
default|default:
name|gtk_widget_destroy
argument_list|(
name|widget
argument_list|)
expr_stmt|;
break|break;
block|}
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
name|gegl_sampler_get
argument_list|(
name|sel_sampler
argument_list|,
name|col
operator|+
name|sel_x1
argument_list|,
name|row
operator|+
name|sel_y1
argument_list|,
name|NULL
argument_list|,
operator|&
name|ret
argument_list|,
name|GEGL_ABYSS_NONE
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
name|gboolean
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
specifier|static
name|void
DECL|function|do_points (spline_list_array_type in_splines,GimpImage * image)
name|do_points
parameter_list|(
name|spline_list_array_type
name|in_splines
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|gint32
name|stroke
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|gboolean
name|have_points
init|=
name|FALSE
decl_stmt|;
name|spline_list_type
name|spline_list
decl_stmt|;
comment|/* check if there really is something to do... */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|SPLINE_LIST_ARRAY_LENGTH
argument_list|(
name|in_splines
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|spline_list
operator|=
name|SPLINE_LIST_ARRAY_ELT
argument_list|(
name|in_splines
argument_list|,
name|i
argument_list|)
expr_stmt|;
comment|/* Ignore single points that are on their own */
if|if
condition|(
name|SPLINE_LIST_LENGTH
argument_list|(
name|spline_list
argument_list|)
operator|<
literal|2
condition|)
continue|continue;
name|have_points
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|have_points
condition|)
return|return;
name|vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Selection"
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|SPLINE_LIST_ARRAY_LENGTH
argument_list|(
name|in_splines
argument_list|)
condition|;
name|j
operator|++
control|)
block|{
name|spline_type
name|seg
decl_stmt|;
name|spline_list
operator|=
name|SPLINE_LIST_ARRAY_ELT
argument_list|(
name|in_splines
argument_list|,
name|j
argument_list|)
expr_stmt|;
comment|/* Ignore single points that are on their own */
if|if
condition|(
name|SPLINE_LIST_LENGTH
argument_list|(
name|spline_list
argument_list|)
operator|<
literal|2
condition|)
continue|continue;
name|seg
operator|=
name|SPLINE_LIST_ELT
argument_list|(
name|spline_list
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|stroke
operator|=
name|gimp_vectors_bezier_stroke_new_moveto
argument_list|(
name|vectors
argument_list|,
name|START_POINT
argument_list|(
name|seg
argument_list|)
operator|.
name|x
argument_list|,
name|START_POINT
argument_list|(
name|seg
argument_list|)
operator|.
name|y
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
name|SPLINE_LIST_LENGTH
argument_list|(
name|spline_list
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|seg
operator|=
name|SPLINE_LIST_ELT
argument_list|(
name|spline_list
argument_list|,
name|i
argument_list|)
expr_stmt|;
if|if
condition|(
name|SPLINE_DEGREE
argument_list|(
name|seg
argument_list|)
operator|==
name|LINEAR
condition|)
name|gimp_vectors_bezier_stroke_lineto
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|,
name|END_POINT
argument_list|(
name|seg
argument_list|)
operator|.
name|x
argument_list|,
name|END_POINT
argument_list|(
name|seg
argument_list|)
operator|.
name|y
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|SPLINE_DEGREE
argument_list|(
name|seg
argument_list|)
operator|==
name|CUBIC
condition|)
name|gimp_vectors_bezier_stroke_cubicto
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|,
name|CONTROL1
argument_list|(
name|seg
argument_list|)
operator|.
name|x
argument_list|,
name|CONTROL1
argument_list|(
name|seg
argument_list|)
operator|.
name|y
argument_list|,
name|CONTROL2
argument_list|(
name|seg
argument_list|)
operator|.
name|x
argument_list|,
name|CONTROL2
argument_list|(
name|seg
argument_list|)
operator|.
name|y
argument_list|,
name|END_POINT
argument_list|(
name|seg
argument_list|)
operator|.
name|x
argument_list|,
name|END_POINT
argument_list|(
name|seg
argument_list|)
operator|.
name|y
argument_list|)
expr_stmt|;
else|else
name|g_warning
argument_list|(
literal|"print_spline: strange degree (%d)"
argument_list|,
name|SPLINE_DEGREE
argument_list|(
name|seg
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_vectors_stroke_close
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
expr_stmt|;
comment|/* transform to GIMPs coordinate system, taking the selections        * bounding box into account  */
name|gimp_vectors_stroke_scale
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|,
literal|1.0
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_vectors_stroke_translate
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|,
name|sel_x1
argument_list|,
name|sel_y1
operator|+
name|sel_height
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
name|gimp_image_insert_vectors
argument_list|(
name|image
argument_list|,
name|vectors
argument_list|,
name|NULL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|sel2path (GimpImage * image)
name|sel2path
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpSelection
modifier|*
name|selection
decl_stmt|;
name|GeglBuffer
modifier|*
name|sel_buffer
decl_stmt|;
name|pixel_outline_list_type
name|olt
decl_stmt|;
name|spline_list_array_type
name|splines
decl_stmt|;
name|gimp_selection_bounds
argument_list|(
name|image
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
name|selection
operator|=
name|gimp_image_get_selection
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|selection
condition|)
return|return
name|FALSE
return|;
name|sel_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|selection
argument_list|)
argument_list|)
expr_stmt|;
name|sel_sampler
operator|=
name|gegl_buffer_sampler_new
argument_list|(
name|sel_buffer
argument_list|,
name|babl_format
argument_list|(
literal|"Y u8"
argument_list|)
argument_list|,
name|GEGL_SAMPLER_NEAREST
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
name|do_points
argument_list|(
name|splines
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|sel_sampler
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|sel_buffer
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
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

