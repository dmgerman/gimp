begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* This file is part of GEGL  *  * GEGL is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * GEGL is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with GEGL; if not, see<http://www.gnu.org/licenses/>.  *  * Copyright 2003 Calvin Williamson  *           2006 Ãyvind KolÃ¥s  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GEGL_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GEGL_TYPES_H__
define|#
directive|define
name|__GEGL_TYPES_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GeglConnection
typedef|typedef
name|struct
name|_GeglConnection
name|GeglConnection
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglColor
typedef|typedef
name|struct
name|_GeglColor
name|GeglColor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglCurve
typedef|typedef
name|struct
name|_GeglCurve
name|GeglCurve
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglCRVisitor
typedef|typedef
name|struct
name|_GeglCRVisitor
name|GeglCRVisitor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglDebugRectVisitor
typedef|typedef
name|struct
name|_GeglDebugRectVisitor
name|GeglDebugRectVisitor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglEvalMgr
typedef|typedef
name|struct
name|_GeglEvalMgr
name|GeglEvalMgr
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglEvalVisitor
typedef|typedef
name|struct
name|_GeglEvalVisitor
name|GeglEvalVisitor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglFinishVisitor
typedef|typedef
name|struct
name|_GeglFinishVisitor
name|GeglFinishVisitor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglGraph
typedef|typedef
name|struct
name|_GeglGraph
name|GeglGraph
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglHaveVisitor
typedef|typedef
name|struct
name|_GeglHaveVisitor
name|GeglHaveVisitor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglNeedVisitor
typedef|typedef
name|struct
name|_GeglNeedVisitor
name|GeglNeedVisitor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglNode
typedef|typedef
name|struct
name|_GeglNode
name|GeglNode
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglNodeDynamic
typedef|typedef
name|struct
name|_GeglNodeDynamic
name|GeglNodeDynamic
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglOperation
typedef|typedef
name|struct
name|_GeglOperation
name|GeglOperation
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglPad
typedef|typedef
name|struct
name|_GeglPad
name|GeglPad
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglVector
typedef|typedef
name|struct
name|_GeglVector
name|GeglVector
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglProcessor
typedef|typedef
name|struct
name|_GeglProcessor
name|GeglProcessor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglPrepareVisitor
typedef|typedef
name|struct
name|_GeglPrepareVisitor
name|GeglPrepareVisitor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglVisitable
typedef|typedef
name|struct
name|_GeglVisitable
name|GeglVisitable
typedef|;
end_typedef

begin_comment
DECL|typedef|GeglVisitable
comment|/* dummy typedef */
end_comment

begin_typedef
DECL|typedef|GeglVisitor
typedef|typedef
name|struct
name|_GeglVisitor
name|GeglVisitor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglRectangle
typedef|typedef
name|struct
name|_GeglRectangle
name|GeglRectangle
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglPoint
typedef|typedef
name|struct
name|_GeglPoint
name|GeglPoint
typedef|;
end_typedef

begin_typedef
DECL|typedef|GeglDimension
typedef|typedef
name|struct
name|_GeglDimension
name|GeglDimension
typedef|;
end_typedef

begin_struct
DECL|struct|_GeglRectangle
struct|struct
name|_GeglRectangle
block|{
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GeglPoint
struct|struct
name|_GeglPoint
block|{
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GeglDimension
struct|struct
name|_GeglDimension
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
block|}
struct|;
end_struct

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GEGL_TYPES_H__ */
end_comment

end_unit

