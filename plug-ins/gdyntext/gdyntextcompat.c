begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * GIMP Dynamic Text -- This is a plug-in for The GIMP 1.0  * Copyright (C) 1998,1999,2000 Marco Lamberto<lm@geocities.com>  * Web page: http://www.geocities.com/Tokyo/1474/gimp/  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  * $Id$  */
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
file|"gdyntext.h"
end_include

begin_include
include|#
directive|include
file|"font_selection.h"
end_include

begin_function
DECL|function|gdt_compat_load (GdtVals * data)
name|gboolean
name|gdt_compat_load
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
name|gchar
name|font_family
index|[
literal|1024
index|]
decl_stmt|;
name|gchar
name|font_style
index|[
literal|1024
index|]
decl_stmt|;
name|gint
name|font_size
decl_stmt|;
name|gint
name|font_metric
decl_stmt|;
name|GimpParasite
modifier|*
name|parasite
init|=
name|NULL
decl_stmt|;
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
name|GDYNTEXT_PARASITE_144
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
comment|/* GDynText 1.4.4 - xxxxx uses one parasite */
name|gdtparams
operator|=
name|strdup
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
elseif|else
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
name|GDYNTEXT_PARASITE_131
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
comment|/* GDynText 1.3.1 - 1.4.3 uses one parasite */
name|gdtparams
operator|=
name|strdup
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
elseif|else
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
name|GDYNTEXT_PARASITE_130_MAGIC
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
comment|/* GDynText 1.3.0 uses too parasites and no serialization!! */
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_TEXT
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|data
operator|->
name|text
argument_list|,
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
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
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_FONT_FAMILY
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|font_family
argument_list|,
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
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
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_FONT_STYLE
argument_list|)
expr_stmt|;
name|strncpy
argument_list|(
name|font_style
argument_list|,
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_data_size
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
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_FONT_SIZE
argument_list|)
expr_stmt|;
name|font_size
operator|=
operator|*
operator|(
name|gint32
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_FONT_METRIC
argument_list|)
expr_stmt|;
name|font_metric
operator|=
operator|*
operator|(
name|gint
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_FONT_COLOR
argument_list|)
expr_stmt|;
name|data
operator|->
name|color
operator|=
operator|*
operator|(
name|gint32
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_ANTIALIAS
argument_list|)
expr_stmt|;
name|data
operator|->
name|antialias
operator|=
operator|*
operator|(
name|gboolean
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_ALIGNMENT
argument_list|)
expr_stmt|;
name|data
operator|->
name|alignment
operator|=
operator|*
operator|(
name|GdtAlign
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_ROTATION
argument_list|)
expr_stmt|;
name|data
operator|->
name|rotation
operator|=
operator|*
operator|(
name|gint
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_drawable_parasite_find
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|,
name|GDYNTEXT_PARASITE_130_PREVIEW
argument_list|)
expr_stmt|;
name|data
operator|->
name|preview
operator|=
operator|*
operator|(
name|gboolean
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
comment|/* FIXME: don't exit here!! */
return|return
name|TRUE
return|;
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
operator|||
name|GDT_MAGIC_REV
argument_list|(
name|gdtparams
argument_list|)
operator|==
name|GDT_MAGIC_REV
argument_list|(
name|GDYNTEXT_MAGIC
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
elseif|else
if|if
condition|(
name|GDT_MAGIC_REV
argument_list|(
name|gdtparams
argument_list|)
operator|>
name|GDT_MAGIC_REV
argument_list|(
name|GDYNTEXT_MAGIC
argument_list|)
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
literal|" WARNING: GDynText is too old!"
literal|" A newer version is required to handle this layer."
literal|" Get it from "
name|GDYNTEXT_WEB_PAGE
literal|""
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|gdtparams0
operator|=
name|g_strndup
argument_list|(
name|gdtparams
operator|+
literal|6
argument_list|,
name|strlen
argument_list|(
name|gdtparams
argument_list|)
operator|-
literal|7
argument_list|)
expr_stmt|;
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
name|color
operator|=
name|strtol
argument_list|(
name|params
index|[
name|C_FONT_COLOR
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
name|data
operator|->
name|antialias
operator|=
name|atoi
argument_list|(
name|params
index|[
name|C_ANTIALIAS
index|]
argument_list|)
expr_stmt|;
name|font_size
operator|=
name|atoi
argument_list|(
name|params
index|[
name|C_FONT_SIZE
index|]
argument_list|)
expr_stmt|;
name|font_metric
operator|=
name|atoi
argument_list|(
name|params
index|[
name|C_FONT_SIZE_T
index|]
argument_list|)
expr_stmt|;
comment|/* older GDT< 0.6 formats don't have alignment */
name|data
operator|->
name|alignment
operator|=
name|GDT_MAGIC_REV
argument_list|(
name|gdtparams
argument_list|)
operator|<
literal|6
condition|?
name|LEFT
else|:
name|atoi
argument_list|(
name|params
index|[
name|C_ALIGNMENT
index|]
argument_list|)
expr_stmt|;
comment|/* older GDT< 0.7 formats don't have rotation */
name|data
operator|->
name|rotation
operator|=
name|GDT_MAGIC_REV
argument_list|(
name|gdtparams
argument_list|)
operator|<
literal|7
condition|?
literal|0
else|:
name|atoi
argument_list|(
name|params
index|[
name|C_ROTATION
index|]
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
name|C_TEXT
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
name|strunescape
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
name|strncpy
argument_list|(
name|font_family
argument_list|,
name|params
index|[
name|C_FONT_FAMILY
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|font_family
argument_list|)
argument_list|)
expr_stmt|;
comment|/* older GDT< 0.8 formats don't have font style */
name|strncpy
argument_list|(
name|font_style
argument_list|,
operator|(
name|GDT_MAGIC_REV
argument_list|(
name|gdtparams
argument_list|)
operator|<
literal|8
condition|?
literal|""
else|:
name|params
index|[
name|C_FONT_STYLE
index|]
operator|)
argument_list|,
sizeof|sizeof
argument_list|(
name|font_style
argument_list|)
argument_list|)
expr_stmt|;
comment|/* older GDT< 0.9 formats don't have line spacing */
name|data
operator|->
name|line_spacing
operator|=
name|GDT_MAGIC_REV
argument_list|(
name|gdtparams
argument_list|)
operator|<
literal|9
condition|?
literal|0
else|:
name|atoi
argument_list|(
name|params
index|[
name|C_SPACING
index|]
argument_list|)
expr_stmt|;
comment|/* GDT<= 0.9 doesn't have layer alignment */
name|data
operator|->
name|layer_alignment
operator|=
name|LA_NONE
expr_stmt|;
name|g_snprintf
argument_list|(
name|data
operator|->
name|xlfd
argument_list|,
sizeof|sizeof
argument_list|(
name|data
operator|->
name|xlfd
argument_list|)
argument_list|,
name|font_metric
operator|==
name|FONT_METRIC_PIXELS
condition|?
literal|"-*-%s-%s-*-%d-*-*-*-*-*-*-*"
else|:
literal|"-*-%s-%s-*-*-%d-*-*-*-*-*-*"
argument_list|,
name|font_family
argument_list|,
name|font_style
argument_list|,
name|font_metric
operator|==
name|FONT_METRIC_PIXELS
condition|?
name|font_size
else|:
name|font_size
operator|*
literal|10
argument_list|)
expr_stmt|;
if|if
condition|(
name|GDT_MAGIC_REV
argument_list|(
name|gdtparams
argument_list|)
operator|<
name|GDT_MAGIC_REV
argument_list|(
name|GDYNTEXT_MAGIC
argument_list|)
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
literal|" Upgrading old GDynText layer to "
name|GDYNTEXT_MAGIC
literal|"."
argument_list|)
argument_list|)
expr_stmt|;
block|}
ifdef|#
directive|ifdef
name|DEBUG
name|printf
argument_list|(
literal|"gdt_compat_load:\n  '%s'\n  '%s'\n"
argument_list|,
name|gdtparams
argument_list|,
name|data
operator|->
name|xlfd
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|g_free
argument_list|(
name|gdtparams
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/* vim: set ts=2 sw=2 tw=79 ai nowrap: */
end_comment

end_unit

