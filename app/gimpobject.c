begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<gtk/gtkobject.h>
end_include

begin_include
include|#
directive|include
file|"gimpobjectP.h"
end_include

begin_include
include|#
directive|include
file|"gimpobject.h"
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
DECL|function|gimp_object_get_type (void)
name|GtkType
name|gimp_object_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|GtkTypeInfo
name|info
init|=
block|{
literal|"GimpObject"
block|,
sizeof|sizeof
argument_list|(
name|GimpObject
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpObjectClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_object_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_object_init
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|gtk_object_get_type
argument_list|()
argument_list|,
operator|&
name|info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

end_unit

