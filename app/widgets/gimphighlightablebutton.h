begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphighlightablebutton.h  * Copyright (C) 2018 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_HIGHLIGHTABLE_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_HIGHLIGHTABLE_BUTTON_H__
define|#
directive|define
name|__GIMP_HIGHLIGHTABLE_BUTTON_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_HIGHLIGHTABLE_BUTTON
define|#
directive|define
name|GIMP_TYPE_HIGHLIGHTABLE_BUTTON
value|(gimp_highlightable_button_get_type ())
end_define

begin_define
DECL|macro|GIMP_HIGHLIGHTABLE_BUTTON (obj)
define|#
directive|define
name|GIMP_HIGHLIGHTABLE_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_HIGHLIGHTABLE_BUTTON, GimpHighlightableButton))
end_define

begin_define
DECL|macro|GIMP_HIGHLIGHTABLE_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_HIGHLIGHTABLE_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_HIGHLIGHTABLE_BUTTON, GimpHighlightableButtonClass))
end_define

begin_define
DECL|macro|GIMP_IS_HIGHLIGHTABLE_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_HIGHLIGHTABLE_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_HIGHLIGHTABLE_BUTTON))
end_define

begin_define
DECL|macro|GIMP_IS_HIGHLIGHTABLE_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_HIGHLIGHTABLE_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_HIGHLIGHTABLE_BUTTON))
end_define

begin_define
DECL|macro|GIMP_HIGHLIGHTABLE_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GIMP_HIGHLIGHTABLE_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_HIGHLIGHTABLE_BUTTON, GimpHighlightableButtonClass))
end_define

begin_typedef
DECL|typedef|GimpHighlightableButtonPrivate
typedef|typedef
name|struct
name|_GimpHighlightableButtonPrivate
name|GimpHighlightableButtonPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHighlightableButtonClass
typedef|typedef
name|struct
name|_GimpHighlightableButtonClass
name|GimpHighlightableButtonClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpHighlightableButton
struct|struct
name|_GimpHighlightableButton
block|{
DECL|member|parent_instance
name|GimpButton
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpHighlightableButtonPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpHighlightableButtonClass
struct|struct
name|_GimpHighlightableButtonClass
block|{
DECL|member|parent_class
name|GimpButtonClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_highlightable_button_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_highlightable_button_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_highlightable_button_set_highlight
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|,
name|gboolean
name|highlight
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_highlightable_button_get_highlight
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_highlightable_button_set_highlight_color
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_highlightable_button_get_highlight_color
parameter_list|(
name|GimpHighlightableButton
modifier|*
name|button
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_HIGHLIGHTABLE_BUTTON_H__ */
end_comment

end_unit

