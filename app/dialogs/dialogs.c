begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * dialogs.c  * Copyright (C) 2010 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockwindow.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|global_recent_docks
name|GimpContainer
modifier|*
name|global_recent_docks
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|FOREIGN (id,singleton,remember_size)
define|#
directive|define
name|FOREIGN
parameter_list|(
name|id
parameter_list|,
name|singleton
parameter_list|,
name|remember_size
parameter_list|)
define|\
value|{ id
comment|/* identifier       */
value|, \     NULL
comment|/* name             */
value|, \     NULL
comment|/* blurb            */
value|, \     NULL
comment|/* stock_id         */
value|, \     NULL
comment|/* help_id          */
value|, \     NULL
comment|/* new_func         */
value|, \     0
comment|/* view_size        */
value|, \     singleton
comment|/* singleton        */
value|, \     TRUE
comment|/* session_managed  */
value|, \     remember_size
comment|/* remember_size    */
value|, \     FALSE
comment|/* remember_if_open */
value|, \     TRUE
comment|/* hideable         */
value|, \     FALSE
comment|/* image_window     */
value|, \     FALSE
comment|/* dockable         */
value|}
end_define

begin_define
DECL|macro|IMAGE_WINDOW (id,singleton,remember_size)
define|#
directive|define
name|IMAGE_WINDOW
parameter_list|(
name|id
parameter_list|,
name|singleton
parameter_list|,
name|remember_size
parameter_list|)
define|\
value|{ id
comment|/* identifier       */
value|, \     NULL
comment|/* name             */
value|, \     NULL
comment|/* blurb            */
value|, \     NULL
comment|/* stock_id         */
value|, \     NULL
comment|/* help_id          */
value|, \     NULL
comment|/* new_func         */
value|, \     0
comment|/* view_size        */
value|, \     singleton
comment|/* singleton        */
value|, \     TRUE
comment|/* session_managed  */
value|, \     remember_size
comment|/* remember_size    */
value|, \     FALSE
comment|/* remember_if_open */
value|, \     FALSE
comment|/* hideable         */
value|, \     TRUE
comment|/* image_window     */
value|, \     FALSE
comment|/* dockable         */
value|}
end_define

begin_define
DECL|macro|TOPLEVEL (id,new_func,singleton,session_managed,remember_size)
define|#
directive|define
name|TOPLEVEL
parameter_list|(
name|id
parameter_list|,
name|new_func
parameter_list|,
name|singleton
parameter_list|,
name|session_managed
parameter_list|,
name|remember_size
parameter_list|)
define|\
value|{ id
comment|/* identifier       */
value|, \     NULL
comment|/* name             */
value|, \     NULL
comment|/* blurb            */
value|, \     NULL
comment|/* stock_id         */
value|, \     NULL
comment|/* help_id          */
value|, \     new_func
comment|/* new_func         */
value|, \     0
comment|/* view_size        */
value|, \     singleton
comment|/* singleton        */
value|, \     session_managed
comment|/* session_managed  */
value|, \     remember_size
comment|/* remember_size    */
value|, \     FALSE
comment|/* remember_if_open */
value|, \     TRUE
comment|/* hideable         */
value|, \     FALSE
comment|/* image_window     */
value|, \     FALSE
comment|/* dockable         */
value|}
end_define

begin_define
DECL|macro|DOCKABLE (id,name,blurb,stock_id,help_id,new_func,view_size,singleton)
define|#
directive|define
name|DOCKABLE
parameter_list|(
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|stock_id
parameter_list|,
name|help_id
parameter_list|,
name|new_func
parameter_list|,
name|view_size
parameter_list|,
name|singleton
parameter_list|)
define|\
value|{ id
comment|/* identifier       */
value|, \     name
comment|/* name             */
value|, \     blurb
comment|/* blurb            */
value|, \     stock_id
comment|/* stock_id         */
value|, \     help_id
comment|/* help_id          */
value|, \     new_func
comment|/* new_func         */
value|, \     view_size
comment|/* view_size        */
value|, \     singleton
comment|/* singleton        */
value|, \     FALSE
comment|/* session_managed  */
value|, \     FALSE
comment|/* remember_size    */
value|, \     TRUE
comment|/* remember_if_open */
value|, \     TRUE
comment|/* hideable         */
value|, \     FALSE
comment|/* image_window     */
value|, \     TRUE
comment|/* dockable         */
value|}
end_define

