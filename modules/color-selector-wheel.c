begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP Wheel ColorSelector  * Copyright (C) 2008  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmodule/gimpmodule.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorwheel.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_define
DECL|macro|COLORSEL_TYPE_WHEEL
define|#
directive|define
name|COLORSEL_TYPE_WHEEL
value|(colorsel_wheel_get_type ())
end_define

begin_define
DECL|macro|COLORSEL_WHEEL (obj)
define|#
directive|define
name|COLORSEL_WHEEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), COLORSEL_TYPE_WHEEL, ColorselWheel))
end_define

begin_define
DECL|macro|COLORSEL_WHEEL_CLASS (klass)
define|#
directive|define
name|COLORSEL_WHEEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), COLORSEL_TYPE_WHEEL, ColorselWheelClass))
end_define

begin_define
DECL|macro|COLORSEL_IS_WHEEL (obj)
define|#
directive|define
name|COLORSEL_IS_WHEEL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), COLORSEL_TYPE_WHEEL))
end_define

begin_define
DECL|macro|COLORSEL_IS_WHEEL_CLASS (klass)
define|#
directive|define
name|COLORSEL_IS_WHEEL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), COLORSEL_TYPE_WHEEL))
end_define

begin_typedef
DECL|typedef|ColorselWheel
typedef|typedef
name|struct
name|_ColorselWheel
name|ColorselWheel
typedef|;
end_typedef

begin_typedef
DECL|typedef|ColorselWheelClass
typedef|typedef
name|struct
name|_ColorselWheelClass
name|ColorselWheelClass
typedef|;
end_typedef

begin_struct
DECL|struct|_ColorselWheel
struct|struct
name|_ColorselWheel
block|{
DECL|member|parent_instance
name|GimpColorSelector
name|parent_instance
decl_stmt|;
DECL|member|hsv
name|GtkWidget
modifier|*
name|hsv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ColorselWheelClass
struct|struct
name|_ColorselWheelClass
block|{
DECL|member|parent_class
name|GimpColorSelectorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|GType
name|colorsel_wheel_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_wheel_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_wheel_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorsel_wheel_changed
parameter_list|(
name|GimpColorWheel
modifier|*
name|hsv
parameter_list|,
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|colorsel_wheel_info
specifier|static
specifier|const
name|GimpModuleInfo
name|colorsel_wheel_info
init|=
block|{
name|GIMP_MODULE_ABI_VERSION
block|,
name|N_
argument_list|(
literal|"HSV color wheel"
argument_list|)
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"v1.0"
block|,
literal|"(c) 2008, released under the GPL"
block|,
literal|"08 Aug 2008"
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_DYNAMIC_TYPE (ColorselWheel,colorsel_wheel,GIMP_TYPE_COLOR_SELECTOR)
name|G_DEFINE_DYNAMIC_TYPE
argument_list|(
argument|ColorselWheel
argument_list|,
argument|colorsel_wheel
argument_list|,
argument|GIMP_TYPE_COLOR_SELECTOR
argument_list|)
end_macro

begin_function
name|G_MODULE_EXPORT
specifier|const
name|GimpModuleInfo
modifier|*
name|gimp_module_query
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
return|return
operator|&
name|colorsel_wheel_info
return|;
block|}
end_function

begin_function
name|G_MODULE_EXPORT
name|gboolean
DECL|function|gimp_module_register (GTypeModule * module)
name|gimp_module_register
parameter_list|(
name|GTypeModule
modifier|*
name|module
parameter_list|)
block|{
name|color_wheel_register_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
name|colorsel_wheel_register_type
argument_list|(
name|module
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_wheel_class_init (ColorselWheelClass * klass)
name|colorsel_wheel_class_init
parameter_list|(
name|ColorselWheelClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
init|=
name|GIMP_COLOR_SELECTOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|selector_class
operator|->
name|name
operator|=
name|_
argument_list|(
literal|"Wheel"
argument_list|)
expr_stmt|;
name|selector_class
operator|->
name|help_id
operator|=
literal|"gimp-colorselector-triangle"
expr_stmt|;
name|selector_class
operator|->
name|icon_name
operator|=
name|GIMP_STOCK_COLOR_TRIANGLE
expr_stmt|;
name|selector_class
operator|->
name|set_color
operator|=
name|colorsel_wheel_set_color
expr_stmt|;
name|selector_class
operator|->
name|set_config
operator|=
name|colorsel_wheel_set_config
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_wheel_class_finalize (ColorselWheelClass * klass)
name|colorsel_wheel_class_finalize
parameter_list|(
name|ColorselWheelClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_wheel_init (ColorselWheel * wheel)
name|colorsel_wheel_init
parameter_list|(
name|ColorselWheel
modifier|*
name|wheel
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|wheel
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|wheel
operator|->
name|hsv
operator|=
name|gimp_color_wheel_new
argument_list|()
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|wheel
operator|->
name|hsv
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|wheel
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|wheel
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|wheel
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|wheel
operator|->
name|hsv
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorsel_wheel_changed
argument_list|)
argument_list|,
name|wheel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_wheel_set_color (GimpColorSelector * selector,const GimpRGB * rgb,const GimpHSV * hsv)
name|colorsel_wheel_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|ColorselWheel
modifier|*
name|wheel
init|=
name|COLORSEL_WHEEL
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|gimp_color_wheel_set_color
argument_list|(
name|GIMP_COLOR_WHEEL
argument_list|(
name|wheel
operator|->
name|hsv
argument_list|)
argument_list|,
name|hsv
operator|->
name|h
argument_list|,
name|hsv
operator|->
name|s
argument_list|,
name|hsv
operator|->
name|v
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_wheel_set_config (GimpColorSelector * selector,GimpColorConfig * config)
name|colorsel_wheel_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
name|ColorselWheel
modifier|*
name|wheel
init|=
name|COLORSEL_WHEEL
argument_list|(
name|selector
argument_list|)
decl_stmt|;
if|if
condition|(
name|wheel
operator|->
name|hsv
condition|)
name|gimp_color_wheel_set_color_config
argument_list|(
name|GIMP_COLOR_WHEEL
argument_list|(
name|wheel
operator|->
name|hsv
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorsel_wheel_changed (GimpColorWheel * hsv,GimpColorSelector * selector)
name|colorsel_wheel_changed
parameter_list|(
name|GimpColorWheel
modifier|*
name|hsv
parameter_list|,
name|GimpColorSelector
modifier|*
name|selector
parameter_list|)
block|{
name|gimp_color_wheel_get_color
argument_list|(
name|hsv
argument_list|,
operator|&
name|selector
operator|->
name|hsv
operator|.
name|h
argument_list|,
operator|&
name|selector
operator|->
name|hsv
operator|.
name|s
argument_list|,
operator|&
name|selector
operator|->
name|hsv
operator|.
name|v
argument_list|)
expr_stmt|;
name|gimp_hsv_to_rgb
argument_list|(
operator|&
name|selector
operator|->
name|hsv
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|)
expr_stmt|;
name|gimp_color_selector_color_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

