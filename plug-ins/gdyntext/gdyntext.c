begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999,2000 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
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
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"gdyntext.h"
end_include

begin_include
include|#
directive|include
file|"font_selection.h"
end_include

begin_function_decl
specifier|static
name|void
name|gdt_query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gdt_run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GimpParam
modifier|*
name|param
parameter_list|,
name|int
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
name|NULL
block|,
name|gdt_query
block|,
name|gdt_run
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gdtvals
name|GdtVals
name|gdtvals
decl_stmt|;
end_decl_stmt

begin_ifndef
ifndef|#
directive|ifndef
name|DEBUG_UI
end_ifndef

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|void
name|gdt_query
parameter_list|(
name|void
parameter_list|)
block|{
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
block|{
specifier|static
name|GimpParamDef
name|gdt_args
index|[]
init|=
block|{
comment|/* standard params */
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
literal|"Input drawable"
block|}
block|,
comment|/* gdyntext params */
block|{
name|PARAM_STRING
block|,
literal|"text"
block|,
literal|"Text to render"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"antialias"
block|,
literal|"Generate antialiased text"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"alignment"
block|,
literal|"Text alignment: { LEFT = 0, CENTER = 1, RIGHT = 2 }"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"rotation"
block|,
literal|"Text rotation (degrees)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"line_spacing"
block|,
literal|"Line spacing"
block|}
block|,
block|{
name|PARAM_COLOR
block|,
literal|"color"
block|,
literal|"Text color"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"layer_alignment"
block|,
literal|"Layer alignment { NONE = 0, BOTTOM_LEFT = 1, BOTTOM_CENTER = 2, BOTTOM_RIGHT = 3, MIDDLE_LEFT = 4, CENTER = 5, MIDDLE_RIGHT = 6, TOP_LEFT = 7, TOP_CENTER = 8, TOP_RIGHT = 9 }"
block|}
block|,
block|{
name|PARAM_STRING
block|,
literal|"fontname"
block|,
literal|"The fontname (conforming to the X Logical Font Description Conventions)"
block|}
block|, 		}
decl_stmt|;
specifier|static
name|GimpParamDef
name|gdt_rets
index|[]
init|=
block|{
block|{
name|PARAM_LAYER
block|,
literal|"layer"
block|,
literal|"The text layer"
block|}
block|, 		}
decl_stmt|;
specifier|static
name|int
name|ngdt_args
init|=
sizeof|sizeof
argument_list|(
name|gdt_args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|gdt_args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
specifier|static
name|int
name|ngdt_rets
init|=
sizeof|sizeof
argument_list|(
name|gdt_rets
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|gdt_rets
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_dynamic_text"
argument_list|,
literal|"GIMP Dynamic Text"
argument_list|,
literal|""
argument_list|,
literal|"Marco Lamberto<lm@geocities.com>"
argument_list|,
literal|"Marco Lamberto"
argument_list|,
literal|"Jan 1999"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Render/Dynamic Text..."
argument_list|)
argument_list|,
literal|"RGB*,GRAY*,INDEXED*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|ngdt_args
argument_list|,
name|ngdt_rets
argument_list|,
name|gdt_args
argument_list|,
name|gdt_rets
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|gdt_run (char * name,int nparams,GimpParam * param,int * nreturn_vals,GimpParam ** return_vals)
specifier|static
name|void
name|gdt_run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GimpParam
modifier|*
name|param
parameter_list|,
name|int
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
name|GimpRunModeType
name|run_mode
decl_stmt|;
name|GdtVals
name|oldvals
decl_stmt|;
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
name|gdtvals
operator|.
name|valid
operator|=
name|TRUE
expr_stmt|;
name|gdtvals
operator|.
name|change_layer_name
operator|=
name|FALSE
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
name|gdtvals
operator|.
name|image_id
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
name|gdtvals
operator|.
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
name|gdtvals
operator|.
name|layer_id
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_layer
expr_stmt|;
name|gdtvals
operator|.
name|messages
operator|=
name|NULL
expr_stmt|;
name|gdtvals
operator|.
name|preview
operator|=
name|TRUE
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|2
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
name|STATUS_SUCCESS
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|PARAM_LAYER
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
operator|-
literal|1
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|RUN_INTERACTIVE
case|:
name|memset
argument_list|(
operator|&
name|oldvals
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|GdtVals
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_get_data
argument_list|(
literal|"plug_in_gdyntext"
argument_list|,
operator|&
name|oldvals
argument_list|)
expr_stmt|;
if|if
condition|(
name|oldvals
operator|.
name|valid
condition|)
block|{
name|strncpy
argument_list|(
name|gdtvals
operator|.
name|text
argument_list|,
name|oldvals
operator|.
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|gdtvals
operator|.
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|gdtvals
operator|.
name|xlfd
argument_list|,
name|oldvals
operator|.
name|xlfd
argument_list|,
sizeof|sizeof
argument_list|(
name|gdtvals
operator|.
name|xlfd
argument_list|)
argument_list|)
expr_stmt|;
name|gdtvals
operator|.
name|color
operator|=
name|oldvals
operator|.
name|color
expr_stmt|;
name|gdtvals
operator|.
name|antialias
operator|=
name|oldvals
operator|.
name|antialias
expr_stmt|;
name|gdtvals
operator|.
name|alignment
operator|=
name|oldvals
operator|.
name|alignment
expr_stmt|;
name|gdtvals
operator|.
name|rotation
operator|=
name|oldvals
operator|.
name|rotation
expr_stmt|;
name|gdtvals
operator|.
name|line_spacing
operator|=
name|oldvals
operator|.
name|line_spacing
expr_stmt|;
name|gdtvals
operator|.
name|layer_alignment
operator|=
name|oldvals
operator|.
name|layer_alignment
expr_stmt|;
name|gdtvals
operator|.
name|preview
operator|=
name|oldvals
operator|.
name|preview
expr_stmt|;
block|}
name|gdt_load
argument_list|(
operator|&
name|gdtvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gdt_create_ui
argument_list|(
operator|&
name|gdtvals
argument_list|)
condition|)
return|return;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"%d\n"
argument_list|,
name|nparams
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|nparams
operator|!=
literal|11
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
name|STATUS_CALLING_ERROR
expr_stmt|;
return|return;
block|}
else|else
block|{
name|gdtvals
operator|.
name|new_layer
operator|=
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|gdtvals
operator|.
name|drawable_id
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|gdtvals
operator|.
name|text
argument_list|,
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
sizeof|sizeof
argument_list|(
name|gdtvals
operator|.
name|text
argument_list|)
argument_list|)
expr_stmt|;
name|gdtvals
operator|.
name|antialias
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gdtvals
operator|.
name|alignment
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
name|gdtvals
operator|.
name|rotation
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
name|gdtvals
operator|.
name|line_spacing
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
name|gdtvals
operator|.
name|color
operator|=
operator|(
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|red
operator|<<
literal|16
operator|)
operator|+
operator|(
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|green
operator|<<
literal|8
operator|)
operator|+
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|blue
expr_stmt|;
name|gdtvals
operator|.
name|layer_alignment
operator|=
name|param
index|[
literal|9
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|strncpy
argument_list|(
name|gdtvals
operator|.
name|xlfd
argument_list|,
name|param
index|[
literal|10
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|,
sizeof|sizeof
argument_list|(
name|gdtvals
operator|.
name|xlfd
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"plug_in_gdyntext"
argument_list|,
operator|&
name|gdtvals
argument_list|)
expr_stmt|;
name|gdtvals
operator|.
name|image_id
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
name|gdtvals
operator|.
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
name|gdtvals
operator|.
name|layer_id
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_layer
expr_stmt|;
name|gdtvals
operator|.
name|new_layer
operator|=
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|gdtvals
operator|.
name|drawable_id
argument_list|)
expr_stmt|;
break|break;
block|}
name|gdt_render_text
argument_list|(
operator|&
name|gdtvals
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
literal|"plug_in_gdyntext"
argument_list|,
operator|&
name|gdtvals
argument_list|,
sizeof|sizeof
argument_list|(
name|GdtVals
argument_list|)
argument_list|)
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|gdtvals
operator|.
name|layer_id
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gdt_load (GdtVals * data)
name|void
name|gdt_load
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
block|{
name|gchar
modifier|*
name|gdtparams
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|gdtparams0
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|params
init|=
name|NULL
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|gdt_compat_load
argument_list|(
name|data
argument_list|)
condition|)
return|return;
if|if
condition|(
operator|(
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
name|gdtparams
operator|=
name|g_strdup
argument_list|(
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gdtparams
operator|==
name|NULL
condition|)
name|gdtparams
operator|=
name|gimp_layer_get_name
argument_list|(
name|data
operator|->
name|layer_id
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_has_alpha
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|)
operator|||
name|strncmp
argument_list|(
name|gdtparams
argument_list|,
literal|"GDT"
argument_list|,
literal|3
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|data
operator|->
name|messages
operator|=
name|g_list_append
argument_list|(
name|data
operator|->
name|messages
argument_list|,
name|_
argument_list|(
literal|" Current layer isn't a GDynText layer or it has no alpha channel."
literal|" Forcing new layer creation."
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|->
name|new_layer
operator|=
name|TRUE
expr_stmt|;
comment|/* 		strcpy(data->text, ""); 		strcpy(data->xlfd, ""); 		{ 			GParam *ret_vals; 			gint nret_vals;  			ret_vals = gimp_run_procedure("gimp_palette_get_foreground",&nret_vals, 				PARAM_END); 			data->color = 				(ret_vals[1].data.d_color.red<< 16) + 				(ret_vals[1].data.d_color.green<< 8) + 				ret_vals[1].data.d_color.blue; 			gimp_destroy_params(ret_vals, nret_vals); 		} 		data->antialias				= TRUE; 		data->alignment 			= LEFT; 		data->rotation				= 0; 		data->line_spacing		= 0; 		data->layer_alignment	= LA_NONE; 		*/
return|return;
block|}
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"'%s'\n"
argument_list|,
name|gdtparams
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|{
name|gchar
modifier|*
name|st
decl_stmt|;
name|int
name|len
decl_stmt|;
name|st
operator|=
name|strchr
argument_list|(
name|gdtparams
argument_list|,
literal|'{'
argument_list|)
operator|+
literal|1
expr_stmt|;
name|len
operator|=
name|strrchr
argument_list|(
name|st
argument_list|,
literal|'}'
argument_list|)
operator|-
name|st
expr_stmt|;
name|gdtparams0
operator|=
name|g_strndup
argument_list|(
name|st
argument_list|,
name|len
argument_list|)
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"'%s'\n"
argument_list|,
name|gdtparams0
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|params
operator|=
name|g_strsplit
argument_list|(
name|gdtparams0
argument_list|,
literal|"}{"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|gdtparams0
argument_list|)
expr_stmt|;
name|data
operator|->
name|new_layer
operator|=
name|FALSE
expr_stmt|;
name|data
operator|->
name|antialias
operator|=
name|atoi
argument_list|(
name|params
index|[
name|ANTIALIAS
index|]
argument_list|)
expr_stmt|;
name|data
operator|->
name|alignment
operator|=
name|atoi
argument_list|(
name|params
index|[
name|ALIGNMENT
index|]
argument_list|)
expr_stmt|;
name|data
operator|->
name|rotation
operator|=
name|atoi
argument_list|(
name|params
index|[
name|ROTATION
index|]
argument_list|)
expr_stmt|;
name|data
operator|->
name|line_spacing
operator|=
name|atoi
argument_list|(
name|params
index|[
name|LINE_SPACING
index|]
argument_list|)
expr_stmt|;
name|data
operator|->
name|layer_alignment
operator|=
name|atoi
argument_list|(
name|params
index|[
name|LAYER_ALIGNMENT
index|]
argument_list|)
expr_stmt|;
name|data
operator|->
name|color
operator|=
name|strtol
argument_list|(
name|params
index|[
name|COLOR
index|]
argument_list|,
operator|(
name|char
operator|*
operator|*
operator|)
name|NULL
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|data
operator|->
name|xlfd
argument_list|,
name|params
index|[
name|XLFD
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|data
operator|->
name|xlfd
argument_list|)
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|data
operator|->
name|text
argument_list|,
name|params
index|[
name|TEXT
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|data
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
block|{
name|gchar
modifier|*
name|text
init|=
name|gimp_strcompress
argument_list|(
name|data
operator|->
name|text
argument_list|)
decl_stmt|;
name|g_snprintf
argument_list|(
name|data
operator|->
name|text
argument_list|,
sizeof|sizeof
argument_list|(
name|data
operator|->
name|text
argument_list|)
argument_list|,
literal|"%s"
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|gdtparams
argument_list|)
expr_stmt|;
name|g_strfreev
argument_list|(
name|params
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gdt_save (GdtVals * data)
name|void
name|gdt_save
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
block|{
name|gchar
modifier|*
name|lname
decl_stmt|,
modifier|*
name|text
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|text
operator|=
name|gimp_strescape
argument_list|(
name|data
operator|->
name|text
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|lname
operator|=
name|g_strdup_printf
argument_list|(
name|GDYNTEXT_MAGIC
literal|"{%s}{%d}{%d}{%d}{%d}{%06X}{%d}{%s}"
argument_list|,
name|text
argument_list|,
name|data
operator|->
name|antialias
argument_list|,
name|data
operator|->
name|alignment
argument_list|,
name|data
operator|->
name|rotation
argument_list|,
name|data
operator|->
name|line_spacing
argument_list|,
name|data
operator|->
name|color
argument_list|,
name|data
operator|->
name|layer_alignment
argument_list|,
name|data
operator|->
name|xlfd
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|GDYNTEXT_PARASITE
argument_list|,
name|PARASITE_PERSISTENT
operator||
name|PARASITE_UNDOABLE
argument_list|,
name|strlen
argument_list|(
name|lname
argument_list|)
argument_list|,
name|lname
argument_list|)
expr_stmt|;
name|gimp_drawable_attach_parasite
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|data
operator|->
name|change_layer_name
condition|)
block|{
name|gimp_layer_set_name
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
name|_
argument_list|(
literal|"GDynText Layer"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|lname
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* change the layer name as in GIMP 1.x */
name|gimp_layer_set_name
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
name|lname
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
name|g_free
argument_list|(
name|lname
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gdt_render_text (GdtVals * data)
name|void
name|gdt_render_text
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|)
block|{
name|gdt_render_text_p
argument_list|(
name|data
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gdt_render_text_p (GdtVals * data,gboolean show_progress)
name|void
name|gdt_render_text_p
parameter_list|(
name|GdtVals
modifier|*
name|data
parameter_list|,
name|gboolean
name|show_progress
parameter_list|)
block|{
name|gint
name|layer_ox
decl_stmt|,
name|layer_oy
decl_stmt|,
name|i
decl_stmt|,
name|nret_vals
decl_stmt|,
name|xoffs
decl_stmt|;
name|gint32
name|layer_f
decl_stmt|,
name|selection_empty
decl_stmt|,
name|selection_channel
init|=
operator|-
literal|1
decl_stmt|;
name|gint32
name|text_width
decl_stmt|,
name|text_height
init|=
literal|0
decl_stmt|;
name|gint32
name|text_ascent
decl_stmt|,
name|text_descent
decl_stmt|;
name|gint32
name|layer_width
decl_stmt|,
name|layer_height
decl_stmt|;
name|gint32
name|image_width
decl_stmt|,
name|image_height
decl_stmt|;
name|gint32
name|space_width
decl_stmt|;
name|gfloat
name|font_size
decl_stmt|;
name|gint32
name|font_size_type
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|text_xlfd
decl_stmt|,
modifier|*
modifier|*
name|text_lines
decl_stmt|;
name|gint32
modifier|*
name|text_lines_w
decl_stmt|;
name|GimpParam
modifier|*
name|ret_vals
decl_stmt|;
name|GimpParamColor
name|old_color
decl_stmt|,
name|text_color
decl_stmt|;
if|if
condition|(
name|show_progress
condition|)
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"GIMP Dynamic Text"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* undo start */
name|gimp_undo_push_group_start
argument_list|(
name|gdtvals
operator|.
name|image_id
argument_list|)
expr_stmt|;
comment|/* save and remove current selection */
name|selection_empty
operator|=
name|gimp_selection_is_empty
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection_empty
operator|==
name|FALSE
condition|)
block|{
comment|/* there is an active selection to save */
name|ret_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_selection_save"
argument_list|,
operator|&
name|nret_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|data
operator|->
name|image_id
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|selection_channel
operator|=
name|ret_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|ret_vals
argument_list|,
name|nret_vals
argument_list|)
expr_stmt|;
name|gimp_selection_none
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
expr_stmt|;
block|}
name|text_xlfd
operator|=
name|g_strsplit
argument_list|(
name|data
operator|->
name|xlfd
argument_list|,
literal|"-"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strlen
argument_list|(
name|text_xlfd
index|[
name|XLFD_PIXEL_SIZE
index|]
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|text_xlfd
index|[
name|XLFD_PIXEL_SIZE
index|]
argument_list|,
literal|"*"
argument_list|)
condition|)
block|{
name|font_size
operator|=
name|atof
argument_list|(
name|text_xlfd
index|[
name|XLFD_POINT_SIZE
index|]
argument_list|)
expr_stmt|;
name|font_size_type
operator|=
name|FONT_METRIC_POINTS
expr_stmt|;
block|}
else|else
block|{
name|font_size
operator|=
name|atof
argument_list|(
name|text_xlfd
index|[
name|XLFD_PIXEL_SIZE
index|]
argument_list|)
expr_stmt|;
name|font_size_type
operator|=
name|FONT_METRIC_PIXELS
expr_stmt|;
block|}
name|g_strfreev
argument_list|(
name|text_xlfd
argument_list|)
expr_stmt|;
comment|/* retrieve space char width */
name|gimp_text_get_extents_fontname
argument_list|(
literal|"AA"
argument_list|,
name|font_size
argument_list|,
name|font_size_type
argument_list|,
name|data
operator|->
name|xlfd
argument_list|,
operator|&
name|text_width
argument_list|,
operator|&
name|text_height
argument_list|,
operator|&
name|text_ascent
argument_list|,
operator|&
name|text_descent
argument_list|)
expr_stmt|;
name|space_width
operator|=
name|text_width
expr_stmt|;
name|gimp_text_get_extents_fontname
argument_list|(
literal|"AA"
argument_list|,
name|font_size
argument_list|,
name|font_size_type
argument_list|,
name|data
operator|->
name|xlfd
argument_list|,
operator|&
name|text_width
argument_list|,
operator|&
name|text_height
argument_list|,
operator|&
name|text_ascent
argument_list|,
operator|&
name|text_descent
argument_list|)
expr_stmt|;
name|space_width
operator|-=
name|text_width
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"GDT: space width = %d\n"
argument_list|,
name|space_width
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* setup text and compute layer size */
name|text_lines
operator|=
name|g_strsplit
argument_list|(
name|data
operator|->
name|text
argument_list|,
literal|"\n"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|text_lines
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
empty_stmt|;
name|text_lines_w
operator|=
name|g_new0
argument_list|(
name|gint32
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|layer_width
operator|=
name|layer_height
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|text_lines
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
name|gimp_text_get_extents_fontname
argument_list|(
name|strlen
argument_list|(
name|text_lines
index|[
name|i
index|]
argument_list|)
operator|>
literal|0
condition|?
name|text_lines
index|[
name|i
index|]
else|:
literal|" "
argument_list|,
name|font_size
argument_list|,
name|font_size_type
argument_list|,
name|data
operator|->
name|xlfd
argument_list|,
operator|&
name|text_width
argument_list|,
operator|&
name|text_height
argument_list|,
operator|&
name|text_ascent
argument_list|,
operator|&
name|text_descent
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"GDT: %4dx%4d A:%3d D:%3d [%s]\n"
argument_list|,
name|text_width
argument_list|,
name|text_height
argument_list|,
name|text_ascent
argument_list|,
name|text_descent
argument_list|,
name|text_lines
index|[
name|i
index|]
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|text_lines_w
index|[
name|i
index|]
operator|=
name|text_width
expr_stmt|;
if|if
condition|(
name|layer_width
operator|<
name|text_width
condition|)
name|layer_width
operator|=
name|text_width
expr_stmt|;
name|layer_height
operator|+=
name|text_height
operator|+
name|data
operator|->
name|line_spacing
expr_stmt|;
block|}
name|layer_height
operator|-=
name|data
operator|->
name|line_spacing
expr_stmt|;
if|if
condition|(
name|layer_height
operator|==
literal|0
condition|)
name|layer_height
operator|=
literal|10
expr_stmt|;
if|if
condition|(
name|layer_width
operator|==
literal|0
condition|)
name|layer_width
operator|=
literal|10
expr_stmt|;
if|if
condition|(
operator|!
name|data
operator|->
name|new_layer
condition|)
block|{
comment|/* resize the old layer */
name|gimp_layer_resize
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
name|layer_width
argument_list|,
name|layer_height
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* create a new layer */
name|data
operator|->
name|layer_id
operator|=
name|data
operator|->
name|drawable_id
operator|=
name|gimp_layer_new
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
name|_
argument_list|(
literal|"GDynText Layer "
argument_list|)
argument_list|,
name|layer_width
argument_list|,
name|layer_height
argument_list|,
call|(
name|GDrawableType
call|)
argument_list|(
name|gimp_image_base_type
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
operator|*
literal|2
operator|+
literal|1
argument_list|)
argument_list|,
literal|100.0
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|gimp_layer_add_alpha
argument_list|(
name|data
operator|->
name|layer_id
argument_list|)
expr_stmt|;
name|gimp_image_add_layer
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
name|data
operator|->
name|layer_id
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_set_active_layer
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
name|data
operator|->
name|layer_id
argument_list|)
expr_stmt|;
block|}
comment|/* clear layer */
name|gimp_layer_set_preserve_transparency
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_edit_clear
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
comment|/* get layer offsets */
name|gimp_drawable_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
operator|&
name|layer_ox
argument_list|,
operator|&
name|layer_oy
argument_list|)
expr_stmt|;
comment|/* get foreground color */
name|gimp_palette_get_foreground
argument_list|(
operator|&
name|old_color
operator|.
name|red
argument_list|,
operator|&
name|old_color
operator|.
name|green
argument_list|,
operator|&
name|old_color
operator|.
name|blue
argument_list|)
expr_stmt|;
comment|/* set foreground color to the wanted text color */
name|text_color
operator|.
name|red
operator|=
operator|(
name|data
operator|->
name|color
operator|&
literal|0xff0000
operator|)
operator|>>
literal|16
expr_stmt|;
name|text_color
operator|.
name|green
operator|=
operator|(
name|data
operator|->
name|color
operator|&
literal|0xff00
operator|)
operator|>>
literal|8
expr_stmt|;
name|text_color
operator|.
name|blue
operator|=
name|data
operator|->
name|color
operator|&
literal|0xff
expr_stmt|;
name|gimp_palette_set_foreground
argument_list|(
name|text_color
operator|.
name|red
argument_list|,
name|text_color
operator|.
name|green
argument_list|,
name|text_color
operator|.
name|blue
argument_list|)
expr_stmt|;
comment|/* write text */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|text_lines
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
switch|switch
condition|(
name|data
operator|->
name|alignment
condition|)
block|{
case|case
name|LEFT
case|:
name|xoffs
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|RIGHT
case|:
name|xoffs
operator|=
name|layer_width
operator|-
name|text_lines_w
index|[
name|i
index|]
expr_stmt|;
break|break;
case|case
name|CENTER
case|:
name|xoffs
operator|=
operator|(
name|layer_width
operator|-
name|text_lines_w
index|[
name|i
index|]
operator|)
operator|/
literal|2
expr_stmt|;
break|break;
default|default:
name|xoffs
operator|=
literal|0
expr_stmt|;
block|}
name|layer_f
operator|=
name|gimp_text_fontname
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
name|data
operator|->
name|drawable_id
argument_list|,
operator|(
name|gdouble
operator|)
name|layer_ox
operator|+
name|strspn
argument_list|(
name|text_lines
index|[
name|i
index|]
argument_list|,
literal|" "
argument_list|)
operator|*
name|space_width
operator|+
name|xoffs
argument_list|,
comment|/* x */
operator|(
name|gdouble
operator|)
name|layer_oy
operator|+
name|i
operator|*
operator|(
name|text_height
operator|+
name|data
operator|->
name|line_spacing
operator|)
argument_list|,
comment|/* y */
name|text_lines
index|[
name|i
index|]
argument_list|,
literal|0
argument_list|,
comment|/* border */
name|data
operator|->
name|antialias
argument_list|,
name|font_size
argument_list|,
name|font_size_type
argument_list|,
name|data
operator|->
name|xlfd
argument_list|)
expr_stmt|;
comment|/* FIXME: ascent/descent stuff, use gimp_layer_translate */
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"GDT: MH:%d LH:%d\n"
argument_list|,
name|text_height
argument_list|,
name|gimp_drawable_height
argument_list|(
name|layer_f
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_floating_sel_anchor
argument_list|(
name|layer_f
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_progress
condition|)
name|gimp_progress_update
argument_list|(
call|(
name|double
call|)
argument_list|(
name|i
operator|+
literal|2
argument_list|)
operator|*
literal|100.0
operator|*
operator|(
name|double
operator|)
name|text_height
operator|/
operator|(
name|double
operator|)
name|layer_height
argument_list|)
expr_stmt|;
block|}
name|g_strfreev
argument_list|(
name|text_lines
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text_lines_w
argument_list|)
expr_stmt|;
comment|/* set foreground color to the old one */
name|gimp_palette_set_foreground
argument_list|(
name|old_color
operator|.
name|red
argument_list|,
name|old_color
operator|.
name|green
argument_list|,
name|old_color
operator|.
name|blue
argument_list|)
expr_stmt|;
comment|/* apply rotation */
if|if
condition|(
name|data
operator|->
name|rotation
operator|!=
literal|0
operator|&&
name|abs
argument_list|(
name|data
operator|->
name|rotation
argument_list|)
operator|!=
literal|360
condition|)
block|{
name|gimp_rotate
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|,
operator|(
name|gdouble
operator|)
name|data
operator|->
name|rotation
operator|*
name|G_PI
operator|/
literal|180.0
argument_list|)
expr_stmt|;
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
name|layer_ox
argument_list|,
name|layer_oy
argument_list|)
expr_stmt|;
block|}
comment|/* sets the layer alignment */
name|layer_width
operator|=
name|gimp_drawable_width
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|layer_height
operator|=
name|gimp_drawable_height
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|image_width
operator|=
name|gimp_image_width
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_image_height
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|data
operator|->
name|layer_alignment
condition|)
block|{
case|case
name|LA_TOP_LEFT
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_TOP_CENTER
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
operator|(
name|image_width
operator|-
name|layer_width
operator|)
operator|>>
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_TOP_RIGHT
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
name|image_width
operator|-
name|layer_width
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_MIDDLE_LEFT
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
literal|0
argument_list|,
operator|(
name|image_height
operator|-
name|layer_height
operator|)
operator|>>
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_CENTER
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
operator|(
name|image_width
operator|-
name|layer_width
operator|)
operator|>>
literal|1
argument_list|,
operator|(
name|image_height
operator|-
name|layer_height
operator|)
operator|>>
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_MIDDLE_RIGHT
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
name|image_width
operator|-
name|layer_width
argument_list|,
operator|(
name|image_height
operator|-
name|layer_height
operator|)
operator|>>
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_BOTTOM_LEFT
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
literal|0
argument_list|,
name|image_height
operator|-
name|layer_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_BOTTOM_CENTER
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
operator|(
name|image_width
operator|-
name|layer_width
operator|)
operator|>>
literal|1
argument_list|,
name|image_height
operator|-
name|layer_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_BOTTOM_RIGHT
case|:
name|gimp_layer_set_offsets
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
name|image_width
operator|-
name|layer_width
argument_list|,
name|image_height
operator|-
name|layer_height
argument_list|)
expr_stmt|;
break|break;
case|case
name|LA_NONE
case|:
default|default:
block|}
name|gimp_layer_set_preserve_transparency
argument_list|(
name|data
operator|->
name|layer_id
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/* restore old selection if any */
if|if
condition|(
name|selection_empty
operator|==
name|FALSE
condition|)
block|{
name|ret_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_selection_load"
argument_list|,
operator|&
name|nret_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|data
operator|->
name|image_id
argument_list|,
name|PARAM_CHANNEL
argument_list|,
name|selection_channel
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|ret_vals
argument_list|,
name|nret_vals
argument_list|)
expr_stmt|;
name|gimp_image_remove_channel
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
name|selection_channel
argument_list|)
expr_stmt|;
block|}
name|gdt_save
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/* undo end */
name|gimp_undo_push_group_end
argument_list|(
name|gdtvals
operator|.
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|show_progress
condition|)
name|gimp_progress_update
argument_list|(
literal|100.0
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit

