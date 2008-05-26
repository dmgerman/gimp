begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS  * file for a list of people on the GTK+ Team.  See the ChangeLog  * files for a list of changes.  These files are distributed with  * GTK+ at ftp://ftp.gtk.org/pub/gtk/.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HRULER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HRULER_H__
define|#
directive|define
name|__GIMP_HRULER_H__
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
DECL|macro|GIMP_TYPE_HRULER
define|#
directive|define
name|GIMP_TYPE_HRULER
value|(gimp_hruler_get_type ())
end_define

begin_define
DECL|macro|GIMP_HRULER (obj)
define|#
directive|define
name|GIMP_HRULER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HRULER, GimpHRuler))
end_define

begin_define
DECL|macro|GIMP_HRULER_CLASS (klass)
define|#
directive|define
name|GIMP_HRULER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HRULER, GimpHRulerClass))
end_define

begin_define
DECL|macro|GIMP_IS_HRULER (obj)
define|#
directive|define
name|GIMP_IS_HRULER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HRULER))
end_define

begin_define
DECL|macro|GIMP_IS_HRULER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HRULER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HRULER))
end_define

begin_define
DECL|macro|GIMP_HRULER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HRULER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HRULER, GimpHRulerClass))
end_define

begin_typedef
DECL|typedef|GimpHRulerClass
typedef|typedef
name|GimpRulerClass
name|GimpHRulerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHRuler
typedef|typedef
name|GimpRuler
name|GimpHRuler
typedef|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_hruler_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_hruler_new
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
comment|/* __GIMP_HRULER_H__ */
end_comment

end_unit

