begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerbox.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_BOX_H__
define|#
directive|define
name|__GIMP_CONTAINER_BOX_H__
end_define

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_BOX
define|#
directive|define
name|GIMP_TYPE_CONTAINER_BOX
value|(gimp_container_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_BOX (obj)
define|#
directive|define
name|GIMP_CONTAINER_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_BOX, GimpContainerBox))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_BOX, GimpContainerBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_BOX (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_BOX))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_BOX, GimpContainerBoxClass))
end_define

begin_typedef
DECL|typedef|GimpContainerBoxClass
typedef|typedef
name|struct
name|_GimpContainerBoxClass
name|GimpContainerBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerBox
struct|struct
name|_GimpContainerBox
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|scrolled_win
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerBoxClass
struct|struct
name|_GimpContainerBoxClass
block|{
DECL|member|parent_class
name|GimpEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_container_box_set_size_request
parameter_list|(
name|GimpContainerBox
modifier|*
name|box
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_BOX_H__  */
end_comment

end_unit

