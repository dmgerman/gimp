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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"paint-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./paint-enums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_brush_application_mode_get_type (void)
name|gimp_brush_application_mode_get_type
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
name|GIMP_BRUSH_HARD
block|,
literal|"GIMP_BRUSH_HARD"
block|,
literal|"hard"
block|}
block|,
block|{
name|GIMP_BRUSH_SOFT
block|,
literal|"GIMP_BRUSH_SOFT"
block|,
literal|"soft"
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
name|GIMP_BRUSH_HARD
block|,
literal|"GIMP_BRUSH_HARD"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BRUSH_SOFT
block|,
literal|"GIMP_BRUSH_SOFT"
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
literal|"GimpBrushApplicationMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"brush-application-mode"
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

begin_function
name|GType
DECL|function|gimp_perspective_clone_mode_get_type (void)
name|gimp_perspective_clone_mode_get_type
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
name|GIMP_PERSPECTIVE_CLONE_MODE_ADJUST
block|,
literal|"GIMP_PERSPECTIVE_CLONE_MODE_ADJUST"
block|,
literal|"adjust"
block|}
block|,
block|{
name|GIMP_PERSPECTIVE_CLONE_MODE_PAINT
block|,
literal|"GIMP_PERSPECTIVE_CLONE_MODE_PAINT"
block|,
literal|"paint"
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
name|GIMP_PERSPECTIVE_CLONE_MODE_ADJUST
block|,
name|NC_
argument_list|(
literal|"perspective-clone-mode"
argument_list|,
literal|"Modify Perspective"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_PERSPECTIVE_CLONE_MODE_PAINT
block|,
name|NC_
argument_list|(
literal|"perspective-clone-mode"
argument_list|,
literal|"Perspective Clone"
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
literal|"GimpPerspectiveCloneMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"perspective-clone-mode"
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

begin_function
name|GType
DECL|function|gimp_source_align_mode_get_type (void)
name|gimp_source_align_mode_get_type
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
name|GIMP_SOURCE_ALIGN_NO
block|,
literal|"GIMP_SOURCE_ALIGN_NO"
block|,
literal|"no"
block|}
block|,
block|{
name|GIMP_SOURCE_ALIGN_YES
block|,
literal|"GIMP_SOURCE_ALIGN_YES"
block|,
literal|"yes"
block|}
block|,
block|{
name|GIMP_SOURCE_ALIGN_REGISTERED
block|,
literal|"GIMP_SOURCE_ALIGN_REGISTERED"
block|,
literal|"registered"
block|}
block|,
block|{
name|GIMP_SOURCE_ALIGN_FIXED
block|,
literal|"GIMP_SOURCE_ALIGN_FIXED"
block|,
literal|"fixed"
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
name|GIMP_SOURCE_ALIGN_NO
block|,
name|NC_
argument_list|(
literal|"source-align-mode"
argument_list|,
literal|"None"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SOURCE_ALIGN_YES
block|,
name|NC_
argument_list|(
literal|"source-align-mode"
argument_list|,
literal|"Aligned"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SOURCE_ALIGN_REGISTERED
block|,
name|NC_
argument_list|(
literal|"source-align-mode"
argument_list|,
literal|"Registered"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SOURCE_ALIGN_FIXED
block|,
name|NC_
argument_list|(
literal|"source-align-mode"
argument_list|,
literal|"Fixed"
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
literal|"GimpSourceAlignMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"source-align-mode"
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

