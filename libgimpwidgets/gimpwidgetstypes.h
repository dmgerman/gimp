begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgetstypes.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<libgimpconfig/gimpconfigtypes.h>
end_include

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpwidgetsenums.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpBrowser
typedef|typedef
name|struct
name|_GimpBrowser
name|GimpBrowser
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
DECL|typedef|GimpCellRendererColor
typedef|typedef
name|struct
name|_GimpCellRendererColor
name|GimpCellRendererColor
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCellRendererToggle
typedef|typedef
name|struct
name|_GimpCellRendererToggle
name|GimpCellRendererToggle
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
DECL|typedef|GimpColorDisplayStack
typedef|typedef
name|struct
name|_GimpColorDisplayStack
name|GimpColorDisplayStack
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorHexEntry
typedef|typedef
name|struct
name|_GimpColorHexEntry
name|GimpColorHexEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorNotebook
typedef|typedef
name|struct
name|_GimpColorNotebook
name|GimpColorNotebook
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorProfileComboBox
typedef|typedef
name|struct
name|_GimpColorProfileComboBox
name|GimpColorProfileComboBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorProfileStore
typedef|typedef
name|struct
name|_GimpColorProfileStore
name|GimpColorProfileStore
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorScale
typedef|typedef
name|struct
name|_GimpColorScale
name|GimpColorScale
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorScales
typedef|typedef
name|struct
name|_GimpColorScales
name|GimpColorScales
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
DECL|typedef|GimpColorSelection
typedef|typedef
name|struct
name|_GimpColorSelection
name|GimpColorSelection
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpController
typedef|typedef
name|struct
name|_GimpController
name|GimpController
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
DECL|typedef|GimpEnumStore
typedef|typedef
name|struct
name|_GimpEnumStore
name|GimpEnumStore
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEnumComboBox
typedef|typedef
name|struct
name|_GimpEnumComboBox
name|GimpEnumComboBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpEnumLabel
typedef|typedef
name|struct
name|_GimpEnumLabel
name|GimpEnumLabel
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFileEntry
typedef|typedef
name|struct
name|_GimpFileEntry
name|GimpFileEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFrame
typedef|typedef
name|struct
name|_GimpFrame
name|GimpFrame
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpIntComboBox
typedef|typedef
name|struct
name|_GimpIntComboBox
name|GimpIntComboBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpIntStore
typedef|typedef
name|struct
name|_GimpIntStore
name|GimpIntStore
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMemsizeEntry
typedef|typedef
name|struct
name|_GimpMemsizeEntry
name|GimpMemsizeEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpNumberPairEntry
typedef|typedef
name|struct
name|_GimpNumberPairEntry
name|GimpNumberPairEntry
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
DECL|typedef|GimpPageSelector
typedef|typedef
name|struct
name|_GimpPageSelector
name|GimpPageSelector
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
DECL|typedef|GimpPickButton
typedef|typedef
name|struct
name|_GimpPickButton
name|GimpPickButton
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreview
typedef|typedef
name|struct
name|_GimpPreview
name|GimpPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPreviewArea
typedef|typedef
name|struct
name|_GimpPreviewArea
name|GimpPreviewArea
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
DECL|typedef|GimpRuler
typedef|typedef
name|struct
name|_GimpRuler
name|GimpRuler
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpScrolledPreview
typedef|typedef
name|struct
name|_GimpScrolledPreview
name|GimpScrolledPreview
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
DECL|typedef|GimpStringComboBox
typedef|typedef
name|struct
name|_GimpStringComboBox
name|GimpStringComboBox
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
DECL|typedef|GimpZoomModel
typedef|typedef
name|struct
name|_GimpZoomModel
name|GimpZoomModel
typedef|;
end_typedef

begin_comment
comment|/**  * GimpHelpFunc:  * @help_id:   the help ID  * @help_data: the help user data  *  * This is the prototype for all functions you pass as @help_func to  * the various GIMP dialog constructors like gimp_dialog_new(),  * gimp_query_int_box() etc.  *  * Help IDs are textual identifiers the help system uses to figure  * which page to display.  *  * All these dialog constructors functions call gimp_help_connect().  *  * In most cases it will be ok to use gimp_standard_help_func() which  * does nothing but passing the @help_id string to gimp_help(). If  * your plug-in needs some more sophisticated help handling you can  * provide your own @help_func which has to call gimp_help() to  * actually display the help.  **/
end_comment

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
name|help_id
parameter_list|,
name|gpointer
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

