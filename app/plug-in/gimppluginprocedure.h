begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginprocedure.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_PROCEDURE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_PROCEDURE_H__
define|#
directive|define
name|__GIMP_PLUG_IN_PROCEDURE_H__
end_define

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_comment
comment|/* time_t */
end_comment

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"pdb/gimpprocedure.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PLUG_IN_PROCEDURE
define|#
directive|define
name|GIMP_TYPE_PLUG_IN_PROCEDURE
value|(gimp_plug_in_procedure_get_type ())
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_PROCEDURE (obj)
define|#
directive|define
name|GIMP_PLUG_IN_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PLUG_IN_PROCEDURE, GimpPlugInProcedure))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_PROCEDURE_CLASS (klass)
define|#
directive|define
name|GIMP_PLUG_IN_PROCEDURE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PLUG_IN_PROCEDURE, GimpPlugInProcedureClass))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_PROCEDURE (obj)
define|#
directive|define
name|GIMP_IS_PLUG_IN_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PLUG_IN_PROCEDURE))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_PROCEDURE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PLUG_IN_PROCEDURE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PLUG_IN_PROCEDURE))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_PROCEDURE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PLUG_IN_PROCEDURE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PLUG_IN_PROCEDURE, GimpPlugInProcedureClass))
end_define

begin_typedef
DECL|typedef|GimpPlugInProcedureClass
typedef|typedef
name|struct
name|_GimpPlugInProcedureClass
name|GimpPlugInProcedureClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugInProcedure
struct|struct
name|_GimpPlugInProcedure
block|{
DECL|member|parent_instance
name|GimpProcedure
name|parent_instance
decl_stmt|;
comment|/*  common members  */
DECL|member|prog
name|gchar
modifier|*
name|prog
decl_stmt|;
DECL|member|menu_label
name|gchar
modifier|*
name|menu_label
decl_stmt|;
DECL|member|menu_paths
name|GList
modifier|*
name|menu_paths
decl_stmt|;
DECL|member|icon_type
name|GimpIconType
name|icon_type
decl_stmt|;
DECL|member|icon_data_length
name|gint
name|icon_data_length
decl_stmt|;
DECL|member|icon_data
name|guint8
modifier|*
name|icon_data
decl_stmt|;
DECL|member|image_types
name|gchar
modifier|*
name|image_types
decl_stmt|;
DECL|member|image_types_val
name|GimpPlugInImageType
name|image_types_val
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|installed_during_init
name|gboolean
name|installed_during_init
decl_stmt|;
comment|/*  file proc specific members  */
DECL|member|file_proc
name|gboolean
name|file_proc
decl_stmt|;
DECL|member|extensions
name|gchar
modifier|*
name|extensions
decl_stmt|;
DECL|member|prefixes
name|gchar
modifier|*
name|prefixes
decl_stmt|;
DECL|member|magics
name|gchar
modifier|*
name|magics
decl_stmt|;
DECL|member|mime_type
name|gchar
modifier|*
name|mime_type
decl_stmt|;
DECL|member|extensions_list
name|GSList
modifier|*
name|extensions_list
decl_stmt|;
DECL|member|prefixes_list
name|GSList
modifier|*
name|prefixes_list
decl_stmt|;
DECL|member|magics_list
name|GSList
modifier|*
name|magics_list
decl_stmt|;
DECL|member|thumb_loader
name|gchar
modifier|*
name|thumb_loader
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPlugInProcedureClass
struct|struct
name|_GimpPlugInProcedureClass
block|{
DECL|member|parent_class
name|GimpProcedureClass
name|parent_class
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|get_progname
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_progname
function_decl|)
parameter_list|(
specifier|const
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|menu_path_added
name|void
function_decl|(
modifier|*
name|menu_path_added
function_decl|)
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_plug_in_procedure_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpProcedure
modifier|*
name|gimp_plug_in_procedure_new
parameter_list|(
name|GimpPDBProcType
name|proc_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPlugInProcedure
modifier|*
name|gimp_plug_in_procedure_find
parameter_list|(
name|GSList
modifier|*
name|list
parameter_list|,
specifier|const
name|gchar
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_plug_in_procedure_get_progname
parameter_list|(
specifier|const
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plug_in_procedure_add_menu_path
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_plug_in_procedure_get_label
parameter_list|(
specifier|const
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|locale_domain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_procedure_set_icon
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
name|GimpIconType
name|type
parameter_list|,
specifier|const
name|guint8
modifier|*
name|data
parameter_list|,
name|gint
name|data_length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_plug_in_procedure_get_stock_id
parameter_list|(
specifier|const
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|gimp_plug_in_procedure_get_pixbuf
parameter_list|(
specifier|const
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_plug_in_procedure_get_help_id
parameter_list|(
specifier|const
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_plug_in_procedure_get_sensitive
parameter_list|(
specifier|const
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
name|GimpImageType
name|image_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_procedure_set_image_types
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|image_types
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_procedure_set_file_proc
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|proc
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
name|void
name|gimp_plug_in_procedure_set_mime_type
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_ype
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_procedure_set_thumb_loader
parameter_list|(
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thumbnailer
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_PROCEDURE_H__ */
end_comment

end_unit

