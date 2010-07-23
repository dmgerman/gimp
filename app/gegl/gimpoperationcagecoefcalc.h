begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpoperationcagecoefcalc.h  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_CAGE_COEF_CALC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_CAGE_COEF_CALC_H__
define|#
directive|define
name|__GIMP_OPERATION_CAGE_COEF_CALC_H__
end_define

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|<operation/gegl-operation-source.h>
end_include

begin_enum
enum|enum
DECL|enum|__anon2accc2db0103
block|{
DECL|enumerator|GIMP_OPERATION_CAGE_COEF_CALC_PROP_0
name|GIMP_OPERATION_CAGE_COEF_CALC_PROP_0
block|,
DECL|enumerator|GIMP_OPERATION_CAGE_COEF_CALC_PROP_CONFIG
name|GIMP_OPERATION_CAGE_COEF_CALC_PROP_CONFIG
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TYPE_OPERATION_CAGE_COEF_CALC
define|#
directive|define
name|GIMP_TYPE_OPERATION_CAGE_COEF_CALC
value|(gimp_operation_cage_coef_calc_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_CAGE_COEF_CALC (obj)
define|#
directive|define
name|GIMP_OPERATION_CAGE_COEF_CALC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_CAGE_COEF_CALC, GimpOperationCageCoefCalc))
end_define

begin_define
DECL|macro|GIMP_OPERATION_CAGE_COEF_CALC_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_CAGE_COEF_CALC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_CAGE_COEF_CALC, GimpOperationCageCoefCalcClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_CAGE_COEF_CALC (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_CAGE_COEF_CALC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_CAGE_COEF_CALC))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_CAGE_COEF_CALC_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_CAGE_COEF_CALC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_CAGE_COEF_CALC))
end_define

begin_define
DECL|macro|GIMP_OPERATION_CAGE_COEF_CALC_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_CAGE_COEF_CALC_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_CAGE_COEF_CALC, GimpOperationCageCoefCalcClass))
end_define

begin_typedef
DECL|typedef|GimpOperationCageCoefCalcClass
typedef|typedef
name|struct
name|_GimpOperationCageCoefCalcClass
name|GimpOperationCageCoefCalcClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationCageCoefCalc
struct|struct
name|_GimpOperationCageCoefCalc
block|{
DECL|member|parent_instance
name|GeglOperationSource
name|parent_instance
decl_stmt|;
DECL|member|config
name|GimpCageConfig
modifier|*
name|config
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationCageCoefCalcClass
struct|struct
name|_GimpOperationCageCoefCalcClass
block|{
DECL|member|parent_class
name|GeglOperationSourceClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_cage_coef_calc_get_type
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
comment|/* __GIMP_OPERATION_CAGE_COEF_CALC_H__ */
end_comment

end_unit

