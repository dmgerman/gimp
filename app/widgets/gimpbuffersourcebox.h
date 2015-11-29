begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbuffersourcebox.h  * Copyright (C) 2015  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BUFFER_SOURCE_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BUFFER_SOURCE_BOX_H__
define|#
directive|define
name|__GIMP_BUFFER_SOURCE_BOX_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_BUFFER_SOURCE_BOX
define|#
directive|define
name|GIMP_TYPE_BUFFER_SOURCE_BOX
value|(gimp_buffer_source_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_BUFFER_SOURCE_BOX (obj)
define|#
directive|define
name|GIMP_BUFFER_SOURCE_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BUFFER_SOURCE_BOX, GimpBufferSourceBox))
end_define

begin_define
DECL|macro|GIMP_BUFFER_SOURCE_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_BUFFER_SOURCE_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BUFFER_SOURCE_BOX, GimpBufferSourceBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_BUFFER_SOURCE_BOX (obj)
define|#
directive|define
name|GIMP_IS_BUFFER_SOURCE_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BUFFER_SOURCE_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_BUFFER_SOURCE_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BUFFER_SOURCE_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BUFFER_SOURCE_BOX))
end_define

begin_define
DECL|macro|GIMP_BUFFER_SOURCE_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BUFFER_SOURCE_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BUFFER_SOURCE_BOX, GimpBufferSourceBoxClass))
end_define

begin_typedef
DECL|typedef|GimpBufferSourceBoxPrivate
typedef|typedef
name|struct
name|_GimpBufferSourceBoxPrivate
name|GimpBufferSourceBoxPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBufferSourceBoxClass
typedef|typedef
name|struct
name|_GimpBufferSourceBoxClass
name|GimpBufferSourceBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBufferSourceBox
struct|struct
name|_GimpBufferSourceBox
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpBufferSourceBoxPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBufferSourceBoxClass
struct|struct
name|_GimpBufferSourceBoxClass
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
name|gimp_buffer_source_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_buffer_source_box_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GeglNode
modifier|*
name|source_node
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BUFFER_SOURCE_BOX_H__  */
end_comment

end_unit

