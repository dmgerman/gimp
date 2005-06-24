begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpenumlabel.h  * Copyright (C) 2005  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ENUM__LABEL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ENUM__LABEL_H__
define|#
directive|define
name|__GIMP_ENUM__LABEL_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtklabel.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_ENUM_LABEL
define|#
directive|define
name|GIMP_TYPE_ENUM_LABEL
value|(gimp_enum_label_get_type ())
end_define

begin_define
DECL|macro|GIMP_ENUM_LABEL (obj)
define|#
directive|define
name|GIMP_ENUM_LABEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ENUM_LABEL, GimpEnumLabel))
end_define

begin_define
DECL|macro|GIMP_ENUM_LABEL_CLASS (klass)
define|#
directive|define
name|GIMP_ENUM_LABEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ENUM_LABEL, GimpEnumLabelClass))
end_define

begin_define
DECL|macro|GIMP_IS_ENUM_LABEL (obj)
define|#
directive|define
name|GIMP_IS_ENUM_LABEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ENUM_LABEL))
end_define

begin_define
DECL|macro|GIMP_IS_ENUM_LABEL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ENUM_LABEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ENUM_LABEL))
end_define

begin_define
DECL|macro|GIMP_ENUM_LABEL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ENUM_LABEL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ENUM_LABEL, GimpEnumLabelClass))
end_define

begin_typedef
DECL|typedef|GimpEnumLabelClass
typedef|typedef
name|struct
name|_GimpEnumLabelClass
name|GimpEnumLabelClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEnumLabel
struct|struct
name|_GimpEnumLabel
block|{
DECL|member|parent_instance
name|GtkLabel
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|enum_class
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEnumLabelClass
struct|struct
name|_GimpEnumLabelClass
block|{
DECL|member|parent_instance
name|GtkLabelClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_enum_label_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_enum_label_new
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_enum_label_set_value
parameter_list|(
name|GimpEnumLabel
modifier|*
name|label
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ENUM_LABEL_H__ */
end_comment

end_unit

