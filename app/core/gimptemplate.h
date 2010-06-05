begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimptemplate.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TEMPLATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TEMPLATE_H__
define|#
directive|define
name|__GIMP_TEMPLATE_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TEMPLATE_PARAM_COPY_FIRST
define|#
directive|define
name|GIMP_TEMPLATE_PARAM_COPY_FIRST
value|(1<< (8 + G_PARAM_USER_SHIFT))
end_define

begin_comment
comment|/*  The default image aspect ratio is the golden mean. We use  *  two adjacent fibonacci numbers for the unstable series and  *  some less odd values for the stable version.  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_UNSTABLE
end_ifdef

begin_define
DECL|macro|GIMP_DEFAULT_IMAGE_WIDTH
define|#
directive|define
name|GIMP_DEFAULT_IMAGE_WIDTH
value|610
end_define

begin_define
DECL|macro|GIMP_DEFAULT_IMAGE_HEIGHT
define|#
directive|define
name|GIMP_DEFAULT_IMAGE_HEIGHT
value|377
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|GIMP_DEFAULT_IMAGE_WIDTH
define|#
directive|define
name|GIMP_DEFAULT_IMAGE_WIDTH
value|640
end_define

begin_define
DECL|macro|GIMP_DEFAULT_IMAGE_HEIGHT
define|#
directive|define
name|GIMP_DEFAULT_IMAGE_HEIGHT
value|400
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|GIMP_TYPE_TEMPLATE
define|#
directive|define
name|GIMP_TYPE_TEMPLATE
value|(gimp_template_get_type ())
end_define

begin_define
DECL|macro|GIMP_TEMPLATE (obj)
define|#
directive|define
name|GIMP_TEMPLATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TEMPLATE, GimpTemplate))
end_define

begin_define
DECL|macro|GIMP_TEMPLATE_CLASS (klass)
define|#
directive|define
name|GIMP_TEMPLATE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TEMPLATE, GimpTemplateClass))
end_define

begin_define
DECL|macro|GIMP_IS_TEMPLATE (obj)
define|#
directive|define
name|GIMP_IS_TEMPLATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TEMPLATE))
end_define

begin_define
DECL|macro|GIMP_IS_TEMPLATE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TEMPLATE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TEMPLATE))
end_define

begin_define
DECL|macro|GIMP_TEMPLATE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TEMPLATE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TEMPLATE, GimpTemplateClass))
end_define

begin_typedef
DECL|typedef|GimpTemplateClass
typedef|typedef
name|struct
name|_GimpTemplateClass
name|GimpTemplateClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTemplate
struct|struct
name|_GimpTemplate
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|xresolution
name|gdouble
name|xresolution
decl_stmt|;
DECL|member|yresolution
name|gdouble
name|yresolution
decl_stmt|;
DECL|member|resolution_unit
name|GimpUnit
name|resolution_unit
decl_stmt|;
DECL|member|image_type
name|GimpImageBaseType
name|image_type
decl_stmt|;
DECL|member|fill_type
name|GimpFillType
name|fill_type
decl_stmt|;
DECL|member|comment
name|gchar
modifier|*
name|comment
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|initial_size
name|guint64
name|initial_size
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTemplateClass
struct|struct
name|_GimpTemplateClass
block|{
DECL|member|parent_instance
name|GimpViewableClass
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_template_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpTemplate
modifier|*
name|gimp_template_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_template_set_from_image
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TEMPLATE__ */
end_comment

end_unit

