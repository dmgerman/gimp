begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__DISPLAY_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__DISPLAY_ENUMS_H__
define|#
directive|define
name|__DISPLAY_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_CURSOR_MODE
define|#
directive|define
name|GIMP_TYPE_CURSOR_MODE
value|(gimp_cursor_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_cursor_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b2c75660103
block|{
DECL|enumerator|GIMP_CURSOR_MODE_TOOL_ICON
name|GIMP_CURSOR_MODE_TOOL_ICON
block|,
comment|/*< desc="Tool Icon">*/
DECL|enumerator|GIMP_CURSOR_MODE_TOOL_CROSSHAIR
name|GIMP_CURSOR_MODE_TOOL_CROSSHAIR
block|,
comment|/*< desc="Tool Icon with Crosshair">*/
DECL|enumerator|GIMP_CURSOR_MODE_CROSSHAIR
name|GIMP_CURSOR_MODE_CROSSHAIR
comment|/*< desc="Crosshair only">*/
DECL|typedef|GimpCursorMode
block|}
name|GimpCursorMode
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __DISPLAY_ENUMS_H__ */
end_comment

end_unit

