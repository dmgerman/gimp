begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpThrobber  * Copyright (C) 2005  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THROBBER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THROBBER_H__
define|#
directive|define
name|__GIMP_THROBBER_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_THROBBER
define|#
directive|define
name|GIMP_TYPE_THROBBER
value|(gimp_throbber_get_type ())
end_define

begin_define
DECL|macro|GIMP_THROBBER (obj)
define|#
directive|define
name|GIMP_THROBBER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_THROBBER, GimpThrobber))
end_define

begin_define
DECL|macro|GIMP_THROBBER_CLASS (klass)
define|#
directive|define
name|GIMP_THROBBER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_THROBBER, GimpThrobberClass))
end_define

begin_define
DECL|macro|GIMP_IS_THROBBER (obj)
define|#
directive|define
name|GIMP_IS_THROBBER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_THROBBER))
end_define

begin_define
DECL|macro|GIMP_IS_THROBBER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_THROBBER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_THROBBER))
end_define

begin_define
DECL|macro|GIMP_THROBBER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_THROBBER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS((obj), GIMP_TYPE_THROBBER, GimpThrobberClass))
end_define

begin_typedef
DECL|typedef|GimpThrobber
typedef|typedef
name|struct
name|_GimpThrobber
name|GimpThrobber
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThrobberClass
typedef|typedef
name|struct
name|_GimpThrobberClass
name|GimpThrobberClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThrobberPrivate
typedef|typedef
name|struct
name|_GimpThrobberPrivate
name|GimpThrobberPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpThrobber
struct|struct
name|_GimpThrobber
block|{
DECL|member|parent
name|GtkToolItem
name|parent
decl_stmt|;
comment|/*< private>*/
DECL|member|priv
name|GimpThrobberPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpThrobberClass
struct|struct
name|_GimpThrobberClass
block|{
DECL|member|parent_class
name|GtkToolItemClass
name|parent_class
decl_stmt|;
comment|/* signal */
DECL|member|clicked
name|void
function_decl|(
modifier|*
name|clicked
function_decl|)
parameter_list|(
name|GimpThrobber
modifier|*
name|tool_item
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_throbber_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkToolItem
modifier|*
name|gimp_throbber_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_throbber_set_stock_id
parameter_list|(
name|GimpThrobber
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_throbber_get_stock_id
parameter_list|(
name|GimpThrobber
modifier|*
name|button
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
comment|/* __GIMP_THROBBER_H__ */
end_comment

end_unit

