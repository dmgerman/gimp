begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  * mapcolor plugin  * Copyright (C) 1998 Peter Kirchgessner  * email: peter@kirchgessner.net, WWW: http://www.kirchgessner.net)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_comment
comment|/* Event history:  * V 1.00, PK, 26-Oct-98: Creation.  * V 1.01, PK, 21-Nov-99: Fix problem with working on layered images  *                        Internationalization  */
end_comment

begin_define
DECL|macro|VERSIO
define|#
directive|define
name|VERSIO
value|1.01
end_define

begin_decl_stmt
DECL|variable|dversio
specifier|static
name|char
name|dversio
index|[]
init|=
literal|"v1.01  21-Nov-99"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ident
specifier|static
name|char
name|ident
index|[]
init|=
literal|"@(#) GIMP mapcolor plug-in v1.01  21-Nov-99"
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
file|<time.h>
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
file|"libgimp/gimpui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_CONFIG_H
end_ifdef

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

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
DECL|struct|__anon2b6fdda30108
block|{
DECL|member|colors
name|guchar
name|colors
index|[
literal|4
index|]
index|[
literal|3
index|]
decl_stmt|;
DECL|member|map_mode
name|gint32
name|map_mode
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
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|,
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|}
block|,
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|,
block|{
literal|255
block|,
literal|255
block|,
literal|255
block|}
block|}
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_flag
name|gint
name|run_flag
init|=
name|FALSE
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

begin_function_decl
specifier|static
name|gint
name|dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|mapcolor_close_callback
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

begin_function_decl
specifier|static
name|void
name|mapcolor_ok_callback
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

