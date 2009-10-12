begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamics.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdynamicsoutput.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"gimpheal.h"
end_include

begin_include
include|#
directive|include
file|"gimpsourceoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* NOTES:  *  * I had the code working for healing from a pattern, but the results look  * terrible and I can't see a use for it right now.  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_heal_start
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_heal_substitute_0_for_1
parameter_list|(
name|PixelRegion
modifier|*
name|pr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_heal_divide
parameter_list|(
name|PixelRegion
modifier|*
name|topPR
parameter_list|,
name|PixelRegion
modifier|*
name|bottomPR
parameter_list|,
name|gdouble
modifier|*
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_heal_multiply
parameter_list|(
name|gdouble
modifier|*
name|first
parameter_list|,
name|PixelRegion
modifier|*
name|secondPR
parameter_list|,
name|PixelRegion
modifier|*
name|resultPR
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_heal_laplace_iteration
parameter_list|(
name|gdouble
modifier|*
name|matrix
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|depth
parameter_list|,
name|gint
name|width
parameter_list|,
name|gdouble
modifier|*
name|solution
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_heal_laplace_loop
parameter_list|(
name|gdouble
modifier|*
name|matrix
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|depth
parameter_list|,
name|gint
name|width
parameter_list|,
name|gdouble
modifier|*
name|solution
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|PixelRegion
modifier|*
name|gimp_heal_region
parameter_list|(
name|PixelRegion
modifier|*
name|tempPR
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|TempBuf
modifier|*
name|mask_buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_heal_motion
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|TempBuf
modifier|*
name|paint_area
parameter_list|,
name|gint
name|paint_area_offset_x
parameter_list|,
name|gint
name|paint_area_offset_y
parameter_list|,
name|gint
name|paint_area_width
parameter_list|,
name|gint
name|paint_area_height
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpHeal,gimp_heal,GIMP_TYPE_SOURCE_CORE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpHeal
argument_list|,
argument|gimp_heal
argument_list|,
argument|GIMP_TYPE_SOURCE_CORE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_heal_parent_class
end_define

begin_function
name|void
name|gimp_heal_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_HEAL
argument_list|,
name|GIMP_TYPE_SOURCE_OPTIONS
argument_list|,
literal|"gimp-heal"
argument_list|,
name|_
argument_list|(
literal|"Heal"
argument_list|)
argument_list|,
literal|"gimp-tool-heal"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_heal_class_init (GimpHealClass * klass)
name|gimp_heal_class_init
parameter_list|(
name|GimpHealClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpSourceCoreClass
modifier|*
name|source_core_class
init|=
name|GIMP_SOURCE_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|paint_core_class
operator|->
name|start
operator|=
name|gimp_heal_start
expr_stmt|;
name|source_core_class
operator|->
name|motion
operator|=
name|gimp_heal_motion
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_heal_init (GimpHeal * heal)
name|gimp_heal_init
parameter_list|(
name|GimpHeal
modifier|*
name|heal
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_heal_start (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,GError ** error)
name|gimp_heal_start
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpSourceCore
modifier|*
name|source_core
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|start
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|coords
argument_list|,
name|error
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
operator|!
name|source_core
operator|->
name|set_source
operator|&&
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Healing does not operate on indexed layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  * Substitute any zeros in the input PixelRegion for ones.  This is needed by  * the algorithm to avoid division by zero, and to get a more realistic image  * since multiplying by zero is often incorrect (i.e., healing from a dark to  * a light region will have incorrect spots of zero)  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_heal_substitute_0_for_1 (PixelRegion * pr)
name|gimp_heal_substitute_0_for_1
parameter_list|(
name|PixelRegion
modifier|*
name|pr
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|gint
name|height
init|=
name|pr
operator|->
name|h
decl_stmt|;
name|gint
name|width
init|=
name|pr
operator|->
name|w
decl_stmt|;
name|gint
name|depth
init|=
name|pr
operator|->
name|bytes
decl_stmt|;
name|guchar
modifier|*
name|pr_data
init|=
name|pr
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|p
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|=
name|pr_data
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|depth
condition|;
name|k
operator|++
control|)
block|{
if|if
condition|(
name|p
index|[
name|k
index|]
operator|==
literal|0
condition|)
name|p
index|[
name|k
index|]
operator|=
literal|1
expr_stmt|;
block|}
name|p
operator|+=
name|depth
expr_stmt|;
block|}
name|pr_data
operator|+=
name|pr
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  * Divide topPR by bottomPR and store the result as a double  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_heal_divide (PixelRegion * topPR,PixelRegion * bottomPR,gdouble * result)
name|gimp_heal_divide
parameter_list|(
name|PixelRegion
modifier|*
name|topPR
parameter_list|,
name|PixelRegion
modifier|*
name|bottomPR
parameter_list|,
name|gdouble
modifier|*
name|result
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|gint
name|height
init|=
name|topPR
operator|->
name|h
decl_stmt|;
name|gint
name|width
init|=
name|topPR
operator|->
name|w
decl_stmt|;
name|gint
name|depth
init|=
name|topPR
operator|->
name|bytes
decl_stmt|;
name|guchar
modifier|*
name|t_data
init|=
name|topPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|b_data
init|=
name|bottomPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|t
decl_stmt|;
name|guchar
modifier|*
name|b
decl_stmt|;
name|gdouble
modifier|*
name|r
init|=
name|result
decl_stmt|;
name|g_assert
argument_list|(
name|topPR
operator|->
name|bytes
operator|==
name|bottomPR
operator|->
name|bytes
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
control|)
block|{
name|t
operator|=
name|t_data
expr_stmt|;
name|b
operator|=
name|b_data
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|depth
condition|;
name|k
operator|++
control|)
block|{
name|r
index|[
name|k
index|]
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|t
index|[
name|k
index|]
argument_list|)
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|b
index|[
name|k
index|]
argument_list|)
expr_stmt|;
block|}
name|t
operator|+=
name|depth
expr_stmt|;
name|b
operator|+=
name|depth
expr_stmt|;
name|r
operator|+=
name|depth
expr_stmt|;
block|}
name|t_data
operator|+=
name|topPR
operator|->
name|rowstride
expr_stmt|;
name|b_data
operator|+=
name|bottomPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  * multiply first by secondPR and store the result as a PixelRegion  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_heal_multiply (gdouble * first,PixelRegion * secondPR,PixelRegion * resultPR)
name|gimp_heal_multiply
parameter_list|(
name|gdouble
modifier|*
name|first
parameter_list|,
name|PixelRegion
modifier|*
name|secondPR
parameter_list|,
name|PixelRegion
modifier|*
name|resultPR
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|gint
name|height
init|=
name|secondPR
operator|->
name|h
decl_stmt|;
name|gint
name|width
init|=
name|secondPR
operator|->
name|w
decl_stmt|;
name|gint
name|depth
init|=
name|secondPR
operator|->
name|bytes
decl_stmt|;
name|guchar
modifier|*
name|s_data
init|=
name|secondPR
operator|->
name|data
decl_stmt|;
name|guchar
modifier|*
name|r_data
init|=
name|resultPR
operator|->
name|data
decl_stmt|;
name|gdouble
modifier|*
name|f
init|=
name|first
decl_stmt|;
name|guchar
modifier|*
name|s
decl_stmt|;
name|guchar
modifier|*
name|r
decl_stmt|;
name|g_assert
argument_list|(
name|secondPR
operator|->
name|bytes
operator|==
name|resultPR
operator|->
name|bytes
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
control|)
block|{
name|s
operator|=
name|s_data
expr_stmt|;
name|r
operator|=
name|r_data
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|depth
condition|;
name|k
operator|++
control|)
block|{
name|r
index|[
name|k
index|]
operator|=
operator|(
name|guchar
operator|)
name|CLAMP0255
argument_list|(
name|ROUND
argument_list|(
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|f
index|[
name|k
index|]
argument_list|)
operator|)
operator|*
operator|(
call|(
name|gdouble
call|)
argument_list|(
name|s
index|[
name|k
index|]
argument_list|)
operator|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|f
operator|+=
name|depth
expr_stmt|;
name|s
operator|+=
name|depth
expr_stmt|;
name|r
operator|+=
name|depth
expr_stmt|;
block|}
name|s_data
operator|+=
name|secondPR
operator|->
name|rowstride
expr_stmt|;
name|r_data
operator|+=
name|resultPR
operator|->
name|rowstride
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  * Perform one iteration of the laplace solver for matrix.  Store the  * result in solution and return the square of the cummulative error  * of the solution.  */
end_comment

begin_function
specifier|static
name|gdouble
DECL|function|gimp_heal_laplace_iteration (gdouble * matrix,gint height,gint depth,gint width,gdouble * solution,guchar * mask)
name|gimp_heal_laplace_iteration
parameter_list|(
name|gdouble
modifier|*
name|matrix
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|depth
parameter_list|,
name|gint
name|width
parameter_list|,
name|gdouble
modifier|*
name|solution
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|)
block|{
name|gint
name|rowstride
init|=
name|width
operator|*
name|depth
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|gdouble
name|tmp
decl_stmt|,
name|diff
decl_stmt|;
name|gdouble
name|err
init|=
literal|0.0
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|height
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|width
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
operator|(
literal|0
operator|==
operator|*
name|mask
operator|)
operator|||
operator|(
name|i
operator|==
literal|0
operator|)
operator|||
operator|(
name|i
operator|==
operator|(
name|height
operator|-
literal|1
operator|)
operator|)
operator|||
operator|(
name|j
operator|==
literal|0
operator|)
operator|||
operator|(
name|j
operator|==
operator|(
name|height
operator|-
literal|1
operator|)
operator|)
condition|)
block|{
comment|/* do nothing at the boundary or outside mask */
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|depth
condition|;
name|k
operator|++
control|)
operator|*
operator|(
name|solution
operator|+
name|k
operator|)
operator|=
operator|*
operator|(
name|matrix
operator|+
name|k
operator|)
expr_stmt|;
block|}
else|else
block|{
comment|/* calculate the mean of four neighbours for all color channels */
comment|/* v[i][j] = 0.45 * (v[i][j-1]+v[i][j+1]+v[i-1][j]+v[i+1][j]) */
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|depth
condition|;
name|k
operator|++
control|)
block|{
name|tmp
operator|=
operator|*
operator|(
name|solution
operator|+
name|k
operator|)
expr_stmt|;
operator|*
operator|(
name|solution
operator|+
name|k
operator|)
operator|=
literal|0.25
operator|*
operator|(
operator|*
operator|(
name|matrix
operator|-
name|depth
operator|+
name|k
operator|)
comment|/* west */
operator|+
operator|*
operator|(
name|matrix
operator|+
name|depth
operator|+
name|k
operator|)
comment|/* east */
operator|+
operator|*
operator|(
name|matrix
operator|-
name|rowstride
operator|+
name|k
operator|)
comment|/* north */
operator|+
operator|*
operator|(
name|matrix
operator|+
name|rowstride
operator|+
name|k
operator|)
operator|)
expr_stmt|;
comment|/* south */
name|diff
operator|=
operator|*
operator|(
name|solution
operator|+
name|k
operator|)
operator|-
name|tmp
expr_stmt|;
name|err
operator|+=
name|diff
operator|*
name|diff
expr_stmt|;
block|}
block|}
comment|/* advance pointers to data */
name|matrix
operator|+=
name|depth
expr_stmt|;
name|solution
operator|+=
name|depth
expr_stmt|;
name|mask
operator|++
expr_stmt|;
block|}
block|}
return|return
name|err
return|;
block|}
end_function

begin_comment
comment|/*  * Solve the laplace equation for matrix and store the result in solution.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_heal_laplace_loop (gdouble * matrix,gint height,gint depth,gint width,gdouble * solution,guchar * mask)
name|gimp_heal_laplace_loop
parameter_list|(
name|gdouble
modifier|*
name|matrix
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|depth
parameter_list|,
name|gint
name|width
parameter_list|,
name|gdouble
modifier|*
name|solution
parameter_list|,
name|guchar
modifier|*
name|mask
parameter_list|)
block|{
DECL|macro|EPSILON
define|#
directive|define
name|EPSILON
value|0.0001
DECL|macro|MAX_ITER
define|#
directive|define
name|MAX_ITER
value|500
name|gint
name|i
decl_stmt|;
comment|/* repeat until convergence or max iterations */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|MAX_ITER
condition|;
name|i
operator|++
control|)
block|{
name|gdouble
name|sqr_err
decl_stmt|;
comment|/* do one iteration and store the amount of error */
name|sqr_err
operator|=
name|gimp_heal_laplace_iteration
argument_list|(
name|matrix
argument_list|,
name|height
argument_list|,
name|depth
argument_list|,
name|width
argument_list|,
name|solution
argument_list|,
name|mask
argument_list|)
expr_stmt|;
comment|/* copy solution to matrix */
name|memcpy
argument_list|(
name|matrix
argument_list|,
name|solution
argument_list|,
name|width
operator|*
name|height
operator|*
name|depth
operator|*
sizeof|sizeof
argument_list|(
name|double
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|sqr_err
operator|<
name|SQR
argument_list|(
name|EPSILON
argument_list|)
condition|)
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  * Algorithm Design:  *  * T. Georgiev, "Image Reconstruction Invariant to Relighting", EUROGRAPHICS  * 2005, http://www.tgeorgiev.net/  */
end_comment

begin_function
specifier|static
name|PixelRegion
modifier|*
DECL|function|gimp_heal_region (PixelRegion * tempPR,PixelRegion * srcPR,TempBuf * mask_buf)
name|gimp_heal_region
parameter_list|(
name|PixelRegion
modifier|*
name|tempPR
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|TempBuf
modifier|*
name|mask_buf
parameter_list|)
block|{
name|gdouble
modifier|*
name|i_1
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|tempPR
operator|->
name|h
operator|*
name|tempPR
operator|->
name|bytes
operator|*
name|tempPR
operator|->
name|w
argument_list|)
decl_stmt|;
name|gdouble
modifier|*
name|i_2
init|=
name|g_new
argument_list|(
name|gdouble
argument_list|,
name|tempPR
operator|->
name|h
operator|*
name|tempPR
operator|->
name|bytes
operator|*
name|tempPR
operator|->
name|w
argument_list|)
decl_stmt|;
name|guchar
modifier|*
name|mask
init|=
name|temp_buf_get_data
argument_list|(
name|mask_buf
argument_list|)
decl_stmt|;
comment|/* substitute 0's for 1's for the division and multiplication operations that    * come later    */
name|gimp_heal_substitute_0_for_1
argument_list|(
name|srcPR
argument_list|)
expr_stmt|;
comment|/* divide tempPR by srcPR and store the result as a double in i_1 */
name|gimp_heal_divide
argument_list|(
name|tempPR
argument_list|,
name|srcPR
argument_list|,
name|i_1
argument_list|)
expr_stmt|;
comment|/* FIXME: is a faster implementation needed? */
name|gimp_heal_laplace_loop
argument_list|(
name|i_1
argument_list|,
name|tempPR
operator|->
name|h
argument_list|,
name|tempPR
operator|->
name|bytes
argument_list|,
name|tempPR
operator|->
name|w
argument_list|,
name|i_2
argument_list|,
name|mask
argument_list|)
expr_stmt|;
comment|/* multiply a double by srcPR and store in tempPR */
name|gimp_heal_multiply
argument_list|(
name|i_2
argument_list|,
name|srcPR
argument_list|,
name|tempPR
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|i_1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|i_2
argument_list|)
expr_stmt|;
return|return
name|tempPR
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_heal_motion (GimpSourceCore * source_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,const GimpCoords * coords,gdouble opacity,GimpPickable * src_pickable,PixelRegion * srcPR,gint src_offset_x,gint src_offset_y,TempBuf * paint_area,gint paint_area_offset_x,gint paint_area_offset_y,gint paint_area_width,gint paint_area_height)
name|gimp_heal_motion
parameter_list|(
name|GimpSourceCore
modifier|*
name|source_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|GimpPickable
modifier|*
name|src_pickable
parameter_list|,
name|PixelRegion
modifier|*
name|srcPR
parameter_list|,
name|gint
name|src_offset_x
parameter_list|,
name|gint
name|src_offset_y
parameter_list|,
name|TempBuf
modifier|*
name|paint_area
parameter_list|,
name|gint
name|paint_area_offset_x
parameter_list|,
name|gint
name|paint_area_offset_y
parameter_list|,
name|gint
name|paint_area_width
parameter_list|,
name|gint
name|paint_area_height
parameter_list|)
block|{
name|GimpPaintCore
modifier|*
name|paint_core
init|=
name|GIMP_PAINT_CORE
argument_list|(
name|source_core
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|TempBuf
modifier|*
name|src
decl_stmt|;
name|TempBuf
modifier|*
name|temp
decl_stmt|;
name|PixelRegion
name|origPR
decl_stmt|;
name|PixelRegion
name|tempPR
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|GimpImageType
name|src_type
decl_stmt|;
name|TempBuf
modifier|*
name|mask_buf
decl_stmt|;
name|gdouble
name|hardness
decl_stmt|;
name|gdouble
name|fade_point
init|=
name|gimp_paint_options_get_fade
argument_list|(
name|paint_options
argument_list|,
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|,
name|paint_core
operator|->
name|pixel_dist
argument_list|)
decl_stmt|;
name|hardness
operator|=
name|gimp_dynamics_output_get_linear_value
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
operator|->
name|dynamics
operator|->
name|hardness_output
argument_list|,
operator|*
name|coords
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
name|mask_buf
operator|=
name|gimp_brush_core_get_brush_mask
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|source_core
argument_list|)
argument_list|,
name|coords
argument_list|,
name|GIMP_BRUSH_HARD
argument_list|,
name|hardness
argument_list|)
expr_stmt|;
name|src_type
operator|=
name|gimp_pickable_get_image_type
argument_list|(
name|src_pickable
argument_list|)
expr_stmt|;
comment|/* we need the source area with alpha and we modify it, so make a copy */
name|src
operator|=
name|temp_buf_new
argument_list|(
name|srcPR
operator|->
name|w
argument_list|,
name|srcPR
operator|->
name|h
argument_list|,
name|GIMP_IMAGE_TYPE_BYTES
argument_list|(
name|GIMP_IMAGE_TYPE_WITH_ALPHA
argument_list|(
name|src_type
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|tempPR
argument_list|,
name|src
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|width
argument_list|,
name|src
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/*    * the effect of the following is to copy the contents of the source    * region to the "src" temp-buf, adding an alpha channel if necessary    */
if|if
condition|(
name|GIMP_IMAGE_TYPE_HAS_ALPHA
argument_list|(
name|src_type
argument_list|)
condition|)
name|copy_region
argument_list|(
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
else|else
name|add_alpha_region
argument_list|(
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
comment|/* reinitialize srcPR */
name|pixel_region_init_temp_buf
argument_list|(
name|srcPR
argument_list|,
name|src
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|width
argument_list|,
name|src
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IMAGE_TYPE_WITH_ALPHA
argument_list|(
name|src_type
argument_list|)
operator|!=
name|gimp_drawable_type_with_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
decl_stmt|;
name|TempBuf
modifier|*
name|temp2
decl_stmt|;
name|gboolean
name|new_buf
decl_stmt|;
name|temp2
operator|=
name|gimp_image_transform_temp_buf
argument_list|(
name|image
argument_list|,
name|gimp_drawable_type_with_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|src
argument_list|,
operator|&
name|new_buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_buf
condition|)
name|temp_buf_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|src
operator|=
name|temp2
expr_stmt|;
block|}
comment|/* reinitialize srcPR */
name|pixel_region_init_temp_buf
argument_list|(
name|srcPR
argument_list|,
name|src
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|src
operator|->
name|width
argument_list|,
name|src
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/* FIXME: the area under the cursor and the source area should be x% larger    * than the brush size.  Otherwise the brush must be a lot bigger than the    * area to heal to get good results.  Having the user pick such a large brush    * is perhaps counter-intutitive?    */
name|pixel_region_init
argument_list|(
operator|&
name|origPR
argument_list|,
name|gimp_drawable_get_tiles
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|paint_area
operator|->
name|x
argument_list|,
name|paint_area
operator|->
name|y
argument_list|,
name|paint_area
operator|->
name|width
argument_list|,
name|paint_area
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|temp
operator|=
name|temp_buf_new
argument_list|(
name|origPR
operator|.
name|w
argument_list|,
name|origPR
operator|.
name|h
argument_list|,
name|gimp_drawable_bytes_with_alpha
argument_list|(
name|drawable
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|temp
operator|->
name|width
argument_list|,
name|temp
operator|->
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|copy_region
argument_list|(
operator|&
name|origPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
else|else
name|add_alpha_region
argument_list|(
operator|&
name|origPR
argument_list|,
operator|&
name|tempPR
argument_list|)
expr_stmt|;
comment|/* reinitialize tempPR */
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|temp
operator|->
name|width
argument_list|,
name|temp
operator|->
name|height
argument_list|)
expr_stmt|;
comment|/* now tempPR holds the data under the cursor and    * srcPR holds the area to sample from    */
comment|/* get the destination to paint to */
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|destPR
argument_list|,
name|paint_area
argument_list|,
name|paint_area_offset_x
argument_list|,
name|paint_area_offset_y
argument_list|,
name|paint_area_width
argument_list|,
name|paint_area_height
argument_list|)
expr_stmt|;
comment|/* check that srcPR, tempPR, destPR, and mask_buf are the same size */
if|if
condition|(
operator|(
name|srcPR
operator|->
name|w
operator|!=
name|tempPR
operator|.
name|w
operator|)
operator|||
operator|(
name|srcPR
operator|->
name|w
operator|!=
name|destPR
operator|.
name|w
operator|)
operator|||
operator|(
name|srcPR
operator|->
name|h
operator|!=
name|tempPR
operator|.
name|h
operator|)
operator|||
operator|(
name|srcPR
operator|->
name|h
operator|!=
name|destPR
operator|.
name|h
operator|)
operator|||
operator|(
name|srcPR
operator|->
name|h
operator|!=
name|mask_buf
operator|->
name|height
operator|)
operator|||
operator|(
name|srcPR
operator|->
name|w
operator|!=
name|mask_buf
operator|->
name|width
operator|)
condition|)
block|{
comment|/* this generally means that the source point has hit the edge of the          layer, so it is not an error and we should not complain, just          don't do anything */
name|temp_buf_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* heal tempPR using srcPR */
name|gimp_heal_region
argument_list|(
operator|&
name|tempPR
argument_list|,
name|srcPR
argument_list|,
name|mask_buf
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
comment|/* reinitialize tempPR */
name|pixel_region_init_temp_buf
argument_list|(
operator|&
name|tempPR
argument_list|,
name|temp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|temp
operator|->
name|width
argument_list|,
name|temp
operator|->
name|height
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|temp_buf_free
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|opacity
operator|*=
name|gimp_dynamics_output_get_linear_value
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
operator|->
name|dynamics
operator|->
name|opacity_output
argument_list|,
operator|*
name|coords
argument_list|,
name|fade_point
argument_list|)
expr_stmt|;
comment|/* replace the canvas with our healed data */
name|gimp_brush_core_replace_canvas
argument_list|(
name|GIMP_BRUSH_CORE
argument_list|(
name|paint_core
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|coords
argument_list|,
name|MIN
argument_list|(
name|opacity
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_paint_options_get_brush_mode
argument_list|(
name|paint_options
argument_list|)
argument_list|,
name|hardness
argument_list|,
name|GIMP_PAINT_INCREMENTAL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

