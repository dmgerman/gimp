begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VRULER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VRULER_H__
define|#
directive|define
name|__GIMP_VRULER_H__
end_define

begin_include
include|#
directive|include
file|"gimpruler.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_VRULER
define|#
directive|define
name|GIMP_TYPE_VRULER
value|(gimp_vruler_get_type ())
end_define

begin_define
DECL|macro|GIMP_VRULER (obj)
define|#
directive|define
name|GIMP_VRULER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VRULER, GimpVRuler))
end_define

begin_define
DECL|macro|GIMP_VRULER_CLASS (klass)
define|#
directive|define
name|GIMP_VRULER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VRULER, GimpVRulerClass))
end_define

begin_define
DECL|macro|GIMP_IS_VRULER (obj)
define|#
directive|define
name|GIMP_IS_VRULER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VRULER))
end_define

begin_define
DECL|macro|GIMP_IS_VRULER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VRULER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VRULER))
end_define

begin_define
DECL|macro|GIMP_VRULER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VRULER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VRULER, GimpVRulerClass))
end_define

begin_typedef
DECL|typedef|GimpVRulerClass
typedef|typedef
name|GimpRulerClass
name|GimpVRulerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVRuler
typedef|typedef
name|GimpRuler
name|GimpVRuler
typedef|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_vruler_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_vruler_new
parameter_list|(
name|void
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
comment|/* __GIMP_VRULER_H__ */
end_comment

end_unit

