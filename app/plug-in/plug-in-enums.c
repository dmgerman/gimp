begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Generated data (by gimp-mkenums) */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./plug-in-enums.h" */
end_comment

begin_function
name|GType
DECL|function|plug_in_image_type_get_type (void)
name|plug_in_image_type_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GFlagsValue
name|values
index|[]
init|=
block|{
block|{
name|PLUG_IN_RGB_IMAGE
block|,
literal|"PLUG_IN_RGB_IMAGE"
block|,
literal|"rgb-image"
block|}
block|,
block|{
name|PLUG_IN_GRAY_IMAGE
block|,
literal|"PLUG_IN_GRAY_IMAGE"
block|,
literal|"gray-image"
block|}
block|,
block|{
name|PLUG_IN_INDEXED_IMAGE
block|,
literal|"PLUG_IN_INDEXED_IMAGE"
block|,
literal|"indexed-image"
block|}
block|,
block|{
name|PLUG_IN_RGBA_IMAGE
block|,
literal|"PLUG_IN_RGBA_IMAGE"
block|,
literal|"rgba-image"
block|}
block|,
block|{
name|PLUG_IN_GRAYA_IMAGE
block|,
literal|"PLUG_IN_GRAYA_IMAGE"
block|,
literal|"graya-image"
block|}
block|,
block|{
name|PLUG_IN_INDEXEDA_IMAGE
block|,
literal|"PLUG_IN_INDEXEDA_IMAGE"
block|,
literal|"indexeda-image"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpFlagsDesc
name|descs
index|[]
init|=
block|{
block|{
name|PLUG_IN_RGB_IMAGE
block|,
literal|"PLUG_IN_RGB_IMAGE"
block|,
name|NULL
block|}
block|,
block|{
name|PLUG_IN_GRAY_IMAGE
block|,
literal|"PLUG_IN_GRAY_IMAGE"
block|,
name|NULL
block|}
block|,
block|{
name|PLUG_IN_INDEXED_IMAGE
block|,
literal|"PLUG_IN_INDEXED_IMAGE"
block|,
name|NULL
block|}
block|,
block|{
name|PLUG_IN_RGBA_IMAGE
block|,
literal|"PLUG_IN_RGBA_IMAGE"
block|,
name|NULL
block|}
block|,
block|{
name|PLUG_IN_GRAYA_IMAGE
block|,
literal|"PLUG_IN_GRAYA_IMAGE"
block|,
name|NULL
block|}
block|,
block|{
name|PLUG_IN_INDEXEDA_IMAGE
block|,
literal|"PLUG_IN_INDEXEDA_IMAGE"
block|,
name|NULL
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
name|type
operator|=
name|g_flags_register_static
argument_list|(
literal|"PlugInImageType"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_flags_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_comment
comment|/* Generated data ends here */
end_comment

end_unit

