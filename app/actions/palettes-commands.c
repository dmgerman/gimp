begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gui-types.h"
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
file|"widgets/gimpcontainerlistview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimplistitem.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"palette-import-dialog.h"
end_include

begin_include
include|#
directive|include
file|"palettes-commands.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtklist.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|palettes_merge_palettes_query
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|palettes_merge_palettes_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
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
DECL|function|palettes_import_palette_cmd_callback (GtkWidget * widget,gpointer data)
name|palettes_import_palette_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|palette_import_dialog_show
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
operator|->
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|palettes_merge_palettes_cmd_callback (GtkWidget * widget,gpointer data)
name|palettes_merge_palettes_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|palettes_merge_palettes_query
argument_list|(
name|editor
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
DECL|function|palettes_merge_palettes_query (GimpContainerEditor * editor)
name|palettes_merge_palettes_query
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|qbox
decl_stmt|;
name|qbox
operator|=
name|gimp_query_string_box
argument_list|(
name|_
argument_list|(
literal|"Merge Palette"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/palette_editor/merge_palette.html"
argument_list|,
name|_
argument_list|(
literal|"Enter a name for merged palette"
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
name|palettes_merge_palettes_callback
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|qbox
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|palettes_merge_palettes_callback (GtkWidget * widget,gchar * palette_name,gpointer data)
name|palettes_merge_palettes_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gchar
modifier|*
name|palette_name
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|GimpPalette
modifier|*
name|palette
decl_stmt|;
name|GimpPalette
modifier|*
name|new_palette
decl_stmt|;
name|GimpPaletteEntry
modifier|*
name|entry
decl_stmt|;
name|GList
modifier|*
name|sel_list
decl_stmt|;
name|editor
operator|=
operator|(
name|GimpContainerEditor
operator|*
operator|)
name|data
expr_stmt|;
name|sel_list
operator|=
name|GTK_LIST
argument_list|(
name|GIMP_CONTAINER_LIST_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
operator|->
name|gtk_list
argument_list|)
operator|->
name|selection
expr_stmt|;
if|if
condition|(
operator|!
name|sel_list
condition|)
block|{
name|g_message
argument_list|(
literal|"Can't merge palettes because there are no palettes selected."
argument_list|)
expr_stmt|;
return|return;
block|}
name|new_palette
operator|=
name|GIMP_PALETTE
argument_list|(
name|gimp_palette_new
argument_list|(
name|palette_name
argument_list|,
name|FALSE
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|sel_list
condition|)
block|{
name|GimpListItem
modifier|*
name|list_item
decl_stmt|;
name|GList
modifier|*
name|cols
decl_stmt|;
name|list_item
operator|=
name|GIMP_LIST_ITEM
argument_list|(
name|sel_list
operator|->
name|data
argument_list|)
expr_stmt|;
name|palette
operator|=
operator|(
name|GimpPalette
operator|*
operator|)
name|GIMP_PREVIEW
argument_list|(
name|list_item
operator|->
name|preview
argument_list|)
operator|->
name|viewable
expr_stmt|;
if|if
condition|(
name|palette
condition|)
block|{
for|for
control|(
name|cols
operator|=
name|palette
operator|->
name|colors
init|;
name|cols
condition|;
name|cols
operator|=
name|g_list_next
argument_list|(
name|cols
argument_list|)
control|)
block|{
name|entry
operator|=
operator|(
name|GimpPaletteEntry
operator|*
operator|)
name|cols
operator|->
name|data
expr_stmt|;
name|gimp_palette_add_entry
argument_list|(
name|new_palette
argument_list|,
name|entry
operator|->
name|name
argument_list|,
operator|&
name|entry
operator|->
name|color
argument_list|)
expr_stmt|;
block|}
block|}
name|sel_list
operator|=
name|sel_list
operator|->
name|next
expr_stmt|;
block|}
name|gimp_container_add
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|new_palette
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

