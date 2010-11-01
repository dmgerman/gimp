begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpspinscale.h  * Copyright (C) 2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SPIN_SCALE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SPIN_SCALE_H__
define|#
directive|define
name|__GIMP_SPIN_SCALE_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_SPIN_SCALE
define|#
directive|define
name|GIMP_TYPE_SPIN_SCALE
value|(gimp_spin_scale_get_type ())
end_define

begin_define
DECL|macro|GIMP_SPIN_SCALE (obj)
define|#
directive|define
name|GIMP_SPIN_SCALE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SPIN_SCALE, GimpSpinScale))
end_define

begin_define
DECL|macro|GIMP_SPIN_SCALE_CLASS (klass)
define|#
directive|define
name|GIMP_SPIN_SCALE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SPIN_SCALE, GimpSpinScaleClass))
end_define

begin_define
DECL|macro|GIMP_IS_SPIN_SCALE (obj)
define|#
directive|define
name|GIMP_IS_SPIN_SCALE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SPIN_SCALE))
end_define

begin_define
DECL|macro|GIMP_IS_SPIN_SCALE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SPIN_SCALE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SPIN_SCALE))
end_define

begin_define
DECL|macro|GIMP_SPIN_SCALE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SPIN_SCALE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SPIN_SCALE, GimpSpinScaleClass))
end_define

begin_typedef
DECL|typedef|GimpSpinScale
typedef|typedef
name|struct
name|_GimpSpinScale
name|GimpSpinScale
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSpinScaleClass
typedef|typedef
name|struct
name|_GimpSpinScaleClass
name|GimpSpinScaleClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSpinScale
struct|struct
name|_GimpSpinScale
block|{
DECL|member|parent_instance
name|GtkSpinButton
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSpinScaleClass
struct|struct
name|_GimpSpinScaleClass
block|{
DECL|member|parent_class
name|GtkSpinButtonClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_spin_scale_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_spin_scale_new
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
name|gint
name|digits
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SPIN_SCALE_H__  */
end_comment

end_unit

