begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gimp Image Compositing  * Copyright (C) 2003  Helvetix Victorinox, a pseudonym,<helvetix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPOSITE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPOSITE_H__
define|#
directive|define
name|__GIMP_COMPOSITE_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c0bc5280103
block|{
DECL|enumerator|GIMP_PIXELFORMAT_V8
name|GIMP_PIXELFORMAT_V8
block|,
DECL|enumerator|GIMP_PIXELFORMAT_VA8
name|GIMP_PIXELFORMAT_VA8
block|,
DECL|enumerator|GIMP_PIXELFORMAT_RGB8
name|GIMP_PIXELFORMAT_RGB8
block|,
DECL|enumerator|GIMP_PIXELFORMAT_RGBA8
name|GIMP_PIXELFORMAT_RGBA8
block|,
if|#
directive|if
name|GIMP_COMPOSITE_16BIT
DECL|enumerator|GIMP_PIXELFORMAT_V16
name|GIMP_PIXELFORMAT_V16
block|,
DECL|enumerator|GIMP_PIXELFORMAT_VA16
name|GIMP_PIXELFORMAT_VA16
block|,
DECL|enumerator|GIMP_PIXELFORMAT_RGB16
name|GIMP_PIXELFORMAT_RGB16
block|,
DECL|enumerator|GIMP_PIXELFORMAT_RGBA16
name|GIMP_PIXELFORMAT_RGBA16
block|,
endif|#
directive|endif
if|#
directive|if
name|GIMP_COMPOSITE_32BIT
DECL|enumerator|GIMP_PIXELFORMAT_V32
name|GIMP_PIXELFORMAT_V32
block|,
DECL|enumerator|GIMP_PIXELFORMAT_VA32
name|GIMP_PIXELFORMAT_VA32
block|,
DECL|enumerator|GIMP_PIXELFORMAT_RGB32
name|GIMP_PIXELFORMAT_RGB32
block|,
DECL|enumerator|GIMP_PIXELFORMAT_RGBA32
name|GIMP_PIXELFORMAT_RGBA32
block|,
endif|#
directive|endif
DECL|enumerator|GIMP_PIXELFORMAT_ANY
name|GIMP_PIXELFORMAT_ANY
block|,
DECL|enumerator|GIMP_PIXELFORMAT_N
name|GIMP_PIXELFORMAT_N
DECL|typedef|GimpPixelFormat
block|}
name|GimpPixelFormat
typedef|;
end_typedef

begin_comment
comment|/*  * The following typedefs are temporary and only used in regression testing. 	*/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280208
block|{
DECL|member|v
name|guint8
name|v
decl_stmt|;
DECL|typedef|gimp_v8_t
block|}
name|gimp_v8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280308
block|{
DECL|member|v
name|guint8
name|v
decl_stmt|;
DECL|member|a
name|guint8
name|a
decl_stmt|;
DECL|typedef|gimp_va8_t
block|}
name|gimp_va8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280408
block|{
DECL|member|r
name|guint8
name|r
decl_stmt|;
DECL|member|g
name|guint8
name|g
decl_stmt|;
DECL|member|b
name|guint8
name|b
decl_stmt|;
DECL|typedef|gimp_rgb8_t
block|}
name|gimp_rgb8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280508
block|{
DECL|member|r
name|guint8
name|r
decl_stmt|;
DECL|member|g
name|guint8
name|g
decl_stmt|;
DECL|member|b
name|guint8
name|b
decl_stmt|;
DECL|member|a
name|guint8
name|a
decl_stmt|;
DECL|typedef|gimp_rgba8_t
block|}
name|gimp_rgba8_t
typedef|;
end_typedef

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_COMPOSIE_16BIT
end_ifdef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280608
block|{
DECL|member|v
name|guint16
name|v
decl_stmt|;
DECL|typedef|gimp_v16_t
block|}
name|gimp_v16_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280708
block|{
DECL|member|v
name|guint16
name|v
decl_stmt|;
DECL|member|a
name|guint16
name|a
decl_stmt|;
DECL|typedef|gimp_va16_t
block|}
name|gimp_va16_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280808
block|{
DECL|member|r
name|guint16
name|r
decl_stmt|;
DECL|member|g
name|guint16
name|g
decl_stmt|;
DECL|member|b
name|guint16
name|b
decl_stmt|;
DECL|typedef|gimp_rgb16_t
block|}
name|gimp_rgb16_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280908
block|{
DECL|member|r
name|guint16
name|r
decl_stmt|;
DECL|member|g
name|guint16
name|g
decl_stmt|;
DECL|member|b
name|guint16
name|b
decl_stmt|;
DECL|member|a
name|guint16
name|a
decl_stmt|;
DECL|typedef|gimp_rgba16_t
block|}
name|gimp_rgba16_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_COMPOSIE_32BIT
end_ifdef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280a08
block|{
DECL|member|v
name|guint32
name|v
decl_stmt|;
DECL|typedef|gimp_v32_t
block|}
name|gimp_v32_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280b08
block|{
DECL|member|v
name|guint32
name|v
decl_stmt|;
DECL|member|a
name|guint32
name|a
decl_stmt|;
DECL|typedef|gimp_va32_t
block|}
name|gimp_va32_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280c08
block|{
DECL|member|r
name|guint32
name|r
decl_stmt|;
DECL|member|g
name|guint32
name|g
decl_stmt|;
DECL|member|b
name|guint32
name|b
decl_stmt|;
DECL|typedef|gimp_rgb32_t
block|}
name|gimp_rgb32_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280d08
block|{
DECL|member|r
name|guint32
name|r
decl_stmt|;
DECL|member|g
name|guint32
name|g
decl_stmt|;
DECL|member|b
name|guint32
name|b
decl_stmt|;
DECL|member|a
name|guint32
name|a
decl_stmt|;
DECL|typedef|gimp_rgba32_t
block|}
name|gimp_rgba32_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* bytes per-pixel for each of the pixel formats */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|guchar
name|gimp_composite_pixel_bpp
index|[]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* does pixel format have alpha? */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|guchar
name|gimp_composite_pixel_alphap
index|[]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* converter between alpha and non-alpha pixel formats */
end_comment

