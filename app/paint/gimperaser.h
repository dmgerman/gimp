begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ERASER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ERASER_H__
define|#
directive|define
name|__GIMP_ERASER_H__
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
DECL|macro|GIMP_TYPE_ERASER
define|#
directive|define
name|GIMP_TYPE_ERASER
value|(gimp_eraser_get_type ())
end_define

begin_define
DECL|macro|GIMP_ERASER (obj)
define|#
directive|define
name|GIMP_ERASER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ERASER, GimpEraser))
end_define

begin_define
DECL|macro|GIMP_ERASER_CLASS (klass)
define|#
directive|define
name|GIMP_ERASER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ERASER, GimpEraserClass))
end_define

begin_define
DECL|macro|GIMP_IS_ERASER (obj)
define|#
directive|define
name|GIMP_IS_ERASER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ERASER))
end_define

begin_define
DECL|macro|GIMP_IS_ERASER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ERASER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ERASER))
end_define

begin_define
DECL|macro|GIMP_ERASER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ERASER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ERASER, GimpEraserClass))
end_define

begin_typedef
DECL|typedef|GimpEraser
typedef|typedef
name|struct
name|_GimpEraser
name|GimpEraser
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEraserClass
typedef|typedef
name|struct
name|_GimpEraserClass
name|GimpEraserClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEraser
struct|struct
name|_GimpEraser
block|{
DECL|member|parent_instance
name|GimpPaintCore
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpEraserClass
struct|struct
name|_GimpEraserClass
block|{
DECL|member|parent_class
name|GimpPaintCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpEraserOptions
typedef|typedef
name|struct
name|_GimpEraserOptions
name|GimpEraserOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpEraserOptions
struct|struct
name|_GimpEraserOptions
block|{
DECL|member|paint_options
name|GimpPaintOptions
name|paint_options
decl_stmt|;
DECL|member|hard
name|gboolean
name|hard
decl_stmt|;
DECL|member|hard_d
name|gboolean
name|hard_d
decl_stmt|;
DECL|member|hard_w
name|GtkWidget
modifier|*
name|hard_w
decl_stmt|;
DECL|member|anti_erase
name|gboolean
name|anti_erase
decl_stmt|;
DECL|member|anti_erase_d
name|gboolean
name|anti_erase_d
decl_stmt|;
DECL|member|anti_erase_w
name|GtkWidget
modifier|*
name|anti_erase_w
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_eraser_register
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
name|gimp_eraser_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpEraserOptions
modifier|*
name|gimp_eraser_options_new
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
comment|/*  __GIMP_ERASER_H__  */
end_comment

end_unit

