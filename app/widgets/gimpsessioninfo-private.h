begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsessioninfo-private.h  * Copyright (C) 2001-2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SESSION_INFO_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SESSION_INFO_PRIVATE_H__
define|#
directive|define
name|__GIMP_SESSION_INFO_PRIVATE_H__
end_define

begin_struct
DECL|struct|_GimpSessionInfoPrivate
struct|struct
name|_GimpSessionInfoPrivate
block|{
comment|/*  the dialog factory entry for object we have session info for    *  note that pure "dock" entries don't have any factory entry    */
DECL|member|factory_entry
name|GimpDialogFactoryEntry
modifier|*
name|factory_entry
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|right_align
name|gboolean
name|right_align
decl_stmt|;
DECL|member|bottom_align
name|gboolean
name|bottom_align
decl_stmt|;
comment|/*  only valid while restoring and saving the session  */
DECL|member|open
name|gboolean
name|open
decl_stmt|;
DECL|member|screen
name|gint
name|screen
decl_stmt|;
comment|/*  dialog specific list of GimpSessionInfoAux  */
DECL|member|aux_info
name|GList
modifier|*
name|aux_info
decl_stmt|;
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
comment|/*  list of GimpSessionInfoDock  */
DECL|member|docks
name|GList
modifier|*
name|docks
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SESSION_INFO_PRIVATE_H__ */
end_comment

end_unit

