begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-babl.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojectable.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-actions.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-filter.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-profile.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayxfer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_profile_free
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_color_config_notify
parameter_list|(
name|GimpColorConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_profile_init (GimpDisplayShell * shell)
name|gimp_display_shell_profile_init
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|color_config
decl_stmt|;
name|color_config
operator|=
name|GIMP_CORE_CONFIG
argument_list|(
name|shell
operator|->
name|display
operator|->
name|config
argument_list|)
operator|->
name|color_management
expr_stmt|;
name|shell
operator|->
name|color_config
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|color_config
argument_list|)
argument_list|)
expr_stmt|;
comment|/* use after so we are called after the profile cache is invalidated    * in gimp_widget_get_color_transform()    */
name|g_signal_connect_after
argument_list|(
name|shell
operator|->
name|color_config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_color_config_notify
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_profile_finalize (GimpDisplayShell * shell)
name|gimp_display_shell_profile_finalize
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
name|shell
operator|->
name|color_config
condition|)
block|{
name|g_object_unref
argument_list|(
name|shell
operator|->
name|color_config
argument_list|)
expr_stmt|;
name|shell
operator|->
name|color_config
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_display_shell_profile_free
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_profile_update (GimpDisplayShell * shell)
name|gimp_display_shell_profile_update
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpColorProfile
modifier|*
name|src_profile
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|src_format
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|dest_format
decl_stmt|;
name|gimp_display_shell_profile_free
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"gimp_display_shell_profile_update\n"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
condition|)
return|return;
name|src_profile
operator|=
name|gimp_color_managed_get_color_profile
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|src_profile
condition|)
return|return;
name|src_format
operator|=
name|gimp_projectable_get_format
argument_list|(
name|GIMP_PROJECTABLE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_display_shell_has_filter
argument_list|(
name|shell
argument_list|)
operator|||
operator|!
name|gimp_display_shell_profile_can_convert_to_u8
argument_list|(
name|shell
argument_list|)
condition|)
block|{
name|dest_format
operator|=
name|shell
operator|->
name|filter_format
expr_stmt|;
block|}
else|else
block|{
name|dest_format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
block|}
name|g_printerr
argument_list|(
literal|"src_profile: %s\n"
literal|"src_format:  %s\n"
literal|"dest_format: %s\n"
argument_list|,
name|gimp_color_profile_get_label
argument_list|(
name|src_profile
argument_list|)
argument_list|,
name|babl_get_name
argument_list|(
name|src_format
argument_list|)
argument_list|,
name|babl_get_name
argument_list|(
name|dest_format
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_transform
operator|=
name|gimp_widget_get_color_transform
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
argument_list|,
name|gimp_display_shell_get_color_config
argument_list|(
name|shell
argument_list|)
argument_list|,
name|src_profile
argument_list|,
name|src_format
argument_list|,
name|dest_format
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|profile_transform
condition|)
block|{
name|gint
name|w
init|=
name|GIMP_DISPLAY_RENDER_BUF_WIDTH
operator|*
name|GIMP_DISPLAY_RENDER_MAX_SCALE
decl_stmt|;
name|gint
name|h
init|=
name|GIMP_DISPLAY_RENDER_BUF_HEIGHT
operator|*
name|GIMP_DISPLAY_RENDER_MAX_SCALE
decl_stmt|;
name|shell
operator|->
name|profile_data
operator|=
name|gegl_malloc
argument_list|(
name|w
operator|*
name|h
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|src_format
argument_list|)
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_stride
operator|=
name|w
operator|*
name|babl_format_get_bytes_per_pixel
argument_list|(
name|src_format
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_buffer
operator|=
name|gegl_buffer_linear_new_from_data
argument_list|(
name|shell
operator|->
name|profile_data
argument_list|,
name|src_format
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gegl_free
argument_list|,
name|shell
operator|->
name|profile_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_profile_can_convert_to_u8 (GimpDisplayShell * shell)
name|gimp_display_shell_profile_can_convert_to_u8
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
decl_stmt|;
if|if
condition|(
name|image
condition|)
block|{
switch|switch
condition|(
name|gimp_image_get_component_type
argument_list|(
name|image
argument_list|)
condition|)
block|{
case|case
name|GIMP_COMPONENT_TYPE_U8
case|:
if|#
directive|if
literal|0
comment|/* would like to convert directly for these too, but it            * produces inferior results, see bug 750874            */
block|case GIMP_COMPONENT_TYPE_U16:         case GIMP_COMPONENT_TYPE_U32:
endif|#
directive|endif
return|return
name|TRUE
return|;
default|default:
break|break;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_profile_free (GimpDisplayShell * shell)
name|gimp_display_shell_profile_free
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
name|shell
operator|->
name|profile_transform
condition|)
block|{
name|g_object_unref
argument_list|(
name|shell
operator|->
name|profile_transform
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_transform
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|shell
operator|->
name|profile_buffer
condition|)
block|{
name|g_object_unref
argument_list|(
name|shell
operator|->
name|profile_buffer
argument_list|)
expr_stmt|;
name|shell
operator|->
name|profile_buffer
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|profile_data
operator|=
name|NULL
expr_stmt|;
name|shell
operator|->
name|profile_stride
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_color_config_notify (GimpColorConfig * config,const GParamSpec * pspec,GimpDisplayShell * shell)
name|gimp_display_shell_color_config_notify
parameter_list|(
name|GimpColorConfig
modifier|*
name|config
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"mode"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"display-rendering-intent"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"display-use-black-point-compensation"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"simulation-rendering-intent"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"simulation-use-black-point-compensation"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"simulation-gamut-check"
argument_list|)
condition|)
block|{
name|gboolean
name|managed
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|softproof
init|=
name|FALSE
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|action
init|=
name|NULL
decl_stmt|;
DECL|macro|SET_SENSITIVE (action,sensitive)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|sensitive
parameter_list|)
define|\
value|gimp_display_shell_set_action_sensitive (shell, action, sensitive);
DECL|macro|SET_ACTIVE (action,active)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_display_shell_set_action_active (shell, action, active);
switch|switch
condition|(
name|gimp_color_config_get_mode
argument_list|(
name|config
argument_list|)
condition|)
block|{
case|case
name|GIMP_COLOR_MANAGEMENT_OFF
case|:
break|break;
case|case
name|GIMP_COLOR_MANAGEMENT_DISPLAY
case|:
name|managed
operator|=
name|TRUE
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_MANAGEMENT_SOFTPROOF
case|:
name|managed
operator|=
name|TRUE
expr_stmt|;
name|softproof
operator|=
name|TRUE
expr_stmt|;
break|break;
block|}
name|SET_ACTIVE
argument_list|(
literal|"view-color-management-enable"
argument_list|,
name|managed
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-color-management-softproof"
argument_list|,
name|softproof
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_color_config_get_display_intent
argument_list|(
name|config
argument_list|)
condition|)
block|{
case|case
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
case|:
name|action
operator|=
literal|"view-display-intent-perceptual"
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
case|:
name|action
operator|=
literal|"view-display-intent-relative-colorimetric"
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_RENDERING_INTENT_SATURATION
case|:
name|action
operator|=
literal|"view-display-intent-saturation"
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC
case|:
name|action
operator|=
literal|"view-display-intent-absolute-colorimetric"
expr_stmt|;
break|break;
block|}
name|SET_SENSITIVE
argument_list|(
literal|"view-display-intent-perceptual"
argument_list|,
name|managed
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-display-intent-relative-colorimetric"
argument_list|,
name|managed
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-display-intent-saturation"
argument_list|,
name|managed
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-display-intent-absolute-colorimetric"
argument_list|,
name|managed
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|action
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-display-black-point-compensation"
argument_list|,
name|managed
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-display-black-point-compensation"
argument_list|,
name|gimp_color_config_get_display_bpc
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_color_config_get_simulation_intent
argument_list|(
name|config
argument_list|)
condition|)
block|{
case|case
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
case|:
name|action
operator|=
literal|"view-softproof-intent-perceptual"
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
case|:
name|action
operator|=
literal|"view-softproof-intent-relative-colorimetric"
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_RENDERING_INTENT_SATURATION
case|:
name|action
operator|=
literal|"view-softproof-intent-saturation"
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC
case|:
name|action
operator|=
literal|"view-softproof-intent-absolute-colorimetric"
expr_stmt|;
break|break;
block|}
name|SET_SENSITIVE
argument_list|(
literal|"view-softproof-intent-perceptual"
argument_list|,
name|softproof
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-softproof-intent-relative-colorimetric"
argument_list|,
name|softproof
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-softproof-intent-saturation"
argument_list|,
name|softproof
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-softproof-intent-absolute-colorimetric"
argument_list|,
name|softproof
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
name|action
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-softproof-black-point-compensation"
argument_list|,
name|softproof
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-softproof-black-point-compensation"
argument_list|,
name|gimp_color_config_get_simulation_bpc
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-softproof-gamut-check"
argument_list|,
name|softproof
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-softproof-gamut-check"
argument_list|,
name|gimp_color_config_get_simulation_gamut_check
argument_list|(
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_color_managed_profile_changed
argument_list|(
name|GIMP_COLOR_MANAGED
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

