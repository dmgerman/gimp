begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CLONE_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CLONE_OPTIONS_H__
define|#
directive|define
name|__GIMP_CLONE_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CLONE_OPTIONS
define|#
directive|define
name|GIMP_TYPE_CLONE_OPTIONS
value|(gimp_clone_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_CLONE_OPTIONS (obj)
define|#
directive|define
name|GIMP_CLONE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CLONE_OPTIONS, GimpCloneOptions))
end_define

begin_define
DECL|macro|GIMP_CLONE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_CLONE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CLONE_OPTIONS, GimpCloneOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_CLONE_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_CLONE_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CLONE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_CLONE_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CLONE_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CLONE_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_CLONE_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CLONE_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CLONE_OPTIONS, GimpCloneOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpCloneOptions
typedef|typedef
name|struct
name|_GimpCloneOptions
name|GimpCloneOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCloneOptionsClass
typedef|typedef
name|struct
name|_GimpPaintOptionsClass
name|GimpCloneOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCloneOptions
struct|struct
name|_GimpCloneOptions
block|{
DECL|member|paint_options
name|GimpPaintOptions
name|paint_options
decl_stmt|;
DECL|member|clone_type
name|GimpCloneType
name|clone_type
decl_stmt|;
DECL|member|align_mode
name|GimpCloneAlignMode
name|align_mode
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_clone_options_get_type
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
comment|/*  __GIMP_CLONE_OPTIONS_H__  */
end_comment

end_unit

