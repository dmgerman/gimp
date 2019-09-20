begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Destripe filter  *  * Copyright 1997 Marc Lehmann, heavily modified from a filter by  * Michael Sweet.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
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
value|"plug-in-destripe"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"destripe"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-destripe"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"0.2"
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|140
end_define

begin_define
DECL|macro|MAX_AVG
define|#
directive|define
name|MAX_AVG
value|100
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c5c94f30108
block|{
DECL|member|histogram
name|gboolean
name|histogram
decl_stmt|;
DECL|member|avg_width
name|gint
name|avg_width
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|DestripeValues
block|}
name|DestripeValues
typedef|;
end_typedef

begin_typedef
DECL|typedef|Destripe
typedef|typedef
name|struct
name|_Destripe
name|Destripe
typedef|;
end_typedef

begin_typedef
DECL|typedef|DestripeClass
typedef|typedef
name|struct
name|_DestripeClass
name|DestripeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Destripe
struct|struct
name|_Destripe
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_DestripeClass
struct|struct
name|_DestripeClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|DESTRIPE_TYPE
define|#
directive|define
name|DESTRIPE_TYPE
value|(destripe_get_type ())
end_define

begin_define
DECL|macro|DESTRIPE
define|#
directive|define
name|DESTRIPE
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), DESTRIPE_TYPE, Destripe))
end_define

