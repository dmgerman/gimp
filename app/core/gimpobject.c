begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_function
specifier|static
name|void
DECL|function|gimp_object_init (GimpObject * gobject)
name|gimp_object_init
parameter_list|(
name|GimpObject
modifier|*
name|gobject
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_class_init (GimpObjectClass * gobjectclass)
name|gimp_object_class_init
parameter_list|(
name|GimpObjectClass
modifier|*
name|gobjectclass
parameter_list|)
block|{ }
end_function

begin_function
name|GtkType
DECL|function|gimp_object_get_type (void)
name|gimp_object_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
init|=
literal|0
decl_stmt|;
name|GIMP_TYPE_INIT
argument_list|(
name|type
argument_list|,
name|GimpObject
argument_list|,
name|GimpObjectClass
argument_list|,
name|gimp_object_init
argument_list|,
name|gimp_object_class_init
argument_list|,
name|GTK_TYPE_OBJECT
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

end_unit

