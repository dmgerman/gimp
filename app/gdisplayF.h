begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GDISPLAY_F_H__
end_ifndef

begin_define
DECL|macro|__GDISPLAY_F_H__
define|#
directive|define
name|__GDISPLAY_F_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c4813610103
block|{
DECL|enumerator|SelectionOff
name|SelectionOff
block|,
DECL|enumerator|SelectionLayerOff
name|SelectionLayerOff
block|,
DECL|enumerator|SelectionOn
name|SelectionOn
block|,
DECL|enumerator|SelectionPause
name|SelectionPause
block|,
DECL|enumerator|SelectionResume
name|SelectionResume
DECL|typedef|SelectionControl
block|}
name|SelectionControl
typedef|;
end_typedef

begin_typedef
DECL|typedef|GDisplay
typedef|typedef
name|struct
name|_GDisplay
name|GDisplay
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

end_unit

