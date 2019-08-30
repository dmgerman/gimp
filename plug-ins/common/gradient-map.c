begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gradient Map plug-in  * Copyright (C) 1997 Eiichi Takamori<taka@ma1.seikyou.ne.jp>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Some useful macros */
end_comment

begin_define
DECL|macro|GRADMAP_PROC
define|#
directive|define
name|GRADMAP_PROC
value|"plug-in-gradmap"
end_define

begin_define
DECL|macro|PALETTEMAP_PROC
define|#
directive|define
name|PALETTEMAP_PROC
value|"plug-in-palettemap"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"gradient-map"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-gradient-map"
end_define

begin_define
DECL|macro|NSAMPLES
define|#
directive|define
name|NSAMPLES
value|2048
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2beff5420103
block|{
DECL|enumerator|GRADIENT_MODE
name|GRADIENT_MODE
init|=
literal|1
block|,
DECL|enumerator|PALETTE_MODE
name|PALETTE_MODE
DECL|typedef|MapMode
block|}
name|MapMode
typedef|;
end_typedef

begin_typedef
DECL|typedef|Map
typedef|typedef
name|struct
name|_Map
name|Map
typedef|;
end_typedef

begin_typedef
DECL|typedef|MapClass
typedef|typedef
name|struct
name|_MapClass
name|MapClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Map
struct|struct
name|_Map
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_MapClass
struct|struct
name|_MapClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|MAP_TYPE
define|#
directive|define
name|MAP_TYPE
value|(map_get_type ())
end_define

begin_define
DECL|macro|MAP
define|#
directive|define
name|MAP
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MAP_TYPE, Map))
end_define

