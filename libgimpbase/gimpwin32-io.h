begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Compatibilty defines, you mostly need this as unistd.h replacement  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WIN32_IO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIN32_IO_H__
define|#
directive|define
name|__GIMP_WIN32_IO_H__
end_define

begin_include
include|#
directive|include
file|<io.h>
end_include

begin_include
include|#
directive|include
file|<direct.h>
end_include

begin_define
DECL|macro|mkdir (n,a)
define|#
directive|define
name|mkdir
parameter_list|(
name|n
parameter_list|,
name|a
parameter_list|)
value|_mkdir(n)
end_define

begin_define
DECL|macro|chmod (n,f)
define|#
directive|define
name|chmod
parameter_list|(
name|n
parameter_list|,
name|f
parameter_list|)
value|_chmod(n,f)
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|S_ISREG
end_ifndef

begin_define
DECL|macro|S_ISREG (m)
define|#
directive|define
name|S_ISREG
parameter_list|(
name|m
parameter_list|)
value|(((m)& _S_IFMT) == _S_IFREG)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_ISDIR
end_ifndef

begin_define
DECL|macro|S_ISDIR (m)
define|#
directive|define
name|S_ISDIR
parameter_list|(
name|m
parameter_list|)
value|(((m)& _S_IFMT) == _S_IFDIR)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IRUSR
end_ifndef

begin_define
DECL|macro|S_IRUSR
define|#
directive|define
name|S_IRUSR
value|_S_IREAD
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IWUSR
end_ifndef

begin_define
DECL|macro|S_IWUSR
define|#
directive|define
name|S_IWUSR
value|_S_IWRITE
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_IXUSR
end_ifndef

begin_define
DECL|macro|S_IXUSR
define|#
directive|define
name|S_IXUSR
value|_S_IEXEC
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|_O_BINARY
end_ifndef

begin_define
DECL|macro|_O_BINARY
define|#
directive|define
name|_O_BINARY
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|_O_TEMPORARY
end_ifndef

begin_define
DECL|macro|_O_TEMPORARY
define|#
directive|define
name|_O_TEMPORARY
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|W_OK
end_ifndef

begin_define
DECL|macro|W_OK
define|#
directive|define
name|W_OK
value|2
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

end_unit