begin_define
DECL|macro|DOCK (id,new_func)
define|#
directive|define
name|DOCK
parameter_list|(
name|id
parameter_list|,
name|new_func
parameter_list|)
define|\
value|{ id
comment|/* identifier       */
value|, \     NULL
comment|/* name             */
value|, \     NULL
comment|/* blurb            */
value|, \     NULL
comment|/* stock_id         */
value|, \     NULL
comment|/* help_id          */
value|, \     new_func
comment|/* new_func         */
value|, \     0
comment|/* view_size        */
value|, \     FALSE
comment|/* singleton        */
value|, \     FALSE
comment|/* session_managed  */
value|, \     FALSE
comment|/* remember_size    */
value|, \     FALSE
comment|/* remember_if_open */
value|, \     TRUE
comment|/* hideable         */
value|, \     FALSE
comment|/* image_window     */
value|, \     FALSE
comment|/* dockable         */
value|}
end_define

begin_define
DECL|macro|DOCK_WINDOW (id,new_func)
define|#
directive|define
name|DOCK_WINDOW
parameter_list|(
name|id
parameter_list|,
name|new_func
parameter_list|)
define|\
value|{ id
comment|/* identifier       */
value|, \     NULL
comment|/* name             */
value|, \     NULL
comment|/* blurb            */
value|, \     NULL
comment|/* stock_id         */
value|, \     NULL
comment|/* help_id          */
value|, \     new_func
comment|/* new_func         */
value|, \     0
comment|/* view_size        */
value|, \     FALSE
comment|/* singleton        */
value|, \     TRUE
comment|/* session_managed  */
value|, \     TRUE
comment|/* remember_size    */
value|, \     TRUE
comment|/* remember_if_open */
value|, \     TRUE
comment|/* hideable         */
value|, \     FALSE
comment|/* image_window     */
value|, \     FALSE
comment|/* dockable         */
value|}
end_define

begin_define
DECL|macro|LISTGRID (id,name,blurb,stock_id,help_id,view_size)
define|#
directive|define
name|LISTGRID
parameter_list|(
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|stock_id
parameter_list|,
name|help_id
parameter_list|,
name|view_size
parameter_list|)
define|\
value|{ "gimp-"#id"-list"
comment|/* identifier       */
value|,  \     name
comment|/* name             */
value|,  \     blurb
comment|/* blurb            */
value|,  \     stock_id
comment|/* stock_id         */
value|,  \     help_id
comment|/* help_id          */
value|,  \     dialogs_##id##_list_view_new
comment|/* new_func         */
value|,  \     view_size
comment|/* view_size        */
value|,  \     FALSE
comment|/* singleton        */
value|,  \     FALSE
comment|/* session_managed  */
value|,  \     FALSE
comment|/* remember_size    */
value|,  \     TRUE
comment|/* remember_if_open */
value|,  \     TRUE
comment|/* hideable         */
value|,  \     FALSE
comment|/* image_window     */
value|,  \     TRUE
comment|/* dockable         */
value|}, \   { "gimp-"#id"-grid"
comment|/* identifier       */
value|,  \     name
comment|/* name             */
value|,  \     blurb
comment|/* blurb            */
value|,  \     stock_id
comment|/* stock_id         */
value|,  \     help_id
comment|/* help_id          */
value|,  \     dialogs_##id##_grid_view_new
comment|/* new_func         */
value|,  \     view_size
comment|/* view_size        */
value|,  \     FALSE
comment|/* singleton        */
value|,  \     FALSE
comment|/* session_managed  */
value|,  \     FALSE
comment|/* remember_size    */
value|,  \     TRUE
comment|/* remember_if_open */
value|,  \     TRUE
comment|/* hideable         */
value|,  \     FALSE
comment|/* image_window     */
value|,  \     TRUE
comment|/* dockable         */
value|}
end_define

