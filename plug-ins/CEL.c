begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* cel.c -- KISS CEL file format plug-in for The GIMP  * (copyright) 1997 Nick Lamb (njl195@ecs.soton.ac.uk)  *  * Skeleton cloned from Michael Sweet's PNG plug-in. KISS format courtesy  * of the KISS/GS documentation. Problem reports to the above address  */
end_comment

begin_comment
comment|/* History:  * 0.1	Very limited functionality (modern 4bit only)  * 0.2  Default palette (nice yellows) is automatically used  * 0.3  Support for the older (pre KISS/GS) cell format  * 0.4  First support for saving images  * Future additions:  *  +   Automagically or via dialog box choose a KCF palette  *  +   Save (perhaps optionally?) the palette in a KCF  *  +   Support offsets -- like GIF?  */
end_comment

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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_define
DECL|macro|VERSION
define|#
directive|define
name|VERSION
value|"0.4"
end_define

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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint32
name|load_image
parameter_list|(
name|char
modifier|*
name|file
parameter_list|,
name|char
modifier|*
name|brief
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|save_image
parameter_list|(
name|char
modifier|*
name|file
parameter_list|,
name|char
modifier|*
name|brief
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint32
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Globals... */
end_comment

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
block|,
comment|/* run_proc */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Let GIMP library handle initialisation (and inquisitive users) */
end_comment

begin_function
DECL|function|main (int argc,char * argv[])
name|int
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
return|return
operator|(
name|gimp_main
argument_list|(
name|argc
argument_list|,
name|argv
argument_list|)
operator|)
return|;
block|}
end_function

begin_comment
comment|/* GIMP queries plug-in for parameters etc. */
end_comment

begin_function
DECL|function|query (void)
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GParamDef
name|load_args
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
name|PARAM_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to load"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|,   }
decl_stmt|;
specifier|static
name|int
name|nload_args
init|=
sizeof|sizeof
argument_list|(
name|load_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|load_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|int
name|nload_return_vals
init|=
sizeof|sizeof
argument_list|(
name|load_return_vals
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|load_return_vals
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|GParamDef
name|save_args
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
literal|"Drawable to save"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,   }
decl_stmt|;
specifier|static
name|int
name|nsave_args
init|=
sizeof|sizeof
argument_list|(
name|save_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|save_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_cel_load"
argument_list|,
literal|"Loads files in KISS CEL file format"
argument_list|,
literal|"This plug-in loads individual KISS cell files."
argument_list|,
literal|"Nick Lamb"
argument_list|,
literal|"Nick Lamb"
argument_list|,
name|VERSION
argument_list|,
literal|"<Load>/CEL"
argument_list|,
name|NULL
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nload_args
argument_list|,
name|nload_return_vals
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
literal|"file_cel_load"
argument_list|,
literal|"cel"
argument_list|,
literal|""
argument_list|,
literal|"0,string,KiSS"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_cel_save"
argument_list|,
literal|"Saves files in KISS CEL file format"
argument_list|,
literal|"This plug-in saves individual KISS cell files."
argument_list|,
literal|"Nick Lamb"
argument_list|,
literal|"Nick Lamb"
argument_list|,
name|VERSION
argument_list|,
literal|"<Save>/CEL"
argument_list|,
literal|"INDEXED*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nsave_args
argument_list|,
literal|0
argument_list|,
name|save_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
literal|"file_cel_save"
argument_list|,
literal|"cel"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
specifier|static
name|void
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
name|gint32
name|image
decl_stmt|;
comment|/* image ID after load */
name|gint
name|status
decl_stmt|;
comment|/* status after save */
specifier|static
name|GParam
name|values
index|[
literal|2
index|]
decl_stmt|;
comment|/* Return values */
comment|/* Set up default return values */
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
name|STATUS_SUCCESS
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
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_cel_load"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|image
operator|=
name|load_image
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|!=
operator|-
literal|1
condition|)
block|{
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
name|PARAM_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image
expr_stmt|;
block|}
else|else
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_cel_save"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|save_image
argument_list|(
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|,
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
block|}
else|else
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* Load CEL image into The GIMP */
end_comment

begin_function
DECL|function|load_image (char * file,char * brief)
specifier|static
name|gint32
name|load_image
parameter_list|(
name|char
modifier|*
name|file
parameter_list|,
name|char
modifier|*
name|brief
parameter_list|)
block|{
name|FILE
modifier|*
name|fp
decl_stmt|;
comment|/* Read file pointer */
name|char
name|progress
index|[
literal|255
index|]
decl_stmt|;
comment|/* Title for progress display */
name|guchar
name|header
index|[
literal|32
index|]
decl_stmt|;
comment|/* File header */
name|int
name|height
decl_stmt|,
name|width
decl_stmt|,
comment|/* Dimensions of image */
name|colours
decl_stmt|;
comment|/* Number of colours */
name|gint32
name|image
decl_stmt|,
comment|/* Image */
name|layer
decl_stmt|;
comment|/* Layer */
name|guchar
modifier|*
name|palette
decl_stmt|,
comment|/* 24 bit palette */
modifier|*
name|buffer
decl_stmt|,
comment|/* Temporary buffer */
modifier|*
name|line
decl_stmt|;
comment|/* Pixel data */
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* Drawable for layer */
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
comment|/* Pixel region for layer */
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
comment|/* Counters */
comment|/* Open the file for reading */
name|fp
operator|=
name|fopen
argument_list|(
name|file
argument_list|,
literal|"r"
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|progress
argument_list|,
literal|"Loading %s:"
argument_list|,
name|brief
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|progress
argument_list|)
expr_stmt|;
comment|/* Get the image dimensions and create the image... */
name|fread
argument_list|(
name|header
argument_list|,
literal|4
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
name|header
argument_list|,
literal|"KiSS"
argument_list|,
literal|4
argument_list|)
condition|)
block|{
name|colours
operator|=
literal|16
expr_stmt|;
name|width
operator|=
name|header
index|[
literal|0
index|]
operator|+
operator|(
literal|256
operator|*
name|header
index|[
literal|1
index|]
operator|)
expr_stmt|;
name|height
operator|=
name|header
index|[
literal|2
index|]
operator|+
operator|(
literal|256
operator|*
name|header
index|[
literal|3
index|]
operator|)
expr_stmt|;
block|}
else|else
block|{
name|fread
argument_list|(
name|header
argument_list|,
literal|28
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
name|colours
operator|=
operator|(
literal|1
operator|<<
name|header
index|[
literal|1
index|]
operator|)
expr_stmt|;
name|width
operator|=
name|header
index|[
literal|4
index|]
operator|+
operator|(
literal|256
operator|*
name|header
index|[
literal|5
index|]
operator|)
expr_stmt|;
name|height
operator|=
name|header
index|[
literal|6
index|]
operator|+
operator|(
literal|256
operator|*
name|header
index|[
literal|7
index|]
operator|)
expr_stmt|;
block|}
name|image
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|INDEXED
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|==
operator|-
literal|1
condition|)
block|{
name|g_print
argument_list|(
literal|"Can't allocate new image\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
name|gimp_image_set_filename
argument_list|(
name|image
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|palette
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|colours
operator|*
literal|3
argument_list|)
expr_stmt|;
comment|/* FIXME Default palette -- hopefully nasty enough to encourage a fix */
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|colours
condition|;
operator|++
name|i
control|)
name|palette
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
name|palette
index|[
name|i
operator|*
literal|3
index|]
operator|=
name|i
operator|*
literal|256
operator|/
name|colours
expr_stmt|;
name|gimp_image_set_cmap
argument_list|(
name|image
argument_list|,
name|palette
argument_list|,
name|colours
argument_list|)
expr_stmt|;
comment|/* Create an indexed-alpha layer to hold the image... */
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
literal|"Background"
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|INDEXEDA_IMAGE
argument_list|,
literal|100
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Get the drawable and set the pixel region for our load... */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Read the image in and give it to the GIMP a line at a time */
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|line
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|width
operator|+
literal|1
operator|)
operator|*
literal|2
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
name|height
condition|;
operator|++
name|i
control|)
block|{
switch|switch
condition|(
name|colours
condition|)
block|{
case|case
literal|16
case|:
name|fread
argument_list|(
name|buffer
argument_list|,
operator|(
name|width
operator|+
literal|1
operator|)
operator|/
literal|2
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|j
operator|<
name|width
operator|*
literal|2
condition|;
name|j
operator|+=
literal|4
operator|,
operator|++
name|k
control|)
block|{
name|line
index|[
name|j
index|]
operator|=
name|buffer
index|[
name|k
index|]
operator|/
literal|16
expr_stmt|;
name|line
index|[
name|j
operator|+
literal|1
index|]
operator|=
name|line
index|[
name|j
index|]
condition|?
literal|255
else|:
literal|0
expr_stmt|;
name|line
index|[
name|j
operator|+
literal|2
index|]
operator|=
name|buffer
index|[
name|k
index|]
operator|&
literal|15
expr_stmt|;
name|line
index|[
name|j
operator|+
literal|3
index|]
operator|=
name|line
index|[
name|j
operator|+
literal|2
index|]
condition|?
literal|255
else|:
literal|0
expr_stmt|;
block|}
break|break;
case|case
literal|256
case|:
name|fread
argument_list|(
name|buffer
argument_list|,
name|width
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|j
operator|<
name|width
operator|*
literal|2
condition|;
name|j
operator|+=
literal|2
operator|,
operator|++
name|k
control|)
block|{
name|line
index|[
name|j
index|]
operator|=
name|buffer
index|[
name|k
index|]
expr_stmt|;
name|line
index|[
name|j
operator|+
literal|1
index|]
operator|=
name|line
index|[
name|j
index|]
condition|?
literal|255
else|:
literal|0
expr_stmt|;
block|}
break|break;
block|}
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|line
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|i
operator|/
operator|(
name|float
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
comment|/* Close files, give back allocated memory */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|line
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|palette
argument_list|)
expr_stmt|;
comment|/* Now get everything redrawn and hand back the finished image */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
operator|(
name|image
operator|)
return|;
block|}
end_function

begin_function
DECL|function|save_image (char * file,char * brief,gint32 image,gint32 layer)
specifier|static
name|gint
name|save_image
parameter_list|(
name|char
modifier|*
name|file
parameter_list|,
name|char
modifier|*
name|brief
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint32
name|layer
parameter_list|)
block|{
name|FILE
modifier|*
name|fp
decl_stmt|;
comment|/* Write file pointer */
name|char
name|progress
index|[
literal|255
index|]
decl_stmt|;
comment|/* Title for progress display */
name|guchar
name|header
index|[
literal|32
index|]
decl_stmt|;
comment|/* File header */
name|gint
name|colours
decl_stmt|,
name|type
decl_stmt|;
comment|/* Number of colours, type of layer */
name|guchar
modifier|*
name|palette
decl_stmt|,
comment|/* 24 bit palette */
modifier|*
name|buffer
decl_stmt|,
comment|/* Temporary buffer */
modifier|*
name|line
decl_stmt|;
comment|/* Pixel data */
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* Drawable for layer */
name|GPixelRgn
name|pixel_rgn
decl_stmt|;
comment|/* Pixel region for layer */
name|int
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
comment|/* Counters */
comment|/* Check that this is an indexed image, fail otherwise */
name|type
operator|=
name|gimp_drawable_type
argument_list|(
name|layer
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|!=
name|INDEXED_IMAGE
operator|&&
name|type
operator|!=
name|INDEXEDA_IMAGE
condition|)
block|{
name|g_print
argument_list|(
literal|"GIMP tried to save a non-indexed image as CEL.\n"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layer
argument_list|)
expr_stmt|;
comment|/* Open the file for writing */
name|fp
operator|=
name|fopen
argument_list|(
name|file
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
name|sprintf
argument_list|(
name|progress
argument_list|,
literal|"Saving %s:"
argument_list|,
name|brief
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|progress
argument_list|)
expr_stmt|;
comment|/* Headers */
name|bzero
argument_list|(
name|header
argument_list|,
literal|32
argument_list|)
expr_stmt|;
name|strcpy
argument_list|(
name|header
argument_list|,
literal|"KiSS"
argument_list|)
expr_stmt|;
name|header
index|[
literal|4
index|]
operator|=
literal|0x20
expr_stmt|;
comment|/* Work out whether to save as 8bit or 4bit */
name|gimp_image_get_cmap
argument_list|(
name|image
argument_list|,
operator|&
name|colours
argument_list|)
expr_stmt|;
if|if
condition|(
name|colours
operator|>
literal|16
condition|)
block|{
name|header
index|[
literal|5
index|]
operator|=
literal|8
expr_stmt|;
block|}
else|else
block|{
name|header
index|[
literal|5
index|]
operator|=
literal|4
expr_stmt|;
block|}
comment|/* Fill in the blanks ... */
name|header
index|[
literal|8
index|]
operator|=
name|drawable
operator|->
name|width
operator|%
literal|256
expr_stmt|;
name|header
index|[
literal|9
index|]
operator|=
name|drawable
operator|->
name|width
operator|/
literal|256
expr_stmt|;
name|header
index|[
literal|10
index|]
operator|=
name|drawable
operator|->
name|height
operator|%
literal|256
expr_stmt|;
name|header
index|[
literal|11
index|]
operator|=
name|drawable
operator|->
name|height
operator|/
literal|256
expr_stmt|;
name|fwrite
argument_list|(
name|header
argument_list|,
literal|32
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
comment|/* Arrange for memory etc. */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
name|drawable
operator|->
name|height
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
name|line
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|drawable
operator|->
name|width
operator|+
literal|1
operator|)
operator|*
literal|2
argument_list|)
expr_stmt|;
comment|/* Get the image from the GIMP one line at a time and write it out */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|drawable
operator|->
name|height
condition|;
operator|++
name|i
control|)
block|{
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|line
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
literal|1
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|colours
condition|)
block|{
case|case
literal|16
case|:
for|for
control|(
name|j
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|j
operator|<
name|drawable
operator|->
name|width
operator|*
literal|2
condition|;
name|j
operator|+=
literal|4
operator|,
operator|++
name|k
control|)
block|{
name|buffer
index|[
name|k
index|]
operator|=
literal|16
operator|*
operator|(
name|line
index|[
name|j
operator|+
literal|1
index|]
condition|?
name|line
index|[
name|j
index|]
else|:
literal|0
operator|)
operator|+
operator|(
name|line
index|[
name|j
operator|+
literal|3
index|]
condition|?
name|line
index|[
name|j
operator|+
literal|2
index|]
else|:
literal|0
operator|)
expr_stmt|;
block|}
name|fwrite
argument_list|(
name|buffer
argument_list|,
operator|(
name|drawable
operator|->
name|width
operator|+
literal|1
operator|)
operator|/
literal|2
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
break|break;
case|case
literal|256
case|:
for|for
control|(
name|j
operator|=
literal|0
operator|,
name|k
operator|=
literal|0
init|;
name|j
operator|<
name|drawable
operator|->
name|width
operator|*
literal|2
condition|;
name|j
operator|+=
literal|2
operator|,
operator|++
name|k
control|)
block|{
name|buffer
index|[
name|k
index|]
operator|=
name|line
index|[
name|j
operator|+
literal|1
index|]
condition|?
name|line
index|[
name|j
index|]
else|:
literal|0
expr_stmt|;
block|}
name|fwrite
argument_list|(
name|buffer
argument_list|,
name|drawable
operator|->
name|width
argument_list|,
literal|1
argument_list|,
name|fp
argument_list|)
expr_stmt|;
break|break;
block|}
name|gimp_progress_update
argument_list|(
operator|(
name|float
operator|)
name|i
operator|/
operator|(
name|float
operator|)
name|drawable
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
comment|/* Close files, give back allocated memory */
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|line
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

