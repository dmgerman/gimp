begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__BOUNDARY_F_H__
end_ifndef

begin_define
DECL|macro|__BOUNDARY_F_H__
define|#
directive|define
name|__BOUNDARY_F_H__
end_define

begin_typedef
DECL|typedef|BoundSeg
typedef|typedef
name|struct
name|_BoundSeg
name|BoundSeg
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27baa44e0103
block|{
DECL|enumerator|WithinBounds
name|WithinBounds
block|,
DECL|enumerator|IgnoreBounds
name|IgnoreBounds
DECL|typedef|BoundaryType
block|}
name|BoundaryType
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

end_unit

