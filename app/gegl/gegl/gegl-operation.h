begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* This file is part of GEGL  *  * GEGL is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * GEGL is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with GEGL; if not, see<http://www.gnu.org/licenses/>.  *  * Copyright 2003 Calvin Williamson  *           2005, 2006 Ãyvind KolÃ¥s  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GEGL_OPERATION_H__
end_ifndef

begin_define
DECL|macro|__GEGL_OPERATION_H__
define|#
directive|define
name|__GEGL_OPERATION_H__
end_define

begin_include
include|#
directive|include
file|"gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"buffer/gegl-buffer-types.h"
end_include

begin_include
include|#
directive|include
file|<babl/babl.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GEGL_TYPE_OPERATION
define|#
directive|define
name|GEGL_TYPE_OPERATION
value|(gegl_operation_get_type ())
end_define

begin_define
DECL|macro|GEGL_OPERATION (obj)
define|#
directive|define
name|GEGL_OPERATION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GEGL_TYPE_OPERATION, GeglOperation))
end_define

begin_define
DECL|macro|GEGL_OPERATION_CLASS (klass)
define|#
directive|define
name|GEGL_OPERATION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GEGL_TYPE_OPERATION, GeglOperationClass))
end_define

begin_define
DECL|macro|GEGL_IS_OPERATION (obj)
define|#
directive|define
name|GEGL_IS_OPERATION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEGL_TYPE_OPERATION))
end_define

begin_define
DECL|macro|GEGL_IS_OPERATION_CLASS (klass)
define|#
directive|define
name|GEGL_IS_OPERATION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GEGL_TYPE_OPERATION))
end_define

begin_define
DECL|macro|GEGL_OPERATION_GET_CLASS (obj)
define|#
directive|define
name|GEGL_OPERATION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GEGL_TYPE_OPERATION, GeglOperationClass))
end_define

begin_define
DECL|macro|MAX_PADS
define|#
directive|define
name|MAX_PADS
value|16
end_define

begin_define
DECL|macro|MAX_INPUT_PADS
define|#
directive|define
name|MAX_INPUT_PADS
value|MAX_PADS
end_define

begin_define
DECL|macro|MAX_OUTPUT_PADS
define|#
directive|define
name|MAX_OUTPUT_PADS
value|MAX_PADS
end_define

