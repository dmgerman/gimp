begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-2004 Maurits Rijk  m.rijk@chello.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_IMAP_ICONS_H
end_ifndef

begin_define
DECL|macro|_IMAP_ICONS_H
define|#
directive|define
name|_IMAP_ICONS_H
end_define

begin_define
DECL|macro|IMAP_ARROW
define|#
directive|define
name|IMAP_ARROW
value|"imap-arrow"
end_define

begin_define
DECL|macro|IMAP_CIRCLE
define|#
directive|define
name|IMAP_CIRCLE
value|"imap-circle"
end_define

begin_define
DECL|macro|IMAP_COORD
define|#
directive|define
name|IMAP_COORD
value|"imap-coord"
end_define

begin_define
DECL|macro|IMAP_DIMENSION
define|#
directive|define
name|IMAP_DIMENSION
value|"imap-dimension"
end_define

begin_define
DECL|macro|IMAP_JAVA
define|#
directive|define
name|IMAP_JAVA
value|"imap-java"
end_define

begin_define
DECL|macro|IMAP_LINK
define|#
directive|define
name|IMAP_LINK
value|"imap-link"
end_define

begin_define
DECL|macro|IMAP_POLYGON
define|#
directive|define
name|IMAP_POLYGON
value|"imap-polygon"
end_define

begin_define
DECL|macro|IMAP_RECTANGLE
define|#
directive|define
name|IMAP_RECTANGLE
value|"imap-rectangle"
end_define

begin_define
DECL|macro|IMAP_TO_BACK
define|#
directive|define
name|IMAP_TO_BACK
value|"imap-to-back"
end_define

begin_define
DECL|macro|IMAP_TO_FRONT
define|#
directive|define
name|IMAP_TO_FRONT
value|"imap-to-front"
end_define

begin_function_decl
name|void
name|init_icons
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _IMAP_ICONS_H */
end_comment

end_unit

