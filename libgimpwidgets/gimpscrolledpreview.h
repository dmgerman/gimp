begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpscrolledpreview.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
name|__GIMP_SCROLLED_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SCROLLED_PREVIEW_H__
define|#
directive|define
name|__GIMP_SCROLLED_PREVIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_SCROLLED_PREVIEW
define|#
directive|define
name|GIMP_TYPE_SCROLLED_PREVIEW
value|(gimp_scrolled_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_SCROLLED_PREVIEW (obj)
define|#
directive|define
name|GIMP_SCROLLED_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SCROLLED_PREVIEW, GimpScrolledPreview))
end_define

begin_define
DECL|macro|GIMP_SCROLLED_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_SCROLLED_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SCROLLED_PREVIEW, GimpScrolledPreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_SCROLLED_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_SCROLLED_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SCROLLED_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_SCROLLED_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SCROLLED_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SCROLLED_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_SCROLLED_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SCROLLED_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SCROLLED_PREVIEW, GimpScrolledPreviewClass))
end_define

begin_typedef
DECL|typedef|GimpScrolledPreviewClass
typedef|typedef
name|struct
name|_GimpScrolledPreviewClass
name|GimpScrolledPreviewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpScrolledPreview
struct|struct
name|_GimpScrolledPreview
block|{
DECL|member|parent_instance
name|GimpPreview
name|parent_instance
decl_stmt|;
comment|/*< protected>*/
DECL|member|hscr
name|GtkWidget
modifier|*
name|hscr
decl_stmt|;
DECL|member|vscr
name|GtkWidget
modifier|*
name|vscr
decl_stmt|;
DECL|member|nav_icon
name|GtkWidget
modifier|*
name|nav_icon
decl_stmt|;
DECL|member|nav_popup
name|GtkWidget
modifier|*
name|nav_popup
decl_stmt|;
DECL|member|cursor_move
name|GdkCursor
modifier|*
name|cursor_move
decl_stmt|;
DECL|member|nav_gc
name|gpointer
name|nav_gc
decl_stmt|;
comment|/* unused */
comment|/*< private>*/
DECL|member|priv
name|gpointer
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpScrolledPreviewClass
struct|struct
name|_GimpScrolledPreviewClass
block|{
DECL|member|parent_class
name|GimpPreviewClass
name|parent_class
decl_stmt|;
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
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_scrolled_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_scrolled_preview_set_position
parameter_list|(
name|GimpScrolledPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scrolled_preview_set_policy
parameter_list|(
name|GimpScrolledPreview
modifier|*
name|preview
parameter_list|,
name|GtkPolicyType
name|hscrollbar_policy
parameter_list|,
name|GtkPolicyType
name|vscrollbar_policy
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  only for use from derived widgets  */
end_comment

begin_function_decl
name|void
name|gimp_scrolled_preview_freeze
parameter_list|(
name|GimpScrolledPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_scrolled_preview_thaw
parameter_list|(
name|GimpScrolledPreview
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
comment|/* __GIMP_SCROLLED_PREVIEW_H__ */
end_comment

end_unit

