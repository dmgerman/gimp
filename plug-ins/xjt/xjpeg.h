begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  xjpeg.h  *  * This Module contains:  *   jpeg load and save procedures for the use in XJT fileformat save  *   (based on libjpeg)  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 1.00.00; 1998/10/26  hof: 1.st (pre) release  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_XJPEG_H
end_ifndef

begin_define
DECL|macro|_XJPEG_H
define|#
directive|define
name|_XJPEG_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_typedef
DECL|enum|__anon2b412a520103
typedef|typedef
enum|enum
block|{
DECL|enumerator|JSVM_DRAWABLE
name|JSVM_DRAWABLE
block|,
comment|/* save the drawable as it is (ignore alpha channel) */
DECL|enumerator|JSVM_ALPHA
name|JSVM_ALPHA
comment|/* save the alpha channel */
DECL|typedef|t_save_mode
block|}
name|t_save_mode
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b412a520208
block|{
DECL|member|quality
name|gdouble
name|quality
decl_stmt|;
DECL|member|smoothing
name|gdouble
name|smoothing
decl_stmt|;
DECL|member|optimize
name|gint
name|optimize
decl_stmt|;
DECL|member|clr_transparent
name|gint
name|clr_transparent
decl_stmt|;
comment|/* clear pixels where alpha is full transparent */
DECL|typedef|t_JpegSaveVals
block|}
name|t_JpegSaveVals
typedef|;
end_typedef

begin_function_decl
name|gint
name|xjpg_save_drawable
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|save_mode
parameter_list|,
name|t_JpegSaveVals
modifier|*
name|jsvals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|xjpg_load_layer
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|int
name|image_type
parameter_list|,
name|char
modifier|*
name|layer_name
parameter_list|,
name|gdouble
name|layer_opacity
parameter_list|,
name|GimpLayerModeEffects
name|layer_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|xjpg_load_layer_alpha
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|layer_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|xjpg_load_channel
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
name|char
modifier|*
name|channel_name
parameter_list|,
name|gdouble
name|channel_opacity
parameter_list|,
name|guchar
name|red
parameter_list|,
name|guchar
name|green
parameter_list|,
name|guchar
name|blue
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

