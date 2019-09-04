begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DISPLAY_IMPL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DISPLAY_IMPL_H__
define|#
directive|define
name|__GIMP_DISPLAY_IMPL_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpdisplay.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DISPLAY_IMPL
define|#
directive|define
name|GIMP_TYPE_DISPLAY_IMPL
value|(gimp_display_impl_get_type ())
end_define

begin_define
DECL|macro|GIMP_DISPLAY_IMPL (obj)
define|#
directive|define
name|GIMP_DISPLAY_IMPL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DISPLAY_IMPL, GimpDisplayImpl))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_IMPL_CLASS (klass)
define|#
directive|define
name|GIMP_DISPLAY_IMPL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DISPLAY_IMPL, GimpDisplayImplClass))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_IMPL (obj)
define|#
directive|define
name|GIMP_IS_DISPLAY_IMPL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DISPLAY_IMPL))
end_define

begin_define
DECL|macro|GIMP_IS_DISPLAY_IMPL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DISPLAY_IMPL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DISPLAY_IMPL))
end_define

begin_define
DECL|macro|GIMP_DISPLAY_IMPL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DISPLAY_IMPL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DISPLAY_IMPL, GimpDisplayImplClass))
end_define

begin_typedef
DECL|typedef|GimpDisplayImpl
typedef|typedef
name|struct
name|_GimpDisplayImpl
name|GimpDisplayImpl
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplayImplClass
typedef|typedef
name|struct
name|_GimpDisplayImplClass
name|GimpDisplayImplClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDisplayImplPrivate
typedef|typedef
name|struct
name|_GimpDisplayImplPrivate
name|GimpDisplayImplPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDisplayImpl
struct|struct
name|_GimpDisplayImpl
block|{
DECL|member|parent_instance
name|GimpDisplay
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpDisplayImplPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDisplayImplClass
struct|struct
name|_GimpDisplayImplClass
block|{
DECL|member|parent_class
name|GimpDisplayClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_display_impl_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDisplay
modifier|*
name|gimp_display_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|GimpUIManager
modifier|*
name|popup_manager
parameter_list|,
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_delete
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_close
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_display_get_action_name
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_display_get_image
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_set_image
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_display_get_instance
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDisplayShell
modifier|*
name|gimp_display_get_shell
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_empty
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_fill
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_update_area
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|now
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_flush
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_display_flush_now
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DISPLAY_IMPL_H__  */
end_comment

end_unit

