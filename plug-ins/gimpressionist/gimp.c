begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<math.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpressionist.h"
end_include

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
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
name|gimpressionist_main
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
name|char
modifier|*
parameter_list|,
name|int
parameter_list|,
name|GParam
modifier|*
parameter_list|,
name|int
modifier|*
parameter_list|,
name|GParam
modifier|*
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|repaint
parameter_list|(
name|struct
name|ppm
modifier|*
name|p
parameter_list|,
name|struct
name|ppm
modifier|*
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|create_gimpressionist
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|img_width
DECL|variable|img_height
DECL|variable|img_bpp
specifier|static
name|gint
name|img_width
decl_stmt|,
name|img_height
decl_stmt|,
name|img_bpp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|img_has_alpha
name|gint
name|img_has_alpha
init|=
literal|0
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
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
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
DECL|variable|pcvals
name|gimpressionist_vals_t
name|pcvals
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|defaultpcvals
name|gimpressionist_vals_t
name|defaultpcvals
init|=
block|{
literal|4
block|,
literal|0.0
block|,
literal|60.0
block|,
literal|0
block|,
literal|12.0
block|,
literal|20.0
block|,
literal|20.0
block|,
literal|1.0
block|,
literal|1
block|,
literal|0.1
block|,
literal|0.0
block|,
literal|30.0
block|,
literal|0
block|,
literal|0
block|,
literal|"defaultbrush.pgm"
block|,
literal|"defaultpaper.pgm"
block|,
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|,
literal|1
block|,
literal|0
block|,
block|{
block|{
literal|0.5
block|,
literal|0.5
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|0
block|}
block|}
block|,
literal|1
block|,
literal|0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|20.0
block|,
literal|1
block|,
literal|10.0
block|,
literal|20.0
block|,
literal|0
block|,
literal|0.1
block|,
block|{
block|{
literal|0.5
block|,
literal|0.5
block|,
literal|50.0
block|,
literal|1.0
block|}
block|}
block|,
literal|1
block|,
literal|1.0
block|,
literal|0
block|,
literal|10
block|,
literal|4
block|,
literal|0
block|,
literal|0.0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable
specifier|static
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
end_decl_stmt

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
literal|"Interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,   }
decl_stmt|;
comment|/* args */
specifier|static
name|GParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
specifier|static
name|int
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
name|PLUG_IN_NAME
argument_list|,
literal|"Performs various artistic operations on an image"
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
literal|"<Image>/Filters/Artistic/GIMPressionist..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nargs
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

begin_comment
comment|/* query */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimpressionist_get_data (char * name,void * ptr)
name|gimpressionist_get_data
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|void
modifier|*
name|ptr
parameter_list|)
block|{
name|memcpy
argument_list|(
operator|&
name|pcvals
argument_list|,
operator|&
name|defaultpcvals
argument_list|,
sizeof|sizeof
argument_list|(
name|pcvals
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_get_data
argument_list|(
name|name
argument_list|,
name|ptr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|GStatusType
name|status
decl_stmt|;
name|status
operator|=
name|STATUS_SUCCESS
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
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|PARAM_STATUS
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
comment|/* Get the active drawable info */
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
name|img_width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|img_height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|img_bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|img_has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|RUN_INTERACTIVE
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|gimpressionist_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pcvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|create_gimpressionist
argument_list|()
condition|)
return|return;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
name|INIT_I18N
argument_list|()
expr_stmt|;
name|g_message
argument_list|(
literal|"GIMPressionist: RUN_NONINTERACTIVE not implemented yet!\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|gimpressionist_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pcvals
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_message
argument_list|(
literal|"Huh?!\n"
argument_list|)
expr_stmt|;
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|(
name|status
operator|==
name|STATUS_SUCCESS
operator|)
operator|&&
operator|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|)
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
name|RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_NAME
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
elseif|else
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
name|status
operator|=
name|STATUS_EXECUTION_ERROR
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|grabarea (void)
name|void
name|grabarea
parameter_list|(
name|void
parameter_list|)
block|{
name|GPixelRgn
name|src_rgn
decl_stmt|;
name|guchar
modifier|*
name|src_row
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
name|gint
name|alpha
decl_stmt|,
name|has_alpha
decl_stmt|,
name|bpp
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|struct
name|ppm
modifier|*
name|p
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
name|row
decl_stmt|,
name|col
decl_stmt|;
name|int
name|rowstride
decl_stmt|;
if|if
condition|(
name|standalone
condition|)
block|{
name|loadppm
argument_list|(
name|standalone
argument_list|,
operator|&
name|infile
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|alpha
operator|=
operator|(
name|has_alpha
operator|)
condition|?
name|bpp
operator|-
literal|1
else|:
name|bpp
expr_stmt|;
name|newppm
argument_list|(
operator|&
name|infile
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
name|p
operator|=
operator|&
name|infile
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
name|newppm
argument_list|(
operator|&
name|inalpha
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
name|rowstride
operator|=
name|p
operator|->
name|width
operator|*
literal|3
expr_stmt|;
name|src_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|bpp
operator|==
literal|3
condition|)
block|{
comment|/* RGB */
name|int
name|bpr
init|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
literal|3
decl_stmt|;
for|for
control|(
name|row
operator|=
literal|0
operator|,
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|row
operator|++
operator|,
name|y
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src_row
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
argument_list|,
name|src_row
argument_list|,
name|bpr
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|bpp
operator|>
literal|3
condition|)
block|{
comment|/* RGBA */
for|for
control|(
name|row
operator|=
literal|0
operator|,
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|row
operator|++
operator|,
name|y
operator|++
control|)
block|{
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
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src_row
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|src
operator|=
name|src_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
operator|,
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
condition|;
name|col
operator|++
operator|,
name|x
operator|++
control|)
block|{
name|int
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
name|src
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
name|src
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
name|src
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
name|src
index|[
literal|3
index|]
expr_stmt|;
name|src
operator|+=
name|src_rgn
operator|.
name|bpp
expr_stmt|;
block|}
block|}
block|}
elseif|else
if|if
condition|(
name|bpp
operator|==
literal|2
condition|)
block|{
comment|/* GrayA */
for|for
control|(
name|row
operator|=
literal|0
operator|,
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|row
operator|++
operator|,
name|y
operator|++
control|)
block|{
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
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src_row
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|src
operator|=
name|src_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
operator|,
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
condition|;
name|col
operator|++
operator|,
name|x
operator|++
control|)
block|{
name|int
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
name|src
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
name|src
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
name|src
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
name|src
index|[
literal|1
index|]
expr_stmt|;
name|src
operator|+=
name|src_rgn
operator|.
name|bpp
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
comment|/* Gray */
for|for
control|(
name|row
operator|=
literal|0
operator|,
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|row
operator|++
operator|,
name|y
operator|++
control|)
block|{
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
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src_row
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|src
operator|=
name|src_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
operator|,
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
condition|;
name|col
operator|++
operator|,
name|x
operator|++
control|)
block|{
name|int
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
name|src
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
name|src
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
name|src
index|[
literal|0
index|]
expr_stmt|;
name|src
operator|+=
name|src_rgn
operator|.
name|bpp
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|src_row
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gimpressionist_main (void)
name|void
name|gimpressionist_main
parameter_list|(
name|void
parameter_list|)
block|{
name|GPixelRgn
name|dest_rgn
decl_stmt|;
name|guchar
modifier|*
name|dest_row
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|gint
name|alpha
decl_stmt|,
name|has_alpha
decl_stmt|,
name|bpp
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|struct
name|ppm
modifier|*
name|p
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
name|row
decl_stmt|,
name|col
decl_stmt|;
name|int
name|rowstride
decl_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|alpha
operator|=
operator|(
name|has_alpha
operator|)
condition|?
name|bpp
operator|-
literal|1
else|:
name|bpp
expr_stmt|;
name|dest_row
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Painting..."
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|infile
operator|.
name|col
condition|)
block|{
name|grabarea
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|img_has_alpha
condition|)
name|repaint
argument_list|(
operator|&
name|infile
argument_list|,
operator|&
name|inalpha
argument_list|)
expr_stmt|;
else|else
name|repaint
argument_list|(
operator|&
name|infile
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|,
name|TRUE
argument_list|,
name|TRUE
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
if|if
condition|(
name|bpp
operator|==
literal|3
condition|)
block|{
name|int
name|bpr
init|=
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
literal|3
decl_stmt|;
for|for
control|(
name|row
operator|=
literal|0
operator|,
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|row
operator|++
operator|,
name|y
operator|++
control|)
block|{
if|if
condition|(
name|row
operator|%
literal|10
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
literal|0.8
operator|+
literal|0.2
operator|*
operator|(
operator|(
name|double
operator|)
name|row
operator|/
operator|(
name|y2
operator|-
name|y1
operator|)
operator|)
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|dest_row
argument_list|,
name|p
operator|->
name|col
operator|+
name|row
operator|*
name|rowstride
argument_list|,
name|bpr
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|dest_row
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|bpp
operator|==
literal|4
condition|)
block|{
for|for
control|(
name|row
operator|=
literal|0
operator|,
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|row
operator|++
operator|,
name|y
operator|++
control|)
block|{
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
if|if
condition|(
name|row
operator|%
literal|10
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
literal|0.8
operator|+
literal|0.2
operator|*
operator|(
operator|(
name|double
operator|)
name|row
operator|/
operator|(
name|y2
operator|-
name|y1
operator|)
operator|)
argument_list|)
expr_stmt|;
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
operator|,
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
condition|;
name|col
operator|++
operator|,
name|x
operator|++
control|)
block|{
name|int
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
name|dest
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
name|dest
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
name|dest
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
name|dest
index|[
literal|3
index|]
operator|=
literal|255
operator|-
name|inalpha
operator|.
name|col
index|[
name|row
operator|*
name|rowstride
operator|+
name|k
index|]
expr_stmt|;
name|dest
operator|+=
name|dest_rgn
operator|.
name|bpp
expr_stmt|;
block|}
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|dest_row
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|bpp
operator|==
literal|2
condition|)
block|{
for|for
control|(
name|row
operator|=
literal|0
operator|,
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|row
operator|++
operator|,
name|y
operator|++
control|)
block|{
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
if|if
condition|(
name|row
operator|%
literal|10
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
literal|0.8
operator|+
literal|0.2
operator|*
operator|(
operator|(
name|double
operator|)
name|row
operator|/
operator|(
name|y2
operator|-
name|y1
operator|)
operator|)
argument_list|)
expr_stmt|;
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
operator|,
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
condition|;
name|col
operator|++
operator|,
name|x
operator|++
control|)
block|{
name|int
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
operator|(
name|tmprow
index|[
name|k
index|]
operator|+
name|tmprow
index|[
name|k
operator|+
literal|1
index|]
operator|+
name|tmprow
index|[
name|k
operator|+
literal|2
index|]
operator|)
operator|/
literal|3
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
literal|255
operator|-
name|inalpha
operator|.
name|col
index|[
name|row
operator|*
name|rowstride
operator|+
name|k
index|]
expr_stmt|;
name|dest
operator|+=
name|dest_rgn
operator|.
name|bpp
expr_stmt|;
block|}
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|dest_row
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|row
operator|=
literal|0
operator|,
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|row
operator|++
operator|,
name|y
operator|++
control|)
block|{
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
if|if
condition|(
name|row
operator|%
literal|10
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
literal|0.8
operator|+
literal|0.2
operator|*
operator|(
operator|(
name|double
operator|)
name|row
operator|/
operator|(
name|y2
operator|-
name|y1
operator|)
operator|)
argument_list|)
expr_stmt|;
name|dest
operator|=
name|dest_row
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
operator|,
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
condition|;
name|col
operator|++
operator|,
name|x
operator|++
control|)
block|{
name|int
name|k
init|=
name|col
operator|*
literal|3
decl_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
operator|(
name|tmprow
index|[
name|k
index|]
operator|+
name|tmprow
index|[
name|k
operator|+
literal|1
index|]
operator|+
name|tmprow
index|[
name|k
operator|+
literal|2
index|]
operator|)
operator|/
literal|3
expr_stmt|;
name|dest
operator|+=
name|dest_rgn
operator|.
name|bpp
expr_stmt|;
block|}
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|dest_row
argument_list|,
name|x1
argument_list|,
name|y
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|dest_row
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
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

