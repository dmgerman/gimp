begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpTextLayer  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEXT_LAYER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEXT_LAYER_H__
define|#
directive|define
name|__GIMP_TEXT_LAYER_H__
end_define

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TEXT_LAYER
define|#
directive|define
name|GIMP_TYPE_TEXT_LAYER
value|(gimp_text_layer_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEXT_LAYER (obj)
define|#
directive|define
name|GIMP_TEXT_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEXT_LAYER, GimpTextLayer))
end_define

begin_define
DECL|macro|GIMP_TEXT_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_TEXT_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEXT_LAYER, GimpTextLayerClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_LAYER (obj)
define|#
directive|define
name|GIMP_IS_TEXT_LAYER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEXT_LAYER))
end_define

begin_define
DECL|macro|GIMP_IS_TEXT_LAYER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEXT_LAYER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEXT_LAYER))
end_define

begin_define
DECL|macro|GIMP_TEXT_LAYER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TEXT_LAYER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TEXT_LAYER, GimpTextLayerClass))
end_define

begin_typedef
DECL|typedef|GimpTextLayerClass
typedef|typedef
name|struct
name|_GimpTextLayerClass
name|GimpTextLayerClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTextLayer
struct|struct
name|_GimpTextLayer
block|{
DECL|member|layer
name|GimpLayer
name|layer
decl_stmt|;
DECL|member|text
name|GimpText
modifier|*
name|text
decl_stmt|;
DECL|member|text_parasite
specifier|const
name|gchar
modifier|*
name|text_parasite
decl_stmt|;
comment|/*  parasite name that this text was set from,                                  *  and that should be removed when the text                                  *  is changed.                                  */
DECL|member|auto_rename
name|gboolean
name|auto_rename
decl_stmt|;
DECL|member|modified
name|gboolean
name|modified
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTextLayerClass
struct|struct
name|_GimpTextLayerClass
block|{
DECL|member|parent_class
name|GimpLayerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_text_layer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpLayer
modifier|*
name|gimp_text_layer_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpText
modifier|*
name|gimp_text_layer_get_text
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layer_set_text
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|,
name|GimpText
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_text_layer_discard
parameter_list|(
name|GimpTextLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|void
name|gimp_text_layer_set
argument_list|(
name|GimpTextLayer
operator|*
name|layer
argument_list|,
specifier|const
name|gchar
operator|*
name|undo_desc
argument_list|,
specifier|const
name|gchar
operator|*
name|first_property_name
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_item_is_text_layer
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEXT_LAYER_H__ */
end_comment

end_unit

