begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGuide  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GUIDE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GUIDE_H__
define|#
directive|define
name|__GIMP_GUIDE_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_GUIDE_POSITION_UNDEFINED
define|#
directive|define
name|GIMP_GUIDE_POSITION_UNDEFINED
value|G_MININT
end_define

begin_define
DECL|macro|GIMP_TYPE_GUIDE
define|#
directive|define
name|GIMP_TYPE_GUIDE
value|(gimp_guide_get_type ())
end_define

begin_define
DECL|macro|GIMP_GUIDE (obj)
define|#
directive|define
name|GIMP_GUIDE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_GUIDE, GimpGuide))
end_define

begin_define
DECL|macro|GIMP_GUIDE_CLASS (klass)
define|#
directive|define
name|GIMP_GUIDE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GUIDE, GimpGuideClass))
end_define

begin_define
DECL|macro|GIMP_IS_GUIDE (obj)
define|#
directive|define
name|GIMP_IS_GUIDE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_GUIDE))
end_define

begin_define
DECL|macro|GIMP_IS_GUIDE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GUIDE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GUIDE))
end_define

begin_define
DECL|macro|GIMP_GUIDE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_GUIDE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_GUIDE, GimpGuideClass))
end_define

begin_typedef
DECL|typedef|GimpGuidePrivate
typedef|typedef
name|struct
name|_GimpGuidePrivate
name|GimpGuidePrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpGuideClass
typedef|typedef
name|struct
name|_GimpGuideClass
name|GimpGuideClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGuide
struct|struct
name|_GimpGuide
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpGuidePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpGuideClass
struct|struct
name|_GimpGuideClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|removed
name|void
function_decl|(
modifier|*
name|removed
function_decl|)
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_guide_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpGuide
modifier|*
name|gimp_guide_new
parameter_list|(
name|GimpOrientationType
name|orientation
parameter_list|,
name|guint32
name|guide_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGuide
modifier|*
name|gimp_guide_custom_new
parameter_list|(
name|GimpOrientationType
name|orientation
parameter_list|,
name|guint32
name|guide_ID
parameter_list|,
name|GimpGuideStyle
name|guide_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint32
name|gimp_guide_get_ID
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpOrientationType
name|gimp_guide_get_orientation
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_guide_set_orientation
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|GimpOrientationType
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_guide_get_position
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_guide_set_position
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|gint
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_guide_removed
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpGuideStyle
name|gimp_guide_get_style
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_guide_is_custom
parameter_list|(
name|GimpGuide
modifier|*
name|guide
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GUIDE_H__ */
end_comment

end_unit

