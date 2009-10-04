begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpuiconfigurer.h  * Copyright (C) 2009 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UI_CONFIGURER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UI_CONFIGURER_H__
define|#
directive|define
name|__GIMP_UI_CONFIGURER_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_UI_CONFIGURER
define|#
directive|define
name|GIMP_TYPE_UI_CONFIGURER
value|(gimp_ui_configurer_get_type ())
end_define

begin_define
DECL|macro|GIMP_UI_CONFIGURER (obj)
define|#
directive|define
name|GIMP_UI_CONFIGURER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_UI_CONFIGURER, GimpUIConfigurer))
end_define

begin_define
DECL|macro|GIMP_UI_CONFIGURER_CLASS (vtable)
define|#
directive|define
name|GIMP_UI_CONFIGURER_CLASS
parameter_list|(
name|vtable
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((vtable), GIMP_TYPE_UI_CONFIGURER, GimpUIConfigurerClass))
end_define

begin_define
DECL|macro|GIMP_IS_UI_CONFIGURER (obj)
define|#
directive|define
name|GIMP_IS_UI_CONFIGURER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_UI_CONFIGURER))
end_define

begin_define
DECL|macro|GIMP_IS_UI_CONFIGURER_CLASS (vtable)
define|#
directive|define
name|GIMP_IS_UI_CONFIGURER_CLASS
parameter_list|(
name|vtable
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((vtable), GIMP_TYPE_UI_CONFIGURER))
end_define

begin_define
DECL|macro|GIMP_UI_CONFIGURER_GET_CLASS (inst)
define|#
directive|define
name|GIMP_UI_CONFIGURER_GET_CLASS
parameter_list|(
name|inst
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((inst), GIMP_TYPE_UI_CONFIGURER, GimpUIConfigurerClass))
end_define

begin_typedef
DECL|typedef|GimpUIConfigurerClass
typedef|typedef
name|struct
name|_GimpUIConfigurerClass
name|GimpUIConfigurerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUIConfigurerPrivate
typedef|typedef
name|struct
name|_GimpUIConfigurerPrivate
name|GimpUIConfigurerPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUIConfigurer
struct|struct
name|_GimpUIConfigurer
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpUIConfigurerPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpUIConfigurerClass
struct|struct
name|_GimpUIConfigurerClass
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
name|gimp_ui_configurer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_ui_configurer_configure
parameter_list|(
name|GimpUIConfigurer
modifier|*
name|ui_configurer
parameter_list|,
name|gboolean
name|single_window_mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UI_CONFIGURER_H__ */
end_comment

end_unit

