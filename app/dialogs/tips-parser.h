begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * tips-parser.h -- Parse the gimp-tips.xml file.  * Copyright (C) 2002  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TIPS_PARSER_H__
end_ifndef

begin_define
DECL|macro|__TIPS_PARSER_H__
define|#
directive|define
name|__TIPS_PARSER_H__
end_define

begin_typedef
DECL|typedef|GimpTip
typedef|typedef
name|struct
name|_GimpTip
name|GimpTip
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTip
struct|struct
name|_GimpTip
block|{
DECL|member|welcome
name|gchar
modifier|*
name|welcome
decl_stmt|;
DECL|member|thetip
name|gchar
modifier|*
name|thetip
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GimpTip
modifier|*
name|gimp_tip_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|1
operator|,
function_decl|2
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_tip_set
parameter_list|(
name|GimpTip
modifier|*
name|tip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_function_decl
name|void
name|gimp_tip_free
parameter_list|(
name|GimpTip
modifier|*
name|tip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_tips_from_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tips_free
parameter_list|(
name|GList
modifier|*
name|tips
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TIPS_PARSER_H__ */
end_comment

end_unit

