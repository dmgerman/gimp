begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsizebox.h  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SIZE_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SIZE_BOX_H__
define|#
directive|define
name|__GIMP_SIZE_BOX_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_SIZE_BOX
define|#
directive|define
name|GIMP_TYPE_SIZE_BOX
value|(gimp_size_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_SIZE_BOX (obj)
define|#
directive|define
name|GIMP_SIZE_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SIZE_BOX, GimpSizeBox))
end_define

begin_define
DECL|macro|GIMP_SIZE_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_SIZE_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SIZE_BOX, GimpSizeBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_SIZE_BOX (obj)
define|#
directive|define
name|GIMP_IS_SIZE_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SIZE_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_SIZE_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SIZE_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SIZE_BOX))
end_define

begin_define
DECL|macro|GIMP_SIZE_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SIZE_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SIZE_BOX, GimpSizeBoxClass))
end_define

begin_typedef
DECL|typedef|GimpSizeBoxClass
typedef|typedef
name|struct
name|_GimpSizeBoxClass
name|GimpSizeBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSizeBox
struct|struct
name|_GimpSizeBox
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|size_group
name|GtkSizeGroup
modifier|*
name|size_group
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|xresolution
name|gdouble
name|xresolution
decl_stmt|;
DECL|member|yresolution
name|gdouble
name|yresolution
decl_stmt|;
DECL|member|resolution_unit
name|GimpUnit
name|resolution_unit
decl_stmt|;
DECL|member|edit_resolution
name|gboolean
name|edit_resolution
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSizeBoxClass
struct|struct
name|_GimpSizeBoxClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_size_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SIZE_BOX_H__ */
end_comment

end_unit