begin_decl_stmt
name|GType
name|map_get_type
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
name|map_query_procedures
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
name|map_create_procedure
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
name|map_run
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
name|map
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|shadow_buffer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|MapMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
modifier|*
name|get_samples_gradient
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
modifier|*
name|get_samples_palette
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (Map,map,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Map
argument_list|,
argument|map
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|MAP_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|map_class_init
parameter_list|(
name|MapClass
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
name|map_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|map_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|map_init (Map * map)
name|map_init
parameter_list|(
name|Map
modifier|*
name|map
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|map_query_procedures (GimpPlugIn * plug_in)
name|map_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|GRADMAP_PROC
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|PALETTEMAP_PROC
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|map_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|map_create_procedure
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
name|GRADMAP_PROC
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
name|GIMP_PLUGIN
argument_list|,
name|map_run
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GRADIENT_MODE
argument_list|)
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
literal|"_Gradient Map"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Colors/Map"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Recolor the image using colors "
literal|"from the active gradient"
argument_list|)
argument_list|,
literal|"This plug-in maps the contents of "
literal|"the specified drawable with active "
literal|"gradient. It calculates luminosity "
literal|"of each pixel and replaces the pixel "
literal|"by the sample of active gradient at "
literal|"the position proportional to that "
literal|"luminosity. Complete black pixel "
literal|"becomes the leftmost color of the "
literal|"gradient, and complete white becomes "
literal|"the rightmost. Works on both "
literal|"Grayscale and RGB image "
literal|"with/without alpha channel."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Eiichi Takamori"
argument_list|,
literal|"Eiichi Takamori"
argument_list|,
literal|"1997"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|PALETTEMAP_PROC
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
name|GIMP_PLUGIN
argument_list|,
name|map_run
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|PALETTE_MODE
argument_list|)
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
literal|"_Palette Map"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Colors/Map"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Recolor the image using colors "
literal|"from the active palette"
argument_list|)
argument_list|,
literal|"This plug-in maps the contents of "
literal|"the specified drawable with the "
literal|"active palette. It calculates "
literal|"luminosity of each pixel and "
literal|"replaces the pixel by the palette "
literal|"sample at the corresponding index. "
literal|"A complete black pixel becomes the "
literal|"lowest palette entry, and complete "
literal|"white becomes the highest. Works on "
literal|"both Grayscale and RGB image "
literal|"with/without alpha channel."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Bill Skaggs"
argument_list|,
literal|"Bill Skaggs"
argument_list|,
literal|"2004"
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
DECL|function|map_run (GimpProcedure * procedure,GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,const GimpValueArray * args,gpointer run_data)
name|map_run
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
name|MapMode
name|mode
init|=
name|GPOINTER_TO_INT
argument_list|(
name|run_data
argument_list|)
decl_stmt|;
name|GeglBuffer
modifier|*
name|shadow_buffer
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
name|shadow_buffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/*  Make sure that the drawable is gray or RGB color  */
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
if|if
condition|(
name|mode
operator|==
name|GRADIENT_MODE
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Gradient Map"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Palette Map"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|map
argument_list|(
name|buffer
argument_list|,
name|shadow_buffer
argument_list|,
name|drawable
argument_list|,
name|mode
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
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shadow_buffer
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
literal|0
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
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
DECL|function|map (GeglBuffer * buffer,GeglBuffer * shadow_buffer,GimpDrawable * drawable,MapMode mode)
name|map
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|shadow_buffer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|MapMode
name|mode
parameter_list|)
block|{
name|GeglBufferIterator
modifier|*
name|gi
decl_stmt|;
name|gint
name|nb_color_chan
decl_stmt|;
name|gint
name|nb_chan
decl_stmt|;
name|gint
name|nb_chan2
decl_stmt|;
name|gint
name|nb_chan_samp
decl_stmt|;
name|gint
name|index_iter
decl_stmt|;
name|gboolean
name|interpolate
decl_stmt|;
name|gdouble
modifier|*
name|samples
decl_stmt|;
name|gboolean
name|is_rgb
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format_shadow
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format_buffer
decl_stmt|;
name|is_rgb
operator|=
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|mode
condition|)
block|{
case|case
name|GRADIENT_MODE
case|:
name|samples
operator|=
name|get_samples_gradient
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|interpolate
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|PALETTE_MODE
case|:
name|samples
operator|=
name|get_samples_palette
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|interpolate
operator|=
name|FALSE
expr_stmt|;
break|break;
default|default:
name|g_error
argument_list|(
literal|"plug_in_gradmap: invalid mode"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|is_rgb
condition|)
block|{
name|nb_color_chan
operator|=
literal|3
expr_stmt|;
name|nb_chan_samp
operator|=
literal|4
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|format_shadow
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A float"
argument_list|)
expr_stmt|;
else|else
name|format_shadow
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' float"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|nb_color_chan
operator|=
literal|1
expr_stmt|;
name|nb_chan_samp
operator|=
literal|2
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|format_shadow
operator|=
name|babl_format
argument_list|(
literal|"Y'A float"
argument_list|)
expr_stmt|;
else|else
name|format_shadow
operator|=
name|babl_format
argument_list|(
literal|"Y' float"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|has_alpha
condition|)
block|{
name|nb_chan
operator|=
name|nb_color_chan
operator|+
literal|1
expr_stmt|;
name|nb_chan2
operator|=
literal|2
expr_stmt|;
name|format_buffer
operator|=
name|babl_format
argument_list|(
literal|"Y'A float"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|nb_chan
operator|=
name|nb_color_chan
expr_stmt|;
name|nb_chan2
operator|=
literal|1
expr_stmt|;
name|format_buffer
operator|=
name|babl_format
argument_list|(
literal|"Y' float"
argument_list|)
expr_stmt|;
block|}
name|gi
operator|=
name|gegl_buffer_iterator_new
argument_list|(
name|shadow_buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|format_shadow
argument_list|,
name|GEGL_ACCESS_WRITE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|index_iter
operator|=
name|gegl_buffer_iterator_add
argument_list|(
name|gi
argument_list|,
name|buffer
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|format_buffer
argument_list|,
name|GEGL_ACCESS_READ
argument_list|,
name|GEGL_ABYSS_NONE
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
name|gfloat
modifier|*
name|data
decl_stmt|;
name|gfloat
modifier|*
name|data2
decl_stmt|;
name|data
operator|=
operator|(
name|gfloat
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
name|data2
operator|=
operator|(
name|gfloat
operator|*
operator|)
name|gi
operator|->
name|items
index|[
name|index_iter
index|]
operator|.
name|data
expr_stmt|;
if|if
condition|(
name|interpolate
condition|)
block|{
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
name|gint
name|b
decl_stmt|,
name|ind1
decl_stmt|,
name|ind2
decl_stmt|;
name|gdouble
modifier|*
name|samp1
decl_stmt|,
modifier|*
name|samp2
decl_stmt|;
name|gfloat
name|c1
decl_stmt|,
name|c2
decl_stmt|,
name|val
decl_stmt|;
name|val
operator|=
name|data2
index|[
literal|0
index|]
operator|*
operator|(
name|NSAMPLES
operator|-
literal|1
operator|)
expr_stmt|;
name|ind1
operator|=
name|CLAMP
argument_list|(
name|floor
argument_list|(
name|val
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NSAMPLES
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ind2
operator|=
name|CLAMP
argument_list|(
name|ceil
argument_list|(
name|val
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NSAMPLES
operator|-
literal|1
argument_list|)
expr_stmt|;
name|c1
operator|=
literal|1.0
operator|-
operator|(
name|val
operator|-
name|ind1
operator|)
expr_stmt|;
name|c2
operator|=
literal|1.0
operator|-
name|c1
expr_stmt|;
name|samp1
operator|=
operator|&
operator|(
name|samples
index|[
name|ind1
operator|*
name|nb_chan_samp
index|]
operator|)
expr_stmt|;
name|samp2
operator|=
operator|&
operator|(
name|samples
index|[
name|ind2
operator|*
name|nb_chan_samp
index|]
operator|)
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|nb_color_chan
condition|;
name|b
operator|++
control|)
name|data
index|[
name|b
index|]
operator|=
operator|(
name|samp1
index|[
name|b
index|]
operator|*
name|c1
operator|+
name|samp2
index|[
name|b
index|]
operator|*
name|c2
operator|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
name|float
name|alpha
init|=
operator|(
name|samp1
index|[
name|b
index|]
operator|*
name|c1
operator|+
name|samp2
index|[
name|b
index|]
operator|*
name|c2
operator|)
decl_stmt|;
name|data
index|[
name|b
index|]
operator|=
name|alpha
operator|*
name|data2
index|[
literal|1
index|]
expr_stmt|;
block|}
name|data
operator|+=
name|nb_chan
expr_stmt|;
name|data2
operator|+=
name|nb_chan2
expr_stmt|;
block|}
block|}
else|else
block|{
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
name|gint
name|b
decl_stmt|,
name|ind
decl_stmt|;
name|gdouble
modifier|*
name|samp
decl_stmt|;
name|ind
operator|=
name|CLAMP
argument_list|(
name|data2
index|[
literal|0
index|]
operator|*
operator|(
name|NSAMPLES
operator|-
literal|1
operator|)
argument_list|,
literal|0
argument_list|,
name|NSAMPLES
operator|-
literal|1
argument_list|)
expr_stmt|;
name|samp
operator|=
operator|&
operator|(
name|samples
index|[
name|ind
operator|*
name|nb_chan_samp
index|]
operator|)
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|nb_color_chan
condition|;
name|b
operator|++
control|)
name|data
index|[
name|b
index|]
operator|=
name|samp
index|[
name|b
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
name|data
index|[
name|b
index|]
operator|=
name|samp
index|[
name|b
index|]
operator|*
name|data2
index|[
literal|1
index|]
expr_stmt|;
block|}
name|data
operator|+=
name|nb_chan
expr_stmt|;
name|data2
operator|+=
name|nb_chan2
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|samples
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*   Returns 2048 samples of the gradient.   Each sample is (R'G'B'A float) or (Y'A float), depending on the drawable  */
end_comment

begin_function
specifier|static
name|gdouble
modifier|*
DECL|function|get_samples_gradient (GimpDrawable * drawable)
name|get_samples_gradient
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
name|gint
name|n_d_samples
decl_stmt|;
name|gdouble
modifier|*
name|d_samples
init|=
name|NULL
decl_stmt|;
name|gradient_name
operator|=
name|gimp_context_get_gradient
argument_list|()
expr_stmt|;
comment|/* FIXME: "reverse" hardcoded to FALSE. */
name|gimp_gradient_get_uniform_samples
argument_list|(
name|gradient_name
argument_list|,
name|NSAMPLES
argument_list|,
name|FALSE
argument_list|,
operator|&
name|n_d_samples
argument_list|,
operator|&
name|d_samples
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gradient_name
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
specifier|const
name|Babl
modifier|*
name|format_src
init|=
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format_dst
init|=
name|babl_format
argument_list|(
literal|"Y'A double"
argument_list|)
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|fish
init|=
name|babl_fish
argument_list|(
name|format_src
argument_list|,
name|format_dst
argument_list|)
decl_stmt|;
name|babl_process
argument_list|(
name|fish
argument_list|,
name|d_samples
argument_list|,
name|d_samples
argument_list|,
name|NSAMPLES
argument_list|)
expr_stmt|;
block|}
return|return
name|d_samples
return|;
block|}
end_function

begin_comment
comment|/*   Returns 2048 samples of the palette.   Each sample is (R'G'B'A float) or (Y'A float), depending on the drawable  */
end_comment

begin_function
specifier|static
name|gdouble
modifier|*
DECL|function|get_samples_palette (GimpDrawable * drawable)
name|get_samples_palette
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gchar
modifier|*
name|palette_name
decl_stmt|;
name|GimpRGB
name|color_sample
decl_stmt|;
name|gdouble
modifier|*
name|d_samples
decl_stmt|,
modifier|*
name|d_samp
decl_stmt|;
name|gboolean
name|is_rgb
decl_stmt|;
name|gdouble
name|factor
decl_stmt|;
name|gint
name|pal_entry
decl_stmt|,
name|num_colors
decl_stmt|;
name|gint
name|nb_color_chan
decl_stmt|,
name|nb_chan
decl_stmt|,
name|i
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|palette_name
operator|=
name|gimp_context_get_palette
argument_list|()
expr_stmt|;
name|gimp_palette_get_info
argument_list|(
name|palette_name
argument_list|,
operator|&
name|num_colors
argument_list|)
expr_stmt|;
name|is_rgb
operator|=
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|factor
operator|=
operator|(
operator|(
name|double
operator|)
name|num_colors
operator|)
operator|/
name|NSAMPLES
expr_stmt|;
name|format
operator|=
name|is_rgb
condition|?
name|babl_format
argument_list|(
literal|"R'G'B'A double"
argument_list|)
else|:
name|babl_format
argument_list|(
literal|"Y'A double"
argument_list|)
expr_stmt|;
name|nb_color_chan
operator|=
name|is_rgb
condition|?
literal|3
else|:
literal|1
expr_stmt|;
name|nb_chan
operator|=
name|nb_color_chan
operator|+
literal|1
expr_stmt|;
name|d_samples
operator|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|NSAMPLES
operator|*
name|nb_chan
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
name|NSAMPLES
condition|;
name|i
operator|++
control|)
block|{
name|d_samp
operator|=
operator|&
name|d_samples
index|[
name|i
operator|*
name|nb_chan
index|]
expr_stmt|;
name|pal_entry
operator|=
name|CLAMP
argument_list|(
call|(
name|int
call|)
argument_list|(
name|i
operator|*
name|factor
argument_list|)
argument_list|,
literal|0
argument_list|,
name|num_colors
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_palette_entry_get_color
argument_list|(
name|palette_name
argument_list|,
name|pal_entry
argument_list|,
operator|&
name|color_sample
argument_list|)
expr_stmt|;
name|gimp_rgb_get_pixel
argument_list|(
operator|&
name|color_sample
argument_list|,
name|format
argument_list|,
name|d_samp
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|palette_name
argument_list|)
expr_stmt|;
return|return
name|d_samples
return|;
block|}
end_function

end_unit

