begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

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

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_typedef
DECL|typedef|GimpMarshalFunc
typedef|typedef
name|GValueArray
modifier|*
function_decl|(
modifier|*
name|GimpMarshalFunc
function_decl|)
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GValueArray
modifier|*
name|args
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

begin_struct
DECL|struct|_GimpProcedure
struct|struct
name|_GimpProcedure
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|proc_type
name|GimpPDBProcType
name|proc_type
decl_stmt|;
comment|/* Type of procedure              */
DECL|member|static_strings
name|gboolean
name|static_strings
decl_stmt|;
comment|/* Are the strings allocated?     */
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* Procedure name                 */
DECL|member|original_name
name|gchar
modifier|*
name|original_name
decl_stmt|;
comment|/* Uncanonicalized procedure name */
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
comment|/* Short procedure description    */
DECL|member|help
name|gchar
modifier|*
name|help
decl_stmt|;
comment|/* Detailed help instructions     */
DECL|member|author
name|gchar
modifier|*
name|author
decl_stmt|;
comment|/* Author field                   */
DECL|member|copyright
name|gchar
modifier|*
name|copyright
decl_stmt|;
comment|/* Copyright field                */
DECL|member|date
name|gchar
modifier|*
name|date
decl_stmt|;
comment|/* Date field                     */
DECL|member|deprecated
name|gchar
modifier|*
name|deprecated
decl_stmt|;
comment|/* Replacement if deprecated      */
DECL|member|num_args
name|gint32
name|num_args
decl_stmt|;
comment|/* Number of procedure arguments  */
DECL|member|args
name|GParamSpec
modifier|*
modifier|*
name|args
decl_stmt|;
comment|/* Array of procedure arguments   */
DECL|member|num_values
name|gint32
name|num_values
decl_stmt|;
comment|/* Number of return values        */
DECL|member|values
name|GParamSpec
modifier|*
modifier|*
name|values
decl_stmt|;
comment|/* Array of return values         */
DECL|member|marshal_func
name|GimpMarshalFunc
name|marshal_func
decl_stmt|;
comment|/* Marshaller for internal procs  */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpProcedureClass
struct|struct
name|_GimpProcedureClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|execute
name|GValueArray
modifier|*
function_decl|(
modifier|*
name|execute
function_decl|)
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GValueArray
modifier|*
name|args
parameter_list|)
function_decl|;
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
name|GimpMarshalFunc
name|marshal_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_set_static_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_procedure_take_strings
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|,
name|gchar
modifier|*
name|original_name
parameter_list|,
name|gchar
modifier|*
name|blurb
parameter_list|,
name|gchar
modifier|*
name|help
parameter_list|,
name|gchar
modifier|*
name|author
parameter_list|,
name|gchar
modifier|*
name|copyright
parameter_list|,
name|gchar
modifier|*
name|date
parameter_list|,
name|gchar
modifier|*
name|deprecated
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
name|GValueArray
modifier|*
name|gimp_procedure_get_arguments
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GValueArray
modifier|*
name|gimp_procedure_get_return_values
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|gboolean
name|success
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GValueArray
modifier|*
name|gimp_procedure_execute
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GValueArray
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PROCEDURE_H__  */
end_comment

end_unit

