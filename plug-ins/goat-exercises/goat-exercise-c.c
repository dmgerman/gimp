begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  *  Goat exercise plug-in by Ãyvind KolÃ¥s, pippin@gimp.org  */
end_comment

begin_comment
comment|/*  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_define
DECL|macro|GIMP_DISABLE_COMPAR_CRUFT
define|#
directive|define
name|GIMP_DISABLE_COMPAR_CRUFT
end_define

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"goat-exercise-c"
end_define

begin_define
DECL|macro|PLUG_IN_SOURCE
define|#
directive|define
name|PLUG_IN_SOURCE
value|PLUG_IN_BINARY ".c"
end_define

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-goat-exercise-c"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"goat-exercise-c"
end_define

begin_define
DECL|macro|GOAT_URI
define|#
directive|define
name|GOAT_URI
value|"https://gitlab.gnome.org/GNOME/gimp/blob/master/plug-ins/goat-exercises/goat-exercise-c.c"
end_define

begin_typedef
DECL|typedef|Goat
typedef|typedef
name|struct
name|_Goat
name|Goat
typedef|;
end_typedef

begin_typedef
DECL|typedef|GoatClass
typedef|typedef
name|struct
name|_GoatClass
name|GoatClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Goat
struct|struct
name|_Goat
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GoatClass
struct|struct
name|_GoatClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Declare local functions.  */
end_comment

begin_define
DECL|macro|GOAT_TYPE
define|#
directive|define
name|GOAT_TYPE
value|(goat_get_type ())
end_define

begin_define
DECL|macro|GOAT
define|#
directive|define
name|GOAT
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GOAT_TYPE, Goat))
end_define

begin_decl_stmt
name|GType
name|goat_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|GList
modifier|*
name|goat_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProcedure
modifier|*
name|goat_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|goat_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (Goat,goat,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Goat
argument_list|,
argument|goat
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|GOAT_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|goat_class_init
parameter_list|(
name|GoatClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPlugInClass
modifier|*
name|plug_in_class
init|=
name|GIMP_PLUG_IN_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|plug_in_class
operator|->
name|query_procedures
operator|=
name|goat_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|goat_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|goat_init (Goat * goat)
name|goat_init
parameter_list|(
name|Goat
modifier|*
name|goat
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|goat_query_procedures (GimpPlugIn * plug_in)
name|goat_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
return|return
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|g_strdup
argument_list|(
name|PLUG_IN_PROC
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|goat_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|goat_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_image_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|goat_run
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_image_types
argument_list|(
name|procedure
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Exercise in _C minor"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_icon_name
argument_list|(
name|procedure
argument_list|,
name|GIMP_ICON_GEGL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_menu_path
argument_list|(
name|procedure
argument_list|,
literal|"<Image>/Filters/Development/Goat exercises/"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Exercise a goat in the C language"
argument_list|)
argument_list|,
literal|"Takes a goat for a walk"
argument_list|,
name|PLUG_IN_PROC
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Ãyvind KolÃ¥s<pippin@gimp.org>"
argument_list|,
literal|"Ãyvind KolÃ¥s<pippin@gimp.org>"
argument_list|,
literal|"21 march 2012"
argument_list|)
expr_stmt|;
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|goat_run (GimpProcedure * procedure,GimpRunMode run_mode,gint32 image_id,gint32 drawable_id,const GimpValueArray * args,gpointer run_data)
name|goat_run
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/* In interactive mode, display a dialog to advertize the exercise. */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GFileInputStream
modifier|*
name|input
decl_stmt|;
name|gchar
modifier|*
name|head_text
decl_stmt|;
name|gchar
modifier|*
name|path
decl_stmt|;
name|GdkGeometry
name|geometry
decl_stmt|;
name|gchar
name|source_text
index|[
literal|4096
index|]
decl_stmt|;
name|gssize
name|read
decl_stmt|;
name|gint
name|response
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Exercise a goat (C)"
argument_list|)
argument_list|,
name|PLUG_IN_ROLE
argument_list|,
name|NULL
argument_list|,
name|GTK_DIALOG_USE_HEADER_BAR
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
argument_list|,
name|_
argument_list|(
literal|"_Cancel"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"_Source"
argument_list|)
argument_list|,
name|GTK_RESPONSE_APPLY
argument_list|,
name|_
argument_list|(
literal|"_Run"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|geometry
operator|.
name|min_aspect
operator|=
literal|0.5
expr_stmt|;
name|geometry
operator|.
name|max_aspect
operator|=
literal|1.0
expr_stmt|;
name|gtk_window_set_geometry_hints
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|,
operator|&
name|geometry
argument_list|,
name|GDK_HINT_ASPECT
argument_list|)
expr_stmt|;
name|box
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|box
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|head_text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"This plug-in is an exercise in '%s' "
literal|"to demo plug-in creation.\n"
literal|"Check out the last version "
literal|"of the source code online by "
literal|"clicking the \"Source\" button."
argument_list|)
argument_list|,
literal|"C"
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_label_new
argument_list|(
name|head_text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|head_text
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|scrolled
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|scrolled
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_set_vexpand
argument_list|(
name|GTK_WIDGET
argument_list|(
name|scrolled
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled
argument_list|)
expr_stmt|;
name|path
operator|=
name|g_build_filename
argument_list|(
name|gimp_plug_in_directory
argument_list|()
argument_list|,
literal|"plug-ins"
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|PLUG_IN_SOURCE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_text_view_new
argument_list|()
expr_stmt|;
name|gtk_text_view_set_wrap_mode
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_WRAP_WORD
argument_list|)
expr_stmt|;
name|gtk_text_view_set_editable
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|input
operator|=
name|g_file_read
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|read
operator|=
name|g_input_stream_read
argument_list|(
name|G_INPUT_STREAM
argument_list|(
name|input
argument_list|)
argument_list|,
name|source_text
argument_list|,
literal|4096
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|)
operator|&&
name|read
operator|!=
operator|-
literal|1
condition|)
block|{
name|gtk_text_buffer_insert_at_cursor
argument_list|(
name|buffer
argument_list|,
name|source_text
argument_list|,
name|read
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled
argument_list|)
argument_list|,
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|response
operator|=
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|response
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
block|}
elseif|else
if|if
condition|(
name|response
operator|==
name|GTK_RESPONSE_APPLY
condition|)
block|{
comment|/* Show the code. */
name|g_app_info_launch_default_for_uri
argument_list|(
name|GOAT_URI
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
continue|continue;
block|}
else|else
comment|/* CANCEL, CLOSE, DELETE_EVENT */
block|{
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_CANCEL
argument_list|,
name|NULL
argument_list|)
return|;
block|}
block|}
block|}
if|if
condition|(
name|gimp_drawable_mask_intersect
argument_list|(
name|drawable_id
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
condition|)
block|{
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|GeglBuffer
modifier|*
name|shadow_buffer
decl_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|shadow_buffer
operator|=
name|gimp_drawable_get_shadow_buffer
argument_list|(
name|drawable_id
argument_list|)
expr_stmt|;
name|gegl_render_op
argument_list|(
name|buffer
argument_list|,
name|shadow_buffer
argument_list|,
literal|"gegl:invert"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|shadow_buffer
argument_list|)
expr_stmt|;
comment|/* flushes the shadow tiles */
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable_id
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
name|gegl_exit
argument_list|()
expr_stmt|;
block|}
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|status
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

