begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
DECL|macro|gimp_image_parasite_find
define|#
directive|define
name|gimp_image_parasite_find
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
comment|/* #define gimp_get_data 			gimp_procedural_db_get_data #define gimp_get_data_size		gimp_procedural_db_get_data_size   #define gimp_set_data(id, data, bytes) \ 	(gimp_procedural_db_set_data (id, bytes, data))  #define gimp_query_images		gimp_image_list */
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

