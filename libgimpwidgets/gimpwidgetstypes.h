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

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the html documentation */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon289d00520103
block|{
DECL|enumerator|GIMP_COLOR_AREA_FLAT
name|GIMP_COLOR_AREA_FLAT
init|=
literal|0
block|,
DECL|enumerator|GIMP_COLOR_AREA_SMALL_CHECKS
name|GIMP_COLOR_AREA_SMALL_CHECKS
block|,
DECL|enumerator|GIMP_COLOR_AREA_LARGE_CHECKS
name|GIMP_COLOR_AREA_LARGE_CHECKS
DECL|typedef|GimpColorAreaType
block|}
name|GimpColorAreaType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon289d00520203
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
end_typedef

begin_typedef
DECL|typedef|GimpButton
typedef|typedef
name|struct
name|_GimpButton
name|GimpButton
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChainButton
typedef|typedef
name|struct
name|_GimpChainButton
name|GimpChainButton
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorArea
typedef|typedef
name|struct
name|_GimpColorArea
name|GimpColorArea
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorButton
typedef|typedef
name|struct
name|_GimpColorButton
name|GimpColorButton
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorDisplay
typedef|typedef
name|struct
name|_GimpColorDisplay
name|GimpColorDisplay
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorSelector
typedef|typedef
name|struct
name|_GimpColorSelector
name|GimpColorSelector
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorSelect
typedef|typedef
name|struct
name|_GimpColorSelect
name|GimpColorSelect
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDialog
typedef|typedef
name|struct
name|_GimpDialog
name|GimpDialog
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFileSelection
typedef|typedef
name|struct
name|_GimpFileSelection
name|GimpFileSelection
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOffsetArea
typedef|typedef
name|struct
name|_GimpOffsetArea
name|GimpOffsetArea
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPathEditor
typedef|typedef
name|struct
name|_GimpPathEditor
name|GimpPathEditor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPixmap
typedef|typedef
name|struct
name|_GimpPixmap
name|GimpPixmap
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSizeEntry
typedef|typedef
name|struct
name|_GimpSizeEntry
name|GimpSizeEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpUnitMenu
typedef|typedef
name|struct
name|_GimpUnitMenu
name|GimpUnitMenu
typedef|;
end_typedef

begin_typedef
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
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_WIDGETS_TYPES_H__ */
end_comment

end_unit

