begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpcolornotebook.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on color_notebook module  * Copyright (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_NOTEBOOK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_NOTEBOOK_H__
define|#
directive|define
name|__GIMP_COLOR_NOTEBOOK_H__
end_define

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpcolorselector.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_COLOR_NOTEBOOK
define|#
directive|define
name|GIMP_TYPE_COLOR_NOTEBOOK
value|(gimp_color_notebook_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_NOTEBOOK (obj)
define|#
directive|define
name|GIMP_COLOR_NOTEBOOK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_NOTEBOOK, GimpColorNotebook))
end_define

begin_define
DECL|macro|GIMP_COLOR_NOTEBOOK_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_NOTEBOOK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_NOTEBOOK, GimpColorNotebookClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_NOTEBOOK (obj)
define|#
directive|define
name|GIMP_IS_COLOR_NOTEBOOK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_NOTEBOOK))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_NOTEBOOK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_NOTEBOOK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_NOTEBOOK))
end_define

begin_define
DECL|macro|GIMP_COLOR_NOTEBOOK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_NOTEBOOK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_NOTEBOOK, GimpColorNotebookClass))
end_define

begin_typedef
DECL|typedef|GimpColorNotebookClass
typedef|typedef
name|struct
name|_GimpColorNotebookClass
name|GimpColorNotebookClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorNotebook
struct|struct
name|_GimpColorNotebook
block|{
DECL|member|parent_instance
name|GimpColorSelector
name|parent_instance
decl_stmt|;
DECL|member|notebook
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
DECL|member|selectors
name|GList
modifier|*
name|selectors
decl_stmt|;
DECL|member|cur_page
name|GimpColorSelector
modifier|*
name|cur_page
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorNotebookClass
struct|struct
name|_GimpColorNotebookClass
block|{
DECL|member|parent_class
name|GimpColorSelectorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_notebook_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_NOTEBOOK_H__ */
end_comment

end_unit

