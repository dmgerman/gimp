begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcompat.h  * Compatibility defines to ease migration from the GIMP-1.2 API  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPAT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPAT_H__
define|#
directive|define
name|__GIMP_COMPAT_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* This file contains aliases that are kept for historical reasons,  * because a wide code base depends on them. We suggest that you  * only use this header temporarily while porting a plug-in to the  * new API.  *  * These defines will be removed in the next development cycle.  */
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
DECL|macro|GimpRunModeType
define|#
directive|define
name|GimpRunModeType
value|GimpRunMode
DECL|macro|GimpExportReturnType
define|#
directive|define
name|GimpExportReturnType
value|GimpExportReturn
DECL|macro|gimp_use_xshm
define|#
directive|define
name|gimp_use_xshm
value|TRUE
DECL|macro|gimp_color_cube
define|#
directive|define
name|gimp_color_cube
value|((guchar *) { 6, 6, 4, 24 })
DECL|macro|gimp_convert_rgb
define|#
directive|define
name|gimp_convert_rgb
value|gimp_image_convert_rgb
DECL|macro|gimp_convert_grayscale
define|#
directive|define
name|gimp_convert_grayscale
value|gimp_image_convert_grayscale
DECL|macro|gimp_convert_indexed
define|#
directive|define
name|gimp_convert_indexed
value|gimp_image_convert_indexed
DECL|macro|gimp_crop
define|#
directive|define
name|gimp_crop
value|gimp_image_crop
DECL|macro|gimp_channel_get_image_id
define|#
directive|define
name|gimp_channel_get_image_id
value|gimp_drawable_get_image
DECL|macro|gimp_channel_delete
define|#
directive|define
name|gimp_channel_delete
value|gimp_drawable_delete
DECL|macro|gimp_channel_get_name
define|#
directive|define
name|gimp_channel_get_name
value|gimp_drawable_get_name
DECL|macro|gimp_channel_set_name
define|#
directive|define
name|gimp_channel_set_name
value|gimp_drawable_set_name
DECL|macro|gimp_channel_get_visible
define|#
directive|define
name|gimp_channel_get_visible
value|gimp_drawable_get_visible
DECL|macro|gimp_channel_set_visible
define|#
directive|define
name|gimp_channel_set_visible
value|gimp_drawable_set_visible
DECL|macro|gimp_channel_get_tattoo
define|#
directive|define
name|gimp_channel_get_tattoo
value|gimp_drawable_get_tattoo
DECL|macro|gimp_channel_set_tattoo
define|#
directive|define
name|gimp_channel_set_tattoo
value|gimp_drawable_set_tattoo
DECL|macro|gimp_layer_get_image_id
define|#
directive|define
name|gimp_layer_get_image_id
value|gimp_drawable_get_image
DECL|macro|gimp_layer_delete
define|#
directive|define
name|gimp_layer_delete
value|gimp_drawable_delete
DECL|macro|gimp_layer_get_name
define|#
directive|define
name|gimp_layer_get_name
value|gimp_drawable_get_name
DECL|macro|gimp_layer_set_name
define|#
directive|define
name|gimp_layer_set_name
value|gimp_drawable_set_name
DECL|macro|gimp_layer_get_visible
define|#
directive|define
name|gimp_layer_get_visible
value|gimp_drawable_get_visible
DECL|macro|gimp_layer_set_visible
define|#
directive|define
name|gimp_layer_set_visible
value|gimp_drawable_set_visible
DECL|macro|gimp_layer_get_linked
define|#
directive|define
name|gimp_layer_get_linked
value|gimp_drawable_get_linked
DECL|macro|gimp_layer_set_linked
define|#
directive|define
name|gimp_layer_set_linked
value|gimp_drawable_set_linked
DECL|macro|gimp_layer_get_tattoo
define|#
directive|define
name|gimp_layer_get_tattoo
value|gimp_drawable_get_tattoo
DECL|macro|gimp_layer_set_tattoo
define|#
directive|define
name|gimp_layer_set_tattoo
value|gimp_drawable_set_tattoo
DECL|macro|gimp_layer_mask
define|#
directive|define
name|gimp_layer_mask
value|gimp_layer_get_mask
DECL|macro|gimp_layer_get_mask_id
define|#
directive|define
name|gimp_layer_get_mask_id
value|gimp_layer_get_mask
DECL|macro|gimp_drawable_image
define|#
directive|define
name|gimp_drawable_image
value|gimp_drawable_get_image
DECL|macro|gimp_drawable_image_id
define|#
directive|define
name|gimp_drawable_image_id
value|gimp_drawable_get_image
DECL|macro|gimp_drawable_name
define|#
directive|define
name|gimp_drawable_name
value|gimp_drawable_get_name
DECL|macro|gimp_drawable_visible
define|#
directive|define
name|gimp_drawable_visible
value|gimp_drawable_get_visible
DECL|macro|gimp_gradients_get_active
define|#
directive|define
name|gimp_gradients_get_active
value|gimp_gradients_get_gradient
DECL|macro|gimp_gradients_set_active
define|#
directive|define
name|gimp_gradients_set_active
value|gimp_gradients_set_gradient
DECL|macro|gimp_help_init ()
define|#
directive|define
name|gimp_help_init
parameter_list|()
value|((void) 0)
DECL|macro|gimp_help_free ()
define|#
directive|define
name|gimp_help_free
parameter_list|()
value|((void) 0)
DECL|macro|gimp_interactive_selection_brush
define|#
directive|define
name|gimp_interactive_selection_brush
value|gimp_brush_select_new
DECL|macro|gimp_brush_select_widget
define|#
directive|define
name|gimp_brush_select_widget
value|gimp_brush_select_widget_new
DECL|macro|gimp_brush_select_widget_set_popup
define|#
directive|define
name|gimp_brush_select_widget_set_popup
value|gimp_brush_select_widget_set
DECL|macro|gimp_brush_select_widget_close_popup
define|#
directive|define
name|gimp_brush_select_widget_close_popup
value|gimp_brush_select_widget_close
DECL|macro|gimp_interactive_selection_font
define|#
directive|define
name|gimp_interactive_selection_font
value|gimp_font_select_new
DECL|macro|gimp_gradient_select_widget
define|#
directive|define
name|gimp_gradient_select_widget
value|gimp_gradient_select_widget_new
DECL|macro|gimp_gradient_select_widget_set_popup
define|#
directive|define
name|gimp_gradient_select_widget_set_popup
value|gimp_gradient_select_widget_set
DECL|macro|gimp_gradient_select_widget_close_popup
define|#
directive|define
name|gimp_gradient_select_widget_close_popup
value|gimp_gradient_select_widget_close
DECL|macro|gimp_interactive_selection_gradient
define|#
directive|define
name|gimp_interactive_selection_gradient
value|gimp_gradient_select_new
DECL|macro|gimp_font_select_widget
define|#
directive|define
name|gimp_font_select_widget
value|gimp_font_select_widget_new
DECL|macro|gimp_font_select_widget_set_popup
define|#
directive|define
name|gimp_font_select_widget_set_popup
value|gimp_font_select_widget_set
DECL|macro|gimp_font_select_widget_close_popup
define|#
directive|define
name|gimp_font_select_widget_close_popup
value|gimp_font_select_widget_close
DECL|macro|gimp_interactive_selection_pattern
define|#
directive|define
name|gimp_interactive_selection_pattern
value|gimp_pattern_select_new
DECL|macro|gimp_pattern_select_widget
define|#
directive|define
name|gimp_pattern_select_widget
value|gimp_pattern_select_widget_new
DECL|macro|gimp_pattern_select_widget_set_popup
define|#
directive|define
name|gimp_pattern_select_widget_set_popup
value|gimp_pattern_select_widget_set
DECL|macro|gimp_pattern_select_widget_close_popup
define|#
directive|define
name|gimp_pattern_select_widget_close_popup
value|gimp_pattern_select_widget_close
DECL|macro|INTENSITY (r,g,b)
define|#
directive|define
name|INTENSITY
parameter_list|(
name|r
parameter_list|,
name|g
parameter_list|,
name|b
parameter_list|)
value|GIMP_RGB_INTENSITY(r,g,b)
DECL|macro|INTENSITY_RED
define|#
directive|define
name|INTENSITY_RED
value|GIMP_RGB_INTENSITY_RED
DECL|macro|INTENSITY_GREEN
define|#
directive|define
name|INTENSITY_GREEN
value|GIMP_RGB_INTENSITY_GREEN
DECL|macro|INTENSITY_BLUE
define|#
directive|define
name|INTENSITY_BLUE
value|GIMP_RGB_INTENSITY_BLUE
DECL|macro|gimp_file_selection_
define|#
directive|define
name|gimp_file_selection_
value|gimp_file_entry_
DECL|macro|GimpFileSelection
define|#
directive|define
name|GimpFileSelection
value|GimpFileEntry
DECL|macro|GIMP_TYPE_FILE_SELECTION
define|#
directive|define
name|GIMP_TYPE_FILE_SELECTION
value|GIMP_TYPE_FILE_ENTRY
DECL|macro|GIMP_FILE_SELECTION
define|#
directive|define
name|GIMP_FILE_SELECTION
value|GIMP_FILE_ENTRY
DECL|macro|GIMP_IS_FILE_SELECTION
define|#
directive|define
name|GIMP_IS_FILE_SELECTION
value|GIMP_IS_FILE_ENTRY
name|enum
DECL|enum|__anon29e0af740103
type|{
DECL|enumerator|GIMP_WHITE_MASK
name|GIMP_WHITE_MASK
init|=
name|GIMP_ADD_WHITE_MASK
decl_stmt|,
DECL|enumerator|GIMP_BLACK_MASK
name|GIMP_BLACK_MASK
init|=
name|GIMP_ADD_BLACK_MASK
decl_stmt|,
DECL|enumerator|GIMP_ALPHA_MASK
name|GIMP_ALPHA_MASK
init|=
name|GIMP_ADD_ALPHA_MASK
decl_stmt|,
DECL|enumerator|GIMP_SELECTION_MASK
name|GIMP_SELECTION_MASK
init|=
name|GIMP_ADD_SELECTION_MASK
decl_stmt|,
DECL|enumerator|GIMP_COPY_MASK
name|GIMP_COPY_MASK
init|=
name|GIMP_ADD_COPY_MASK
decl_stmt|,
end_decl_stmt

begin_enum
unit|};
enum|enum
DECL|enum|__anon29e0af740203
block|{
DECL|enumerator|GIMP_ADD
name|GIMP_ADD
init|=
name|GIMP_CHANNEL_OP_ADD
block|,
DECL|enumerator|GIMP_SUB
name|GIMP_SUB
init|=
name|GIMP_CHANNEL_OP_SUBTRACT
block|,
DECL|enumerator|GIMP_REPLACE
name|GIMP_REPLACE
init|=
name|GIMP_CHANNEL_OP_REPLACE
block|,
DECL|enumerator|GIMP_INTERSECT
name|GIMP_INTERSECT
init|=
name|GIMP_CHANNEL_OP_INTERSECT
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e0af740303
block|{
DECL|enumerator|GIMP_FG_BG_RGB
name|GIMP_FG_BG_RGB
init|=
name|GIMP_FG_BG_RGB_MODE
block|,
DECL|enumerator|GIMP_FG_BG_HSV
name|GIMP_FG_BG_HSV
init|=
name|GIMP_FG_BG_HSV_MODE
block|,
DECL|enumerator|GIMP_FG_TRANS
name|GIMP_FG_TRANS
init|=
name|GIMP_FG_TRANSPARENT_MODE
block|,
DECL|enumerator|GIMP_CUSTOM
name|GIMP_CUSTOM
init|=
name|GIMP_CUSTOM_MODE
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e0af740403
block|{
DECL|enumerator|GIMP_FG_IMAGE_FILL
name|GIMP_FG_IMAGE_FILL
init|=
name|GIMP_FOREGROUND_FILL
block|,
DECL|enumerator|GIMP_BG_IMAGE_FILL
name|GIMP_BG_IMAGE_FILL
init|=
name|GIMP_BACKGROUND_FILL
block|,
DECL|enumerator|GIMP_WHITE_IMAGE_FILL
name|GIMP_WHITE_IMAGE_FILL
init|=
name|GIMP_WHITE_FILL
block|,
DECL|enumerator|GIMP_TRANS_IMAGE_FILL
name|GIMP_TRANS_IMAGE_FILL
init|=
name|GIMP_TRANSPARENT_FILL
block|,
DECL|enumerator|GIMP_NO_IMAGE_FILL
name|GIMP_NO_IMAGE_FILL
init|=
name|GIMP_NO_FILL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e0af740503
block|{
DECL|enumerator|GIMP_APPLY
name|GIMP_APPLY
init|=
name|GIMP_MASK_APPLY
block|,
DECL|enumerator|GIMP_DISCARD
name|GIMP_DISCARD
init|=
name|GIMP_MASK_DISCARD
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e0af740603
block|{
DECL|enumerator|GIMP_HARD
name|GIMP_HARD
init|=
name|GIMP_BRUSH_HARD
block|,
DECL|enumerator|GIMP_SOFT
name|GIMP_SOFT
init|=
name|GIMP_BRUSH_SOFT
block|, }
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e0af740703
block|{
DECL|enumerator|GIMP_CONTINUOUS
name|GIMP_CONTINUOUS
init|=
name|GIMP_PAINT_CONSTANT
block|,
DECL|enumerator|GIMP_INCREMENTAL
name|GIMP_INCREMENTAL
init|=
name|GIMP_PAINT_INCREMENTAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e0af740803
block|{
DECL|enumerator|GIMP_HORIZONTAL
name|GIMP_HORIZONTAL
init|=
name|GIMP_ORIENTATION_HORIZONTAL
block|,
DECL|enumerator|GIMP_VERTICAL
name|GIMP_VERTICAL
init|=
name|GIMP_ORIENTATION_VERTICAL
block|,
DECL|enumerator|GIMP_UNKNOWN
name|GIMP_UNKNOWN
init|=
name|GIMP_ORIENTATION_UNKNOWN
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon29e0af740903
block|{
DECL|enumerator|GIMP_LINEAR
name|GIMP_LINEAR
init|=
name|GIMP_GRADIENT_LINEAR
block|,
DECL|enumerator|GIMP_BILNEAR
name|GIMP_BILNEAR
init|=
name|GIMP_GRADIENT_BILINEAR
block|,
DECL|enumerator|GIMP_RADIAL
name|GIMP_RADIAL
init|=
name|GIMP_GRADIENT_RADIAL
block|,
DECL|enumerator|GIMP_SQUARE
name|GIMP_SQUARE
init|=
name|GIMP_GRADIENT_SQUARE
block|,
DECL|enumerator|GIMP_CONICAL_SYMMETRIC
name|GIMP_CONICAL_SYMMETRIC
init|=
name|GIMP_GRADIENT_CONICAL_SYMMETRIC
block|,
DECL|enumerator|GIMP_CONICAL_ASYMMETRIC
name|GIMP_CONICAL_ASYMMETRIC
init|=
name|GIMP_GRADIENT_CONICAL_ASYMMETRIC
block|,
DECL|enumerator|GIMP_SHAPEBURST_ANGULAR
name|GIMP_SHAPEBURST_ANGULAR
init|=
name|GIMP_GRADIENT_SHAPEBURST_ANGULAR
block|,
DECL|enumerator|GIMP_SHAPEBURST_SPHERICAL
name|GIMP_SHAPEBURST_SPHERICAL
init|=
name|GIMP_GRADIENT_SHAPEBURST_SPHERICAL
block|,
DECL|enumerator|GIMP_SHAPEBURST_DIMPLED
name|GIMP_SHAPEBURST_DIMPLED
init|=
name|GIMP_GRADIENT_SHAPEBURST_DIMPLED
block|,
DECL|enumerator|GIMP_SPIRAL_CLOCKWISE
name|GIMP_SPIRAL_CLOCKWISE
init|=
name|GIMP_GRADIENT_SPIRAL_CLOCKWISE
block|,
DECL|enumerator|GIMP_SPIRAL_ANTICLOCKWISE
name|GIMP_SPIRAL_ANTICLOCKWISE
init|=
name|GIMP_GRADIENT_SPIRAL_ANTICLOCKWISE
block|}
enum|;
end_enum

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* GIMP_DISABLE_DEPRECATED */
end_comment

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COMPAT_H__ */
end_comment

end_unit

