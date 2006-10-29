begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpRc  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RC_H__
define|#
directive|define
name|__GIMP_RC_H__
end_define

begin_include
include|#
directive|include
file|"config/gimppluginconfig.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_RC
define|#
directive|define
name|GIMP_TYPE_RC
value|(gimp_rc_get_type ())
end_define

begin_define
DECL|macro|GIMP_RC (obj)
define|#
directive|define
name|GIMP_RC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_RC, GimpRc))
end_define

begin_define
DECL|macro|GIMP_RC_CLASS (klass)
define|#
directive|define
name|GIMP_RC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RC, GimpRcClass))
end_define

begin_define
DECL|macro|GIMP_IS_RC (obj)
define|#
directive|define
name|GIMP_IS_RC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_RC))
end_define

begin_define
DECL|macro|GIMP_IS_RC_CLASS (klass)
define|#
directive|define
name|GIMP_IS_RC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_RC))
end_define

begin_typedef
DECL|typedef|GimpRcClass
typedef|typedef
name|struct
name|_GimpRcClass
name|GimpRcClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRc
struct|struct
name|_GimpRc
block|{
DECL|member|parent_instance
name|GimpPluginConfig
name|parent_instance
decl_stmt|;
DECL|member|user_gimprc
name|gchar
modifier|*
name|user_gimprc
decl_stmt|;
DECL|member|system_gimprc
name|gchar
modifier|*
name|system_gimprc
decl_stmt|;
DECL|member|verbose
name|gboolean
name|verbose
decl_stmt|;
DECL|member|autosave
name|gboolean
name|autosave
decl_stmt|;
DECL|member|save_idle_id
name|guint
name|save_idle_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpRcClass
struct|struct
name|_GimpRcClass
block|{
DECL|member|parent_class
name|GimpPluginConfigClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_rc_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpRc
modifier|*
name|gimp_rc_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|system_gimprc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|user_gimprc
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rc_set_autosave
parameter_list|(
name|GimpRc
modifier|*
name|gimprc
parameter_list|,
name|gboolean
name|autosave
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rc_save
parameter_list|(
name|GimpRc
modifier|*
name|gimprc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_rc_query
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|key
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rc_set_unknown_token
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|token
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_rc_migrate
parameter_list|(
name|GimpRc
modifier|*
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_RC_H__ */
end_comment

end_unit