begin_decl_stmt
name|GType
name|destripe_get_type
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
name|destripe_query_procedures
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
name|destripe_create_procedure
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
name|destripe_run
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
name|destripe
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|destripe_preview
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|destripe_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|Destripe
argument_list|,
argument|destripe
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|DESTRIPE_TYPE
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|DestripeValues
name|vals
init|=
block|{
name|FALSE
block|,
comment|/* histogram     */
literal|36
block|,
comment|/* average width */
name|TRUE
comment|/* preview */
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|destripe_class_init (DestripeClass * klass)
name|destripe_class_init
parameter_list|(
name|DestripeClass
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
name|destripe_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|destripe_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|destripe_init (Destripe * destripe)
name|destripe_init
parameter_list|(
name|Destripe
modifier|*
name|destripe
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|destripe_query_procedures (GimpPlugIn * plug_in)
name|destripe_query_procedures
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
DECL|function|destripe_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|destripe_create_procedure
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
name|destripe_run
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
literal|"RGB*, GRAY*"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Des_tripe..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Colors/Tone Mapping"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Remove vertical stripe artifacts "
literal|"from the image"
argument_list|)
argument_list|,
literal|"This plug-in tries to remove vertical "
literal|"stripes from an image."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Marc Lehmann<pcg@goof.com>"
argument_list|,
literal|"Marc Lehmann<pcg@goof.com>"
argument_list|,
name|PLUG_IN_VERSION
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"avg-width"
argument_list|,
literal|"Avg width"
argument_list|,
literal|"Averaging filter width"
argument_list|,
literal|2
argument_list|,
name|MAX_AVG
argument_list|,
literal|36
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
DECL|function|destripe_run (GimpProcedure * procedure,GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,const GimpValueArray * args,gpointer run_data)
name|destripe_run
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
name|vals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|destripe_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
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
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|vals
operator|.
name|avg_width
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|vals
argument_list|)
expr_stmt|;
break|break;
block|}
empty_stmt|;
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|destripe
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
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
name|vals
argument_list|,
sizeof|sizeof
argument_list|(
name|vals
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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

begin_function
specifier|static
name|void
DECL|function|destripe (GimpDrawable * drawable,GimpPreview * preview)
name|destripe
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|guchar
modifier|*
name|src_rows
decl_stmt|;
comment|/* image data */
name|gdouble
name|progress
decl_stmt|,
name|progress_inc
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|glong
modifier|*
name|hist
decl_stmt|,
modifier|*
name|corr
decl_stmt|;
comment|/* "histogram" data */
name|gint
name|tile_width
init|=
name|gimp_tile_width
argument_list|()
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|,
name|ox
decl_stmt|,
name|cols
decl_stmt|;
name|progress
operator|=
literal|0.0
expr_stmt|;
name|progress_inc
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_preview_get_size
argument_list|(
name|preview
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Destriping"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
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
return|return;
block|}
name|progress
operator|=
literal|0
expr_stmt|;
name|progress_inc
operator|=
literal|0.5
operator|*
name|tile_width
operator|/
name|width
expr_stmt|;
block|}
name|x2
operator|=
name|x1
operator|+
name|width
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
expr_stmt|;
else|else
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
expr_stmt|;
block|}
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
comment|/*    * Setup for filter...    */
name|src_buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|dest_buffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|hist
operator|=
name|g_new
argument_list|(
name|long
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|corr
operator|=
name|g_new
argument_list|(
name|long
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|src_rows
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|tile_width
operator|*
name|height
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|hist
argument_list|,
literal|0
argument_list|,
name|width
operator|*
name|bpp
operator|*
sizeof|sizeof
argument_list|(
name|long
argument_list|)
argument_list|)
expr_stmt|;
comment|/*    * collect "histogram" data.    */
for|for
control|(
name|ox
operator|=
name|x1
init|;
name|ox
operator|<
name|x2
condition|;
name|ox
operator|+=
name|tile_width
control|)
block|{
name|guchar
modifier|*
name|rows
init|=
name|src_rows
decl_stmt|;
name|cols
operator|=
name|x2
operator|-
name|ox
expr_stmt|;
if|if
condition|(
name|cols
operator|>
name|tile_width
condition|)
name|cols
operator|=
name|tile_width
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|src_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|ox
argument_list|,
name|y1
argument_list|,
name|cols
argument_list|,
name|height
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|rows
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|long
modifier|*
name|h
init|=
name|hist
operator|+
operator|(
name|ox
operator|-
name|x1
operator|)
operator|*
name|bpp
decl_stmt|;
name|guchar
modifier|*
name|row_end
init|=
name|rows
operator|+
name|cols
operator|*
name|bpp
decl_stmt|;
while|while
condition|(
name|rows
operator|<
name|row_end
condition|)
operator|*
name|h
operator|++
operator|+=
operator|*
name|rows
operator|++
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|preview
condition|)
name|gimp_progress_update
argument_list|(
name|progress
operator|+=
name|progress_inc
argument_list|)
expr_stmt|;
block|}
comment|/*    * average out histogram    */
block|{
name|gint
name|extend
init|=
operator|(
name|vals
operator|.
name|avg_width
operator|/
literal|2
operator|)
operator|*
name|bpp
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|MIN
argument_list|(
literal|3
argument_list|,
name|bpp
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|long
modifier|*
name|h
init|=
name|hist
operator|-
name|extend
operator|+
name|i
decl_stmt|;
name|long
modifier|*
name|c
init|=
name|corr
operator|-
name|extend
operator|+
name|i
decl_stmt|;
name|long
name|sum
init|=
literal|0
decl_stmt|;
name|gint
name|cnt
init|=
literal|0
decl_stmt|;
for|for
control|(
name|x
operator|=
operator|-
name|extend
init|;
name|x
operator|<
name|width
operator|*
name|bpp
condition|;
name|x
operator|+=
name|bpp
control|)
block|{
if|if
condition|(
name|x
operator|+
name|extend
operator|<
name|width
operator|*
name|bpp
condition|)
block|{
name|sum
operator|+=
name|h
index|[
name|extend
index|]
expr_stmt|;
name|cnt
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|-
name|extend
operator|>=
literal|0
condition|)
block|{
name|sum
operator|-=
name|h
index|[
operator|-
name|extend
index|]
expr_stmt|;
name|cnt
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
operator|*
name|h
condition|)
operator|*
name|c
operator|=
operator|(
operator|(
name|sum
operator|/
name|cnt
operator|-
operator|*
name|h
operator|)
operator|<<
literal|10
operator|)
operator|/
operator|*
name|h
expr_stmt|;
else|else
operator|*
name|c
operator|=
name|G_MAXINT
expr_stmt|;
block|}
name|h
operator|+=
name|bpp
expr_stmt|;
name|c
operator|+=
name|bpp
expr_stmt|;
block|}
block|}
block|}
comment|/*    * remove stripes.    */
for|for
control|(
name|ox
operator|=
name|x1
init|;
name|ox
operator|<
name|x2
condition|;
name|ox
operator|+=
name|tile_width
control|)
block|{
name|guchar
modifier|*
name|rows
init|=
name|src_rows
decl_stmt|;
name|cols
operator|=
name|x2
operator|-
name|ox
expr_stmt|;
if|if
condition|(
name|cols
operator|>
name|tile_width
condition|)
name|cols
operator|=
name|tile_width
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|src_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|ox
argument_list|,
name|y1
argument_list|,
name|cols
argument_list|,
name|height
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|rows
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
name|gimp_progress_update
argument_list|(
name|progress
operator|+=
name|progress_inc
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
name|long
modifier|*
name|c
init|=
name|corr
operator|+
operator|(
name|ox
operator|-
name|x1
operator|)
operator|*
name|bpp
decl_stmt|;
name|guchar
modifier|*
name|row_end
init|=
name|rows
operator|+
name|cols
operator|*
name|bpp
decl_stmt|;
if|if
condition|(
name|vals
operator|.
name|histogram
condition|)
block|{
while|while
condition|(
name|rows
operator|<
name|row_end
condition|)
block|{
operator|*
name|rows
operator|=
name|MIN
argument_list|(
literal|255
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
literal|128
operator|+
operator|(
operator|*
name|rows
operator|*
operator|*
name|c
operator|>>
literal|10
operator|)
argument_list|)
argument_list|)
expr_stmt|;
name|c
operator|++
expr_stmt|;
name|rows
operator|++
expr_stmt|;
block|}
block|}
else|else
block|{
while|while
condition|(
name|rows
operator|<
name|row_end
condition|)
block|{
operator|*
name|rows
operator|=
name|MIN
argument_list|(
literal|255
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
operator|*
name|rows
operator|+
operator|(
operator|*
name|rows
operator|*
operator|*
name|c
operator|>>
literal|10
operator|)
argument_list|)
argument_list|)
expr_stmt|;
name|c
operator|++
expr_stmt|;
name|rows
operator|++
expr_stmt|;
block|}
block|}
block|}
name|gegl_buffer_set
argument_list|(
name|dest_buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
name|ox
argument_list|,
name|y1
argument_list|,
name|cols
argument_list|,
name|height
argument_list|)
argument_list|,
literal|0
argument_list|,
name|format
argument_list|,
name|src_rows
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
name|gimp_progress_update
argument_list|(
name|progress
operator|+=
name|progress_inc
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src_rows
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|src_buffer
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
condition|)
block|{
name|guchar
modifier|*
name|buffer
init|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bpp
argument_list|)
decl_stmt|;
name|gegl_buffer_get
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
literal|1.0
argument_list|,
name|format
argument_list|,
name|buffer
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
name|gimp_preview_draw_buffer
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|buffer
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|dest_buffer
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
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
name|g_free
argument_list|(
name|hist
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|corr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|destripe_preview (GimpDrawable * drawable,GimpPreview * preview)
name|destripe_preview
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|destripe
argument_list|(
name|drawable
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|destripe_dialog (GimpDrawable * drawable)
name|destripe_dialog
parameter_list|(
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
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|grid
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Destripe"
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
name|preview
operator|=
name|gimp_drawable_preview_new_from_drawable
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
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
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|destripe_preview
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|grid
operator|=
name|gtk_grid_new
argument_list|()
expr_stmt|;
name|gtk_grid_set_column_spacing
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
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
name|grid
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
name|grid
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Width:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|vals
operator|.
name|avg_width
argument_list|,
literal|2
argument_list|,
name|MAX_AVG
argument_list|,
literal|1
argument_list|,
literal|10
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
name|vals
operator|.
name|avg_width
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Create _histogram"
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
name|vals
operator|.
name|histogram
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
name|vals
operator|.
name|histogram
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
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

