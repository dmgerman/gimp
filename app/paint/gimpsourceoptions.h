begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SOURCE_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SOURCE_OPTIONS_H__
define|#
directive|define
name|__GIMP_SOURCE_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SOURCE_OPTIONS
define|#
directive|define
name|GIMP_TYPE_SOURCE_OPTIONS
value|(gimp_source_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_SOURCE_OPTIONS (obj)
define|#
directive|define
name|GIMP_SOURCE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SOURCE_OPTIONS, GimpSourceOptions))
end_define

begin_define
DECL|macro|GIMP_SOURCE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_SOURCE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SOURCE_OPTIONS, GimpSourceOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_SOURCE_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_SOURCE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SOURCE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_SOURCE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SOURCE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SOURCE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_SOURCE_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SOURCE_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SOURCE_OPTIONS, GimpSourceOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpSourceOptionsClass
typedef|typedef
name|struct
name|_GimpSourceOptionsClass
name|GimpSourceOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSourceOptions
struct|struct
name|_GimpSourceOptions
block|{
DECL|member|parent_instance
name|GimpPaintOptions
name|parent_instance
decl_stmt|;
DECL|member|align_mode
name|GimpSourceAlignMode
name|align_mode
decl_stmt|;
DECL|member|sample_merged
name|gboolean
name|sample_merged
decl_stmt|;
DECL|member|use_source
name|gboolean
name|use_source
decl_stmt|;
comment|/* not a property */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSourceOptionsClass
struct|struct
name|_GimpSourceOptionsClass
block|{
DECL|member|parent_class
name|GimpPaintOptionsClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_source_options_get_type
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
comment|/*  __GIMP_SOURCE_OPTIONS_H__  */
end_comment

end_unit

