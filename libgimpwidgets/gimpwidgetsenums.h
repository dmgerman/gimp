begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
comment|/**  * GimpAspectType:  * @GIMP_ASPECT_SQUARE:    it's a 1:1 square  * @GIMP_ASPECT_PORTRAIT:  it's higher than it's wide  * @GIMP_ASPECT_LANDSCAPE: it's wider than it's high  *  * Aspect ratios.  **/
DECL|macro|GIMP_TYPE_ASPECT_TYPE
define|#
directive|define
name|GIMP_TYPE_ASPECT_TYPE
value|(gimp_aspect_type_get_type ())
name|GType
name|gimp_aspect_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bb227c70103
block|{
DECL|enumerator|GIMP_ASPECT_SQUARE
name|GIMP_ASPECT_SQUARE
block|,
comment|/*< desc="Square">*/
DECL|enumerator|GIMP_ASPECT_PORTRAIT
name|GIMP_ASPECT_PORTRAIT
block|,
comment|/*< desc="Portrait">*/
DECL|enumerator|GIMP_ASPECT_LANDSCAPE
name|GIMP_ASPECT_LANDSCAPE
comment|/*< desc="Landscape">*/
DECL|typedef|GimpAspectType
block|}
name|GimpAspectType
typedef|;
end_typedef

begin_comment
comment|/**  * GimpChainPosition:  * @GIMP_CHAIN_TOP:    the chain is on top  * @GIMP_CHAIN_LEFT:   the chain is to the left  * @GIMP_CHAIN_BOTTOM: the chain is on bottom  * @GIMP_CHAIN_RIGHT:  the chain is to the right  *  * Possible chain positions for #GimpChainButton.  **/
end_comment

begin_define
DECL|macro|GIMP_TYPE_CHAIN_POSITION
define|#
directive|define
name|GIMP_TYPE_CHAIN_POSITION
value|(gimp_chain_position_get_type ())
end_define

begin_decl_stmt
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
DECL|enum|__anon2bb227c70203
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

begin_comment
comment|/**  * GimpColorAreaType:  * @GIMP_COLOR_AREA_FLAT:         don't display transparency  * @GIMP_COLOR_AREA_SMALL_CHECKS: display transparency using small checks  * @GIMP_COLOR_AREA_LARGE_CHECKS: display transparency using large checks  *  * The types of transparency display for #GimpColorArea.  **/
end_comment

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
DECL|enum|__anon2bb227c70303
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

begin_comment
comment|/**  * GimpColorSelectorChannel:  * @GIMP_COLOR_SELECTOR_HUE:        the hue channel  * @GIMP_COLOR_SELECTOR_SATURATION: the saturation channel  * @GIMP_COLOR_SELECTOR_VALUE:      the value channel  * @GIMP_COLOR_SELECTOR_RED:        the red channel  * @GIMP_COLOR_SELECTOR_GREEN:      the green channel  * @GIMP_COLOR_SELECTOR_BLUE:       the blue channel  * @GIMP_COLOR_SELECTOR_ALPHA:      the alpha channel  *  * An enum to specify the types of color channels edited in  * #GimpColorSelector widgets.  **/
end_comment

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
DECL|enum|__anon2bb227c70403
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

begin_comment
comment|/**  * GimpPageSelectorTarget:  * @GIMP_PAGE_SELECTOR_TARGET_LAYERS: import as layers of one image  * @GIMP_PAGE_SELECTOR_TARGET_IMAGES: import as separate images  *  * Import targets for #GimpPageSelector.  **/
end_comment

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
DECL|enum|__anon2bb227c70503
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

begin_comment
comment|/**  * GimpSizeEntryUpdatePolicy:  * @GIMP_SIZE_ENTRY_UPDATE_NONE:       the size entry's meaning is up to the user  * @GIMP_SIZE_ENTRY_UPDATE_SIZE:       the size entry displays values  * @GIMP_SIZE_ENTRY_UPDATE_RESOLUTION: the size entry displays resolutions  *  * Update policies for #GimpSizeEntry.  **/
end_comment

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
DECL|enum|__anon2bb227c70603
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

begin_comment
comment|/**  * GimpZoomType:  * @GIMP_ZOOM_IN:       zoom in  * @GIMP_ZOOM_OUT:      zoom out  * @GIMP_ZOOM_IN_MORE:  zoom in a lot  * @GIMP_ZOOM_OUT_MORE: zoom out a lot  * @GIMP_ZOOM_IN_MAX:   zoom in as far as possible  * @GIMP_ZOOM_OUT_MAX:  zoom out as far as possible  * @GIMP_ZOOM_TO:       zoom to a specific zoom factor  *  * the zoom types for #GimpZoomModel.  **/
end_comment

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
DECL|enum|__anon2bb227c70703
block|{
DECL|enumerator|GIMP_ZOOM_IN
name|GIMP_ZOOM_IN
block|,
comment|/*< desc="Zoom in">*/
DECL|enumerator|GIMP_ZOOM_OUT
name|GIMP_ZOOM_OUT
block|,
comment|/*< desc="Zoom out">*/
DECL|enumerator|GIMP_ZOOM_IN_MORE
name|GIMP_ZOOM_IN_MORE
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_ZOOM_OUT_MORE
name|GIMP_ZOOM_OUT_MORE
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_ZOOM_IN_MAX
name|GIMP_ZOOM_IN_MAX
block|,
comment|/*< skip>*/
DECL|enumerator|GIMP_ZOOM_OUT_MAX
name|GIMP_ZOOM_OUT_MAX
block|,
comment|/*< skip>*/
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

