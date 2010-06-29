begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpbasetypes.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpbasetypes.h"
end_include

begin_comment
comment|/**  * SECTION: gimpbasetypes  * @title: gimpbasetypes  * @short_description: Translation between gettext translation domain  *                     identifier and GType.  *  * Translation between gettext translation domain identifier and  * GType.  **/
end_comment

begin_decl_stmt
specifier|static
name|GQuark
name|gimp_translation_domain_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|static
name|GQuark
name|gimp_translation_context_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|static
name|GQuark
name|gimp_value_descriptions_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**  * gimp_type_set_translation_domain:  * @type:   a #GType  * @domain: a constant string that identifies a translation domain or %NULL  *  * This function attaches a constant string as a gettext translation  * domain identifier to a #GType. The only purpose of this function is  * to use it when registering a #G_TYPE_ENUM with translatable value  * names.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_type_set_translation_domain (GType type,const gchar * domain)
name|gimp_type_set_translation_domain
parameter_list|(
name|GType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|)
block|{
name|g_type_set_qdata
argument_list|(
name|type
argument_list|,
name|gimp_translation_domain_quark
argument_list|()
argument_list|,
operator|(
name|gpointer
operator|)
name|domain
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_type_get_translation_domain:  * @type: a #GType  *  * Retrieves the gettext translation domain identifier that has been  * previously set using gimp_type_set_translation_domain(). You should  * not need to use this function directly, use gimp_enum_get_value()  * or gimp_enum_value_get_desc() instead.  *  * Return value: the translation domain associated with @type  *               or %NULL if no domain was set  *  * Since: GIMP 2.2  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_type_get_translation_domain (GType type)
name|gimp_type_get_translation_domain
parameter_list|(
name|GType
name|type
parameter_list|)
block|{
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|g_type_get_qdata
argument_list|(
name|type
argument_list|,
name|gimp_translation_domain_quark
argument_list|()
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_type_set_translation_context:  * @type:    a #GType  * @context: a constant string that identifies a translation context or %NULL  *  * This function attaches a constant string as a translation context  * to a #GType. The only purpose of this function is to use it when  * registering a #G_TYPE_ENUM with translatable value names.  *  * Since: GIMP 2.8  **/
end_comment

begin_function
name|void
DECL|function|gimp_type_set_translation_context (GType type,const gchar * context)
name|gimp_type_set_translation_context
parameter_list|(
name|GType
name|type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|context
parameter_list|)
block|{
name|g_type_set_qdata
argument_list|(
name|type
argument_list|,
name|gimp_translation_context_quark
argument_list|()
argument_list|,
operator|(
name|gpointer
operator|)
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_type_get_translation_context:  * @type: a #GType  *  * Retrieves the translation context that has been previously set  * using gimp_type_set_translation_context(). You should not need to  * use this function directly, use gimp_enum_get_value() or  * gimp_enum_value_get_desc() instead.  *  * Return value: the translation context associated with @type  *               or %NULL if no context was set  *  * Since: GIMP 2.8  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_type_get_translation_context (GType type)
name|gimp_type_get_translation_context
parameter_list|(
name|GType
name|type
parameter_list|)
block|{
return|return
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|g_type_get_qdata
argument_list|(
name|type
argument_list|,
name|gimp_translation_context_quark
argument_list|()
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_set_value_descriptions:  * @enum_type:    a #GType  * @descriptions: a %NULL terminated constant static array of #GimpEnumDesc  *  * Sets the array of human readable and translatable descriptions  * and help texts for enum values.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_enum_set_value_descriptions (GType enum_type,const GimpEnumDesc * descriptions)
name|gimp_enum_set_value_descriptions
parameter_list|(
name|GType
name|enum_type
parameter_list|,
specifier|const
name|GimpEnumDesc
modifier|*
name|descriptions
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|enum_type
argument_list|,
name|G_TYPE_ENUM
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|descriptions
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|enum_type
argument_list|,
name|gimp_value_descriptions_quark
argument_list|()
argument_list|,
operator|(
name|gpointer
operator|)
name|descriptions
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_enum_get_value_descriptions:  * @enum_type: a #GType  *  * Retreives the array of human readable and translatable descriptions  * and help texts for enum values.  *  * Returns: a %NULL terminated constant array of #GimpEnumDesc  *  * Since: GIMP 2.2  **/
end_comment

begin_function
specifier|const
name|GimpEnumDesc
modifier|*
DECL|function|gimp_enum_get_value_descriptions (GType enum_type)
name|gimp_enum_get_value_descriptions
parameter_list|(
name|GType
name|enum_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|enum_type
argument_list|,
name|G_TYPE_ENUM
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|(
specifier|const
name|GimpEnumDesc
operator|*
operator|)
name|g_type_get_qdata
argument_list|(
name|enum_type
argument_list|,
name|gimp_value_descriptions_quark
argument_list|()
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_flags_set_value_descriptions:  * @flags_type:   a #GType  * @descriptions: a %NULL terminated constant static array of #GimpFlagsDesc  *  * Sets the array of human readable and translatable descriptions  * and help texts for flags values.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|void
DECL|function|gimp_flags_set_value_descriptions (GType flags_type,const GimpFlagsDesc * descriptions)
name|gimp_flags_set_value_descriptions
parameter_list|(
name|GType
name|flags_type
parameter_list|,
specifier|const
name|GimpFlagsDesc
modifier|*
name|descriptions
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|flags_type
argument_list|,
name|G_TYPE_FLAGS
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|descriptions
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_type_set_qdata
argument_list|(
name|flags_type
argument_list|,
name|gimp_value_descriptions_quark
argument_list|()
argument_list|,
operator|(
name|gpointer
operator|)
name|descriptions
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_flags_get_value_descriptions:  * @flags_type: a #GType  *  * Retreives the array of human readable and translatable descriptions  * and help texts for flags values.  *  * Returns: a %NULL terminated constant array of #GimpFlagsDesc  *  * Since: GIMP 2.2  **/
end_comment

begin_function
specifier|const
name|GimpFlagsDesc
modifier|*
DECL|function|gimp_flags_get_value_descriptions (GType flags_type)
name|gimp_flags_get_value_descriptions
parameter_list|(
name|GType
name|flags_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|flags_type
argument_list|,
name|G_TYPE_FLAGS
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
operator|(
specifier|const
name|GimpFlagsDesc
operator|*
operator|)
name|g_type_get_qdata
argument_list|(
name|flags_type
argument_list|,
name|gimp_value_descriptions_quark
argument_list|()
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GQuark
DECL|function|gimp_translation_domain_quark (void)
name|gimp_translation_domain_quark
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GQuark
name|quark
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|quark
condition|)
name|quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-translation-domain-quark"
argument_list|)
expr_stmt|;
return|return
name|quark
return|;
block|}
end_function

begin_function
specifier|static
name|GQuark
DECL|function|gimp_translation_context_quark (void)
name|gimp_translation_context_quark
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GQuark
name|quark
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|quark
condition|)
name|quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-translation-context-quark"
argument_list|)
expr_stmt|;
return|return
name|quark
return|;
block|}
end_function

begin_function
specifier|static
name|GQuark
DECL|function|gimp_value_descriptions_quark (void)
name|gimp_value_descriptions_quark
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GQuark
name|quark
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|quark
condition|)
name|quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-value-descriptions-quark"
argument_list|)
expr_stmt|;
return|return
name|quark
return|;
block|}
end_function

end_unit

