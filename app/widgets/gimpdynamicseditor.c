begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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

begin_comment
comment|//#include "core/gimpbrushgenerated.h"
end_comment

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdynamicseditor.h"
end_include

begin_comment
comment|//To do:
end_comment

begin_comment
comment|// discard unneeded ones.
end_comment

begin_comment
comment|// needs to be fixed to gimppaintdynamics.h when that works.
end_comment

begin_comment
comment|/* #include "paint/gimppaintoptions.h"  #include "core/gimptoolinfo.h"  #include "widgets/gimppropwidgets.h" #include "widgets/gimpviewablebox.h" #include "widgets/gimpwidgets-utils.h"  #include "tools/gimpairbrushtool.h" #include "tools/gimpclonetool.h" #include "tools/gimpconvolvetool.h" #include "tools/gimpdodgeburntool.h" #include "tools/gimperasertool.h" #include "tools/gimphealtool.h" #include "tools/gimpinktool.h" #include "tools/gimppaintoptions-gui.h" #include "tools/gimppenciltool.h" #include "tools/gimpperspectiveclonetool.h" #include "tools/gimpsmudgetool.h" #include "tools/gimptooloptions-gui.h"  */
end_comment

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|face
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_dynamics_editor_constructor
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
name|void
name|gimp_dynamics_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dynamics_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*dynamics options gui*/
end_comment

begin_comment
comment|/* static gboolean    tool_has_opacity_dynamics      (GType       tool_type); static gboolean    tool_has_hardness_dynamics     (GType       tool_type); static gboolean    tool_has_rate_dynamics         (GType       tool_type); static gboolean    tool_has_size_dynamics         (GType       tool_type); static gboolean    tool_has_color_dynamics        (GType       tool_type); static gboolean    tool_has_angle_dynamics        (GType       tool_type); static gboolean    tool_has_aspect_ratio_dynamics (GType       tool_type);  static void        pressure_options_gui  (GimpPaintOptions *paint_options,                                           GType             tool_type,                                           GtkTable         *table,                                           gint              row,                                           GtkWidget        *labels[]); static void        velocity_options_gui  (GimpPaintOptions *paint_options,                                           GType             tool_type,                                           GtkTable         *table,                                           gint              row); static void        direction_options_gui (GimpPaintOptions *paint_options,                                           GType             tool_type,                                           GtkTable         *table,                                           gint              row); static void        tilt_options_gui      (GimpPaintOptions *paint_options,                                           GType             tool_type,                                           GtkTable         *table,                                           gint              row); static void        random_options_gui    (GimpPaintOptions *paint_options,                                           GType             tool_type,                                           GtkTable         *table,                                           gint              row);  static void        fading_options_gui    (GimpPaintOptions *paint_options,                                           GType             tool_type,                                           GtkTable         *table,                                           gint              row); */
end_comment

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpDynamicsEditor
argument_list|,
argument|gimp_dynamics_editor
argument_list|,
argument|GIMP_TYPE_DATA_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_dynamics_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dynamics_editor_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpDockedInterface
modifier|*
name|parent_docked_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_editor_class_init (GimpDynamicsEditorClass * klass)
name|gimp_dynamics_editor_class_init
parameter_list|(
name|GimpDynamicsEditorClass
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
name|GimpDataEditorClass
modifier|*
name|editor_class
init|=
name|GIMP_DATA_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_dynamics_editor_constructor
expr_stmt|;
name|editor_class
operator|->
name|set_data
operator|=
name|gimp_dynamics_editor_set_data
expr_stmt|;
name|editor_class
operator|->
name|title
operator|=
name|_
argument_list|(
literal|"Dynamics Editor"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_editor_docked_iface_init (GimpDockedInterface * iface)
name|gimp_dynamics_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_docked_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent_docked_iface
condition|)
name|parent_docked_iface
operator|=
name|g_type_default_interface_peek
argument_list|(
name|GIMP_TYPE_DOCKED
argument_list|)
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_dynamics_editor_set_context
expr_stmt|;
block|}
end_function

