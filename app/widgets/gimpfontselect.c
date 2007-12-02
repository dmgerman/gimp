begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfontselect.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"text/gimpfont.h"
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
file|"gimpfontselect.h"
end_include

begin_include
include|#
directive|include
file|"gimpfontview.h"
end_include

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_font_select_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GValueArray
modifier|*
name|gimp_font_select_run_callback
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
DECL|function|G_DEFINE_TYPE (GimpFontSelect,gimp_font_select,GIMP_TYPE_PDB_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFontSelect
argument_list|,
argument|gimp_font_select
argument_list|,
argument|GIMP_TYPE_PDB_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_font_select_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_font_select_class_init
parameter_list|(
name|GimpFontSelectClass
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
name|constructor
operator|=
name|gimp_font_select_constructor
expr_stmt|;
name|pdb_class
operator|->
name|run_callback
operator|=
name|gimp_font_select_run_callback
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_font_select_init (GimpFontSelect * select)
name|gimp_font_select_init
parameter_list|(
name|GimpFontSelect
modifier|*
name|select
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_font_select_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_font_select_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpPdbDialog
modifier|*
name|dialog
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|GIMP_PDB_DIALOG
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|view
operator|=
name|gimp_font_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
name|dialog
operator|->
name|context
operator|->
name|gimp
operator|->
name|fonts
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
literal|6
operator|*
operator|(
name|GIMP_VIEW_SIZE_MEDIUM
operator|+
literal|2
operator|)
argument_list|,
literal|6
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|view
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|gimp_font_select_run_callback (GimpPdbDialog * dialog,GimpObject * object,gboolean closing,GError ** error)
name|gimp_font_select_run_callback
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
name|object
operator|->
name|name
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

