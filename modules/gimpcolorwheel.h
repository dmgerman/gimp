begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* HSV color selector for GTK+  *  * Copyright (C) 1999 The Free Software Foundation  *  * Authors: Simon Budig<Simon.Budig@unix-ag.org> (original code)  *          Federico Mena-Quintero<federico@gimp.org> (cleanup for GTK+)  *          Jonathan Blandford<jrb@redhat.com> (cleanup for GTK+)  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS  * file for a list of people on the GTK+ Team.  See the ChangeLog  * files for a list of changes.  These files are distributed with  * GTK+ at ftp://ftp.gtk.org/pub/gtk/.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_WHEEL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_WHEEL_H__
define|#
directive|define
name|__GIMP_COLOR_WHEEL_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_COLOR_WHEEL
define|#
directive|define
name|GIMP_TYPE_COLOR_WHEEL
value|(gimp_color_wheel_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_WHEEL (obj)
define|#
directive|define
name|GIMP_COLOR_WHEEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_WHEEL, GimpColorWheel))
end_define

begin_define
DECL|macro|GIMP_COLOR_WHEEL_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_WHEEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_WHEEL, GimpColorWheelClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_WHEEL (obj)
define|#
directive|define
name|GIMP_IS_COLOR_WHEEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_WHEEL))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_WHEEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_WHEEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_WHEEL))
end_define

begin_define
DECL|macro|GIMP_COLOR_WHEEL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_WHEEL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_WHEEL, GimpColorWheelClass))
end_define

begin_typedef
DECL|typedef|GimpColorWheel
typedef|typedef
name|struct
name|_GimpColorWheel
name|GimpColorWheel
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorWheelClass
typedef|typedef
name|struct
name|_GimpColorWheelClass
name|GimpColorWheelClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorWheel
struct|struct
name|_GimpColorWheel
block|{
DECL|member|parent_instance
name|GtkWidget
name|parent_instance
decl_stmt|;
comment|/* Private data */
DECL|member|priv
name|gpointer
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorWheelClass
struct|struct
name|_GimpColorWheelClass
block|{
DECL|member|parent_class
name|GtkWidgetClass
name|parent_class
decl_stmt|;
comment|/* Notification signals */
DECL|member|changed
name|void
function_decl|(
modifier|*
name|changed
function_decl|)
parameter_list|(
name|GimpColorWheel
modifier|*
name|wheel
parameter_list|)
function_decl|;
comment|/* Keybindings */
DECL|member|move
name|void
function_decl|(
modifier|*
name|move
function_decl|)
parameter_list|(
name|GimpColorWheel
modifier|*
name|wheel
parameter_list|,
name|GtkDirectionType
name|type
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|color_wheel_register_type
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_color_wheel_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_wheel_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_wheel_set_color
parameter_list|(
name|GimpColorWheel
modifier|*
name|wheel
parameter_list|,
name|double
name|h
parameter_list|,
name|double
name|s
parameter_list|,
name|double
name|v
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_wheel_get_color
parameter_list|(
name|GimpColorWheel
modifier|*
name|wheel
parameter_list|,
name|gdouble
modifier|*
name|h
parameter_list|,
name|gdouble
modifier|*
name|s
parameter_list|,
name|gdouble
modifier|*
name|v
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_wheel_set_ring_fraction
parameter_list|(
name|GimpColorWheel
modifier|*
name|wheel
parameter_list|,
name|gdouble
name|fraction
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_color_wheel_get_ring_fraction
parameter_list|(
name|GimpColorWheel
modifier|*
name|wheel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_wheel_set_color_config
parameter_list|(
name|GimpColorWheel
modifier|*
name|wheel
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_color_wheel_is_adjusting
parameter_list|(
name|GimpColorWheel
modifier|*
name|wheel
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
comment|/* __GIMP_COLOR_WHEEL_H__ */
end_comment

end_unit

