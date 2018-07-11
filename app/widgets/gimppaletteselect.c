begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppaletteselect.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
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
file|"core/gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimppaletteselect.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_palette_select_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|gimp_palette_select_run_callback
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gboolean
name|closing
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPaletteSelect,gimp_palette_select,GIMP_TYPE_PDB_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPaletteSelect
argument_list|,
argument|gimp_palette_select
argument_list|,
argument|GIMP_TYPE_PDB_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_palette_select_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_palette_select_class_init
parameter_list|(
name|GimpPaletteSelectClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpPdbDialogClass
modifier|*
name|pdb_class
init|=
name|GIMP_PDB_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_palette_select_constructed
expr_stmt|;
name|pdb_class
operator|->
name|run_callback
operator|=
name|gimp_palette_select_run_callback
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_select_init (GimpPaletteSelect * dialog)
name|gimp_palette_select_init
parameter_list|(
name|GimpPaletteSelect
modifier|*
name|dialog
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_palette_select_constructed (GObject * object)
name|gimp_palette_select_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPdbDialog
modifier|*
name|dialog
init|=
name|GIMP_PDB_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|content_area
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|view
operator|=
name|gimp_data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|dialog
operator|->
name|context
operator|->
name|gimp
operator|->
name|palette_factory
argument_list|,
name|dialog
operator|->
name|context
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|,
literal|1
argument_list|,
name|dialog
operator|->
name|menu_factory
argument_list|,
literal|"<Palettes>"
argument_list|,
literal|"/palettes-popup"
argument_list|,
literal|"palettes"
argument_list|)
expr_stmt|;
name|gimp_container_box_set_size_request
argument_list|(
name|GIMP_CONTAINER_BOX
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
operator|->
name|view
argument_list|)
argument_list|,
literal|5
operator|*
operator|(
name|GIMP_VIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|,
literal|8
operator|*
operator|(
name|GIMP_VIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|content_area
operator|=
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|content_area
argument_list|)
argument_list|,
name|dialog
operator|->
name|view
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gimp_palette_select_run_callback (GimpPdbDialog * dialog,GimpObject * object,gboolean closing,GError ** error)
name|gimp_palette_select_run_callback
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gboolean
name|closing
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpPalette
modifier|*
name|palette
init|=
name|GIMP_PALETTE
argument_list|(
name|object
argument_list|)
decl_stmt|;
return|return
name|gimp_pdb_execute_procedure_by_name
argument_list|(
name|dialog
operator|->
name|pdb
argument_list|,
name|dialog
operator|->
name|caller_context
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|,
name|dialog
operator|->
name|callback_name
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|gimp_palette_get_n_colors
argument_list|(
name|palette
argument_list|)
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|closing
argument_list|,
name|G_TYPE_NONE
argument_list|)
return|;
block|}
end_function

end_unit

