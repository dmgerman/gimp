begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPLIST_H__
end_ifndef

begin_define
DECL|macro|__GIMPLIST_H__
define|#
directive|define
name|__GIMPLIST_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimplistF.h"
end_include

begin_comment
comment|/* GimpList - a typed list of objects with signals for adding and    removing of stuff. If it is weak, destroyed objects get removed    automatically. If it is not, it refs them so they won't be freed    till they are removed. (Though they can be destroyed, of course) */
end_comment

begin_define
DECL|macro|GIMP_TYPE_LIST
define|#
directive|define
name|GIMP_TYPE_LIST
value|gimp_list_get_type()
end_define

begin_define
DECL|macro|GIMP_LIST (obj)
define|#
directive|define
name|GIMP_LIST
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, GIMP_TYPE_LIST, GimpList)
end_define

begin_define
DECL|macro|GIMP_IS_LIST (obj)
define|#
directive|define
name|GIMP_IS_LIST
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, gimp_list_get_type())
end_define

begin_comment
comment|/* Signals:    add    remove */
end_comment

begin_function_decl
name|guint
name|gimp_list_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpList
modifier|*
name|gimp_list_new
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
name|gimp_list_type
parameter_list|(
name|GimpList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_list_add
parameter_list|(
name|GimpList
modifier|*
name|gimplist
parameter_list|,
name|gpointer
name|ob
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_list_remove
parameter_list|(
name|GimpList
modifier|*
name|gimplist
parameter_list|,
name|gpointer
name|ob
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_list_have
parameter_list|(
name|GimpList
modifier|*
name|gimplist
parameter_list|,
name|gpointer
name|ob
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_list_foreach
parameter_list|(
name|GimpList
modifier|*
name|gimplist
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
name|gimp_list_size
parameter_list|(
name|GimpList
modifier|*
name|gimplist
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

