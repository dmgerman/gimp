begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_ENUMS_H__
define|#
directive|define
name|__PLUG_IN_ENUMS_H__
end_define

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2c7218c30103
block|{
DECL|enumerator|PLUG_IN_RGB_IMAGE
name|PLUG_IN_RGB_IMAGE
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|PLUG_IN_GRAY_IMAGE
name|PLUG_IN_GRAY_IMAGE
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|PLUG_IN_INDEXED_IMAGE
name|PLUG_IN_INDEXED_IMAGE
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|PLUG_IN_RGBA_IMAGE
name|PLUG_IN_RGBA_IMAGE
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|PLUG_IN_GRAYA_IMAGE
name|PLUG_IN_GRAYA_IMAGE
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|PLUG_IN_INDEXEDA_IMAGE
name|PLUG_IN_INDEXEDA_IMAGE
init|=
literal|1
operator|<<
literal|5
DECL|typedef|PlugInImageType
block|}
name|PlugInImageType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip>*/
DECL|enum|__anon2c7218c30203
block|{
DECL|enumerator|GIMP_PLUG_IN_CALL_NONE
name|GIMP_PLUG_IN_CALL_NONE
block|,
DECL|enumerator|GIMP_PLUG_IN_CALL_RUN
name|GIMP_PLUG_IN_CALL_RUN
block|,
DECL|enumerator|GIMP_PLUG_IN_CALL_QUERY
name|GIMP_PLUG_IN_CALL_QUERY
block|,
DECL|enumerator|GIMP_PLUG_IN_CALL_INIT
name|GIMP_PLUG_IN_CALL_INIT
DECL|typedef|GimpPlugInCallMode
block|}
name|GimpPlugInCallMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_ENUMS_H__ */
end_comment

end_unit

