begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SMUDGE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SMUDGE_H__
define|#
directive|define
name|__GIMP_SMUDGE_H__
end_define

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushcore.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SMUDGE
define|#
directive|define
name|GIMP_TYPE_SMUDGE
value|(gimp_smudge_get_type ())
end_define

begin_define
DECL|macro|GIMP_SMUDGE (obj)
define|#
directive|define
name|GIMP_SMUDGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SMUDGE, GimpSmudge))
end_define

begin_define
DECL|macro|GIMP_SMUDGE_CLASS (klass)
define|#
directive|define
name|GIMP_SMUDGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SMUDGE, GimpSmudgeClass))
end_define

begin_define
DECL|macro|GIMP_IS_SMUDGE (obj)
define|#
directive|define
name|GIMP_IS_SMUDGE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SMUDGE))
end_define

begin_define
DECL|macro|GIMP_IS_SMUDGE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SMUDGE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SMUDGE))
end_define

begin_define
DECL|macro|GIMP_SMUDGE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SMUDGE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SMUDGE, GimpSmudgeClass))
end_define

begin_typedef
DECL|typedef|GimpSmudge
typedef|typedef
name|struct
name|_GimpSmudge
name|GimpSmudge
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSmudgeClass
typedef|typedef
name|struct
name|_GimpSmudgeClass
name|GimpSmudgeClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSmudge
struct|struct
name|_GimpSmudge
block|{
DECL|member|parent_instance
name|GimpBrushCore
name|parent_instance
decl_stmt|;
DECL|member|initialized
name|gboolean
name|initialized
decl_stmt|;
DECL|member|accumPR
name|PixelRegion
name|accumPR
decl_stmt|;
DECL|member|accum_data
name|guchar
modifier|*
name|accum_data
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSmudgeClass
struct|struct
name|_GimpSmudgeClass
block|{
DECL|member|parent_class
name|GimpBrushCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_smudge_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_smudge_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SMUDGE_H__  */
end_comment

end_unit

