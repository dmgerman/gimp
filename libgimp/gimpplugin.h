begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_PLUG_IN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_H__
define|#
directive|define
name|__GIMP_PLUG_IN_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PLUG_IN
define|#
directive|define
name|GIMP_TYPE_PLUG_IN
value|(gimp_plug_in_get_type ())
end_define

begin_define
DECL|macro|GIMP_PLUG_IN (obj)
define|#
directive|define
name|GIMP_PLUG_IN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PLUG_IN, GimpPlugIn))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_CLASS (klass)
define|#
directive|define
name|GIMP_PLUG_IN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PLUG_IN, GimpPlugInClass))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN (obj)
define|#
directive|define
name|GIMP_IS_PLUG_IN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PLUG_IN))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PLUG_IN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PLUG_IN))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PLUG_IN_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PLUG_IN, GimpPlugInClass))
end_define

begin_typedef
DECL|typedef|GimpPlugInClass
typedef|typedef
name|struct
name|_GimpPlugInClass
name|GimpPlugInClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPlugInPrivate
typedef|typedef
name|struct
name|_GimpPlugInPrivate
name|GimpPlugInPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugIn
struct|struct
name|_GimpPlugIn
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpPlugInPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/**  * GimpPlugInClass:  * @query_procedures: This method can be overridden by all plug-ins to  *   return a newly allocated #GList of allocated strings naming the  *   procedures registered by this plug-in. See documentation of  *   #GimpPlugInClass.init_procedures() for differences.  * @init_procedures: This method can be overridden by all plug-ins to  *   return a newly allocated #GList of allocated strings naming  *   procedures registered by this plug-in.  *   It is different from #GimpPlugInClass.query_procedures() in that  *   init happens at every startup, whereas query happens only once in  *   the life of a plug-in (right after installation or update). Hence  *   #GimpPlugInClass.init_procedures() typically returns procedures  *   dependent to runtime conditions (such as the presence of a  *   third-party tool), whereas #GimpPlugInClass.query_procedures()  *   would usually return procedures that are always available  *   unconditionally.  *   Most of the time, you only want to override  *   #GimpPlugInClass.query_procedures() and leave  *   #GimpPlugInClass.init_procedures() untouched.  * @create_procedure: This method must be overridden by all plug-ins  *   and return a newly allocated #GimpProcedure named @name. It will  *   be called for every @name as returned by  *   #GimpPlugInClass.query_procedures() and  *   #GimpPlugInClass.init_procedures() so care must be taken to  *   handle them all.  *   Upon procedure registration, #GimpPlugInClass.create_procedure()  *   will be called in the order of the lists returned by  *   #GimpPlugInClass.query_procedures() and  *   #GimpPlugInClass.init_procedures()  * @quit: This method can be overridden by a plug-in which needs to  *   perform some actions upon quitting.  *  * A class which every plug-in should sublass, while overriding  * #GimpPlugInClass.query_procedures() and/or  * #GimpPlugInClass.init_procedures(), as well as  * #GimpPlugInClass.create_procedure().  *  * Since: 3.0  **/
end_comment

begin_struct
DECL|struct|_GimpPlugInClass
struct|struct
name|_GimpPlugInClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
comment|/**    * GimpPlugInClass::query_procedures:    * @plug_in: a #GimpPlugIn.    *    * Returns: (element-type gchar*) (transfer full):    *          the names of the procedures registered by @plug_in.    **/
DECL|member|query_procedures
name|GList
modifier|*
function_decl|(
modifier|*
name|query_procedures
function_decl|)
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
comment|/**    * GimpPlugInClass::init_procedures:    * @plug_in: a #GimpPlugIn.    *    * Returns: (element-type gchar*) (transfer full):    *          the names of the procedures registered by @plug_in.    **/
DECL|member|init_procedures
name|GList
modifier|*
function_decl|(
modifier|*
name|init_procedures
function_decl|)
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
comment|/**    * GimpPlugInClass::create_procedure:    * @plug_in:        a #GimpPlugIn.    * @procedure_name: procedure name.    *    * Returns: (transfer full):    *          the procedure to be registered or executed by @plug_in.    **/
DECL|member|create_procedure
name|GimpProcedure
modifier|*
function_decl|(
modifier|*
name|create_procedure
function_decl|)
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
function_decl|;
comment|/**    * GimpPlugInClass::quit:    * @plug_in: a #GimpPlugIn.    **/
DECL|member|quit
name|void
function_decl|(
modifier|*
name|quit
function_decl|)
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_plug_in_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_plug_in_set_translation_domain
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
name|GFile
modifier|*
name|domain_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_set_help_domain
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
name|GFile
modifier|*
name|domain_uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_add_menu_branch
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_add_temp_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_remove_temp_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_plug_in_get_temp_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpProcedure
modifier|*
name|gimp_plug_in_get_temp_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_extension_enable
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_extension_process
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|guint
name|timeout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_set_pdb_error_handler
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
name|GimpPDBErrorHandler
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPDBErrorHandler
name|gimp_plug_in_get_pdb_error_handler
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_H__ */
end_comment

end_unit

