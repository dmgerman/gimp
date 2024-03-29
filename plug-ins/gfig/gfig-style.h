begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for GIMP.  *  * Generates images containing vector type drawings.  *  * Copyright (C) 1997 Andy Thomas  alt@picnic.demon.co.uk  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GFIG_STYLE_H__
end_ifndef

begin_define
DECL|macro|__GFIG_STYLE_H__
define|#
directive|define
name|__GFIG_STYLE_H__
end_define

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_struct
DECL|struct|_Style
struct|struct
name|_Style
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|brush_name
name|gchar
modifier|*
name|brush_name
decl_stmt|;
DECL|member|brush_width
name|gint
name|brush_width
decl_stmt|;
DECL|member|brush_height
name|gint
name|brush_height
decl_stmt|;
DECL|member|brush_spacing
name|gint
name|brush_spacing
decl_stmt|;
DECL|member|brush_type
name|BrushType
name|brush_type
decl_stmt|;
DECL|member|brushfade
name|gdouble
name|brushfade
decl_stmt|;
DECL|member|brushgradient
name|gdouble
name|brushgradient
decl_stmt|;
DECL|member|airbrushpressure
name|gdouble
name|airbrushpressure
decl_stmt|;
DECL|member|fill_type
name|FillType
name|fill_type
decl_stmt|;
DECL|member|fill_opacity
name|gdouble
name|fill_opacity
decl_stmt|;
DECL|member|pattern
name|gchar
modifier|*
name|pattern
decl_stmt|;
DECL|member|gradient
name|gchar
modifier|*
name|gradient
decl_stmt|;
DECL|member|paint_type
name|PaintType
name|paint_type
decl_stmt|;
DECL|member|foreground
name|GimpRGB
name|foreground
decl_stmt|;
DECL|member|background
name|GimpRGB
name|background
decl_stmt|;
DECL|member|reverselines
name|gboolean
name|reverselines
decl_stmt|;
DECL|member|ref_count
name|gint
name|ref_count
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|gboolean
name|gfig_load_style
parameter_list|(
name|Style
modifier|*
name|style
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gfig_skip_style
parameter_list|(
name|Style
modifier|*
name|style
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gfig_load_styles
parameter_list|(
name|GFigObj
modifier|*
name|gfig
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_save_style
parameter_list|(
name|Style
modifier|*
name|style
parameter_list|,
name|GString
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_style_save_as_attributes
parameter_list|(
name|Style
modifier|*
name|style
parameter_list|,
name|GString
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_save_styles
parameter_list|(
name|GString
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_foreground_callback
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_background_callback
parameter_list|(
name|GimpColorButton
modifier|*
name|button
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_paint_type_callback
parameter_list|(
name|GtkToggleButton
modifier|*
name|toggle
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_brush_changed_callback
parameter_list|(
name|GimpBrushSelectButton
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|brush_name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpLayerMode
name|paint_mode
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask_data
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_pattern_changed_callback
parameter_list|(
name|GimpPatternSelectButton
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
specifier|const
name|guchar
modifier|*
name|mask_data
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_gradient_changed_callback
parameter_list|(
name|GimpGradientSelectButton
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|gint
name|width
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|grad_data
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_rgba_copy
parameter_list|(
name|GimpRGB
modifier|*
name|color1
parameter_list|,
name|GimpRGB
modifier|*
name|color2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_style_copy
parameter_list|(
name|Style
modifier|*
name|style1
parameter_list|,
name|Style
modifier|*
name|style0
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_style_apply
parameter_list|(
name|Style
modifier|*
name|style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_read_gimp_style
parameter_list|(
name|Style
modifier|*
name|style
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_style_set_context_from_style
parameter_list|(
name|Style
modifier|*
name|style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gfig_style_set_style_from_context
parameter_list|(
name|Style
modifier|*
name|style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mygimp_brush_info
parameter_list|(
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
name|Style
modifier|*
name|gfig_context_get_current_style
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
comment|/* __GFIG_STYLE_H__ */
end_comment

end_unit

