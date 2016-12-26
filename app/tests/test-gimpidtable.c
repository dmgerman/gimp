begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2011 Martin Nordholts<martinn@src.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpidtable.h"
end_include

begin_define
DECL|macro|ADD_TEST (function)
define|#
directive|define
name|ADD_TEST
parameter_list|(
name|function
parameter_list|)
define|\
value|g_test_add ("/gimpidtable/" #function, \               GimpTestFixture, \               NULL, \               gimp_test_id_table_setup, \               gimp_test_id_table_ ## function, \               gimp_test_id_table_teardown);
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon292c1b7f0108
block|{
DECL|member|id_table
name|GimpIdTable
modifier|*
name|id_table
decl_stmt|;
DECL|typedef|GimpTestFixture
block|}
name|GimpTestFixture
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|data1
specifier|static
name|gpointer
name|data1
init|=
operator|(
name|gpointer
operator|)
literal|0x00000001
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|data2
specifier|static
name|gpointer
name|data2
init|=
operator|(
name|gpointer
operator|)
literal|0x00000002
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_setup (GimpTestFixture * fixture,gconstpointer data)
name|gimp_test_id_table_setup
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|fixture
operator|->
name|id_table
operator|=
name|gimp_id_table_new
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_teardown (GimpTestFixture * fixture,gconstpointer data)
name|gimp_test_id_table_teardown
parameter_list|(
name|GimpTestFixture
modifier|*
name|fixture
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|g_object_unref
argument_list|(
name|fixture
operator|->
name|id_table
argument_list|)
expr_stmt|;
name|fixture
operator|->
name|id_table
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_id_table_insert_and_lookup:  *  * Test that insert and lookup works.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_insert_and_lookup (GimpTestFixture * f,gconstpointer data)
name|gimp_test_id_table_insert_and_lookup
parameter_list|(
name|GimpTestFixture
modifier|*
name|f
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|gint
name|ret_id
init|=
name|gimp_id_table_insert
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|data1
argument_list|)
decl_stmt|;
name|gpointer
name|ret_data
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id
argument_list|)
decl_stmt|;
name|g_assert
argument_list|(
name|ret_data
operator|==
name|data1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_id_table_insert_twice:  *  * Test that two consecutive inserts generates different IDs.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_insert_twice (GimpTestFixture * f,gconstpointer data)
name|gimp_test_id_table_insert_twice
parameter_list|(
name|GimpTestFixture
modifier|*
name|f
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|gint
name|ret_id
init|=
name|gimp_id_table_insert
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|data1
argument_list|)
decl_stmt|;
name|gpointer
name|ret_data
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id
argument_list|)
decl_stmt|;
name|gint
name|ret_id2
init|=
name|gimp_id_table_insert
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|data2
argument_list|)
decl_stmt|;
name|gpointer
name|ret_data2
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id2
argument_list|)
decl_stmt|;
name|g_assert
argument_list|(
name|ret_id
operator|!=
name|ret_id2
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data
operator|==
name|data1
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data2
operator|==
name|data2
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_id_table_insert_with_id:  *  * Test that it is possible to insert data with a specific ID.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_insert_with_id (GimpTestFixture * f,gconstpointer data)
name|gimp_test_id_table_insert_with_id
parameter_list|(
name|GimpTestFixture
modifier|*
name|f
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
specifier|const
name|int
name|id
init|=
literal|10
decl_stmt|;
name|int
name|ret_id
init|=
name|gimp_id_table_insert_with_id
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|id
argument_list|,
name|data1
argument_list|)
decl_stmt|;
name|gpointer
name|ret_data
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|id
argument_list|)
decl_stmt|;
name|g_assert
argument_list|(
name|ret_id
operator|==
name|id
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data
operator|==
name|data1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_id_table_insert_with_id_existing:  *  * Test that it is not possible to insert data with a specific ID if  * that ID already is inserted.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_insert_with_id_existing (GimpTestFixture * f,gconstpointer data)
name|gimp_test_id_table_insert_with_id_existing
parameter_list|(
name|GimpTestFixture
modifier|*
name|f
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
specifier|const
name|int
name|id
init|=
literal|10
decl_stmt|;
name|int
name|ret_id
init|=
name|gimp_id_table_insert_with_id
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|id
argument_list|,
name|data1
argument_list|)
decl_stmt|;
name|gpointer
name|ret_data
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id
argument_list|)
decl_stmt|;
name|int
name|ret_id2
init|=
name|gimp_id_table_insert_with_id
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|id
argument_list|,
name|data2
argument_list|)
decl_stmt|;
name|gpointer
name|ret_data2
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id2
argument_list|)
decl_stmt|;
name|g_assert
argument_list|(
name|id
operator|==
name|ret_id
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_id2
operator|==
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data
operator|==
name|data1
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data2
operator|==
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_id_table_replace:  *  * Test that it is possible to replace data with a given ID with  * different data.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_replace (GimpTestFixture * f,gconstpointer data)
name|gimp_test_id_table_replace
parameter_list|(
name|GimpTestFixture
modifier|*
name|f
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|int
name|ret_id
init|=
name|gimp_id_table_insert
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|data1
argument_list|)
decl_stmt|;
name|gpointer
name|ret_data
decl_stmt|;
name|gimp_id_table_replace
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id
argument_list|,
name|data2
argument_list|)
expr_stmt|;
name|ret_data
operator|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data
operator|==
name|data2
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_id_table_replace_as_insert:  *  * Test that replace works like insert when there is no data to  * replace.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_replace_as_insert (GimpTestFixture * f,gconstpointer data)
name|gimp_test_id_table_replace_as_insert
parameter_list|(
name|GimpTestFixture
modifier|*
name|f
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
specifier|const
name|int
name|id
init|=
literal|10
decl_stmt|;
name|gpointer
name|ret_data
decl_stmt|;
name|gimp_id_table_replace
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|id
argument_list|,
name|data1
argument_list|)
expr_stmt|;
name|ret_data
operator|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|id
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data
operator|==
name|data1
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_id_table_remove:  *  * Test that it is possible to remove data identified by the ID:  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_remove (GimpTestFixture * f,gconstpointer data)
name|gimp_test_id_table_remove
parameter_list|(
name|GimpTestFixture
modifier|*
name|f
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|gint
name|ret_id
init|=
name|gimp_id_table_insert
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|data1
argument_list|)
decl_stmt|;
name|void
modifier|*
name|ret_data
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id
argument_list|)
decl_stmt|;
name|gboolean
name|remove_successful
init|=
name|gimp_id_table_remove
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id
argument_list|)
decl_stmt|;
name|void
modifier|*
name|ret_data2
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|ret_id
argument_list|)
decl_stmt|;
name|g_assert
argument_list|(
name|remove_successful
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data
operator|==
name|data1
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data2
operator|==
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_test_id_table_remove_non_existing:  *  * Tests that things work properly when trying to remove data with an  * ID that doesn't exist.  **/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_test_id_table_remove_non_existing (GimpTestFixture * f,gconstpointer data)
name|gimp_test_id_table_remove_non_existing
parameter_list|(
name|GimpTestFixture
modifier|*
name|f
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
specifier|const
name|int
name|id
init|=
literal|10
decl_stmt|;
name|gboolean
name|remove_successful
init|=
name|gimp_id_table_remove
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|id
argument_list|)
decl_stmt|;
name|void
modifier|*
name|ret_data
init|=
name|gimp_id_table_lookup
argument_list|(
name|f
operator|->
name|id_table
argument_list|,
name|id
argument_list|)
decl_stmt|;
name|g_assert
argument_list|(
operator|!
name|remove_successful
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|ret_data
operator|==
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|main (int argc,char ** argv)
name|int
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
name|g_test_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|insert_and_lookup
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|insert_twice
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|insert_with_id
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|insert_with_id_existing
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|replace
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|replace_as_insert
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|remove
argument_list|)
expr_stmt|;
name|ADD_TEST
argument_list|(
name|remove_non_existing
argument_list|)
expr_stmt|;
return|return
name|g_test_run
argument_list|()
return|;
block|}
end_function

end_unit

