begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald  *  * GtkHWrapBox: Horizontal wrapping box widget  * Copyright (C) 1999 Tim Janik  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONSTRAINED_HWRAP_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONSTRAINED_HWRAP_BOX_H__
define|#
directive|define
name|__GIMP_CONSTRAINED_HWRAP_BOX_H__
end_define

begin_include
include|#
directive|include
file|"gtkhwrapbox.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CONSTRAINED_HWRAP_BOX
define|#
directive|define
name|GIMP_TYPE_CONSTRAINED_HWRAP_BOX
value|(gimp_constrained_hwrap_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONSTRAINED_HWRAP_BOX (obj)
define|#
directive|define
name|GIMP_CONSTRAINED_HWRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONSTRAINED_HWRAP_BOX, GimpConstrainedHWrapBox))
end_define

begin_define
DECL|macro|GIMP_CONSTRAINED_HWRAP_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_CONSTRAINED_HWRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONSTRAINED_HWRAP_BOX, GimpConstrainedHWrapBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONSTRAINED_HWRAP_BOX (obj)
define|#
directive|define
name|GIMP_IS_CONSTRAINED_HWRAP_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONSTRAINED_HWRAP_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_CONSTRAINED_HWRAP_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONSTRAINED_HWRAP_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONSTRAINED_HWRAP_BOX))
end_define

begin_define
DECL|macro|GIMP_CONSTRAINED_HWRAP_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONSTRAINED_HWRAP_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(GIMP_CONSTRAINED_HWRAP_BOX_CLASS (((GtkObject *) (obj))->klass))
end_define

begin_typedef
DECL|typedef|GimpConstrainedHWrapBox
typedef|typedef
name|struct
name|_GimpConstrainedHWrapBox
name|GimpConstrainedHWrapBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpConstrainedHWrapBoxClass
typedef|typedef
name|struct
name|_GimpConstrainedHWrapBoxClass
name|GimpConstrainedHWrapBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpConstrainedHWrapBox
struct|struct
name|_GimpConstrainedHWrapBox
block|{
DECL|member|parent_instance
name|GtkHWrapBox
name|parent_instance
decl_stmt|;
DECL|member|rows
name|guint
name|rows
decl_stmt|;
DECL|member|columns
name|guint
name|columns
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpConstrainedHWrapBoxClass
struct|struct
name|_GimpConstrainedHWrapBoxClass
block|{
DECL|member|parent_class
name|GtkHWrapBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GtkType
name|gimp_constrained_hwrap_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_constrained_hwrap_box_new
parameter_list|(
name|gboolean
name|homogeneous
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GTK_CONSTRAINED_HWRAP_BOX_H__ */
end_comment

end_unit

