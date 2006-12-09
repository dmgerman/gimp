begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdatafactoryview.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DATA_FACTORY_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DATA_FACTORY_VIEW_H__
define|#
directive|define
name|__GIMP_DATA_FACTORY_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontainereditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DATA_FACTORY_VIEW
define|#
directive|define
name|GIMP_TYPE_DATA_FACTORY_VIEW
value|(gimp_data_factory_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_DATA_FACTORY_VIEW (obj)
define|#
directive|define
name|GIMP_DATA_FACTORY_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DATA_FACTORY_VIEW, GimpDataFactoryView))
end_define

begin_define
DECL|macro|GIMP_DATA_FACTORY_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_DATA_FACTORY_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DATA_FACTORY_VIEW, GimpDataFactoryViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_FACTORY_VIEW (obj)
define|#
directive|define
name|GIMP_IS_DATA_FACTORY_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DATA_FACTORY_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_FACTORY_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DATA_FACTORY_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DATA_FACTORY_VIEW))
end_define

begin_define
DECL|macro|GIMP_DATA_FACTORY_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DATA_FACTORY_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DATA_FACTORY_VIEW, GimpDataFactoryViewClass))
end_define

begin_typedef
DECL|typedef|GimpDataFactoryViewClass
typedef|typedef
name|struct
name|_GimpDataFactoryViewClass
name|GimpDataFactoryViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDataFactoryView
struct|struct
name|_GimpDataFactoryView
block|{
DECL|member|parent_instance
name|GimpContainerEditor
name|parent_instance
decl_stmt|;
DECL|member|factory
name|GimpDataFactory
modifier|*
name|factory
decl_stmt|;
DECL|member|edit_button
name|GtkWidget
modifier|*
name|edit_button
decl_stmt|;
DECL|member|new_button
name|GtkWidget
modifier|*
name|new_button
decl_stmt|;
DECL|member|duplicate_button
name|GtkWidget
modifier|*
name|duplicate_button
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
decl_stmt|;
DECL|member|refresh_button
name|GtkWidget
modifier|*
name|refresh_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDataFactoryViewClass
struct|struct
name|_GimpDataFactoryViewClass
block|{
DECL|member|parent_class
name|GimpContainerEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_data_factory_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_data_factory_view_new
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_group
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|gboolean
name|gimp_data_factory_view_construct
parameter_list|(
name|GimpDataFactoryView
modifier|*
name|factory_view
parameter_list|,
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
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|ui_identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|action_group
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DATA_FACTORY_VIEW_H__  */
end_comment

end_unit

