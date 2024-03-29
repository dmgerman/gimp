begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationnormal.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_NORMAL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_NORMAL_H__
define|#
directive|define
name|__GIMP_OPERATION_NORMAL_H__
end_define

begin_include
include|#
directive|include
file|"gimpoperationlayermode.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_NORMAL
define|#
directive|define
name|GIMP_TYPE_OPERATION_NORMAL
value|(gimp_operation_normal_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_NORMAL (obj)
define|#
directive|define
name|GIMP_OPERATION_NORMAL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_NORMAL, GimpOperationNormal))
end_define

begin_define
DECL|macro|GIMP_OPERATION_NORMAL_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_NORMAL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_NORMAL, GimpOperationNormalClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_NORMAL (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_NORMAL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_NORMAL))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_NORMAL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_NORMAL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_NORMAL))
end_define

begin_define
DECL|macro|GIMP_OPERATION_NORMAL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_NORMAL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_NORMAL, GimpOperationNormalClass))
end_define

begin_typedef
DECL|typedef|GimpOperationNormal
typedef|typedef
name|struct
name|_GimpOperationNormal
name|GimpOperationNormal
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationNormalClass
typedef|typedef
name|struct
name|_GimpOperationNormalClass
name|GimpOperationNormalClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationNormal
struct|struct
name|_GimpOperationNormal
block|{
DECL|member|parent_instance
name|GimpOperationLayerMode
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationNormalClass
struct|struct
name|_GimpOperationNormalClass
block|{
DECL|member|parent_class
name|GimpOperationLayerModeClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_normal_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|gboolean
name|gimp_operation_normal_process
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|,
name|void
modifier|*
name|in
parameter_list|,
name|void
modifier|*
name|layer
parameter_list|,
name|void
modifier|*
name|mask
parameter_list|,
name|void
modifier|*
name|out
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
name|COMPILE_SSE2_INTRINISICS
end_if

begin_function_decl
name|gboolean
name|gimp_operation_normal_process_sse2
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|,
name|void
modifier|*
name|in
parameter_list|,
name|void
modifier|*
name|layer
parameter_list|,
name|void
modifier|*
name|mask
parameter_list|,
name|void
modifier|*
name|out
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* COMPILE_SSE2_INTRINISICS */
end_comment

begin_if
if|#
directive|if
name|COMPILE_SSE4_1_INTRINISICS
end_if

begin_function_decl
name|gboolean
name|gimp_operation_normal_process_sse4
parameter_list|(
name|GeglOperation
modifier|*
name|op
parameter_list|,
name|void
modifier|*
name|in
parameter_list|,
name|void
modifier|*
name|layer
parameter_list|,
name|void
modifier|*
name|mask
parameter_list|,
name|void
modifier|*
name|out
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* COMPILE_SSE4_1_INTRINISICS */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OPERATION_NORMAL_H__ */
end_comment

end_unit

