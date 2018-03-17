package io.github.fnickru.bugs;

import android.content.Context;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GameView extends SurfaceView implements
        SurfaceHolder.Callback {
    private Bug bug;
    private DrawThread thread;
    private Game game;

    public GameView(Context context) {
        super(context);
        getHolder().addCallback(this);

        game = new Game(getWidth(), getHeight(), this);
        thread = new DrawThread(getHolder(), this, game);

        setFocusable(true);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        game.touchHandler(event);
        return true;
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        thread.setRunning(true);
        thread.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        boolean retry = true;
        thread.setRunning(false);
        while (retry) {
            try {
                thread.join();
                retry = false;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
