package io.github.fnickru.bugs;

import android.graphics.Canvas;
import android.graphics.Rect;

public class Bug {
	
	public static final float initSpeed = 5;
	public static final long initTimeBetweenBugs = 1800;
	
	public static float speed;
	public static long timeBetweenBugs;
	
	public static long timeOfLastBug;
	
	public static boolean toRight = true;
	
	public static long timeBetweenSpeedups = 250;
	public static long timeOfLastSpeedup;
	
	
	public float x;
	public float y;
	
	private float velocity;
	
	public Bug(int y){
		this.y = y;
		
		if (Bug.toRight) {
			this.x = Game.screenWidth;
			velocity = speed * -1;
		} else {
			this.x = 0 - Game.bugImage.getWidth();
			velocity = speed;
		}

		Bug.toRight = !Bug.toRight;
	}
	
	public void update() {
		this.x += velocity;
	}
	
	public void draw(Canvas canvas) {
		if(velocity < 0)
			canvas.drawBitmap(Game.bugImage, x, y, null);
		else
			canvas.drawBitmap(Game.bugRightImage, x, y, null);
	}

	public boolean isTouched(int touchX, int touchY) {
		Rect duckRect = new Rect((int)this.x, (int)this.y, (int)this.x + Game.bugImage.getWidth(), (int)this.y + Game.bugImage.getHeight());
		
		return duckRect.contains(touchX, touchY);
	}

}
