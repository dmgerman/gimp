begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"config.h"
end_include

begin_comment
comment|/* configure cares about HAVE_PROGRESSIVE_JPEG */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* We want glib.h first because of some                        * pretty obscure Win32 compilation issues.                        */
end_comment

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<setjmp.h>
end_include

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<jpeglib.h>
end_include

begin_include
include|#
directive|include
file|<jerror.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_include
include|#
directive|include
file|<libexif/exif-data.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_EXIF */
end_comment

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
DECL|struct|my_error_mgr
typedef|typedef
struct|struct
name|my_error_mgr
block|{
DECL|member|pub
name|struct
name|jpeg_error_mgr
name|pub
decl_stmt|;
comment|/* "public" fields */
ifdef|#
directive|ifdef
name|__ia64__
comment|/* Ugh, the jmp_buf field needs to be 16-byte aligned on ia64 and some    * glibc/icc combinations don't guarantee this. So we pad. See bug #138357    * for details.    */
DECL|member|dummy
name|long
name|double
name|dummy
decl_stmt|;
endif|#
directive|endif
DECL|member|setjmp_buffer
name|jmp_buf
name|setjmp_buffer
decl_stmt|;
comment|/* for return to caller */
DECL|typedef|my_error_ptr
block|}
typedef|*
name|my_error_ptr
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|image_ID_global
name|gint32
specifier|volatile
name|image_ID_global
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|layer_ID_global
name|gint32
name|layer_ID_global
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable_global
name|GimpDrawable
modifier|*
name|drawable_global
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|undo_touched
name|gboolean
name|undo_touched
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|display_ID
name|gint32
name|display_ID
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_comment
name|gchar
modifier|*
name|image_comment
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_decl_stmt
DECL|variable|exif_data
name|ExifData
modifier|*
name|exif_data
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_EXIF */
end_comment

begin_function_decl
name|gint32
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|GimpRunMode
name|runmode
parameter_list|,
name|gboolean
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|destroy_preview
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_EXIF
end_ifdef

begin_function_decl
name|gint32
name|load_thumbnail_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_EXIF */
end_comment

begin_function_decl
name|void
name|my_error_exit
parameter_list|(
name|j_common_ptr
name|cinfo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|my_emit_message
parameter_list|(
name|j_common_ptr
name|cinfo
parameter_list|,
name|int
name|msg_level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|my_output_message
parameter_list|(
name|j_common_ptr
name|cinfo
parameter_list|)
function_decl|;
end_function_decl

end_unit

