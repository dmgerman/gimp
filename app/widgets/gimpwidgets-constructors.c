begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GIMP_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_paint_mode_menu_new (GCallback callback,gpointer data,gboolean with_behind_mode,GimpLayerModeEffects initial)
name|gimp_paint_mode_menu_new
parameter_list|(
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|gboolean
name|with_behind_mode
parameter_list|,
name|GimpLayerModeEffects
name|initial
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
if|if
condition|(
name|with_behind_mode
condition|)
block|{
name|menu
operator|=
name|gimp_int_option_menu_new
argument_list|(
name|FALSE
argument_list|,
name|callback
argument_list|,
name|data
argument_list|,
name|initial
argument_list|,
name|_
argument_list|(
literal|"Normal"
argument_list|)
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Dissolve"
argument_list|)
argument_list|,
name|GIMP_DISSOLVE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Behind"
argument_list|)
argument_list|,
name|GIMP_BEHIND_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color Erase"
argument_list|)
argument_list|,
name|GIMP_COLOR_ERASE_MODE
argument_list|,
name|NULL
argument_list|,
literal|"---"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Multiply"
argument_list|)
argument_list|,
name|GIMP_MULTIPLY_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Divide"
argument_list|)
argument_list|,
name|GIMP_DIVIDE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Screen"
argument_list|)
argument_list|,
name|GIMP_SCREEN_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Overlay"
argument_list|)
argument_list|,
name|GIMP_OVERLAY_MODE
argument_list|,
name|NULL
argument_list|,
literal|"---"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Dodge"
argument_list|)
argument_list|,
name|GIMP_DODGE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Burn"
argument_list|)
argument_list|,
name|GIMP_BURN_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Hard Light"
argument_list|)
argument_list|,
name|GIMP_HARDLIGHT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Soft Light"
argument_list|)
argument_list|,
name|GIMP_SOFTLIGHT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Grain Extract"
argument_list|)
argument_list|,
name|GIMP_GRAIN_EXTRACT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Grain Merge"
argument_list|)
argument_list|,
name|GIMP_GRAIN_MERGE_MODE
argument_list|,
name|NULL
argument_list|,
literal|"---"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Difference"
argument_list|)
argument_list|,
name|GIMP_DIFFERENCE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Addition"
argument_list|)
argument_list|,
name|GIMP_ADDITION_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Subtract"
argument_list|)
argument_list|,
name|GIMP_SUBTRACT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Darken Only"
argument_list|)
argument_list|,
name|GIMP_DARKEN_ONLY_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Lighten Only"
argument_list|)
argument_list|,
name|GIMP_LIGHTEN_ONLY_MODE
argument_list|,
name|NULL
argument_list|,
literal|"---"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Hue"
argument_list|)
argument_list|,
name|GIMP_HUE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Saturation"
argument_list|)
argument_list|,
name|GIMP_SATURATION_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
name|GIMP_COLOR_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Value"
argument_list|)
argument_list|,
name|GIMP_VALUE_MODE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|menu
operator|=
name|gimp_int_option_menu_new
argument_list|(
name|FALSE
argument_list|,
name|callback
argument_list|,
name|data
argument_list|,
name|initial
argument_list|,
name|_
argument_list|(
literal|"Normal"
argument_list|)
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Dissolve"
argument_list|)
argument_list|,
name|GIMP_DISSOLVE_MODE
argument_list|,
name|NULL
argument_list|,
literal|"---"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Multiply"
argument_list|)
argument_list|,
name|GIMP_MULTIPLY_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Divide"
argument_list|)
argument_list|,
name|GIMP_DIVIDE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Screen"
argument_list|)
argument_list|,
name|GIMP_SCREEN_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Overlay"
argument_list|)
argument_list|,
name|GIMP_OVERLAY_MODE
argument_list|,
name|NULL
argument_list|,
literal|"---"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Dodge"
argument_list|)
argument_list|,
name|GIMP_DODGE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Burn"
argument_list|)
argument_list|,
name|GIMP_BURN_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Hard Light"
argument_list|)
argument_list|,
name|GIMP_HARDLIGHT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Soft Light"
argument_list|)
argument_list|,
name|GIMP_SOFTLIGHT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Grain Extract"
argument_list|)
argument_list|,
name|GIMP_GRAIN_EXTRACT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Grain Merge"
argument_list|)
argument_list|,
name|GIMP_GRAIN_MERGE_MODE
argument_list|,
name|NULL
argument_list|,
literal|"---"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Difference"
argument_list|)
argument_list|,
name|GIMP_DIFFERENCE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Addition"
argument_list|)
argument_list|,
name|GIMP_ADDITION_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Subtract"
argument_list|)
argument_list|,
name|GIMP_SUBTRACT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Darken Only"
argument_list|)
argument_list|,
name|GIMP_DARKEN_ONLY_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Lighten Only"
argument_list|)
argument_list|,
name|GIMP_LIGHTEN_ONLY_MODE
argument_list|,
name|NULL
argument_list|,
literal|"---"
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Hue"
argument_list|)
argument_list|,
name|GIMP_HUE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Saturation"
argument_list|)
argument_list|,
name|GIMP_SATURATION_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
name|GIMP_COLOR_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Value"
argument_list|)
argument_list|,
name|GIMP_VALUE_MODE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
return|return
name|menu
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_paint_mode_menu_set_history (GtkOptionMenu * menu,GimpLayerModeEffects value)
name|gimp_paint_mode_menu_set_history
parameter_list|(
name|GtkOptionMenu
modifier|*
name|menu
parameter_list|,
name|GimpLayerModeEffects
name|value
parameter_list|)
block|{
name|gimp_int_option_menu_set_history
argument_list|(
name|menu
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

