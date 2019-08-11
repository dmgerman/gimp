begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimplegacy.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LEGACY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LEGACY_H__
define|#
directive|define
name|__GIMP_LEGACY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_COMPAT_CRUFT
end_ifndef

begin_comment
comment|/**  * GimpInitProc:  *  * The init procedure is run at every GIMP startup.  */
end_comment

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

begin_comment
comment|/**  * GimpQuitProc:  *  * The quit procedure is run each time the plug-in ends.  */
end_comment

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

begin_comment
comment|/**  * GimpQueryProc:  *  * The initialization procedure is run at GIMP startup, only the first  * time after a plug-in is installed, or if it has been updated.  */
end_comment

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

begin_comment
comment|/**  * GimpRunProc:  * @name: the name of the procedure which has been called.  * @n_params: the number of parameters passed to the procedure.  * @param: (array length=n_params): the parameters passed to @name.  * @n_return_vals: (out caller-allocates): the number of values returned by @name.  * @return_vals: (array length=n_return_vals) (out callee-allocates): the returned values.  *  * The run procedure is run during the lifetime of the GIMP session,  * each time a plug-in procedure is called.  */
end_comment

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

begin_comment
comment|/**  * GimpParamDef:  * @type:        the parameter's type.  * @name:        the parameter's name.  * @description: the parameter's desctiption.  **/
end_comment

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

begin_comment
comment|/**  * GimpParamData:  * @d_int32:       a 32-bit integer.  * @d_int16:       a 16-bit integer.  * @d_int8:        an 8-bit unsigned integer.  * @d_float:       a double.  * @d_string:      a string.  * @d_color:       a #GimpRGB.  * @d_int32array:  an array of int32.  * @d_int16array:  an array of int16.  * @d_int8array:   an array of int8.  * @d_floatarray:  an array of floats.  * @d_stringarray: an array of strings.  * @d_colorarray:  an array of colors.  * @d_display:     a display id.  * @d_image:       an image id.  * @d_item:        an item id.  * @d_drawable:    a drawable id.  * @d_layer:       a layer id.  * @d_channel:     a channel id.  * @d_layer_mask:  a layer mask id.  * @d_selection:   a selection id.  * @d_vectors:     a vectors id.  * @d_unit:        a GimpUnit.  * @d_parasite:    a GimpParasite.  * @d_tattoo:      a tattoo.  * @d_status:      a return status.  **/
end_comment

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
DECL|member|d_color
name|GimpRGB
name|d_color
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
DECL|member|d_drawable
name|gint32
name|d_drawable
decl_stmt|;
DECL|member|d_layer
name|gint32
name|d_layer
decl_stmt|;
DECL|member|d_channel
name|gint32
name|d_channel
decl_stmt|;
DECL|member|d_layer_mask
name|gint32
name|d_layer_mask
decl_stmt|;
DECL|member|d_selection
name|gint32
name|d_selection
decl_stmt|;
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

begin_comment
comment|/**  * GimpParam:  * @type: the parameter's type.  * @data: the parameter's data.  **/
end_comment

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
value|struct HINSTANCE__;                                  \                                                         \    int _stdcall                                         \    WinMain (struct HINSTANCE__ *hInstance,              \             struct HINSTANCE__ *hPrevInstance,          \             char *lpszCmdLine,                          \             int   nCmdShow);                            \                                                         \    int _stdcall                                         \    WinMain (struct HINSTANCE__ *hInstance,              \             struct HINSTANCE__ *hPrevInstance,          \             char *lpszCmdLine,                          \             int   nCmdShow)                             \    {                                                    \      return gimp_main_legacy (&PLUG_IN_INFO,            \                               __argc, __argv);          \    }                                                    \                                                         \    int                                                  \    main (int argc, char *argv[])                        \    {                                                    \
comment|/* Use __argc and __argv here, too, as they work   \       * better with mingw-w64.                          \       */
value|\      return gimp_main_legacy (&PLUG_IN_INFO,            \                               __argc, __argv);          \    }
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
value|int                                                  \    main (int argc, char *argv[])                        \    {                                                    \      return gimp_main_legacy (&PLUG_IN_INFO,            \                               argc, argv);              \    }
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* The main procedure that must be called with the PLUG_IN_INFO  * structure and the 'argc' and 'argv' that are passed to "main".  */
end_comment

begin_function_decl
name|gint
name|gimp_main_legacy
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
comment|/* Run a procedure in the procedure database. The parameters are  *  specified as a GimpValueArray, so are the return values.  */
end_comment

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_run_procedure_array
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|arguments
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
comment|/* Retrieve the error message and return status for the last procedure  * call.  */
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

begin_function_decl
name|GimpPDBStatusType
name|gimp_get_pdb_status
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* gimp_plugin API that should now be done by using GimpPlugIn  */
end_comment

begin_function_decl
name|gboolean
name|gimp_plugin_domain_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plugin_help_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plugin_menu_branch_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plugin_set_pdb_error_handler
parameter_list|(
name|GimpPDBErrorHandler
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPDBErrorHandler
name|gimp_plugin_get_pdb_error_handler
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* gimp_plugin API that should now be done by using GimpProcedure  */
end_comment

begin_function_decl
name|gboolean
name|gimp_plugin_menu_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plugin_icon_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GimpIconType
name|icon_type
parameter_list|,
name|gconstpointer
name|icon_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* gimp_fileops API that should now be done by using GimpFileProcedure  */
end_comment

begin_function_decl
name|gboolean
name|gimp_register_magic_load_handler
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
parameter_list|,
specifier|const
name|gchar
modifier|*
name|magics
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_register_load_handler
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_register_save_handler
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_register_file_handler_priority
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gint
name|priority
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_register_file_handler_mime
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_types
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_register_file_handler_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_register_file_handler_raw
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_register_thumbnail_loader
parameter_list|(
specifier|const
name|gchar
modifier|*
name|load_proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thumb_proc
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* pdb stuff that should now be done using GimpPDB  */
end_comment

begin_function_decl
name|gchar
modifier|*
name|gimp_pdb_temp_name
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_dump
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_query
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
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_matches
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|procedure_names
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_proc_exists
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_proc_info
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
modifier|*
name|date
parameter_list|,
name|GimpPDBProcType
modifier|*
name|proc_type
parameter_list|,
name|gint
modifier|*
name|num_args
parameter_list|,
name|gint
modifier|*
name|num_values
parameter_list|,
name|GimpParamDef
modifier|*
modifier|*
name|args
parameter_list|,
name|GimpParamDef
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_proc_arg
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gint
name|arg_num
parameter_list|,
name|GimpPDBArgType
modifier|*
name|arg_type
parameter_list|,
name|gchar
modifier|*
modifier|*
name|arg_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|arg_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_proc_val
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gint
name|val_num
parameter_list|,
name|GimpPDBArgType
modifier|*
name|val_type
parameter_list|,
name|gchar
modifier|*
modifier|*
name|val_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|val_desc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_COMPAT_CRUFT */
end_comment

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LEGACY_H__ */
end_comment

end_unit

