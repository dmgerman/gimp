begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PROPGUI_TYPES_H__
end_ifndef

begin_define
DECL|macro|__PROPGUI_TYPES_H__
define|#
directive|define
name|__PROPGUI_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_comment
comment|/*  enums, move to propgui-enums.h if we get more  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2be3b9050103
block|{
DECL|enumerator|GIMP_CONTROLLER_TYPE_LINE
name|GIMP_CONTROLLER_TYPE_LINE
block|,
DECL|enumerator|GIMP_CONTROLLER_TYPE_SLIDER_LINE
name|GIMP_CONTROLLER_TYPE_SLIDER_LINE
DECL|typedef|GimpControllerType
block|}
name|GimpControllerType
typedef|;
end_typedef

begin_comment
comment|/*  structs  */
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2be3b9050208
block|{
DECL|member|value
name|gdouble
name|value
decl_stmt|;
DECL|member|min
name|gdouble
name|min
decl_stmt|;
DECL|member|max
name|gdouble
name|max
decl_stmt|;
DECL|typedef|GimpControllerSlider
block|}
name|GimpControllerSlider
typedef|;
end_typedef

begin_comment
comment|/*  function types  */
end_comment

begin_typedef
DECL|typedef|GimpControllerLineCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpControllerLineCallback
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpControllerSliderLineCallback
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpControllerSliderLineCallback
function_decl|)
parameter_list|(
name|gpointer
name|data
parameter_list|,
name|GeglRectangle
modifier|*
name|area
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
specifier|const
name|GimpControllerSlider
modifier|*
name|sliders
parameter_list|,
name|gint
name|n_sliders
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpCreatePickerFunc
typedef|typedef
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|GimpCreatePickerFunc
function_decl|)
parameter_list|(
name|gpointer
name|creator
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
name|gboolean
name|pick_abyss
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpCreateControllerFunc
typedef|typedef
name|GCallback
function_decl|(
modifier|*
name|GimpCreateControllerFunc
function_decl|)
parameter_list|(
name|gpointer
name|creator
parameter_list|,
name|GimpControllerType
name|controller_type
parameter_list|,
name|GCallback
name|callback
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gpointer
modifier|*
name|set_func_data
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PROPGUI_TYPES_H__ */
end_comment

end_unit

