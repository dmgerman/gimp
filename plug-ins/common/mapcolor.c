begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * mapcolor plugin  * Copyright (C) 1998 Peter Kirchgessner  * email: peter@kirchgessner.net, WWW: http://www.kirchgessner.net)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_comment
comment|/* Event history:  * V 1.00, PK, 26-Oct-98: Creation.  * V 1.01, PK, 21-Nov-99: Fix problem with working on layered images  *                        Internationalization  * V 1.02, PK, 19-Mar-00: Better explaining text/dialogue  *                        Preview added  *                        Fix problem with divide by zero  * V 1.03,neo, 22-May-00: Fixed divide by zero in preview code.  */
end_comment

begin_define
DECL|macro|VERSIO
define|#
directive|define
name|VERSIO
value|1.03
end_define

begin_decl_stmt
DECL|variable|dversio
specifier|static
name|char
name|dversio
index|[]
init|=
literal|"v1.03  22-May-00"
decl_stmt|;
end_decl_stmt

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
DECL|macro|COLOR_MAP_PROC
define|#
directive|define
name|COLOR_MAP_PROC
value|"plug-in-color-map"
end_define

begin_define
DECL|macro|COLOR_ADJUST_PROC
define|#
directive|define
name|COLOR_ADJUST_PROC
value|"plug-in-color-adjust"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"mapcolor"
end_define

begin_define
DECL|macro|PRV_WIDTH
define|#
directive|define
name|PRV_WIDTH
value|50
end_define

