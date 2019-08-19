begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpthumbnailprocedure.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THUMBNAIL_PROCEDURE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THUMBNAIL_PROCEDURE_H__
define|#
directive|define
name|__GIMP_THUMBNAIL_PROCEDURE_H__
end_define

begin_include
include|#
directive|include
file|<libgimp/gimpprocedure.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_comment
comment|/**  * GimpRunThumbnailFunc:  * @procedure:   the #GimpProcedure that runs.  * @file:        the #GFile to load the thumbnail from.  * @size:        the requested thumbnail size.  * @args:        the @procedure's remaining arguments.  * @run_data:    the run_data given in gimp_thumbnail_procedure_new().  *  * The thumbnail function is run during the lifetime of the GIMP session,  * each time a plug-in thumbnail procedure is called.  *  * Returns: (transfer full): the @procedure's return values.  *  * Since: 3.0  **/
end_comment

begin_typedef
DECL|typedef|GimpRunThumbnailFunc
typedef|typedef
name|GimpValueArray
modifier|*
function_decl|(
modifier|*
name|GimpRunThumbnailFunc
function_decl|)
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
name|gint
name|size
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
DECL|macro|GIMP_TYPE_THUMBNAIL_PROCEDURE
define|#
directive|define
name|GIMP_TYPE_THUMBNAIL_PROCEDURE
value|(gimp_thumbnail_procedure_get_type ())
end_define

begin_define
DECL|macro|GIMP_THUMBNAIL_PROCEDURE (obj)
define|#
directive|define
name|GIMP_THUMBNAIL_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_THUMBNAIL_PROCEDURE, GimpThumbnailProcedure))
end_define

begin_define
DECL|macro|GIMP_THUMBNAIL_PROCEDURE_CLASS (klass)
define|#
directive|define
name|GIMP_THUMBNAIL_PROCEDURE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_THUMBNAIL_PROCEDURE, GimpThumbnailProcedureClass))
end_define

begin_define
DECL|macro|GIMP_IS_THUMBNAIL_PROCEDURE (obj)
define|#
directive|define
name|GIMP_IS_THUMBNAIL_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_THUMBNAIL_PROCEDURE))
end_define

begin_define
DECL|macro|GIMP_IS_THUMBNAIL_PROCEDURE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_THUMBNAIL_PROCEDURE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_THUMBNAIL_PROCEDURE))
end_define

begin_define
DECL|macro|GIMP_THUMBNAIL_PROCEDURE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_THUMBNAIL_PROCEDURE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_THUMBNAIL_PROCEDURE, GimpThumbnailProcedureClass))
end_define

begin_typedef
DECL|typedef|GimpThumbnailProcedure
typedef|typedef
name|struct
name|_GimpThumbnailProcedure
name|GimpThumbnailProcedure
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThumbnailProcedureClass
typedef|typedef
name|struct
name|_GimpThumbnailProcedureClass
name|GimpThumbnailProcedureClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThumbnailProcedurePrivate
typedef|typedef
name|struct
name|_GimpThumbnailProcedurePrivate
name|GimpThumbnailProcedurePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpThumbnailProcedure
struct|struct
name|_GimpThumbnailProcedure
block|{
DECL|member|parent_instance
name|GimpProcedure
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpThumbnailProcedurePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpThumbnailProcedureClass
struct|struct
name|_GimpThumbnailProcedureClass
block|{
DECL|member|parent_class
name|GimpProcedureClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_thumbnail_procedure_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpProcedure
modifier|*
name|gimp_thumbnail_procedure_new
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
name|GimpRunThumbnailFunc
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

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_THUMBNAIL_PROCEDURE_H__  */
end_comment

end_unit

