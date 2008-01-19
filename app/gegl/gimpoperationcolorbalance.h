begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoperationcolorbalance.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_COLOR_BALANCE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_COLOR_BALANCE_H__
define|#
directive|define
name|__GIMP_OPERATION_COLOR_BALANCE_H__
end_define

begin_include
include|#
directive|include
file|<operation/gegl-operation-point-filter.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_OPERATION_COLOR_BALANCE
define|#
directive|define
name|GIMP_TYPE_OPERATION_COLOR_BALANCE
value|(gimp_operation_color_balance_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_COLOR_BALANCE (obj)
define|#
directive|define
name|GIMP_OPERATION_COLOR_BALANCE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_COLOR_BALANCE, GimpOperationColorBalance))
end_define

begin_define
DECL|macro|GIMP_OPERATION_COLOR_BALANCE_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_COLOR_BALANCE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_COLOR_BALANCE, GimpOperationColorBalanceClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_COLOR_BALANCE (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_COLOR_BALANCE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_COLOR_BALANCE))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_COLOR_BALANCE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_COLOR_BALANCE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_COLOR_BALANCE))
end_define

begin_define
DECL|macro|GIMP_OPERATION_COLOR_BALANCE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_COLOR_BALANCE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_COLOR_BALANCE, GimpOperationColorBalanceClass))
end_define

begin_typedef
DECL|typedef|GimpOperationColorBalanceClass
typedef|typedef
name|struct
name|_GimpOperationColorBalanceClass
name|GimpOperationColorBalanceClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationColorBalance
struct|struct
name|_GimpOperationColorBalance
block|{
DECL|member|parent_instance
name|GeglOperationPointFilter
name|parent_instance
decl_stmt|;
DECL|member|range
name|GimpTransferMode
name|range
decl_stmt|;
DECL|member|cyan_red
name|gdouble
name|cyan_red
index|[
literal|3
index|]
decl_stmt|;
DECL|member|magenta_green
name|gdouble
name|magenta_green
index|[
literal|3
index|]
decl_stmt|;
DECL|member|yellow_blue
name|gdouble
name|yellow_blue
index|[
literal|3
index|]
decl_stmt|;
DECL|member|preserve_luminosity
name|gboolean
name|preserve_luminosity
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationColorBalanceClass
struct|struct
name|_GimpOperationColorBalanceClass
block|{
DECL|member|parent_class
name|GeglOperationPointFilterClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_color_balance_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OPERATION_COLOR_BALANCE_H__ */
end_comment

end_unit

