begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"gimpsignal.h"
end_include

begin_include
include|#
directive|include
file|"gimpsetP.h"
end_include

begin_comment
comment|/* Yep, this can be optimized quite a lot */
end_comment

begin_typedef
DECL|struct|_GimpSetHandler
typedef|typedef
struct|struct
name|_GimpSetHandler
block|{
DECL|member|signame
specifier|const
name|gchar
modifier|*
name|signame
decl_stmt|;
DECL|member|func
name|GtkSignalFunc
name|func
decl_stmt|;
DECL|member|user_data
name|gpointer
name|user_data
decl_stmt|;
DECL|typedef|GimpSetHandler
block|}
name|GimpSetHandler
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28caaa680108
typedef|typedef
struct|struct
block|{
DECL|member|object
name|gpointer
name|object
decl_stmt|;
DECL|member|handlers
name|GArray
modifier|*
name|handlers
decl_stmt|;
DECL|member|destroy_handler
name|guint
name|destroy_handler
decl_stmt|;
DECL|typedef|Node
block|}
name|Node
typedef|;
end_typedef

begin_enum
enum|enum
DECL|enum|__anon28caaa680203
block|{
DECL|enumerator|ADD
name|ADD
block|,
DECL|enumerator|REMOVE
name|REMOVE
block|,
DECL|enumerator|ACTIVE_CHANGED
name|ACTIVE_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|Node
modifier|*
name|gimp_set_find_node
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|ob
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Node
modifier|*
name|gimp_set_node_new
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|ob
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_set_node_free
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|Node
modifier|*
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_set_signals
specifier|static
name|guint
name|gimp_set_signals
index|[
name|LAST_SIGNAL
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_set_destroy (GtkObject * ob)
name|gimp_set_destroy
parameter_list|(
name|GtkObject
modifier|*
name|ob
parameter_list|)
block|{
name|GimpSet
modifier|*
name|set
init|=
name|GIMP_SET
argument_list|(
name|ob
argument_list|)
decl_stmt|;
name|GSList
modifier|*
name|l
decl_stmt|;
for|for
control|(
name|l
operator|=
name|set
operator|->
name|list
init|;
name|l
condition|;
name|l
operator|=
name|l
operator|->
name|next
control|)
name|gimp_set_node_free
argument_list|(
name|set
argument_list|,
name|l
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_slist_free
argument_list|(
name|set
operator|->
name|list
argument_list|)
expr_stmt|;
name|g_array_free
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|ob
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_set_init (GimpSet * set)
name|gimp_set_init
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|)
block|{
name|set
operator|->
name|list
operator|=
name|NULL
expr_stmt|;
name|set
operator|->
name|type
operator|=
name|GTK_TYPE_OBJECT
expr_stmt|;
name|set
operator|->
name|handlers
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpSetHandler
argument_list|)
argument_list|)
expr_stmt|;
name|set
operator|->
name|active_element
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_set_class_init (GimpSetClass * klass)
name|gimp_set_class_init
parameter_list|(
name|GimpSetClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkType
name|type
init|=
name|object_class
operator|->
name|type
decl_stmt|;
name|parent_class
operator|=
name|gtk_type_parent_class
argument_list|(
name|type
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_set_destroy
expr_stmt|;
name|gimp_set_signals
index|[
name|ADD
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"add"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|type
argument_list|,
literal|0
argument_list|,
name|gimp_sigtype_pointer
argument_list|)
expr_stmt|;
name|gimp_set_signals
index|[
name|REMOVE
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"remove"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|type
argument_list|,
literal|0
argument_list|,
name|gimp_sigtype_pointer
argument_list|)
expr_stmt|;
name|gimp_set_signals
index|[
name|ACTIVE_CHANGED
index|]
operator|=
name|gimp_signal_new
argument_list|(
literal|"active_changed"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|type
argument_list|,
literal|0
argument_list|,
name|gimp_sigtype_pointer
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_set_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|gimp_set_get_type (void)
name|GtkType
name|gimp_set_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|type
decl_stmt|;
name|GIMP_TYPE_INIT
argument_list|(
name|type
argument_list|,
name|GimpSet
argument_list|,
name|GimpSetClass
argument_list|,
name|gimp_set_init
argument_list|,
name|gimp_set_class_init
argument_list|,
name|GIMP_TYPE_OBJECT
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

begin_function
name|GimpSet
modifier|*
DECL|function|gimp_set_new (GtkType type,gboolean weak)
name|gimp_set_new
parameter_list|(
name|GtkType
name|type
parameter_list|,
name|gboolean
name|weak
parameter_list|)
block|{
name|GimpSet
modifier|*
name|set
decl_stmt|;
comment|/* untyped sets must not be weak, since we can't attach a          * destroy handler */
name|g_assert
argument_list|(
operator|!
operator|(
name|type
operator|==
name|GTK_TYPE_NONE
operator|&&
name|weak
operator|==
name|TRUE
operator|)
argument_list|)
expr_stmt|;
name|set
operator|=
name|gtk_type_new
argument_list|(
name|gimp_set_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|set
operator|->
name|type
operator|=
name|type
expr_stmt|;
name|set
operator|->
name|weak
operator|=
name|weak
expr_stmt|;
return|return
name|set
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_set_destroy_cb (GtkObject * ob,gpointer data)
name|gimp_set_destroy_cb
parameter_list|(
name|GtkObject
modifier|*
name|ob
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpSet
modifier|*
name|set
init|=
name|GIMP_SET
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_set_remove
argument_list|(
name|set
argument_list|,
name|ob
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Node
modifier|*
DECL|function|gimp_set_find_node (GimpSet * set,gpointer ob)
name|gimp_set_find_node
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|ob
parameter_list|)
block|{
name|GSList
modifier|*
name|l
init|=
name|set
operator|->
name|list
decl_stmt|;
for|for
control|(
name|l
operator|=
name|set
operator|->
name|list
init|;
name|l
condition|;
name|l
operator|=
name|l
operator|->
name|next
control|)
block|{
name|Node
modifier|*
name|n
init|=
name|l
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|n
operator|->
name|object
operator|==
name|ob
condition|)
return|return
name|n
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|Node
modifier|*
DECL|function|gimp_set_node_new (GimpSet * set,gpointer ob)
name|gimp_set_node_new
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|ob
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|Node
modifier|*
name|n
init|=
name|g_new
argument_list|(
name|Node
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|n
operator|->
name|object
operator|=
name|ob
expr_stmt|;
name|n
operator|->
name|handlers
operator|=
name|g_array_new
argument_list|(
name|FALSE
argument_list|,
name|FALSE
argument_list|,
sizeof|sizeof
argument_list|(
name|guint
argument_list|)
argument_list|)
expr_stmt|;
name|g_array_set_size
argument_list|(
name|n
operator|->
name|handlers
argument_list|,
name|set
operator|->
name|handlers
operator|->
name|len
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
name|n
operator|->
name|handlers
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpSetHandler
modifier|*
name|h
init|=
operator|&
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|h
operator|->
name|signame
condition|)
name|g_array_index
argument_list|(
name|n
operator|->
name|handlers
argument_list|,
name|guint
argument_list|,
name|i
argument_list|)
operator|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|ob
argument_list|)
argument_list|,
name|h
operator|->
name|signame
argument_list|,
name|h
operator|->
name|func
argument_list|,
name|h
operator|->
name|user_data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|set
operator|->
name|weak
condition|)
name|n
operator|->
name|destroy_handler
operator|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|ob
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_set_destroy_cb
argument_list|)
argument_list|,
name|set
argument_list|)
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_set_node_free (GimpSet * set,Node * n)
name|gimp_set_node_free
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|Node
modifier|*
name|n
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|GimpObject
modifier|*
name|ob
init|=
name|n
operator|->
name|object
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|set
operator|->
name|handlers
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
name|GimpSetHandler
modifier|*
name|h
init|=
operator|&
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|i
argument_list|)
decl_stmt|;
if|if
condition|(
name|h
operator|->
name|signame
condition|)
name|gtk_signal_disconnect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|ob
argument_list|)
argument_list|,
name|g_array_index
argument_list|(
name|n
operator|->
name|handlers
argument_list|,
name|guint
argument_list|,
name|i
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|set
operator|->
name|weak
condition|)
name|gtk_signal_disconnect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|ob
argument_list|)
argument_list|,
name|n
operator|->
name|destroy_handler
argument_list|)
expr_stmt|;
name|g_array_free
argument_list|(
name|n
operator|->
name|handlers
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|n
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_set_add (GimpSet * set,gpointer val)
name|gimp_set_add
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|val
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|set
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|set
operator|->
name|type
operator|!=
name|GTK_TYPE_NONE
condition|)
name|g_return_val_if_fail
argument_list|(
name|GTK_CHECK_TYPE
argument_list|(
name|val
argument_list|,
name|set
operator|->
name|type
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_set_find_node
argument_list|(
name|set
argument_list|,
name|val
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|set
operator|->
name|list
operator|=
name|g_slist_prepend
argument_list|(
name|set
operator|->
name|list
argument_list|,
name|gimp_set_node_new
argument_list|(
name|set
argument_list|,
name|val
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|set
argument_list|)
argument_list|,
name|gimp_set_signals
index|[
name|ADD
index|]
argument_list|,
name|val
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_set_remove (GimpSet * set,gpointer val)
name|gimp_set_remove
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|val
parameter_list|)
block|{
name|Node
modifier|*
name|n
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|set
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|n
operator|=
name|gimp_set_find_node
argument_list|(
name|set
argument_list|,
name|val
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|n
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|set
argument_list|)
argument_list|,
name|gimp_set_signals
index|[
name|REMOVE
index|]
argument_list|,
name|val
argument_list|)
expr_stmt|;
name|gimp_set_node_free
argument_list|(
name|set
argument_list|,
name|n
argument_list|)
expr_stmt|;
name|set
operator|->
name|list
operator|=
name|g_slist_remove
argument_list|(
name|set
operator|->
name|list
argument_list|,
name|n
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_set_have (GimpSet * set,gpointer val)
name|gimp_set_have
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|val
parameter_list|)
block|{
return|return
operator|!
operator|!
name|gimp_set_find_node
argument_list|(
name|set
argument_list|,
name|val
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_foreach (GimpSet * set,GFunc func,gpointer user_data)
name|gimp_set_foreach
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|GFunc
name|func
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GSList
modifier|*
name|l
decl_stmt|;
for|for
control|(
name|l
operator|=
name|set
operator|->
name|list
init|;
name|l
condition|;
name|l
operator|=
name|l
operator|->
name|next
control|)
block|{
name|Node
modifier|*
name|n
init|=
name|l
operator|->
name|data
decl_stmt|;
name|func
argument_list|(
name|n
operator|->
name|object
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_set_type (GimpSet * set)
name|gimp_set_type
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|)
block|{
return|return
name|set
operator|->
name|type
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_set_active (GimpSet * set,gpointer ob)
name|gimp_set_set_active
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|gpointer
name|ob
parameter_list|)
block|{
if|if
condition|(
name|ob
operator|!=
name|set
operator|->
name|active_element
operator|&&
name|gimp_set_have
argument_list|(
name|set
argument_list|,
name|ob
argument_list|)
condition|)
block|{
comment|/* g_warning("Gimp_Set got new active element"); */
name|set
operator|->
name|active_element
operator|=
name|ob
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|set
argument_list|)
argument_list|,
name|gimp_set_signals
index|[
name|ACTIVE_CHANGED
index|]
argument_list|,
name|ob
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gpointer
DECL|function|gimp_set_get_active (GimpSet * set)
name|gimp_set_get_active
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|)
block|{
if|if
condition|(
name|gimp_set_have
argument_list|(
name|set
argument_list|,
name|set
operator|->
name|active_element
argument_list|)
condition|)
return|return
name|set
operator|->
name|active_element
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpSetHandlerId
DECL|function|gimp_set_add_handler (GimpSet * set,const gchar * signame,GtkSignalFunc handler,gpointer user_data)
name|gimp_set_add_handler
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
specifier|const
name|gchar
modifier|*
name|signame
parameter_list|,
name|GtkSignalFunc
name|handler
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|GimpSetHandler
name|h
decl_stmt|;
name|GSList
modifier|*
name|l
decl_stmt|;
name|guint
name|a
decl_stmt|;
name|g_assert
argument_list|(
name|signame
argument_list|)
expr_stmt|;
comment|/* you can't set a handler on something that's not a GTK          * object */
name|g_assert
argument_list|(
name|set
operator|->
name|type
operator|!=
name|GTK_TYPE_NONE
argument_list|)
expr_stmt|;
name|h
operator|.
name|signame
operator|=
name|signame
expr_stmt|;
name|h
operator|.
name|func
operator|=
name|handler
expr_stmt|;
name|h
operator|.
name|user_data
operator|=
name|user_data
expr_stmt|;
for|for
control|(
name|a
operator|=
literal|0
init|;
name|a
operator|<
name|set
operator|->
name|handlers
operator|->
name|len
condition|;
name|a
operator|++
control|)
if|if
condition|(
operator|!
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|a
argument_list|)
operator|.
name|signame
condition|)
break|break;
if|if
condition|(
name|a
operator|<
name|set
operator|->
name|handlers
operator|->
name|len
condition|)
block|{
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|a
argument_list|)
operator|=
name|h
expr_stmt|;
for|for
control|(
name|l
operator|=
name|set
operator|->
name|list
init|;
name|l
condition|;
name|l
operator|=
name|l
operator|->
name|next
control|)
block|{
name|Node
modifier|*
name|n
init|=
name|l
operator|->
name|data
decl_stmt|;
name|guint
name|i
init|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|n
operator|->
name|object
argument_list|)
argument_list|,
name|signame
argument_list|,
name|handler
argument_list|,
name|user_data
argument_list|)
decl_stmt|;
name|g_array_index
argument_list|(
name|n
operator|->
name|handlers
argument_list|,
name|guint
argument_list|,
name|a
argument_list|)
operator|=
name|i
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_array_append_val
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|h
argument_list|)
expr_stmt|;
for|for
control|(
name|l
operator|=
name|set
operator|->
name|list
init|;
name|l
condition|;
name|l
operator|=
name|l
operator|->
name|next
control|)
block|{
name|Node
modifier|*
name|n
init|=
name|l
operator|->
name|data
decl_stmt|;
name|guint
name|i
init|=
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|n
operator|->
name|object
argument_list|)
argument_list|,
name|signame
argument_list|,
name|handler
argument_list|,
name|user_data
argument_list|)
decl_stmt|;
name|g_array_append_val
argument_list|(
name|n
operator|->
name|handlers
argument_list|,
name|i
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|a
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_set_remove_handler (GimpSet * set,GimpSetHandlerId id)
name|gimp_set_remove_handler
parameter_list|(
name|GimpSet
modifier|*
name|set
parameter_list|,
name|GimpSetHandlerId
name|id
parameter_list|)
block|{
name|GSList
modifier|*
name|l
decl_stmt|;
comment|/* you can't remove a signal handler on something that's not a          * GTK object */
name|g_return_if_fail
argument_list|(
name|set
operator|->
name|type
operator|!=
name|GTK_TYPE_NONE
argument_list|)
expr_stmt|;
for|for
control|(
name|l
operator|=
name|set
operator|->
name|list
init|;
name|l
condition|;
name|l
operator|=
name|l
operator|->
name|next
control|)
block|{
name|Node
modifier|*
name|n
init|=
name|l
operator|->
name|data
decl_stmt|;
name|gtk_signal_disconnect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|n
operator|->
name|object
argument_list|)
argument_list|,
name|g_array_index
argument_list|(
name|n
operator|->
name|handlers
argument_list|,
name|guint
argument_list|,
name|id
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|g_array_index
argument_list|(
name|set
operator|->
name|handlers
argument_list|,
name|GimpSetHandler
argument_list|,
name|id
argument_list|)
operator|.
name|signame
operator|=
name|NULL
expr_stmt|;
block|}
end_function

end_unit

