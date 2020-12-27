
#ifndef LINAINPUT_EXPORT_H
#define LINAINPUT_EXPORT_H

#ifdef LINAINPUT_STATIC_DEFINE
#  define LINAINPUT_EXPORT
#  define LINAINPUT_NO_EXPORT
#else
#  ifndef LINAINPUT_EXPORT
#    ifdef LinaInput_EXPORTS
        /* We are building this library */
#      define LINAINPUT_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define LINAINPUT_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef LINAINPUT_NO_EXPORT
#    define LINAINPUT_NO_EXPORT 
#  endif
#endif

#ifndef LINAINPUT_DEPRECATED
#  define LINAINPUT_DEPRECATED __declspec(deprecated)
#endif

#ifndef LINAINPUT_DEPRECATED_EXPORT
#  define LINAINPUT_DEPRECATED_EXPORT LINAINPUT_EXPORT LINAINPUT_DEPRECATED
#endif

#ifndef LINAINPUT_DEPRECATED_NO_EXPORT
#  define LINAINPUT_DEPRECATED_NO_EXPORT LINAINPUT_NO_EXPORT LINAINPUT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LINAINPUT_NO_DEPRECATED
#    define LINAINPUT_NO_DEPRECATED
#  endif
#endif

#endif /* LINAINPUT_EXPORT_H */
