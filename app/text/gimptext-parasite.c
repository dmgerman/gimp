begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-parasite.h"
end_include

begin_include
include|#
directive|include
file|"gimptext-xlfd.h"
end_include

begin_comment
comment|/****************************************/
end_comment

begin_comment
comment|/*  The native GimpTextLayer parasite.  */
end_comment

begin_comment
comment|/****************************************/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_text_parasite_name (void)
name|gimp_text_parasite_name
parameter_list|(
name|void
parameter_list|)
block|{
return|return
literal|"gimp-text-layer"
return|;
block|}
end_function

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_text_to_parasite (const GimpText * text)
name|gimp_text_to_parasite
parameter_list|(
specifier|const
name|GimpText
modifier|*
name|text
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TEXT
argument_list|(
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|gimp_config_serialize_to_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|text
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|str
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
name|gimp_text_parasite_name
argument_list|()
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|str
argument_list|)
operator|+
literal|1
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
return|return
name|parasite
return|;
block|}
end_function

begin_function
name|GimpText
modifier|*
DECL|function|gimp_text_from_parasite (const GimpParasite * parasite,GError ** error)
name|gimp_text_from_parasite
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpText
modifier|*
name|text
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parasite
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|strcmp
argument_list|(
name|gimp_parasite_name
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_text_parasite_name
argument_list|()
argument_list|)
operator|==
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|str
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_config_deserialize_string
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|text
argument_list|)
argument_list|,
name|str
argument_list|,
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
expr_stmt|;
return|return
name|text
return|;
block|}
end_function

begin_comment
comment|/****************************************************************/
end_comment

begin_comment
comment|/*  Compatibility to plug-in GDynText 1.4.4 and later versions  */
end_comment

begin_comment
comment|/*  GDynText was written by Marco Lamberto<lm@geocities.com>   */
end_comment

begin_comment
comment|/****************************************************************/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_text_gdyntext_parasite_name (void)
name|gimp_text_gdyntext_parasite_name
parameter_list|(
name|void
parameter_list|)
block|{
return|return
literal|"plug_in_gdyntext/data"
return|;
block|}
end_function

begin_enum
enum|enum
DECL|enum|__anon2c3b3fdd0103
block|{
DECL|enumerator|TEXT
name|TEXT
init|=
literal|0
block|,
DECL|enumerator|ANTIALIAS
name|ANTIALIAS
init|=
literal|1
block|,
DECL|enumerator|ALIGNMENT
name|ALIGNMENT
init|=
literal|2
block|,
DECL|enumerator|ROTATION
name|ROTATION
init|=
literal|3
block|,
DECL|enumerator|LINE_SPACING
name|LINE_SPACING
init|=
literal|4
block|,
DECL|enumerator|COLOR
name|COLOR
init|=
literal|5
block|,
DECL|enumerator|LAYER_ALIGNMENT
name|LAYER_ALIGNMENT
init|=
literal|6
block|,
DECL|enumerator|XLFD
name|XLFD
init|=
literal|7
block|,
DECL|enumerator|NUM_PARAMS
name|NUM_PARAMS
block|}
enum|;
end_enum

begin_function
name|GimpText
modifier|*
DECL|function|gimp_text_from_gdyntext_parasite (const GimpParasite * parasite)
name|gimp_text_from_gdyntext_parasite
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
name|GimpText
modifier|*
name|retval
init|=
name|NULL
decl_stmt|;
name|GimpTextJustification
name|justify
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|str
decl_stmt|;
name|gchar
modifier|*
name|text
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|params
decl_stmt|;
name|gboolean
name|antialias
decl_stmt|;
name|gdouble
name|spacing
decl_stmt|;
name|GimpRGB
name|rgb
decl_stmt|;
name|glong
name|color
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parasite
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|strcmp
argument_list|(
name|gimp_parasite_name
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_text_gdyntext_parasite_name
argument_list|()
argument_list|)
operator|==
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|str
operator|=
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|str
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_str_has_prefix
argument_list|(
name|str
argument_list|,
literal|"GDT10{"
argument_list|)
condition|)
comment|/*  magic value  */
return|return
name|NULL
return|;
name|params
operator|=
name|g_strsplit
argument_list|(
name|str
operator|+
name|strlen
argument_list|(
literal|"GDT10{"
argument_list|)
argument_list|,
literal|"}{"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*  first check that we have the required number of parameters  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|NUM_PARAMS
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|!
name|params
index|[
name|i
index|]
condition|)
goto|goto
name|cleanup
goto|;
name|text
operator|=
name|g_strcompress
argument_list|(
name|params
index|[
name|TEXT
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|tmp
init|=
name|gimp_any_to_utf8
argument_list|(
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|text
operator|=
name|tmp
expr_stmt|;
block|}
name|antialias
operator|=
name|atoi
argument_list|(
name|params
index|[
name|ANTIALIAS
index|]
argument_list|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
switch|switch
condition|(
name|atoi
argument_list|(
name|params
index|[
name|ALIGNMENT
index|]
argument_list|)
condition|)
block|{
default|default:
case|case
literal|0
case|:
name|justify
operator|=
name|GIMP_TEXT_JUSTIFY_LEFT
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|justify
operator|=
name|GIMP_TEXT_JUSTIFY_CENTER
expr_stmt|;
break|break;
case|case
literal|2
case|:
name|justify
operator|=
name|GIMP_TEXT_JUSTIFY_RIGHT
expr_stmt|;
break|break;
block|}
name|spacing
operator|=
name|atof
argument_list|(
name|params
index|[
name|LINE_SPACING
index|]
argument_list|)
expr_stmt|;
name|color
operator|=
name|strtol
argument_list|(
name|params
index|[
name|COLOR
index|]
argument_list|,
name|NULL
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|rgb
argument_list|,
name|color
operator|>>
literal|16
argument_list|,
name|color
operator|>>
literal|8
argument_list|,
name|color
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|retval
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TEXT
argument_list|,
literal|"text"
argument_list|,
name|text
argument_list|,
literal|"antialias"
argument_list|,
name|antialias
argument_list|,
literal|"justify"
argument_list|,
name|justify
argument_list|,
literal|"line-spacing"
argument_list|,
name|spacing
argument_list|,
literal|"color"
argument_list|,
operator|&
name|rgb
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_text_set_font_from_xlfd
argument_list|(
name|GIMP_TEXT
argument_list|(
name|retval
argument_list|)
argument_list|,
name|params
index|[
name|XLFD
index|]
argument_list|)
expr_stmt|;
name|cleanup
label|:
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_strfreev
argument_list|(
name|params
argument_list|)
expr_stmt|;
return|return
name|retval
return|;
block|}
end_function

end_unit

