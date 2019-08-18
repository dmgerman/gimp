begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PRINT_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__PRINT_PREVIEW_H__
define|#
directive|define
name|__PRINT_PREVIEW_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|PRINT_TYPE_PREVIEW
define|#
directive|define
name|PRINT_TYPE_PREVIEW
value|(print_preview_get_type ())
end_define

begin_define
DECL|macro|PRINT_PREVIEW (obj)
define|#
directive|define
name|PRINT_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), PRINT_TYPE_PREVIEW, PrintPreview))
end_define

begin_define
DECL|macro|PRINT_PREVIEW_CLASS (klass)
define|#
directive|define
name|PRINT_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), PRINT_TYPE_PREVIEW, PrintPreviewClass))
end_define

begin_define
DECL|macro|PRINT_IS_PREVIEW (obj)
define|#
directive|define
name|PRINT_IS_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), PRINT_TYPE_PREVIEW))
end_define

begin_define
DECL|macro|PRINT_IS_PREVIEW_CLASS (klass)
define|#
directive|define
name|PRINT_IS_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), PRINT_TYPE_PREVIEW))
end_define

begin_define
DECL|macro|PRINT_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|PRINT_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), PRINT_TYPE_PREVIEW, PrintPreviewClass))
end_define

begin_typedef
DECL|typedef|PrintPreview
typedef|typedef
name|struct
name|_PrintPreview
name|PrintPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|PrintPreviewClass
typedef|typedef
name|struct
name|_PrintPreviewClass
name|PrintPreviewClass
typedef|;
end_typedef

begin_decl_stmt
name|GType
name|print_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|print_preview_new
parameter_list|(
name|GtkPageSetup
modifier|*
name|page
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|print_preview_set_image_dpi
parameter_list|(
name|PrintPreview
modifier|*
name|preview
parameter_list|,
name|gdouble
name|xres
parameter_list|,
name|gdouble
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|print_preview_set_page_setup
parameter_list|(
name|PrintPreview
modifier|*
name|preview
parameter_list|,
name|GtkPageSetup
modifier|*
name|page
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|print_preview_set_image_offsets
parameter_list|(
name|PrintPreview
modifier|*
name|preview
parameter_list|,
name|gdouble
name|offset_x
parameter_list|,
name|gdouble
name|offset_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|print_preview_set_image_offsets_max
parameter_list|(
name|PrintPreview
modifier|*
name|preview
parameter_list|,
name|gdouble
name|offset_x_max
parameter_list|,
name|gdouble
name|offset_y_max
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|print_preview_set_use_full_page
parameter_list|(
name|PrintPreview
modifier|*
name|preview
parameter_list|,
name|gboolean
name|full_page
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
comment|/* __PRINT_PREVIEW_H__ */
end_comment

end_unit

