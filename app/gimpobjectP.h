begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OBJECT_P_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OBJECT_P_H__
define|#
directive|define
name|__GIMP_OBJECT_P_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkobject.h>
end_include

begin_include
include|#
directive|include
file|"gimpobjectF.h"
end_include

begin_struct
DECL|struct|_GimpObject
struct|struct
name|_GimpObject
block|{
DECL|member|object
name|GtkObject
name|object
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon274a84e00108
block|{
DECL|member|parent_class
name|GtkObjectClass
name|parent_class
decl_stmt|;
DECL|typedef|GimpObjectClass
block|}
name|GimpObjectClass
typedef|;
end_typedef

begin_function_decl
name|guint
name|gimp_object_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

