package io.github.fnickru.bugs;

import android.graphics.Canvas;
import android.graphics.Color;
import android.view.SurfaceHolder;

class DrawThread extends Thread {

    private boolean running = false;
    private SurfaceHolder surfaceHolder;
    private GameView surfaceView;

    private Game game;
    private long gameTime;

    public static final int FPS = 30;
    public static final int FRAME_PERIOD = 1000 / FPS;

    public DrawThread(SurfaceHolder surfaceHolder,
                      GameView surfaceView,
                      Game game) {
        this.surfaceHolder = surfaceHolder;
        this.surfaceView = surfaceView;
        this.game = game;

        this.gameTime = 0;
    }

    public void setRunning(boolean running) {
        this.running = running;
    }

    private void draw(Canvas canvas) {
        canvas.drawColor(Color.BLACK);
        game.draw(canvas);
    }

    @Override
    public void run() {
        long beginTime = System.currentTimeMillis();

        while (running && gameTime < Game.SESSION_TIME) {
            Canvas c = null;
            try {
                c = surfaceHolder.lockCanvas(null);
                if (c == null)
                    continue;

                game.update(gameTime);
                draw(c);
                sleep(FRAME_PERIOD);
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                if (c != null) {
                    surfaceHolder.unlockCanvasAndPost(c);
                }
                gameTime = System.currentTimeMillis() - beginTime;
            }
        }
    }
}
