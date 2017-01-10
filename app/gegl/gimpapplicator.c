begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpapplicator.c  * Copyright (C) 2012-2013 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-nodes.h"
end_include

begin_include
include|#
directive|include
file|"gimpapplicator.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_applicator_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_applicator_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_applicator_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpApplicator,gimp_applicator,G_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpApplicator
argument_list|,
argument|gimp_applicator
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_applicator_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_applicator_class_init
parameter_list|(
name|GimpApplicatorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_applicator_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_applicator_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_applicator_get_property
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_applicator_init (GimpApplicator * applicator)
name|gimp_applicator_init
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|)
block|{
name|applicator
operator|->
name|opacity
operator|=
literal|1.0
expr_stmt|;
name|applicator
operator|->
name|paint_mode
operator|=
name|GIMP_LAYER_MODE_NORMAL
expr_stmt|;
name|applicator
operator|->
name|affect
operator|=
name|GIMP_COMPONENT_MASK_ALL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_applicator_finalize (GObject * object)
name|gimp_applicator_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpApplicator
modifier|*
name|applicator
init|=
name|GIMP_APPLICATOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|applicator
operator|->
name|node
condition|)
block|{
name|g_object_unref
argument_list|(
name|applicator
operator|->
name|node
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|node
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_applicator_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_applicator_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
switch|switch
condition|(
name|property_id
condition|)
block|{
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_applicator_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_applicator_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
switch|switch
condition|(
name|property_id
condition|)
block|{
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|GimpApplicator
modifier|*
DECL|function|gimp_applicator_new (GeglNode * parent,gboolean linear,gboolean use_split_preview,gboolean use_result_cache)
name|gimp_applicator_new
parameter_list|(
name|GeglNode
modifier|*
name|parent
parameter_list|,
name|gboolean
name|linear
parameter_list|,
name|gboolean
name|use_split_preview
parameter_list|,
name|gboolean
name|use_result_cache
parameter_list|)
block|{
name|GimpApplicator
modifier|*
name|applicator
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GEGL_IS_NODE
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|applicator
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_APPLICATOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|linear
operator|=
name|linear
expr_stmt|;
if|if
condition|(
name|parent
condition|)
name|applicator
operator|->
name|node
operator|=
name|g_object_ref
argument_list|(
name|parent
argument_list|)
expr_stmt|;
else|else
name|applicator
operator|->
name|node
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|applicator
operator|->
name|input_node
operator|=
name|gegl_node_get_input_proxy
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|aux_node
operator|=
name|gegl_node_get_input_proxy
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|output_node
operator|=
name|gegl_node_get_output_proxy
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"output"
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|mode_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:normal"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_gegl_mode_node_set_mode
argument_list|(
name|applicator
operator|->
name|mode_node
argument_list|,
name|applicator
operator|->
name|paint_mode
argument_list|,
name|applicator
operator|->
name|linear
argument_list|)
expr_stmt|;
name|gimp_gegl_mode_node_set_opacity
argument_list|(
name|applicator
operator|->
name|mode_node
argument_list|,
name|applicator
operator|->
name|opacity
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|input_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|mode_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|apply_offset_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:translate"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|dup_apply_buffer_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:copy-buffer"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_link_many
argument_list|(
name|applicator
operator|->
name|aux_node
argument_list|,
name|applicator
operator|->
name|apply_offset_node
argument_list|,
name|applicator
operator|->
name|dup_apply_buffer_node
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_split_preview
condition|)
block|{
name|applicator
operator|->
name|preview_cache_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:cache"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|preview_crop_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:nop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_link_many
argument_list|(
name|applicator
operator|->
name|dup_apply_buffer_node
argument_list|,
name|applicator
operator|->
name|preview_cache_node
argument_list|,
name|applicator
operator|->
name|preview_crop_node
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|preview_crop_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|mode_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|dup_apply_buffer_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|mode_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
block|}
name|applicator
operator|->
name|mask_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|applicator
operator|->
name|mask_offset_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:translate"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|mask_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|mask_offset_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
comment|/* don't connect the the mask offset node to mode's aux2 yet */
name|applicator
operator|->
name|affect_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:mask-components"
argument_list|,
literal|"mask"
argument_list|,
name|applicator
operator|->
name|affect
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|use_result_cache
condition|)
block|{
name|applicator
operator|->
name|output_cache_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:cache"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_link_many
argument_list|(
name|applicator
operator|->
name|input_node
argument_list|,
name|applicator
operator|->
name|affect_node
argument_list|,
name|applicator
operator|->
name|output_cache_node
argument_list|,
name|applicator
operator|->
name|output_node
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_node_link_many
argument_list|(
name|applicator
operator|->
name|input_node
argument_list|,
name|applicator
operator|->
name|affect_node
argument_list|,
name|applicator
operator|->
name|output_node
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|mode_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|affect_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
return|return
name|applicator
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_src_buffer (GimpApplicator * applicator,GeglBuffer * src_buffer)
name|gimp_applicator_set_src_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|src_buffer
operator|==
name|NULL
operator|||
name|GEGL_IS_BUFFER
argument_list|(
name|src_buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|src_buffer
operator|==
name|applicator
operator|->
name|src_buffer
condition|)
return|return;
if|if
condition|(
name|src_buffer
condition|)
block|{
if|if
condition|(
operator|!
name|applicator
operator|->
name|src_node
condition|)
block|{
name|applicator
operator|->
name|src_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|src_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|src_node
argument_list|,
literal|"buffer"
argument_list|,
name|src_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|applicator
operator|->
name|src_buffer
condition|)
block|{
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|src_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|mode_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|src_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|affect_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|applicator
operator|->
name|src_buffer
condition|)
block|{
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|input_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|mode_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|input_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|affect_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
name|applicator
operator|->
name|src_buffer
operator|=
name|src_buffer
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_dest_buffer (GimpApplicator * applicator,GeglBuffer * dest_buffer)
name|gimp_applicator_set_dest_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglBuffer
modifier|*
name|dest_buffer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|dest_buffer
operator|==
name|NULL
operator|||
name|GEGL_IS_BUFFER
argument_list|(
name|dest_buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dest_buffer
operator|==
name|applicator
operator|->
name|dest_buffer
condition|)
return|return;
if|if
condition|(
name|dest_buffer
condition|)
block|{
if|if
condition|(
operator|!
name|applicator
operator|->
name|dest_node
condition|)
block|{
name|applicator
operator|->
name|dest_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:write-buffer"
argument_list|,
literal|"buffer"
argument_list|,
name|dest_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|dest_node
argument_list|,
literal|"buffer"
argument_list|,
name|dest_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|applicator
operator|->
name|dest_buffer
condition|)
block|{
name|gegl_node_disconnect
argument_list|(
name|applicator
operator|->
name|output_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|affect_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|dest_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|applicator
operator|->
name|dest_buffer
condition|)
block|{
name|gegl_node_disconnect
argument_list|(
name|applicator
operator|->
name|dest_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|affect_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|output_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
name|applicator
operator|->
name|dest_buffer
operator|=
name|dest_buffer
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_mask_buffer (GimpApplicator * applicator,GeglBuffer * mask_buffer)
name|gimp_applicator_set_mask_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|mask_buffer
operator|==
name|NULL
operator|||
name|GEGL_IS_BUFFER
argument_list|(
name|mask_buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|applicator
operator|->
name|mask_buffer
operator|==
name|mask_buffer
condition|)
return|return;
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|mask_node
argument_list|,
literal|"buffer"
argument_list|,
name|mask_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|mask_buffer
condition|)
block|{
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|mask_offset_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|mode_node
argument_list|,
literal|"aux2"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_node_disconnect
argument_list|(
name|applicator
operator|->
name|mode_node
argument_list|,
literal|"aux2"
argument_list|)
expr_stmt|;
block|}
name|applicator
operator|->
name|mask_buffer
operator|=
name|mask_buffer
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_mask_offset (GimpApplicator * applicator,gint mask_offset_x,gint mask_offset_y)
name|gimp_applicator_set_mask_offset
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|gint
name|mask_offset_x
parameter_list|,
name|gint
name|mask_offset_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|applicator
operator|->
name|mask_offset_x
operator|!=
name|mask_offset_x
operator|||
name|applicator
operator|->
name|mask_offset_y
operator|!=
name|mask_offset_y
condition|)
block|{
name|applicator
operator|->
name|mask_offset_x
operator|=
name|mask_offset_x
expr_stmt|;
name|applicator
operator|->
name|mask_offset_y
operator|=
name|mask_offset_y
expr_stmt|;
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|mask_offset_node
argument_list|,
literal|"x"
argument_list|,
operator|(
name|gdouble
operator|)
name|mask_offset_x
argument_list|,
literal|"y"
argument_list|,
operator|(
name|gdouble
operator|)
name|mask_offset_y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_apply_buffer (GimpApplicator * applicator,GeglBuffer * apply_buffer)
name|gimp_applicator_set_apply_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglBuffer
modifier|*
name|apply_buffer
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|apply_buffer
operator|==
name|NULL
operator|||
name|GEGL_IS_BUFFER
argument_list|(
name|apply_buffer
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|apply_buffer
operator|==
name|applicator
operator|->
name|apply_buffer
condition|)
return|return;
if|if
condition|(
name|apply_buffer
condition|)
block|{
if|if
condition|(
operator|!
name|applicator
operator|->
name|apply_src_node
condition|)
block|{
name|applicator
operator|->
name|apply_src_node
operator|=
name|gegl_node_new_child
argument_list|(
name|applicator
operator|->
name|node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|apply_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|apply_src_node
argument_list|,
literal|"buffer"
argument_list|,
name|apply_buffer
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|applicator
operator|->
name|apply_buffer
condition|)
block|{
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|apply_src_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|apply_offset_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|applicator
operator|->
name|apply_buffer
condition|)
block|{
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|aux_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|apply_offset_node
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
name|applicator
operator|->
name|apply_buffer
operator|=
name|apply_buffer
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_apply_offset (GimpApplicator * applicator,gint apply_offset_x,gint apply_offset_y)
name|gimp_applicator_set_apply_offset
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|gint
name|apply_offset_x
parameter_list|,
name|gint
name|apply_offset_y
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|applicator
operator|->
name|apply_offset_x
operator|!=
name|apply_offset_x
operator|||
name|applicator
operator|->
name|apply_offset_y
operator|!=
name|apply_offset_y
condition|)
block|{
name|applicator
operator|->
name|apply_offset_x
operator|=
name|apply_offset_x
expr_stmt|;
name|applicator
operator|->
name|apply_offset_y
operator|=
name|apply_offset_y
expr_stmt|;
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|apply_offset_node
argument_list|,
literal|"x"
argument_list|,
operator|(
name|gdouble
operator|)
name|apply_offset_x
argument_list|,
literal|"y"
argument_list|,
operator|(
name|gdouble
operator|)
name|apply_offset_y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_opacity (GimpApplicator * applicator,gdouble opacity)
name|gimp_applicator_set_opacity
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|gdouble
name|opacity
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|applicator
operator|->
name|opacity
operator|!=
name|opacity
condition|)
block|{
name|applicator
operator|->
name|opacity
operator|=
name|opacity
expr_stmt|;
name|gimp_gegl_mode_node_set_opacity
argument_list|(
name|applicator
operator|->
name|mode_node
argument_list|,
name|opacity
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_mode (GimpApplicator * applicator,GimpLayerMode paint_mode)
name|gimp_applicator_set_mode
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GimpLayerMode
name|paint_mode
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|applicator
operator|->
name|paint_mode
operator|!=
name|paint_mode
condition|)
block|{
name|applicator
operator|->
name|paint_mode
operator|=
name|paint_mode
expr_stmt|;
name|gimp_gegl_mode_node_set_mode
argument_list|(
name|applicator
operator|->
name|mode_node
argument_list|,
name|paint_mode
argument_list|,
name|applicator
operator|->
name|linear
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_set_affect (GimpApplicator * applicator,GimpComponentMask affect)
name|gimp_applicator_set_affect
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GimpComponentMask
name|affect
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|applicator
operator|->
name|affect
operator|!=
name|affect
condition|)
block|{
name|applicator
operator|->
name|affect
operator|=
name|affect
expr_stmt|;
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|affect_node
argument_list|,
literal|"mask"
argument_list|,
name|affect
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function_decl
name|gboolean
name|gegl_buffer_list_valid_rectangles
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|,
name|GeglRectangle
modifier|*
modifier|*
name|rectangles
parameter_list|,
name|gint
modifier|*
name|n_rectangles
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|gimp_applicator_set_preview (GimpApplicator * applicator,gboolean enable,const GeglRectangle * rect)
name|gimp_applicator_set_preview
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|gboolean
name|enable
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|applicator
operator|->
name|preview_cache_node
condition|)
return|return;
if|if
condition|(
name|applicator
operator|->
name|preview_enabled
operator|!=
name|enable
operator|||
name|applicator
operator|->
name|preview_rect
operator|.
name|x
operator|!=
name|rect
operator|->
name|x
operator|||
name|applicator
operator|->
name|preview_rect
operator|.
name|y
operator|!=
name|rect
operator|->
name|y
operator|||
name|applicator
operator|->
name|preview_rect
operator|.
name|width
operator|!=
name|rect
operator|->
name|width
operator|||
name|applicator
operator|->
name|preview_rect
operator|.
name|height
operator|!=
name|rect
operator|->
name|height
condition|)
block|{
if|if
condition|(
name|enable
condition|)
block|{
if|if
condition|(
operator|!
name|applicator
operator|->
name|preview_enabled
condition|)
block|{
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|preview_crop_node
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:compose-crop"
argument_list|,
literal|"x"
argument_list|,
name|rect
operator|->
name|x
argument_list|,
literal|"y"
argument_list|,
name|rect
operator|->
name|y
argument_list|,
literal|"width"
argument_list|,
name|rect
operator|->
name|width
argument_list|,
literal|"height"
argument_list|,
name|rect
operator|->
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_connect_to
argument_list|(
name|applicator
operator|->
name|input_node
argument_list|,
literal|"output"
argument_list|,
name|applicator
operator|->
name|preview_crop_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|preview_crop_node
argument_list|,
literal|"x"
argument_list|,
name|rect
operator|->
name|x
argument_list|,
literal|"y"
argument_list|,
name|rect
operator|->
name|y
argument_list|,
literal|"width"
argument_list|,
name|rect
operator|->
name|width
argument_list|,
literal|"height"
argument_list|,
name|rect
operator|->
name|height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|applicator
operator|->
name|preview_enabled
condition|)
block|{
name|GeglBuffer
modifier|*
name|cache
decl_stmt|;
name|gegl_node_disconnect
argument_list|(
name|applicator
operator|->
name|preview_crop_node
argument_list|,
literal|"aux"
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|preview_crop_node
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:nop"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  when disabling the preview, preserve the cached result            *  by processing it into the output cache, which only            *  involves the mode and affect nodes.            */
name|gegl_node_get
argument_list|(
name|applicator
operator|->
name|preview_cache_node
argument_list|,
literal|"cache"
argument_list|,
operator|&
name|cache
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
condition|)
block|{
name|GeglRectangle
modifier|*
name|rectangles
decl_stmt|;
name|gint
name|n_rectangles
decl_stmt|;
if|if
condition|(
name|gegl_buffer_list_valid_rectangles
argument_list|(
name|cache
argument_list|,
operator|&
name|rectangles
argument_list|,
operator|&
name|n_rectangles
argument_list|)
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_rectangles
condition|;
name|i
operator|++
control|)
name|gegl_node_blit
argument_list|(
name|applicator
operator|->
name|output_cache_node
argument_list|,
literal|1.0
argument_list|,
operator|&
name|rectangles
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GEGL_BLIT_DEFAULT
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rectangles
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|cache
argument_list|)
expr_stmt|;
block|}
block|}
name|applicator
operator|->
name|preview_enabled
operator|=
name|enable
expr_stmt|;
name|applicator
operator|->
name|preview_rect
operator|=
operator|*
name|rect
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_applicator_blit (GimpApplicator * applicator,const GeglRectangle * rect)
name|gimp_applicator_blit
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|)
expr_stmt|;
name|gegl_node_blit
argument_list|(
name|applicator
operator|->
name|dest_node
argument_list|,
literal|1.0
argument_list|,
name|rect
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GEGL_BLIT_DEFAULT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_applicator_dup_apply_buffer (GimpApplicator * applicator,const GeglRectangle * rect)
name|gimp_applicator_dup_apply_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|rect
parameter_list|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|shifted
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rect
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gegl_buffer_new
argument_list|(
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|rect
operator|->
name|width
argument_list|,
name|rect
operator|->
name|height
argument_list|)
argument_list|,
name|babl_format
argument_list|(
literal|"RGBA float"
argument_list|)
argument_list|)
expr_stmt|;
name|shifted
operator|=
name|g_object_new
argument_list|(
name|GEGL_TYPE_BUFFER
argument_list|,
literal|"source"
argument_list|,
name|buffer
argument_list|,
literal|"shift-x"
argument_list|,
operator|-
name|rect
operator|->
name|x
argument_list|,
literal|"shift-y"
argument_list|,
operator|-
name|rect
operator|->
name|y
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|applicator
operator|->
name|dup_apply_buffer_node
argument_list|,
literal|"buffer"
argument_list|,
name|shifted
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shifted
argument_list|)
expr_stmt|;
return|return
name|buffer
return|;
block|}
end_function

begin_function
name|GeglBuffer
modifier|*
DECL|function|gimp_applicator_get_cache_buffer (GimpApplicator * applicator,GeglRectangle ** rectangles,gint * n_rectangles)
name|gimp_applicator_get_cache_buffer
parameter_list|(
name|GimpApplicator
modifier|*
name|applicator
parameter_list|,
name|GeglRectangle
modifier|*
modifier|*
name|rectangles
parameter_list|,
name|gint
modifier|*
name|n_rectangles
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_APPLICATOR
argument_list|(
name|applicator
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|rectangles
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n_rectangles
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|applicator
operator|->
name|output_cache_node
condition|)
block|{
name|GeglBuffer
modifier|*
name|cache
decl_stmt|;
name|gegl_node_get
argument_list|(
name|applicator
operator|->
name|output_cache_node
argument_list|,
literal|"cache"
argument_list|,
operator|&
name|cache
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
condition|)
block|{
if|if
condition|(
name|gegl_buffer_list_valid_rectangles
argument_list|(
name|cache
argument_list|,
name|rectangles
argument_list|,
name|n_rectangles
argument_list|)
condition|)
return|return
name|cache
return|;
name|g_object_unref
argument_list|(
name|cache
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

