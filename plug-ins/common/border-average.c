begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* borderaverage 0.01 - image processing plug-in for GIMP.  *  * Copyright (C) 1998 Philipp Klaus (webmaster@access.ch)  *  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
value|"plug-in-borderaverage"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"border-average"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-border-average"
end_define

begin_typedef
DECL|typedef|BorderAverage
typedef|typedef
name|struct
name|_BorderAverage
name|BorderAverage
typedef|;
end_typedef

begin_typedef
DECL|typedef|BorderAverageClass
typedef|typedef
name|struct
name|_BorderAverageClass
name|BorderAverageClass
typedef|;
end_typedef

begin_struct
DECL|struct|_BorderAverage
struct|struct
name|_BorderAverage
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_BorderAverageClass
struct|struct
name|_BorderAverageClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|BORDER_AVERAGE_TYPE
define|#
directive|define
name|BORDER_AVERAGE_TYPE
value|(border_average_get_type ())
end_define

begin_define
DECL|macro|BORDER_AVERAGE
define|#
directive|define
name|BORDER_AVERAGE
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), BORDER_AVERAGE_TYPE, BorderAverage))
end_define

begin_decl_stmt
name|GType
name|border_average_get_type
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
name|border_average_query_procedures
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
name|border_average_create_procedure
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
name|border_average_run
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
name|void
name|borderaverage
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRGB
modifier|*
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|borderaverage_dialog
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|add_new_color
parameter_list|(
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
modifier|*
name|cube
parameter_list|,
name|gint
name|bucket_expo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|thickness_callback
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

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|BorderAverage
argument_list|,
argument|border_average
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|BORDER_AVERAGE_TYPE
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|gint
name|borderaverage_thickness
init|=
literal|3
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|borderaverage_bucket_exponent
specifier|static
name|gint
name|borderaverage_bucket_exponent
init|=
literal|4
decl_stmt|;
end_decl_stmt

begin_struct
DECL|struct|borderaverage_data
struct|struct
name|borderaverage_data
block|{
DECL|member|thickness
name|gint
name|thickness
decl_stmt|;
DECL|member|bucket_exponent
name|gint
name|bucket_exponent
decl_stmt|;
block|}
DECL|variable|borderaverage_data
decl|static
name|borderaverage_data
init|=
block|{
literal|3
block|,
literal|4
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|border_average_class_init (BorderAverageClass * klass)
name|border_average_class_init
parameter_list|(
name|BorderAverageClass
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
name|border_average_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|border_average_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|border_average_init (BorderAverage * film)
name|border_average_init
parameter_list|(
name|BorderAverage
modifier|*
name|film
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|border_average_query_procedures (GimpPlugIn * plug_in)
name|border_average_query_procedures
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
DECL|function|border_average_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|border_average_create_procedure
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
name|border_average_run
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
literal|"RGB*"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"_Border Average..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Colors/Info"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Set foreground to the average color of the image border"
argument_list|)
argument_list|,
literal|""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Philipp Klaus"
argument_list|,
literal|"Internet Access AG"
argument_list|,
literal|"1998"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"thickness"
argument_list|,
literal|"Border size to take in count"
argument_list|,
literal|"Border size to take in count"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
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
literal|"bucket-exponent"
argument_list|,
literal|"Bits for bucket size (default=4: 16 Levels)"
argument_list|,
literal|"Bits for bucket size (default=4: 16 Levels)"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|4
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_VAL_RGB
argument_list|(
name|procedure
argument_list|,
literal|"borderaverage"
argument_list|,
literal|"The average color of the specified border."
argument_list|,
literal|"The average color of the specified border."
argument_list|,
name|TRUE
argument_list|,
name|NULL
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
DECL|function|border_average_run (GimpProcedure * procedure,GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,const GimpValueArray * args,gpointer run_data)
name|border_average_run
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
name|GimpValueArray
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpRGB
name|result_color
init|=
block|{
literal|0.0
block|, }
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
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
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
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
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|borderaverage_data
argument_list|)
expr_stmt|;
name|borderaverage_thickness
operator|=
name|borderaverage_data
operator|.
name|thickness
expr_stmt|;
name|borderaverage_bucket_exponent
operator|=
name|borderaverage_data
operator|.
name|bucket_exponent
expr_stmt|;
if|if
condition|(
operator|!
name|borderaverage_dialog
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|)
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|gimp_value_array_length
argument_list|(
name|args
argument_list|)
operator|!=
literal|2
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
name|borderaverage_thickness
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|borderaverage_bucket_exponent
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
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
name|borderaverage_data
argument_list|)
expr_stmt|;
name|borderaverage_thickness
operator|=
name|borderaverage_data
operator|.
name|thickness
expr_stmt|;
name|borderaverage_bucket_exponent
operator|=
name|borderaverage_data
operator|.
name|bucket_exponent
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
comment|/*  Make sure that the drawable is RGB color  */
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Border Average"
argument_list|)
argument_list|)
expr_stmt|;
name|borderaverage
argument_list|(
name|buffer
argument_list|,
name|drawable
argument_list|,
operator|&
name|result_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|gimp_context_set_foreground
argument_list|(
operator|&
name|result_color
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|borderaverage_data
operator|.
name|thickness
operator|=
name|borderaverage_thickness
expr_stmt|;
name|borderaverage_data
operator|.
name|bucket_exponent
operator|=
name|borderaverage_bucket_exponent
expr_stmt|;
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|borderaverage_data
argument_list|,
sizeof|sizeof
argument_list|(
name|borderaverage_data
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|status
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|GIMP_VALUES_SET_RGB
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|,
operator|&
name|result_color
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|borderaverage (GeglBuffer * buffer,GimpDrawable * drawable,GimpRGB * result)
name|borderaverage
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRGB
modifier|*
name|result
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
name|gint
name|max
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|bucket_num
decl_stmt|,
name|bucket_expo
decl_stmt|,
name|bucket_rexpo
decl_stmt|;
name|gint
modifier|*
name|cube
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|GeglRectangle
name|border
index|[
literal|4
index|]
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
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
name|gimp_rgba_set_uchar
argument_list|(
name|result
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|255
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* allocate and clear the cube before */
name|bucket_expo
operator|=
name|borderaverage_bucket_exponent
expr_stmt|;
name|bucket_rexpo
operator|=
literal|8
operator|-
name|bucket_expo
expr_stmt|;
name|cube
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
literal|1
operator|<<
operator|(
name|bucket_rexpo
operator|*
literal|3
operator|)
argument_list|)
expr_stmt|;
name|bucket_num
operator|=
literal|1
operator|<<
name|bucket_rexpo
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bucket_num
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|bucket_num
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bucket_num
condition|;
name|k
operator|++
control|)
block|{
name|cube
index|[
operator|(
name|i
operator|<<
operator|(
name|bucket_rexpo
operator|<<
literal|1
operator|)
operator|)
operator|+
operator|(
name|j
operator|<<
name|bucket_rexpo
operator|)
operator|+
name|k
index|]
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
comment|/* Top */
name|border
index|[
literal|0
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|border
index|[
literal|0
index|]
operator|.
name|y
operator|=
name|y
expr_stmt|;
name|border
index|[
literal|0
index|]
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|border
index|[
literal|0
index|]
operator|.
name|height
operator|=
name|borderaverage_thickness
expr_stmt|;
comment|/* Bottom */
name|border
index|[
literal|1
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|border
index|[
literal|1
index|]
operator|.
name|y
operator|=
name|y
operator|+
name|height
operator|-
name|borderaverage_thickness
expr_stmt|;
name|border
index|[
literal|1
index|]
operator|.
name|width
operator|=
name|width
expr_stmt|;
name|border
index|[
literal|1
index|]
operator|.
name|height
operator|=
name|borderaverage_thickness
expr_stmt|;
comment|/* Left */
name|border
index|[
literal|2
index|]
operator|.
name|x
operator|=
name|x
expr_stmt|;
name|border
index|[
literal|2
index|]
operator|.
name|y
operator|=
name|y
operator|+
name|borderaverage_thickness
expr_stmt|;
name|border
index|[
literal|2
index|]
operator|.
name|width
operator|=
name|borderaverage_thickness
expr_stmt|;
name|border
index|[
literal|2
index|]
operator|.
name|height
operator|=
name|height
operator|-
literal|2
operator|*
name|borderaverage_thickness
expr_stmt|;
comment|/* Right */
name|border
index|[
literal|3
index|]
operator|.
name|x
operator|=
name|x
operator|+
name|width
operator|-
name|borderaverage_thickness
expr_stmt|;
name|border
index|[
literal|3
index|]
operator|.
name|y
operator|=
name|y
operator|+
name|borderaverage_thickness
expr_stmt|;
name|border
index|[
literal|3
index|]
operator|.
name|width
operator|=
name|borderaverage_thickness
expr_stmt|;
name|border
index|[
literal|3
index|]
operator|.
name|height
operator|=
name|height
operator|-
literal|2
operator|*
name|borderaverage_thickness
expr_stmt|;
comment|/* Fill the cube */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|border
index|[
name|i
index|]
operator|.
name|width
operator|>
literal|0
operator|&&
name|border
index|[
name|i
index|]
operator|.
name|height
operator|>
literal|0
condition|)
block|{
name|GeglBufferIterator
modifier|*
name|gi
decl_stmt|;
name|gi
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|buffer
argument_list|,
operator|&
name|border
index|[
name|i
index|]
argument_list|,
literal|0
argument_list|,
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
argument_list|,
name|GEGL_ACCESS_READWRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
while|while
condition|(
name|gegl_buffer_iterator_next
argument_list|(
name|gi
argument_list|)
condition|)
block|{
name|guint
name|k
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|data
operator|=
operator|(
name|guchar
operator|*
operator|)
name|gi
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|data
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|gi
operator|->
name|length
condition|;
name|k
operator|++
control|)
block|{
name|add_new_color
argument_list|(
name|data
operator|+
name|k
operator|*
literal|3
argument_list|,
name|cube
argument_list|,
name|bucket_expo
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
name|max
operator|=
literal|0
expr_stmt|;
name|r
operator|=
literal|0
expr_stmt|;
name|g
operator|=
literal|0
expr_stmt|;
name|b
operator|=
literal|0
expr_stmt|;
comment|/* get max of cube */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bucket_num
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|bucket_num
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bucket_num
condition|;
name|k
operator|++
control|)
block|{
if|if
condition|(
name|cube
index|[
operator|(
name|i
operator|<<
operator|(
name|bucket_rexpo
operator|<<
literal|1
operator|)
operator|)
operator|+
operator|(
name|j
operator|<<
name|bucket_rexpo
operator|)
operator|+
name|k
index|]
operator|>
name|max
condition|)
block|{
name|max
operator|=
name|cube
index|[
operator|(
name|i
operator|<<
operator|(
name|bucket_rexpo
operator|<<
literal|1
operator|)
operator|)
operator|+
operator|(
name|j
operator|<<
name|bucket_rexpo
operator|)
operator|+
name|k
index|]
expr_stmt|;
name|r
operator|=
operator|(
name|i
operator|<<
name|bucket_expo
operator|)
operator|+
operator|(
literal|1
operator|<<
operator|(
name|bucket_expo
operator|-
literal|1
operator|)
operator|)
expr_stmt|;
name|g
operator|=
operator|(
name|j
operator|<<
name|bucket_expo
operator|)
operator|+
operator|(
literal|1
operator|<<
operator|(
name|bucket_expo
operator|-
literal|1
operator|)
operator|)
expr_stmt|;
name|b
operator|=
operator|(
name|k
operator|<<
name|bucket_expo
operator|)
operator|+
operator|(
literal|1
operator|<<
operator|(
name|bucket_expo
operator|-
literal|1
operator|)
operator|)
expr_stmt|;
block|}
block|}
block|}
block|}
comment|/* return the color */
name|gimp_rgba_set_uchar
argument_list|(
name|result
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cube
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_new_color (const guchar * buffer,gint * cube,gint bucket_expo)
name|add_new_color
parameter_list|(
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
modifier|*
name|cube
parameter_list|,
name|gint
name|bucket_expo
parameter_list|)
block|{
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|bucket_rexpo
decl_stmt|;
name|bucket_rexpo
operator|=
literal|8
operator|-
name|bucket_expo
expr_stmt|;
name|r
operator|=
name|buffer
index|[
literal|0
index|]
operator|>>
name|bucket_expo
expr_stmt|;
name|g
operator|=
name|buffer
index|[
literal|1
index|]
operator|>>
name|bucket_expo
expr_stmt|;
name|b
operator|=
name|buffer
index|[
literal|2
index|]
operator|>>
name|bucket_expo
expr_stmt|;
name|cube
index|[
operator|(
name|r
operator|<<
operator|(
name|bucket_rexpo
operator|<<
literal|1
operator|)
operator|)
operator|+
operator|(
name|g
operator|<<
name|bucket_rexpo
operator|)
operator|+
name|b
index|]
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|borderaverage_dialog (GimpImage * image,GimpDrawable * drawable)
name|borderaverage_dialog
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|size_entry
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkSizeGroup
modifier|*
name|group
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|labels
index|[]
init|=
block|{
literal|"1"
block|,
literal|"2"
block|,
literal|"4"
block|,
literal|"8"
block|,
literal|"16"
block|,
literal|"32"
block|,
literal|"64"
block|,
literal|"128"
block|,
literal|"256"
block|}
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Border Average"
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
name|gimp_dialog_set_alternative_button_order
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
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Border Size"
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
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Thickness:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|group
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|group
argument_list|)
expr_stmt|;
comment|/*  Get the image resolution and unit  */
name|gimp_image_get_resolution
argument_list|(
name|image
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|size_entry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|unit
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|size_entry
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  set the size (in pixels) that will be treated as 0% and 100%  */
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|buffer
condition|)
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|,
name|MIN
argument_list|(
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1.0
argument_list|,
literal|256.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|(
name|gdouble
operator|)
name|borderaverage_thickness
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|size_entry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|thickness_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|size_entry
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Number of Colors"
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
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Bucket size:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|group
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_int_combo_box_new_array
argument_list|(
name|G_N_ELEMENTS
argument_list|(
name|labels
argument_list|)
argument_list|,
name|labels
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|borderaverage_bucket_exponent
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|borderaverage_bucket_exponent
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|combo
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

begin_function
specifier|static
name|void
DECL|function|thickness_callback (GtkWidget * widget,gpointer data)
name|thickness_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|borderaverage_thickness
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

