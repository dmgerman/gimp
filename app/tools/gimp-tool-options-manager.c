begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-tool-options-manager.c  * Copyright (C) 2018 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-tool-options-manager.h"
end_include

begin_typedef
DECL|typedef|GimpToolOptionsManager
typedef|typedef
name|struct
name|_GimpToolOptionsManager
name|GimpToolOptionsManager
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolOptionsManager
struct|struct
name|_GimpToolOptionsManager
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|global_paint_options
name|GimpPaintOptions
modifier|*
name|global_paint_options
decl_stmt|;
DECL|member|global_props
name|GimpContextPropMask
name|global_props
decl_stmt|;
DECL|member|active_tool
name|GimpToolInfo
modifier|*
name|active_tool
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|manager_quark
specifier|static
name|GQuark
name|manager_quark
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpContextPropMask
name|tool_options_manager_get_global_props
parameter_list|(
name|GimpCoreConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_manager_global_notify
parameter_list|(
name|GimpCoreConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolOptionsManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_manager_paint_options_notify
parameter_list|(
name|GimpPaintOptions
modifier|*
name|src
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpPaintOptions
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_manager_copy_paint_props
parameter_list|(
name|GimpPaintOptions
modifier|*
name|src
parameter_list|,
name|GimpPaintOptions
modifier|*
name|dest
parameter_list|,
name|GimpContextPropMask
name|prop_mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_options_manager_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|user_context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpToolOptionsManager
modifier|*
name|manager
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_tool_options_manager_init (Gimp * gimp)
name|gimp_tool_options_manager_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpToolOptionsManager
modifier|*
name|manager
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|GimpCoreConfig
modifier|*
name|config
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager_quark
operator|==
literal|0
argument_list|)
expr_stmt|;
name|manager_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-tool-options-manager"
argument_list|)
expr_stmt|;
name|config
operator|=
name|gimp
operator|->
name|config
expr_stmt|;
name|manager
operator|=
name|g_slice_new0
argument_list|(
name|GimpToolOptionsManager
argument_list|)
expr_stmt|;
name|manager
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|manager
operator|->
name|global_paint_options
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_PAINT_OPTIONS
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"name"
argument_list|,
literal|"tool-options-manager-global-paint-options"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|manager
operator|->
name|global_props
operator|=
name|tool_options_manager_get_global_props
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|g_object_set_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|manager_quark
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_tool_info_iter
argument_list|(
name|gimp
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|list
operator|->
name|data
decl_stmt|;
comment|/*  the global props that are actually used by the tool are        *  always shared with the user context by undefining them...        */
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|manager
operator|->
name|global_props
operator|&
name|tool_info
operator|->
name|context_props
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  ...and setting the user context as parent        */
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
comment|/*  make sure paint tools also share their brush, dynamics,        *  gradient properties if the resp. context properties are        *  global        */
if|if
condition|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|g_signal_connect
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_paint_options_notify
argument_list|)
argument_list|,
name|manager
operator|->
name|global_paint_options
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|manager
operator|->
name|global_paint_options
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_paint_options_notify
argument_list|)
argument_list|,
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|tool_options_manager_copy_paint_props
argument_list|(
name|manager
operator|->
name|global_paint_options
argument_list|,
name|GIMP_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context_props
operator|&
name|manager
operator|->
name|global_props
argument_list|)
expr_stmt|;
block|}
block|}
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::global-brush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_global_notify
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::global-dynamics"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_global_notify
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::global-pattern"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_global_notify
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::global-palette"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_global_notify
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::global-gradient"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_global_notify
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::global-font"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_global_notify
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|user_context
argument_list|,
literal|"tool-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_options_manager_tool_changed
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|tool_options_manager_tool_changed
argument_list|(
name|user_context
argument_list|,
name|gimp_context_get_tool
argument_list|(
name|user_context
argument_list|)
argument_list|,
name|manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_options_manager_exit (Gimp * gimp)
name|gimp_tool_options_manager_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpToolOptionsManager
modifier|*
name|manager
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|manager
operator|=
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|manager_quark
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|manager
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|user_context
argument_list|,
name|tool_options_manager_tool_changed
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
name|tool_options_manager_global_notify
argument_list|,
name|manager
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_tool_info_iter
argument_list|(
name|gimp
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|,
name|tool_options_manager_paint_options_notify
argument_list|,
name|manager
operator|->
name|global_paint_options
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|manager
operator|->
name|global_paint_options
argument_list|,
name|tool_options_manager_paint_options_notify
argument_list|,
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
block|}
block|}
name|g_clear_object
argument_list|(
operator|&
name|manager
operator|->
name|global_paint_options
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpToolOptionsManager
argument_list|,
name|manager
argument_list|)
expr_stmt|;
name|g_object_set_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|manager_quark
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpContextPropMask
DECL|function|tool_options_manager_get_global_props (GimpCoreConfig * config)
name|tool_options_manager_get_global_props
parameter_list|(
name|GimpCoreConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpContextPropMask
name|global_props
init|=
literal|0
decl_stmt|;
comment|/*  FG and BG are always shared between all tools  */
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_FOREGROUND
expr_stmt|;
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_BACKGROUND
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_brush
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_BRUSH
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_dynamics
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_DYNAMICS
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_pattern
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_PATTERN
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_palette
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_PALETTE
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_gradient
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_GRADIENT
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_font
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PROP_MASK_FONT
expr_stmt|;
return|return
name|global_props
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_manager_global_notify (GimpCoreConfig * config,const GParamSpec * pspec,GimpToolOptionsManager * manager)
name|tool_options_manager_global_notify
parameter_list|(
name|GimpCoreConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpToolOptionsManager
modifier|*
name|manager
parameter_list|)
block|{
name|GimpContextPropMask
name|global_props
decl_stmt|;
name|GimpContextPropMask
name|enabled_global_props
decl_stmt|;
name|GimpContextPropMask
name|disabled_global_props
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|global_props
operator|=
name|tool_options_manager_get_global_props
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|enabled_global_props
operator|=
name|global_props
operator|&
operator|~
name|manager
operator|->
name|global_props
expr_stmt|;
name|disabled_global_props
operator|=
name|manager
operator|->
name|global_props
operator|&
operator|~
name|global_props
expr_stmt|;
comment|/*  copy the newly enabled global props to all tool options, and    *  disconnect the newly disabled ones from the user context    */
for|for
control|(
name|list
operator|=
name|gimp_get_tool_info_iter
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|list
operator|->
name|data
decl_stmt|;
comment|/*  don't change the active tool, it is always fully connected        *  to the user_context anway because we set its        *  defined/undefined context props in tool_changed()        */
if|if
condition|(
name|tool_info
operator|==
name|manager
operator|->
name|active_tool
condition|)
continue|continue;
comment|/*  defining the newly disabled ones disconnects them from the        *  parent user context        */
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context_props
operator|&
name|disabled_global_props
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  undefining the newly enabled ones copies the value from the        *  parent user context        */
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context_props
operator|&
name|enabled_global_props
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
condition|)
name|tool_options_manager_copy_paint_props
argument_list|(
name|manager
operator|->
name|global_paint_options
argument_list|,
name|GIMP_PAINT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context_props
operator|&
name|enabled_global_props
argument_list|)
expr_stmt|;
block|}
name|manager
operator|->
name|global_props
operator|=
name|global_props
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|brush_props
specifier|static
specifier|const
name|gchar
modifier|*
name|brush_props
index|[]
init|=
block|{
literal|"brush-size"
block|,
literal|"brush-angle"
block|,
literal|"brush-aspect-ratio"
block|,
literal|"brush-spacing"
block|,
literal|"brush-hardness"
block|,
literal|"brush-force"
block|,
literal|"brush-link-size"
block|,
literal|"brush-link-angle"
block|,
literal|"brush-link-aspect-ratio"
block|,
literal|"brush-link-spacing"
block|,
literal|"brush-link-hardness"
block|,
literal|"brush-lock-to-view"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dynamics_props
specifier|static
specifier|const
name|gchar
modifier|*
name|dynamics_props
index|[]
init|=
block|{
literal|"dynamics-expanded"
block|,
literal|"fade-reverse"
block|,
literal|"fade-length"
block|,
literal|"fade-unit"
block|,
literal|"fade-repeat"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gradient_props
specifier|static
specifier|const
name|gchar
modifier|*
name|gradient_props
index|[]
init|=
block|{
literal|"gradient-reverse"
block|,
literal|"gradient-blend-color-space"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|static
specifier|const
name|gint
name|max_n_props
init|=
operator|(
name|G_N_ELEMENTS
argument_list|(
name|brush_props
argument_list|)
operator|+
name|G_N_ELEMENTS
argument_list|(
name|dynamics_props
argument_list|)
operator|+
name|G_N_ELEMENTS
argument_list|(
name|gradient_props
argument_list|)
operator|)
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|tool_options_manager_paint_options_notify (GimpPaintOptions * src,const GParamSpec * pspec,GimpPaintOptions * dest)
name|tool_options_manager_paint_options_notify
parameter_list|(
name|GimpPaintOptions
modifier|*
name|src
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpPaintOptions
modifier|*
name|dest
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP_CONTEXT
argument_list|(
name|src
argument_list|)
operator|->
name|gimp
decl_stmt|;
name|GimpCoreConfig
modifier|*
name|config
init|=
name|gimp
operator|->
name|config
decl_stmt|;
name|GimpToolOptionsManager
modifier|*
name|manager
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|gboolean
name|active
init|=
name|FALSE
decl_stmt|;
name|GValue
name|value
init|=
name|G_VALUE_INIT
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|manager
operator|=
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|manager_quark
argument_list|)
expr_stmt|;
comment|/*  one of the options is the global one, the other is the tool's,    *  get the tool_info from the tool's options    */
if|if
condition|(
name|manager
operator|->
name|global_paint_options
operator|==
name|src
condition|)
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|dest
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|src
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|==
name|manager
operator|->
name|active_tool
condition|)
name|active
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|(
name|active
operator|||
name|config
operator|->
name|global_brush
operator|)
operator|&&
name|tool_info
operator|->
name|context_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_BRUSH
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|brush_props
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
name|brush_props
index|[
name|i
index|]
argument_list|)
condition|)
goto|goto
name|copy_value
goto|;
block|}
if|if
condition|(
operator|(
name|active
operator|||
name|config
operator|->
name|global_dynamics
operator|)
operator|&&
name|tool_info
operator|->
name|context_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_DYNAMICS
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|dynamics_props
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
name|dynamics_props
index|[
name|i
index|]
argument_list|)
condition|)
goto|goto
name|copy_value
goto|;
block|}
if|if
condition|(
operator|(
name|active
operator|||
name|config
operator|->
name|global_gradient
operator|)
operator|&&
name|tool_info
operator|->
name|context_props
operator|&
name|GIMP_CONTEXT_PROP_MASK_GRADIENT
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|gradient_props
argument_list|)
condition|;
name|i
operator|++
control|)
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
name|gradient_props
index|[
name|i
index|]
argument_list|)
condition|)
goto|goto
name|copy_value
goto|;
block|}
return|return;
name|copy_value
label|:
name|g_value_init
argument_list|(
operator|&
name|value
argument_list|,
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|G_OBJECT
argument_list|(
name|src
argument_list|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|dest
argument_list|,
name|tool_options_manager_paint_options_notify
argument_list|,
name|src
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
name|pspec
operator|->
name|name
argument_list|,
operator|&
name|value
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dest
argument_list|,
name|tool_options_manager_paint_options_notify
argument_list|,
name|src
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
operator|&
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_manager_copy_paint_props (GimpPaintOptions * src,GimpPaintOptions * dest,GimpContextPropMask prop_mask)
name|tool_options_manager_copy_paint_props
parameter_list|(
name|GimpPaintOptions
modifier|*
name|src
parameter_list|,
name|GimpPaintOptions
modifier|*
name|dest
parameter_list|,
name|GimpContextPropMask
name|prop_mask
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|names
index|[
name|max_n_props
index|]
decl_stmt|;
name|GValue
name|values
index|[
name|max_n_props
index|]
decl_stmt|;
name|gint
name|n_props
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|prop_mask
operator|&
name|GIMP_CONTEXT_PROP_MASK_BRUSH
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|brush_props
argument_list|)
condition|;
name|i
operator|++
control|)
name|names
index|[
name|n_props
operator|++
index|]
operator|=
name|brush_props
index|[
name|i
index|]
expr_stmt|;
block|}
if|if
condition|(
name|prop_mask
operator|&
name|GIMP_CONTEXT_PROP_MASK_DYNAMICS
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|dynamics_props
argument_list|)
condition|;
name|i
operator|++
control|)
name|names
index|[
name|n_props
operator|++
index|]
operator|=
name|dynamics_props
index|[
name|i
index|]
expr_stmt|;
block|}
if|if
condition|(
name|prop_mask
operator|&
name|GIMP_CONTEXT_PROP_MASK_GRADIENT
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|gradient_props
argument_list|)
condition|;
name|i
operator|++
control|)
name|names
index|[
name|n_props
operator|++
index|]
operator|=
name|gradient_props
index|[
name|i
index|]
expr_stmt|;
block|}
if|if
condition|(
name|n_props
operator|>
literal|0
condition|)
block|{
name|g_object_getv
argument_list|(
name|G_OBJECT
argument_list|(
name|src
argument_list|)
argument_list|,
name|n_props
argument_list|,
name|names
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|dest
argument_list|,
name|tool_options_manager_paint_options_notify
argument_list|,
name|src
argument_list|)
expr_stmt|;
name|g_object_setv
argument_list|(
name|G_OBJECT
argument_list|(
name|dest
argument_list|)
argument_list|,
name|n_props
argument_list|,
name|names
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|dest
argument_list|,
name|tool_options_manager_paint_options_notify
argument_list|,
name|src
argument_list|)
expr_stmt|;
while|while
condition|(
name|n_props
operator|--
condition|)
name|g_value_unset
argument_list|(
operator|&
name|values
index|[
name|n_props
index|]
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_options_manager_tool_changed (GimpContext * user_context,GimpToolInfo * tool_info,GimpToolOptionsManager * manager)
name|tool_options_manager_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|user_context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpToolOptionsManager
modifier|*
name|manager
parameter_list|)
block|{
if|if
condition|(
name|tool_info
operator|==
name|manager
operator|->
name|active_tool
condition|)
return|return;
comment|/*  FIXME: gimp_busy HACK    *  the tool manager will stop the emission, so simply return    */
if|if
condition|(
name|user_context
operator|->
name|gimp
operator|->
name|busy
condition|)
return|return;
comment|/*  note that in this function we only deal with non-global    *  properties, so we never have to copy from or to the global paint    *  options    */
if|if
condition|(
name|manager
operator|->
name|active_tool
condition|)
block|{
name|GimpToolInfo
modifier|*
name|active
init|=
name|manager
operator|->
name|active_tool
decl_stmt|;
comment|/*  disconnect the old active tool from all context properties        *  it uses, but are not currently global        */
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|active
operator|->
name|tool_options
argument_list|)
argument_list|,
name|active
operator|->
name|context_props
operator|&
operator|~
name|manager
operator|->
name|global_props
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|manager
operator|->
name|active_tool
operator|=
name|tool_info
expr_stmt|;
if|if
condition|(
name|manager
operator|->
name|active_tool
condition|)
block|{
name|GimpToolInfo
modifier|*
name|active
init|=
name|manager
operator|->
name|active_tool
decl_stmt|;
comment|/*  copy the new tool's context properties that are not        *  currently global to the user context, so they get used by        *  everything        */
name|gimp_context_copy_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|active
operator|->
name|tool_options
argument_list|)
argument_list|,
name|gimp_get_user_context
argument_list|(
name|manager
operator|->
name|gimp
argument_list|)
argument_list|,
name|active
operator|->
name|context_props
operator|&
operator|~
name|manager
operator|->
name|global_props
argument_list|)
expr_stmt|;
comment|/*  then, undefine these properties so the tool syncs with the        *  user context automatically        */
name|gimp_context_define_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|active
operator|->
name|tool_options
argument_list|)
argument_list|,
name|active
operator|->
name|context_props
operator|&
operator|~
name|manager
operator|->
name|global_props
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

