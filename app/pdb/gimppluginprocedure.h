begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in-proc-def.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_PROC_DEF_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_PROC_DEF_H__
define|#
directive|define
name|__PLUG_IN_PROC_DEF_H__
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
file|"pdb/procedural_db.h"
end_include

begin_comment
comment|/* ProcRecord */
end_comment

begin_struct
DECL|struct|_PlugInProcDef
struct|struct
name|_PlugInProcDef
block|{
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
name|gchar
modifier|*
name|icon_data
decl_stmt|;
DECL|member|image_types
name|gchar
modifier|*
name|image_types
decl_stmt|;
DECL|member|image_types_val
name|PlugInImageType
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
DECL|member|db_info
name|ProcRecord
name|db_info
decl_stmt|;
comment|/*  file proc specific members  */
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
block|}
struct|;
end_struct

begin_function_decl
name|PlugInProcDef
modifier|*
name|plug_in_proc_def_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|plug_in_proc_def_free
parameter_list|(
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|ProcRecord
modifier|*
name|plug_in_proc_def_get_proc
parameter_list|(
specifier|const
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|plug_in_proc_def_get_progname
parameter_list|(
specifier|const
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|plug_in_proc_def_get_label
parameter_list|(
specifier|const
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|locale_domain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|plug_in_proc_def_get_stock_id
parameter_list|(
specifier|const
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkPixbuf
modifier|*
name|plug_in_proc_def_get_pixbuf
parameter_list|(
specifier|const
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|plug_in_proc_def_get_help_id
parameter_list|(
specifier|const
name|PlugInProcDef
modifier|*
name|proc_def
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
name|plug_in_proc_def_get_sensitive
parameter_list|(
specifier|const
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|,
name|GimpImageType
name|image_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_PROC_DEF_H__ */
end_comment

end_unit

