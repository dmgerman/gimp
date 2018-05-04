begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppreview.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREVIEW_H__
define|#
directive|define
name|__GIMP_PREVIEW_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PREVIEW
define|#
directive|define
name|GIMP_TYPE_PREVIEW
value|(gimp_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_PREVIEW (obj)
define|#
directive|define
name|GIMP_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PREVIEW, GimpPreview))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREVIEW, GimpPreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PREVIEW, GimpPreviewClass))
end_define

begin_typedef
DECL|typedef|GimpPreviewPrivate
typedef|typedef
name|struct
name|_GimpPreviewPrivate
name|GimpPreviewPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewClass
typedef|typedef
name|struct
name|_GimpPreviewClass
name|GimpPreviewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPreview
struct|struct
name|_GimpPreview
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpPreviewPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPreviewClass
struct|struct
name|_GimpPreviewClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
comment|/* virtual methods */
DECL|member|draw
name|void
function_decl|(
modifier|*
name|draw
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
DECL|member|draw_thumb
name|void
function_decl|(
modifier|*
name|draw_thumb
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GimpPreviewArea
modifier|*
name|area
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
DECL|member|draw_buffer
name|void
function_decl|(
modifier|*
name|draw_buffer
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
name|rowstride
parameter_list|)
function_decl|;
DECL|member|set_cursor
name|void
function_decl|(
modifier|*
name|set_cursor
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
DECL|member|transform
name|void
function_decl|(
modifier|*
name|transform
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|)
function_decl|;
DECL|member|untransform
name|void
function_decl|(
modifier|*
name|untransform
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|)
function_decl|;
comment|/* signal */
DECL|member|invalidated
name|void
function_decl|(
modifier|*
name|invalidated
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_preview_set_update
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gboolean
name|update
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_preview_get_update
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_bounds
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|xmin
parameter_list|,
name|gint
name|ymin
parameter_list|,
name|gint
name|xmax
parameter_list|,
name|gint
name|ymax
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_get_bounds
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
modifier|*
name|xmin
parameter_list|,
name|gint
modifier|*
name|ymin
parameter_list|,
name|gint
modifier|*
name|xmax
parameter_list|,
name|gint
modifier|*
name|ymax
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_size
parameter_list|(
name|GimpPreview
modifier|*
name|preview
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
name|void
name|gimp_preview_get_size
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_offsets
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|xoff
parameter_list|,
name|gint
name|yoff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_get_offsets
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
modifier|*
name|xoff
parameter_list|,
name|gint
modifier|*
name|yoff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_get_position
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_transform
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_untransform
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|src_x
parameter_list|,
name|gint
name|src_y
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_preview_get_frame
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_preview_get_table
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_preview_get_area
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_draw
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_draw_buffer
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
specifier|const
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
name|rowstride
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_invalidate
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_default_cursor
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GdkCursor
modifier|*
name|cursor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkCursor
modifier|*
name|gimp_preview_get_default_cursor
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_preview_get_controls
parameter_list|(
name|GimpPreview
modifier|*
name|preview
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
comment|/* __GIMP_PREVIEW_H__ */
end_comment

end_unit

