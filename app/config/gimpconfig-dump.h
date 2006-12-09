begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONFIG_DUMP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONFIG_DUMP_H__
define|#
directive|define
name|__GIMP_CONFIG_DUMP_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2ad618840103
block|{
DECL|enumerator|GIMP_CONFIG_DUMP_NONE
name|GIMP_CONFIG_DUMP_NONE
block|,
DECL|enumerator|GIMP_CONFIG_DUMP_GIMPRC
name|GIMP_CONFIG_DUMP_GIMPRC
block|,
DECL|enumerator|GIMP_CONFIG_DUMP_GIMPRC_SYSTEM
name|GIMP_CONFIG_DUMP_GIMPRC_SYSTEM
block|,
DECL|enumerator|GIMP_CONFIG_DUMP_GIMPRC_MANPAGE
name|GIMP_CONFIG_DUMP_GIMPRC_MANPAGE
DECL|typedef|GimpConfigDumpFormat
block|}
name|GimpConfigDumpFormat
typedef|;
end_typedef

begin_function_decl
name|gboolean
name|gimp_config_dump
parameter_list|(
name|GimpConfigDumpFormat
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONFIG_DUMP_H__ */
end_comment

end_unit

