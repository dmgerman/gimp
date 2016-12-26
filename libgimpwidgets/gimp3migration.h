begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp3migration.h  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_WIDGETS_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_WIDGETS_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpwidgets/gimpwidgets.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_3_MIGRATION_H__
end_ifndef

begin_define
DECL|macro|__GIMP_3_MIGRATION_H__
define|#
directive|define
name|__GIMP_3_MIGRATION_H__
end_define

begin_comment
comment|/* This file is evil. Its purpose is to keep GIMP's gtk3-port branch  * manageable, and contains functions that are only in GTK+ 3.x but  * are *not* in GTK+ 2.x. Please just ignore the uglyness and move  * along. This file will be removed in GIMP 3.  */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_box_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|,
name|gint
name|spacing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_button_box_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_paned_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_scale_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|,
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_scrollbar_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|,
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gtk_separator_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon294796840103
block|{
DECL|enumerator|GDK_MODIFIER_INTENT_PRIMARY_ACCELERATOR
name|GDK_MODIFIER_INTENT_PRIMARY_ACCELERATOR
block|,
DECL|enumerator|GDK_MODIFIER_INTENT_CONTEXT_MENU
name|GDK_MODIFIER_INTENT_CONTEXT_MENU
block|,
DECL|enumerator|GDK_MODIFIER_INTENT_EXTEND_SELECTION
name|GDK_MODIFIER_INTENT_EXTEND_SELECTION
block|,
DECL|enumerator|GDK_MODIFIER_INTENT_MODIFY_SELECTION
name|GDK_MODIFIER_INTENT_MODIFY_SELECTION
block|,
DECL|enumerator|GDK_MODIFIER_INTENT_NO_TEXT_INPUT
name|GDK_MODIFIER_INTENT_NO_TEXT_INPUT
DECL|typedef|GdkModifierIntent
block|}
name|GdkModifierIntent
typedef|;
end_typedef

begin_function_decl
name|gboolean
name|gdk_event_triggers_context_menu
parameter_list|(
specifier|const
name|GdkEvent
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkModifierType
name|gdk_keymap_get_modifier_mask
parameter_list|(
name|GdkKeymap
modifier|*
name|keymap
parameter_list|,
name|GdkModifierIntent
name|intent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkModifierType
name|gtk_widget_get_modifier_mask
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierIntent
name|intent
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gdk_cairo_get_clip_rectangle
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GdkRectangle
modifier|*
name|rect
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gdk_screen_get_monitor_workarea
parameter_list|(
name|GdkScreen
modifier|*
name|screen
parameter_list|,
name|gint
name|monitor_num
parameter_list|,
name|GdkRectangle
modifier|*
name|dest
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_label_set_xalign
parameter_list|(
name|GtkLabel
modifier|*
name|label
parameter_list|,
name|gfloat
name|xalign
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gtk_label_get_xalign
parameter_list|(
name|GtkLabel
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gtk_label_set_yalign
parameter_list|(
name|GtkLabel
modifier|*
name|label
parameter_list|,
name|gfloat
name|yalign
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gfloat
name|gtk_label_get_yalign
parameter_list|(
name|GtkLabel
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_3_MIGRATION_H__ */
end_comment

end_unit

