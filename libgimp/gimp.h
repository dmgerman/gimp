begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<glib-object.h>
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
file|<libgimp/gimpbrushes.h>
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
file|<libgimp/gimpgradients.h>
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
file|<libgimp/gimplayer.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppalette.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppalettes.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppaletteselect.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppatterns.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppatternselect.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppixelfetcher.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimppixelrgn.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpplugin.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpproceduraldb.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpprogress.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpregioniterator.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpselection.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimptile.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpvectors.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp_pdb.h>
end_include

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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|gimp_get_data
define|#
directive|define
name|gimp_get_data
value|gimp_procedural_db_get_data
end_define

begin_define
DECL|macro|gimp_get_data_size
define|#
directive|define
name|gimp_get_data_size
value|gimp_procedural_db_get_data_size
end_define

begin_define
DECL|macro|gimp_set_data
define|#
directive|define
name|gimp_set_data
value|gimp_procedural_db_set_data
end_define

begin_typedef
DECL|typedef|GimpInitProc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpInitProc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpQuitProc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpQuitProc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpQueryProc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpQueryProc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpRunProc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRunProc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|n_params
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|n_return_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/**  * GimpPlugInInfo:  * @init_proc:  called when the gimp application initially starts up  * @quit_proc:  called when the gimp application exits  * @query_proc: called by gimp so that the plug-in can inform the  *              gimp of what it does. (ie. installing a procedure database  *              procedure).  * @run_proc:   called to run a procedure the plug-in installed in the  *              procedure database.  **/
end_comment

