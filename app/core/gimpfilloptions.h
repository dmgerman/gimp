begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpfilloptions.h  * Copyright (C) 2003 Simon Budig  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FILL_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FILL_OPTIONS_H__
define|#
directive|define
name|__GIMP_FILL_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FILL_OPTIONS
define|#
directive|define
name|GIMP_TYPE_FILL_OPTIONS
value|(gimp_fill_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_FILL_OPTIONS (obj)
define|#
directive|define
name|GIMP_FILL_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FILL_OPTIONS, GimpFillOptions))
end_define

begin_define
DECL|macro|GIMP_FILL_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_FILL_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FILL_OPTIONS, GimpFillOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_FILL_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_FILL_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FILL_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_FILL_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FILL_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FILL_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_FILL_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FILL_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FILL_OPTIONS, GimpFillOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpFillOptionsClass
typedef|typedef
name|struct
name|_GimpFillOptionsClass
name|GimpFillOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFillOptions
struct|struct
name|_GimpFillOptions
block|{
DECL|member|parent_instance
name|GimpContext
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFillOptionsClass
struct|struct
name|_GimpFillOptionsClass
block|{
DECL|member|parent_class
name|GimpContextClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_fill_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpFillOptions
modifier|*
name|gimp_fill_options_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpFillStyle
name|gimp_fill_options_get_style
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_fill_options_get_antialias
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_FILL_OPTIONS_H__ */
end_comment

end_unit

