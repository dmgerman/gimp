begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpopendialog.c  * Copyright (C) 2015 Jehan<jehan@girinstud.io>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpfiledialog.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpopendialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpOpenDialog,gimp_open_dialog,GIMP_TYPE_FILE_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpOpenDialog
argument_list|,
argument|gimp_open_dialog
argument_list|,
argument|GIMP_TYPE_FILE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_open_dialog_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_open_dialog_class_init
parameter_list|(
name|GimpOpenDialogClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_open_dialog_init (GimpOpenDialog * dialog)
name|gimp_open_dialog_init
parameter_list|(
name|GimpOpenDialog
modifier|*
name|dialog
parameter_list|)
block|{ }
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_open_dialog_new (Gimp * gimp)
name|gimp_open_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpOpenDialog
modifier|*
name|dialog
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_OPEN_DIALOG
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
literal|"title"
argument_list|,
name|_
argument_list|(
literal|"Open Image"
argument_list|)
argument_list|,
literal|"role"
argument_list|,
literal|"gimp-file-open"
argument_list|,
literal|"help-id"
argument_list|,
name|GIMP_HELP_FILE_OPEN
argument_list|,
literal|"stock-id"
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
literal|"automatic-label"
argument_list|,
name|_
argument_list|(
literal|"Automatically Detected"
argument_list|)
argument_list|,
literal|"automatic-help-id"
argument_list|,
name|GIMP_HELP_FILE_OPEN_BY_EXTENSION
argument_list|,
literal|"action"
argument_list|,
name|GTK_FILE_CHOOSER_ACTION_OPEN
argument_list|,
literal|"file-procs"
argument_list|,
name|gimp
operator|->
name|plug_in_manager
operator|->
name|load_procs
argument_list|,
literal|"file-procs-all-images"
argument_list|,
name|NULL
argument_list|,
literal|"file-filter-label"
argument_list|,
name|NULL
argument_list|,
literal|"local-only"
argument_list|,
name|FALSE
argument_list|,
literal|"do-overwrite-confirmation"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_open_dialog_set_image (GimpOpenDialog * dialog,GimpImage * image,gboolean open_as_layers)
name|gimp_open_dialog_set_image
parameter_list|(
name|GimpOpenDialog
modifier|*
name|dialog
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|open_as_layers
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OPEN_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|GIMP_FILE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|image
operator|=
name|image
expr_stmt|;
name|dialog
operator|->
name|open_as_layers
operator|=
name|open_as_layers
expr_stmt|;
block|}
end_function

end_unit

