begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HISTOGRAM_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HISTOGRAM_EDITOR_H__
define|#
directive|define
name|__GIMP_HISTOGRAM_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gimpimageeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_HISTOGRAM_EDITOR
define|#
directive|define
name|GIMP_TYPE_HISTOGRAM_EDITOR
value|(gimp_histogram_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_EDITOR (obj)
define|#
directive|define
name|GIMP_HISTOGRAM_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HISTOGRAM_EDITOR, GimpHistogramEditor))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_HISTOGRAM_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HISTOGRAM_EDITOR, GimpHistogramEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_HISTOGRAM_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_HISTOGRAM_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HISTOGRAM_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HISTOGRAM_EDITOR))
end_define

begin_define
DECL|macro|GIMP_HISTOGRAM_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HISTOGRAM_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HISTOGRAM_EDITOR, GimpHistogramEditorClass))
end_define

begin_typedef
DECL|typedef|GimpHistogramEditorClass
typedef|typedef
name|struct
name|_GimpHistogramEditorClass
name|GimpHistogramEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHistogramEditor
struct|struct
name|_GimpHistogramEditor
block|{
DECL|member|parent_instance
name|GimpImageEditor
name|parent_instance
decl_stmt|;
DECL|member|trc
name|GimpTRCType
name|trc
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|histogram
name|GimpHistogram
modifier|*
name|histogram
decl_stmt|;
DECL|member|bg_histogram
name|GimpHistogram
modifier|*
name|bg_histogram
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|recompute
name|gboolean
name|recompute
decl_stmt|;
DECL|member|calculate_async
name|GimpAsync
modifier|*
name|calculate_async
decl_stmt|;
DECL|member|bg_pending
name|gboolean
name|bg_pending
decl_stmt|;
DECL|member|update_pending
name|gboolean
name|update_pending
decl_stmt|;
DECL|member|menu
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
DECL|member|box
name|GtkWidget
modifier|*
name|box
decl_stmt|;
DECL|member|labels
name|GtkWidget
modifier|*
name|labels
index|[
literal|6
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHistogramEditorClass
struct|struct
name|_GimpHistogramEditorClass
block|{
DECL|member|parent_class
name|GimpImageEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_histogram_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_histogram_editor_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HISTOGRAM_EDITOR_H__ */
end_comment

end_unit

