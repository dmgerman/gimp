begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgetstypes.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WIDGETS_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIDGETS_TYPES_H__
define|#
directive|define
name|__GIMP_WIDGETS_TYPES_H__
end_define

begin_include
include|#
directive|include
file|<libgimpbase/gimpbasetypes.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the html documentation */
typedef|typedef
enum|enum
DECL|enum|__anon288bcdda0103
block|{
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_NONE
name|GIMP_SIZE_ENTRY_UPDATE_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_SIZE
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
init|=
literal|1
block|,
DECL|enumerator|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
name|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
init|=
literal|2
DECL|typedef|GimpSizeEntryUpdatePolicy
block|}
name|GimpSizeEntryUpdatePolicy
typedef|;
DECL|typedef|GimpButton
typedef|typedef
name|struct
name|_GimpButton
name|GimpButton
typedef|;
DECL|typedef|GimpChainButton
typedef|typedef
name|struct
name|_GimpChainButton
name|GimpChainButton
typedef|;
DECL|typedef|GimpColorArea
typedef|typedef
name|struct
name|_GimpColorArea
name|GimpColorArea
typedef|;
DECL|typedef|GimpColorButton
typedef|typedef
name|struct
name|_GimpColorButton
name|GimpColorButton
typedef|;
DECL|typedef|GimpOffsetArea
typedef|typedef
name|struct
name|_GimpOffsetArea
name|GimpOffsetArea
typedef|;
DECL|typedef|GimpPathEditor
typedef|typedef
name|struct
name|_GimpPathEditor
name|GimpPathEditor
typedef|;
DECL|typedef|GimpPixmap
typedef|typedef
name|struct
name|_GimpPixmap
name|GimpPixmap
typedef|;
DECL|typedef|GimpSizeEntry
typedef|typedef
name|struct
name|_GimpSizeEntry
name|GimpSizeEntry
typedef|;
DECL|typedef|GimpUnitMenu
typedef|typedef
name|struct
name|_GimpUnitMenu
name|GimpUnitMenu
typedef|;
DECL|typedef|GimpHelpFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpHelpFunc
function_decl|)
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WIDGETS_TYPES_H__ */
end_comment

end_unit

