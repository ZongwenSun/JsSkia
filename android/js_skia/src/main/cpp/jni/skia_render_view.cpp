#include <jni.h>
#include <memory>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "EGL/egl.h"
#include "GLES2/gl2.h"

#include "SkCanvas.h"
#include "SkColorSpace.h"
#include "SkPicture.h"
#include "SkSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"

//
// Created by 孙宗文 on 2022/12/21.
//

using OpenGLDrawingContext = struct {
    EGLContext glContext;
    EGLDisplay glDisplay;
    EGLConfig glConfig;
    sk_sp<GrDirectContext> skContext;
};

std::shared_ptr<OpenGLDrawingContext> openGlDrawingContext = nullptr;

ANativeWindow *gNativeWindow = nullptr;
int gWidth = 0;
int gHeight = 0;

EGLBoolean initializeWindow(EGLNativeWindowType nativeWindow) {
    openGlDrawingContext = std::make_shared<OpenGLDrawingContext>();
    const EGLint configAttribs[] = {EGL_RENDERABLE_TYPE,
                                    EGL_OPENGL_ES2_BIT,
                                    EGL_SURFACE_TYPE,
                                    EGL_WINDOW_BIT,
                                    EGL_ALPHA_SIZE,
                                    8,
                                    EGL_BLUE_SIZE,
                                    8,
                                    EGL_GREEN_SIZE,
                                    8,
                                    EGL_RED_SIZE,
                                    8,
                                    EGL_DEPTH_SIZE,
                                    0,
                                    EGL_STENCIL_SIZE,
                                    0,
                                    EGL_NONE};
    const EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        return EGL_FALSE;
    }
    EGLint major, minor;
    if (!eglInitialize(display, &major, &minor)) {
        return EGL_FALSE;
    }
    EGLConfig config;
    EGLint numConfigs;
    if (!eglChooseConfig(display, configAttribs, &config, 1, &numConfigs)) {
        return EGL_FALSE;
    }
    EGLSurface window = eglCreateWindowSurface(display, config, nativeWindow, NULL);
    if (window == EGL_NO_SURFACE) {
        return EGL_FALSE;
    }
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (context == EGL_NO_CONTEXT) {
        return EGL_FALSE;
    }
    if (!eglMakeCurrent(display, window, window, context)) {
        return EGL_FALSE;
    }

    openGlDrawingContext->glDisplay = display;
    openGlDrawingContext->glConfig = config;
    openGlDrawingContext->glContext = context;

    auto backendInterface = GrGLMakeNativeInterface();
    openGlDrawingContext->skContext =
            GrDirectContext::MakeGL(backendInterface);

    glViewport(0, 0, gWidth, gHeight);

    GLint buffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &buffer);

    GLint stencil;
    glGetIntegerv(GL_STENCIL_BITS, &stencil);

    GLint samples;
    glGetIntegerv(GL_SAMPLES, &samples);

    auto maxSamples =
            openGlDrawingContext->skContext->maxSurfaceSampleCountForColorType(
                    kRGBA_8888_SkColorType);

    if (samples > maxSamples)
        samples = maxSamples;

    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = buffer;
    fbInfo.fFormat = 0x8058;

    GrBackendRenderTarget _skRenderTarget =
            GrBackendRenderTarget(gWidth, gHeight, samples, stencil, fbInfo);

    sk_sp<SkSurface> _skSurface = SkSurface::MakeFromBackendRenderTarget(
            openGlDrawingContext->skContext.get(), _skRenderTarget,
            kBottomLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, nullptr, nullptr);


    SkCanvas *canvas = _skSurface->getCanvas();

    SkColor color = SkColorSetARGB(255, 255, 255, 0);
    canvas->drawColor(color);

    _skSurface->flushAndSubmit();
    eglSwapBuffers(openGlDrawingContext->glDisplay, window);

    return EGL_TRUE;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_szw_jsskia_SkiaRenderView_surfaceAvailable(JNIEnv *env, jobject thiz,
                                                    jobject m_surface, jint width,
                                                    jint height) {
    gNativeWindow = ANativeWindow_fromSurface(env, m_surface);
    gWidth = width;
    gHeight = height;
    initializeWindow(gNativeWindow);
}



extern "C"
JNIEXPORT void JNICALL
Java_com_szw_jsskia_SkiaRenderView_surfaceSizeChanged(JNIEnv *env, jobject thiz, jint width,
                                                      jint height) {
}
extern "C"
JNIEXPORT void JNICALL
Java_com_szw_jsskia_SkiaRenderView_surfaceDestroyed(JNIEnv *env, jobject thiz) {
}
