begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GTK - The GIMP Toolkit  * Copyright (C) 2005 Ronald S. Bultje  * Copyright (C) 2006, 2007 Christian Persch  * Copyright (C) 2006 Jan Arne Petersen  * Copyright (C) 2007 Red Hat, Inc.  *  * Authors:  * - Ronald S. Bultje<rbultje@ronald.bitfreak.net>  * - Bastien Nocera<bnocera@redhat.com>  * - Jan Arne Petersen<jpetersen@jpetersen.org>  * - Christian Persch<chpe@svn.gnome.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * Modified by the GTK+ Team and others 2007.  See the AUTHORS  * file for a list of people on the GTK+ Team.  See the ChangeLog  * files for a list of changes.  These files are distributed with  * GTK+ at ftp://ftp.gtk.org/pub/gtk/.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GTK_SCALE_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GTK_SCALE_BUTTON_H__
define|#
directive|define
name|__GIMP_GTK_SCALE_BUTTON_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GTK_TYPE_SCALE_BUTTON
define|#
directive|define
name|GTK_TYPE_SCALE_BUTTON
value|(gimp_gtk_scale_button_get_type ())
end_define

begin_define
DECL|macro|GTK_SCALE_BUTTON (obj)
define|#
directive|define
name|GTK_SCALE_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCALE_BUTTON, GtkScaleButton))
end_define

begin_define
DECL|macro|GTK_SCALE_BUTTON_CLASS (klass)
define|#
directive|define
name|GTK_SCALE_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SCALE_BUTTON, GtkScaleButtonClass))
end_define

begin_define
DECL|macro|GTK_IS_SCALE_BUTTON (obj)
define|#
directive|define
name|GTK_IS_SCALE_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCALE_BUTTON))
end_define

begin_define
DECL|macro|GTK_IS_SCALE_BUTTON_CLASS (klass)
define|#
directive|define
name|GTK_IS_SCALE_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SCALE_BUTTON))
end_define

begin_define
DECL|macro|GTK_SCALE_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GTK_SCALE_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SCALE_BUTTON, GtkScaleButtonClass))
end_define

begin_typedef
DECL|typedef|GtkScaleButton
typedef|typedef
name|struct
name|_GtkScaleButton
name|GtkScaleButton
typedef|;
end_typedef

begin_typedef
DECL|typedef|GtkScaleButtonClass
typedef|typedef
name|struct
name|_GtkScaleButtonClass
name|GtkScaleButtonClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GtkScaleButtonPrivate
typedef|typedef
name|struct
name|_GtkScaleButtonPrivate
name|GtkScaleButtonPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GtkScaleButton
struct|struct
name|_GtkScaleButton
block|{
DECL|member|parent
name|GtkButton
name|parent
decl_stmt|;
name|GtkWidget
modifier|*
name|GSEAL
parameter_list|(
name|plus_button
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|GSEAL
parameter_list|(
name|minus_button
parameter_list|)
function_decl|;
comment|/*< private>*/
name|GtkScaleButtonPrivate
modifier|*
name|GSEAL
parameter_list|(
name|priv
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GtkScaleButtonClass
struct|struct
name|_GtkScaleButtonClass
block|{
DECL|member|parent_class
name|GtkButtonClass
name|parent_class
decl_stmt|;
comment|/* signals */
DECL|member|value_changed
name|void
function_decl|(
modifier|*
name|value_changed
function_decl|)
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gtk_reserved1
name|void
function_decl|(
modifier|*
name|_gtk_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved2
name|void
function_decl|(
modifier|*
name|_gtk_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved3
name|void
function_decl|(
modifier|*
name|_gtk_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gtk_reserved4
name|void
function_decl|(
modifier|*
name|_gtk_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_gtk_scale_button_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_gtk_scale_button_new
parameter_list|(
name|GtkIconSize
name|size
parameter_list|,
name|gdouble
name|min
parameter_list|,
name|gdouble
name|max
parameter_list|,
name|gdouble
name|step
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|icons
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gtk_scale_button_set_icons
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|icons
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_gtk_scale_button_get_value
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gtk_scale_button_set_value
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|,
name|gdouble
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkAdjustment
modifier|*
name|gimp_gtk_scale_button_get_adjustment
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gtk_scale_button_set_adjustment
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|,
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkOrientation
name|gimp_gtk_scale_button_get_orientation
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_gtk_scale_button_set_orientation
parameter_list|(
name|GtkScaleButton
modifier|*
name|button
parameter_list|,
name|GtkOrientation
name|orientation
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
comment|/* __GTK_SCALE_BUTTON_H__ */
end_comment

end_unit

