begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * ValueTypes for config objects  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_TYPES_H__
define|#
directive|define
name|__GIMP_CONFIG_TYPES_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_COLOR
define|#
directive|define
name|GIMP_TYPE_COLOR
value|(gimp_color_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_COLOR (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_COLOR
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_COLOR))
end_define

begin_decl_stmt
name|GType
name|gimp_color_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|GIMP_TYPE_MEMSIZE
define|#
directive|define
name|GIMP_TYPE_MEMSIZE
value|(gimp_memsize_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_MEMSIZE (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_MEMSIZE
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_MEMSIZE))
end_define

begin_decl_stmt
name|GType
name|gimp_memsize_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|GIMP_TYPE_PATH
define|#
directive|define
name|GIMP_TYPE_PATH
value|(gimp_path_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_PATH (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_PATH
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_PATH))
end_define

begin_decl_stmt
name|GType
name|gimp_path_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|GIMP_TYPE_UNIT
define|#
directive|define
name|GIMP_TYPE_UNIT
value|(gimp_unit_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_unit_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_TYPES_H__ */
end_comment

end_unit

