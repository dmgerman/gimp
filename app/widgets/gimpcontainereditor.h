begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainereditor.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_EDITOR_H__
define|#
directive|define
name|__GIMP_CONTAINER_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkvbox.h>
end_include

begin_typedef
DECL|typedef|GimpContainerContextFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpContainerContextFunc
function_decl|)
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b57a36d0103
block|{
DECL|enumerator|GIMP_VIEW_TYPE_GRID
name|GIMP_VIEW_TYPE_GRID
block|,
DECL|enumerator|GIMP_VIEW_TYPE_LIST
name|GIMP_VIEW_TYPE_LIST
DECL|typedef|GimpViewType
block|}
name|GimpViewType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_EDITOR
define|#
directive|define
name|GIMP_TYPE_CONTAINER_EDITOR
value|(gimp_container_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_EDITOR (obj)
define|#
directive|define
name|GIMP_CONTAINER_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_EDITOR, GimpContainerEditor))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_CONTAINER_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CONTAINER_EDITOR, GimpContainerEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CONTAINER_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CONTAINER_EDITOR))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CONTAINER_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CONTAINER_EDITOR, GimpContainerEditorClass))
end_define

begin_typedef
DECL|typedef|GimpContainerEditorClass
typedef|typedef
name|struct
name|_GimpContainerEditorClass
name|GimpContainerEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerEditor
struct|struct
name|_GimpContainerEditor
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|context_func
name|GimpContainerContextFunc
name|context_func
decl_stmt|;
DECL|member|view
name|GimpContainerView
modifier|*
name|view
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpContainerEditorClass
struct|struct
name|_GimpContainerEditorClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
DECL|member|select_item
name|void
function_decl|(
modifier|*
name|select_item
function_decl|)
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|)
function_decl|;
DECL|member|activate_item
name|void
function_decl|(
modifier|*
name|activate_item
function_decl|)
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|)
function_decl|;
DECL|member|context_item
name|void
function_decl|(
modifier|*
name|context_item
function_decl|)
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_container_editor_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|gboolean
name|gimp_container_editor_construct
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewType
name|view_type
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|preview_size
parameter_list|,
name|gboolean
name|reorderable
parameter_list|,
name|gint
name|min_items_x
parameter_list|,
name|gint
name|min_items_y
parameter_list|,
name|GimpContainerContextFunc
name|context_func
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_EDITOR_H__  */
end_comment

end_unit

