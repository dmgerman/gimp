begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__LAYER_ADD_MASK_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__LAYER_ADD_MASK_DIALOG_H__
define|#
directive|define
name|__LAYER_ADD_MASK_DIALOG_H__
end_define

begin_typedef
DECL|typedef|LayerAddMaskDialog
typedef|typedef
name|struct
name|_LayerAddMaskDialog
name|LayerAddMaskDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_LayerAddMaskDialog
struct|struct
name|_LayerAddMaskDialog
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|layer
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
DECL|member|add_mask_type
name|GimpAddMaskType
name|add_mask_type
decl_stmt|;
DECL|member|channel
name|GimpChannel
modifier|*
name|channel
decl_stmt|;
DECL|member|invert
name|gboolean
name|invert
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|LayerAddMaskDialog
modifier|*
name|layer_add_mask_dialog_new
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpAddMaskType
name|add_mask_type
parameter_list|,
name|gboolean
name|invert
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __LAYER_ADD_MASK_DIALOG_H__ */
end_comment

end_unit

