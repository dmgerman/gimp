begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SET_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SET_H__
define|#
directive|define
name|__GIMP_SET_H__
end_define

begin_comment
comment|/* GimpSet - a (usually) typed set of objects with signals for adding  * and removing of stuff. If it is weak, destroyed objects get removed  * automatically. If it is not, it refs them so they won't be freed  * till they are removed. (Though they can be destroyed, of course).  *  * If GTK_TYPE_NONE is specified at gimpset creation time, no type  * checking is performed by gimp_set_add() and the  * gimp_set_{add,remove}_handler() functions should not be used.  It  * is also illegal to ask for a weak untyped gimpset. */
end_comment

begin_define
DECL|macro|GIMP_TYPE_SET
define|#
directive|define
name|GIMP_TYPE_SET
value|gimp_set_get_type ()
end_define

begin_define
DECL|macro|GIMP_SET (obj)
define|#
directive|define
name|GIMP_SET
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, GIMP_TYPE_SET, GimpSet)
end_define

begin_define
DECL|macro|GIMP_IS_SET (obj)
define|#
directive|define
name|GIMP_IS_SET
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, gimp_set_get_type())
end_define

begin_comment
comment|/* Signals:    add    remove    active_changed */
end_comment

begin_typedef
DECL|typedef|GimpSetHandlerId
typedef|typedef
name|guint
name|GimpSetHandlerId
typedef|;
end_typedef

begin_function_decl
name|GtkType
name|gimp_set_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSet
modifier|*
name|gimp_set_new
parameter_list|(
name|GtkType
name|type
parameter_list|,
name|gboolean
name|weak
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_set_type
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_set_add
parameter_list|(
name|GimpSet
modifier|*
name|gimpset
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_set_remove
parameter_list|(
name|GimpSet
modifier|*
name|gimpset
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_set_have
parameter_list|(
name|GimpSet
modifier|*
name|gimpset
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_foreach
parameter_list|(
name|GimpSet
modifier|*
name|gimpset
parameter_list|,
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_set_size
parameter_list|(
name|GimpSet
modifier|*
name|gimpset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_set_active
parameter_list|(
name|GimpSet
modifier|*
name|gimpset
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|gimp_set_get_active
parameter_list|(
name|GimpSet
modifier|*
name|gimpset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSetHandlerId
name|gimp_set_add_handler
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signame
parameter_list|,
name|GtkSignalFunc
name|handler
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_remove_handler
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|GimpSetHandlerId
name|id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SET_H__ */
end_comment

end_unit

