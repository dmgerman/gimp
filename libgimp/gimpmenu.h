begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpmenu.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MENU_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MENU_H__
define|#
directive|define
name|__GIMP_MENU_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpConstraintFunc
typedef|typedef
name|gint
function_decl|(
modifier|*
name|GimpConstraintFunc
function_decl|)
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpMenuCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpMenuCallback
function_decl|)
parameter_list|(
name|gint32
name|any_id
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpRunBrushCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRunBrushCallback
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|gint
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
end_typedef

begin_typedef
DECL|typedef|GimpRunFontCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRunFontCallback
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gboolean
name|dialog_closing
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpRunGradientCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRunGradientCallback
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
end_typedef

begin_typedef
DECL|typedef|GimpRunPatternCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpRunPatternCallback
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
end_typedef

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_image_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_layer_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_channel_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_drawable_menu_new
parameter_list|(
name|GimpConstraintFunc
name|constraint
parameter_list|,
name|GimpMenuCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gint32
name|active_drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_interactive_selection_brush
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
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
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpRunBrushCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_brush_select_widget
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
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
name|GimpLayerModeEffects
name|paint_mode
parameter_list|,
name|GimpRunBrushCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_select_widget_set_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_brush_select_widget_close_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_interactive_selection_font
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|,
name|GimpRunFontCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_font_select_widget
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|,
name|GimpRunFontCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_font_select_widget_close_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_font_select_widget_set_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|font_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_interactive_selection_gradient
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|gint
name|sample_size
parameter_list|,
name|GimpRunGradientCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_gradient_select_widget
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|,
name|GimpRunGradientCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_select_widget_close_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gradient_select_widget_set_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|gradient_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_interactive_selection_pattern
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
parameter_list|,
name|GimpRunPatternCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_pattern_select_widget
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
parameter_list|,
name|GimpRunPatternCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pattern_select_widget_close_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pattern_select_widget_set_popup
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
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
comment|/* __GIMP_MENU_H__ */
end_comment

end_unit

