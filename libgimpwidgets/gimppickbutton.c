begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppickbutton.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on gtk+/gtk/gtkcolorsel.c  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcairo-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpui.h"
end_include

begin_include
include|#
directive|include
file|"gimpicons.h"
end_include

begin_include
include|#
directive|include
file|"gimppickbutton.h"
end_include

begin_include
include|#
directive|include
file|"gimppickbutton-default.h"
end_include

begin_include
include|#
directive|include
file|"gimppickbutton-kwin.h"
end_include

begin_include
include|#
directive|include
file|"gimppickbutton-private.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
end_ifdef

begin_include
include|#
directive|include
file|"gimppickbutton-quartz.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimppickbutton  * @title: GimpPickButton  * @short_description: Widget to pick a color from screen.  *  * #GimpPickButton is a specialized button. When clicked, it changes  * the cursor to a color-picker pipette and allows the user to pick a  * color from any point on the screen.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon28dc2bd00103
block|{
DECL|enumerator|COLOR_PICKED
name|COLOR_PICKED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_pick_button_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pick_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpPickButton
argument_list|,
argument|gimp_pick_button
argument_list|,
argument|GTK_TYPE_BUTTON
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_pick_button_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|pick_button_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_pick_button_class_init (GimpPickButtonClass * klass)
name|gimp_pick_button_class_init
parameter_list|(
name|GimpPickButtonClass
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
name|GtkButtonClass
modifier|*
name|button_class
init|=
name|GTK_BUTTON_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
comment|/**    * GimpPickButton::color-picked:    * @gimppickbutton: the object which received the signal.    * @arg1: pointer to a #GimpRGB structure that holds the picked color    *    * This signal is emitted when the user has picked a color.    **/
name|pick_button_signals
index|[
name|COLOR_PICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"color-picked"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpPickButtonClass
argument_list|,
name|color_picked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_pick_button_dispose
expr_stmt|;
name|button_class
operator|->
name|clicked
operator|=
name|gimp_pick_button_clicked
expr_stmt|;
name|klass
operator|->
name|color_picked
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pick_button_init (GimpPickButton * button)
name|gimp_pick_button_init
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|button
operator|->
name|priv
operator|=
name|gimp_pick_button_get_instance_private
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|GIMP_ICON_COLOR_PICK_FROM_SCREEN
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|GTK_WIDGET
argument_list|(
name|button
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Click the eyedropper, then click a color "
literal|"anywhere on your screen to select that color."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pick_button_dispose (GObject * object)
name|gimp_pick_button_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPickButton
modifier|*
name|button
init|=
name|GIMP_PICK_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|cursor
condition|)
block|{
name|g_object_unref
argument_list|(
name|button
operator|->
name|priv
operator|->
name|cursor
argument_list|)
expr_stmt|;
name|button
operator|->
name|priv
operator|->
name|cursor
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|button
operator|->
name|priv
operator|->
name|grab_widget
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|button
operator|->
name|priv
operator|->
name|grab_widget
argument_list|)
expr_stmt|;
name|button
operator|->
name|priv
operator|->
name|grab_widget
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pick_button_clicked (GtkButton * button)
name|gimp_pick_button_clicked
parameter_list|(
name|GtkButton
modifier|*
name|button
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|GDK_WINDOWING_QUARTZ
name|_gimp_pick_button_quartz_pick
argument_list|(
name|GIMP_PICK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
else|#
directive|else
if|if
condition|(
name|_gimp_pick_button_kwin_available
argument_list|()
condition|)
name|_gimp_pick_button_kwin_pick
argument_list|(
name|GIMP_PICK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|_gimp_pick_button_default_pick
argument_list|(
name|GIMP_PICK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**  * gimp_pick_button_new:  *  * Creates a new #GimpPickButton widget.  *  * Returns: A new #GimpPickButton widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_pick_button_new (void)
name|gimp_pick_button_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PICK_BUTTON
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

