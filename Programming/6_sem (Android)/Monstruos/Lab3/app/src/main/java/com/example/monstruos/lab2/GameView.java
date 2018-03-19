package com.example.monstruos.lab2;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.AudioManager;
import android.media.SoundPool;
import android.os.CountDownTimer;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.util.*;

public class GameView extends SurfaceView implements
        SurfaceHolder.Callback {

    private SoundPool soundPool;
    private volatile int score;

    /**объект класса GameView*/
    private BugManager gameLoopThread;

    /**Объект класса Sprite*/
    private List<Sprite> sprites = new ArrayList<>();
    private Map<String, Integer> sounds = new HashMap<>();

    private Sprite createSprite(int resource, double scale) {
        Bitmap bmp = BitmapFactory.decodeResource(getResources(), resource);
        bmp = Bitmap.createScaledBitmap(bmp, (int)(bmp.getWidth() * scale), (int)(bmp.getHeight() * scale), true);
        return new Sprite(this,bmp);
    }
    private void createSprites() {
        final Random random = new Random();
        new CountDownTimer(BugManager.GAME_TIME, 1000) {
            @Override
            public void onTick(long millisUntilFinished) {
                int r = random.nextInt(3);
                switch (r) {
                    case 0:
                        Sprite bigbug = createSprite(R.drawable.bigbug, 0.2);
                        new Thread(bigbug).start();
                        sprites.add(bigbug);
                        break;
                    case 1:
                        Sprite fastbug = createSprite(R.drawable.fastbug, 0.02);
                        new Thread(fastbug).start();
                        sprites.add(fastbug);
                        break;
                    default:
                        Sprite fatbug = createSprite(R.drawable.fatbug, 0.13);
                        new Thread(fatbug).start();
                        sprites.add(fatbug);
                }
            }

            @Override
            public void onFinish() {
                for(Sprite sprite : sprites) {
                    sprite.setAlive(false);
                }
            }
        }.start();
    }

    /**Конструктор*/
    public GameView(Context context) {
        super(context);
        gameLoopThread = new BugManager(this);

        /*Рисуем все наши объекты и все все все*/
        getHolder().addCallback(this);

        soundPool = new SoundPool(60, AudioManager.STREAM_MUSIC, 0);
        sounds.put("vil", soundPool.load(context, R.raw.vilgelm, 1));

        score = 0;
    }

    /**Функция рисующая все спрайты и фон*/
    /*protected void draw(Canvas canvas) {
        canvas.drawColor(Color.BLACK);
        for(Sprite sprite : sprites) {
            sprite.draw(canvas);
        }
    }*/

    public List<Sprite> getSprites() {
        return sprites;
    }

    public boolean onTouchEvent(MotionEvent event) {
        float x = event.getX();
        float y = event.getY();

        if (event.getAction() == MotionEvent.ACTION_DOWN)
            synchronized (getHolder())
            {
                boolean isCatched = false;
                for (int i = sprites.size() - 1; i >= 0; i--)
                {
                    Sprite sprite = sprites.get(i);
                    if (sprite.isCollision(x, y))
                    {
                        ++score;
                        isCatched = true;
                        soundPool.play(1, 100, 100, 1, 0, 1);
                        sprite.setAlive(false);
                        sprites.remove(sprite);
                        break;
                    }
                }
                if (!isCatched)
                    --score;
            }
        return true;
    }

    /*** Уничтожение области рисования */
    public void surfaceDestroyed(SurfaceHolder holder) {
        boolean retry = true;
        gameLoopThread.setRunning(false);
        while (retry)
        {
            try
            {
                gameLoopThread.join();
                retry = false;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    /** Создание области рисования */
    public void surfaceCreated(SurfaceHolder holder) {
        createSprites();
        gameLoopThread.setRunning(true);
        gameLoopThread.start();
    }

    /** Изменение области рисования */
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    }

    public int getScore() {
        return score;
    }
}