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
file|"gimpobjectF.h"
end_include

begin_define
DECL|macro|GIMP_OBJECT (obj)
define|#
directive|define
name|GIMP_OBJECT
parameter_list|(
name|obj
parameter_list|)
define|\
value|GTK_CHECK_CAST (obj, gimp_object_get_type (), GimpObject)
end_define

begin_define
DECL|macro|GIMP_OBJECT_CLASS (klass)
define|#
directive|define
name|GIMP_OBJECT_CLASS
parameter_list|(
name|klass
parameter_list|)
define|\
value|GTK_CHECK_CLASS_CAST (klass, gimp_object_get_type(), GimpObjectClass)
end_define

begin_define
DECL|macro|GIMP_IS_OBJECT (obj)
define|#
directive|define
name|GIMP_IS_OBJECT
parameter_list|(
name|obj
parameter_list|)
define|\
value|GTK_CHECK_TYPE (obj, gimp_object_get_type())
end_define

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

