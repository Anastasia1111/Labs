package io.github.fnickru.bugs;

import android.graphics.Canvas;
import android.graphics.Rect;

public class Bug implements Runnable {
	
	public static final float initSpeed = 5;
	public static final long initTimeBetweenBugs = 1800;
	
	public static float speed;
	public static long timeBetweenBugs;
	
	public static long timeOfLastBug;
	
	private static boolean toRight = true;
	
	public static long timeBetweenSpeedups = 250;
	public static long timeOfLastSpeedup;
	
	
	private float x;
	private float y;
	
	private float velocity;
	
	public Bug(int y){
		this.y = y;
		
		if (Bug.toRight) {
			this.x = Game.width;
			velocity = speed * -1;
		} else {
			this.x = 0 - Game.bugImage.getWidth();
			velocity = speed;
		}

		Bug.toRight = !Bug.toRight;
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

	private void update() {
		this.x += velocity;
	}
	
	public void draw(Canvas canvas) {
		if(velocity < 0)
			canvas.drawBitmap(Game.bugImage, x, y, null);
		else
			canvas.drawBitmap(Game.bugRightImage, x, y, null);
	}

	public boolean isTouched(int touchX, int touchY) {
		Rect bugRect = new Rect((int)this.x, (int)this.y, (int)this.x + Game.bugImage.getWidth(), (int)this.y + Game.bugImage.getHeight());
		
		return bugRect.contains(touchX, touchY);
	}

	@Override
	public void run() {
		update();

		while (x < Game.width && x > 0 - Game.bugImage.getWidth()) {
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			} finally {
				update();
			}
		}
	}
}