begin_typedef
DECL|typedef|GeglOperationClass
typedef|typedef
name|struct
name|_GeglOperationClass
name|GeglOperationClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GeglOperation
struct|struct
name|_GeglOperation
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|node
name|GeglNode
modifier|*
name|node
decl_stmt|;
comment|/* the node that this operation object is communicated                       with through */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GeglOperationClass
struct|struct
name|_GeglOperationClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
DECL|member|name
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
comment|/* name used to refer to this type of                                     operation in GEGL */
DECL|member|description
name|gchar
modifier|*
name|description
decl_stmt|;
comment|/* textual description of the operation */
DECL|member|categories
name|char
modifier|*
name|categories
decl_stmt|;
comment|/* a colon seperated list of categories */
DECL|member|no_cache
name|gboolean
name|no_cache
decl_stmt|;
comment|/* do not create a cache for this operation */
comment|/* attach this operation with a GeglNode, override this if you are creating a    * GeglGraph, it is already defined for Filters/Sources/Composers.    */
DECL|member|attach
name|void
function_decl|(
modifier|*
name|attach
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
comment|/* called as a refresh before any of the region needs getters, used in    * the area base class for instance.    */
DECL|member|tickle
name|void
function_decl|(
modifier|*
name|tickle
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
comment|/* prepare the node for processing (all properties will be set) override this    * if you are creating a meta operation (using the node as a GeglGraph).    */
DECL|member|prepare
name|void
function_decl|(
modifier|*
name|prepare
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
comment|/* Returns a bounding rectangle for the data that is defined by this op. (is    * already implemented in GeglOperationPointFilter and    * GeglOperationPointComposer, GeglOperationAreaFilter base classes.    */
DECL|member|get_defined_region
name|GeglRectangle
function_decl|(
modifier|*
name|get_defined_region
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
comment|/* Computes the region in output (same affected rect assumed for all outputs)    * when a given region has changed on an input. Used to aggregate dirt in the    * graph. A default implementation of this, if not provided should probably    * be to report that the entire defined region is dirtied.    */
DECL|member|compute_affected_region
name|GeglRectangle
function_decl|(
modifier|*
name|compute_affected_region
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|input_pad
parameter_list|,
name|GeglRectangle
name|region
parameter_list|)
function_decl|;
comment|/* computes the rectangle needed to be correctly computed in a buffer    * on the named input_pad, for a given result rectangle    */
DECL|member|compute_input_request
name|GeglRectangle
function_decl|(
modifier|*
name|compute_input_request
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|input_pad
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
comment|/* Adjust result rect, adapts the rectangle used for computing results.    * (useful for global operations like contrast stretching, as well as    * file loaders to force caching of the full raster).    */
DECL|member|adjust_result_region
name|GeglRectangle
function_decl|(
modifier|*
name|adjust_result_region
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
comment|/* Returns the node providing data for a specific location    */
DECL|member|detect
name|GeglNode
modifier|*
function_decl|(
modifier|*
name|detect
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
comment|/* XXX: get array of in Gvalues and out Gvalues, filled with buffers? */
comment|/* do the actual processing needed to put GeglBuffers on the output pad    * Replace context_id with an actual object?    *    * GeglOperationData<- per evaluation unique data for operation?    *                       (or node?)     *    * .. compute_input request?    *    */
DECL|member|process
name|gboolean
function_decl|(
modifier|*
name|process
function_decl|)
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
comment|/*                               GValue             **pads,                               const gchar        **pad_names,                               gint                 n_pads,                               const GeglRectangle *result_rect,                               const GeglRectangle *requested_rect,     */
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|output_pad
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result_rect
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_comment
comment|/* returns|registers the gtype for GeglOperation */
end_comment

begin_decl_stmt
name|GType
name|gegl_operation_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* retrieves the bounding box of a connected input */
end_comment

begin_function_decl
name|GeglRectangle
modifier|*
name|gegl_operation_source_get_defined_region
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pad_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* sets the ROI needed to be computed on one of the sources */
end_comment

begin_function_decl
name|void
name|gegl_operation_set_source_region
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pad_name
parameter_list|,
name|GeglRectangle
modifier|*
name|region
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* returns the bounding box of the buffer that needs to be computed */
end_comment

begin_comment
unit|const GeglRectangle * gegl_operation_result_rect    (GeglOperation *operation,                                                      gpointer       context_id);
comment|/* returns the bounding box of the buffer needed for computation */
end_comment

begin_endif
unit|const GeglRectangle * gegl_operation_need_rect      (GeglOperation *operation,                                                      gpointer       context_id);
endif|#
directive|endif
end_endif

begin_comment
comment|/* virtual method invokers that depends only on the set properties of a  * operation|node  */
end_comment

begin_comment
comment|/* retrieves the node providing data to a named input pad */
end_comment

begin_function_decl
name|GeglNode
modifier|*
name|gegl_operation_get_source_node
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pad_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
name|gegl_operation_compute_affected_region
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|input_pad
parameter_list|,
name|GeglRectangle
name|region
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
name|gegl_operation_get_defined_region
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
name|gegl_operation_adjust_result_region
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglRectangle
name|gegl_operation_compute_input_request
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|input_pad
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglNode
modifier|*
name|gegl_operation_detect
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* virtual method invokers that change behavior based on the roi being computed,  * needs a context_id being based that is used for storing dynamic data.  */
end_comment

begin_function_decl
name|void
name|gegl_operation_attach
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GeglNode
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_operation_prepare
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gegl_operation_process
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|output_pad
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|result_rect
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* retrieve the buffer that we are going to write into, it will be of the  * dimensions retrieved through the rectangle computation, and of the format  * currently specified on the associated nodes, "property_name" pad.  */
end_comment

begin_function_decl
name|GeglBuffer
modifier|*
name|gegl_operation_get_target
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GeglBuffer
modifier|*
name|gegl_operation_get_source
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gegl_list_operations
parameter_list|(
name|guint
modifier|*
name|n_operations_p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GParamSpec
modifier|*
modifier|*
name|gegl_list_properties
parameter_list|(
specifier|const
name|gchar
modifier|*
name|operation_type
parameter_list|,
name|guint
modifier|*
name|n_properties_p
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* set the name of an operation, transforms all occurences of "_" into "-" */
end_comment

begin_function_decl
name|void
name|gegl_operation_class_set_name
parameter_list|(
name|GeglOperationClass
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* create a pad for a specified property for this operation, this method is  * to be called from the attach method of operations, most operations do not  * have to care about this since a super class like filter, sink, source or  * composer already does so.  */
end_comment

begin_function_decl
name|void
name|gegl_operation_create_pad
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* specify the bablformat for a pad on this operation (XXX: document when  * this is legal, at the moment, only used internally in some ops,. but might  * turn into a global mechanism) */
end_comment

begin_function_decl
name|void
name|gegl_operation_set_format
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pad_name
parameter_list|,
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Used to look up the gtype when changing the type of operation associated  * a GeglNode using just a string with the registered name.  */
end_comment

begin_function_decl
name|GType
name|gegl_operation_gtype_from_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* set a dynamic named instance for this node, this function takes over  * ownership of the reference (should only be used for internal GeglOperation  * implementations that override caching behaviour, use with care)  */
end_comment

begin_function_decl
name|void
name|gegl_operation_set_data
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|GObject
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*************************  *  The following is internal GEGL functions, declared in the header for now, should.  *  be removed when the operation API is made public.  */
end_comment

begin_comment
comment|/* retrieve a gobject previously set dynamically on an operation */
end_comment

begin_function_decl
name|GObject
modifier|*
name|gegl_operation_get_data
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gegl_operation_calc_source_regions
parameter_list|(
name|GeglOperation
modifier|*
name|operation
parameter_list|,
name|gpointer
name|context_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_operation_vector_prop_changed
parameter_list|(
name|GeglVector
modifier|*
name|vector
parameter_list|,
name|GeglOperation
modifier|*
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_extension_handler_cleanup
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gegl_operation_gtype_cleanup
parameter_list|(
name|void
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
comment|/* __GEGL_OPERATION_H__ */
end_comment

end_unit

