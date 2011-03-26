begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SELECTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SELECTION_H__
define|#
directive|define
name|__GIMP_SELECTION_H__
end_define

begin_include
include|#
directive|include
file|"gimpchannel.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SELECTION
define|#
directive|define
name|GIMP_TYPE_SELECTION
value|(gimp_selection_get_type ())
end_define

begin_define
DECL|macro|GIMP_SELECTION (obj)
define|#
directive|define
name|GIMP_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SELECTION, GimpSelection))
end_define

begin_define
DECL|macro|GIMP_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SELECTION, GimpSelectionClass))
end_define

begin_define
DECL|macro|GIMP_IS_SELECTION (obj)
define|#
directive|define
name|GIMP_IS_SELECTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SELECTION))
end_define

begin_define
DECL|macro|GIMP_IS_SELECTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SELECTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SELECTION))
end_define

begin_define
DECL|macro|GIMP_SELECTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SELECTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SELECTION, GimpSelectionClass))
end_define

begin_typedef
DECL|typedef|GimpSelectionClass
typedef|typedef
name|struct
name|_GimpSelectionClass
name|GimpSelectionClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSelection
struct|struct
name|_GimpSelection
block|{
DECL|member|parent_instance
name|GimpChannel
name|parent_instance
decl_stmt|;
DECL|member|stroking_count
name|gint
name|stroking_count
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSelectionClass
struct|struct
name|_GimpSelectionClass
block|{
DECL|member|parent_class
name|GimpChannelClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_selection_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_selection_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_selection_push_stroking
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_selection_pop_stroking
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_selection_load
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|,
name|GimpChannel
modifier|*
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpChannel
modifier|*
name|gimp_selection_save
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TileManager
modifier|*
name|gimp_selection_extract
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|,
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|cut_image
parameter_list|,
name|gboolean
name|keep_indexed
parameter_list|,
name|gboolean
name|add_alpha
parameter_list|,
name|gint
modifier|*
name|offset_x
parameter_list|,
name|gint
modifier|*
name|offset_y
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_selection_float
parameter_list|(
name|GimpSelection
modifier|*
name|selection
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|cut_image
parameter_list|,
name|gint
name|off_x
parameter_list|,
name|gint
name|off_y
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SELECTION_H__ */
end_comment

end_unit

