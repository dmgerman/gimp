begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* $Id$ */
end_comment

begin_include
include|#
directive|include
file|"glace.h"
end_include

begin_typedef
DECL|struct|__anon2771ffdf0108
typedef|typedef
struct|struct
block|{
DECL|member|strength
name|gdouble
name|strength
decl_stmt|;
DECL|member|bradj
name|gdouble
name|bradj
decl_stmt|;
DECL|member|coefftol
name|gdouble
name|coefftol
decl_stmt|;
DECL|member|smoothing
name|gdouble
name|smoothing
decl_stmt|;
DECL|member|iterations
name|guint
name|iterations
decl_stmt|;
DECL|member|wsize
name|guint
name|wsize
decl_stmt|;
DECL|member|color_method
name|Glace_ColorMethods
name|color_method
decl_stmt|;
DECL|member|link
name|gboolean
name|link
decl_stmt|;
DECL|typedef|AceValues
block|}
name|AceValues
typedef|;
end_typedef

end_unit

