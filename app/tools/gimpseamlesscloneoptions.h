begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpseamlesscloneoptions.h  * Copyright (C) 2011 Barak Itkin<lightningismyname@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SEAMLESS_CLONE_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SEAMLESS_CLONE_OPTIONS_H__
define|#
directive|define
name|__GIMP_SEAMLESS_CLONE_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SEAMLESS_CLONE_OPTIONS
define|#
directive|define
name|GIMP_TYPE_SEAMLESS_CLONE_OPTIONS
value|(gimp_seamless_clone_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_SEAMLESS_CLONE_OPTIONS (obj)
define|#
directive|define
name|GIMP_SEAMLESS_CLONE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SEAMLESS_CLONE_OPTIONS, GimpSeamlessCloneOptions))
end_define

begin_define
DECL|macro|GIMP_SEAMLESS_CLONE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_SEAMLESS_CLONE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SEAMLESS_CLONE_OPTIONS, GimpSeamlessCloneOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_SEAMLESS_CLONE_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_SEAMLESS_CLONE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SEAMLESS_CLONE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_SEAMLESS_CLONE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SEAMLESS_CLONE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SEAMLESS_CLONE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_SEAMLESS_CLONE_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SEAMLESS_CLONE_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SEAMLESS_CLONE_OPTIONS, GimpSeamlessCloneOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpSeamlessCloneOptions
typedef|typedef
name|struct
name|_GimpSeamlessCloneOptions
name|GimpSeamlessCloneOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSeamlessCloneOptionsClass
typedef|typedef
name|struct
name|_GimpSeamlessCloneOptionsClass
name|GimpSeamlessCloneOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSeamlessCloneOptions
struct|struct
name|_GimpSeamlessCloneOptions
block|{
DECL|member|parent_instance
name|GimpToolOptions
name|parent_instance
decl_stmt|;
DECL|member|max_refine_scale
name|gint
name|max_refine_scale
decl_stmt|;
DECL|member|temp
name|gboolean
name|temp
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSeamlessCloneOptionsClass
struct|struct
name|_GimpSeamlessCloneOptionsClass
block|{
DECL|member|parent_class
name|GimpToolOptionsClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_seamless_clone_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_seamless_clone_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SEAMLESS_CLONE_OPTIONS_H__  */
end_comment

end_unit

