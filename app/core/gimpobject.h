begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OBJECT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OBJECT_H__
define|#
directive|define
name|__GIMP_OBJECT_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtktypeutils.h>
end_include

begin_include
include|#
directive|include
file|"gimpobjectF.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OBJECT
define|#
directive|define
name|GIMP_TYPE_OBJECT
value|gimp_object_get_type()
end_define

begin_define
DECL|macro|GIMP_OBJECT (obj)
define|#
directive|define
name|GIMP_OBJECT
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_CAST (obj, GIMP_TYPE_OBJECT, GimpObject)
end_define

begin_define
DECL|macro|GIMP_IS_OBJECT (obj)
define|#
directive|define
name|GIMP_IS_OBJECT
parameter_list|(
name|obj
parameter_list|)
value|GTK_CHECK_TYPE (obj, GIMP_TYPE_OBJECT)
end_define

begin_function_decl
name|guint
name|gimp_object_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* hacks to fake a gimp object lib */
end_comment

begin_define
DECL|macro|GIMP_CHECK_CAST
define|#
directive|define
name|GIMP_CHECK_CAST
value|GTK_CHECK_CAST
end_define

begin_define
DECL|macro|GIMP_CHECK_TYPE
define|#
directive|define
name|GIMP_CHECK_TYPE
value|GTK_CHECK_TYPE
end_define

begin_define
DECL|macro|gimp_type_new
define|#
directive|define
name|gimp_type_new
value|gtk_type_new
end_define

begin_define
DECL|macro|gimp_object_destroy (obj)
define|#
directive|define
name|gimp_object_destroy
parameter_list|(
name|obj
parameter_list|)
value|gtk_object_destroy(GTK_OBJECT(obj))
end_define

begin_define
DECL|macro|gimp_object_ref (obj)
define|#
directive|define
name|gimp_object_ref
parameter_list|(
name|obj
parameter_list|)
value|gtk_object_ref(GTK_OBJECT(obj))
end_define

begin_define
DECL|macro|gimp_object_unref (obj)
define|#
directive|define
name|gimp_object_unref
parameter_list|(
name|obj
parameter_list|)
value|gtk_object_unref(GTK_OBJECT(obj))
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit

