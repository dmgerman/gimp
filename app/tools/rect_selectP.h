begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__RECT_SELECTP_H__
end_ifndef

begin_define
DECL|macro|__RECT_SELECTP_H__
define|#
directive|define
name|__RECT_SELECTP_H__
end_define

begin_include
include|#
directive|include
file|"draw_core.h"
end_include

begin_typedef
DECL|typedef|RectSelect
DECL|typedef|EllipseSelect
typedef|typedef
name|struct
name|_rect_select
name|RectSelect
typedef|,
name|EllipseSelect
typedef|;
end_typedef

begin_struct
DECL|struct|_rect_select
struct|struct
name|_rect_select
block|{
DECL|member|core
name|DrawCore
modifier|*
name|core
decl_stmt|;
comment|/*  Core select object                      */
DECL|member|x
DECL|member|y
name|int
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  upper left hand coordinate              */
DECL|member|w
DECL|member|h
name|int
name|w
decl_stmt|,
name|h
decl_stmt|;
comment|/*  width and height                        */
DECL|member|center
name|int
name|center
decl_stmt|;
comment|/*  is the selection being created from the center out? */
DECL|member|op
name|int
name|op
decl_stmt|;
comment|/*  selection operation (ADD, SUB, etc)     */
DECL|member|context_id
name|guint
name|context_id
decl_stmt|;
comment|/*  for the statusbar                       */
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __RECT_SELECTP_H__  */
end_comment

end_unit

