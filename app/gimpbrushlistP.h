begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPBRUSHLISTP_H__
end_ifndef

begin_define
DECL|macro|__GIMPBRUSHLISTP_H__
define|#
directive|define
name|__GIMPBRUSHLISTP_H__
end_define

begin_include
include|#
directive|include
file|"gimplistP.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushlist.h"
end_include

begin_struct
DECL|struct|_GimpBrushList
struct|struct
name|_GimpBrushList
block|{
DECL|member|gimplist
name|GimpList
name|gimplist
decl_stmt|;
DECL|member|num_brushes
name|int
name|num_brushes
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBrushListClass
struct|struct
name|_GimpBrushListClass
block|{
DECL|member|parent_class
name|GimpListClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpBrushListClass
typedef|typedef
name|struct
name|_GimpBrushListClass
name|GimpBrushListClass
typedef|;
end_typedef

begin_define
DECL|macro|BRUSH_LIST_CLASS (klass)
define|#
directive|define
name|BRUSH_LIST_CLASS
parameter_list|(
name|klass
parameter_list|)
define|\
value|GTK_CHECK_CLASS_CAST (klass, gimp_brush_list_get_type(), GimpBrushListClass)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMPBRUSHLISTP_H__ */
end_comment

end_unit

