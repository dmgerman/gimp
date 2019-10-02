begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * DDS GIMP plugin  *  * Copyright (C) 2004-2012 Shawn Kirst<skirst@gmail.com>,  * with parts (C) 2003 Arne Reuter<homepage@arnereuter.de> where specified.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DDSWRITE_H__
end_ifndef

begin_define
DECL|macro|__DDSWRITE_H__
define|#
directive|define
name|__DDSWRITE_H__
end_define

begin_function_decl
specifier|extern
name|GimpPDBStatusType
name|write_dds
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|interactive
parameter_list|,
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DDSWRITE_H__ */
end_comment

end_unit

