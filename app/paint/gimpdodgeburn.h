begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DODGE_BURN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DODGE_BURN_H__
define|#
directive|define
name|__GIMP_DODGE_BURN_H__
end_define

begin_include
include|#
directive|include
file|"gimppaintcore.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DODGEBURN
define|#
directive|define
name|GIMP_TYPE_DODGEBURN
value|(gimp_dodgeburn_get_type ())
end_define

begin_define
DECL|macro|GIMP_DODGEBURN (obj)
define|#
directive|define
name|GIMP_DODGEBURN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DODGEBURN, GimpDodgeBurn))
end_define

begin_define
DECL|macro|GIMP_IS_DODGEBURN (obj)
define|#
directive|define
name|GIMP_IS_DODGEBURN
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DODGEBURN))
end_define

begin_define
DECL|macro|GIMP_DODGEBURN_CLASS (klass)
define|#
directive|define
name|GIMP_DODGEBURN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DODGEBURN, GimpDodgeBurnClass))
end_define

begin_define
DECL|macro|GIMP_IS_DODGEBURN_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DODGEBURN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DODGEBURN))
end_define

begin_typedef
DECL|typedef|GimpDodgeBurn
typedef|typedef
name|struct
name|_GimpDodgeBurn
name|GimpDodgeBurn
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDodgeBurnClass
typedef|typedef
name|struct
name|_GimpDodgeBurnClass
name|GimpDodgeBurnClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDodgeBurn
struct|struct
name|_GimpDodgeBurn
block|{
DECL|member|parent_instance
name|GimpPaintCore
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDodgeBurnClass
struct|struct
name|_GimpDodgeBurnClass
block|{
DECL|member|parent_class
name|GimpPaintCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpDodgeBurnOptions
typedef|typedef
name|struct
name|_GimpDodgeBurnOptions
name|GimpDodgeBurnOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDodgeBurnOptions
struct|struct
name|_GimpDodgeBurnOptions
block|{
DECL|member|paint_options
name|GimpPaintOptions
name|paint_options
decl_stmt|;
DECL|member|type
name|GimpDodgeBurnType
name|type
decl_stmt|;
DECL|member|type_d
name|GimpDodgeBurnType
name|type_d
decl_stmt|;
DECL|member|type_w
name|GtkWidget
modifier|*
name|type_w
decl_stmt|;
DECL|member|mode
name|GimpTransferMode
name|mode
decl_stmt|;
comment|/*highlights, midtones, shadows*/
DECL|member|mode_d
name|GimpTransferMode
name|mode_d
decl_stmt|;
DECL|member|mode_w
name|GtkWidget
modifier|*
name|mode_w
decl_stmt|;
DECL|member|exposure
name|gdouble
name|exposure
decl_stmt|;
DECL|member|exposure_d
name|gdouble
name|exposure_d
decl_stmt|;
DECL|member|exposure_w
name|GtkObject
modifier|*
name|exposure_w
decl_stmt|;
DECL|member|lut
name|GimpLut
modifier|*
name|lut
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_dodgeburn_register
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
name|gimp_dodgeburn_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDodgeBurnOptions
modifier|*
name|gimp_dodgeburn_options_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DODGEBURN_H__  */
end_comment

end_unit

