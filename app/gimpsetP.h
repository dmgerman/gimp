begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMPSETP_H__
end_ifndef

begin_define
DECL|macro|__GIMPSETP_H__
define|#
directive|define
name|__GIMPSETP_H__
end_define

begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_include
include|#
directive|include
file|"gimpset.h"
end_include

begin_struct
DECL|struct|_GimpSet
struct|struct
name|_GimpSet
block|{
DECL|member|gobject
name|GimpObject
name|gobject
decl_stmt|;
DECL|member|type
name|GtkType
name|type
decl_stmt|;
DECL|member|list
name|GSList
modifier|*
name|list
decl_stmt|;
DECL|member|weak
name|gboolean
name|weak
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSetClass
struct|struct
name|_GimpSetClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpSetClass
typedef|typedef
name|struct
name|_GimpSetClass
name|GimpSetClass
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_SET_CLASS (klass)
define|#
directive|define
name|GIMP_SET_CLASS
parameter_list|(
name|klass
parameter_list|)
value|GTK_CHECK_CLASS_CAST (klass, gimp_set_get_type(), GimpSetClass)
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit

