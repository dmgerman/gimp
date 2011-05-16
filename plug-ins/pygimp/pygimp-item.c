begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-  * Gimp-Python - allows the writing of Gimp plugins in Python.  * Copyright (C) 1997-2002  James Henstridge<james@daa.com.au>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_CONFIG_H
end_ifdef

begin_include
include|#
directive|include
file|<config.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NO_IMPORT_PYGOBJECT
define|#
directive|define
name|NO_IMPORT_PYGOBJECT
end_define

begin_include
include|#
directive|include
file|<pygobject.h>
end_include

begin_include
include|#
directive|include
file|"pygimp.h"
end_include

begin_define
DECL|macro|NO_IMPORT_PYGIMPCOLOR
define|#
directive|define
name|NO_IMPORT_PYGIMPCOLOR
end_define

begin_include
include|#
directive|include
file|"pygimpcolor-api.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_function
name|PyObject
modifier|*
DECL|function|item_from_id (PyObject * not_used,PyObject * args)
name|item_from_id
parameter_list|(
name|PyObject
modifier|*
name|not_used
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|)
block|{
name|gint32
name|ID
decl_stmt|;
if|if
condition|(
operator|!
name|PyArg_ParseTuple
argument_list|(
name|args
argument_list|,
literal|"i"
argument_list|,
operator|&
name|ID
argument_list|)
condition|)
return|return
name|NULL
return|;
return|return
name|pygimp_item_new
argument_list|(
name|ID
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|item_methods
specifier|static
name|PyMethodDef
name|item_methods
index|[]
init|=
block|{
block|{
literal|"from_id"
block|,
operator|(
name|PyCFunction
operator|)
name|item_from_id
block|,
name|METH_VARARGS
operator||
name|METH_STATIC
block|}
block|,
block|{
name|NULL
block|,
name|NULL
block|}
comment|/* sentinel */
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|item_get_parent (PyGimpLayer * self,void * closure)
name|item_get_parent
parameter_list|(
name|PyGimpLayer
modifier|*
name|self
parameter_list|,
name|void
modifier|*
name|closure
parameter_list|)
block|{
comment|/*  Not implemented yet */
return|return
name|NULL
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|item_getsets
specifier|static
name|PyGetSetDef
name|item_getsets
index|[]
init|=
block|{
block|{
literal|"parent"
block|,
operator|(
name|getter
operator|)
name|item_get_parent
block|,
operator|(
name|setter
operator|)
literal|0
block|}
block|,
block|{
name|NULL
block|,
operator|(
name|getter
operator|)
literal|0
block|,
operator|(
name|setter
operator|)
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|item_dealloc (PyGimpItem * self)
name|item_dealloc
parameter_list|(
name|PyGimpItem
modifier|*
name|self
parameter_list|)
block|{
name|PyObject_DEL
argument_list|(
name|self
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|PyObject
modifier|*
DECL|function|item_repr (PyGimpItem * self)
name|item_repr
parameter_list|(
name|PyGimpItem
modifier|*
name|self
parameter_list|)
block|{
name|PyObject
modifier|*
name|s
decl_stmt|;
name|s
operator|=
name|PyString_FromFormat
argument_list|(
literal|"<gimp.Item '%d'>"
argument_list|,
name|self
operator|->
name|ID
argument_list|)
expr_stmt|;
return|return
name|s
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|item_init (PyGimpLayer * self,PyObject * args,PyObject * kwargs)
name|item_init
parameter_list|(
name|PyGimpLayer
modifier|*
name|self
parameter_list|,
name|PyObject
modifier|*
name|args
parameter_list|,
name|PyObject
modifier|*
name|kwargs
parameter_list|)
block|{
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|PyGimpItem_Type
name|PyTypeObject
name|PyGimpItem_Type
init|=
block|{
name|PyObject_HEAD_INIT
argument_list|(
name|NULL
argument_list|)
literal|0
block|,
comment|/* ob_size */
literal|"gimp.Item"
block|,
comment|/* tp_name */
sizeof|sizeof
argument_list|(
name|PyGimpItem
argument_list|)
block|,
comment|/* tp_basicsize */
literal|0
block|,
comment|/* tp_itemsize */
comment|/* methods */
operator|(
name|destructor
operator|)
name|item_dealloc
block|,
comment|/* tp_dealloc */
operator|(
name|printfunc
operator|)
literal|0
block|,
comment|/* tp_print */
operator|(
name|getattrfunc
operator|)
literal|0
block|,
comment|/* tp_getattr */
operator|(
name|setattrfunc
operator|)
literal|0
block|,
comment|/* tp_setattr */
operator|(
name|cmpfunc
operator|)
literal|0
block|,
comment|/* tp_compare */
operator|(
name|reprfunc
operator|)
name|item_repr
block|,
comment|/* tp_repr */
literal|0
block|,
comment|/* tp_as_number */
literal|0
block|,
comment|/* tp_as_sequence */
literal|0
block|,
comment|/* tp_as_mapping */
operator|(
name|hashfunc
operator|)
literal|0
block|,
comment|/* tp_hash */
operator|(
name|ternaryfunc
operator|)
literal|0
block|,
comment|/* tp_call */
operator|(
name|reprfunc
operator|)
literal|0
block|,
comment|/* tp_str */
operator|(
name|getattrofunc
operator|)
literal|0
block|,
comment|/* tp_getattro */
operator|(
name|setattrofunc
operator|)
literal|0
block|,
comment|/* tp_setattro */
literal|0
block|,
comment|/* tp_as_buffer */
name|Py_TPFLAGS_DEFAULT
block|,
comment|/* tp_flags */
name|NULL
block|,
comment|/* Documentation string */
operator|(
name|traverseproc
operator|)
literal|0
block|,
comment|/* tp_traverse */
operator|(
name|inquiry
operator|)
literal|0
block|,
comment|/* tp_clear */
operator|(
name|richcmpfunc
operator|)
literal|0
block|,
comment|/* tp_richcompare */
literal|0
block|,
comment|/* tp_weaklistoffset */
operator|(
name|getiterfunc
operator|)
literal|0
block|,
comment|/* tp_iter */
operator|(
name|iternextfunc
operator|)
literal|0
block|,
comment|/* tp_iternext */
name|item_methods
block|,
comment|/* tp_methods */
literal|0
block|,
comment|/* tp_members */
name|item_getsets
block|,
comment|/* tp_getset */
operator|(
name|PyTypeObject
operator|*
operator|)
literal|0
block|,
comment|/* tp_base */
operator|(
name|PyObject
operator|*
operator|)
literal|0
block|,
comment|/* tp_dict */
literal|0
block|,
comment|/* tp_descr_get */
literal|0
block|,
comment|/* tp_descr_set */
literal|0
block|,
comment|/* tp_dictoffset */
operator|(
name|initproc
operator|)
name|item_init
block|,
comment|/* tp_init */
operator|(
name|allocfunc
operator|)
literal|0
block|,
comment|/* tp_alloc */
operator|(
name|newfunc
operator|)
literal|0
block|,
comment|/* tp_new */
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|PyObject
modifier|*
DECL|function|pygimp_item_new (gint32 ID)
name|pygimp_item_new
parameter_list|(
name|gint32
name|ID
parameter_list|)
block|{
name|PyObject
modifier|*
name|self
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_item_is_valid
argument_list|(
name|ID
argument_list|)
condition|)
block|{
name|Py_INCREF
argument_list|(
name|Py_None
argument_list|)
expr_stmt|;
return|return
name|Py_None
return|;
block|}
comment|/* create the appropriate object type */
if|if
condition|(
name|gimp_item_is_drawable
argument_list|(
name|ID
argument_list|)
condition|)
name|self
operator|=
name|pygimp_drawable_new
argument_list|(
name|NULL
argument_list|,
name|ID
argument_list|)
expr_stmt|;
else|else
comment|/* Vectors */
name|self
operator|=
name|pygimp_vectors_new
argument_list|(
name|ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|self
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
return|return
name|self
return|;
block|}
end_function

end_unit

