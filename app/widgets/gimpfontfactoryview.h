begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfontfactoryview.h  * Copyright (C) 2018 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FONT_FACTORY_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FONT_FACTORY_VIEW_H__
define|#
directive|define
name|__GIMP_FONT_FACTORY_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpdatafactoryview.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FONT_FACTORY_VIEW
define|#
directive|define
name|GIMP_TYPE_FONT_FACTORY_VIEW
value|(gimp_font_factory_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_FONT_FACTORY_VIEW (obj)
define|#
directive|define
name|GIMP_FONT_FACTORY_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FONT_FACTORY_VIEW, GimpFontFactoryView))
end_define

begin_define
DECL|macro|GIMP_FONT_FACTORY_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_FONT_FACTORY_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FONT_FACTORY_VIEW, GimpFontFactoryViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_FONT_FACTORY_VIEW (obj)
define|#
directive|define
name|GIMP_IS_FONT_FACTORY_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FONT_FACTORY_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_FONT_FACTORY_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FONT_FACTORY_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FONT_FACTORY_VIEW))
end_define

begin_define
DECL|macro|GIMP_FONT_FACTORY_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FONT_FACTORY_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FONT_FACTORY_VIEW, GimpFontFactoryViewClass))
end_define

begin_typedef
DECL|typedef|GimpFontFactoryViewClass
typedef|typedef
name|struct
name|_GimpFontFactoryViewClass
name|GimpFontFactoryViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFontFactoryView
struct|struct
name|_GimpFontFactoryView
block|{
DECL|member|parent_instance
name|GimpDataFactoryView
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFontFactoryViewClass
struct|struct
name|_GimpFontFactoryViewClass
block|{
DECL|member|parent_class
name|GimpDataFactoryViewClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_font_factory_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_font_factory_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_FONT_FACTORY_VIEW_H__  */
end_comment

end_unit

