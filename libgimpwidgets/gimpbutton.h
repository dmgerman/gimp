begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbutton.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BUTTON_H__
define|#
directive|define
name|__GIMP_BUTTON_H__
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
comment|/* For information look into the C source or the html documentation */
DECL|macro|GIMP_TYPE_BUTTON
define|#
directive|define
name|GIMP_TYPE_BUTTON
value|(gimp_button_get_type ())
DECL|macro|GIMP_BUTTON (obj)
define|#
directive|define
name|GIMP_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_BUTTON, GimpButton))
DECL|macro|GIMP_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BUTTON, GimpButtonClass))
DECL|macro|GIMP_IS_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_BUTTON))
DECL|macro|GIMP_IS_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BUTTON))
DECL|typedef|GimpButtonClass
typedef|typedef
name|struct
name|_GimpButtonClass
name|GimpButtonClass
typedef|;
DECL|struct|_GimpButton
struct|struct
name|_GimpButton
block|{
DECL|member|parent_instance
name|GtkButton
name|parent_instance
decl_stmt|;
comment|/*< private>*/
DECL|member|press_state
name|guint
name|press_state
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpButtonClass
struct|struct
name|_GimpButtonClass
block|{
DECL|member|parent_class
name|GtkButtonClass
name|parent_class
decl_stmt|;
DECL|member|extended_clicked
name|void
function_decl|(
modifier|*
name|extended_clicked
function_decl|)
parameter_list|(
name|GimpButton
modifier|*
name|preview
parameter_list|,
name|guint
name|modifier_state
parameter_list|)
function_decl|;
block|}
struct|;
name|GtkType
name|gimp_button_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GtkWidget
modifier|*
name|gimp_button_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BUTTON_H__ */
end_comment

end_unit

