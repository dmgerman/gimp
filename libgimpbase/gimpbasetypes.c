begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpbasetypes.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/**  * gimp_type_set_translation_domain:  * @type:   a #GType  * @domain: a constant string that identifies a translation domain or %NULL  *  * This function attaches a constant string as a gettext translation  * domain identifier to a #GType. The only purpose of this function is  * to use it when registering a #GTypeEnum with translatable value  * names.  *  * Since: GIMP 2.2  **/
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
comment|/**  * gimp_type_get_translation_domain:  * @type: a #GType  *  * Retrieves the gettext translation domain identifier that has been  * previously set using gimp_type_set_translation_domain(). You should  * not need to use this function directly, use gimp_enum_get_value()  * or gimp_enum_value_get_name() instead.  *  * Return value: the translation domain associated with @type  *               or %NULL if no domain was set  *  * Since: GIMP 2.2  **/
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

end_unit

