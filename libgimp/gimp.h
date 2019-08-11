begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_H__
define|#
directive|define
name|__GIMP_H__
end_define

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<libgimpbase/gimpbase.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcolor.h>
end_include

begin_include
include|#
directive|include
file|<libgimpconfig/gimpconfig.h>
end_include

begin_include
include|#
directive|include
file|<libgimpmath/gimpmath.h>
end_include

begin_define
DECL|macro|__GIMP_H_INSIDE__
define|#
directive|define
name|__GIMP_H_INSIDE__
end_define

begin_include
include|#
directive|include
file|<libgimp/gimpenums.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimptypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpbrushselect.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpchannel.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpdrawable.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpfontselect.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpgimprc.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpgradientselect.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpimage.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpimagecolorprofile.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimplayer.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimploadprocedure.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimplegacy.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppaletteselect.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpparamspecs.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppatternselect.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppdb.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpplugin.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpprogress.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpsaveprocedure.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpselection.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp_pdb_headers.h>
end_include

begin_undef
undef|#
directive|undef
name|__GIMP_H_INSIDE__
end_undef

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_comment
comment|/* For __argc and __argv */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|G_BEGIN_DECLS
DECL|macro|gimp_get_data
define|#
directive|define
name|gimp_get_data
value|gimp_pdb_get_data
DECL|macro|gimp_get_data_size
define|#
directive|define
name|gimp_get_data_size
value|gimp_pdb_get_data_size
DECL|macro|gimp_set_data
define|#
directive|define
name|gimp_set_data
value|gimp_pdb_set_data
comment|/**  * GIMP_MAIN:  * @plug_in_type: The #GType of the plug-in's #GimpPlugIn subclass  *  * A macro that expands to the appropriate main() function for the  * platform being compiled for.  *  * To use this macro, simply place a line that contains just the code  *  * GIMP_MAIN (MY_TYPE_PLUG_IN)  *  * at the toplevel of your file. No semicolon should be used.  **/
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* Define WinMain() because plug-ins are built as GUI applications. Also  * define a main() in case some plug-in still is built as a console  * application.  */
ifdef|#
directive|ifdef
name|__GNUC__
ifndef|#
directive|ifndef
name|_stdcall
DECL|macro|_stdcall
define|#
directive|define
name|_stdcall
value|__attribute__((stdcall))
endif|#
directive|endif
endif|#
directive|endif
DECL|macro|GIMP_MAIN (plug_in_type)
define|#
directive|define
name|GIMP_MAIN
parameter_list|(
name|plug_in_type
parameter_list|)
define|\
value|struct HINSTANCE__;                                  \                                                         \    int _stdcall                                         \    WinMain (struct HINSTANCE__ *hInstance,              \             struct HINSTANCE__ *hPrevInstance,          \             char *lpszCmdLine,                          \             int   nCmdShow);                            \                                                         \    int _stdcall                                         \    WinMain (struct HINSTANCE__ *hInstance,              \             struct HINSTANCE__ *hPrevInstance,          \             char *lpszCmdLine,                          \             int   nCmdShow)                             \    {                                                    \      return gimp_main (plug_in_type,                    \                        __argc, __argv);                 \    }                                                    \                                                         \    int                                                  \    main (int argc, char *argv[])                        \    {                                                    \
comment|/* Use __argc and __argv here, too, as they work   \       * better with mingw-w64.                          \       */
value|\      return gimp_main (plug_in_type,                    \                        __argc, __argv);                 \    }
else|#
directive|else
define|#
directive|define
name|GIMP_MAIN
parameter_list|(
name|plug_in_type
parameter_list|)
define|\
value|int                                                  \    main (int argc, char *argv[])                        \    {                                                    \      return gimp_main (plug_in_type,                    \                        argc, argv);                     \    }
endif|#
directive|endif
comment|/* The main procedure that must be called with the plug-in's  * GimpPlugIn subclass type and the 'argc' and 'argv' that are passed  * to "main".  */
name|gint
name|gimp_main
parameter_list|(
name|GType
name|plug_in_type
parameter_list|,
name|gint
name|argc
parameter_list|,
name|gchar
modifier|*
name|argv
index|[]
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return the GimpPlugIn singleton of this plug-in process  */
end_comment

begin_function_decl
name|GimpPlugIn
modifier|*
name|gimp_get_plug_in
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return the GimpPDB singleton of this plug-in process  */
end_comment

begin_function_decl
name|GimpPDB
modifier|*
name|gimp_get_pdb
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Forcefully causes the gimp library to exit and  * close down its connection to main gimp application.  */
end_comment

begin_decl_stmt
name|void
name|gimp_quit
argument_list|(
name|void
argument_list|)
name|G_GNUC_NORETURN
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Return various constants given by the GIMP core at plug-in config time.  */
end_comment

begin_decl_stmt
name|guint
name|gimp_tile_width
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|guint
name|gimp_tile_height
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|gimp_show_help_button
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|gimp_export_color_profile
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|gimp_export_exif
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|gimp_export_xmp
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|gimp_export_iptc
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GimpCheckSize
name|gimp_check_size
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GimpCheckType
name|gimp_check_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint32
name|gimp_default_display
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_wm_class
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_display_name
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|gimp_monitor_number
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|guint32
name|gimp_user_time
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_icon_theme_dir
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|const
name|gchar
modifier|*
name|gimp_get_progname
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_H__ */
end_comment

end_unit

