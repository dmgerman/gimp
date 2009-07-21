begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpview.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"palettes-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|palettes_merge_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functionss */
end_comment

begin_function
name|void
DECL|function|palettes_import_cmd_callback (GtkAction * action,gpointer data)
name|palettes_import_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|return_if_no_widget
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-palette-import-dialog"
argument_list|,
operator|-
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palettes_merge_cmd_callback (GtkAction * action,gpointer data)
name|palettes_merge_cmd_callback
parameter_list|(
name|GtkAction
modifier|*
name|action
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Merge Palette"
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_PALETTE_MERGE
argument_list|,
name|_
argument_list|(
literal|"Enter a name for the merged palette"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|palettes_merge_callback
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|palettes_merge_callback (GtkWidget * widget,const gchar * palette_name,gpointer data)
name|palettes_merge_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
comment|/* FIXME: reimplement palettes_merge_callback() */
if|#
directive|if
literal|0
block|GimpContainerEditor *editor;   GimpPalette         *palette;   GimpPalette         *new_palette;   GimpPaletteEntry    *entry;   GList               *sel_list;    editor = (GimpContainerEditor *) data;    sel_list = GTK_LIST (GIMP_CONTAINER_LIST_VIEW (editor->view)->gtk_list)->selection;    if (! sel_list)     {       gimp_message_literal (gimp, 			    G_OBJECT (widget), GIMP_MESSAGE_WARNING, 			    "Can't merge palettes because " 			    "there are no palettes selected.");       return;     }    new_palette = GIMP_PALETTE (gimp_palette_new (palette_name, FALSE));    while (sel_list)     {       GimpListItem *list_item;       GList        *cols;        list_item = GIMP_LIST_ITEM (sel_list->data);        palette = (GimpPalette *) GIMP_VIEW (list_item->preview)->viewable;        if (palette)         {           for (cols = palette->colors; cols; cols = g_list_next (cols))             {               entry = (GimpPaletteEntry *) cols->data;                gimp_palette_add_entry (new_palette,                                       entry->name,&entry->color);             }         }        sel_list = sel_list->next;     }    gimp_container_add (editor->view->container,                       GIMP_OBJECT (new_palette));
endif|#
directive|endif
block|}
end_function

end_unit