begin_define
DECL|macro|LIST (id,new_func,name,blurb,stock_id,help_id,view_size)
define|#
directive|define
name|LIST
parameter_list|(
name|id
parameter_list|,
name|new_func
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|stock_id
parameter_list|,
name|help_id
parameter_list|,
name|view_size
parameter_list|)
define|\
value|{ "gimp-"#id"-list"
comment|/* identifier       */
value|, \     name
comment|/* name             */
value|, \     blurb
comment|/* blurb            */
value|, \     stock_id
comment|/* stock_id         */
value|, \     help_id
comment|/* help_id          */
value|, \     dialogs_##new_func##_list_view_new
comment|/* new_func         */
value|, \     view_size
comment|/* view_size        */
value|, \     FALSE
comment|/* singleton        */
value|, \     FALSE
comment|/* session_managed  */
value|, \     FALSE
comment|/* remember_size    */
value|, \     TRUE
comment|/* remember_if_open */
value|, \     TRUE
comment|/* hideable         */
value|, \     FALSE
comment|/* image_window     */
value|, \     TRUE
comment|/* dockable         */
value|}
end_define

begin_decl_stmt
DECL|variable|entries
specifier|static
specifier|const
name|GimpDialogFactoryEntry
name|entries
index|[]
init|=
block|{
comment|/*  foreign toplevels without constructor  */
name|FOREIGN
argument_list|(
literal|"gimp-brightness-contrast-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-color-balance-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-color-picker-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-colorize-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-crop-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-curves-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-desaturate-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-gegl-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-hue-saturation-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-levels-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-measure-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-posterize-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-rotate-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-scale-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-shear-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-text-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-threshold-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-perspective-tool-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-toolbox-color-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-gradient-editor-color-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-palette-editor-color-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-colormap-editor-color-dialog"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-controller-editor-dialog"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-controller-action-dialog"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
block|,
comment|/*  ordinary toplevels  */
name|TOPLEVEL
argument_list|(
literal|"gimp-image-new-dialog"
argument_list|,
name|dialogs_image_new_new
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-file-open-dialog"
argument_list|,
name|dialogs_file_open_new
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-file-open-location-dialog"
argument_list|,
name|dialogs_file_open_location_new
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-file-save-dialog"
argument_list|,
name|dialogs_file_save_new
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-file-export-dialog"
argument_list|,
name|dialogs_file_export_new
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
comment|/*  singleton toplevels  */
name|TOPLEVEL
argument_list|(
literal|"gimp-preferences-dialog"
argument_list|,
name|dialogs_preferences_get
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-input-devices-dialog"
argument_list|,
name|dialogs_input_devices_get
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-keyboard-shortcuts-dialog"
argument_list|,
name|dialogs_keyboard_shortcuts_get
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-module-dialog"
argument_list|,
name|dialogs_module_get
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-palette-import-dialog"
argument_list|,
name|dialogs_palette_import_get
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-tips-dialog"
argument_list|,
name|dialogs_tips_get
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-about-dialog"
argument_list|,
name|dialogs_about_get
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-error-dialog"
argument_list|,
name|dialogs_error_get
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-close-all-dialog"
argument_list|,
name|dialogs_close_all_get
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-quit-dialog"
argument_list|,
name|dialogs_quit_get
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
block|,
comment|/*  docks  */
name|DOCK
argument_list|(
literal|"gimp-dock"
argument_list|,
name|dialogs_dock_new
argument_list|)
block|,
name|DOCK
argument_list|(
literal|"gimp-toolbox"
argument_list|,
name|dialogs_toolbox_new
argument_list|)
block|,
comment|/*  dock windows  */
name|DOCK_WINDOW
argument_list|(
literal|"gimp-dock-window"
argument_list|,
name|dialogs_dock_window_new
argument_list|)
block|,
name|DOCK_WINDOW
argument_list|(
literal|"gimp-toolbox-window"
argument_list|,
name|dialogs_toolbox_dock_window_new
argument_list|)
block|,
comment|/*  singleton dockables  */
name|DOCKABLE
argument_list|(
literal|"gimp-tool-options"
argument_list|,
name|N_
argument_list|(
literal|"Tool Options"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_TOOL_OPTIONS
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
argument_list|,
name|dialogs_tool_options_new
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-device-status"
argument_list|,
name|N_
argument_list|(
literal|"Devices"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Device Status"
argument_list|)
argument_list|,
name|GIMP_STOCK_DEVICE_STATUS
argument_list|,
name|GIMP_HELP_DEVICE_STATUS_DIALOG
argument_list|,
name|dialogs_device_status_new
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-error-console"
argument_list|,
name|N_
argument_list|(
literal|"Errors"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Error Console"
argument_list|)
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|GIMP_HELP_ERRORS_DIALOG
argument_list|,
name|dialogs_error_console_new
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-cursor-view"
argument_list|,
name|N_
argument_list|(
literal|"Pointer"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Pointer Information"
argument_list|)
argument_list|,
name|GIMP_STOCK_CURSOR
argument_list|,
name|GIMP_HELP_POINTER_INFO_DIALOG
argument_list|,
name|dialogs_cursor_view_new
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
comment|/*  list& grid views  */
name|LISTGRID
argument_list|(
name|image
argument_list|,
name|N_
argument_list|(
literal|"Images"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_IMAGES
argument_list|,
name|GIMP_HELP_IMAGE_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|brush
argument_list|,
name|N_
argument_list|(
literal|"Brushes"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_BRUSH
argument_list|,
name|GIMP_HELP_BRUSH_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|pattern
argument_list|,
name|N_
argument_list|(
literal|"Patterns"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_PATTERN
argument_list|,
name|GIMP_HELP_PATTERN_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|gradient
argument_list|,
name|N_
argument_list|(
literal|"Gradients"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_GRADIENT
argument_list|,
name|GIMP_HELP_GRADIENT_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|palette
argument_list|,
name|N_
argument_list|(
literal|"Palettes"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_PALETTE
argument_list|,
name|GIMP_HELP_PALETTE_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|font
argument_list|,
name|N_
argument_list|(
literal|"Fonts"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_FONT
argument_list|,
name|GIMP_HELP_FONT_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|buffer
argument_list|,
name|N_
argument_list|(
literal|"Buffers"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_BUFFER
argument_list|,
name|GIMP_HELP_BUFFER_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|document
argument_list|,
name|N_
argument_list|(
literal|"History"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Document History"
argument_list|)
argument_list|,
literal|"document-open-recent"
argument_list|,
name|GIMP_HELP_DOCUMENT_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_LARGE
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|template
argument_list|,
name|N_
argument_list|(
literal|"Templates"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Image Templates"
argument_list|)
argument_list|,
name|GIMP_STOCK_TEMPLATE
argument_list|,
name|GIMP_HELP_TEMPLATE_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
block|,
comment|/* Some things do not have grids, so just list */
name|LIST
argument_list|(
name|dynamics
argument_list|,
name|dynamics
argument_list|,
name|N_
argument_list|(
literal|"Paint Dynamics"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_DYNAMICS
argument_list|,
name|GIMP_HELP_DYNAMICS_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LIST
argument_list|(
name|tool
operator|-
name|preset
argument_list|,
name|tool_preset
argument_list|,
name|N_
argument_list|(
literal|"Tool Presets"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_TOOL_PRESET
argument_list|,
name|GIMP_HELP_TOOL_PRESET_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
comment|/*  image related  */
name|DOCKABLE
argument_list|(
literal|"gimp-layer-list"
argument_list|,
name|N_
argument_list|(
literal|"Layers"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_LAYERS
argument_list|,
name|GIMP_HELP_LAYER_DIALOG
argument_list|,
name|dialogs_layer_list_view_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-channel-list"
argument_list|,
name|N_
argument_list|(
literal|"Channels"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_CHANNELS
argument_list|,
name|GIMP_HELP_CHANNEL_DIALOG
argument_list|,
name|dialogs_channel_list_view_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-vectors-list"
argument_list|,
name|N_
argument_list|(
literal|"Paths"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_PATHS
argument_list|,
name|GIMP_HELP_PATH_DIALOG
argument_list|,
name|dialogs_vectors_list_view_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-indexed-palette"
argument_list|,
name|N_
argument_list|(
literal|"Colormap"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_COLORMAP
argument_list|,
name|GIMP_HELP_INDEXED_PALETTE_DIALOG
argument_list|,
name|dialogs_colormap_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-histogram-editor"
argument_list|,
name|N_
argument_list|(
literal|"Histogram"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_HISTOGRAM
argument_list|,
name|GIMP_HELP_HISTOGRAM_DIALOG
argument_list|,
name|dialogs_histogram_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-selection-editor"
argument_list|,
name|N_
argument_list|(
literal|"Selection"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Selection Editor"
argument_list|)
argument_list|,
name|GIMP_STOCK_SELECTION
argument_list|,
name|GIMP_HELP_SELECTION_DIALOG
argument_list|,
name|dialogs_selection_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-undo-history"
argument_list|,
name|N_
argument_list|(
literal|"Undo"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Undo History"
argument_list|)
argument_list|,
name|GIMP_STOCK_UNDO_HISTORY
argument_list|,
name|GIMP_HELP_UNDO_DIALOG
argument_list|,
name|dialogs_undo_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-sample-point-editor"
argument_list|,
name|N_
argument_list|(
literal|"Sample Points"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Sample Points"
argument_list|)
argument_list|,
name|GIMP_STOCK_SAMPLE_POINT
argument_list|,
name|GIMP_HELP_SAMPLE_POINT_DIALOG
argument_list|,
name|dialogs_sample_point_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
comment|/*  display related  */
name|DOCKABLE
argument_list|(
literal|"gimp-navigation-view"
argument_list|,
name|N_
argument_list|(
literal|"Navigation"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Display Navigation"
argument_list|)
argument_list|,
name|GIMP_STOCK_NAVIGATION
argument_list|,
name|GIMP_HELP_NAVIGATION_DIALOG
argument_list|,
name|dialogs_navigation_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
comment|/*  editors  */
name|DOCKABLE
argument_list|(
literal|"gimp-color-editor"
argument_list|,
name|N_
argument_list|(
literal|"FG/BG"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"FG/BG Color"
argument_list|)
argument_list|,
name|GIMP_STOCK_DEFAULT_COLORS
argument_list|,
name|GIMP_HELP_COLOR_DIALOG
argument_list|,
name|dialogs_color_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
comment|/*  singleton editors  */
name|DOCKABLE
argument_list|(
literal|"gimp-brush-editor"
argument_list|,
name|N_
argument_list|(
literal|"Brush Editor"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_BRUSH
argument_list|,
name|GIMP_HELP_BRUSH_EDITOR_DIALOG
argument_list|,
name|dialogs_brush_editor_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-dynamics-editor"
argument_list|,
name|N_
argument_list|(
literal|"Paint Dynamics Editor"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_DYNAMICS
argument_list|,
name|GIMP_HELP_DYNAMICS_EDITOR_DIALOG
argument_list|,
name|dialogs_dynamics_editor_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-gradient-editor"
argument_list|,
name|N_
argument_list|(
literal|"Gradient Editor"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_GRADIENT
argument_list|,
name|GIMP_HELP_GRADIENT_EDITOR_DIALOG
argument_list|,
name|dialogs_gradient_editor_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-palette-editor"
argument_list|,
name|N_
argument_list|(
literal|"Palette Editor"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_PALETTE
argument_list|,
name|GIMP_HELP_PALETTE_EDITOR_DIALOG
argument_list|,
name|dialogs_palette_editor_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-tool-preset-editor"
argument_list|,
name|N_
argument_list|(
literal|"Tool Preset Editor"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_TOOL_PRESET
argument_list|,
name|GIMP_HELP_TOOL_PRESET_EDITOR_DIALOG
argument_list|,
name|dialogs_tool_preset_editor_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
comment|/*  image windows  */
name|IMAGE_WINDOW
argument_list|(
literal|"gimp-empty-image-window"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|IMAGE_WINDOW
argument_list|(
literal|"gimp-single-image-window"
argument_list|,
argument|TRUE
argument_list|,
argument|TRUE
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|dialogs_init (Gimp * gimp,GimpMenuFactory * menu_factory)
name|dialogs_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpDialogFactory
modifier|*
name|factory
init|=
name|NULL
decl_stmt|;
name|gint
name|i
init|=
literal|0
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|)
expr_stmt|;
name|factory
operator|=
name|gimp_dialog_factory_new
argument_list|(
literal|"toplevel"
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|menu_factory
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_set_singleton
argument_list|(
name|factory
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|entries
argument_list|)
condition|;
name|i
operator|++
control|)
name|gimp_dialog_factory_register_entry
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|identifier
argument_list|,
name|gettext
argument_list|(
name|entries
index|[
name|i
index|]
operator|.
name|name
argument_list|)
argument_list|,
name|gettext
argument_list|(
name|entries
index|[
name|i
index|]
operator|.
name|blurb
argument_list|)
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|stock_id
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|help_id
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|new_func
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|view_size
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|singleton
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|session_managed
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|remember_size
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|remember_if_open
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|hideable
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|image_window
argument_list|,
name|entries
index|[
name|i
index|]
operator|.
name|dockable
argument_list|)
expr_stmt|;
name|global_recent_docks
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_SESSION_INFO
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_exit (Gimp * gimp)
name|dialogs_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dialog_factory_get_singleton
argument_list|()
condition|)
block|{
comment|/* run dispose manually so the factory destroys its dialogs, which        * might in turn directly or indirectly ref the factory        */
name|g_object_run_dispose
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_set_singleton
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|global_recent_docks
condition|)
block|{
name|g_object_unref
argument_list|(
name|global_recent_docks
argument_list|)
expr_stmt|;
name|global_recent_docks
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|dialogs_ensure_factory_entry_on_recent_dock (GimpSessionInfo * info)
name|dialogs_ensure_factory_entry_on_recent_dock
parameter_list|(
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
block|{
if|if
condition|(
operator|!
name|gimp_session_info_get_factory_entry
argument_list|(
name|info
argument_list|)
condition|)
block|{
name|GimpDialogFactoryEntry
modifier|*
name|entry
init|=
name|NULL
decl_stmt|;
comment|/* The recent docks container only contains session infos for        * dock windows        */
name|entry
operator|=
name|gimp_dialog_factory_find_entry
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|,
literal|"gimp-dock-window"
argument_list|)
expr_stmt|;
name|gimp_session_info_set_factory_entry
argument_list|(
name|info
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|dialogs_load_recent_docks (Gimp * gimp)
name|dialogs_load_recent_docks
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"dockrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|global_recent_docks
argument_list|)
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
operator|->
name|code
operator|!=
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
comment|/* In GIMP 2.6 dockrc did not contain the factory entries for the    * session infos, so set that up manually if needed    */
name|gimp_container_foreach
argument_list|(
name|global_recent_docks
argument_list|,
operator|(
name|GFunc
operator|)
name|dialogs_ensure_factory_entry_on_recent_dock
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|global_recent_docks
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_save_recent_docks (Gimp * gimp)
name|dialogs_save_recent_docks
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"dockrc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|global_recent_docks
argument_list|)
argument_list|,
name|filename
argument_list|,
literal|"recently closed docks"
argument_list|,
literal|"end of recently closed docks"
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|dialogs_get_toolbox (void)
name|dialogs_get_toolbox
parameter_list|(
name|void
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_dialog_factory_get_open_dialogs
argument_list|(
name|gimp_dialog_factory_get_singleton
argument_list|()
argument_list|)
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
if|if
condition|(
name|GIMP_IS_DOCK_WINDOW
argument_list|(
name|list
operator|->
name|data
argument_list|)
operator|&&
name|gimp_dock_window_has_toolbox
argument_list|(
name|list
operator|->
name|data
argument_list|)
condition|)
return|return
name|list
operator|->
name|data
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

