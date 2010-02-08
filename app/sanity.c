begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<fontconfig/fontconfig.h>
end_include

begin_include
include|#
directive|include
file|<pango/pango.h>
end_include

begin_include
include|#
directive|include
file|<pango/pangoft2.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"sanity.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|gchar
modifier|*
name|sanity_check_gimp
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|sanity_check_glib
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|sanity_check_pango
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|sanity_check_fontconfig
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|sanity_check_freetype
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|sanity_check_babl
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|sanity_check_gegl
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|sanity_check_filename_encoding
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|sanity_check (void)
name|sanity_check
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|abort_message
init|=
name|sanity_check_gimp
argument_list|()
decl_stmt|;
if|if
condition|(
operator|!
name|abort_message
condition|)
name|abort_message
operator|=
name|sanity_check_glib
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|abort_message
condition|)
name|abort_message
operator|=
name|sanity_check_pango
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|abort_message
condition|)
name|abort_message
operator|=
name|sanity_check_fontconfig
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|abort_message
condition|)
name|abort_message
operator|=
name|sanity_check_freetype
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|abort_message
condition|)
name|abort_message
operator|=
name|sanity_check_babl
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|abort_message
condition|)
name|abort_message
operator|=
name|sanity_check_gegl
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|abort_message
condition|)
name|abort_message
operator|=
name|sanity_check_filename_encoding
argument_list|()
expr_stmt|;
return|return
name|abort_message
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|sanity_check_version (guint major_version,guint required_major,guint minor_version,guint required_minor,guint micro_version,guint required_micro)
name|sanity_check_version
parameter_list|(
name|guint
name|major_version
parameter_list|,
name|guint
name|required_major
parameter_list|,
name|guint
name|minor_version
parameter_list|,
name|guint
name|required_minor
parameter_list|,
name|guint
name|micro_version
parameter_list|,
name|guint
name|required_micro
parameter_list|)
block|{
if|if
condition|(
name|major_version
operator|>
name|required_major
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
name|major_version
operator|<
name|required_major
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|minor_version
operator|>
name|required_minor
condition|)
return|return
name|TRUE
return|;
if|if
condition|(
name|minor_version
operator|<
name|required_minor
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
name|micro_version
operator|>=
name|required_micro
condition|)
return|return
name|TRUE
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|sanity_check_gimp (void)
name|sanity_check_gimp
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|GIMP_MAJOR_VERSION
operator|!=
name|gimp_major_version
operator|||
name|GIMP_MINOR_VERSION
operator|!=
name|gimp_minor_version
operator|||
name|GIMP_MICRO_VERSION
operator|!=
name|gimp_micro_version
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"Libgimp version mismatch!\n\n"
literal|"The GIMP binary cannot run with a libgimp version\n"
literal|"other than its own. This is GIMP %d.%d.%d, but the\n"
literal|"libgimp version is %d.%d.%d.\n\n"
literal|"Maybe you have GIMP versions in both /usr and /usr/local ?"
argument_list|,
name|GIMP_MAJOR_VERSION
argument_list|,
name|GIMP_MINOR_VERSION
argument_list|,
name|GIMP_MICRO_VERSION
argument_list|,
name|gimp_major_version
argument_list|,
name|gimp_minor_version
argument_list|,
name|gimp_micro_version
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|sanity_check_glib (void)
name|sanity_check_glib
parameter_list|(
name|void
parameter_list|)
block|{
DECL|macro|GLIB_REQUIRED_MAJOR
define|#
directive|define
name|GLIB_REQUIRED_MAJOR
value|2
DECL|macro|GLIB_REQUIRED_MINOR
define|#
directive|define
name|GLIB_REQUIRED_MINOR
value|22
DECL|macro|GLIB_REQUIRED_MICRO
define|#
directive|define
name|GLIB_REQUIRED_MICRO
value|0
specifier|const
name|gchar
modifier|*
name|mismatch
init|=
name|glib_check_version
argument_list|(
name|GLIB_REQUIRED_MAJOR
argument_list|,
name|GLIB_REQUIRED_MINOR
argument_list|,
name|GLIB_REQUIRED_MICRO
argument_list|)
decl_stmt|;
if|if
condition|(
name|mismatch
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"%s\n\n"
literal|"GIMP requires GLib version %d.%d.%d or later.\n"
literal|"Installed GLib version is %d.%d.%d.\n\n"
literal|"Somehow you or your software packager managed\n"
literal|"to install GIMP with an older GLib version.\n\n"
literal|"Please upgrade to GLib version %d.%d.%d or later."
argument_list|,
name|mismatch
argument_list|,
name|GLIB_REQUIRED_MAJOR
argument_list|,
name|GLIB_REQUIRED_MINOR
argument_list|,
name|GLIB_REQUIRED_MICRO
argument_list|,
name|glib_major_version
argument_list|,
name|glib_minor_version
argument_list|,
name|glib_micro_version
argument_list|,
name|GLIB_REQUIRED_MAJOR
argument_list|,
name|GLIB_REQUIRED_MINOR
argument_list|,
name|GLIB_REQUIRED_MICRO
argument_list|)
return|;
block|}
undef|#
directive|undef
name|GLIB_REQUIRED_MAJOR
undef|#
directive|undef
name|GLIB_REQUIRED_MINOR
undef|#
directive|undef
name|GLIB_REQUIRED_MICRO
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|sanity_check_pango (void)
name|sanity_check_pango
parameter_list|(
name|void
parameter_list|)
block|{
DECL|macro|PANGO_REQUIRED_MAJOR
define|#
directive|define
name|PANGO_REQUIRED_MAJOR
value|1
DECL|macro|PANGO_REQUIRED_MINOR
define|#
directive|define
name|PANGO_REQUIRED_MINOR
value|20
DECL|macro|PANGO_REQUIRED_MICRO
define|#
directive|define
name|PANGO_REQUIRED_MICRO
value|1
specifier|const
name|gchar
modifier|*
name|mismatch
init|=
name|pango_version_check
argument_list|(
name|PANGO_REQUIRED_MAJOR
argument_list|,
name|PANGO_REQUIRED_MINOR
argument_list|,
name|PANGO_REQUIRED_MICRO
argument_list|)
decl_stmt|;
if|if
condition|(
name|mismatch
condition|)
block|{
specifier|const
name|gint
name|pango_major_version
init|=
name|pango_version
argument_list|()
operator|/
literal|100
operator|/
literal|100
decl_stmt|;
specifier|const
name|gint
name|pango_minor_version
init|=
name|pango_version
argument_list|()
operator|/
literal|100
operator|%
literal|100
decl_stmt|;
specifier|const
name|gint
name|pango_micro_version
init|=
name|pango_version
argument_list|()
operator|%
literal|100
decl_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"%s\n\n"
literal|"GIMP requires Pango version %d.%d.%d or later.\n"
literal|"Installed Pango version is %d.%d.%d.\n\n"
literal|"Somehow you or your software packager managed\n"
literal|"to install GIMP with an older Pango version.\n\n"
literal|"Please upgrade to Pango version %d.%d.%d or later."
argument_list|,
name|mismatch
argument_list|,
name|PANGO_REQUIRED_MAJOR
argument_list|,
name|PANGO_REQUIRED_MINOR
argument_list|,
name|PANGO_REQUIRED_MICRO
argument_list|,
name|pango_major_version
argument_list|,
name|pango_minor_version
argument_list|,
name|pango_micro_version
argument_list|,
name|PANGO_REQUIRED_MAJOR
argument_list|,
name|PANGO_REQUIRED_MINOR
argument_list|,
name|PANGO_REQUIRED_MICRO
argument_list|)
return|;
block|}
undef|#
directive|undef
name|PANGO_REQUIRED_MAJOR
undef|#
directive|undef
name|PANGO_REQUIRED_MINOR
undef|#
directive|undef
name|PANGO_REQUIRED_MICRO
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|sanity_check_fontconfig (void)
name|sanity_check_fontconfig
parameter_list|(
name|void
parameter_list|)
block|{
specifier|const
name|gint
name|fc_version
init|=
name|FcGetVersion
argument_list|()
decl_stmt|;
DECL|macro|FC_REQUIRED_MAJOR
define|#
directive|define
name|FC_REQUIRED_MAJOR
value|2
DECL|macro|FC_REQUIRED_MINOR
define|#
directive|define
name|FC_REQUIRED_MINOR
value|2
DECL|macro|FC_REQUIRED_MICRO
define|#
directive|define
name|FC_REQUIRED_MICRO
value|0
if|if
condition|(
name|fc_version
operator|<
operator|(
operator|(
name|FC_REQUIRED_MAJOR
operator|*
literal|10000
operator|)
operator|+
operator|(
name|FC_REQUIRED_MINOR
operator|*
literal|100
operator|)
operator|+
operator|(
name|FC_REQUIRED_MICRO
operator|*
literal|1
operator|)
operator|)
condition|)
block|{
specifier|const
name|gint
name|fc_major_version
init|=
name|fc_version
operator|/
literal|100
operator|/
literal|100
decl_stmt|;
specifier|const
name|gint
name|fc_minor_version
init|=
name|fc_version
operator|/
literal|100
operator|%
literal|100
decl_stmt|;
specifier|const
name|gint
name|fc_micro_version
init|=
name|fc_version
operator|%
literal|100
decl_stmt|;
return|return
name|g_strdup_printf
argument_list|(
literal|"The Fontconfig version being used is too old!\n\n"
literal|"GIMP requires Fontconfig version %d.%d.%d or later.\n"
literal|"The Fontconfig version loaded by GIMP is %d.%d.%d.\n\n"
literal|"This may be caused by another instance of libfontconfig.so.1\n"
literal|"being installed in the system, probably in /usr/X11R6/lib.\n"
literal|"Please correct the situation or report it to someone who can."
argument_list|,
name|FC_REQUIRED_MAJOR
argument_list|,
name|FC_REQUIRED_MINOR
argument_list|,
name|FC_REQUIRED_MICRO
argument_list|,
name|fc_major_version
argument_list|,
name|fc_minor_version
argument_list|,
name|fc_micro_version
argument_list|)
return|;
block|}
undef|#
directive|undef
name|FC_REQUIRED_MAJOR
undef|#
directive|undef
name|FC_REQUIRED_MINOR
undef|#
directive|undef
name|FC_REQUIRED_MICRO
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|sanity_check_freetype (void)
name|sanity_check_freetype
parameter_list|(
name|void
parameter_list|)
block|{
name|FT_Library
name|ft_library
decl_stmt|;
name|FT_Int
name|ft_major_version
decl_stmt|;
name|FT_Int
name|ft_minor_version
decl_stmt|;
name|FT_Int
name|ft_micro_version
decl_stmt|;
name|FT_Int
name|ft_version
decl_stmt|;
DECL|macro|FT_REQUIRED_MAJOR
define|#
directive|define
name|FT_REQUIRED_MAJOR
value|2
DECL|macro|FT_REQUIRED_MINOR
define|#
directive|define
name|FT_REQUIRED_MINOR
value|1
DECL|macro|FT_REQUIRED_MICRO
define|#
directive|define
name|FT_REQUIRED_MICRO
value|7
if|if
condition|(
name|FT_Init_FreeType
argument_list|(
operator|&
name|ft_library
argument_list|)
operator|!=
literal|0
condition|)
name|g_error
argument_list|(
literal|"FT_Init_FreeType() failed"
argument_list|)
expr_stmt|;
name|FT_Library_Version
argument_list|(
name|ft_library
argument_list|,
operator|&
name|ft_major_version
argument_list|,
operator|&
name|ft_minor_version
argument_list|,
operator|&
name|ft_micro_version
argument_list|)
expr_stmt|;
if|if
condition|(
name|FT_Done_FreeType
argument_list|(
name|ft_library
argument_list|)
operator|!=
literal|0
condition|)
name|g_error
argument_list|(
literal|"FT_Done_FreeType() failed"
argument_list|)
expr_stmt|;
name|ft_version
operator|=
operator|(
name|ft_major_version
operator|*
literal|10000
operator|+
name|ft_minor_version
operator|*
literal|100
operator|+
name|ft_micro_version
operator|*
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|ft_version
operator|<
operator|(
operator|(
name|FT_REQUIRED_MAJOR
operator|*
literal|10000
operator|)
operator|+
operator|(
name|FT_REQUIRED_MINOR
operator|*
literal|100
operator|)
operator|+
operator|(
name|FT_REQUIRED_MICRO
operator|*
literal|1
operator|)
operator|)
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"FreeType version too old!\n\n"
literal|"GIMP requires FreeType version %d.%d.%d or later.\n"
literal|"Installed FreeType version is %d.%d.%d.\n\n"
literal|"Somehow you or your software packager managed\n"
literal|"to install GIMP with an older FreeType version.\n\n"
literal|"Please upgrade to FreeType version %d.%d.%d or later."
argument_list|,
name|FT_REQUIRED_MAJOR
argument_list|,
name|FT_REQUIRED_MINOR
argument_list|,
name|FT_REQUIRED_MICRO
argument_list|,
name|ft_major_version
argument_list|,
name|ft_minor_version
argument_list|,
name|ft_micro_version
argument_list|,
name|FT_REQUIRED_MAJOR
argument_list|,
name|FT_REQUIRED_MINOR
argument_list|,
name|FT_REQUIRED_MICRO
argument_list|)
return|;
block|}
undef|#
directive|undef
name|FT_REQUIRED_MAJOR
undef|#
directive|undef
name|FT_REQUIRED_MINOR
undef|#
directive|undef
name|FT_REQUIRED_MICRO
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|sanity_check_babl (void)
name|sanity_check_babl
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|babl_major_version
decl_stmt|;
name|gint
name|babl_minor_version
decl_stmt|;
name|gint
name|babl_micro_version
decl_stmt|;
DECL|macro|BABL_REQUIRED_MAJOR
define|#
directive|define
name|BABL_REQUIRED_MAJOR
value|0
DECL|macro|BABL_REQUIRED_MINOR
define|#
directive|define
name|BABL_REQUIRED_MINOR
value|1
DECL|macro|BABL_REQUIRED_MICRO
define|#
directive|define
name|BABL_REQUIRED_MICRO
value|2
name|babl_get_version
argument_list|(
operator|&
name|babl_major_version
argument_list|,
operator|&
name|babl_minor_version
argument_list|,
operator|&
name|babl_micro_version
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sanity_check_version
argument_list|(
name|babl_major_version
argument_list|,
name|BABL_REQUIRED_MAJOR
argument_list|,
name|babl_minor_version
argument_list|,
name|BABL_REQUIRED_MINOR
argument_list|,
name|babl_micro_version
argument_list|,
name|BABL_REQUIRED_MICRO
argument_list|)
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"BABL version too old!\n\n"
literal|"GIMP requires BABL version %d.%d.%d or later.\n"
literal|"Installed BABL version is %d.%d.%d.\n\n"
literal|"Somehow you or your software packager managed\n"
literal|"to install GIMP with an older BABL version.\n\n"
literal|"Please upgrade to BABL version %d.%d.%d or later."
argument_list|,
name|BABL_REQUIRED_MAJOR
argument_list|,
name|BABL_REQUIRED_MINOR
argument_list|,
name|BABL_REQUIRED_MICRO
argument_list|,
name|babl_major_version
argument_list|,
name|babl_minor_version
argument_list|,
name|babl_micro_version
argument_list|,
name|BABL_REQUIRED_MAJOR
argument_list|,
name|BABL_REQUIRED_MINOR
argument_list|,
name|BABL_REQUIRED_MICRO
argument_list|)
return|;
block|}
undef|#
directive|undef
name|BABL_REQUIRED_MAJOR
undef|#
directive|undef
name|BABL_REQUIRED_MINOR
undef|#
directive|undef
name|BABL_REQUIRED_MICRO
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|sanity_check_gegl (void)
name|sanity_check_gegl
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|gegl_major_version
decl_stmt|;
name|gint
name|gegl_minor_version
decl_stmt|;
name|gint
name|gegl_micro_version
decl_stmt|;
DECL|macro|GEGL_REQUIRED_MAJOR
define|#
directive|define
name|GEGL_REQUIRED_MAJOR
value|0
DECL|macro|GEGL_REQUIRED_MINOR
define|#
directive|define
name|GEGL_REQUIRED_MINOR
value|1
DECL|macro|GEGL_REQUIRED_MICRO
define|#
directive|define
name|GEGL_REQUIRED_MICRO
value|2
name|gegl_get_version
argument_list|(
operator|&
name|gegl_major_version
argument_list|,
operator|&
name|gegl_minor_version
argument_list|,
operator|&
name|gegl_micro_version
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sanity_check_version
argument_list|(
name|gegl_major_version
argument_list|,
name|GEGL_REQUIRED_MAJOR
argument_list|,
name|gegl_minor_version
argument_list|,
name|GEGL_REQUIRED_MINOR
argument_list|,
name|gegl_micro_version
argument_list|,
name|GEGL_REQUIRED_MICRO
argument_list|)
condition|)
block|{
return|return
name|g_strdup_printf
argument_list|(
literal|"GEGL version too old!\n\n"
literal|"GIMP requires GEGL version %d.%d.%d or later.\n"
literal|"Installed GEGL version is %d.%d.%d.\n\n"
literal|"Somehow you or your software packager managed\n"
literal|"to install GIMP with an older GEGL version.\n\n"
literal|"Please upgrade to GEGL version %d.%d.%d or later."
argument_list|,
name|GEGL_REQUIRED_MAJOR
argument_list|,
name|GEGL_REQUIRED_MINOR
argument_list|,
name|GEGL_REQUIRED_MICRO
argument_list|,
name|gegl_major_version
argument_list|,
name|gegl_minor_version
argument_list|,
name|gegl_micro_version
argument_list|,
name|GEGL_REQUIRED_MAJOR
argument_list|,
name|GEGL_REQUIRED_MINOR
argument_list|,
name|GEGL_REQUIRED_MICRO
argument_list|)
return|;
block|}
undef|#
directive|undef
name|GEGL_REQUIRED_MAJOR
undef|#
directive|undef
name|GEGL_REQUIRED_MINOR
undef|#
directive|undef
name|GEGL_REQUIRED_MICRO
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|sanity_check_filename_encoding (void)
name|sanity_check_filename_encoding
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|result
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|result
operator|=
name|g_filename_to_utf8
argument_list|(
literal|""
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|result
condition|)
block|{
name|gchar
modifier|*
name|msg
init|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"The configured filename encoding cannot be converted to UTF-8: "
literal|"%s\n\n"
literal|"Please check the value of the environment variable "
literal|"G_FILENAME_ENCODING."
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
decl_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|msg
return|;
block|}
name|g_free
argument_list|(
name|result
argument_list|)
expr_stmt|;
name|result
operator|=
name|g_filename_to_utf8
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|result
condition|)
block|{
name|gchar
modifier|*
name|msg
init|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"The name of the directory holding the GIMP user configuration "
literal|"cannot be converted to UTF-8: "
literal|"%s\n\n"
literal|"Your filesystem probably stores files in an encoding "
literal|"other than UTF-8 and you didn't tell GLib about this. "
literal|"Please set the environment variable G_FILENAME_ENCODING."
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
decl_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
return|return
name|msg
return|;
block|}
name|g_free
argument_list|(
name|result
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

