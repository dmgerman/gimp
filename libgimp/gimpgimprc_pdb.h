begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpgimprc_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GIMPRC_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GIMPRC_PDB_H__
define|#
directive|define
name|__GIMP_GIMPRC_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gchar
modifier|*
name|gimp_gimprc_query
parameter_list|(
specifier|const
name|gchar
modifier|*
name|token
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_gimprc_set
parameter_list|(
specifier|const
name|gchar
modifier|*
name|token
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_get_default_comment
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_get_monitor_resolution
parameter_list|(
name|gdouble
modifier|*
name|xres
parameter_list|,
name|gdouble
modifier|*
name|yres
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_get_theme_dir
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GIMPRC_PDB_H__ */
end_comment

end_unit

