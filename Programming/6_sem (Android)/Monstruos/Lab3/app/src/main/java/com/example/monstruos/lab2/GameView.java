package com.example.monstruos.lab2;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.util.ArrayList;
import java.util.List;

public class GameView extends SurfaceView {

    private long lastClick;

    /**Поле рисования*/
    private SurfaceHolder holder;

    /**объект класса GameView*/
    private BugManager gameLoopThread;

    /**Объект класса Sprite*/
    private List<Sprite> sprites = new ArrayList<Sprite>();
    private List<Thread> threads = new ArrayList<Thread>();

    private Sprite createSprite(int resource, double scale) {
        Bitmap bmp = BitmapFactory.decodeResource(getResources(), resource);
        bmp = Bitmap.createScaledBitmap(bmp, (int)(bmp.getWidth() * scale), (int)(bmp.getHeight() * scale), true);
        return new Sprite(this,bmp);
    }
    private void createSprites() {
        sprites.add(createSprite(R.drawable.bigbug, 0.2));
        sprites.add(createSprite(R.drawable.fastbug, 0.02));
        sprites.add(createSprite(R.drawable.fatbug, 0.13));
    }

    /**Конструктор*/
    public GameView(Context context)
    {
        super(context);
        gameLoopThread = new BugManager(this);
        holder = getHolder();

        /*Рисуем все наши объекты и все все все*/
        holder.addCallback(new SurfaceHolder.Callback() {
            /*** Уничтожение области рисования */
            public void surfaceDestroyed(SurfaceHolder holder)
            {
                boolean retry = true;
                gameLoopThread.setRunning(false);
                while (retry)
                {
                    try
                    {
                        gameLoopThread.join();
                        retry = false;
                    } catch (InterruptedException e)
                    {
                    }
                }
            }

            /** Создание области рисования */
            public void surfaceCreated(SurfaceHolder holder)
            {
                createSprites();
                gameLoopThread.setRunning(true);
                gameLoopThread.start();
            }

            /** Изменение области рисования */
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
            {
            }

        });

    }

    /**Функция рисующая все спрайты и фон*/
    protected void onDraw(Canvas canvas)
    {
        canvas.drawColor(Color.BLACK);
        for(Sprite sprite : sprites) {
            sprite.onDraw(canvas);
        }
    }

    public boolean onTouchEvent(MotionEvent event)
    {
        if (System.currentTimeMillis() - lastClick > 300)
        {
            lastClick = System.currentTimeMillis();
            float x = event.getX();
            float y = event.getY();

            synchronized (getHolder())
            {
                for (int i = sprites.size() - 1; i >= 0; i--)
                {
                    Sprite sprite = sprites.get(i);
                    if (sprite.isCollision(x, y))
                    {
                        sprites.remove(sprite);
                        break;
                    }
                }
            }
        }
        return true;
    }
}