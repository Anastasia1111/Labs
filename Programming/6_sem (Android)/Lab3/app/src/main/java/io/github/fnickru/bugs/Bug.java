package io.github.fnickru.bugs;

import android.content.res.Resources;
import android.graphics.*;
import android.view.View;

public class Bug implements Runnable {
    private Paint p;

    private float x = 100;
    private float y = 100;
    private int size = 250;
    private float speed = 10;

    private Bitmap bitmap;
    private View view;

    private boolean isMoving;

    public Bug(View view) {
        this.view = view;

        p = new Paint();
        p.setColor(Color.GREEN);
        Resources res = view.getResources();
        bitmap = Bitmap.createScaledBitmap(BitmapFactory.decodeResource(res, R.drawable.bug), size, size, false);
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public boolean isMoving() {
        return isMoving;
    }

    public void draw(Canvas canvas) {
        canvas.drawBitmap(bitmap, x, y, p);
    }

    public boolean isTouched(float touchX, float touchY) {
        return touchX >= x && touchX <= x + bitmap.getWidth() && touchY >= y && touchY <= y + bitmap.getHeight();
    }

    public void stop() {
        isMoving = false;
    }

    @Override
    public void run() {
        isMoving = true;

        while (isMoving && x < view.getWidth()) {
            x += speed;
            try {
                Thread.sleep(250);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
