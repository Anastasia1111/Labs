package com.example.monstruos.lab2;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import java.util.Random;
import android.graphics.Rect;
import android.media.MediaPlayer;

public class Sprite implements Runnable{

    /**Объект класса GameView*/
    private GameView gameView;

    /**Картинка*/
    private Bitmap bmp;

    /**Позиция по Х=0*/
    private int x = 5;
    private int y = 0;

    private int xSpeed = 5;
    private int ySpeed = 5;

    private int width;
    private int height;

    private boolean isAlive = false;

    /**Конструктор*/
    public Sprite(GameView gameView, Bitmap bmp)
    {
        this.gameView = gameView;
        this.bmp = bmp;
        this.width = bmp.getWidth();
        this.height = bmp.getHeight();

        Random rnd = new Random();
        xSpeed = rnd.nextInt(10)-5;
        ySpeed = rnd.nextInt(10)-5;
        x = rnd.nextInt(gameView.getWidth() - width);
        y = rnd.nextInt(gameView.getHeight() - height);
    }

    /**Перемещение объекта, его направление*/
    private void update()
    {
        if (x >= gameView.getWidth() - width - xSpeed || x + xSpeed <= 0) {
            xSpeed = -xSpeed;
        }
        x = x + xSpeed;
        if (y >= gameView.getHeight() - height - ySpeed || y + ySpeed <= 0) {
            ySpeed = -ySpeed;
        }
        y = y + ySpeed;
    }

    public boolean isCollision(float x2, float y2) {
        return x2 > x && x2 < x + width && y2 > y && y2 < y + height;
    }

    /**Рисуем наши спрайты*/
    public void draw(Canvas canvas)
    {
        //update();
        int srcX = 0;
        int srcY = 0;
        Rect src = new Rect(0, 0, srcX + width, srcY + height);
        Rect dst = new Rect(x, y, x + width, y + height);
        canvas.drawBitmap(bmp, src, dst, null);
    }

    public boolean isAlive() {
        return isAlive;
    }

    public void setAlive(boolean alive) {
        isAlive = alive;
    }

    @Override
    public void run() {
        isAlive = true;
        while (isAlive) {
            update();
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