begin_struct
DECL|struct|_GimpPlugInInfo
struct|struct
name|_GimpPlugInInfo
block|{
DECL|member|init_proc
name|GimpInitProc
name|init_proc
decl_stmt|;
DECL|member|quit_proc
name|GimpQuitProc
name|quit_proc
decl_stmt|;
DECL|member|query_proc
name|GimpQueryProc
name|query_proc
decl_stmt|;
DECL|member|run_proc
name|GimpRunProc
name|run_proc
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpParamDef
struct|struct
name|_GimpParamDef
block|{
DECL|member|type
name|GimpPDBArgType
name|type
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|description
name|gchar
modifier|*
name|description
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpParamRegion
struct|struct
name|_GimpParamRegion
block|{
DECL|member|x
name|gint32
name|x
decl_stmt|;
DECL|member|y
name|gint32
name|y
decl_stmt|;
DECL|member|width
name|gint32
name|width
decl_stmt|;
DECL|member|height
name|gint32
name|height
decl_stmt|;
block|}
struct|;
end_struct

begin_union
DECL|union|_GimpParamData
union|union
name|_GimpParamData
block|{
DECL|member|d_int32
name|gint32
name|d_int32
decl_stmt|;
DECL|member|d_int16
name|gint16
name|d_int16
decl_stmt|;
DECL|member|d_int8
name|guint8
name|d_int8
decl_stmt|;
DECL|member|d_float
name|gdouble
name|d_float
decl_stmt|;
DECL|member|d_string
name|gchar
modifier|*
name|d_string
decl_stmt|;
DECL|member|d_int32array
name|gint32
modifier|*
name|d_int32array
decl_stmt|;
DECL|member|d_int16array
name|gint16
modifier|*
name|d_int16array
decl_stmt|;
DECL|member|d_int8array
name|guint8
modifier|*
name|d_int8array
decl_stmt|;
DECL|member|d_floatarray
name|gdouble
modifier|*
name|d_floatarray
decl_stmt|;
DECL|member|d_stringarray
name|gchar
modifier|*
modifier|*
name|d_stringarray
decl_stmt|;
DECL|member|d_colorarray
name|GimpRGB
modifier|*
name|d_colorarray
decl_stmt|;
DECL|member|d_color
name|GimpRGB
name|d_color
decl_stmt|;
DECL|member|d_region
name|GimpParamRegion
name|d_region
decl_stmt|;
comment|/* deprecated */
DECL|member|d_display
name|gint32
name|d_display
decl_stmt|;
DECL|member|d_image
name|gint32
name|d_image
decl_stmt|;
DECL|member|d_item
name|gint32
name|d_item
decl_stmt|;
DECL|member|d_layer
name|gint32
name|d_layer
decl_stmt|;
DECL|member|d_layer_mask
name|gint32
name|d_layer_mask
decl_stmt|;
DECL|member|d_channel
name|gint32
name|d_channel
decl_stmt|;
DECL|member|d_drawable
name|gint32
name|d_drawable
decl_stmt|;
DECL|member|d_selection
name|gint32
name|d_selection
decl_stmt|;
DECL|member|d_boundary
name|gint32
name|d_boundary
decl_stmt|;
DECL|member|d_path
name|gint32
name|d_path
decl_stmt|;
comment|/* deprecated */
DECL|member|d_vectors
name|gint32
name|d_vectors
decl_stmt|;
DECL|member|d_unit
name|gint32
name|d_unit
decl_stmt|;
DECL|member|d_parasite
name|GimpParasite
name|d_parasite
decl_stmt|;
DECL|member|d_tattoo
name|gint32
name|d_tattoo
decl_stmt|;
DECL|member|d_status
name|GimpPDBStatusType
name|d_status
decl_stmt|;
block|}
union|;
end_union

begin_struct
DECL|struct|_GimpParam
struct|struct
name|_GimpParam
block|{
DECL|member|type
name|GimpPDBArgType
name|type
decl_stmt|;
DECL|member|data
name|GimpParamData
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * MAIN:  *  * A macro that expands to the appropriate main() function for the  * platform being compiled for.  *  * To use this macro, simply place a line that contains just the code  * MAIN() at the toplevel of your file.  No semicolon should be used.  **/
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_comment
comment|/* Define WinMain() because plug-ins are built as GUI applications. Also  * define a main() in case some plug-in still is built as a console  * application.  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_ifndef
ifndef|#
directive|ifndef
name|_stdcall
end_ifndef

begin_define
DECL|macro|_stdcall
define|#
directive|define
name|_stdcall
value|__attribute__((stdcall))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|MAIN ()
define|#
directive|define
name|MAIN
parameter_list|()
define|\
value|struct HINSTANCE__;                                  \                                                         \    int _stdcall                                         \    WinMain (struct HINSTANCE__ *hInstance,              \             struct HINSTANCE__ *hPrevInstance,          \             char *lpszCmdLine,                          \             int   nCmdShow);                            \                                                         \    int _stdcall                                         \    WinMain (struct HINSTANCE__ *hInstance,              \             struct HINSTANCE__ *hPrevInstance,          \             char *lpszCmdLine,                          \             int   nCmdShow)                             \    {                                                    \      return gimp_main (&PLUG_IN_INFO, __argc, __argv);  \    }                                                    \                                                         \    int                                                  \    main (int argc, char *argv[])                        \    {                                                    \
comment|/* Use __argc and __argv here, too, as they work   \       * better with mingw-w64.				\       */
value|\      return gimp_main (&PLUG_IN_INFO, __argc, __argv);  \    }
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|MAIN ()
define|#
directive|define
name|MAIN
parameter_list|()
define|\
value|int                                                  \    main (int argc, char *argv[])                        \    {                                                    \      return gimp_main (&PLUG_IN_INFO, argc, argv);      \    }
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* The main procedure that must be called with the PLUG_IN_INFO structure  * and the 'argc' and 'argv' that are passed to "main".  */
end_comment

begin_function_decl
name|gint
name|gimp_main
parameter_list|(
specifier|const
name|GimpPlugInInfo
modifier|*
name|info
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
comment|/* Forcefully causes the gimp library to exit and  *  close down its connection to main gimp application.  */
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
comment|/* Install a procedure in the procedure database.  */
end_comment

begin_function_decl
name|void
name|gimp_install_procedure
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_types
parameter_list|,
name|GimpPDBProcType
name|type
parameter_list|,
name|gint
name|n_params
parameter_list|,
name|gint
name|n_return_vals
parameter_list|,
specifier|const
name|GimpParamDef
modifier|*
name|params
parameter_list|,
specifier|const
name|GimpParamDef
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Install a temporary procedure in the procedure database.  */
end_comment

begin_function_decl
name|void
name|gimp_install_temp_proc
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help
parameter_list|,
specifier|const
name|gchar
modifier|*
name|author
parameter_list|,
specifier|const
name|gchar
modifier|*
name|copyright
parameter_list|,
specifier|const
name|gchar
modifier|*
name|date
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_types
parameter_list|,
name|GimpPDBProcType
name|type
parameter_list|,
name|gint
name|n_params
parameter_list|,
name|gint
name|n_return_vals
parameter_list|,
specifier|const
name|GimpParamDef
modifier|*
name|params
parameter_list|,
specifier|const
name|GimpParamDef
modifier|*
name|return_vals
parameter_list|,
name|GimpRunProc
name|run_proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Uninstall a temporary procedure  */
end_comment

begin_function_decl
name|void
name|gimp_uninstall_temp_proc
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Notify the main GIMP application that the extension is ready to run  */
end_comment

begin_function_decl
name|void
name|gimp_extension_ack
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Enable asynchronous processing of temp_procs  */
end_comment

begin_function_decl
name|void
name|gimp_extension_enable
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Process one temp_proc and return  */
end_comment

begin_function_decl
name|void
name|gimp_extension_process
parameter_list|(
name|guint
name|timeout
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Run a procedure in the procedure database. The parameters are  *  specified via the variable length argument list. The return  *  values are returned in the 'GimpParam*' array.  */
end_comment

begin_function_decl
name|GimpParam
modifier|*
name|gimp_run_procedure
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|n_return_vals
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Run a procedure in the procedure database. The parameters are  *  specified as an array of GimpParam.  The return  *  values are returned in the 'GimpParam*' array.  */
end_comment

begin_function_decl
name|GimpParam
modifier|*
name|gimp_run_procedure2
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|n_return_vals
parameter_list|,
name|gint
name|n_params
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Destroy the an array of parameters. This is useful for  *  destroying the return values returned by a call to  *  'gimp_run_procedure'.  */
end_comment

begin_function_decl
name|void
name|gimp_destroy_params
parameter_list|(
name|GimpParam
modifier|*
name|params
parameter_list|,
name|gint
name|n_params
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Destroy the an array of GimpParamDef's. This is useful for  *  destroying the return values returned by a call to  *  'gimp_procedural_db_proc_info'.  */
end_comment

begin_function_decl
name|void
name|gimp_destroy_paramdefs
parameter_list|(
name|GimpParamDef
modifier|*
name|paramdefs
parameter_list|,
name|gint
name|n_params
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Retrieve the error message for the last procedure call.  */
end_comment

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_pdb_error
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

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
name|gint
name|gimp_shm_ID
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|guchar
modifier|*
name|gimp_shm_addr
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gdouble
name|gimp_gamma
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|gimp_install_cmap
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|gimp_min_colors
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gboolean
name|gimp_show_tool_tips
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
name|gimp_get_progname
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_function_decl
name|gboolean
name|gimp_attach_new_parasite
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|flags
parameter_list|,
name|gint
name|size
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

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

