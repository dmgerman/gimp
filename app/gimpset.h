begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPSET_H__
end_ifndef

begin_define
DECL|macro|__GIMPSET_H__
define|#
directive|define
name|__GIMPSET_H__
end_define

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"gimpsetF.h"
end_include

begin_comment
comment|/* GimpSet - a typed set of objects with signals for adding and    removing of stuff. If it is weak, destroyed objects get removed    automatically. If it is not, it refs them so they won't be freed    till they are removed. (Though they can be destroyed, of course) */
end_comment

begin_define
DECL|macro|GIMP_TYPE_SET
define|#
directive|define
name|GIMP_TYPE_SET
value|gimp_set_get_type()
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
comment|/* Signals:    add    remove */
end_comment

begin_typedef
DECL|typedef|GimpSetHandlerId
typedef|typedef
name|guint
name|GimpSetHandlerId
typedef|;
end_typedef

begin_function_decl
name|guint
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
name|ob
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
name|ob
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
name|ob
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

end_unit

