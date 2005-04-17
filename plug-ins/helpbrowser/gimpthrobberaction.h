begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpThrobberAction  * Copyright (C) 2005  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_THROBBER_ACTION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_THROBBER_ACTION_H__
define|#
directive|define
name|__GIMP_THROBBER_ACTION_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_THROBBER_ACTION
define|#
directive|define
name|GIMP_TYPE_THROBBER_ACTION
value|(gimp_throbber_action_get_type ())
end_define

begin_define
DECL|macro|GIMP_THROBBER_ACTION (obj)
define|#
directive|define
name|GIMP_THROBBER_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_THROBBER_ACTION, GimpThrobberAction))
end_define

begin_define
DECL|macro|GIMP_THROBBER_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_THROBBER_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_THROBBER_ACTION, GimpThrobberActionClass))
end_define

begin_define
DECL|macro|GIMP_IS_THROBBER_ACTION (obj)
define|#
directive|define
name|GIMP_IS_THROBBER_ACTION
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_THROBBER_ACTION))
end_define

begin_define
DECL|macro|GIMP_IS_THROBBER_ACTION_CLASS (klass)
define|#
directive|define
name|GIMP_IS_THROBBER_ACTION_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((obj), GIMP_TYPE_THROBBER_ACTION))
end_define

begin_define
DECL|macro|GIMP_THROBBER_ACTION_GET_CLASS (obj)
define|#
directive|define
name|GIMP_THROBBER_ACTION_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS((obj), GIMP_TYPE_THROBBER_ACTION, GimpThrobberActionClass))
end_define

begin_typedef
DECL|typedef|GimpThrobberAction
typedef|typedef
name|GtkAction
name|GimpThrobberAction
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThrobberActionClass
typedef|typedef
name|GtkActionClass
name|GimpThrobberActionClass
typedef|;
end_typedef

begin_decl_stmt
name|GType
name|gimp_throbber_action_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkAction
modifier|*
name|gimp_throbber_action_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
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
comment|/* __GIMP_THROBBER_ACTION_H__ */
end_comment

end_unit

