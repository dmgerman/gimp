begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppickbutton.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on gtk-2-0/gtk/gtkcolorsel.c  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PICK_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PICK_BUTTON_H__
define|#
directive|define
name|__GIMP_PICK_BUTTON_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkbutton.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_PICK_BUTTON
define|#
directive|define
name|GIMP_TYPE_PICK_BUTTON
value|(gimp_pick_button_get_type ())
end_define

begin_define
DECL|macro|GIMP_PICK_BUTTON (obj)
define|#
directive|define
name|GIMP_PICK_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PICK_BUTTON, GimpPickButton))
end_define

begin_define
DECL|macro|GIMP_PICK_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_PICK_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PICK_BUTTON, GimpPickButtonClass))
end_define

begin_define
DECL|macro|GIMP_IS_PICK_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_PICK_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PICK_BUTTON))
end_define

begin_define
DECL|macro|GIMP_IS_PICK_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PICK_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PICK_BUTTON))
end_define

begin_define
DECL|macro|GIMP_PICK_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PICK_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PICK_BUTTON, GimpPickButtonClass))
end_define

begin_typedef
DECL|typedef|GimpPickButtonClass
typedef|typedef
name|struct
name|_GimpPickButtonClass
name|GimpPickButtonClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPickButton
struct|struct
name|_GimpPickButton
block|{
DECL|member|parent_instance
name|GtkButton
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|cursor
name|GdkCursor
modifier|*
name|cursor
decl_stmt|;
DECL|member|grab_widget
name|GtkWidget
modifier|*
name|grab_widget
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPickButtonClass
struct|struct
name|_GimpPickButtonClass
block|{
DECL|member|parent_class
name|GtkButtonClass
name|parent_class
decl_stmt|;
DECL|member|color_picked
name|void
function_decl|(
modifier|*
name|color_picked
function_decl|)
parameter_list|(
name|GimpPickButton
modifier|*
name|button
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_pick_button_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_pick_button_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PICK_BUTTON_H__ */
end_comment

end_unit

