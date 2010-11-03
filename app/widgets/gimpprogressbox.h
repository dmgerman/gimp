begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprogressbox.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROGRESS_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROGRESS_BOX_H__
define|#
directive|define
name|__GIMP_PROGRESS_BOX_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_PROGRESS_BOX
define|#
directive|define
name|GIMP_TYPE_PROGRESS_BOX
value|(gimp_progress_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_PROGRESS_BOX (obj)
define|#
directive|define
name|GIMP_PROGRESS_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROGRESS_BOX, GimpProgressBox))
end_define

begin_define
DECL|macro|GIMP_PROGRESS_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_PROGRESS_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PROGRESS_BOX, GimpProgressBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_PROGRESS_BOX (obj)
define|#
directive|define
name|GIMP_IS_PROGRESS_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROGRESS_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_PROGRESS_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PROGRESS_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PROGRESS_BOX))
end_define

begin_define
DECL|macro|GIMP_PROGRESS_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PROGRESS_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PROGRESS_BOX, GimpProgressBoxClass))
end_define

begin_typedef
DECL|typedef|GimpProgressBoxClass
typedef|typedef
name|struct
name|_GimpProgressBoxClass
name|GimpProgressBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProgressBox
struct|struct
name|_GimpProgressBox
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|active
name|gboolean
name|active
decl_stmt|;
DECL|member|cancelable
name|gboolean
name|cancelable
decl_stmt|;
DECL|member|value
name|gdouble
name|value
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|progress
name|GtkWidget
modifier|*
name|progress
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpProgressBoxClass
struct|struct
name|_GimpProgressBoxClass
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
name|gimp_progress_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_progress_box_new
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
comment|/* __GIMP_PROGRESS_BOX_H__ */
end_comment

end_unit

