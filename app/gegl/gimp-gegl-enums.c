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
file|"core/core-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-gegl-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./gimp-gegl-enums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_cage_mode_get_type (void)
name|gimp_cage_mode_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_CAGE_MODE_CAGE_CHANGE
block|,
literal|"GIMP_CAGE_MODE_CAGE_CHANGE"
block|,
literal|"cage-change"
block|}
block|,
block|{
name|GIMP_CAGE_MODE_DEFORM
block|,
literal|"GIMP_CAGE_MODE_DEFORM"
block|,
literal|"deform"
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
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_CAGE_MODE_CAGE_CHANGE
block|,
name|NC_
argument_list|(
literal|"cage-mode"
argument_list|,
literal|"Create or adjust the cage"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CAGE_MODE_DEFORM
block|,
name|NC_
argument_list|(
literal|"cage-mode"
argument_list|,
literal|"Deform the cage to deform the image"
argument_list|)
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
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpCageMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"cage-mode"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
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

