begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpplugindef.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_DEF_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_DEF_H__
define|#
directive|define
name|__GIMP_PLUG_IN_DEF_H__
end_define

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PLUG_IN_DEF
define|#
directive|define
name|GIMP_TYPE_PLUG_IN_DEF
value|(gimp_plug_in_def_get_type ())
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_DEF (obj)
define|#
directive|define
name|GIMP_PLUG_IN_DEF
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PLUG_IN_DEF, GimpPlugInDef))
end_define

begin_define
DECL|macro|GIMP_PLUG_IN_DEF_CLASS (klass)
define|#
directive|define
name|GIMP_PLUG_IN_DEF_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PLUG_IN_DEF, GimpPlugInDefClass))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_DEF (obj)
define|#
directive|define
name|GIMP_IS_PLUG_IN_DEF
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PLUG_IN_DEF))
end_define

begin_define
DECL|macro|GIMP_IS_PLUG_IN_DEF_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PLUG_IN_DEF_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PLUG_IN_DEF))
end_define

begin_typedef
DECL|typedef|GimpPlugInDefClass
typedef|typedef
name|struct
name|_GimpPlugInDefClass
name|GimpPlugInDefClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugInDef
struct|struct
name|_GimpPlugInDef
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|prog
name|gchar
modifier|*
name|prog
decl_stmt|;
DECL|member|procedures
name|GSList
modifier|*
name|procedures
decl_stmt|;
DECL|member|locale_domain_name
name|gchar
modifier|*
name|locale_domain_name
decl_stmt|;
DECL|member|locale_domain_path
name|gchar
modifier|*
name|locale_domain_path
decl_stmt|;
DECL|member|help_domain_name
name|gchar
modifier|*
name|help_domain_name
decl_stmt|;
DECL|member|help_domain_uri
name|gchar
modifier|*
name|help_domain_uri
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|needs_query
name|gboolean
name|needs_query
decl_stmt|;
comment|/* Does the plug-in need to be queried ?     */
DECL|member|has_init
name|gboolean
name|has_init
decl_stmt|;
comment|/* Does the plug-in need to be initialized ? */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPlugInDefClass
struct|struct
name|_GimpPlugInDefClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_plug_in_def_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPlugInDef
modifier|*
name|gimp_plug_in_def_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|prog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_def_add_procedure
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_def_remove_procedure
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|GimpPlugInProcedure
modifier|*
name|proc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_def_set_locale_domain
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
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
name|void
name|gimp_plug_in_def_set_help_domain
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
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
name|void
name|gimp_plug_in_def_set_mtime
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|time_t
name|mtime
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_def_set_needs_query
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|gboolean
name|needs_query
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_plug_in_def_set_has_init
parameter_list|(
name|GimpPlugInDef
modifier|*
name|plug_in_def
parameter_list|,
name|gboolean
name|has_init
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PLUG_IN_DEF_H__ */
end_comment

end_unit

