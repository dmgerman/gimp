begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* SVG loading and saving file filter for the GIMP  * -Dom Lachowicz<cinamod@hotmail.com>  *  * TODO:   * 1) size/zoom dialog, resultion setting  * 2) image preview  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<rsvg.h>
end_include

begin_comment
comment|/* TODO: remove me, initialize gimp i18n services */
end_comment

begin_define
DECL|macro|_ (String)
define|#
directive|define
name|_
parameter_list|(
name|String
parameter_list|)
value|(String)
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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|gint32
name|load_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpRunMode
name|runmode
parameter_list|,
name|gboolean
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
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

begin_comment
comment|/*  * 'query()' - Respond to a plug-in query...  */
end_comment

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw_filename"
block|,
literal|"The name of the file to load"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"file_svg_load"
argument_list|,
literal|"Loads files in the SVG file format"
argument_list|,
literal|"Loads files in the SVG file format"
argument_list|,
literal|"Dom Lachowicz<cinamod@hotmail.com>"
argument_list|,
literal|"Dom Lachowicz<cinamod@hotmail.com>"
argument_list|,
literal|"(c) 2003 - "
name|VERSION
argument_list|,
literal|"<Load>/SVG"
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_return_vals
argument_list|)
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
literal|"file_svg_load"
argument_list|,
literal|"svg"
argument_list|,
literal|""
argument_list|,
literal|"0,string,<?xml,0,string,<svg"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * 'run()' - Run the plug-in...  */
end_comment

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint32
name|image_ID
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
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
comment|/* MUST call this before any RSVG funcs */
name|g_type_init
argument_list|()
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"file_svg_load"
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* INIT_I18N_UI (); */
name|image_ID
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
name|run_mode
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
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
name|GIMP_PDB_IMAGE
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
name|image_ID
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
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

begin_comment
comment|/*  * 'load_image()' - Load a SVG image into a new image window.  */
end_comment

begin_function
specifier|static
name|gint32
DECL|function|load_image (gchar * filename,GimpRunMode runmode,gboolean preview)
name|load_image
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
comment|/* I - File to load */
name|GimpRunMode
name|runmode
parameter_list|,
name|gboolean
name|preview
parameter_list|)
block|{
name|gint32
name|image
decl_stmt|;
comment|/* Image */
name|gint32
name|layer
decl_stmt|;
comment|/* Layer */
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/* Drawable for layer */
name|GimpPixelRgn
name|pixel_rgn
decl_stmt|;
comment|/* Pixel region for layer */
name|GdkPixbuf
modifier|*
name|pixbuf
decl_stmt|;
comment|/* SVG, rasterized */
name|gchar
modifier|*
name|status
decl_stmt|;
comment|/* TODO: could possibly use preview abilities */
name|pixbuf
operator|=
name|rsvg_pixbuf_from_file
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|pixbuf
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"can't open \"%s\"\n"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
name|runmode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|status
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Loading %s:"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|status
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|status
argument_list|)
expr_stmt|;
block|}
name|image
operator|=
name|gimp_image_new
argument_list|(
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|GIMP_RGB
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
name|g_message
argument_list|(
literal|"Can't allocate new image\n%s"
argument_list|,
name|filename
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
name|filename
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|GIMP_RGBA_IMAGE
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|)
expr_stmt|;
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
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|pixel_rgn
argument_list|,
name|gdk_pixbuf_get_pixels
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
argument_list|,
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|pixbuf
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Tell the GIMP to display the image.    */
name|gimp_image_add_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

end_unit

