begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_include
include|#
directive|include
file|"infile.h"
end_include

begin_include
include|#
directive|include
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"preview.h"
end_include

begin_include
include|#
directive|include
file|"brush.h"
end_include

begin_include
include|#
directive|include
file|"presets.h"
end_include

begin_include
include|#
directive|include
file|"random.h"
end_include

begin_include
include|#
directive|include
file|"orientmap.h"
end_include

begin_include
include|#
directive|include
file|"size.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

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
name|gimpressionist_main
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
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
comment|/* run_proc */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* PLUG_IN_INFO */
end_comment

begin_decl_stmt
DECL|variable|drawable_id
specifier|static
name|gint32
name|drawable_id
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|infile
specifier|static
name|ppm_t
name|infile
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|inalpha
specifier|static
name|ppm_t
name|inalpha
init|=
block|{
literal|0
block|,
literal|0
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|infile_copy_to_ppm (ppm_t * p)
name|infile_copy_to_ppm
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|)
block|{
if|if
condition|(
operator|!
name|PPM_IS_INITED
argument_list|(
operator|&
name|infile
argument_list|)
condition|)
name|grabarea
argument_list|()
expr_stmt|;
name|ppm_copy
argument_list|(
operator|&
name|infile
argument_list|,
name|p
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|infile_copy_alpha_to_ppm (ppm_t * p)
name|infile_copy_alpha_to_ppm
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|)
block|{
name|ppm_copy
argument_list|(
operator|&
name|inalpha
argument_list|,
name|p
argument_list|)
expr_stmt|;
block|}
end_function

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
literal|"The run mode { RUN-INTERACTIVE (0) }"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
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
name|GIMP_PDB_STRING
block|,
literal|"preset"
block|,
literal|"Preset Name"
block|}
block|,   }
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Performs various artistic operations"
argument_list|)
argument_list|,
literal|"Performs various artistic operations on an image"
argument_list|,
literal|"Vidar Madsen<vidar@prosalg.no>"
argument_list|,
literal|"Vidar Madsen"
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|N_
argument_list|(
literal|"_GIMPressionist..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
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
literal|"<Image>/Filters/Artistic"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimpressionist_get_data (void)
name|gimpressionist_get_data
parameter_list|(
name|void
parameter_list|)
block|{
name|restore_default_values
argument_list|()
expr_stmt|;
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|pcvals
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
literal|2
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|gboolean
name|with_specified_preset
decl_stmt|;
name|gchar
modifier|*
name|preset_name
init|=
name|NULL
decl_stmt|;
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
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
name|with_specified_preset
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|nparams
operator|>
literal|3
condition|)
block|{
name|preset_name
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|preset_name
argument_list|,
literal|""
argument_list|)
condition|)
block|{
name|with_specified_preset
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
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
comment|/* Get the active drawable info */
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
name|img_has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|random_generator
operator|=
name|g_rand_new
argument_list|()
expr_stmt|;
comment|/*    * Check precondition before we open a dialog: Is there a selection    * that intersects, OR is there no selection (use entire drawable.)    */
block|{
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
comment|/* Not used. */
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|_
argument_list|(
literal|"The selection does not intersect "
literal|"the active layer or mask."
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
switch|switch
condition|(
name|run_mode
condition|)
block|{
comment|/*          * Note: there's a limitation here. Running this plug-in before the          * interactive plug-in was run will cause it to crash, because the          * data is uninitialized.          * */
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimpressionist_get_data
argument_list|()
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
if|if
condition|(
operator|!
name|create_gimpressionist
argument_list|()
condition|)
return|return;
block|}
break|break;
default|default:
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|)
operator|&&
operator|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable_id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable_id
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|with_specified_preset
condition|)
block|{
comment|/* If select_preset fails - set to an error */
if|if
condition|(
name|select_preset
argument_list|(
name|preset_name
argument_list|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
comment|/* It seems that the value of the run variable is stored in        * the preset. I don't know if it's a bug or a feature, but        * I just work here and am anxious to get a working version.        * So I'm setting it to the correct value here.        *        * It also seems that defaultpcvals have this erroneous        * value as well, so it gets set to FALSE as well. Thus it        * is always set to TRUE upon a non-interactive run.        *        -- Shlomi Fish        * */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|pcvals
operator|.
name|run
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gimpressionist_main
argument_list|()
expr_stmt|;
name|gimp_displays_flush
argument_list|()
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
name|pcvals
argument_list|,
sizeof|sizeof
argument_list|(
name|gimpressionist_vals_t
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
comment|/* Resources Cleanup */
name|g_rand_free
argument_list|(
name|random_generator
argument_list|)
expr_stmt|;
name|free_parsepath_cache
argument_list|()
expr_stmt|;
name|brush_reload
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|preview_free_resources
argument_list|()
expr_stmt|;
name|brush_free
argument_list|()
expr_stmt|;
name|preset_free
argument_list|()
expr_stmt|;
name|orientation_map_free_resources
argument_list|()
expr_stmt|;
name|size_map_free_resources
argument_list|()
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
block|}
end_function

begin_function
specifier|static
specifier|const
name|Babl
modifier|*
DECL|function|get_u8_format (gint32 drawable_id)
name|get_u8_format
parameter_list|(
name|gint32
name|drawable_id
parameter_list|)
block|{
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable_id
argument_list|)
condition|)
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_id
argument_list|)
condition|)
return|return
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
return|;
else|else
return|return
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
return|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_id
argument_list|)
condition|)
return|return
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
return|;
else|else
return|return
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
return|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|grabarea (void)
name|grabarea
parameter_list|(
name|void
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|ppm_t
modifier|*
name|p
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
name|ppm_new
argument_list|(
operator|&
name|infile
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|p
operator|=
operator|&
name|infile
expr_stmt|;
name|format
operator|=
name|get_u8_format
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable_id
argument_list|)
condition|)
name|ppm_new
argument_list|(
operator|&
name|inalpha
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|rowstride
operator|=
name|p
operator|->
name|width
operator|*
literal|3
expr_stmt|;
name|src_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|src_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|GEGL_ACCESS_READ
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
name|iter
argument_list|)
condition|)
block|{
name|GeglRectangle
name|roi
init|=
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|roi
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|src
init|=
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|data
decl_stmt|;
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|row
operator|=
name|roi
operator|.
name|y
operator|-
name|y1
init|;
name|y
operator|<
name|roi
operator|.
name|height
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|tmprow
init|=
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|col
operator|=
name|roi
operator|.
name|x
operator|-
name|x1
init|;
name|x
operator|<
name|roi
operator|.
name|width
condition|;
name|x
operator|++
operator|,
name|col
operator|++
control|)
block|{
name|gint
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|0
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|1
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|2
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|s
operator|++
expr_stmt|;
block|}
name|src
operator|+=
name|bpp
operator|*
name|roi
operator|.
name|width
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|row
operator|=
name|roi
operator|.
name|y
operator|-
name|y1
init|;
name|y
operator|<
name|roi
operator|.
name|height
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|tmprow
init|=
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
name|guchar
modifier|*
name|tmparow
init|=
name|inalpha
operator|.
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|col
operator|=
name|roi
operator|.
name|x
operator|-
name|x1
init|;
name|x
operator|<
name|roi
operator|.
name|width
condition|;
name|x
operator|++
operator|,
name|col
operator|++
control|)
block|{
name|gint
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|0
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|1
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|2
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|tmparow
index|[
name|k
index|]
operator|=
literal|255
operator|-
name|s
index|[
literal|1
index|]
expr_stmt|;
name|s
operator|+=
literal|2
expr_stmt|;
block|}
name|src
operator|+=
name|bpp
operator|*
name|roi
operator|.
name|width
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
name|col
operator|=
name|roi
operator|.
name|x
operator|-
name|x1
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|row
operator|=
name|roi
operator|.
name|y
operator|-
name|y1
init|;
name|y
operator|<
name|roi
operator|.
name|height
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
operator|+
name|col
operator|*
literal|3
argument_list|,
name|src
argument_list|,
name|roi
operator|.
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|src
operator|+=
name|bpp
operator|*
name|roi
operator|.
name|width
expr_stmt|;
block|}
break|break;
case|case
literal|4
case|:
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|row
operator|=
name|roi
operator|.
name|y
operator|-
name|y1
init|;
name|y
operator|<
name|roi
operator|.
name|height
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
specifier|const
name|guchar
modifier|*
name|s
init|=
name|src
decl_stmt|;
name|guchar
modifier|*
name|tmprow
init|=
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
name|guchar
modifier|*
name|tmparow
init|=
name|inalpha
operator|.
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|col
operator|=
name|roi
operator|.
name|x
operator|-
name|x1
init|;
name|x
operator|<
name|roi
operator|.
name|width
condition|;
name|x
operator|++
operator|,
name|col
operator|++
control|)
block|{
name|gint
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|0
index|]
operator|=
name|s
index|[
literal|0
index|]
expr_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|1
index|]
operator|=
name|s
index|[
literal|1
index|]
expr_stmt|;
name|tmprow
index|[
name|k
operator|+
literal|2
index|]
operator|=
name|s
index|[
literal|2
index|]
expr_stmt|;
name|tmparow
index|[
name|k
index|]
operator|=
literal|255
operator|-
name|s
index|[
literal|3
index|]
expr_stmt|;
name|s
operator|+=
literal|4
expr_stmt|;
block|}
name|src
operator|+=
name|bpp
operator|*
name|roi
operator|.
name|width
expr_stmt|;
block|}
break|break;
block|}
block|}
name|g_object_unref
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimpressionist_main (void)
name|gimpressionist_main
parameter_list|(
name|void
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
name|GeglBufferIterator
modifier|*
name|iter
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|ppm_t
modifier|*
name|p
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|glong
name|done
init|=
literal|0
decl_stmt|;
name|glong
name|total
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
return|return;
name|total
operator|=
name|width
operator|*
name|height
expr_stmt|;
name|format
operator|=
name|get_u8_format
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Painting"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|PPM_IS_INITED
argument_list|(
operator|&
name|infile
argument_list|)
condition|)
name|grabarea
argument_list|()
expr_stmt|;
name|repaint
argument_list|(
operator|&
name|infile
argument_list|,
operator|(
name|img_has_alpha
operator|)
condition|?
operator|&
name|inalpha
else|:
name|NULL
argument_list|)
expr_stmt|;
name|p
operator|=
operator|&
name|infile
expr_stmt|;
name|rowstride
operator|=
name|p
operator|->
name|width
operator|*
literal|3
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|dest_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|GEGL_ACCESS_WRITE
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
name|iter
argument_list|)
condition|)
block|{
name|GeglRectangle
name|roi
init|=
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|roi
decl_stmt|;
name|guchar
modifier|*
name|dest
init|=
name|iter
operator|->
name|items
index|[
literal|0
index|]
operator|.
name|data
decl_stmt|;
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|row
operator|=
name|roi
operator|.
name|y
operator|-
name|y1
init|;
name|y
operator|<
name|roi
operator|.
name|height
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|tmprow
init|=
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|col
operator|=
name|roi
operator|.
name|x
operator|-
name|x1
init|;
name|x
operator|<
name|roi
operator|.
name|width
condition|;
name|x
operator|++
operator|,
name|col
operator|++
control|)
block|{
name|gint
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
operator|*
name|d
operator|++
operator|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|tmprow
index|[
name|k
operator|+
literal|0
index|]
argument_list|,
name|tmprow
index|[
name|k
operator|+
literal|1
index|]
argument_list|,
name|tmprow
index|[
name|k
operator|+
literal|2
index|]
argument_list|)
expr_stmt|;
block|}
name|dest
operator|+=
name|bpp
operator|*
name|roi
operator|.
name|width
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|row
operator|=
name|roi
operator|.
name|y
operator|-
name|y1
init|;
name|y
operator|<
name|roi
operator|.
name|height
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|tmprow
init|=
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|tmparow
init|=
name|inalpha
operator|.
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|col
operator|=
name|roi
operator|.
name|x
operator|-
name|x1
init|;
name|x
operator|<
name|roi
operator|.
name|width
condition|;
name|x
operator|++
operator|,
name|col
operator|++
control|)
block|{
name|gint
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
name|gint
name|value
init|=
name|GIMP_RGB_LUMINANCE
argument_list|(
name|tmprow
index|[
name|k
operator|+
literal|0
index|]
argument_list|,
name|tmprow
index|[
name|k
operator|+
literal|1
index|]
argument_list|,
name|tmprow
index|[
name|k
operator|+
literal|2
index|]
argument_list|)
decl_stmt|;
name|d
index|[
literal|0
index|]
operator|=
name|value
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
literal|255
operator|-
name|tmparow
index|[
name|k
index|]
expr_stmt|;
name|d
operator|+=
literal|2
expr_stmt|;
block|}
name|dest
operator|+=
name|bpp
operator|*
name|roi
operator|.
name|width
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
name|col
operator|=
name|roi
operator|.
name|x
operator|-
name|x1
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|row
operator|=
name|roi
operator|.
name|y
operator|-
name|y1
init|;
name|y
operator|<
name|roi
operator|.
name|height
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest
argument_list|,
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
operator|+
name|col
operator|*
literal|3
argument_list|,
name|roi
operator|.
name|width
operator|*
literal|3
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|bpp
operator|*
name|roi
operator|.
name|width
expr_stmt|;
block|}
break|break;
case|case
literal|4
case|:
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|row
operator|=
name|roi
operator|.
name|y
operator|-
name|y1
init|;
name|y
operator|<
name|roi
operator|.
name|height
condition|;
name|y
operator|++
operator|,
name|row
operator|++
control|)
block|{
name|guchar
modifier|*
name|d
init|=
name|dest
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|tmprow
init|=
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
specifier|const
name|guchar
modifier|*
name|tmparow
init|=
name|inalpha
operator|.
name|col
operator|+
name|row
operator|*
name|rowstride
decl_stmt|;
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|col
operator|=
name|roi
operator|.
name|x
operator|-
name|x1
init|;
name|x
operator|<
name|roi
operator|.
name|width
condition|;
name|x
operator|++
operator|,
name|col
operator|++
control|)
block|{
name|gint
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
name|d
index|[
literal|0
index|]
operator|=
name|tmprow
index|[
name|k
operator|+
literal|0
index|]
expr_stmt|;
name|d
index|[
literal|1
index|]
operator|=
name|tmprow
index|[
name|k
operator|+
literal|1
index|]
expr_stmt|;
name|d
index|[
literal|2
index|]
operator|=
name|tmprow
index|[
name|k
operator|+
literal|2
index|]
expr_stmt|;
name|d
index|[
literal|3
index|]
operator|=
literal|255
operator|-
name|tmparow
index|[
name|k
index|]
expr_stmt|;
name|d
operator|+=
literal|4
expr_stmt|;
block|}
name|dest
operator|+=
name|bpp
operator|*
name|roi
operator|.
name|width
expr_stmt|;
block|}
break|break;
block|}
name|done
operator|+=
name|roi
operator|.
name|width
operator|*
name|roi
operator|.
name|height
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|0.8
operator|+
literal|0.2
operator|*
name|done
operator|/
name|total
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

