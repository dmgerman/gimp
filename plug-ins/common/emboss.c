begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/**************************************************  * file: emboss/emboss.c  *  * Copyright (c) 1997 Eric L. Hernes (erich@rrnet.com)  * All rights reserved.  *  * Redistribution and use in source and binary forms, with or without  * modification, are permitted provided that the following conditions  * are met:  * 1. Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer.  * 2. The name of the author may not be used to endorse or promote products  *    derived from this software withough specific prior written permission  *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  */
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
value|"plug-in-emboss"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"emboss"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-emboss"
end_define

begin_enum
enum|enum
DECL|enum|__anon2b8407cf0103
block|{
DECL|enumerator|FUNCTION_BUMPMAP
name|FUNCTION_BUMPMAP
init|=
literal|0
block|,
DECL|enumerator|FUNCTION_EMBOSS
name|FUNCTION_EMBOSS
init|=
literal|1
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b8407cf0208
block|{
DECL|member|azimuth
name|gdouble
name|azimuth
decl_stmt|;
DECL|member|elevation
name|gdouble
name|elevation
decl_stmt|;
DECL|member|depth
name|gint32
name|depth
decl_stmt|;
DECL|member|embossp
name|gint32
name|embossp
decl_stmt|;
DECL|typedef|piArgs
block|}
name|piArgs
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|evals
specifier|static
name|piArgs
name|evals
init|=
block|{
literal|30.0
block|,
comment|/* azimuth   */
literal|45.0
block|,
comment|/* elevation */
literal|20
block|,
comment|/* depth     */
literal|1
comment|/* emboss    */
block|}
decl_stmt|;
end_decl_stmt

begin_struct
DECL|struct|embossFilter
struct|struct
name|embossFilter
block|{
DECL|member|Lx
name|gdouble
name|Lx
decl_stmt|;
DECL|member|Ly
name|gdouble
name|Ly
decl_stmt|;
DECL|member|Lz
name|gdouble
name|Lz
decl_stmt|;
DECL|member|Nz
name|gdouble
name|Nz
decl_stmt|;
DECL|member|Nz2
name|gdouble
name|Nz2
decl_stmt|;
DECL|member|NzLz
name|gdouble
name|NzLz
decl_stmt|;
DECL|member|bg
name|gdouble
name|bg
decl_stmt|;
DECL|variable|Filter
block|}
decl|static
name|Filter
struct|;
end_struct

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
name|nparam
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nretvals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|retvals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|emboss
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
name|emboss_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|emboss_init
parameter_list|(
name|gdouble
name|azimuth
parameter_list|,
name|gdouble
name|elevation
parameter_list|,
name|gushort
name|width45
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|emboss_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|texture
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|guint
name|width
parameter_list|,
name|guint
name|bypp
parameter_list|,
name|gboolean
name|alpha
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|DtoR (d)
define|#
directive|define
name|DtoR
parameter_list|(
name|d
parameter_list|)
value|((d)*(G_PI/(gdouble)180))
end_define

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init  */
name|NULL
block|,
comment|/* quit  */
name|query
block|,
comment|/* query */
name|run
block|,
comment|/* run   */
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
literal|"The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"The Image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The Drawable"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"azimuth"
block|,
literal|"The Light Angle (degrees)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"elevation"
block|,
literal|"The Elevation Angle (degrees)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"depth"
block|,
literal|"The Filter Width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"emboss"
block|,
literal|"Emboss or Bumpmap"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Simulate an image created by embossing"
argument_list|)
argument_list|,
literal|"Emboss or Bumpmap the given drawable, specifying "
literal|"the angle and elevation for the light source."
argument_list|,
literal|"Eric L. Hernes, John Schlag"
argument_list|,
literal|"Eric L. Hernes"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Emboss (legacy)..."
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
literal|"<Image>/Filters/Distorts"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparam,const GimpParam * param,gint * nretvals,GimpParam ** retvals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparam
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nretvals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|retvals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|rvals
index|[
literal|1
index|]
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
operator|*
name|nretvals
operator|=
literal|1
expr_stmt|;
operator|*
name|retvals
operator|=
name|rvals
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
name|drawable
operator|->
name|ntile_cols
argument_list|)
expr_stmt|;
name|rvals
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|rvals
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
switch|switch
condition|(
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
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
name|evals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|emboss_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|rvals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
block|}
else|else
block|{
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|evals
argument_list|,
sizeof|sizeof
argument_list|(
name|piArgs
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparam
operator|!=
literal|7
condition|)
block|{
name|rvals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
name|evals
operator|.
name|azimuth
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
name|evals
operator|.
name|elevation
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
name|evals
operator|.
name|depth
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
name|evals
operator|.
name|embossp
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|emboss
argument_list|(
name|drawable
argument_list|,
name|NULL
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
name|evals
argument_list|)
expr_stmt|;
comment|/* use this image and drawable, even with last args */
name|emboss
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_define
DECL|macro|pixelScale
define|#
directive|define
name|pixelScale
value|255.9
end_define

begin_function
specifier|static
name|void
DECL|function|emboss_init (gdouble azimuth,gdouble elevation,gushort width45)
name|emboss_init
parameter_list|(
name|gdouble
name|azimuth
parameter_list|,
name|gdouble
name|elevation
parameter_list|,
name|gushort
name|width45
parameter_list|)
block|{
comment|/*    * compute the light vector from the input parameters.    * normalize the length to pixelScale for fast shading calculation.    */
name|Filter
operator|.
name|Lx
operator|=
name|cos
argument_list|(
name|azimuth
argument_list|)
operator|*
name|cos
argument_list|(
name|elevation
argument_list|)
operator|*
name|pixelScale
expr_stmt|;
name|Filter
operator|.
name|Ly
operator|=
name|sin
argument_list|(
name|azimuth
argument_list|)
operator|*
name|cos
argument_list|(
name|elevation
argument_list|)
operator|*
name|pixelScale
expr_stmt|;
name|Filter
operator|.
name|Lz
operator|=
name|sin
argument_list|(
name|elevation
argument_list|)
operator|*
name|pixelScale
expr_stmt|;
comment|/*    * constant z component of image surface normal - this depends on the    * image slope we wish to associate with an angle of 45 degrees, which    * depends on the width of the filter used to produce the source image.    */
name|Filter
operator|.
name|Nz
operator|=
operator|(
literal|6
operator|*
literal|255
operator|)
operator|/
name|width45
expr_stmt|;
name|Filter
operator|.
name|Nz2
operator|=
name|Filter
operator|.
name|Nz
operator|*
name|Filter
operator|.
name|Nz
expr_stmt|;
name|Filter
operator|.
name|NzLz
operator|=
name|Filter
operator|.
name|Nz
operator|*
name|Filter
operator|.
name|Lz
expr_stmt|;
comment|/* optimization for vertical normals: L.[0 0 1] */
name|Filter
operator|.
name|bg
operator|=
name|Filter
operator|.
name|Lz
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * ANSI C code from the article  * "Fast Embossing Effects on Raster Image Data"  * by John Schlag, jfs@kerner.com  * in "Graphics Gems IV", Academic Press, 1994  *  *  * Emboss - shade 24-bit pixels using a single distant light source.  * Normals are obtained by differentiating a monochrome 'bump' image.  * The unary case ('texture' == NULL) uses the shading result as output.  * The binary case multiples the optional 'texture' image by the shade.  * Images are in row major order with interleaved color components (rgbrgb...).  * E.g., component c of pixel x,y of 'dst' is dst[3*(y*width + x) + c].  *  */
end_comment

begin_function
specifier|static
name|void
DECL|function|emboss_row (const guchar * src,const guchar * texture,guchar * dst,guint width,guint bypp,gboolean alpha)
name|emboss_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
specifier|const
name|guchar
modifier|*
name|texture
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|guint
name|width
parameter_list|,
name|guint
name|bypp
parameter_list|,
name|gboolean
name|alpha
parameter_list|)
block|{
specifier|const
name|guchar
modifier|*
name|s
index|[
literal|3
index|]
decl_stmt|;
name|gdouble
name|M
index|[
literal|3
index|]
index|[
literal|3
index|]
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|bytes
decl_stmt|;
comment|/* mung pixels, avoiding edge pixels */
name|s
index|[
literal|0
index|]
operator|=
name|src
expr_stmt|;
name|s
index|[
literal|1
index|]
operator|=
name|s
index|[
literal|0
index|]
operator|+
operator|(
name|width
operator|*
name|bypp
operator|)
expr_stmt|;
name|s
index|[
literal|2
index|]
operator|=
name|s
index|[
literal|1
index|]
operator|+
operator|(
name|width
operator|*
name|bypp
operator|)
expr_stmt|;
name|dst
operator|+=
name|bypp
expr_stmt|;
name|bytes
operator|=
operator|(
name|alpha
operator|)
condition|?
name|bypp
operator|-
literal|1
else|:
name|bypp
expr_stmt|;
if|if
condition|(
name|texture
condition|)
name|texture
operator|+=
operator|(
name|width
operator|+
literal|1
operator|)
operator|*
name|bypp
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|1
init|;
name|x
operator|<
name|width
operator|-
literal|1
condition|;
name|x
operator|++
control|)
block|{
name|gdouble
name|a
decl_stmt|;
name|glong
name|Nx
decl_stmt|,
name|Ny
decl_stmt|,
name|NdotL
decl_stmt|;
name|gint
name|shade
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
name|M
index|[
name|i
index|]
index|[
name|j
index|]
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|alpha
condition|)
name|a
operator|=
name|s
index|[
name|i
index|]
index|[
name|j
operator|*
name|bypp
operator|+
name|bytes
index|]
operator|/
literal|255.0
expr_stmt|;
else|else
name|a
operator|=
literal|1.0
expr_stmt|;
name|M
index|[
name|i
index|]
index|[
name|j
index|]
operator|+=
name|a
operator|*
name|s
index|[
name|i
index|]
index|[
name|j
operator|*
name|bypp
operator|+
name|b
index|]
expr_stmt|;
block|}
block|}
name|Nx
operator|=
name|M
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|+
name|M
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|+
name|M
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|-
name|M
index|[
literal|0
index|]
index|[
literal|2
index|]
operator|-
name|M
index|[
literal|1
index|]
index|[
literal|2
index|]
operator|-
name|M
index|[
literal|2
index|]
index|[
literal|2
index|]
expr_stmt|;
name|Ny
operator|=
name|M
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|+
name|M
index|[
literal|2
index|]
index|[
literal|1
index|]
operator|+
name|M
index|[
literal|2
index|]
index|[
literal|2
index|]
operator|-
name|M
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|-
name|M
index|[
literal|0
index|]
index|[
literal|1
index|]
operator|-
name|M
index|[
literal|0
index|]
index|[
literal|2
index|]
expr_stmt|;
comment|/* shade with distant light source */
if|if
condition|(
name|Nx
operator|==
literal|0
operator|&&
name|Ny
operator|==
literal|0
condition|)
name|shade
operator|=
name|Filter
operator|.
name|bg
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|NdotL
operator|=
name|Nx
operator|*
name|Filter
operator|.
name|Lx
operator|+
name|Ny
operator|*
name|Filter
operator|.
name|Ly
operator|+
name|Filter
operator|.
name|NzLz
operator|)
operator|<
literal|0
condition|)
name|shade
operator|=
literal|0
expr_stmt|;
else|else
name|shade
operator|=
name|NdotL
operator|/
name|sqrt
argument_list|(
name|Nx
operator|*
name|Nx
operator|+
name|Ny
operator|*
name|Ny
operator|+
name|Filter
operator|.
name|Nz2
argument_list|)
expr_stmt|;
comment|/* do something with the shading result */
if|if
condition|(
name|texture
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
operator|*
name|dst
operator|++
operator|=
operator|(
operator|*
name|texture
operator|++
operator|*
name|shade
operator|)
operator|>>
literal|8
expr_stmt|;
if|if
condition|(
name|alpha
condition|)
block|{
operator|*
name|dst
operator|++
operator|=
name|s
index|[
literal|1
index|]
index|[
name|bypp
operator|+
name|bytes
index|]
expr_stmt|;
comment|/* preserve the alpha */
name|texture
operator|++
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
operator|*
name|dst
operator|++
operator|=
name|shade
expr_stmt|;
if|if
condition|(
name|alpha
condition|)
operator|*
name|dst
operator|++
operator|=
name|s
index|[
literal|1
index|]
index|[
name|bypp
operator|+
name|bytes
index|]
expr_stmt|;
comment|/* preserve the alpha */
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|3
condition|;
name|i
operator|++
control|)
name|s
index|[
name|i
index|]
operator|+=
name|bypp
expr_stmt|;
block|}
if|if
condition|(
name|texture
condition|)
name|texture
operator|+=
name|bypp
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|emboss (GimpDrawable * drawable,GimpPreview * preview)
name|emboss
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
name|GimpPixelRgn
name|src
decl_stmt|,
name|dst
decl_stmt|;
name|gint
name|p_update
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bypp
decl_stmt|,
name|rowsize
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|guchar
modifier|*
name|srcbuf
decl_stmt|,
modifier|*
name|dstbuf
decl_stmt|;
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
name|x2
operator|=
name|x1
operator|+
name|width
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|height
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable
operator|->
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
comment|/* expand the bounds a little */
name|x1
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|x1
operator|-
name|evals
operator|.
name|depth
argument_list|)
expr_stmt|;
name|y1
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|y1
operator|-
name|evals
operator|.
name|depth
argument_list|)
expr_stmt|;
name|x2
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
name|width
argument_list|,
name|x1
operator|+
name|width
operator|+
name|evals
operator|.
name|depth
argument_list|)
expr_stmt|;
name|y2
operator|=
name|MIN
argument_list|(
name|drawable
operator|->
name|height
argument_list|,
name|y1
operator|+
name|height
operator|+
name|evals
operator|.
name|depth
argument_list|)
expr_stmt|;
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
block|}
name|bypp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|p_update
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
name|height
operator|/
literal|20
argument_list|)
expr_stmt|;
name|rowsize
operator|=
name|width
operator|*
name|bypp
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dst
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|preview
operator|==
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|srcbuf
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|rowsize
operator|*
literal|3
argument_list|)
expr_stmt|;
name|dstbuf
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|rowsize
argument_list|)
expr_stmt|;
name|emboss_init
argument_list|(
name|DtoR
argument_list|(
name|evals
operator|.
name|azimuth
argument_list|)
argument_list|,
name|DtoR
argument_list|(
name|evals
operator|.
name|elevation
argument_list|)
argument_list|,
name|evals
operator|.
name|depth
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Emboss"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* first row */
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src
argument_list|,
name|srcbuf
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|srcbuf
argument_list|,
name|srcbuf
operator|+
name|rowsize
argument_list|,
name|rowsize
argument_list|)
expr_stmt|;
name|emboss_row
argument_list|(
name|srcbuf
argument_list|,
name|evals
operator|.
name|embossp
condition|?
name|NULL
else|:
name|srcbuf
argument_list|,
name|dstbuf
argument_list|,
name|width
argument_list|,
name|bypp
argument_list|,
name|has_alpha
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dst
argument_list|,
name|dstbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
comment|/* middle rows */
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
operator|-
literal|2
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|preview
operator|&&
operator|(
name|y
operator|%
name|p_update
operator|==
literal|0
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|y
operator|/
operator|(
name|gdouble
operator|)
name|height
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src
argument_list|,
name|srcbuf
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|y
argument_list|,
name|width
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|emboss_row
argument_list|(
name|srcbuf
argument_list|,
name|evals
operator|.
name|embossp
condition|?
name|NULL
else|:
name|srcbuf
argument_list|,
name|dstbuf
argument_list|,
name|width
argument_list|,
name|bypp
argument_list|,
name|has_alpha
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dst
argument_list|,
name|dstbuf
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|y
operator|+
literal|1
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
comment|/* last row */
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src
argument_list|,
name|srcbuf
argument_list|,
name|x1
argument_list|,
name|y2
operator|-
literal|3
argument_list|,
name|width
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|srcbuf
operator|+
name|rowsize
operator|*
literal|2
argument_list|,
name|srcbuf
operator|+
name|rowsize
argument_list|,
name|rowsize
argument_list|)
expr_stmt|;
name|emboss_row
argument_list|(
name|srcbuf
argument_list|,
name|evals
operator|.
name|embossp
condition|?
name|NULL
else|:
name|srcbuf
argument_list|,
name|dstbuf
argument_list|,
name|width
argument_list|,
name|bypp
argument_list|,
name|has_alpha
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dst
argument_list|,
name|dstbuf
argument_list|,
name|x1
argument_list|,
name|y2
operator|-
literal|1
argument_list|,
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_drawable_preview_draw_region
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|&
name|dst
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
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
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
name|g_free
argument_list|(
name|srcbuf
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dstbuf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|emboss_dialog (GimpDrawable * drawable)
name|emboss_dialog
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
name|radio1
decl_stmt|;
name|GtkWidget
modifier|*
name|radio2
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
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
literal|"Emboss"
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
name|preview
operator|=
name|gimp_drawable_preview_new_from_drawable_id
argument_list|(
name|drawable
operator|->
name|drawable_id
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
name|emboss
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Function"
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|evals
operator|.
name|embossp
argument_list|,
name|evals
operator|.
name|embossp
argument_list|,
name|_
argument_list|(
literal|"_Bumpmap"
argument_list|)
argument_list|,
name|FUNCTION_BUMPMAP
argument_list|,
operator|&
name|radio1
argument_list|,
name|_
argument_list|(
literal|"_Emboss"
argument_list|)
argument_list|,
name|FUNCTION_EMBOSS
argument_list|,
operator|&
name|radio2
argument_list|,
name|NULL
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
name|g_signal_connect_swapped
argument_list|(
name|radio1
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
name|g_signal_connect_swapped
argument_list|(
name|radio2
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
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
literal|"_Azimuth:"
argument_list|)
argument_list|,
literal|100
argument_list|,
literal|6
argument_list|,
name|evals
operator|.
name|azimuth
argument_list|,
literal|0.0
argument_list|,
literal|360.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|2
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
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|evals
operator|.
name|azimuth
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
literal|1
argument_list|,
name|_
argument_list|(
literal|"E_levation:"
argument_list|)
argument_list|,
literal|100
argument_list|,
literal|6
argument_list|,
name|evals
operator|.
name|elevation
argument_list|,
literal|0.0
argument_list|,
literal|180.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|2
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
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|evals
operator|.
name|elevation
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
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Depth:"
argument_list|)
argument_list|,
literal|100
argument_list|,
literal|6
argument_list|,
name|evals
operator|.
name|depth
argument_list|,
literal|1.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|5.0
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
name|evals
operator|.
name|depth
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
name|gtk_widget_show
argument_list|(
name|table
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
if|if
condition|(
name|run
condition|)
name|emboss
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

