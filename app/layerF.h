begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__LAYER_F_H__
end_ifndef

begin_define
DECL|macro|__LAYER_F_H__
define|#
directive|define
name|__LAYER_F_H__
end_define

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=ADD_>*/
DECL|enum|__anon28c80aec0103
block|{
DECL|enumerator|ADD_WHITE_MASK
name|ADD_WHITE_MASK
block|,
DECL|enumerator|ADD_BLACK_MASK
name|ADD_BLACK_MASK
block|,
DECL|enumerator|ADD_ALPHA_MASK
name|ADD_ALPHA_MASK
DECL|typedef|AddMaskType
block|}
name|AddMaskType
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayer
typedef|typedef
name|struct
name|_GimpLayer
name|GimpLayer
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerClass
typedef|typedef
name|struct
name|_GimpLayerClass
name|GimpLayerClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerMask
typedef|typedef
name|struct
name|_GimpLayerMask
name|GimpLayerMask
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerMaskClass
typedef|typedef
name|struct
name|_GimpLayerMaskClass
name|GimpLayerMaskClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|Layer
typedef|typedef
name|GimpLayer
name|Layer
typedef|;
end_typedef

begin_comment
DECL|typedef|Layer
comment|/* convenience */
end_comment

begin_typedef
DECL|typedef|LayerMask
typedef|typedef
name|GimpLayerMask
name|LayerMask
typedef|;
end_typedef

begin_comment
DECL|typedef|LayerMask
comment|/* convenience */
end_comment

begin_typedef
DECL|typedef|LayerUndo
typedef|typedef
name|struct
name|_layer_undo
name|LayerUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|LayerMaskUndo
typedef|typedef
name|struct
name|_layer_mask_undo
name|LayerMaskUndo
typedef|;
end_typedef

begin_typedef
DECL|typedef|FStoLayerUndo
typedef|typedef
name|struct
name|_fs_to_layer_undo
name|FStoLayerUndo
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

end_unit

