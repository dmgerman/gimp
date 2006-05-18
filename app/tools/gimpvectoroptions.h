begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VECTOR_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VECTOR_OPTIONS_H__
define|#
directive|define
name|__GIMP_VECTOR_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"core/gimptooloptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_VECTOR_OPTIONS
define|#
directive|define
name|GIMP_TYPE_VECTOR_OPTIONS
value|(gimp_vector_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_VECTOR_OPTIONS (obj)
define|#
directive|define
name|GIMP_VECTOR_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VECTOR_OPTIONS, GimpVectorOptions))
end_define

begin_define
DECL|macro|GIMP_VECTOR_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_VECTOR_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VECTOR_OPTIONS, GimpVectorOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_VECTOR_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_VECTOR_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VECTOR_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_VECTOR_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VECTOR_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VECTOR_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_VECTOR_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VECTOR_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VECTOR_OPTIONS, GimpVectorOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpVectorOptions
typedef|typedef
name|struct
name|_GimpVectorOptions
name|GimpVectorOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVectorOptionsClass
typedef|typedef
name|struct
name|_GimpToolOptionsClass
name|GimpVectorOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpVectorOptions
struct|struct
name|_GimpVectorOptions
block|{
DECL|member|parent_instance
name|GimpToolOptions
name|parent_instance
decl_stmt|;
DECL|member|edit_mode
name|GimpVectorMode
name|edit_mode
decl_stmt|;
DECL|member|polygonal
name|gboolean
name|polygonal
decl_stmt|;
comment|/*  options gui  */
DECL|member|to_selection_button
name|GtkWidget
modifier|*
name|to_selection_button
decl_stmt|;
DECL|member|stroke_button
name|GtkWidget
modifier|*
name|stroke_button
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_vector_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_vector_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_VECTOR_OPTIONS_H__  */
end_comment

end_unit

