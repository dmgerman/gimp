begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SCRIPT_FU_TYPES_H__
end_ifndef

begin_define
DECL|macro|__SCRIPT_FU_TYPES_H__
define|#
directive|define
name|__SCRIPT_FU_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"script-fu-enums.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b8564770108
block|{
DECL|member|adj
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
DECL|member|value
name|gdouble
name|value
decl_stmt|;
DECL|member|lower
name|gdouble
name|lower
decl_stmt|;
DECL|member|upper
name|gdouble
name|upper
decl_stmt|;
DECL|member|step
name|gdouble
name|step
decl_stmt|;
DECL|member|page
name|gdouble
name|page
decl_stmt|;
DECL|member|digits
name|gint
name|digits
decl_stmt|;
DECL|member|type
name|SFAdjustmentType
name|type
decl_stmt|;
DECL|typedef|SFAdjustment
block|}
name|SFAdjustment
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b8564770208
block|{
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|typedef|SFFilename
block|}
name|SFFilename
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b8564770308
block|{
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
DECL|member|spacing
name|gint
name|spacing
decl_stmt|;
DECL|member|paint_mode
name|GimpLayerModeEffects
name|paint_mode
decl_stmt|;
DECL|typedef|SFBrush
block|}
name|SFBrush
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b8564770408
block|{
DECL|member|list
name|GSList
modifier|*
name|list
decl_stmt|;
DECL|member|history
name|gint
name|history
decl_stmt|;
DECL|typedef|SFOption
block|}
name|SFOption
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b8564770508
block|{
DECL|member|type_name
name|gchar
modifier|*
name|type_name
decl_stmt|;
DECL|member|history
name|gint
name|history
decl_stmt|;
DECL|typedef|SFEnum
block|}
name|SFEnum
typedef|;
end_typedef

begin_typedef
typedef|typedef
union|union
DECL|union|__anon2b856477060a
block|{
DECL|member|sfa_image
name|gint32
name|sfa_image
decl_stmt|;
DECL|member|sfa_drawable
name|gint32
name|sfa_drawable
decl_stmt|;
DECL|member|sfa_layer
name|gint32
name|sfa_layer
decl_stmt|;
DECL|member|sfa_channel
name|gint32
name|sfa_channel
decl_stmt|;
DECL|member|sfa_color
name|GimpRGB
name|sfa_color
decl_stmt|;
DECL|member|sfa_toggle
name|gint32
name|sfa_toggle
decl_stmt|;
DECL|member|sfa_value
name|gchar
modifier|*
name|sfa_value
decl_stmt|;
DECL|member|sfa_adjustment
name|SFAdjustment
name|sfa_adjustment
decl_stmt|;
DECL|member|sfa_file
name|SFFilename
name|sfa_file
decl_stmt|;
DECL|member|sfa_font
name|gchar
modifier|*
name|sfa_font
decl_stmt|;
DECL|member|sfa_gradient
name|gchar
modifier|*
name|sfa_gradient
decl_stmt|;
DECL|member|sfa_palette
name|gchar
modifier|*
name|sfa_palette
decl_stmt|;
DECL|member|sfa_pattern
name|gchar
modifier|*
name|sfa_pattern
decl_stmt|;
DECL|member|sfa_brush
name|SFBrush
name|sfa_brush
decl_stmt|;
DECL|member|sfa_option
name|SFOption
name|sfa_option
decl_stmt|;
DECL|member|sfa_enum
name|SFEnum
name|sfa_enum
decl_stmt|;
DECL|typedef|SFArgValue
block|}
name|SFArgValue
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b8564770708
block|{
DECL|member|script_name
name|gchar
modifier|*
name|script_name
decl_stmt|;
DECL|member|menu_path
name|gchar
modifier|*
name|menu_path
decl_stmt|;
DECL|member|help
name|gchar
modifier|*
name|help
decl_stmt|;
DECL|member|author
name|gchar
modifier|*
name|author
decl_stmt|;
DECL|member|copyright
name|gchar
modifier|*
name|copyright
decl_stmt|;
DECL|member|date
name|gchar
modifier|*
name|date
decl_stmt|;
DECL|member|img_types
name|gchar
modifier|*
name|img_types
decl_stmt|;
DECL|member|num_args
name|gint
name|num_args
decl_stmt|;
DECL|member|arg_types
name|SFArgType
modifier|*
name|arg_types
decl_stmt|;
DECL|member|arg_labels
name|gchar
modifier|*
modifier|*
name|arg_labels
decl_stmt|;
DECL|member|arg_defaults
name|SFArgValue
modifier|*
name|arg_defaults
decl_stmt|;
DECL|member|arg_values
name|SFArgValue
modifier|*
name|arg_values
decl_stmt|;
DECL|member|image_based
name|gboolean
name|image_based
decl_stmt|;
DECL|member|args
name|GimpParamDef
modifier|*
name|args
decl_stmt|;
comment|/*  used only temporary until installed  */
DECL|typedef|SFScript
block|}
name|SFScript
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SCRIPT_FU_TYPES__  */
end_comment

end_unit

