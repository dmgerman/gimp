begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis, and others  *  * gimp-gradients.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gradients.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|FG_BG_RGB_KEY
define|#
directive|define
name|FG_BG_RGB_KEY
value|"gimp-gradient-fg-bg-rgb"
end_define

begin_define
DECL|macro|FG_BG_HSV_CCW_KEY
define|#
directive|define
name|FG_BG_HSV_CCW_KEY
value|"gimp-gradient-fg-bg-hsv-ccw"
end_define

begin_define
DECL|macro|FG_BG_HSV_CW_KEY
define|#
directive|define
name|FG_BG_HSV_CW_KEY
value|"gimp-gradient-fg-bg-hsv-cw"
end_define

begin_define
DECL|macro|FG_TRANSPARENT_KEY
define|#
directive|define
name|FG_TRANSPARENT_KEY
value|"gimp-gradient-fg-transparent"
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpGradient
modifier|*
name|gimp_gradients_add_gradient
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_gradients_init (Gimp * gimp)
name|gimp_gradients_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|gradient
operator|=
name|gimp_gradients_add_gradient
argument_list|(
name|gimp
argument_list|,
name|_
argument_list|(
literal|"FG to BG (RGB)"
argument_list|)
argument_list|,
name|FG_BG_RGB_KEY
argument_list|)
expr_stmt|;
name|gimp_context_set_gradient
argument_list|(
name|gimp
operator|->
name|user_context
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|gradient
operator|=
name|gimp_gradients_add_gradient
argument_list|(
name|gimp
argument_list|,
name|_
argument_list|(
literal|"FG to BG (HSV counter-clockwise)"
argument_list|)
argument_list|,
name|FG_BG_HSV_CCW_KEY
argument_list|)
expr_stmt|;
name|gradient
operator|->
name|segments
operator|->
name|color
operator|=
name|GIMP_GRADIENT_SEGMENT_HSV_CCW
expr_stmt|;
name|gradient
operator|=
name|gimp_gradients_add_gradient
argument_list|(
name|gimp
argument_list|,
name|_
argument_list|(
literal|"FG to BG (HSV clockwise hue)"
argument_list|)
argument_list|,
name|FG_BG_HSV_CW_KEY
argument_list|)
expr_stmt|;
name|gradient
operator|->
name|segments
operator|->
name|color
operator|=
name|GIMP_GRADIENT_SEGMENT_HSV_CW
expr_stmt|;
name|gradient
operator|=
name|gimp_gradients_add_gradient
argument_list|(
name|gimp
argument_list|,
name|_
argument_list|(
literal|"FG to Transparent"
argument_list|)
argument_list|,
name|FG_TRANSPARENT_KEY
argument_list|)
expr_stmt|;
name|gradient
operator|->
name|segments
operator|->
name|right_color_type
operator|=
name|GIMP_GRADIENT_COLOR_FOREGROUND_TRANSPARENT
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpGradient
modifier|*
DECL|function|gimp_gradients_add_gradient (Gimp * gimp,const gchar * name,const gchar * id)
name|gimp_gradients_add_gradient
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|id
parameter_list|)
block|{
name|GimpGradient
modifier|*
name|gradient
init|=
name|GIMP_GRADIENT
argument_list|(
name|gimp_gradient_new
argument_list|(
name|name
argument_list|)
argument_list|)
decl_stmt|;
name|gimp_data_make_internal
argument_list|(
name|GIMP_DATA
argument_list|(
name|gradient
argument_list|)
argument_list|,
name|id
argument_list|)
expr_stmt|;
name|gradient
operator|->
name|segments
operator|->
name|left_color_type
operator|=
name|GIMP_GRADIENT_COLOR_FOREGROUND
expr_stmt|;
name|gradient
operator|->
name|segments
operator|->
name|right_color_type
operator|=
name|GIMP_GRADIENT_COLOR_BACKGROUND
expr_stmt|;
name|gimp_container_add
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|gradient_factory
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gradient
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|id
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
return|return
name|gradient
return|;
block|}
end_function

end_unit

