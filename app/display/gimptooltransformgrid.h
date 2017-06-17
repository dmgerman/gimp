begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptooltransformgrid.h  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_TRANSFORM_GRID_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_TRANSFORM_GRID_H__
define|#
directive|define
name|__GIMP_TOOL_TRANSFORM_GRID_H__
end_define

begin_include
include|#
directive|include
file|"gimptoolwidget.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bf5a03f0103
block|{
DECL|enumerator|GIMP_TRANSFORM_HANDLE_NONE
name|GIMP_TRANSFORM_HANDLE_NONE
block|,
DECL|enumerator|GIMP_TRANSFORM_HANDLE_NW_P
name|GIMP_TRANSFORM_HANDLE_NW_P
block|,
comment|/* north west perspective         */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_NE_P
name|GIMP_TRANSFORM_HANDLE_NE_P
block|,
comment|/* north east perspective         */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_SW_P
name|GIMP_TRANSFORM_HANDLE_SW_P
block|,
comment|/* south west perspective         */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_SE_P
name|GIMP_TRANSFORM_HANDLE_SE_P
block|,
comment|/* south east perspective         */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_NW
name|GIMP_TRANSFORM_HANDLE_NW
block|,
comment|/* north west                     */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_NE
name|GIMP_TRANSFORM_HANDLE_NE
block|,
comment|/* north east                     */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_SW
name|GIMP_TRANSFORM_HANDLE_SW
block|,
comment|/* south west                     */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_SE
name|GIMP_TRANSFORM_HANDLE_SE
block|,
comment|/* south east                     */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_N
name|GIMP_TRANSFORM_HANDLE_N
block|,
comment|/* north                          */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_S
name|GIMP_TRANSFORM_HANDLE_S
block|,
comment|/* south                          */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_E
name|GIMP_TRANSFORM_HANDLE_E
block|,
comment|/* east                           */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_W
name|GIMP_TRANSFORM_HANDLE_W
block|,
comment|/* west                           */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_CENTER
name|GIMP_TRANSFORM_HANDLE_CENTER
block|,
comment|/* center for moving              */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_PIVOT
name|GIMP_TRANSFORM_HANDLE_PIVOT
block|,
comment|/* pivot for rotation and scaling */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_N_S
name|GIMP_TRANSFORM_HANDLE_N_S
block|,
comment|/* north shearing                 */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_S_S
name|GIMP_TRANSFORM_HANDLE_S_S
block|,
comment|/* south shearing                 */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_E_S
name|GIMP_TRANSFORM_HANDLE_E_S
block|,
comment|/* east shearing                  */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_W_S
name|GIMP_TRANSFORM_HANDLE_W_S
block|,
comment|/* west shearing                  */
DECL|enumerator|GIMP_TRANSFORM_HANDLE_ROTATION
name|GIMP_TRANSFORM_HANDLE_ROTATION
block|,
comment|/* rotation                       */
DECL|enumerator|GIMP_N_TRANSFORM_HANDLES
name|GIMP_N_TRANSFORM_HANDLES
comment|/* keep this last so *handles[] is the right size */
DECL|typedef|GimpTransformHandle
block|}
name|GimpTransformHandle
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_TOOL_TRANSFORM_GRID
define|#
directive|define
name|GIMP_TYPE_TOOL_TRANSFORM_GRID
value|(gimp_tool_transform_grid_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_TRANSFORM_GRID (obj)
define|#
directive|define
name|GIMP_TOOL_TRANSFORM_GRID
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_TRANSFORM_GRID, GimpToolTransformGrid))
end_define

begin_define
DECL|macro|GIMP_TOOL_TRANSFORM_GRID_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_TRANSFORM_GRID_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_TRANSFORM_GRID, GimpToolTransformGridClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_TRANSFORM_GRID (obj)
define|#
directive|define
name|GIMP_IS_TOOL_TRANSFORM_GRID
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_TRANSFORM_GRID))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_TRANSFORM_GRID_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_TRANSFORM_GRID_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_TRANSFORM_GRID))
end_define

begin_define
DECL|macro|GIMP_TOOL_TRANSFORM_GRID_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_TRANSFORM_GRID_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_TRANSFORM_GRID, GimpToolTransformGridClass))
end_define

begin_typedef
DECL|typedef|GimpToolTransformGrid
typedef|typedef
name|struct
name|_GimpToolTransformGrid
name|GimpToolTransformGrid
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolTransformGridPrivate
typedef|typedef
name|struct
name|_GimpToolTransformGridPrivate
name|GimpToolTransformGridPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpToolTransformGridClass
typedef|typedef
name|struct
name|_GimpToolTransformGridClass
name|GimpToolTransformGridClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolTransformGrid
struct|struct
name|_GimpToolTransformGrid
block|{
DECL|member|parent_instance
name|GimpToolWidget
name|parent_instance
decl_stmt|;
DECL|member|private
name|GimpToolTransformGridPrivate
modifier|*
name|private
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolTransformGridClass
struct|struct
name|_GimpToolTransformGridClass
block|{
DECL|member|parent_class
name|GimpToolWidgetClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_transform_grid_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpToolWidget
modifier|*
name|gimp_tool_transform_grid_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|transform
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
name|GimpGuidesType
name|guide_type
parameter_list|,
name|gint
name|n_guides
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_TRANSFORM_GRID_H__ */
end_comment

end_unit

