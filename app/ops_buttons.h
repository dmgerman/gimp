begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__OPS_BUTTONS_H__
end_ifndef

begin_define
DECL|macro|__OPS_BUTTONS_H__
define|#
directive|define
name|__OPS_BUTTONS_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29bee3ba0103
block|{
DECL|enumerator|OPS_BUTTON_MODIFIER_NONE
name|OPS_BUTTON_MODIFIER_NONE
block|,
DECL|enumerator|OPS_BUTTON_MODIFIER_SHIFT
name|OPS_BUTTON_MODIFIER_SHIFT
block|,
DECL|enumerator|OPS_BUTTON_MODIFIER_CTRL
name|OPS_BUTTON_MODIFIER_CTRL
block|,
DECL|enumerator|OPS_BUTTON_MODIFIER_ALT
name|OPS_BUTTON_MODIFIER_ALT
block|,
DECL|enumerator|OPS_BUTTON_MODIFIER_SHIFT_CTRL
name|OPS_BUTTON_MODIFIER_SHIFT_CTRL
block|,
DECL|enumerator|OPS_BUTTON_MODIFIER_LAST
name|OPS_BUTTON_MODIFIER_LAST
DECL|typedef|OpsButtonModifier
block|}
name|OpsButtonModifier
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon29bee3ba0203
block|{
DECL|enumerator|OPS_BUTTON_NORMAL
name|OPS_BUTTON_NORMAL
block|,
DECL|enumerator|OPS_BUTTON_RADIO
name|OPS_BUTTON_RADIO
DECL|typedef|OpsButtonType
block|}
name|OpsButtonType
typedef|;
end_typedef

begin_typedef
DECL|typedef|OpsButton
typedef|typedef
name|struct
name|_OpsButton
name|OpsButton
typedef|;
end_typedef

begin_struct
DECL|struct|_OpsButton
struct|struct
name|_OpsButton
block|{
DECL|member|xpm_data
name|gchar
modifier|*
modifier|*
name|xpm_data
decl_stmt|;
comment|/*  xpm data for the button  */
DECL|member|callback
name|GtkSignalFunc
name|callback
decl_stmt|;
comment|/*  callback function        */
DECL|member|ext_callbacks
name|GtkSignalFunc
modifier|*
name|ext_callbacks
decl_stmt|;
comment|/*  callback functions when 				   *  modifiers are pressed    */
DECL|member|tooltip
name|gchar
modifier|*
name|tooltip
decl_stmt|;
DECL|member|private_tip
name|gchar
modifier|*
name|private_tip
decl_stmt|;
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
comment|/*  the button widget        */
DECL|member|modifier
name|gint
name|modifier
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/* Function declarations */
end_comment

begin_function_decl
name|GtkWidget
modifier|*
name|ops_button_box_new
parameter_list|(
name|OpsButton
modifier|*
name|ops_button
parameter_list|,
name|OpsButtonType
name|ops_type
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __OPS_BUTTONS_H__ */
end_comment

end_unit

