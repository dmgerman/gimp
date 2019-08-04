begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprocedure.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
name|__GIMP_PROCEDURE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROCEDURE_H__
define|#
directive|define
name|__GIMP_PROCEDURE_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * GimpRunFunc:  * @procedure: the #GimpProcedure that runs.  * @args:      the @procedure's arguments.  * @run_data:  the run_data given in gimp_procedure_new().  *  * The run function is run during the lifetime of the GIMP session,  * each time a plug-in procedure is called.  *  * Returns: (transfer full): the @procedure's return values.  *  * Since: 3.0  **/
end_comment

begin_typedef
DECL|typedef|GimpRunFunc
typedef|typedef
name|GimpValueArray
modifier|*
function_decl|(
modifier|*
name|GimpRunFunc
function_decl|)
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PROCEDURE
define|#
directive|define
name|GIMP_TYPE_PROCEDURE
value|(gimp_procedure_get_type ())
end_define

begin_define
DECL|macro|GIMP_PROCEDURE (obj)
define|#
directive|define
name|GIMP_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROCEDURE, GimpProcedure))
end_define

begin_define
DECL|macro|GIMP_PROCEDURE_CLASS (klass)
define|#
directive|define
name|GIMP_PROCEDURE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PROCEDURE, GimpProcedureClass))
end_define

begin_define
DECL|macro|GIMP_IS_PROCEDURE (obj)
define|#
directive|define
name|GIMP_IS_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROCEDURE))
end_define

begin_define
DECL|macro|GIMP_IS_PROCEDURE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PROCEDURE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PROCEDURE))
end_define

begin_define
DECL|macro|GIMP_PROCEDURE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PROCEDURE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PROCEDURE, GimpProcedureClass))
end_define

begin_typedef
DECL|typedef|GimpProcedureClass
typedef|typedef
name|struct
name|_GimpProcedureClass
name|GimpProcedureClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpProcedurePrivate
typedef|typedef
name|struct
name|_GimpProcedurePrivate
name|GimpProcedurePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProcedure
struct|struct
name|_GimpProcedure
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpProcedurePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpProcedureClass
struct|struct
name|_GimpProcedureClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_procedure_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpProcedure
modifier|*
name|gimp_procedure_new
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpPDBProcType
name|proc_type
parameter_list|,
name|GimpRunFunc
name|run_func
parameter_list|,
name|gpointer
name|run_data
parameter_list|,
name|GDestroyNotify
name|run_data_destroy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugIn
modifier|*
name|gimp_procedure_get_plug_in
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_name
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPDBProcType
name|gimp_procedure_get_proc_type
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_menu_label
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_menu_label
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_documentation
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
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
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_blurb
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_help
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_help_id
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_attribution
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|authors
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_authors
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_copyright
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_date
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_image_types
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_types
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_procedure_get_image_types
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_icon
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpIconType
name|icon_type
parameter_list|,
specifier|const
name|guint8
modifier|*
name|icon_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpIconType
name|gimp_procedure_get_icon
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|guint8
modifier|*
modifier|*
name|icon_data
parameter_list|,
name|gint
modifier|*
name|icon_data_length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_menu_path
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_procedure_get_menu_paths
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_argument
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_argument_from_property
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prop_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_return_value
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_add_return_value_from_property
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prop_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GParamSpec
modifier|*
modifier|*
name|gimp_procedure_get_arguments
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gint
modifier|*
name|n_arguments
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GParamSpec
modifier|*
modifier|*
name|gimp_procedure_get_return_values
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gint
modifier|*
name|n_return_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_procedure_new_arguments
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_procedure_new_return_values
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpPDBStatusType
name|status
parameter_list|,
name|GError
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpValueArray
modifier|*
name|gimp_procedure_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_extension_ready
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
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
comment|/*  __GIMP_PROCEDURE_H__  */
end_comment

end_unit
