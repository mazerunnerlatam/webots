// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QOPENGL_H
#define QOPENGL_H

#include <QtGui/qtguiglobal.h>

#ifndef QT_NO_OPENGL

// On Windows we need to ensure that APIENTRY and WINGDIAPI are defined before
// we can include gl.h. But we do not want to include <windows.h> in this public
// Qt header, as it pollutes the global namespace with macros.
// We also need to make sure that CALLBACK and GLAPI are defined (and all of
// these keep being defined) in case <GL/glu.h> is included after this header.
#if defined(Q_OS_WIN)
# ifndef APIENTRY
#  define APIENTRY __stdcall
# endif // APIENTRY
# ifndef WINGDIAPI
#  define WINGDIAPI __declspec(dllimport)
# endif // WINGDIAPI
# ifndef CALLBACK
#  define CALLBACK APIENTRY
# endif // CALLBACK
# ifndef GLAPI
#  define GLAPI extern
# endif // GLAPI
# define QT_APIENTRY __stdcall
#endif

// Note: Apple is a "controlled platform" for OpenGL ABI so we
// use the system provided headers there. Controlled means that the
// headers always match the actual driver implementation so there
// is no possibility of drivers exposing additional functionality
// from the system headers. Also it means that the vendor can
// (and does) make different choices about some OpenGL types. For
// e.g. Apple uses void* for GLhandleARB whereas other platforms
// use unsigned int.
//
// For the "uncontrolled" Windows and Linux platforms we use the
// official Khronos headers. On these platforms this gives
// access to additional functionality the drivers may expose but
// which the system headers do not.

#if QT_CONFIG(opengles2)
# if defined(Q_OS_IOS) || defined(Q_OS_TVOS)
#  if QT_CONFIG(opengles3)
#   include <OpenGLES/ES3/gl.h>
#   include <OpenGLES/ES3/glext.h>
#  else
#   include <OpenGLES/ES2/gl.h>
#   include <OpenGLES/ES2/glext.h>
#  endif

/*
   OES_EGL_image_external is not included in the Apple provided
   system headers yet, but we define the missing typedef so that
   the qopenglextensions.cpp code will magically work once Apple
   include the extension in their drivers.
*/
typedef void* GLeglImageOES;

# elif !defined(Q_OS_DARWIN) // "uncontrolled" ES2 platforms

// In "es2" builds (QT_CONFIG(opengles2)) additional defines indicate GLES 3.0 or
// higher is available *at build time*. In this case include the corresponding
// header. These are backwards compatible and it should be safe to include
// headers on top of each other, meaning that applications can include gl2.h
// even if gl31.h gets included here.

// NB! The fact that Qt was built against an SDK with GLES 2 only does not mean
// applications cannot be deployed on a GLES 3 system. Therefore
// QOpenGLFunctions and friends must do everything dynamically and must not rely
// on these macros, except in special cases for controlled build/run environments.

// Some Khronos headers use the ext proto guard in the standard headers as well,
// which is bad. Work it around, but avoid spilling over to the ext header.
#  ifndef GL_GLEXT_PROTOTYPES
#   define GL_GLEXT_PROTOTYPES
#   define QGL_TEMP_GLEXT_PROTO
#  endif

#  if QT_CONFIG(opengles32)
#   include <GLES3/gl32.h>
#  elif QT_CONFIG(opengles31)
#   include <GLES3/gl31.h>
#  elif QT_CONFIG(opengles3)
#   include <GLES3/gl3.h>
#  else
#   include <GLES2/gl2.h>
#  endif

#  ifdef QGL_TEMP_GLEXT_PROTO
#   undef GL_GLEXT_PROTOTYPES
#   undef QGL_TEMP_GLEXT_PROTO
#  endif

/*
   Some GLES2 implementations (like the one on Harmattan) are missing the
   typedef for GLchar. Work around it here by adding it. The Kkronos headers
   specify GLChar as a typedef to char, so if an implementation already
   provides it, then this doesn't do any harm.
*/
typedef char GLchar;

