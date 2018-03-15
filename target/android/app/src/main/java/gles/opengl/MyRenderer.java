package gles.opengl;

import android.content.res.AssetManager;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyRenderer implements GLSurfaceView.Renderer {
    static {
        System.loadLibrary("native-lib");
    }

    AppCompatActivity activity;

    public MyRenderer(AppCompatActivity activity) {
        this.activity = activity;
    }

    public static native void nativeSurfaceCreate(AssetManager assetManager);

    public static native void nativeSurfaceChange(int width, int height);

    public static native void nativeDrawFrame();

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

        GLES30.glClearColor(1.0f,0.0f,1.0f,1.0f);
        nativeSurfaceCreate(activity.getAssets());
     }

    @Override
    public void onSurfaceChanged(GL10 gl10, int w, int h) {
        GLES30.glViewport(0,0,w, h);
        nativeSurfaceChange(w, h);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {

        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT| GLES30.GL_DEPTH_BUFFER_BIT);
        nativeDrawFrame();
    }
}
