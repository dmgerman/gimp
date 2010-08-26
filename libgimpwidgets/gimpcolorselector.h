begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolorselector.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on:  * Colour selector module  * Copyright (C) 1999 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_SELECTOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_SELECTOR_H__
define|#
directive|define
name|__GIMP_COLOR_SELECTOR_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look at the html documentation */
end_comment

begin_comment
comment|/**  * GIMP_COLOR_SELECTOR_SIZE:  *  * The suggested size for a color area in a #GimpColorSelector  * implementation.  **/
end_comment

begin_define
DECL|macro|GIMP_COLOR_SELECTOR_SIZE
define|#
directive|define
name|GIMP_COLOR_SELECTOR_SIZE
value|150
end_define

begin_comment
comment|/**  * GIMP_COLOR_SELECTOR_BAR_SIZE:  *  * The suggested width for a color bar in a #GimpColorSelector  * implementation.  **/
end_comment

begin_define
DECL|macro|GIMP_COLOR_SELECTOR_BAR_SIZE
define|#
directive|define
name|GIMP_COLOR_SELECTOR_BAR_SIZE
value|15
end_define

begin_define
DECL|macro|GIMP_TYPE_COLOR_SELECTOR
define|#
directive|define
name|GIMP_TYPE_COLOR_SELECTOR
value|(gimp_color_selector_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTOR (obj)
define|#
directive|define
name|GIMP_COLOR_SELECTOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_SELECTOR, GimpColorSelector))
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTOR_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_SELECTOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_SELECTOR, GimpColorSelectorClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SELECTOR (obj)
define|#
directive|define
name|GIMP_IS_COLOR_SELECTOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_SELECTOR))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_SELECTOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_SELECTOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_SELECTOR))
end_define

begin_define
DECL|macro|GIMP_COLOR_SELECTOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_SELECTOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_SELECTOR, GimpColorSelectorClass))
end_define

begin_typedef
DECL|typedef|GimpColorSelectorClass
typedef|typedef
name|struct
name|_GimpColorSelectorClass
name|GimpColorSelectorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorSelector
struct|struct
name|_GimpColorSelector
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|toggles_visible
name|gboolean
name|toggles_visible
decl_stmt|;
DECL|member|toggles_sensitive
name|gboolean
name|toggles_sensitive
decl_stmt|;
DECL|member|show_alpha
name|gboolean
name|show_alpha
decl_stmt|;
DECL|member|rgb
name|GimpRGB
name|rgb
decl_stmt|;
DECL|member|hsv
name|GimpHSV
name|hsv
decl_stmt|;
DECL|member|channel
name|GimpColorSelectorChannel
name|channel
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorSelectorClass
struct|struct
name|_GimpColorSelectorClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|member|stock_id
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
comment|/*  virtual functions  */
DECL|member|set_toggles_visible
name|void
function_decl|(
modifier|*
name|set_toggles_visible
function_decl|)
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
DECL|member|set_toggles_sensitive
name|void
function_decl|(
modifier|*
name|set_toggles_sensitive
function_decl|)
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
DECL|member|set_show_alpha
name|void
function_decl|(
modifier|*
name|set_show_alpha
function_decl|)
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
function_decl|;
DECL|member|set_color
name|void
function_decl|(
modifier|*
name|set_color
function_decl|)
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
DECL|member|set_channel
name|void
function_decl|(
modifier|*
name|set_channel
function_decl|)
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
function_decl|;
comment|/*  signals  */
DECL|member|color_changed
name|void
function_decl|(
modifier|*
name|color_changed
function_decl|)
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
DECL|member|channel_changed
name|void
function_decl|(
modifier|*
name|channel_changed
function_decl|)
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
function_decl|;
comment|/*  another virtual function  */
DECL|member|set_config
name|void
function_decl|(
modifier|*
name|set_config
function_decl|)
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
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
name|gimp_color_selector_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_selector_new
parameter_list|(
name|GType
name|selector_type
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selector_set_toggles_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selector_set_toggles_sensitive
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selector_set_show_alpha
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selector_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selector_set_channel
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selector_color_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selector_channel_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_selector_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
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
comment|/* __GIMP_COLOR_SELECTOR_H__ */
end_comment

end_unit

