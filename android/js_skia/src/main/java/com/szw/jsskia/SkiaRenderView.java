package com.szw.jsskia;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.view.Surface;
import android.view.TextureView;

import androidx.annotation.NonNull;

public class SkiaRenderView extends TextureView implements TextureView.SurfaceTextureListener {
    private Surface mSurface;

    public SkiaRenderView(@NonNull Context context) {
        super(context);
        setSurfaceTextureListener(this);
    }

    @Override
    public void onSurfaceTextureAvailable(@NonNull SurfaceTexture surfaceTexture, int width, int height) {
        mSurface = new Surface(surfaceTexture);
        surfaceAvailable(mSurface, width, height);
    }

    @Override
    public void onSurfaceTextureSizeChanged(@NonNull SurfaceTexture surfaceTexture, int width, int height) {
        surfaceSizeChanged(width,height);
    }

    @Override
    public boolean onSurfaceTextureDestroyed(@NonNull SurfaceTexture surfaceTexture) {
        surfaceDestroyed();
        mSurface.release();
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(@NonNull SurfaceTexture surfaceTexture) {
        // Nothing special to do here
    }

    protected native void surfaceAvailable(Surface mSurface, int width, int height);

    protected native void surfaceSizeChanged(int width, int height);

    protected native void surfaceDestroyed();
}
