begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONVOLVE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONVOLVE_H__
define|#
directive|define
name|__GIMP_CONVOLVE_H__
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
DECL|macro|GIMP_TYPE_CONVOLVE
define|#
directive|define
name|GIMP_TYPE_CONVOLVE
value|(gimp_convolve_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONVOLVE (obj)
define|#
directive|define
name|GIMP_CONVOLVE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONVOLVE, GimpConvolve))
end_define

begin_define
DECL|macro|GIMP_CONVOLVE_CLASS (klass)
define|#
directive|define
name|GIMP_CONVOLVE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONVOLVE, GimpConvolveClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONVOLVE (obj)
define|#
directive|define
name|GIMP_IS_CONVOLVE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONVOLVE))
end_define

begin_define
DECL|macro|GIMP_IS_CONVOLVE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONVOLVE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONVOLVE))
end_define

begin_define
DECL|macro|GIMP_CONVOLVE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONVOLVE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONVOLVE, GimpConvolveClass))
end_define

begin_typedef
DECL|typedef|GimpConvolve
typedef|typedef
name|struct
name|_GimpConvolve
name|GimpConvolve
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpConvolveClass
typedef|typedef
name|struct
name|_GimpConvolveClass
name|GimpConvolveClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpConvolve
struct|struct
name|_GimpConvolve
block|{
DECL|member|parent_instance
name|GimpPaintCore
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpConvolveClass
struct|struct
name|_GimpConvolveClass
block|{
DECL|member|parent_class
name|GimpPaintCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpConvolveOptions
typedef|typedef
name|struct
name|_GimpConvolveOptions
name|GimpConvolveOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpConvolveOptions
struct|struct
name|_GimpConvolveOptions
block|{
DECL|member|paint_options
name|GimpPaintOptions
name|paint_options
decl_stmt|;
DECL|member|type
name|GimpConvolveType
name|type
decl_stmt|;
DECL|member|type_d
name|GimpConvolveType
name|type_d
decl_stmt|;
DECL|member|type_w
name|GtkWidget
modifier|*
name|type_w
index|[
literal|2
index|]
decl_stmt|;
DECL|member|rate
name|gdouble
name|rate
decl_stmt|;
DECL|member|rate_d
name|gdouble
name|rate_d
decl_stmt|;
DECL|member|rate_w
name|GtkObject
modifier|*
name|rate_w
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_convolve_register
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
name|gimp_convolve_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpConvolveOptions
modifier|*
name|gimp_convolve_options_new
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
comment|/*  __GIMP_CONVOLVE_H__  */
end_comment

end_unit

