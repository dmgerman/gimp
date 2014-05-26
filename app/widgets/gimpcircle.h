begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcircle.h  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * Based on code from the color-rotate plug-in  * Copyright (C) 1997-1999 Sven Anders (anderss@fmi.uni-passau.de)  *                         Based on code from Pavel Grinfeld (pavel@ml.com)  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CIRCLE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CIRCLE_H__
define|#
directive|define
name|__GIMP_CIRCLE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CIRCLE
define|#
directive|define
name|GIMP_TYPE_CIRCLE
value|(gimp_circle_get_type ())
end_define

begin_define
DECL|macro|GIMP_CIRCLE (obj)
define|#
directive|define
name|GIMP_CIRCLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CIRCLE, GimpCircle))
end_define

begin_define
DECL|macro|GIMP_CIRCLE_CLASS (klass)
define|#
directive|define
name|GIMP_CIRCLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CIRCLE, GimpCircleClass))
end_define

begin_define
DECL|macro|GIMP_IS_CIRCLE (obj)
define|#
directive|define
name|GIMP_IS_CIRCLE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_CIRCLE))
end_define

begin_define
DECL|macro|GIMP_IS_CIRCLE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CIRCLE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CIRCLE))
end_define

begin_define
DECL|macro|GIMP_CIRCLE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CIRCLE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CIRCLE, GimpCircleClass))
end_define

begin_typedef
DECL|typedef|GimpCirclePrivate
typedef|typedef
name|struct
name|_GimpCirclePrivate
name|GimpCirclePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCircleClass
typedef|typedef
name|struct
name|_GimpCircleClass
name|GimpCircleClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCircle
struct|struct
name|_GimpCircle
block|{
DECL|member|parent_instance
name|GtkWidget
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpCirclePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCircleClass
struct|struct
name|_GimpCircleClass
block|{
DECL|member|parent_class
name|GtkWidgetClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_circle_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_circle_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CIRCLE_H__ */
end_comment

end_unit

