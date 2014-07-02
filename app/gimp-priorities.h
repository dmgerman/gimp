begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PRIORITIES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PRIORITIES_H__
define|#
directive|define
name|__GIMP_PRIORITIES_H__
end_define

begin_comment
comment|/* #define G_PRIORITY_HIGH -100 */
end_comment

begin_comment
comment|/* #define G_PRIORITY_DEFAULT 0 */
end_comment

begin_comment
comment|/* #define G_PRIORITY_HIGH_IDLE 100 */
end_comment

begin_comment
comment|/* #define GTK_PRIORITY_REDRAW (G_PRIORITY_HIGH_IDLE + 20) */
end_comment

begin_comment
comment|/*  a bit higher than projection construction  */
end_comment

begin_define
DECL|macro|GIMP_PRIORITY_DISPLAY_SHELL_FILL_IDLE
define|#
directive|define
name|GIMP_PRIORITY_DISPLAY_SHELL_FILL_IDLE
value|(G_PRIORITY_HIGH_IDLE + 21)
end_define

begin_comment
comment|/*  just a bit less than GDK_PRIORITY_REDRAW   */
end_comment

begin_define
DECL|macro|GIMP_PRIORITY_PROJECTION_IDLE
define|#
directive|define
name|GIMP_PRIORITY_PROJECTION_IDLE
value|(G_PRIORITY_HIGH_IDLE + 22)
end_define

begin_comment
comment|/* #define G_PRIORITY_DEFAULT_IDLE 200 */
end_comment

begin_define
DECL|macro|GIMP_PRIORITY_VIEWABLE_IDLE
define|#
directive|define
name|GIMP_PRIORITY_VIEWABLE_IDLE
value|(G_PRIORITY_LOW)
end_define

begin_comment
comment|/* #define G_PRIORITY_LOW 300 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PRIORITIES_H__ */
end_comment

end_unit

