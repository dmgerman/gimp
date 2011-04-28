begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpchainbutton.h  * Copyright (C) 1999-2000 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * This implements a widget derived from GtkTable that visualizes  * it's state with two different pixmaps showing a closed and a  * broken chain. It's intented to be used with the GimpSizeEntry  * widget. The usage is quite similar to the one the GtkToggleButton  * provides.  */
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
name|__GIMP_CHAIN_BUTTON_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHAIN_BUTTON_H__
define|#
directive|define
name|__GIMP_CHAIN_BUTTON_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_CHAIN_BUTTON
define|#
directive|define
name|GIMP_TYPE_CHAIN_BUTTON
value|(gimp_chain_button_get_type ())
end_define

begin_define
DECL|macro|GIMP_CHAIN_BUTTON (obj)
define|#
directive|define
name|GIMP_CHAIN_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CHAIN_BUTTON, GimpChainButton))
end_define

begin_define
DECL|macro|GIMP_CHAIN_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_CHAIN_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CHAIN_BUTTON, GimpChainButtonClass))
end_define

begin_define
DECL|macro|GIMP_IS_CHAIN_BUTTON (obj)
define|#
directive|define
name|GIMP_IS_CHAIN_BUTTON
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CHAIN_BUTTON))
end_define

begin_define
DECL|macro|GIMP_IS_CHAIN_BUTTON_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CHAIN_BUTTON_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CHAIN_BUTTON))
end_define

begin_define
DECL|macro|GIMP_CHAIN_BUTTON_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CHAIN_BUTTON_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CHAIN_BUTTON, GimpChainButtonClass))
end_define

begin_typedef
DECL|typedef|GimpChainButtonClass
typedef|typedef
name|struct
name|_GimpChainButtonClass
name|GimpChainButtonClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpChainButton
struct|struct
name|_GimpChainButton
block|{
DECL|member|parent_instance
name|GtkTable
name|parent_instance
decl_stmt|;
DECL|member|position
name|GimpChainPosition
name|position
decl_stmt|;
DECL|member|active
name|gboolean
name|active
decl_stmt|;
DECL|member|button
name|GtkWidget
modifier|*
name|button
decl_stmt|;
DECL|member|line1
name|GtkWidget
modifier|*
name|line1
decl_stmt|;
DECL|member|line2
name|GtkWidget
modifier|*
name|line2
decl_stmt|;
DECL|member|image
name|GtkWidget
modifier|*
name|image
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpChainButtonClass
struct|struct
name|_GimpChainButtonClass
block|{
DECL|member|parent_class
name|GtkTableClass
name|parent_class
decl_stmt|;
DECL|member|toggled
name|void
function_decl|(
modifier|*
name|toggled
function_decl|)
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
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
name|gimp_chain_button_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_chain_button_new
parameter_list|(
name|GimpChainPosition
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_chain_button_set_active
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_chain_button_get_active
parameter_list|(
name|GimpChainButton
modifier|*
name|button
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
comment|/* __GIMP_CHAIN_BUTTON_H__ */
end_comment

end_unit

