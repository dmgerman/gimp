begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/**************************************************  * file: emboss/emboss.c  *  * Copyright (c) 1997 Eric L. Hernes (erich@rrnet.com)  * All rights reserved.  *  * Redistribution and use in source and binary forms, with or without  * modification, are permitted provided that the following conditions  * are met:  * 1. Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer.  * 2. The name of the author may not be used to endorse or promote products  *    derived from this software withough specific prior written permission  *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *  * $Id$  */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<plug-ins/megawidget/megawidget.h>
end_include

begin_decl_stmt
DECL|variable|emboss_do_preview
specifier|static
name|mw_preview_t
name|emboss_do_preview
decl_stmt|;
end_decl_stmt

begin_struct
DECL|struct|Grgb
struct|struct
name|Grgb
block|{
DECL|member|red
name|guint8
name|red
decl_stmt|;
DECL|member|green
name|guint8
name|green
decl_stmt|;
DECL|member|blue
name|guint8
name|blue
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|GRegion
struct|struct
name|GRegion
block|{
DECL|member|x
name|gint32
name|x
decl_stmt|;
DECL|member|y
name|gint32
name|y
decl_stmt|;
DECL|member|width
name|gint32
name|width
decl_stmt|;
DECL|member|height
name|gint32
name|height
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|piArgs
struct|struct
name|piArgs
block|{
DECL|member|img
name|gint32
name|img
decl_stmt|;
DECL|member|drw
name|gint32
name|drw
decl_stmt|;
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
block|}
struct|;
end_struct

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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparam
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nretvals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|retvals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|pluginCore
parameter_list|(
name|struct
name|piArgs
modifier|*
name|argp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|pluginCoreIA
parameter_list|(
name|struct
name|piArgs
modifier|*
name|argp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|inline
name|void
name|EmbossInit
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
specifier|inline
name|void
name|EmbossRow
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|texture
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|guint
name|xSize
parameter_list|,
name|guint
name|bypp
parameter_list|,
name|gint
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
value|((d)*(M_PI/(gdouble)180))
end_define

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init */
name|NULL
block|,
comment|/* quit */
name|query
block|,
comment|/* query */
name|run
block|,
comment|/* run */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thePreview
specifier|static
name|struct
name|mwPreview
modifier|*
name|thePreview
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
name|GParamDef
name|args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"img"
block|,
literal|"The Image"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drw"
block|,
literal|"The Drawable"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"azimuth"
block|,
literal|"The Light Angle (degrees)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"elevation"
block|,
literal|"The Elevation Angle (degrees)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"depth"
block|,
literal|"The Filter Width"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"embossp"
block|,
literal|"Emboss or Bumpmap"
block|}
block|,   }
decl_stmt|;
specifier|static
name|gint
name|nargs
init|=
sizeof|sizeof
argument_list|(
name|args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|GParamDef
modifier|*
name|rets
init|=
name|NULL
decl_stmt|;
specifier|static
name|gint
name|nrets
init|=
literal|0
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_emboss"
argument_list|,
literal|"Emboss filter"
argument_list|,
literal|"Emboss or Bumpmap the given drawable, specifying the angle and elevation for the light source."
argument_list|,
literal|"Eric L. Hernes, John Schlag"
argument_list|,
literal|"Eric L. Hernes"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Image>/Filters/Distorts/Emboss"
argument_list|,
literal|"RGB"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nargs
argument_list|,
name|nrets
argument_list|,
name|args
argument_list|,
name|rets
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparam,GParam * param,gint * nretvals,GParam ** retvals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparam
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nretvals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|retvals
parameter_list|)
block|{
specifier|static
name|GParam
name|rvals
index|[
literal|1
index|]
decl_stmt|;
name|struct
name|piArgs
name|args
decl_stmt|;
name|GDrawable
modifier|*
name|drw
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
comment|/* bzero(&args, sizeof(struct piArgs)); */
name|memset
argument_list|(
operator|&
name|args
argument_list|,
operator|(
name|int
operator|)
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|piArgs
argument_list|)
argument_list|)
expr_stmt|;
name|rvals
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|PARAM_STATUS
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
name|STATUS_SUCCESS
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
name|RUN_INTERACTIVE
case|:
name|gimp_get_data
argument_list|(
literal|"plug_in_emboss"
argument_list|,
operator|&
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|args
operator|.
name|img
operator|==
literal|0
operator|&&
name|args
operator|.
name|drw
operator|==
literal|0
condition|)
block|{
comment|/* initial conditions */
name|args
operator|.
name|azimuth
operator|=
literal|30.0
expr_stmt|;
name|args
operator|.
name|elevation
operator|=
literal|45.0
expr_stmt|;
name|args
operator|.
name|depth
operator|=
literal|20
expr_stmt|;
name|args
operator|.
name|embossp
operator|=
literal|1
expr_stmt|;
block|}
name|args
operator|.
name|img
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
name|args
operator|.
name|drw
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
name|drw
operator|=
name|gimp_drawable_get
argument_list|(
name|args
operator|.
name|drw
argument_list|)
expr_stmt|;
name|thePreview
operator|=
name|mw_preview_build
argument_list|(
name|drw
argument_list|)
expr_stmt|;
if|if
condition|(
name|pluginCoreIA
argument_list|(
operator|&
name|args
argument_list|)
operator|==
operator|-
literal|1
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
block|{
name|gimp_set_data
argument_list|(
literal|"plug_in_emboss"
argument_list|,
operator|&
name|args
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|piArgs
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|RUN_NONINTERACTIVE
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
name|STATUS_CALLING_ERROR
expr_stmt|;
break|break;
block|}
name|args
operator|.
name|img
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
name|args
operator|.
name|drw
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
name|args
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
name|args
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
name|args
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
name|args
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
if|if
condition|(
name|pluginCore
argument_list|(
operator|&
name|args
argument_list|)
operator|==
operator|-
literal|1
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"plug_in_emboss"
argument_list|,
operator|&
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|pluginCore
argument_list|(
operator|&
name|args
argument_list|)
operator|==
operator|-
literal|1
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
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
name|void
DECL|function|EmbossInit (gdouble azimuth,gdouble elevation,gushort width45)
name|EmbossInit
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
comment|/*         * compute the light vector from the input parameters.         * normalize the length to pixelScale for fast shading calculation.         */
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
comment|/*         * constant z component of image surface normal - this depends on the         * image slope we wish to associate with an angle of 45 degrees, which         * depends on the width of the filter used to produce the source image.         */
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
comment|/*  * ANSI C code from the article  * "Fast Embossing Effects on Raster Image Data"  * by John Schlag, jfs@kerner.com  * in "Graphics Gems IV", Academic Press, 1994  *  *  * Emboss - shade 24-bit pixels using a single distant light source.  * Normals are obtained by differentiating a monochrome 'bump' image.  * The unary case ('texture' == NULL) uses the shading result as output.  * The binary case multiples the optional 'texture' image by the shade.  * Images are in row major order with interleaved color components (rgbrgb...).  * E.g., component c of pixel x,y of 'dst' is dst[3*(y*xSize + x) + c].  *  */
end_comment

begin_function
name|void
DECL|function|EmbossRow (guchar * src,guchar * texture,guchar * dst,guint xSize,guint bypp,gint alpha)
name|EmbossRow
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|texture
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|guint
name|xSize
parameter_list|,
name|guint
name|bypp
parameter_list|,
name|gint
name|alpha
parameter_list|)
block|{
name|glong
name|Nx
decl_stmt|,
name|Ny
decl_stmt|,
name|NdotL
decl_stmt|;
name|guchar
modifier|*
name|s1
decl_stmt|,
modifier|*
name|s2
decl_stmt|,
modifier|*
name|s3
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|shade
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
comment|/* mung pixels, avoiding edge pixels */
name|s1
operator|=
name|src
operator|+
name|bypp
expr_stmt|;
name|s2
operator|=
name|s1
operator|+
operator|(
name|xSize
operator|*
name|bypp
operator|)
expr_stmt|;
name|s3
operator|=
name|s2
operator|+
operator|(
name|xSize
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
name|xSize
operator|-
literal|1
condition|;
name|x
operator|++
operator|,
name|s1
operator|+=
name|bypp
operator|,
name|s2
operator|+=
name|bypp
operator|,
name|s3
operator|+=
name|bypp
control|)
block|{
comment|/*            * compute the normal from the src map. the type of the            * expression before the cast is compiler dependent. in            * some cases the sum is unsigned, in others it is            * signed. ergo, cast to signed.            */
name|Nx
operator|=
call|(
name|int
call|)
argument_list|(
name|s1
index|[
operator|-
name|bypp
index|]
operator|+
name|s2
index|[
operator|-
name|bypp
index|]
operator|+
name|s3
index|[
operator|-
name|bypp
index|]
operator|-
name|s1
index|[
name|bypp
index|]
operator|-
name|s2
index|[
name|bypp
index|]
operator|-
name|s3
index|[
name|bypp
index|]
argument_list|)
expr_stmt|;
name|Ny
operator|=
call|(
name|int
call|)
argument_list|(
name|s3
index|[
operator|-
name|bypp
index|]
operator|+
name|s3
index|[
literal|0
index|]
operator|+
name|s3
index|[
name|bypp
index|]
operator|-
name|s1
index|[
operator|-
name|bypp
index|]
operator|-
name|s1
index|[
literal|0
index|]
operator|-
name|s1
index|[
name|bypp
index|]
argument_list|)
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
block|{
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
block|}
if|if
condition|(
name|alpha
condition|)
block|{
operator|*
name|dst
operator|++
operator|=
name|s2
index|[
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
block|{
operator|*
name|dst
operator|++
operator|=
name|shade
expr_stmt|;
block|}
if|if
condition|(
name|alpha
condition|)
operator|*
name|dst
operator|++
operator|=
name|s2
index|[
name|bytes
index|]
expr_stmt|;
comment|/* preserve the alpha */
block|}
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
DECL|function|pluginCore (struct piArgs * argp)
name|int
name|pluginCore
parameter_list|(
name|struct
name|piArgs
modifier|*
name|argp
parameter_list|)
block|{
name|GDrawable
modifier|*
name|drw
decl_stmt|;
name|GPixelRgn
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
name|guint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bypp
decl_stmt|,
name|rowsize
decl_stmt|,
name|has_alpha
decl_stmt|;
name|guchar
modifier|*
name|srcbuf
decl_stmt|,
modifier|*
name|dstbuf
decl_stmt|;
name|drw
operator|=
name|gimp_drawable_get
argument_list|(
name|argp
operator|->
name|drw
argument_list|)
expr_stmt|;
name|width
operator|=
name|drw
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|drw
operator|->
name|height
expr_stmt|;
name|bypp
operator|=
name|drw
operator|->
name|bpp
expr_stmt|;
name|p_update
operator|=
name|height
operator|/
literal|20
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
name|argp
operator|->
name|drw
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src
argument_list|,
name|drw
argument_list|,
literal|0
argument_list|,
literal|0
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
name|drw
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|srcbuf
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
name|rowsize
operator|*
literal|3
argument_list|)
expr_stmt|;
name|dstbuf
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
name|rowsize
argument_list|)
expr_stmt|;
comment|/* bzero(srcbuf, rowsize*3); */
name|memset
argument_list|(
name|srcbuf
argument_list|,
operator|(
name|int
operator|)
literal|0
argument_list|,
call|(
name|size_t
call|)
argument_list|(
name|rowsize
operator|*
literal|3
argument_list|)
argument_list|)
expr_stmt|;
comment|/* bzero(dstbuf, rowsize); */
name|memset
argument_list|(
name|dstbuf
argument_list|,
operator|(
name|int
operator|)
literal|0
argument_list|,
operator|(
name|size_t
operator|)
name|rowsize
argument_list|)
expr_stmt|;
name|EmbossInit
argument_list|(
name|DtoR
argument_list|(
name|argp
operator|->
name|azimuth
argument_list|)
argument_list|,
name|DtoR
argument_list|(
name|argp
operator|->
name|elevation
argument_list|)
argument_list|,
name|argp
operator|->
name|depth
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
literal|"Emboss"
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
operator|(
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
comment|/* first row */
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src
argument_list|,
name|srcbuf
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|bcopy
argument_list|(
name|srcbuf
operator|+
name|rowsize
argument_list|,
name|srcbuf
argument_list|,
name|rowsize
argument_list|)
expr_stmt|;
name|EmbossRow
argument_list|(
name|srcbuf
argument_list|,
name|argp
operator|->
name|embossp
condition|?
operator|(
name|guchar
operator|*
operator|)
literal|0
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
comment|/* last row */
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src
argument_list|,
name|srcbuf
argument_list|,
literal|0
argument_list|,
name|height
operator|-
literal|3
argument_list|,
name|width
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|bcopy
argument_list|(
name|srcbuf
operator|+
name|rowsize
argument_list|,
name|srcbuf
operator|+
name|rowsize
operator|*
literal|2
argument_list|,
name|rowsize
argument_list|)
expr_stmt|;
name|EmbossRow
argument_list|(
name|srcbuf
argument_list|,
name|argp
operator|->
name|embossp
condition|?
operator|(
name|guchar
operator|*
operator|)
literal|0
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
name|height
operator|-
literal|1
argument_list|,
name|width
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
operator|-
literal|2
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
name|y
operator|%
name|p_update
operator|==
literal|0
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
literal|0
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|EmbossRow
argument_list|(
name|srcbuf
argument_list|,
name|argp
operator|->
name|embossp
condition|?
operator|(
name|guchar
operator|*
operator|)
literal|0
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
name|y
operator|+
literal|1
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
name|free
argument_list|(
name|srcbuf
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|dstbuf
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drw
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drw
operator|->
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drw
operator|->
name|id
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
DECL|function|pluginCoreIA (struct piArgs * argp)
name|int
name|pluginCoreIA
parameter_list|(
name|struct
name|piArgs
modifier|*
name|argp
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|gint
name|runp
decl_stmt|;
name|struct
name|mwRadioGroup
name|functions
index|[]
init|=
block|{
block|{
literal|"Emboss"
block|,
literal|0
block|}
block|,
block|{
literal|"Bumpmap"
block|,
literal|0
block|}
block|,
block|{
name|NULL
block|,
literal|0
block|}
block|,   }
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gint
name|argc
decl_stmt|;
comment|/* Set args */
name|argc
operator|=
literal|1
expr_stmt|;
name|argv
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|argv
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
literal|"emboss"
argument_list|)
expr_stmt|;
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
name|functions
index|[
operator|!
name|argp
operator|->
name|embossp
index|]
operator|.
name|var
operator|=
literal|1
expr_stmt|;
name|dlg
operator|=
name|mw_app_new
argument_list|(
literal|"plug_in_emboss"
argument_list|,
literal|"Emboss"
argument_list|,
operator|&
name|runp
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|mw_preview_new
argument_list|(
name|hbox
argument_list|,
name|thePreview
argument_list|,
operator|&
name|emboss_do_preview
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|"piArgs"
argument_list|,
name|argp
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|"mwRadioGroup"
argument_list|,
operator|&
name|functions
argument_list|)
expr_stmt|;
name|emboss_do_preview
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|mw_radio_group_new
argument_list|(
name|hbox
argument_list|,
literal|"Function"
argument_list|,
name|functions
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
literal|"Parameters"
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|4
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|mw_fscale_entry_new
argument_list|(
name|table
argument_list|,
literal|"Azimuth"
argument_list|,
literal|0.0
argument_list|,
literal|360.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
operator|&
name|argp
operator|->
name|azimuth
argument_list|)
expr_stmt|;
name|mw_fscale_entry_new
argument_list|(
name|table
argument_list|,
literal|"Elevation"
argument_list|,
literal|0.0
argument_list|,
literal|180.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
operator|&
name|argp
operator|->
name|elevation
argument_list|)
expr_stmt|;
name|mw_iscale_entry_new
argument_list|(
name|table
argument_list|,
literal|"Depth"
argument_list|,
literal|1
argument_list|,
literal|100
argument_list|,
literal|1
argument_list|,
literal|5
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
operator|&
name|argp
operator|->
name|depth
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
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
name|gdk_flush
argument_list|()
expr_stmt|;
name|argp
operator|->
name|embossp
operator|=
operator|!
name|mw_radio_result
argument_list|(
name|functions
argument_list|)
expr_stmt|;
if|if
condition|(
name|runp
condition|)
block|{
return|return
name|pluginCore
argument_list|(
name|argp
argument_list|)
return|;
block|}
else|else
block|{
return|return
operator|-
literal|1
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|emboss_do_preview (GtkWidget * w)
name|emboss_do_preview
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|)
block|{
specifier|static
name|GtkWidget
modifier|*
name|theWidget
init|=
name|NULL
decl_stmt|;
name|struct
name|piArgs
modifier|*
name|ap
decl_stmt|;
name|struct
name|mwRadioGroup
modifier|*
name|rgp
decl_stmt|;
name|guchar
modifier|*
name|dst
decl_stmt|,
modifier|*
name|c
decl_stmt|;
name|gint
name|y
decl_stmt|,
name|rowsize
decl_stmt|;
if|if
condition|(
name|theWidget
operator|==
name|NULL
condition|)
block|{
name|theWidget
operator|=
name|w
expr_stmt|;
block|}
name|ap
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|theWidget
argument_list|)
argument_list|,
literal|"piArgs"
argument_list|)
expr_stmt|;
name|rgp
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|theWidget
argument_list|)
argument_list|,
literal|"mwRadioGroup"
argument_list|)
expr_stmt|;
name|ap
operator|->
name|embossp
operator|=
operator|!
name|mw_radio_result
argument_list|(
name|rgp
argument_list|)
expr_stmt|;
name|rowsize
operator|=
name|thePreview
operator|->
name|width
operator|*
name|thePreview
operator|->
name|bpp
expr_stmt|;
name|dst
operator|=
name|malloc
argument_list|(
name|rowsize
argument_list|)
expr_stmt|;
name|c
operator|=
name|malloc
argument_list|(
name|rowsize
operator|*
literal|3
argument_list|)
expr_stmt|;
name|bcopy
argument_list|(
name|thePreview
operator|->
name|bits
argument_list|,
name|c
argument_list|,
name|rowsize
argument_list|)
expr_stmt|;
name|bcopy
argument_list|(
name|thePreview
operator|->
name|bits
argument_list|,
name|c
operator|+
name|rowsize
argument_list|,
name|rowsize
operator|*
literal|2
argument_list|)
expr_stmt|;
name|EmbossInit
argument_list|(
name|DtoR
argument_list|(
name|ap
operator|->
name|azimuth
argument_list|)
argument_list|,
name|DtoR
argument_list|(
name|ap
operator|->
name|elevation
argument_list|)
argument_list|,
name|ap
operator|->
name|depth
argument_list|)
expr_stmt|;
name|EmbossRow
argument_list|(
name|c
argument_list|,
name|ap
operator|->
name|embossp
condition|?
operator|(
name|guchar
operator|*
operator|)
literal|0
else|:
name|c
argument_list|,
name|dst
argument_list|,
name|thePreview
operator|->
name|width
argument_list|,
name|thePreview
operator|->
name|bpp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|theWidget
argument_list|)
argument_list|,
name|dst
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|thePreview
operator|->
name|width
argument_list|)
expr_stmt|;
name|bcopy
argument_list|(
name|thePreview
operator|->
name|bits
operator|+
operator|(
operator|(
name|thePreview
operator|->
name|height
operator|-
literal|2
operator|)
operator|*
name|rowsize
operator|)
argument_list|,
name|c
argument_list|,
name|rowsize
operator|*
literal|2
argument_list|)
expr_stmt|;
name|bcopy
argument_list|(
name|thePreview
operator|->
name|bits
operator|+
operator|(
operator|(
name|thePreview
operator|->
name|height
operator|-
literal|1
operator|)
operator|*
name|rowsize
operator|)
argument_list|,
name|c
operator|+
operator|(
name|rowsize
operator|*
literal|2
operator|)
argument_list|,
name|rowsize
argument_list|)
expr_stmt|;
name|EmbossRow
argument_list|(
name|c
argument_list|,
name|ap
operator|->
name|embossp
condition|?
operator|(
name|guchar
operator|*
operator|)
literal|0
else|:
name|c
argument_list|,
name|dst
argument_list|,
name|thePreview
operator|->
name|width
argument_list|,
name|thePreview
operator|->
name|bpp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|theWidget
argument_list|)
argument_list|,
name|dst
argument_list|,
literal|0
argument_list|,
name|thePreview
operator|->
name|height
operator|-
literal|1
argument_list|,
name|thePreview
operator|->
name|width
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|c
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|c
operator|=
name|thePreview
operator|->
name|bits
init|;
name|y
operator|<
name|thePreview
operator|->
name|height
operator|-
literal|2
condition|;
name|y
operator|++
operator|,
name|c
operator|+=
name|rowsize
control|)
block|{
name|EmbossRow
argument_list|(
name|c
argument_list|,
name|ap
operator|->
name|embossp
condition|?
operator|(
name|guchar
operator|*
operator|)
literal|0
else|:
name|c
argument_list|,
name|dst
argument_list|,
name|thePreview
operator|->
name|width
argument_list|,
name|thePreview
operator|->
name|bpp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|theWidget
argument_list|)
argument_list|,
name|dst
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|thePreview
operator|->
name|width
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_draw
argument_list|(
name|theWidget
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
name|free
argument_list|(
name|dst
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * Local Variables:  * mode: C  * c-indent-level: 2  *  * End:  */
end_comment

begin_comment
comment|/* end of file: emboss/emboss.c */
end_comment

end_unit