begin_decl_stmt
specifier|extern
specifier|const
name|GimpPixelFormat
name|gimp_composite_pixel_alpha
index|[]
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|GIMP_COMPOSITE_ALPHA_OPAQUE
define|#
directive|define
name|GIMP_COMPOSITE_ALPHA_OPAQUE
value|(-1)
end_define

begin_define
DECL|macro|GIMP_COMPOSITE_ALPHA_TRANSPARENT
define|#
directive|define
name|GIMP_COMPOSITE_ALPHA_TRANSPARENT
value|(0)
end_define

begin_comment
comment|/*  * This is the enumeration of all the supported compositing  * operations.  Many of them are taken from the GimpLayerModeEffect  * enumeration, but there are (possibly more) implemented.  Here is  * where they are all enumerated.  *  * Nota Bene: Unfortunately, the order here is important!  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c0bc5280e03
block|{
DECL|enumerator|GIMP_COMPOSITE_NORMAL
name|GIMP_COMPOSITE_NORMAL
init|=
name|GIMP_NORMAL_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_DISSOLVE
name|GIMP_COMPOSITE_DISSOLVE
init|=
name|GIMP_DISSOLVE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_BEHIND
name|GIMP_COMPOSITE_BEHIND
init|=
name|GIMP_BEHIND_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_MULTIPLY
name|GIMP_COMPOSITE_MULTIPLY
init|=
name|GIMP_MULTIPLY_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_SCREEN
name|GIMP_COMPOSITE_SCREEN
init|=
name|GIMP_SCREEN_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_OVERLAY
name|GIMP_COMPOSITE_OVERLAY
init|=
name|GIMP_OVERLAY_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_DIFFERENCE
name|GIMP_COMPOSITE_DIFFERENCE
init|=
name|GIMP_DIFFERENCE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_ADDITION
name|GIMP_COMPOSITE_ADDITION
init|=
name|GIMP_ADDITION_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_SUBTRACT
name|GIMP_COMPOSITE_SUBTRACT
init|=
name|GIMP_SUBTRACT_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_DARKEN
name|GIMP_COMPOSITE_DARKEN
init|=
name|GIMP_DARKEN_ONLY_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_LIGHTEN
name|GIMP_COMPOSITE_LIGHTEN
init|=
name|GIMP_LIGHTEN_ONLY_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_HUE
name|GIMP_COMPOSITE_HUE
init|=
name|GIMP_HUE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_SATURATION
name|GIMP_COMPOSITE_SATURATION
init|=
name|GIMP_SATURATION_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_COLOR_ONLY
name|GIMP_COMPOSITE_COLOR_ONLY
init|=
name|GIMP_COLOR_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_VALUE
name|GIMP_COMPOSITE_VALUE
init|=
name|GIMP_VALUE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_DIVIDE
name|GIMP_COMPOSITE_DIVIDE
init|=
name|GIMP_DIVIDE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_DODGE
name|GIMP_COMPOSITE_DODGE
init|=
name|GIMP_DODGE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_BURN
name|GIMP_COMPOSITE_BURN
init|=
name|GIMP_BURN_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_HARDLIGHT
name|GIMP_COMPOSITE_HARDLIGHT
init|=
name|GIMP_HARDLIGHT_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_SOFTLIGHT
name|GIMP_COMPOSITE_SOFTLIGHT
init|=
name|GIMP_SOFTLIGHT_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_GRAIN_EXTRACT
name|GIMP_COMPOSITE_GRAIN_EXTRACT
init|=
name|GIMP_GRAIN_EXTRACT_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_GRAIN_MERGE
name|GIMP_COMPOSITE_GRAIN_MERGE
init|=
name|GIMP_GRAIN_MERGE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_COLOR_ERASE
name|GIMP_COMPOSITE_COLOR_ERASE
init|=
name|GIMP_COLOR_ERASE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_ERASE
name|GIMP_COMPOSITE_ERASE
init|=
name|GIMP_ERASE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_REPLACE
name|GIMP_COMPOSITE_REPLACE
init|=
name|GIMP_REPLACE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_ANTI_ERASE
name|GIMP_COMPOSITE_ANTI_ERASE
init|=
name|GIMP_ANTI_ERASE_MODE
block|,
DECL|enumerator|GIMP_COMPOSITE_BLEND
name|GIMP_COMPOSITE_BLEND
block|,
DECL|enumerator|GIMP_COMPOSITE_SHADE
name|GIMP_COMPOSITE_SHADE
block|,
DECL|enumerator|GIMP_COMPOSITE_SWAP
name|GIMP_COMPOSITE_SWAP
block|,
DECL|enumerator|GIMP_COMPOSITE_SCALE
name|GIMP_COMPOSITE_SCALE
block|,
DECL|enumerator|GIMP_COMPOSITE_CONVERT
name|GIMP_COMPOSITE_CONVERT
block|,
DECL|enumerator|GIMP_COMPOSITE_N
name|GIMP_COMPOSITE_N
DECL|typedef|GimpCompositeOperation
block|}
name|GimpCompositeOperation
typedef|;
end_typedef

begin_struct
DECL|struct|GimpCompositeOperationEffects
struct|struct
name|GimpCompositeOperationEffects
block|{
DECL|member|affect_opacity
name|guchar
name|affect_opacity
decl_stmt|;
DECL|member|increase_opacity
name|guchar
name|increase_opacity
decl_stmt|;
DECL|member|decrease_opacity
name|guchar
name|decrease_opacity
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|struct
name|GimpCompositeOperationEffects
name|gimp_composite_operation_effects
index|[]
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * This is structure for communicating all that is necessary to a  * compositing operation.  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c0bc5280f08
block|{
DECL|member|A
name|guchar
modifier|*
name|A
decl_stmt|;
comment|/* Source A    */
DECL|member|B
name|guchar
modifier|*
name|B
decl_stmt|;
comment|/* Source B    */
DECL|member|D
name|guchar
modifier|*
name|D
decl_stmt|;
comment|/* Destination */
DECL|member|M
name|guchar
modifier|*
name|M
decl_stmt|;
comment|/* Mask        */
DECL|member|n_pixels
name|gulong
name|n_pixels
decl_stmt|;
DECL|member|pixelformat_A
name|GimpPixelFormat
name|pixelformat_A
decl_stmt|;
DECL|member|pixelformat_B
name|GimpPixelFormat
name|pixelformat_B
decl_stmt|;
DECL|member|pixelformat_D
name|GimpPixelFormat
name|pixelformat_D
decl_stmt|;
DECL|member|pixelformat_M
name|GimpPixelFormat
name|pixelformat_M
decl_stmt|;
DECL|struct|__anon2c0bc5281008
DECL|member|opacity
DECL|member|affect
DECL|member|replace
struct|struct
block|{
name|gint
name|opacity
decl_stmt|;
name|gchar
name|affect
decl_stmt|;
block|}
name|replace
struct|;
DECL|struct|__anon2c0bc5281108
DECL|member|scale
DECL|member|scale
struct|struct
block|{
name|gint
name|scale
decl_stmt|;
block|}
name|scale
struct|;
DECL|struct|__anon2c0bc5281208
DECL|member|blend
DECL|member|blend
struct|struct
block|{
name|gint
name|blend
decl_stmt|;
block|}
name|blend
struct|;
DECL|struct|__anon2c0bc5281308
DECL|member|x
DECL|member|y
DECL|member|opacity
DECL|member|dissolve
struct|struct
block|{
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
name|gint
name|opacity
decl_stmt|;
block|}
name|dissolve
struct|;
DECL|member|combine
name|CombinationMode
name|combine
decl_stmt|;
DECL|member|op
name|GimpCompositeOperation
name|op
decl_stmt|;
DECL|typedef|GimpCompositeContext
block|}
name|GimpCompositeContext
typedef|;
end_typedef

begin_struct
DECL|struct|GimpCompositeOptions
struct|struct
name|GimpCompositeOptions
block|{
DECL|member|initialised
name|gboolean
name|initialised
decl_stmt|;
DECL|member|use
name|gboolean
name|use
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
specifier|extern
name|struct
name|GimpCompositeOptions
name|gimp_composite_options
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|extern
name|void
name|gimp_composite_dispatch
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_context_print
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COMPOSITE_H__  */
end_comment

end_unit