begin_define
DECL|macro|PRV_HEIGHT
define|#
directive|define
name|PRV_HEIGHT
value|20
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b27dac20108
block|{
DECL|member|colors
name|GimpRGB
name|colors
index|[
literal|4
index|]
decl_stmt|;
DECL|member|map_mode
name|gint32
name|map_mode
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|PluginValues
block|}
name|PluginValues
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|plvals
name|PluginValues
name|plvals
init|=
block|{
block|{
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
block|,
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|,
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
block|,
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|,   }
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|redmap
DECL|variable|greenmap
DECL|variable|bluemap
specifier|static
name|guchar
name|redmap
index|[
literal|256
index|]
decl_stmt|,
name|greenmap
index|[
literal|256
index|]
decl_stmt|,
name|bluemap
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Declare some local functions.  */
end_comment

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

begin_function_decl
specifier|static
name|void
name|update_img_preview
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
name|mapcolor_dialog
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
name|get_mapping
parameter_list|(
name|GimpRGB
modifier|*
name|src_col1
parameter_list|,
name|GimpRGB
modifier|*
name|src_col2
parameter_list|,
name|GimpRGB
modifier|*
name|dst_col1
parameter_list|,
name|GimpRGB
modifier|*
name|dst_col2
parameter_list|,
name|gint32
name|map_mode
parameter_list|,
name|guchar
modifier|*
name|redmap
parameter_list|,
name|guchar
modifier|*
name|greenmap
parameter_list|,
name|guchar
modifier|*
name|bluemap
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|add_color_button
parameter_list|(
name|gint
name|csel_index
parameter_list|,
name|gint
name|left
parameter_list|,
name|gint
name|top
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|GtkWidget
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_mapping
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|csel_title
specifier|static
name|gchar
modifier|*
name|csel_title
index|[
literal|4
index|]
init|=
block|{
name|N_
argument_list|(
literal|"First Source Color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Second Source Color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"First Destination Color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Second Destination Color"
argument_list|)
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
name|GimpParamDef
name|adjust_args
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
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (not used)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable to adjust"
block|}
block|}
decl_stmt|;
specifier|static
name|GimpParamDef
name|map_args
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
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (not used)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable where colors are to map"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"srccolor_1"
block|,
literal|"First source color"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"srccolor_2"
block|,
literal|"Second source color"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"dstcolor_1"
block|,
literal|"First destination color"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"dstcolor_2"
block|,
literal|"Second destination color"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"map_mode"
block|,
literal|"Mapping mode (0: linear, others reserved)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|COLOR_ADJUST_PROC
argument_list|,
literal|"Adjust color range given by foreground/background "
literal|"color to black/white"
argument_list|,
literal|"The current foreground color is mapped to black "
literal|"(black point), the current background color is "
literal|"mapped to white (white point). Intermediate "
literal|"colors are interpolated"
argument_list|,
literal|"Peter Kirchgessner"
argument_list|,
literal|"Peter Kirchgessner"
argument_list|,
name|dversio
argument_list|,
name|N_
argument_list|(
literal|"Adjust _FG-BG"
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|adjust_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|adjust_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
name|COLOR_ADJUST_PROC
argument_list|,
literal|"<Image>/Colors/Map"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|COLOR_MAP_PROC
argument_list|,
literal|"Map color range specified by two colors"
literal|"to color range specified by two other color."
argument_list|,
literal|"Map color range specified by two colors"
literal|"to color range specified by two other color."
literal|"Intermediate colors are interpolated."
argument_list|,
literal|"Peter Kirchgessner"
argument_list|,
literal|"Peter Kirchgessner"
argument_list|,
name|dversio
argument_list|,
name|N_
argument_list|(
literal|"Color Range _Mapping..."
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|map_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|map_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
name|COLOR_MAP_PROC
argument_list|,
literal|"<Image>/Colors/Map"
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
literal|1
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|INIT_I18N
argument_list|()
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
name|status
expr_stmt|;
while|while
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
if|if
condition|(
name|nparams
operator|<
literal|3
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
comment|/* Make sure the drawable is RGB color */
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
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot operate on gray or indexed color images."
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|COLOR_ADJUST_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|nparams
operator|!=
literal|3
condition|)
comment|/* Make sure all the arguments are there */
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
name|gimp_context_get_foreground
argument_list|(
name|plvals
operator|.
name|colors
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|plvals
operator|.
name|colors
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_rgb_set
argument_list|(
name|plvals
operator|.
name|colors
operator|+
literal|2
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_rgb_set
argument_list|(
name|plvals
operator|.
name|colors
operator|+
literal|3
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|plvals
operator|.
name|map_mode
operator|=
literal|0
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Adjusting FG-BG"
argument_list|)
argument_list|)
expr_stmt|;
name|color_mapping
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|COLOR_MAP_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
if|if
condition|(
name|nparams
operator|!=
literal|8
condition|)
comment|/* Make sure all the arguments are there */
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|4
condition|;
name|j
operator|++
control|)
block|{
name|plvals
operator|.
name|colors
index|[
name|j
index|]
operator|=
name|param
index|[
literal|3
operator|+
name|j
index|]
operator|.
name|data
operator|.
name|d_color
expr_stmt|;
block|}
name|plvals
operator|.
name|map_mode
operator|=
name|param
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|gimp_get_data
argument_list|(
name|name
argument_list|,
operator|&
name|plvals
argument_list|)
expr_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|plvals
operator|.
name|colors
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|plvals
operator|.
name|colors
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|mapcolor_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
break|break;
block|}
elseif|else
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_WITH_LAST_VALS
condition|)
block|{
name|gimp_get_data
argument_list|(
name|name
argument_list|,
operator|&
name|plvals
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Mapping colors"
argument_list|)
argument_list|)
expr_stmt|;
name|color_mapping
argument_list|(
name|drawable
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
name|name
argument_list|,
operator|&
name|plvals
argument_list|,
sizeof|sizeof
argument_list|(
name|plvals
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
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
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
operator|)
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
if|if
condition|(
name|drawable
operator|!=
name|NULL
condition|)
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
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
name|void
DECL|function|update_img_preview (GimpDrawable * drawable,GimpPreview * preview)
name|update_img_preview
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
name|guchar
name|redmap
index|[
literal|256
index|]
decl_stmt|,
name|greenmap
index|[
literal|256
index|]
decl_stmt|,
name|bluemap
index|[
literal|256
index|]
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|,
name|bpp
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|,
modifier|*
name|s
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|gint
name|j
decl_stmt|;
name|get_mapping
argument_list|(
name|plvals
operator|.
name|colors
argument_list|,
name|plvals
operator|.
name|colors
operator|+
literal|1
argument_list|,
name|plvals
operator|.
name|colors
operator|+
literal|2
argument_list|,
name|plvals
operator|.
name|colors
operator|+
literal|3
argument_list|,
name|plvals
operator|.
name|map_mode
argument_list|,
name|redmap
argument_list|,
name|greenmap
argument_list|,
name|bluemap
argument_list|)
expr_stmt|;
name|src
operator|=
name|gimp_zoom_preview_get_source
argument_list|(
name|GIMP_ZOOM_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
argument_list|)
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
name|j
operator|=
name|width
operator|*
name|height
expr_stmt|;
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|j
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|s
operator|=
name|src
expr_stmt|;
name|d
operator|=
name|dest
expr_stmt|;
while|while
condition|(
name|j
operator|--
operator|>
literal|0
condition|)
block|{
operator|*
operator|(
name|d
operator|++
operator|)
operator|=
name|redmap
index|[
operator|*
operator|(
name|s
operator|++
operator|)
index|]
expr_stmt|;
operator|*
operator|(
name|d
operator|++
operator|)
operator|=
name|greenmap
index|[
operator|*
operator|(
name|s
operator|++
operator|)
index|]
expr_stmt|;
operator|*
operator|(
name|d
operator|++
operator|)
operator|=
name|bluemap
index|[
operator|*
operator|(
name|s
operator|++
operator|)
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
operator|*
operator|(
name|d
operator|++
operator|)
operator|=
operator|*
operator|(
name|s
operator|++
operator|)
expr_stmt|;
block|}
name|gimp_preview_draw_buffer
argument_list|(
name|preview
argument_list|,
name|dest
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|mapcolor_dialog (GimpDrawable * drawable)
name|mapcolor_dialog
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|gint
name|j
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
literal|"Map Color Range"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|COLOR_MAP_PROC
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
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
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_zoom_preview_new
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
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
name|update_img_preview
argument_list|)
argument_list|,
name|drawable
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
literal|2
condition|;
name|j
operator|++
control|)
block|{
name|frame
operator|=
name|gimp_frame_new
argument_list|(
operator|(
name|j
operator|==
literal|0
operator|)
condition|?
name|_
argument_list|(
literal|"Source Color Range"
argument_list|)
else|:
name|_
argument_list|(
literal|"Destination Color Range"
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
comment|/* The table keeps the color selections */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|4
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
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|add_color_button
argument_list|(
name|j
operator|*
literal|2
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|table
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|add_color_button
argument_list|(
name|j
operator|*
literal|2
operator|+
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
name|table
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
name|run
condition|)
name|plvals
operator|.
name|map_mode
operator|=
literal|0
expr_stmt|;
comment|/* Currently always linear mapping */
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
DECL|function|add_color_button (gint csel_index,gint left,gint top,GtkWidget * table,GtkWidget * preview)
name|add_color_button
parameter_list|(
name|gint
name|csel_index
parameter_list|,
name|gint
name|left
parameter_list|,
name|gint
name|top
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|button
operator|=
name|gimp_color_button_new
argument_list|(
name|gettext
argument_list|(
name|csel_title
index|[
name|csel_index
index|]
argument_list|)
argument_list|,
name|PRV_WIDTH
argument_list|,
name|PRV_HEIGHT
argument_list|,
operator|&
name|plvals
operator|.
name|colors
index|[
name|csel_index
index|]
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|left
operator|+
literal|1
argument_list|,
name|top
argument_list|,
operator|(
name|left
operator|==
literal|0
operator|)
condition|?
name|_
argument_list|(
literal|"From:"
argument_list|)
else|:
name|_
argument_list|(
literal|"To:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|button
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_button_get_color
argument_list|)
argument_list|,
operator|&
name|plvals
operator|.
name|colors
index|[
name|csel_index
index|]
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|button
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|get_mapping (GimpRGB * src_col1,GimpRGB * src_col2,GimpRGB * dst_col1,GimpRGB * dst_col2,gint32 map_mode,guchar * redmap,guchar * greenmap,guchar * bluemap)
name|get_mapping
parameter_list|(
name|GimpRGB
modifier|*
name|src_col1
parameter_list|,
name|GimpRGB
modifier|*
name|src_col2
parameter_list|,
name|GimpRGB
modifier|*
name|dst_col1
parameter_list|,
name|GimpRGB
modifier|*
name|dst_col2
parameter_list|,
name|gint32
name|map_mode
parameter_list|,
name|guchar
modifier|*
name|redmap
parameter_list|,
name|guchar
modifier|*
name|greenmap
parameter_list|,
name|guchar
modifier|*
name|bluemap
parameter_list|)
block|{
name|guchar
name|src1
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|src2
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|dst1
index|[
literal|3
index|]
decl_stmt|;
name|guchar
name|dst2
index|[
literal|3
index|]
decl_stmt|;
name|gint
name|rgb
decl_stmt|,
name|i
decl_stmt|,
name|a
decl_stmt|,
name|as
decl_stmt|,
name|b
decl_stmt|,
name|bs
decl_stmt|;
name|guchar
modifier|*
name|colormap
index|[
literal|3
index|]
decl_stmt|;
comment|/* Currently we always do a linear mapping */
name|colormap
index|[
literal|0
index|]
operator|=
name|redmap
expr_stmt|;
name|colormap
index|[
literal|1
index|]
operator|=
name|greenmap
expr_stmt|;
name|colormap
index|[
literal|2
index|]
operator|=
name|bluemap
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|src_col1
argument_list|,
name|src1
argument_list|,
name|src1
operator|+
literal|1
argument_list|,
name|src1
operator|+
literal|2
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|src_col2
argument_list|,
name|src2
argument_list|,
name|src2
operator|+
literal|1
argument_list|,
name|src2
operator|+
literal|2
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|dst_col1
argument_list|,
name|dst1
argument_list|,
name|dst1
operator|+
literal|1
argument_list|,
name|dst1
operator|+
literal|2
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
name|dst_col2
argument_list|,
name|dst2
argument_list|,
name|dst2
operator|+
literal|1
argument_list|,
name|dst2
operator|+
literal|2
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|map_mode
condition|)
block|{
case|case
literal|0
case|:
default|default:
for|for
control|(
name|rgb
operator|=
literal|0
init|;
name|rgb
operator|<
literal|3
condition|;
name|rgb
operator|++
control|)
block|{
name|a
operator|=
name|src1
index|[
name|rgb
index|]
expr_stmt|;
name|as
operator|=
name|dst1
index|[
name|rgb
index|]
expr_stmt|;
name|b
operator|=
name|src2
index|[
name|rgb
index|]
expr_stmt|;
name|bs
operator|=
name|dst2
index|[
name|rgb
index|]
expr_stmt|;
if|if
condition|(
name|b
operator|==
name|a
condition|)
name|b
operator|=
name|a
operator|+
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|j
init|=
operator|(
operator|(
name|i
operator|-
name|a
operator|)
operator|*
operator|(
name|bs
operator|-
name|as
operator|)
operator|)
operator|/
operator|(
name|b
operator|-
name|a
operator|)
operator|+
name|as
decl_stmt|;
name|colormap
index|[
name|rgb
index|]
index|[
name|i
index|]
operator|=
name|CLAMP0255
argument_list|(
name|j
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|mapcolor_func (const guchar * src,guchar * dest,gint bpp,gpointer data)
name|mapcolor_func
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|dest
index|[
literal|0
index|]
operator|=
name|redmap
index|[
name|src
index|[
literal|0
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|greenmap
index|[
name|src
index|[
literal|1
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|bluemap
index|[
name|src
index|[
literal|2
index|]
index|]
expr_stmt|;
if|if
condition|(
name|bpp
operator|>
literal|3
condition|)
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|3
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_mapping (GimpDrawable * drawable)
name|color_mapping
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|gimp_rgb_distance
argument_list|(
operator|&
name|plvals
operator|.
name|colors
index|[
literal|0
index|]
argument_list|,
operator|&
name|plvals
operator|.
name|colors
index|[
literal|1
index|]
argument_list|)
operator|<
literal|0.0001
condition|)
return|return;
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Cannot operate on gray or indexed color images."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
name|drawable
operator|->
name|width
operator|/
name|gimp_tile_width
argument_list|()
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
name|get_mapping
argument_list|(
name|plvals
operator|.
name|colors
argument_list|,
name|plvals
operator|.
name|colors
operator|+
literal|1
argument_list|,
name|plvals
operator|.
name|colors
operator|+
literal|2
argument_list|,
name|plvals
operator|.
name|colors
operator|+
literal|3
argument_list|,
name|plvals
operator|.
name|map_mode
argument_list|,
name|redmap
argument_list|,
name|greenmap
argument_list|,
name|bluemap
argument_list|)
expr_stmt|;
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|mapcolor_func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

