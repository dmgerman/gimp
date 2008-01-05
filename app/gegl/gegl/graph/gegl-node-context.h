begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* This file is part of GEGL  *  * GEGL is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * GEGL is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with GEGL; if not, see<http://www.gnu.org/licenses/>.  *  * Copyright 2003 Calvin Williamson  *           2006 Ãyvind KolÃ¥s  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GEGL_NODE_CONTEXT_H__
end_ifndef

begin_define
DECL|macro|__GEGL_NODE_CONTEXT_H__
define|#
directive|define
name|__GEGL_NODE_CONTEXT_H__
end_define

begin_include
include|#
directive|include
file|<gegl/buffer/gegl-buffer.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GEGL_TYPE_NODE_CONTEXT
define|#
directive|define
name|GEGL_TYPE_NODE_CONTEXT
value|(gegl_node_context_get_type ())
end_define

begin_define
DECL|macro|GEGL_NODE_CONTEXT (obj)
define|#
directive|define
name|GEGL_NODE_CONTEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GEGL_TYPE_NODE_CONTEXT, GeglNodeContext))
end_define

begin_define
DECL|macro|GEGL_NODE_CONTEXT_CLASS (klass)
define|#
directive|define
name|GEGL_NODE_CONTEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GEGL_TYPE_NODE_CONTEXT, GeglNodeContextClass))
end_define

begin_define
DECL|macro|GEGL_IS_NODE_CONTEXT (obj)
define|#
directive|define
name|GEGL_IS_NODE_CONTEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEGL_TYPE_NODE_CONTEXT))
end_define

begin_define
DECL|macro|GEGL_IS_NODE_CONTEXT_CLASS (klass)
define|#
directive|define
name|GEGL_IS_NODE_CONTEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GEGL_TYPE_NODE_CONTEXT))
end_define

begin_define
DECL|macro|GEGL_NODE_CONTEXT_GET_CLASS (obj)
define|#
directive|define
name|GEGL_NODE_CONTEXT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GEGL_TYPE_NODE_CONTEXT, GeglNodeContextClass))
end_define

begin_typedef
DECL|typedef|GeglNodeContextClass
typedef|typedef
name|struct
name|_GeglNodeContextClass
name|GeglNodeContextClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GeglNodeContext
struct|struct
name|_GeglNodeContext
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|node
name|GeglNode
modifier|*
name|node
decl_stmt|;
DECL|member|context_id
name|gpointer
name|context_id
decl_stmt|;
DECL|member|need_rect
name|GeglRectangle
name|need_rect
decl_stmt|;
comment|/* the rectangle needed from this node */
DECL|member|result_rect
name|GeglRectangle
name|result_rect
decl_stmt|;
comment|/* the result computation rectangle for this node,                                  (will differ if the needed rect extends beyond                                  the defined rectangle, some operations might                                  event force/suggest expansion of the result                                  rect.. (contrast stretch?))                                */
DECL|member|cached
name|gboolean
name|cached
decl_stmt|;
comment|/* true if the cache can be used directly, and                                   recomputation of inputs is unneccesary) */
DECL|member|refs
name|gint
name|refs
decl_stmt|;
comment|/* set to number of nodes that depends on it                                   before evaluation begins, each time data is                                   fetched from the op the reference count is                                   dropped, when it drops to zero, the op is                                   asked to clean it's pads                                 */
DECL|member|property
name|GSList
modifier|*
name|property
decl_stmt|;
comment|/* used internally for data being exchanged */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GeglNodeContextClass
struct|struct
name|_GeglNodeContextClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gegl_node_context_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GeglBuffer
modifier|*
name|gegl_node_context_get_target
parameter_list|(
name|GeglNodeContext
modifier|*
name|self
parameter_list|,
specifier|const
name|gchar
modifier|*
name|padname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gegl_node_context_get_source
parameter_list|(
name|GeglNodeContext
modifier|*
name|self
parameter_list|,
specifier|const
name|gchar
modifier|*
name|padname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GObject
modifier|*
name|gegl_node_context_get_object
parameter_list|(
name|GeglNodeContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|padname
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_node_context_set_object
parameter_list|(
name|GeglNodeContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|padname
parameter_list|,
name|GObject
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_node_context_set_property
parameter_list|(
name|GeglNodeContext
modifier|*
name|node
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_node_context_get_property
parameter_list|(
name|GeglNodeContext
modifier|*
name|node
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* the rest of these functions are for internal use only */
end_comment

begin_function_decl
name|void
name|gegl_node_context_remove_property
parameter_list|(
name|GeglNodeContext
modifier|*
name|self
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
modifier|*
name|gegl_node_context_get_need_rect
parameter_list|(
name|GeglNodeContext
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_node_context_set_need_rect
parameter_list|(
name|GeglNodeContext
modifier|*
name|node
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
modifier|*
name|gegl_node_context_get_result_rect
parameter_list|(
name|GeglNodeContext
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_node_context_set_result_rect
parameter_list|(
name|GeglNodeContext
modifier|*
name|node
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GEGL_NODE_H__ */
end_comment

end_unit

