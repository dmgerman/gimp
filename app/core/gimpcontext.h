begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontext.h  * Copyright (C) 1999-2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTEXT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTEXT_H__
define|#
directive|define
name|__GIMP_CONTEXT_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bb870740103
block|{
DECL|enumerator|GIMP_CONTEXT_ARG_IMAGE
name|GIMP_CONTEXT_ARG_IMAGE
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_DISPLAY
name|GIMP_CONTEXT_ARG_DISPLAY
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_TOOL
name|GIMP_CONTEXT_ARG_TOOL
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_FOREGROUND
name|GIMP_CONTEXT_ARG_FOREGROUND
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_BACKGROUND
name|GIMP_CONTEXT_ARG_BACKGROUND
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_OPACITY
name|GIMP_CONTEXT_ARG_OPACITY
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_PAINT_MODE
name|GIMP_CONTEXT_ARG_PAINT_MODE
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_BRUSH
name|GIMP_CONTEXT_ARG_BRUSH
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_PATTERN
name|GIMP_CONTEXT_ARG_PATTERN
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_GRADIENT
name|GIMP_CONTEXT_ARG_GRADIENT
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_PALETTE
name|GIMP_CONTEXT_ARG_PALETTE
block|,
DECL|enumerator|GIMP_CONTEXT_ARG_BUFFER
name|GIMP_CONTEXT_ARG_BUFFER
block|,
DECL|enumerator|GIMP_CONTEXT_NUM_ARGS
name|GIMP_CONTEXT_NUM_ARGS
DECL|typedef|GimpContextArgType
block|}
name|GimpContextArgType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bb870740203
block|{
DECL|enumerator|GIMP_CONTEXT_IMAGE_MASK
name|GIMP_CONTEXT_IMAGE_MASK
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_CONTEXT_DISPLAY_MASK
name|GIMP_CONTEXT_DISPLAY_MASK
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_CONTEXT_TOOL_MASK
name|GIMP_CONTEXT_TOOL_MASK
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_CONTEXT_FOREGROUND_MASK
name|GIMP_CONTEXT_FOREGROUND_MASK
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_CONTEXT_BACKGROUND_MASK
name|GIMP_CONTEXT_BACKGROUND_MASK
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_CONTEXT_OPACITY_MASK
name|GIMP_CONTEXT_OPACITY_MASK
init|=
literal|1
operator|<<
literal|5
block|,
DECL|enumerator|GIMP_CONTEXT_PAINT_MODE_MASK
name|GIMP_CONTEXT_PAINT_MODE_MASK
init|=
literal|1
operator|<<
literal|6
block|,
DECL|enumerator|GIMP_CONTEXT_BRUSH_MASK
name|GIMP_CONTEXT_BRUSH_MASK
init|=
literal|1
operator|<<
literal|7
block|,
DECL|enumerator|GIMP_CONTEXT_PATTERN_MASK
name|GIMP_CONTEXT_PATTERN_MASK
init|=
literal|1
operator|<<
literal|8
block|,
DECL|enumerator|GIMP_CONTEXT_GRADIENT_MASK
name|GIMP_CONTEXT_GRADIENT_MASK
init|=
literal|1
operator|<<
literal|9
block|,
DECL|enumerator|GIMP_CONTEXT_PALETTE_MASK
name|GIMP_CONTEXT_PALETTE_MASK
init|=
literal|1
operator|<<
literal|10
block|,
DECL|enumerator|GIMP_CONTEXT_BUFFER_MASK
name|GIMP_CONTEXT_BUFFER_MASK
init|=
literal|1
operator|<<
literal|11
block|,
comment|/*  aliases  */
DECL|enumerator|GIMP_CONTEXT_PAINT_ARGS_MASK
name|GIMP_CONTEXT_PAINT_ARGS_MASK
init|=
operator|(
name|GIMP_CONTEXT_FOREGROUND_MASK
operator||
name|GIMP_CONTEXT_BACKGROUND_MASK
operator||
name|GIMP_CONTEXT_OPACITY_MASK
operator||
name|GIMP_CONTEXT_PAINT_MODE_MASK
operator||
name|GIMP_CONTEXT_BRUSH_MASK
operator||
name|GIMP_CONTEXT_PATTERN_MASK
operator||
name|GIMP_CONTEXT_GRADIENT_MASK
operator|)
block|,
DECL|enumerator|GIMP_CONTEXT_ALL_ARGS_MASK
name|GIMP_CONTEXT_ALL_ARGS_MASK
init|=
operator|(
name|GIMP_CONTEXT_IMAGE_MASK
operator||
name|GIMP_CONTEXT_DISPLAY_MASK
operator||
name|GIMP_CONTEXT_TOOL_MASK
operator||
name|GIMP_CONTEXT_PALETTE_MASK
operator||
name|GIMP_CONTEXT_BUFFER_MASK
operator||
name|GIMP_CONTEXT_PAINT_ARGS_MASK
operator|)
DECL|typedef|GimpContextArgMask
block|}
name|GimpContextArgMask
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONTEXT
define|#
directive|define
name|GIMP_TYPE_CONTEXT
value|(gimp_context_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTEXT (obj)
define|#
directive|define
name|GIMP_CONTEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTEXT, GimpContext))
end_define

