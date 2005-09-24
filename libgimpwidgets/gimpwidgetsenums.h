begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WIDGETS_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIDGETS_ENUMS_H__
define|#
directive|define
name|__GIMP_WIDGETS_ENUMS_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
DECL|macro|GIMP_TYPE_CHAIN_POSITION
define|#
directive|define
name|GIMP_TYPE_CHAIN_POSITION
value|(gimp_chain_position_get_type ())
name|GType
name|gimp_chain_position_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ad3dc3f0103
block|{
DECL|enumerator|GIMP_CHAIN_TOP
name|GIMP_CHAIN_TOP
block|,
DECL|enumerator|GIMP_CHAIN_LEFT
name|GIMP_CHAIN_LEFT
block|,
DECL|enumerator|GIMP_CHAIN_BOTTOM
name|GIMP_CHAIN_BOTTOM
block|,
DECL|enumerator|GIMP_CHAIN_RIGHT
name|GIMP_CHAIN_RIGHT
DECL|typedef|GimpChainPosition
block|}
name|GimpChainPosition
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_COLOR_AREA_TYPE
define|#
directive|define
name|GIMP_TYPE_COLOR_AREA_TYPE
value|(gimp_color_area_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_area_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ad3dc3f0203
block|{
DECL|enumerator|GIMP_COLOR_AREA_FLAT
name|GIMP_COLOR_AREA_FLAT
init|=
literal|0
block|,
DECL|enumerator|GIMP_COLOR_AREA_SMALL_CHECKS
name|GIMP_COLOR_AREA_SMALL_CHECKS
block|,
DECL|enumerator|GIMP_COLOR_AREA_LARGE_CHECKS
name|GIMP_COLOR_AREA_LARGE_CHECKS
DECL|typedef|GimpColorAreaType
block|}
name|GimpColorAreaType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_COLOR_SELECTOR_CHANNEL
define|#
directive|define
name|GIMP_TYPE_COLOR_SELECTOR_CHANNEL
value|(gimp_color_selector_channel_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_color_selector_channel_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ad3dc3f0303
block|{
DECL|enumerator|GIMP_COLOR_SELECTOR_HUE
name|GIMP_COLOR_SELECTOR_HUE
block|,
comment|/*< desc="_H", help="Hue">*/
DECL|enumerator|GIMP_COLOR_SELECTOR_SATURATION
name|GIMP_COLOR_SELECTOR_SATURATION
block|,
comment|/*< desc="_S", help="Saturation">*/
DECL|enumerator|GIMP_COLOR_SELECTOR_VALUE
name|GIMP_COLOR_SELECTOR_VALUE
block|,
comment|/*< desc="_V", help="Value">*/
DECL|enumerator|GIMP_COLOR_SELECTOR_RED
name|GIMP_COLOR_SELECTOR_RED
block|,
comment|/*< desc="_R", help="Red">*/
DECL|enumerator|GIMP_COLOR_SELECTOR_GREEN
name|GIMP_COLOR_SELECTOR_GREEN
block|,
comment|/*< desc="_G", help="Green">*/
DECL|enumerator|GIMP_COLOR_SELECTOR_BLUE
name|GIMP_COLOR_SELECTOR_BLUE
block|,
comment|/*< desc="_B", help="Blue">*/
DECL|enumerator|GIMP_COLOR_SELECTOR_ALPHA
name|GIMP_COLOR_SELECTOR_ALPHA
comment|/*< desc="_A", help="Alpha">*/
DECL|typedef|GimpColorSelectorChannel
block|}
name|GimpColorSelectorChannel
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PAGE_SELECTOR_TARGET
define|#
directive|define
name|GIMP_TYPE_PAGE_SELECTOR_TARGET
value|(gimp_page_selector_target_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_page_selector_target_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ad3dc3f0403
block|{
DECL|enumerator|GIMP_PAGE_SELECTOR_TARGET_LAYERS
name|GIMP_PAGE_SELECTOR_TARGET_LAYERS
block|,
comment|/*< desc="Layers">*/
DECL|enumerator|GIMP_PAGE_SELECTOR_TARGET_IMAGES
name|GIMP_PAGE_SELECTOR_TARGET_IMAGES
comment|/*< desc="Images">*/
DECL|typedef|GimpPageSelectorTarget
block|}
name|GimpPageSelectorTarget
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_SIZE_ENTRY_UPDATE_POLICY
define|#
directive|define
name|GIMP_TYPE_SIZE_ENTRY_UPDATE_POLICY
value|(gimp_size_entry_update_policy_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_size_entry_update_policy_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ad3dc3f0503
block|{
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_NONE
name|GIMP_SIZE_ENTRY_UPDATE_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_SIZE
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
init|=
literal|1
block|,
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
name|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
init|=
literal|2
DECL|typedef|GimpSizeEntryUpdatePolicy
block|}
name|GimpSizeEntryUpdatePolicy
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ZOOM_WIDGET_TYPE
define|#
directive|define
name|GIMP_TYPE_ZOOM_WIDGET_TYPE
value|(gimp_zoom_model_widget_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_zoom_widget_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ad3dc3f0603
block|{
DECL|enumerator|GIMP_ZOOM_IN_BUTTON
name|GIMP_ZOOM_IN_BUTTON
block|,
DECL|enumerator|GIMP_ZOOM_OUT_BUTTON
name|GIMP_ZOOM_OUT_BUTTON
DECL|typedef|GimpZoomWidgetType
block|}
name|GimpZoomWidgetType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ZOOM_TYPE
define|#
directive|define
name|GIMP_TYPE_ZOOM_TYPE
value|(gimp_zoom_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_zoom_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ad3dc3f0703
block|{
DECL|enumerator|GIMP_ZOOM_IN
name|GIMP_ZOOM_IN
block|,
comment|/*< desc="Zoom in">*/
DECL|enumerator|GIMP_ZOOM_OUT
name|GIMP_ZOOM_OUT
block|,
comment|/*< desc="Zoom out">*/
DECL|enumerator|GIMP_ZOOM_TO
name|GIMP_ZOOM_TO
comment|/*< skip>*/
DECL|typedef|GimpZoomType
block|}
name|GimpZoomType
typedef|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WIDGETS_ENUMS_H__ */
end_comment

end_unit

