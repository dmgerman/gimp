begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * extra constants for use by the plugin  */
end_comment

begin_define
DECL|macro|TRACE_NONE
define|#
directive|define
name|TRACE_NONE
value|0x00
end_define

begin_define
DECL|macro|TRACE_CALL
define|#
directive|define
name|TRACE_CALL
value|0x01
end_define

begin_define
DECL|macro|TRACE_TYPE
define|#
directive|define
name|TRACE_TYPE
value|0x11
end_define

begin_define
DECL|macro|TRACE_NAME
define|#
directive|define
name|TRACE_NAME
value|0x21
end_define

begin_define
DECL|macro|TRACE_DESC
define|#
directive|define
name|TRACE_DESC
value|0x41
end_define

begin_define
DECL|macro|TRACE_ALL
define|#
directive|define
name|TRACE_ALL
value|0xff
end_define

begin_comment
comment|/* defs missing from libgimp */
end_comment

begin_define
DECL|macro|BEHIND_MODE
define|#
directive|define
name|BEHIND_MODE
value|2
end_define

begin_define
DECL|macro|FG_BG_RGB
define|#
directive|define
name|FG_BG_RGB
value|0
end_define

begin_define
DECL|macro|FG_BG_HSV
define|#
directive|define
name|FG_BG_HSV
value|1
end_define

begin_define
DECL|macro|FG_TRANS
define|#
directive|define
name|FG_TRANS
value|2
end_define

begin_define
DECL|macro|CUSTOM
define|#
directive|define
name|CUSTOM
value|3
end_define

begin_define
DECL|macro|LINEAR
define|#
directive|define
name|LINEAR
value|0
end_define

begin_define
DECL|macro|BILINEAR
define|#
directive|define
name|BILINEAR
value|1
end_define

begin_define
DECL|macro|RADIAL
define|#
directive|define
name|RADIAL
value|2
end_define

begin_define
DECL|macro|SQUARE
define|#
directive|define
name|SQUARE
value|3
end_define

begin_define
DECL|macro|CONICAL_SYMMETRIC
define|#
directive|define
name|CONICAL_SYMMETRIC
value|4
end_define

begin_define
DECL|macro|CONICAL_ASYMMETRIC
define|#
directive|define
name|CONICAL_ASYMMETRIC
value|5
end_define

begin_define
DECL|macro|SHAPEBURST_ANGULAR
define|#
directive|define
name|SHAPEBURST_ANGULAR
value|6
end_define

begin_define
DECL|macro|SHAPEBURST_SPHERICAL
define|#
directive|define
name|SHAPEBURST_SPHERICAL
value|7
end_define

begin_define
DECL|macro|SHAPEBURST_DIMPLED
define|#
directive|define
name|SHAPEBURST_DIMPLED
value|8
end_define

begin_define
DECL|macro|REPEAT_NONE
define|#
directive|define
name|REPEAT_NONE
value|0
end_define

begin_define
DECL|macro|REPEAT_SAWTOOTH
define|#
directive|define
name|REPEAT_SAWTOOTH
value|1
end_define

begin_define
DECL|macro|REPEAT_TRIANGULAR
define|#
directive|define
name|REPEAT_TRIANGULAR
value|2
end_define

begin_define
DECL|macro|FG_BUCKET_FILL
define|#
directive|define
name|FG_BUCKET_FILL
value|0
end_define

begin_define
DECL|macro|BG_BUCKET_FILL
define|#
directive|define
name|BG_BUCKET_FILL
value|1
end_define

begin_define
DECL|macro|PATTERN_BUCKET_FILL
define|#
directive|define
name|PATTERN_BUCKET_FILL
value|2
end_define

begin_define
DECL|macro|RED_CHANNEL
define|#
directive|define
name|RED_CHANNEL
value|0
end_define

begin_define
DECL|macro|GREEN_CHANNEL
define|#
directive|define
name|GREEN_CHANNEL
value|1
end_define

begin_define
DECL|macro|BLUE_CHANNEL
define|#
directive|define
name|BLUE_CHANNEL
value|2
end_define

begin_define
DECL|macro|GRAY_CHANNEL
define|#
directive|define
name|GRAY_CHANNEL
value|3
end_define

begin_define
DECL|macro|INDEXED_CHANNEL
define|#
directive|define
name|INDEXED_CHANNEL
value|4
end_define

begin_define
DECL|macro|WHITE_MASK
define|#
directive|define
name|WHITE_MASK
value|0
end_define

begin_define
DECL|macro|BLACK_MASK
define|#
directive|define
name|BLACK_MASK
value|1
end_define

begin_define
DECL|macro|ALPHA_MASK
define|#
directive|define
name|ALPHA_MASK
value|2
end_define

begin_define
DECL|macro|APPLY
define|#
directive|define
name|APPLY
value|0
end_define

begin_define
DECL|macro|DISCARD
define|#
directive|define
name|DISCARD
value|1
end_define

begin_define
DECL|macro|EXPAND_AS_NECESSARY
define|#
directive|define
name|EXPAND_AS_NECESSARY
value|0
end_define

begin_define
DECL|macro|CLIP_TO_IMAGE
define|#
directive|define
name|CLIP_TO_IMAGE
value|1
end_define

begin_define
DECL|macro|CLIP_TO_BOTTOM_LAYER
define|#
directive|define
name|CLIP_TO_BOTTOM_LAYER
value|2
end_define

begin_define
DECL|macro|SELECTION_ADD
define|#
directive|define
name|SELECTION_ADD
value|0
end_define

begin_define
DECL|macro|SELECTION_SUB
define|#
directive|define
name|SELECTION_SUB
value|1
end_define

begin_define
DECL|macro|SELECTION_REPLACE
define|#
directive|define
name|SELECTION_REPLACE
value|2
end_define

begin_define
DECL|macro|SELECTION_INTERSECT
define|#
directive|define
name|SELECTION_INTERSECT
value|3
end_define

begin_define
DECL|macro|PIXELS
define|#
directive|define
name|PIXELS
value|0
end_define

begin_define
DECL|macro|POINTS
define|#
directive|define
name|POINTS
value|1
end_define

begin_define
DECL|macro|IMAGE_CLONE
define|#
directive|define
name|IMAGE_CLONE
value|0
end_define

begin_define
DECL|macro|PATTERN_CLONE
define|#
directive|define
name|PATTERN_CLONE
value|1
end_define

begin_define
DECL|macro|BLUR
define|#
directive|define
name|BLUR
value|0
end_define

begin_define
DECL|macro|SHARPEN
define|#
directive|define
name|SHARPEN
value|1
end_define

begin_comment
comment|/* #define TRUE 1 #define FALSE 0 */
end_comment

end_unit

