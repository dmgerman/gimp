begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PLUG_IN_ERROR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PLUG_IN_ERROR_H__
define|#
directive|define
name|__GIMP_PLUG_IN_ERROR_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c878ff60103
block|{
DECL|enumerator|GIMP_PLUG_IN_FAILED
name|GIMP_PLUG_IN_FAILED
block|,
comment|/* generic error condition */
DECL|enumerator|GIMP_PLUG_IN_EXECUTION_FAILED
name|GIMP_PLUG_IN_EXECUTION_FAILED
block|,
DECL|enumerator|GIMP_PLUG_IN_NOT_FOUND
name|GIMP_PLUG_IN_NOT_FOUND
DECL|typedef|GimpPlugInErrorCode
block|}
name|GimpPlugInErrorCode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_PLUG_IN_ERROR
define|#
directive|define
name|GIMP_PLUG_IN_ERROR
value|(gimp_plug_in_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_plug_in_error_quark
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
comment|/* __GIMP_PLUG_IN_ERROR_H__ */
end_comment

end_unit

