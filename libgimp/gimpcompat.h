begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPCOMPAT_H__
end_ifndef

begin_define
DECL|macro|__GIMPCOMPAT_H__
define|#
directive|define
name|__GIMPCOMPAT_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* some compatibility defines for older plug-ins */
ifndef|#
directive|ifndef
name|GIMP_DISABLE_COMPAT_H
DECL|macro|gimp_attach_parasite
define|#
directive|define
name|gimp_attach_parasite
value|gimp_parasite_attach
DECL|macro|gimp_detach_parasite
define|#
directive|define
name|gimp_detach_parasite
value|gimp_parasite_detach
DECL|macro|gimp_find_parasite
define|#
directive|define
name|gimp_find_parasite
value|gimp_parasite_find
DECL|macro|gimp_image_attach_parasite
define|#
directive|define
name|gimp_image_attach_parasite
value|gimp_image_parasite_attach
DECL|macro|gimp_image_detach_parasite
define|#
directive|define
name|gimp_image_detach_parasite
value|gimp_image_parasite_detach
DECL|macro|gimp_image_find_parasite
define|#
directive|define
name|gimp_image_find_parasite
value|gimp_image_parasite_find
DECL|macro|gimp_drawable_attach_parasite
define|#
directive|define
name|gimp_drawable_attach_parasite
value|gimp_drawable_parasite_attach
DECL|macro|gimp_drawable_detach_parasite
define|#
directive|define
name|gimp_drawable_detach_parasite
value|gimp_drawable_parasite_detach
DECL|macro|gimp_drawable_find_parasite
define|#
directive|define
name|gimp_drawable_find_parasite
value|gimp_drawable_parasite_find
DECL|macro|gimp_drawable_channel
define|#
directive|define
name|gimp_drawable_channel
value|gimp_drawable_is_channel
DECL|macro|gimp_drawable_gray
define|#
directive|define
name|gimp_drawable_gray
value|gimp_drawable_is_gray
DECL|macro|gimp_drawable_color
define|#
directive|define
name|gimp_drawable_color
value|gimp_drawable_is_rgb
DECL|macro|gimp_drawable_indexed
define|#
directive|define
name|gimp_drawable_indexed
value|gimp_drawable_is_indexed
DECL|macro|gimp_drawable_layer
define|#
directive|define
name|gimp_drawable_layer
value|gimp_drawable_is_layer
DECL|macro|gimp_drawable_layer_mask
define|#
directive|define
name|gimp_drawable_layer_mask
value|gimp_drawable_is_layer_mask
DECL|macro|gimp_image_disable_undo
define|#
directive|define
name|gimp_image_disable_undo
value|gimp_image_undo_disable
DECL|macro|gimp_image_enable_undo
define|#
directive|define
name|gimp_image_enable_undo
value|gimp_image_undo_enable
DECL|macro|gimp_image_freeze_undo
define|#
directive|define
name|gimp_image_freeze_undo
value|gimp_image_undo_freeze
DECL|macro|gimp_image_thaw_undo
define|#
directive|define
name|gimp_image_thaw_undo
value|gimp_image_undo_thaw
DECL|macro|gimp_channel_width
define|#
directive|define
name|gimp_channel_width
value|gimp_drawable_width
DECL|macro|gimp_channel_height
define|#
directive|define
name|gimp_channel_height
value|gimp_drawable_height
DECL|macro|gimp_channel_get_image_ID
define|#
directive|define
name|gimp_channel_get_image_ID
value|gimp_drawable_image
DECL|macro|gimp_channel_get_layer_ID
define|#
directive|define
name|gimp_channel_get_layer_ID
value|-1
DECL|macro|gimp_layer_width
define|#
directive|define
name|gimp_layer_width
value|gimp_drawable_width
DECL|macro|gimp_layer_height
define|#
directive|define
name|gimp_layer_height
value|gimp_drawable_height
DECL|macro|gimp_layer_bpp
define|#
directive|define
name|gimp_layer_bpp
value|gimp_drawable_bpp
DECL|macro|gimp_layer_type
define|#
directive|define
name|gimp_layer_type
value|gimp_drawable_type
DECL|macro|gimp_gradient_get_gradient_data
define|#
directive|define
name|gimp_gradient_get_gradient_data
value|gimp_gradients_get_gradient_data
DECL|macro|gimp_plugin_help_func
define|#
directive|define
name|gimp_plugin_help_func
value|gimp_standard_help_func
DECL|macro|gimp_query_database
define|#
directive|define
name|gimp_query_database
value|gimp_procedural_db_query
DECL|macro|gimp_query_images
define|#
directive|define
name|gimp_query_images
value|gimp_image_list
DECL|macro|Parasite
define|#
directive|define
name|Parasite
value|GimpParasite
DECL|macro|PARASITE_PERSISTENT
define|#
directive|define
name|PARASITE_PERSISTENT
value|GIMP_PARASITE_PERSISTENT
DECL|macro|PARASITE_UNDOABLE
define|#
directive|define
name|PARASITE_UNDOABLE
value|GIMP_PARASITE_UNDOABLE
DECL|macro|PARASITE_ATTACH_PARENT
define|#
directive|define
name|PARASITE_ATTACH_PARENT
value|GIMP_PARASITE_ATTACH_PARENT
DECL|macro|PARASITE_PARENT_PERSISTENT
define|#
directive|define
name|PARASITE_PARENT_PERSISTENT
value|GIMP_PARASITE_PARENT_PERSISTENT
DECL|macro|PARASITE_PARENT_UNDOABLE
define|#
directive|define
name|PARASITE_PARENT_UNDOABLE
value|GIMP_PARASITE_PARENT_UNDOABLE
DECL|macro|PARASITE_ATTACH_GRANDPARENT
define|#
directive|define
name|PARASITE_ATTACH_GRANDPARENT
value|GIMP_PARASITE_ATTACH_GRANDPARENT
DECL|macro|PARASITE_GRANDPARENT_PERSISTENT
define|#
directive|define
name|PARASITE_GRANDPARENT_PERSISTENT
value|GIMP_PARASITE_GRANDPARENT_PERSISTENT
DECL|macro|PARASITE_GRANDPARENT_UNDOABLE
define|#
directive|define
name|PARASITE_GRANDPARENT_UNDOABLE
value|GIMP_PARASITE_GRANDPARENT_UNDOABLE
DECL|macro|parasite_new
define|#
directive|define
name|parasite_new
value|gimp_parasite_new
DECL|macro|parasite_free
define|#
directive|define
name|parasite_free
value|gimp_parasite_free
DECL|macro|parasite_copy
define|#
directive|define
name|parasite_copy
value|gimp_parasite_copy
DECL|macro|parasite_compare
define|#
directive|define
name|parasite_compare
value|gimp_parasite_compare
DECL|macro|parasite_is_type
define|#
directive|define
name|parasite_is_type
value|gimp_parasite_is_type
DECL|macro|parasite_is_persistent
define|#
directive|define
name|parasite_is_persistent
value|gimp_parasite_is_persistent
DECL|macro|parasite_is_undoable
define|#
directive|define
name|parasite_is_undoable
value|gimp_parasite_is_undoable
DECL|macro|parasite_has_flag
define|#
directive|define
name|parasite_has_flag
value|gimp_parasite_has_flag
DECL|macro|parasite_flags
define|#
directive|define
name|parasite_flags
value|gimp_parasite_flags
DECL|macro|parasite_name
define|#
directive|define
name|parasite_name
value|gimp_parasite_name
DECL|macro|parasite_data
define|#
directive|define
name|parasite_data
value|gimp_parasite_data
DECL|macro|parasite_data_size
define|#
directive|define
name|parasite_data_size
value|gimp_parasite_data_size
DECL|macro|PIXPIPE_MAXDIM
define|#
directive|define
name|PIXPIPE_MAXDIM
value|GIMP_PIXPIPE_MAXDIM
DECL|macro|PixPipeParams
define|#
directive|define
name|PixPipeParams
value|GimpPixPipeParams
DECL|macro|pixpipeparams_init
define|#
directive|define
name|pixpipeparams_init
value|gimp_pixpipe_params_init
DECL|macro|pixpipeparams_parse
define|#
directive|define
name|pixpipeparams_parse
value|gimp_pixpipe_params_parse
DECL|macro|pixpipeparams_build
define|#
directive|define
name|pixpipeparams_build
value|gimp_pixpipe_params_build
DECL|macro|GPlugInInfo
define|#
directive|define
name|GPlugInInfo
value|GimpPlugInInfo
DECL|macro|GTile
define|#
directive|define
name|GTile
value|GimpTile
DECL|macro|GDrawable
define|#
directive|define
name|GDrawable
value|GimpDrawable
DECL|macro|GPixelRgn
define|#
directive|define
name|GPixelRgn
value|GimpPixelRgn
DECL|macro|GParamColor
define|#
directive|define
name|GParamColor
value|GimpParamColor
DECL|macro|GParamRegion
define|#
directive|define
name|GParamRegion
value|GimpParamRegion
DECL|macro|GParamData
define|#
directive|define
name|GParamData
value|GimpParamData
DECL|macro|GParamDef
define|#
directive|define
name|GParamDef
value|GimpParamDef
DECL|macro|GParam
define|#
directive|define
name|GParam
value|GimpParam
endif|#
directive|endif
comment|/* GIMP_DISABLE_COMPAT_H */
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPCOMPAT_H__ */
end_comment

end_unit