#  include <QtGui/qopengles2ext.h>
# endif
#else // non-ES2 platforms
# if defined(Q_OS_MACOS)
#  include <OpenGL/gl.h>
#  define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#  include <OpenGL/gl3.h>
#  include <OpenGL/glext.h>
# else
#  define GL_GLEXT_LEGACY // Prevents GL/gl.h from #including system glext.h
// Some Khronos headers use the ext proto guard in the standard headers as well,
// which is bad. Work it around, but avoid spilling over to the ext header.
#  ifndef GL_GLEXT_PROTOTYPES
#   define GL_GLEXT_PROTOTYPES
#   include <GL/gl.h>
#   undef GL_GLEXT_PROTOTYPES
#  else
#   include <GL/gl.h>
#  endif
#  include <QtGui/qopenglext.h>
# endif
#endif // !QT_CONFIG(opengles2)

// Desktops can support OpenGL 4.
#if !QT_CONFIG(opengles2)
#define QT_OPENGL_3
#define QT_OPENGL_3_2
#define QT_OPENGL_4
# if !defined(Q_OS_MAC)
#  define QT_OPENGL_4_3
# endif
#endif


// When all else fails we provide sensible fallbacks - this is needed to
// allow compilation on OS X 10.6
#if !QT_CONFIG(opengles2)

// OS X 10.6 doesn't define these which are needed below
// OS X 10.7 and later define them in gl3.h
#ifndef QT_APIENTRY
#define QT_APIENTRY
#endif
#ifndef QT_APIENTRYP
#define QT_APIENTRYP QT_APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif


// This block is copied from glext.h and defines the types needed by
// a few extension classes.

#include <stddef.h>
#ifndef GL_VERSION_2_0
/* GL type for program/shader text */
typedef char GLchar;
#endif

#ifndef GL_VERSION_1_5
/* GL types for handling large vertex buffer objects */
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
#endif

#ifndef GL_ARB_vertex_buffer_object
/* GL types for handling large vertex buffer objects */
typedef ptrdiff_t GLintptrARB;
typedef ptrdiff_t GLsizeiptrARB;
#endif

#ifndef GL_ARB_shader_objects
/* GL types for program/shader text and shader object handles */
typedef char GLcharARB;
# ifdef Q_OS_DARWIN
typedef void *GLhandleARB;
# else
typedef unsigned int GLhandleARB;
# endif // Q_OS_DARWIN
#endif

/* GL type for "half" precision (s10e5) float data in host memory */
#ifndef GL_ARB_half_float_pixel
typedef unsigned short GLhalfARB;
#endif

#ifndef GL_NV_half_float
typedef unsigned short GLhalfNV;
#endif

#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && (defined(__GNUC__) || defined(_MSC_VER))
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif

#ifndef GL_EXT_timer_query
typedef int64_t GLint64EXT;
typedef uint64_t GLuint64EXT;
#endif

#ifndef GL_ARB_sync
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef struct __GLsync *GLsync;
#endif

#ifndef GL_ARB_cl_event
/* These incomplete types let us declare types compatible with OpenCL's cl_context and cl_event */
struct _cl_context;
struct _cl_event;
#endif

#ifndef GL_ARB_debug_output
typedef void (QT_APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const GLvoid *userParam);
#endif

#ifndef GL_AMD_debug_output
typedef void (QT_APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,GLvoid *userParam);
#endif

#ifndef GL_KHR_debug
typedef void (QT_APIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const GLvoid *userParam);
#endif

#ifndef GL_NV_vdpau_interop
typedef GLintptr GLvdpauSurfaceNV;
#endif

// End of block copied from glext.h
#endif

QT_BEGIN_NAMESPACE

// Types that aren't defined in all system's gl.h files.
typedef ptrdiff_t qopengl_GLintptr;
typedef ptrdiff_t qopengl_GLsizeiptr;


#if defined(QT_APIENTRY) && !defined(QOPENGLF_APIENTRY)
#   define QOPENGLF_APIENTRY QT_APIENTRY
#endif

# ifndef QOPENGLF_APIENTRYP
#   ifdef QOPENGLF_APIENTRY
#     define QOPENGLF_APIENTRYP QOPENGLF_APIENTRY *
#   else
#     define QOPENGLF_APIENTRY
#     define QOPENGLF_APIENTRYP *
#   endif
# endif

QT_END_NAMESPACE

#endif // QT_NO_OPENGL

#endif // QOPENGL_H
