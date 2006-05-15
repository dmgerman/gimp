begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfontlist.c  * Copyright (C) 2003-2004  Michael Natterer<mitch@gimp.org>  *                          Sven Neumann<sven@gimp.org>  *                          Manish Singh<yosh@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangoft2.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangofc-fontmap.h>
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpfont.h"
end_include

begin_include
include|#
directive|include
file|"gimpfont-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpfontlist.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* Use fontconfig directly for speed. We can use the pango stuff when/if  * fontconfig/pango get more efficient.  */
end_comment

begin_define
DECL|macro|USE_FONTCONFIG_DIRECTLY
define|#
directive|define
name|USE_FONTCONFIG_DIRECTLY
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|USE_FONTCONFIG_DIRECTLY
end_ifdef

begin_comment
comment|/* PangoFT2 is assumed, so we should have this in our cflags */
end_comment

begin_include
include|#
directive|include
file|<fontconfig/fontconfig.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|GimpFontDescToStringFunc
typedef|typedef
name|char
modifier|*
function_decl|(
modifier|*
name|GimpFontDescToStringFunc
function_decl|)
parameter_list|(
specifier|const
name|PangoFontDescription
modifier|*
name|desc
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
specifier|static
name|void
name|gimp_font_list_add_font
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|,
name|PangoFontDescription
modifier|*
name|desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_font_list_load_names
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|,
name|PangoFontMap
modifier|*
name|fontmap
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFontList
argument_list|,
argument|gimp_font_list
argument_list|,
argument|GIMP_TYPE_LIST
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|GimpFontDescToStringFunc
name|font_desc_to_string
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_class_init (GimpFontListClass * klass)
name|gimp_font_list_class_init
parameter_list|(
name|GimpFontListClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_init (GimpFontList * list)
name|gimp_font_list_init
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|)
block|{ }
end_function

begin_function
name|GimpContainer
modifier|*
DECL|function|gimp_font_list_new (gdouble xresolution,gdouble yresolution)
name|gimp_font_list_new
parameter_list|(
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|)
block|{
name|GimpFontList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|xresolution
operator|>
literal|0.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|yresolution
operator|>
literal|0.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FONT_LIST
argument_list|,
literal|"children_type"
argument_list|,
name|GIMP_TYPE_FONT
argument_list|,
literal|"policy"
argument_list|,
name|GIMP_CONTAINER_POLICY_STRONG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|list
operator|->
name|xresolution
operator|=
name|xresolution
expr_stmt|;
name|list
operator|->
name|yresolution
operator|=
name|yresolution
expr_stmt|;
return|return
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_font_list_restore (GimpFontList * list)
name|gimp_font_list_restore
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|)
block|{
name|PangoFontMap
modifier|*
name|fontmap
decl_stmt|;
name|PangoContext
modifier|*
name|context
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FONT_LIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|font_desc_to_string
operator|==
name|NULL
condition|)
block|{
name|PangoFontDescription
modifier|*
name|desc
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
name|last_char
decl_stmt|;
name|desc
operator|=
name|pango_font_description_new
argument_list|()
expr_stmt|;
name|pango_font_description_set_family
argument_list|(
name|desc
argument_list|,
literal|"Wilber 12"
argument_list|)
expr_stmt|;
name|name
operator|=
name|pango_font_description_to_string
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|last_char
operator|=
name|name
index|[
name|strlen
argument_list|(
name|name
argument_list|)
operator|-
literal|1
index|]
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
if|if
condition|(
name|last_char
operator|!=
literal|','
condition|)
name|font_desc_to_string
operator|=
operator|&
name|gimp_font_util_pango_font_description_to_string
expr_stmt|;
else|else
name|font_desc_to_string
operator|=
operator|&
name|pango_font_description_to_string
expr_stmt|;
block|}
name|fontmap
operator|=
name|pango_ft2_font_map_new
argument_list|()
expr_stmt|;
name|pango_ft2_font_map_set_resolution
argument_list|(
name|PANGO_FT2_FONT_MAP
argument_list|(
name|fontmap
argument_list|)
argument_list|,
name|list
operator|->
name|xresolution
argument_list|,
name|list
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|context
operator|=
name|pango_ft2_font_map_create_context
argument_list|(
name|PANGO_FT2_FONT_MAP
argument_list|(
name|fontmap
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|fontmap
argument_list|)
expr_stmt|;
name|gimp_container_freeze
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_font_list_load_names
argument_list|(
name|list
argument_list|,
name|fontmap
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gimp_list_sort_by_name
argument_list|(
name|GIMP_LIST
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_container_thaw
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_add_font (GimpFontList * list,PangoContext * context,PangoFontDescription * desc)
name|gimp_font_list_add_font
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|,
name|PangoFontDescription
modifier|*
name|desc
parameter_list|)
block|{
name|GimpFont
modifier|*
name|font
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
if|if
condition|(
operator|!
name|desc
condition|)
return|return;
name|name
operator|=
name|font_desc_to_string
argument_list|(
name|desc
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
return|return;
block|}
name|font
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FONT
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
literal|"pango-context"
argument_list|,
name|context
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|gimp_container_add
argument_list|(
name|GIMP_CONTAINER
argument_list|(
name|list
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|font
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|font
argument_list|)
expr_stmt|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|USE_FONTCONFIG_DIRECTLY
end_ifdef

begin_comment
comment|/* We're really chummy here with the implementation. Oh well. */
end_comment

begin_comment
comment|/* This is copied straight from make_alias_description in pango, plus  * the gimp_font_list_add_font bits.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_make_alias (GimpFontList * list,PangoContext * context,const gchar * family,gboolean bold,gboolean italic)
name|gimp_font_list_make_alias
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|family
parameter_list|,
name|gboolean
name|bold
parameter_list|,
name|gboolean
name|italic
parameter_list|)
block|{
name|PangoFontDescription
modifier|*
name|desc
init|=
name|pango_font_description_new
argument_list|()
decl_stmt|;
name|pango_font_description_set_family
argument_list|(
name|desc
argument_list|,
name|family
argument_list|)
expr_stmt|;
name|pango_font_description_set_style
argument_list|(
name|desc
argument_list|,
name|italic
condition|?
name|PANGO_STYLE_ITALIC
else|:
name|PANGO_STYLE_NORMAL
argument_list|)
expr_stmt|;
name|pango_font_description_set_variant
argument_list|(
name|desc
argument_list|,
name|PANGO_VARIANT_NORMAL
argument_list|)
expr_stmt|;
name|pango_font_description_set_weight
argument_list|(
name|desc
argument_list|,
name|bold
condition|?
name|PANGO_WEIGHT_BOLD
else|:
name|PANGO_WEIGHT_NORMAL
argument_list|)
expr_stmt|;
name|pango_font_description_set_stretch
argument_list|(
name|desc
argument_list|,
name|PANGO_STRETCH_NORMAL
argument_list|)
expr_stmt|;
name|gimp_font_list_add_font
argument_list|(
name|list
argument_list|,
name|context
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_load_aliases (GimpFontList * list,PangoContext * context)
name|gimp_font_list_load_aliases
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|families
index|[]
init|=
block|{
literal|"Sans"
block|,
literal|"Serif"
block|,
literal|"Monospace"
block|}
decl_stmt|;
name|gint
name|i
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
block|{
name|gimp_font_list_make_alias
argument_list|(
name|list
argument_list|,
name|context
argument_list|,
name|families
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_font_list_make_alias
argument_list|(
name|list
argument_list|,
name|context
argument_list|,
name|families
index|[
name|i
index|]
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_font_list_make_alias
argument_list|(
name|list
argument_list|,
name|context
argument_list|,
name|families
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_font_list_make_alias
argument_list|(
name|list
argument_list|,
name|context
argument_list|,
name|families
index|[
name|i
index|]
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_load_names (GimpFontList * list,PangoFontMap * fontmap,PangoContext * context)
name|gimp_font_list_load_names
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|,
name|PangoFontMap
modifier|*
name|fontmap
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|)
block|{
name|FcObjectSet
modifier|*
name|os
decl_stmt|;
name|FcPattern
modifier|*
name|pat
decl_stmt|;
name|FcFontSet
modifier|*
name|fontset
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|os
operator|=
name|FcObjectSetBuild
argument_list|(
name|FC_FAMILY
argument_list|,
name|FC_STYLE
argument_list|,
name|FC_SLANT
argument_list|,
name|FC_WEIGHT
argument_list|,
name|FC_WIDTH
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pat
operator|=
name|FcPatternCreate
argument_list|()
expr_stmt|;
name|fontset
operator|=
name|FcFontList
argument_list|(
name|NULL
argument_list|,
name|pat
argument_list|,
name|os
argument_list|)
expr_stmt|;
name|FcPatternDestroy
argument_list|(
name|pat
argument_list|)
expr_stmt|;
name|FcObjectSetDestroy
argument_list|(
name|os
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
name|fontset
operator|->
name|nfont
condition|;
name|i
operator|++
control|)
block|{
name|PangoFontDescription
modifier|*
name|desc
decl_stmt|;
name|desc
operator|=
name|pango_fc_font_description_from_pattern
argument_list|(
name|fontset
operator|->
name|fonts
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_font_list_add_font
argument_list|(
name|list
argument_list|,
name|context
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
comment|/*  only create aliases if there is at least one font available  */
if|if
condition|(
name|fontset
operator|->
name|nfont
operator|>
literal|0
condition|)
name|gimp_font_list_load_aliases
argument_list|(
name|list
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|FcFontSetDestroy
argument_list|(
name|fontset
argument_list|)
expr_stmt|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* ! USE_FONTCONFIG_DIRECTLY */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_font_list_load_names (GimpFontList * list,PangoFontMap * fontmap,PangoContext * context)
name|gimp_font_list_load_names
parameter_list|(
name|GimpFontList
modifier|*
name|list
parameter_list|,
name|PangoFontMap
modifier|*
name|fontmap
parameter_list|,
name|PangoContext
modifier|*
name|context
parameter_list|)
block|{
name|PangoFontFamily
modifier|*
modifier|*
name|families
decl_stmt|;
name|PangoFontFace
modifier|*
modifier|*
name|faces
decl_stmt|;
name|gint
name|n_families
decl_stmt|;
name|gint
name|n_faces
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|pango_font_map_list_families
argument_list|(
name|fontmap
argument_list|,
operator|&
name|families
argument_list|,
operator|&
name|n_families
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
name|n_families
condition|;
name|i
operator|++
control|)
block|{
name|pango_font_family_list_faces
argument_list|(
name|families
index|[
name|i
index|]
argument_list|,
operator|&
name|faces
argument_list|,
operator|&
name|n_faces
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
name|n_faces
condition|;
name|j
operator|++
control|)
block|{
name|PangoFontDescription
modifier|*
name|desc
decl_stmt|;
name|desc
operator|=
name|pango_font_face_describe
argument_list|(
name|faces
index|[
name|j
index|]
argument_list|)
expr_stmt|;
name|gimp_font_list_add_font
argument_list|(
name|list
argument_list|,
name|context
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|pango_font_description_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|families
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* USE_FONTCONFIG_DIRECTLY */
end_comment

end_unit