begin_comment
comment|/* To do: look at other init for dataeditors look at how to move gui codes from paintopitons to here */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_editor_init (GimpDynamicsEditor * editor)
name|gimp_dynamics_editor_init
parameter_list|(
name|GimpDynamicsEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
comment|//GtkWidget      *box;
comment|//gint            row = 0;
comment|//add a frame
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_dynamics_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_dynamics_editor_constructor
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
name|gimp_docked_set_show_button_bar
argument_list|(
name|GIMP_DOCKED
argument_list|(
name|object
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dynamics_editor_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_dynamics_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpDataEditor
modifier|*
name|data_editor
init|=
name|GIMP_DATA_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|parent_docked_iface
operator|->
name|set_context
argument_list|(
name|docked
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_view_renderer_set_context
argument_list|(
name|GIMP_VIEW
argument_list|(
name|data_editor
operator|->
name|view
argument_list|)
operator|->
name|renderer
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dynamics_editor_new (GimpContext * context,GimpMenuFactory * menu_factory)
name|gimp_dynamics_editor_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_DYNAMICS_EDITOR
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<DynamicsEditor>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/dynamics-editor-popup"
argument_list|,
literal|"data-factory"
argument_list|,
name|context
operator|->
name|gimp
operator|->
name|brush_factory
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"data"
argument_list|,
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
return|;
comment|/*   return g_object_new (GIMP_TYPE_DYNAMICS_EDITOR,                        "menu-factory",    menu_factory,                        "menu-identifier", "<DynamicsEditor>",                        "ui-path",         "/dynamics-editor-popup",                        "data-factory",    context->gimp->brush_factory,                        "context",         context,                        "data",            gimp_context_get_brush (context),                        NULL); */
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_comment
comment|/* static gboolean tool_has_opacity_dynamics (GType tool_type) {   return (g_type_is_a (tool_type, GIMP_TYPE_PAINTBRUSH_TOOL) ||           tool_type == GIMP_TYPE_CLONE_TOOL             ||           tool_type == GIMP_TYPE_HEAL_TOOL              ||           tool_type == GIMP_TYPE_PERSPECTIVE_CLONE_TOOL ||           tool_type == GIMP_TYPE_DODGE_BURN_TOOL        ||           tool_type == GIMP_TYPE_ERASER_TOOL); }  static gboolean tool_has_hardness_dynamics (GType tool_type) {   return (tool_type == GIMP_TYPE_AIRBRUSH_TOOL          ||           tool_type == GIMP_TYPE_CLONE_TOOL             ||           tool_type == GIMP_TYPE_HEAL_TOOL              ||           tool_type == GIMP_TYPE_PERSPECTIVE_CLONE_TOOL ||           tool_type == GIMP_TYPE_CONVOLVE_TOOL          ||           tool_type == GIMP_TYPE_ERASER_TOOL            ||           tool_type == GIMP_TYPE_DODGE_BURN_TOOL        ||           tool_type == GIMP_TYPE_PAINTBRUSH_TOOL        ||           tool_type == GIMP_TYPE_SMUDGE_TOOL); }  static gboolean tool_has_rate_dynamics (GType tool_type) {   return (tool_type == GIMP_TYPE_AIRBRUSH_TOOL          ||           tool_type == GIMP_TYPE_CONVOLVE_TOOL          ||           tool_type == GIMP_TYPE_SMUDGE_TOOL); }  static gboolean tool_has_size_dynamics (GType tool_type) {   return (g_type_is_a (tool_type, GIMP_TYPE_PAINTBRUSH_TOOL) ||           tool_type == GIMP_TYPE_CLONE_TOOL             ||           tool_type == GIMP_TYPE_HEAL_TOOL              ||           tool_type == GIMP_TYPE_PERSPECTIVE_CLONE_TOOL ||           tool_type == GIMP_TYPE_CONVOLVE_TOOL          ||           tool_type == GIMP_TYPE_DODGE_BURN_TOOL        ||           tool_type == GIMP_TYPE_ERASER_TOOL); }  static gboolean tool_has_aspect_ratio_dynamics (GType tool_type) {   return (g_type_is_a (tool_type, GIMP_TYPE_PAINTBRUSH_TOOL) ||           tool_type == GIMP_TYPE_CLONE_TOOL             ||           tool_type == GIMP_TYPE_HEAL_TOOL              ||           tool_type == GIMP_TYPE_PERSPECTIVE_CLONE_TOOL ||           tool_type == GIMP_TYPE_CONVOLVE_TOOL          ||           tool_type == GIMP_TYPE_DODGE_BURN_TOOL        ||           tool_type == GIMP_TYPE_ERASER_TOOL); }  static gboolean tool_has_angle_dynamics (GType tool_type) {   return (g_type_is_a (tool_type, GIMP_TYPE_PAINTBRUSH_TOOL)); }  static gboolean tool_has_color_dynamics (GType tool_type) {   return (g_type_is_a (tool_type, GIMP_TYPE_PAINTBRUSH_TOOL)); }  static GtkWidget * dynamics_check_button_new (GObject     *config,                            const gchar *property_name,                            GtkTable    *table,                            gint         column,                            gint         row) {   GtkWidget *button;    button = gimp_prop_check_button_new (config, property_name, NULL);   gtk_table_attach (table, button, column, column + 1, row, row + 1,                     GTK_SHRINK, GTK_SHRINK, 0, 0);   gtk_widget_show (button);    return button; }  static void dynamics_check_button_size_allocate (GtkWidget     *toggle,                                      GtkAllocation *allocation,                                      GtkWidget     *label) {   GtkWidget *fixed = label->parent;   gint       x, y;    if (gtk_widget_get_direction (label) == GTK_TEXT_DIR_LTR)     x = allocation->x;   else     x = allocation->x + allocation->width - label->allocation.width;    x -= fixed->allocation.x;    y = fixed->allocation.height - label->allocation.height;    gtk_fixed_move (GTK_FIXED (fixed), label, x, y); }  static void pressure_options_gui (GimpPaintOptions *paint_options,                       GType             tool_type,                       GtkTable         *table,                       gint              row,                       GtkWidget        *labels[]) {   GObject   *config = G_OBJECT (paint_options);   GtkWidget *button;   gint       column = 1;   GtkWidget *scalebutton;    if (tool_has_opacity_dynamics (tool_type))     {       button = dynamics_check_button_new (config, "pressure-opacity",                                           table, column, row);       g_signal_connect (button, "size-allocate",                         G_CALLBACK (dynamics_check_button_size_allocate),                         labels[column - 1]);       column++;     }    if (tool_has_hardness_dynamics (tool_type))     {       button = dynamics_check_button_new (config, "pressure-hardness",                                           table, column, row);       g_signal_connect (button, "size-allocate",                         G_CALLBACK (dynamics_check_button_size_allocate),                         labels[column - 1]);       column++;     }    if (tool_has_rate_dynamics (tool_type))     {       button = dynamics_check_button_new (config, "pressure-rate",                                           table, column, row);       g_signal_connect (button, "size-allocate",                         G_CALLBACK (dynamics_check_button_size_allocate),                         labels[column - 1]);       column++;     }    if (tool_has_size_dynamics (tool_type))     {       if (tool_type != GIMP_TYPE_AIRBRUSH_TOOL)         button = dynamics_check_button_new (config, "pressure-size",                                             table, column, row);       else         button = dynamics_check_button_new (config, "pressure-inverse-size",                                             table, column, row);        g_signal_connect (button, "size-allocate",                         G_CALLBACK (dynamics_check_button_size_allocate),                         labels[column - 1]);       column++;     }    if (tool_has_aspect_ratio_dynamics (tool_type))     {       button = dynamics_check_button_new (config, "pressure-aspect_ratio",                                           table, column, row);        g_signal_connect (button, "size-allocate",                         G_CALLBACK (dynamics_check_button_size_allocate),                         labels[column - 1]);       column++;      }    if (tool_has_angle_dynamics (tool_type))     {       button = dynamics_check_button_new (config, "pressure-angle",                                           table, column, row);       g_signal_connect (button, "size-allocate",                         G_CALLBACK (dynamics_check_button_size_allocate),                         labels[column - 1]);       column++;     }    if (tool_has_color_dynamics (tool_type))     {       button = dynamics_check_button_new (config, "pressure-color",                                           table, column, row);       g_signal_connect (button, "size-allocate",                         G_CALLBACK (dynamics_check_button_size_allocate),                         labels[column - 1]);       column++;     }     scalebutton = gimp_prop_scale_button_new (config, "pressure-prescale");    gtk_table_attach (table, scalebutton, column, column + 1, row, row + 1,                     GTK_SHRINK, GTK_SHRINK, 0, 0);    gtk_widget_show (scalebutton); }  static void velocity_options_gui (GimpPaintOptions *paint_options,                       GType             tool_type,                       GtkTable         *table,                       gint              row) {   GObject   *config = G_OBJECT (paint_options);   gint       column = 1;   GtkWidget *scalebutton;    if (tool_has_opacity_dynamics (tool_type))     {       dynamics_check_button_new (config, "velocity-opacity",                                  table, column++, row);     }    if (tool_has_hardness_dynamics (tool_type))     {       dynamics_check_button_new (config, "velocity-hardness",                                  table, column++, row);     }    if (tool_has_rate_dynamics (tool_type))     {       dynamics_check_button_new (config, "velocity-rate",                                  table, column++, row);     }    if (tool_has_size_dynamics (tool_type))     {       dynamics_check_button_new (config, "velocity-size",                                  table, column++, row);     }    if (tool_has_aspect_ratio_dynamics (tool_type))     {       dynamics_check_button_new (config, "velocity-aspect-ratio",                                  table, column++, row);     }     if (tool_has_angle_dynamics (tool_type))     {       dynamics_check_button_new (config, "velocity-angle",                                  table, column++, row);     }    if (tool_has_color_dynamics (tool_type))     {       dynamics_check_button_new (config, "velocity-color",                                  table, column++, row);     }    scalebutton = gimp_prop_scale_button_new (config, "velocity-prescale");   gtk_table_attach (table, scalebutton, column, column + 1, row, row + 1,                     GTK_SHRINK, GTK_SHRINK, 0, 0);   gtk_widget_show (scalebutton); }  static void direction_options_gui (GimpPaintOptions *paint_options,                        GType             tool_type,                        GtkTable         *table,                        gint              row) {   GObject   *config = G_OBJECT (paint_options);   gint       column = 1;   GtkWidget *scalebutton;    if (tool_has_opacity_dynamics (tool_type))     {       dynamics_check_button_new (config, "direction-opacity",                                  table, column++, row);     }    if (tool_has_hardness_dynamics (tool_type))     {       dynamics_check_button_new (config, "direction-hardness",                                  table, column++, row);     }    if (tool_has_rate_dynamics (tool_type))     {       dynamics_check_button_new (config, "direction-rate",                                  table, column++, row);     }    if (tool_has_size_dynamics (tool_type))     {       dynamics_check_button_new (config, "direction-size",                                  table, column++, row);     }    if (tool_has_aspect_ratio_dynamics (tool_type))     {       dynamics_check_button_new (config, "direction-aspect-ratio",                                  table, column++, row);     }    if (tool_has_angle_dynamics (tool_type))     {       dynamics_check_button_new (config, "direction-angle",                                  table, column++, row);     }    if (tool_has_color_dynamics (tool_type))     {       dynamics_check_button_new (config, "direction-color",                                  table, column++, row);     }    scalebutton = gimp_prop_scale_button_new (config, "direction-prescale");   gtk_table_attach (table, scalebutton, column, column + 1, row, row + 1,                     GTK_SHRINK, GTK_SHRINK, 0, 0);   gtk_widget_show (scalebutton); }   static void tilt_options_gui (GimpPaintOptions *paint_options,                        GType             tool_type,                        GtkTable         *table,                        gint              row) {   GObject   *config = G_OBJECT (paint_options);   gint       column = 1;   GtkWidget *scalebutton;    if (tool_has_opacity_dynamics (tool_type))     {       dynamics_check_button_new (config, "tilt-opacity",                                  table, column++, row);     }    if (tool_has_hardness_dynamics (tool_type))     {       dynamics_check_button_new (config, "tilt-hardness",                                  table, column++, row);     }    if (tool_has_rate_dynamics (tool_type))     {       dynamics_check_button_new (config, "tilt-rate",                                  table, column++, row);     }    if (tool_has_size_dynamics (tool_type))     {       dynamics_check_button_new (config, "tilt-size",                                  table, column++, row);     }  if (tool_has_aspect_ratio_dynamics (tool_type))     {       dynamics_check_button_new (config, "tilt-aspect-ratio",                                  table, column++, row);     }    if (tool_has_angle_dynamics (tool_type))     {       dynamics_check_button_new (config, "tilt-angle",                                  table, column++, row);     }    if (tool_has_color_dynamics (tool_type))     {       dynamics_check_button_new (config, "tilt-color",                                  table, column++, row);     }    scalebutton = gimp_prop_scale_button_new (config, "tilt-prescale");   gtk_table_attach (table, scalebutton, column, column + 1, row, row + 1,                     GTK_SHRINK, GTK_SHRINK, 0, 0);   gtk_widget_show (scalebutton); }  static void random_options_gui (GimpPaintOptions *paint_options,                     GType             tool_type,                     GtkTable         *table,                     gint              row) {   GObject   *config = G_OBJECT (paint_options);   gint       column = 1;   GtkWidget *scalebutton;    if (tool_has_opacity_dynamics (tool_type))     {       dynamics_check_button_new (config, "random-opacity",                                  table, column++, row);     }    if (tool_has_hardness_dynamics (tool_type))     {       dynamics_check_button_new (config, "random-hardness",                                  table, column++, row);     }    if (tool_has_rate_dynamics (tool_type))     {       dynamics_check_button_new (config, "random-rate",                                  table, column++, row);     }    if (tool_has_size_dynamics (tool_type))     {       dynamics_check_button_new (config, "random-size",                                  table, column++, row);     }    if (tool_has_aspect_ratio_dynamics (tool_type))     {       dynamics_check_button_new (config, "random-aspect-ratio",                                  table, column++, row);     }    if (tool_has_angle_dynamics (tool_type))     {       dynamics_check_button_new (config, "random-angle",                                  table, column++, row);     }    if (tool_has_color_dynamics (tool_type))     {       dynamics_check_button_new (config, "random-color",                                  table, column++, row);     }     scalebutton = gimp_prop_scale_button_new (config, "random-prescale");    gtk_table_attach (table, scalebutton, column, column + 1, row, row + 1,                     GTK_SHRINK, GTK_SHRINK, 0, 0);    gtk_widget_show (scalebutton); }  static void fading_options_gui (GimpPaintOptions *paint_options,                     GType             tool_type,                     GtkTable         *table,                     gint              row) {   GObject   *config = G_OBJECT (paint_options);   gint       column = 1;   GtkWidget *scalebutton;    if (tool_has_opacity_dynamics (tool_type))     {       dynamics_check_button_new (config, "fading-opacity",                                  table, column++, row);     }    if (tool_has_hardness_dynamics (tool_type))     {       dynamics_check_button_new (config, "fading-hardness",                                  table, column++, row);     }    if (tool_has_rate_dynamics (tool_type))     {       dynamics_check_button_new (config, "fading-rate",                                  table, column++, row);     }    if (tool_has_size_dynamics (tool_type))     {       dynamics_check_button_new (config, "fading-size",                                  table, column++, row);     }    if (tool_has_aspect_ratio_dynamics (tool_type))     {       dynamics_check_button_new (config, "fading-aspect-ratio",                                  table, column++, row);     }    if (tool_has_angle_dynamics (tool_type))     {       dynamics_check_button_new (config, "fading-angle",                                  table, column++, row);     }    if (tool_has_color_dynamics (tool_type))     {       dynamics_check_button_new (config, "fading-color",                                  table, column++, row);     }     scalebutton = gimp_prop_scale_button_new (config, "fading-prescale");    gtk_table_attach (table, scalebutton, column, column + 1, row, row + 1,                     GTK_SHRINK, GTK_SHRINK, 0, 0);    gtk_widget_show (scalebutton); }  */
end_comment

begin_comment
comment|/* GtkWidget * gimp_paint_options_gui (GimpToolOptions *tool_options) {    GObject          *config  = G_OBJECT (tool_options);   GimpPaintOptions *options = GIMP_PAINT_OPTIONS (tool_options);   GtkWidget        *vbox    = gimp_tool_options_gui (tool_options);   GtkWidget        *frame;   GtkWidget        *table;   GtkWidget        *menu;   GtkWidget        *label;   GtkWidget        *button;   GtkWidget        *incremental_toggle = NULL;   gint              table_row          = 0;   gint              n_dynamics         = 0;   GtkWidget        *dynamics_labels[7];   GType             tool_type; } */
end_comment

end_unit

