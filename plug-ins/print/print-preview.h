begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PRINT_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PRINT_PREVIEW_H__
define|#
directive|define
name|__GIMP_PRINT_PREVIEW_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_PRINT_PREVIEW
define|#
directive|define
name|GIMP_TYPE_PRINT_PREVIEW
value|(gimp_print_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_PRINT_PREVIEW (obj)
define|#
directive|define
name|GIMP_PRINT_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PRINT_PREVIEW, GimpPrintPreview))
end_define

begin_define
DECL|macro|GIMP_PRINT_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_PRINT_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PRINT_PREVIEW, GimpPrintPreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_PRINT_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_PRINT_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PRINT_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_PRINT_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PRINT_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PRINT_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_PRINT_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PRINT_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PRINT_PREVIEW, GimpPrintPreviewClass))
end_define

begin_typedef
DECL|typedef|GimpPrintPreview
typedef|typedef
name|struct
name|_GimpPrintPreview
name|GimpPrintPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPrintPreviewClass
typedef|typedef
name|struct
name|_GimpPrintPreviewClass
name|GimpPrintPreviewClass
typedef|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_print_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_print_preview_new
parameter_list|(
name|GtkPageSetup
modifier|*
name|page
parameter_list|,
name|gint32
name|drawable_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_print_preview_set_image_dpi
parameter_list|(
name|GimpPrintPreview
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
name|gimp_print_preview_set_page_setup
parameter_list|(
name|GimpPrintPreview
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
name|gimp_print_preview_set_image_offsets
parameter_list|(
name|GimpPrintPreview
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
name|gimp_print_preview_set_image_offsets_max
parameter_list|(
name|GimpPrintPreview
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
name|gimp_print_preview_set_use_full_page
parameter_list|(
name|GimpPrintPreview
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
comment|/* __GIMP_PRINT_PREVIEW_H__ */
end_comment

end_unit