begin_function_decl
specifier|static
name|void
name|add_color_button
parameter_list|(
name|int
name|csel_index
parameter_list|,
name|int
name|left
parameter_list|,
name|int
name|top
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_mapping
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* The run mode */
end_comment

begin_decl_stmt
DECL|variable|l_run_mode
specifier|static
name|GRunModeType
name|l_run_mode
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|csel_title
specifier|static
name|char
modifier|*
name|csel_title
index|[
literal|4
index|]
init|=
block|{
name|N_
argument_list|(
literal|"First source color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Second source color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"First destination color"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Second destination color"
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
name|GParamDef
name|adjust_args
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
literal|"Input image (not used)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable to adjust"
block|}
block|}
decl_stmt|;
specifier|static
name|int
name|nadjust_args
init|=
sizeof|sizeof
argument_list|(
name|adjust_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|adjust_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|GParamDef
name|map_args
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
literal|"Input image (not used)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable where colors are to map"
block|}
block|,
block|{
name|PARAM_COLOR
block|,
literal|"srccolor_1"
block|,
literal|"First source color"
block|}
block|,
block|{
name|PARAM_COLOR
block|,
literal|"srccolor_2"
block|,
literal|"Second source color"
block|}
block|,
block|{
name|PARAM_COLOR
block|,
literal|"dstcolor_1"
block|,
literal|"First destination color"
block|}
block|,
block|{
name|PARAM_COLOR
block|,
literal|"dstcolor_2"
block|,
literal|"Second destination color"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"map_mode"
block|,
literal|"Mapping mode (0: linear, others reserved)"
block|}
block|}
decl_stmt|;
specifier|static
name|int
name|nmap_args
init|=
sizeof|sizeof
argument_list|(
name|map_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|map_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_color_adjust"
argument_list|,
name|_
argument_list|(
literal|"Adjust current foreground/background color in the\  drawable to black/white"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"The current foreground color is mapped to black, \ the current background color is mapped to white."
argument_list|)
argument_list|,
literal|"Peter Kirchgessner"
argument_list|,
literal|"Peter Kirchgessner"
argument_list|,
name|dversio
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors/Map/Adjust FG-BG"
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nadjust_args
argument_list|,
literal|0
argument_list|,
name|adjust_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_color_map"
argument_list|,
name|_
argument_list|(
literal|"Map two source colors to two destination colors. \ Other colors are mapped by interpolation."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Map two source colors to two destination colors. \ Other colors are mapped by interpolation."
argument_list|)
argument_list|,
literal|"Peter Kirchgessner"
argument_list|,
literal|"Peter Kirchgessner"
argument_list|,
name|dversio
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors/Map/Color Mapping..."
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nmap_args
argument_list|,
literal|0
argument_list|,
name|map_args
argument_list|,
name|NULL
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
name|GDrawable
modifier|*
name|drawable
init|=
name|NULL
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
decl_stmt|;
name|guchar
modifier|*
name|c
init|=
operator|(
name|guchar
operator|*
operator|)
name|ident
decl_stmt|;
name|int
name|j
decl_stmt|;
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|l_run_mode
operator|=
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
while|while
condition|(
name|status
operator|==
name|STATUS_SUCCESS
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
name|STATUS_CALLING_ERROR
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
name|id
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|_
argument_list|(
literal|"Color Mapping / Adjust FG/BG:\nCannot operate on grey/indexed images"
argument_list|)
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
name|strcmp
argument_list|(
name|name
argument_list|,
literal|"plug_in_color_adjust"
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
name|STATUS_CALLING_ERROR
expr_stmt|;
break|break;
block|}
name|c
operator|=
operator|&
operator|(
name|plvals
operator|.
name|colors
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|)
expr_stmt|;
comment|/* First source color */
name|gimp_palette_get_foreground
argument_list|(
name|c
argument_list|,
name|c
operator|+
literal|1
argument_list|,
name|c
operator|+
literal|2
argument_list|)
expr_stmt|;
name|c
operator|=
operator|&
operator|(
name|plvals
operator|.
name|colors
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|)
expr_stmt|;
comment|/* Second source color */
name|gimp_palette_get_background
argument_list|(
name|c
argument_list|,
name|c
operator|+
literal|1
argument_list|,
name|c
operator|+
literal|2
argument_list|)
expr_stmt|;
name|c
operator|=
operator|&
operator|(
name|plvals
operator|.
name|colors
index|[
literal|2
index|]
index|[
literal|0
index|]
operator|)
expr_stmt|;
comment|/* First destination color */
name|c
index|[
literal|0
index|]
operator|=
name|c
index|[
literal|1
index|]
operator|=
name|c
index|[
literal|2
index|]
operator|=
literal|0
expr_stmt|;
comment|/* Foreground mapped to black */
name|c
operator|=
operator|&
operator|(
name|plvals
operator|.
name|colors
index|[
literal|3
index|]
index|[
literal|0
index|]
operator|)
expr_stmt|;
comment|/* second destination color */
name|c
index|[
literal|0
index|]
operator|=
name|c
index|[
literal|1
index|]
operator|=
name|c
index|[
literal|2
index|]
operator|=
literal|255
expr_stmt|;
comment|/* Background mapped to white */
name|plvals
operator|.
name|map_mode
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Adjusting Foreground/Background"
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
literal|"plug_in_color_map"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|run_mode
operator|==
name|RUN_NONINTERACTIVE
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
name|STATUS_CALLING_ERROR
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
index|[
literal|0
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
operator|.
name|red
expr_stmt|;
name|plvals
operator|.
name|colors
index|[
name|j
index|]
index|[
literal|1
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
operator|.
name|green
expr_stmt|;
name|plvals
operator|.
name|colors
index|[
name|j
index|]
index|[
literal|2
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
operator|.
name|blue
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
name|RUN_INTERACTIVE
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
name|c
operator|=
operator|&
operator|(
name|plvals
operator|.
name|colors
index|[
literal|0
index|]
index|[
literal|0
index|]
operator|)
expr_stmt|;
comment|/* First source color */
name|gimp_palette_get_foreground
argument_list|(
name|c
argument_list|,
name|c
operator|+
literal|1
argument_list|,
name|c
operator|+
literal|2
argument_list|)
expr_stmt|;
name|c
operator|=
operator|&
operator|(
name|plvals
operator|.
name|colors
index|[
literal|1
index|]
index|[
literal|0
index|]
operator|)
expr_stmt|;
comment|/* Second source color */
name|gimp_palette_get_background
argument_list|(
name|c
argument_list|,
name|c
operator|+
literal|1
argument_list|,
name|c
operator|+
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dialog
argument_list|()
condition|)
break|break;
block|}
elseif|else
if|if
condition|(
name|run_mode
operator|==
name|RUN_WITH_LAST_VALS
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
name|STATUS_CALLING_ERROR
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
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
name|RUN_INTERACTIVE
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
name|STATUS_EXECUTION_ERROR
expr_stmt|;
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
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
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
name|gint
DECL|function|dialog ()
name|dialog
parameter_list|()
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|hbbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|guchar
modifier|*
name|color_cube
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
decl_stmt|;
name|gint
name|argc
decl_stmt|;
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
literal|"Map colors"
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
name|gdk_set_use_xshm
argument_list|(
name|gimp_use_xshm
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_preview_set_gamma
argument_list|(
name|gimp_gamma
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_preview_set_install_cmap
argument_list|(
name|gimp_install_cmap
argument_list|()
argument_list|)
expr_stmt|;
name|color_cube
operator|=
name|gimp_color_cube
argument_list|()
expr_stmt|;
name|gtk_preview_set_color_cube
argument_list|(
name|color_cube
index|[
literal|0
index|]
argument_list|,
name|color_cube
index|[
literal|1
index|]
argument_list|,
name|color_cube
index|[
literal|2
index|]
argument_list|,
name|color_cube
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_set_default_visual
argument_list|(
name|gtk_preview_get_visual
argument_list|()
argument_list|)
expr_stmt|;
name|gtk_widget_set_default_colormap
argument_list|(
name|gtk_preview_get_cmap
argument_list|()
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dlg
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Map colors"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dlg
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|mapcolor_close_callback
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Action area  */
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|hbbox
operator|=
name|gtk_hbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_button_box_set_spacing
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|hbbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|hbbox
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
name|hbbox
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|mapcolor_ok_callback
argument_list|,
name|dlg
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox
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
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|gtk_widget_destroy
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dlg
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox
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
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_container_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|0
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
comment|/* The table keeps the color selections */
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
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|add_color_button
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|add_color_button
argument_list|(
literal|1
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|add_color_button
argument_list|(
literal|2
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|add_color_button
argument_list|(
literal|3
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
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
return|return
name|run_flag
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_color_button (int csel_index,int left,int top,GtkWidget * table)
name|add_color_button
parameter_list|(
name|int
name|csel_index
parameter_list|,
name|int
name|left
parameter_list|,
name|int
name|top
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
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
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|left
argument_list|,
name|left
operator|+
literal|1
argument_list|,
name|top
argument_list|,
name|top
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
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
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
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
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|left
operator|+
literal|1
argument_list|,
name|left
operator|+
literal|2
argument_list|,
name|top
argument_list|,
name|top
operator|+
literal|1
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
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
name|plvals
operator|.
name|colors
index|[
name|csel_index
index|]
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|mapcolor_close_callback (GtkWidget * widget,gpointer data)
name|mapcolor_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|mapcolor_ok_callback (GtkWidget * widget,gpointer data)
name|mapcolor_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|plvals
operator|.
name|map_mode
operator|=
literal|0
expr_stmt|;
comment|/* Currently always linear mapping */
name|run_flag
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|get_mapping (guchar * src_col1,guchar * src_col2,guchar * dst_col1,guchar * dst_col2,gint32 map_mode,guchar * redmap,guchar * greenmap,guchar * bluemap)
name|get_mapping
parameter_list|(
name|guchar
modifier|*
name|src_col1
parameter_list|,
name|guchar
modifier|*
name|src_col2
parameter_list|,
name|guchar
modifier|*
name|dst_col1
parameter_list|,
name|guchar
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
name|int
name|rgb
decl_stmt|,
name|i
decl_stmt|,
name|j
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
name|src_col1
index|[
name|rgb
index|]
expr_stmt|;
name|as
operator|=
name|dst_col1
index|[
name|rgb
index|]
expr_stmt|;
name|b
operator|=
name|src_col2
index|[
name|rgb
index|]
expr_stmt|;
name|bs
operator|=
name|dst_col2
index|[
name|rgb
index|]
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
name|j
operator|=
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
expr_stmt|;
if|if
condition|(
name|j
operator|>
literal|255
condition|)
name|j
operator|=
literal|255
expr_stmt|;
elseif|else
if|if
condition|(
name|j
operator|<
literal|0
condition|)
name|j
operator|=
literal|0
expr_stmt|;
name|colormap
index|[
name|rgb
index|]
index|[
name|i
index|]
operator|=
name|j
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
DECL|function|color_mapping (GDrawable * drawable)
name|color_mapping
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|int
name|processed
decl_stmt|,
name|total
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|xmin
decl_stmt|,
name|xmax
decl_stmt|,
name|ymin
decl_stmt|,
name|ymax
decl_stmt|,
name|bpp
init|=
operator|(
name|gint
operator|)
name|drawable
operator|->
name|bpp
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|GPixelRgn
name|src_rgn
decl_stmt|,
name|dest_rgn
decl_stmt|;
name|gpointer
name|pr
decl_stmt|;
name|double
name|progress
decl_stmt|;
name|unsigned
name|char
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
name|unsigned
name|char
modifier|*
name|src_col1
init|=
name|plvals
operator|.
name|colors
index|[
literal|0
index|]
decl_stmt|;
name|unsigned
name|char
modifier|*
name|src_col2
init|=
name|plvals
operator|.
name|colors
index|[
literal|1
index|]
decl_stmt|;
name|unsigned
name|char
modifier|*
name|dst_col1
init|=
name|plvals
operator|.
name|colors
index|[
literal|2
index|]
decl_stmt|;
name|unsigned
name|char
modifier|*
name|dst_col2
init|=
name|plvals
operator|.
name|colors
index|[
literal|3
index|]
decl_stmt|;
if|if
condition|(
operator|(
name|src_col1
index|[
literal|0
index|]
operator|==
name|src_col2
index|[
literal|0
index|]
operator|)
operator|||
operator|(
name|src_col1
index|[
literal|1
index|]
operator|==
name|src_col2
index|[
literal|1
index|]
operator|)
operator|||
operator|(
name|src_col1
index|[
literal|2
index|]
operator|==
name|src_col2
index|[
literal|2
index|]
operator|)
condition|)
return|return;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
operator|&
name|xmin
argument_list|,
operator|&
name|ymin
argument_list|,
operator|&
name|xmax
argument_list|,
operator|&
name|ymax
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|ymin
operator|==
name|ymax
operator|)
operator|||
operator|(
name|xmin
operator|==
name|xmax
operator|)
condition|)
return|return;
name|total
operator|=
operator|(
name|xmax
operator|-
name|xmin
operator|)
operator|*
operator|(
name|ymax
operator|-
name|ymin
operator|)
expr_stmt|;
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
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
name|xmin
argument_list|,
name|ymin
argument_list|,
operator|(
name|xmax
operator|-
name|xmin
operator|)
argument_list|,
operator|(
name|ymax
operator|-
name|ymin
operator|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|dest_rgn
argument_list|,
name|drawable
argument_list|,
name|xmin
argument_list|,
name|ymin
argument_list|,
operator|(
name|xmax
operator|-
name|xmin
operator|)
argument_list|,
operator|(
name|ymax
operator|-
name|ymin
operator|)
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pr
operator|=
name|gimp_pixel_rgns_register
argument_list|(
literal|2
argument_list|,
operator|&
name|src_rgn
argument_list|,
operator|&
name|dest_rgn
argument_list|)
expr_stmt|;
name|get_mapping
argument_list|(
name|src_col1
argument_list|,
name|src_col2
argument_list|,
name|dst_col1
argument_list|,
name|dst_col2
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
name|processed
operator|=
literal|0
expr_stmt|;
name|progress
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|gimp_pixel_rgns_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|src_rgn
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
name|src
operator|=
name|src_rgn
operator|.
name|data
operator|+
name|y
operator|*
name|src_rgn
operator|.
name|rowstride
expr_stmt|;
name|dest
operator|=
name|dest_rgn
operator|.
name|data
operator|+
name|y
operator|*
name|dest_rgn
operator|.
name|rowstride
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|src_rgn
operator|.
name|w
condition|;
name|x
operator|++
control|)
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
name|src
operator|+=
name|bpp
expr_stmt|;
name|dest
operator|+=
name|bpp
expr_stmt|;
name|processed
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
name|l_run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
block|{
if|if
condition|(
operator|(
name|double
operator|)
name|processed
operator|/
operator|(
name|double
operator|)
name|total
operator|-
name|progress
operator|>
literal|0.1
condition|)
block|{
name|progress
operator|=
operator|(
name|double
operator|)
name|processed
operator|/
operator|(
name|double
operator|)
name|total
expr_stmt|;
name|gimp_progress_update
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|l_run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
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
name|xmin
argument_list|,
name|ymin
argument_list|,
operator|(
name|xmax
operator|-
name|xmin
operator|)
argument_list|,
operator|(
name|ymax
operator|-
name|ymin
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

