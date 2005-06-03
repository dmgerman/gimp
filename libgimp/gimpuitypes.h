begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpuitypes.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_UI_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_UI_TYPES_H__
define|#
directive|define
name|__GIMP_UI_TYPES_H__
end_define

begin_include
include|#
directive|include
file|<libgimpwidgets/gimpwidgetstypes.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpAspectPreview
typedef|typedef
name|struct
name|_GimpAspectPreview
name|GimpAspectPreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawablePreview
typedef|typedef
name|struct
name|_GimpDrawablePreview
name|GimpDrawablePreview
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpProgressBar
typedef|typedef
name|struct
name|_GimpProgressBar
name|GimpProgressBar
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpImageComboBox
typedef|typedef
name|struct
name|_GimpImageComboBox
name|GimpImageComboBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawableComboBox
typedef|typedef
name|struct
name|_GimpDrawableComboBox
name|GimpDrawableComboBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannelComboBox
typedef|typedef
name|struct
name|_GimpChannelComboBox
name|GimpChannelComboBox
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerComboBox
typedef|typedef
name|struct
name|_GimpLayerComboBox
name|GimpLayerComboBox
typedef|;
end_typedef

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_UI_TYPES_H__ */
end_comment

end_unit

