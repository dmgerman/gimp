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
file|<glib.h>
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

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
end_ifndef

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"about.h"
end_include

begin_include
include|#
directive|include
file|"version.h"
end_include

begin_include
include|#
directive|include
file|"git-version.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|gimp_show_library_version (const gchar * package,gint build_time_major,gint build_time_minor,gint build_time_micro,gint run_time_major,gint run_time_minor,gint run_time_micro)
name|gimp_show_library_version
parameter_list|(
specifier|const
name|gchar
modifier|*
name|package
parameter_list|,
name|gint
name|build_time_major
parameter_list|,
name|gint
name|build_time_minor
parameter_list|,
name|gint
name|build_time_micro
parameter_list|,
name|gint
name|run_time_major
parameter_list|,
name|gint
name|run_time_minor
parameter_list|,
name|gint
name|run_time_micro
parameter_list|)
block|{
name|gchar
modifier|*
name|build_time_version
decl_stmt|;
name|gchar
modifier|*
name|run_time_version
decl_stmt|;
name|build_time_version
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d.%d.%d"
argument_list|,
name|build_time_major
argument_list|,
name|build_time_minor
argument_list|,
name|build_time_micro
argument_list|)
expr_stmt|;
name|run_time_version
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d.%d.%d"
argument_list|,
name|run_time_major
argument_list|,
name|run_time_minor
argument_list|,
name|run_time_micro
argument_list|)
expr_stmt|;
comment|/* show versions of libraries used by GIMP */
name|g_print
argument_list|(
name|_
argument_list|(
literal|"using %s version %s (compiled against version %s)"
argument_list|)
argument_list|,
name|package
argument_list|,
name|run_time_version
argument_list|,
name|build_time_version
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|run_time_version
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|build_time_version
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_show_library_versions (void)
name|gimp_show_library_versions
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
name|gimp_show_library_version
argument_list|(
literal|"GEGL"
argument_list|,
name|GEGL_MAJOR_VERSION
argument_list|,
name|GEGL_MINOR_VERSION
argument_list|,
name|GEGL_MICRO_VERSION
argument_list|,
name|gegl_major_version
argument_list|,
name|gegl_minor_version
argument_list|,
name|gegl_micro_version
argument_list|)
expr_stmt|;
name|gimp_show_library_version
argument_list|(
literal|"GLib"
argument_list|,
name|GLIB_MAJOR_VERSION
argument_list|,
name|GLIB_MINOR_VERSION
argument_list|,
name|GLIB_MICRO_VERSION
argument_list|,
name|glib_major_version
argument_list|,
name|glib_minor_version
argument_list|,
name|glib_micro_version
argument_list|)
expr_stmt|;
ifndef|#
directive|ifndef
name|GIMP_CONSOLE_COMPILATION
name|gimp_show_library_version
argument_list|(
literal|"GTK+"
argument_list|,
name|GTK_MAJOR_VERSION
argument_list|,
name|GTK_MINOR_VERSION
argument_list|,
name|GTK_MICRO_VERSION
argument_list|,
name|gtk_major_version
argument_list|,
name|gtk_minor_version
argument_list|,
name|gtk_micro_version
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_show_library_version
argument_list|(
literal|"Pango"
argument_list|,
name|PANGO_VERSION_MAJOR
argument_list|,
name|PANGO_VERSION_MINOR
argument_list|,
name|PANGO_VERSION_MICRO
argument_list|,
name|pango_version
argument_list|()
operator|/
literal|100
operator|/
literal|100
argument_list|,
name|pango_version
argument_list|()
operator|/
literal|100
operator|%
literal|100
argument_list|,
name|pango_version
argument_list|()
operator|%
literal|100
argument_list|)
expr_stmt|;
name|gimp_show_library_version
argument_list|(
literal|"Fontconfig"
argument_list|,
name|FC_MAJOR
argument_list|,
name|FC_MINOR
argument_list|,
name|FC_REVISION
argument_list|,
name|FcGetVersion
argument_list|()
operator|/
literal|100
operator|/
literal|100
argument_list|,
name|FcGetVersion
argument_list|()
operator|/
literal|100
operator|%
literal|100
argument_list|,
name|FcGetVersion
argument_list|()
operator|%
literal|100
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_version_show (gboolean be_verbose)
name|gimp_version_show
parameter_list|(
name|gboolean
name|be_verbose
parameter_list|)
block|{
name|g_print
argument_list|(
name|_
argument_list|(
literal|"%s version %s"
argument_list|)
argument_list|,
name|GIMP_NAME
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|be_verbose
condition|)
block|{
name|g_print
argument_list|(
name|_
argument_list|(
literal|"git commit %s"
argument_list|)
argument_list|,
name|GIMP_GIT_VERSION
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|gimp_show_library_versions
argument_list|()
expr_stmt|;
block|}
block|}
end_function

end_unit