begin_define
DECL|macro|GIMP_CONTEXT_CLASS (klass)
define|#
directive|define
name|GIMP_CONTEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST (klass, GIMP_TYPE_CONTEXT, GimpContextClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTEXT (obj)
define|#
directive|define
name|GIMP_IS_CONTEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTEXT))
end_define

begin_define
DECL|macro|GIMP_IS_CONTEXT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTEXT))
end_define

begin_typedef
DECL|typedef|GimpContextClass
typedef|typedef
name|struct
name|_GimpContextClass
name|GimpContextClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContext
struct|struct
name|_GimpContext
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|parent
name|GimpContext
modifier|*
name|parent
decl_stmt|;
DECL|member|defined_args
name|guint32
name|defined_args
decl_stmt|;
DECL|member|image
name|GimpImage
modifier|*
name|image
decl_stmt|;
DECL|member|display
name|GDisplay
modifier|*
name|display
decl_stmt|;
DECL|member|tool_info
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
DECL|member|tool_name
name|gchar
modifier|*
name|tool_name
decl_stmt|;
DECL|member|foreground
name|GimpRGB
name|foreground
decl_stmt|;
DECL|member|background
name|GimpRGB
name|background
decl_stmt|;
DECL|member|opacity
name|gdouble
name|opacity
decl_stmt|;
DECL|member|paint_mode
name|LayerModeEffects
name|paint_mode
decl_stmt|;
DECL|member|brush
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
DECL|member|brush_name
name|gchar
modifier|*
name|brush_name
decl_stmt|;
DECL|member|pattern
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
DECL|member|pattern_name
name|gchar
modifier|*
name|pattern_name
decl_stmt|;
DECL|member|gradient
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
DECL|member|gradient_name
name|gchar
modifier|*
name|gradient_name
decl_stmt|;
DECL|member|palette
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
DECL|member|palette_name
name|gchar
modifier|*
name|palette_name
decl_stmt|;
DECL|member|buffer
name|GimpBuffer
modifier|*
name|buffer
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContextClass
struct|struct
name|_GimpContextClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|image_changed
name|void
function_decl|(
modifier|*
name|image_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
DECL|member|display_changed
name|void
function_decl|(
modifier|*
name|display_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|tool_changed
name|void
function_decl|(
modifier|*
name|tool_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
DECL|member|foreground_changed
name|void
function_decl|(
modifier|*
name|foreground_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
DECL|member|background_changed
name|void
function_decl|(
modifier|*
name|background_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
DECL|member|opacity_changed
name|void
function_decl|(
modifier|*
name|opacity_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
DECL|member|paint_mode_changed
name|void
function_decl|(
modifier|*
name|paint_mode_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|LayerModeEffects
name|paint_mode
parameter_list|)
function_decl|;
DECL|member|brush_changed
name|void
function_decl|(
modifier|*
name|brush_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
DECL|member|pattern_changed
name|void
function_decl|(
modifier|*
name|pattern_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
function_decl|;
DECL|member|gradient_changed
name|void
function_decl|(
modifier|*
name|gradient_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
function_decl|;
DECL|member|palette_changed
name|void
function_decl|(
modifier|*
name|palette_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
DECL|member|buffer_changed
name|void
function_decl|(
modifier|*
name|buffer_changed
function_decl|)
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_context_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_context_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpContext
modifier|*
name|template
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_context_get_name
parameter_list|(
specifier|const
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_name
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_context_get_parent
parameter_list|(
specifier|const
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_parent
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContext
modifier|*
name|parent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_unset_parent
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  define / undefinine context arguments  *  *  the value of an undefined argument will be taken from the parent context.  */
end_comment

begin_function_decl
name|void
name|gimp_context_define_arg
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContextArgType
name|arg
parameter_list|,
name|gboolean
name|defined
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_arg_defined
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContextArgType
name|arg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_define_args
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContextArgMask
name|args_mask
parameter_list|,
name|gboolean
name|defined
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  copying context arguments  */
end_comment

begin_function_decl
name|void
name|gimp_context_copy_arg
parameter_list|(
name|GimpContext
modifier|*
name|src
parameter_list|,
name|GimpContext
modifier|*
name|dest
parameter_list|,
name|GimpContextArgType
name|arg
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_copy_args
parameter_list|(
name|GimpContext
modifier|*
name|src
parameter_list|,
name|GimpContext
modifier|*
name|dest
parameter_list|,
name|GimpContextArgMask
name|args_mask
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  manipulate by GType  */
end_comment

begin_function_decl
name|GimpContextArgType
name|gimp_context_type_to_arg
parameter_list|(
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_context_type_to_signal_name
parameter_list|(
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_context_get_by_type
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_by_type
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GType
name|type
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_changed_by_type
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  image  */
end_comment

begin_function_decl
name|GimpImage
modifier|*
name|gimp_context_get_image
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_image
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  display  */
end_comment

begin_function_decl
name|GDisplay
modifier|*
name|gimp_context_get_display
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_display
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  tool  */
end_comment

begin_function_decl
name|GimpToolInfo
modifier|*
name|gimp_context_get_tool
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_tool
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  foreground color  */
end_comment

begin_function_decl
name|void
name|gimp_context_get_foreground
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_foreground
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_foreground_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  background color  */
end_comment

begin_function_decl
name|void
name|gimp_context_get_background
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_background
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_background_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  color utility functions  */
end_comment

begin_function_decl
name|void
name|gimp_context_set_default_colors
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_swap_colors
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  opacity  */
end_comment

begin_function_decl
name|gdouble
name|gimp_context_get_opacity
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_opacity
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_opacity_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  paint mode  */
end_comment

begin_function_decl
name|LayerModeEffects
name|gimp_context_get_paint_mode
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_paint_mode
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|LayerModeEffects
name|paint_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_paint_mode_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  brush  */
end_comment

begin_function_decl
name|GimpBrush
modifier|*
name|gimp_context_get_brush
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_brush
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBrush
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_brush_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  pattern  */
end_comment

begin_function_decl
name|GimpPattern
modifier|*
name|gimp_context_get_pattern
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_pattern
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_pattern_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  gradient  */
end_comment

begin_function_decl
name|GimpGradient
modifier|*
name|gimp_context_get_gradient
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_gradient
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_gradient_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  palette  */
end_comment

begin_function_decl
name|GimpPalette
modifier|*
name|gimp_context_get_palette
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_palette
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_palette_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  buffer  */
end_comment

begin_function_decl
name|GimpBuffer
modifier|*
name|gimp_context_get_buffer
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_set_buffer
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpBuffer
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_context_buffer_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONTEXT_H__ */
end_comment

end_unit

