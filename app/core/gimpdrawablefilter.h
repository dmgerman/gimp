begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DRAWABLE_FILTER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DRAWABLE_FILTER_H__
define|#
directive|define
name|__GIMP_DRAWABLE_FILTER_H__
end_define

begin_include
include|#
directive|include
file|"gimpfilter.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DRAWABLE_FILTER
define|#
directive|define
name|GIMP_TYPE_DRAWABLE_FILTER
value|(gimp_drawable_filter_get_type ())
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_FILTER (obj)
define|#
directive|define
name|GIMP_DRAWABLE_FILTER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DRAWABLE_FILTER, GimpDrawableFilter))
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_FILTER_CLASS (klass)
define|#
directive|define
name|GIMP_DRAWABLE_FILTER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAWABLE_FILTER, GimpDrawableFilterClass))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_FILTER (obj)
define|#
directive|define
name|GIMP_IS_DRAWABLE_FILTER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DRAWABLE_FILTER))
end_define

begin_define
DECL|macro|GIMP_IS_DRAWABLE_FILTER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DRAWABLE_FILTER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAWABLE_FILTER))
end_define

begin_define
DECL|macro|GIMP_DRAWABLE_FILTER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DRAWABLE_FILTER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DRAWABLE_FILTER, GimpDrawableFilterClass))
end_define

begin_typedef
DECL|typedef|GimpDrawableFilterClass
typedef|typedef
name|struct
name|_GimpDrawableFilterClass
name|GimpDrawableFilterClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawableFilterClass
struct|struct
name|_GimpDrawableFilterClass
block|{
DECL|member|parent_class
name|GimpFilterClass
name|parent_class
decl_stmt|;
DECL|member|flush
name|void
function_decl|(
modifier|*
name|flush
function_decl|)
parameter_list|(
name|GimpDrawableFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Drawable Filter functions  */
end_comment

begin_comment
comment|/*  Successive apply() functions can be called, but eventually MUST be  *  followed with an commit() or an abort() call, both of which will  *  remove the live filter from the drawable.  */
end_comment

begin_decl_stmt
name|GType
name|gimp_drawable_filter_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDrawableFilter
modifier|*
name|gimp_drawable_filter_new
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglNode
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_filter_set_region
parameter_list|(
name|GimpDrawableFilter
modifier|*
name|filter
parameter_list|,
name|GimpFilterRegion
name|region
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_filter_set_preview
parameter_list|(
name|GimpDrawableFilter
modifier|*
name|filter
parameter_list|,
name|gboolean
name|enabled
parameter_list|,
name|GimpAlignmentType
name|alignment
parameter_list|,
name|gdouble
name|split_position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_filter_set_mode
parameter_list|(
name|GimpDrawableFilter
modifier|*
name|filter
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_filter_set_gamma_hack
parameter_list|(
name|GimpDrawableFilter
modifier|*
name|filter
parameter_list|,
name|gboolean
name|gamma_hack
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_filter_apply
parameter_list|(
name|GimpDrawableFilter
modifier|*
name|filter
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|area
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_drawable_filter_commit
parameter_list|(
name|GimpDrawableFilter
modifier|*
name|filter
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gboolean
name|cancellable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_drawable_filter_abort
parameter_list|(
name|GimpDrawableFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DRAWABLE_FILTER_H__ */
end_comment

end_unit

