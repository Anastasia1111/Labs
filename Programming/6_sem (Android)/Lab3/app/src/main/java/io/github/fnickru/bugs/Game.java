package io.github.fnickru.bugs;

import java.util.ArrayList;
import java.util.Random;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.view.MotionEvent;

public class Game {
	
	public static int width;
	public static int height;
	private static float screenDensity;
	
	private boolean gameOver;
	
	private Rect destBackgroundImage;
	private Paint paintForImages;
	
	private static Bitmap backgroundImage;
	public static Bitmap bugImage;
	public static Bitmap bugRightImage;
	
	private ArrayList<Bug> aliveBugs;
	
	private int bugsKilled;
	
	private Paint paintText;
	private int textSize;
	
	private Random random = new Random();
	
	private float textForRestart_x;
	private float textForRestart_y;

	
	public Game(int width, int height, Resources resources) {
		Game.width = width;
		Game.height = height;
		Game.screenDensity = resources.getDisplayMetrics().density;
		
		this.loadContent(resources);
		
		destBackgroundImage = new Rect(0, 0, width, height);
		
		paintForImages = new Paint();
		paintForImages.setFilterBitmap(true);
		
		aliveBugs = new ArrayList<>();
		
		textSize = 25;
		paintText = new Paint();
		paintText.setColor(Color.BLACK);
		paintText.setTextSize(textSize * Game.screenDensity);

		textForRestart_x = Game.width /2 - 95 * Game.screenDensity;
		textForRestart_y = Game.height / 2 - 20;
		
		this.resetGame();
	}

	private void loadContent(Resources resources) {
		backgroundImage = BitmapFactory.decodeResource(resources, R.drawable.bg);
		bugImage = BitmapFactory.decodeResource(resources, R.drawable.bug);
		
		Matrix matrix = new Matrix();
		matrix.preScale(-1.0f, 1.0f);
		bugRightImage = Bitmap.createBitmap(bugImage, 0, 0, bugImage.getWidth(), bugImage.getHeight(), matrix, false);
	}

	private void resetGame() {
		gameOver = false;
		
		aliveBugs.clear();
		
		Bug.speed = Bug.initSpeed;
		Bug.timeBetweenBugs = Bug.initTimeBetweenBugs;
		Bug.timeOfLastBug = 0;
		
		Bug.timeOfLastSpeedup = 0;
		
		bugsKilled = 0;
		
		this.addNewBug();
		this.addNewBug();
	}
	
	public void update(long gameTime) {
		if (gameOver) {
			return;
		}
		
		if ((gameTime - Bug.timeOfLastBug) > Bug.timeBetweenBugs ) {
			Bug.timeOfLastBug = gameTime;
			
			this.addNewBug();
		}
		
		if( (gameTime - Bug.timeOfLastSpeedup) > Bug.timeBetweenSpeedups ){
			Bug.timeOfLastSpeedup = gameTime;
			
			Bug.speed += 0.03;
			if(Bug.timeBetweenBugs > (0.5 * 1000))
				Bug.timeBetweenBugs -= 90;
		}
	}

	public void draw(Canvas canvas) {
		canvas.drawColor(Color.BLACK);

		canvas.drawBitmap(Game.backgroundImage, null, this.destBackgroundImage, this.paintForImages);

        for (Bug bug : aliveBugs) {
            bug.draw(canvas);
        }

        canvas.drawText("Score: "      + Integer.toString(this.bugsKilled), 8.0f, 25.0f * Game.screenDensity, paintText);
		canvas.drawText("High score: " + Integer.toString(HighScore.highScore),  8.0f, textSize * 2 * Game.screenDensity, paintText);
		
		if (gameOver) {
			canvas.drawText("Game over", Game.width /2 - 65 * Game.screenDensity, Game.height / 3, paintText);
			canvas.drawText("Touch to restart", textForRestart_x, textForRestart_y, paintText);
		}
	}

	public void touchEvent(MotionEvent event){
    	if(!gameOver){
    		this.checkIfAnyBugSmashed(event.getX(), event.getY());
    	} else {
    		if(event.getX() > textForRestart_x && event.getX() < textForRestart_x + 280 &&
    		   event.getY() > textForRestart_y - 50 && event.getY() < textForRestart_y + 50){
    			this.resetGame();
    		}
    	}
    }

    private void checkIfAnyBugSmashed(float touchX, float touchY){
    	for (int i = 0; i < aliveBugs.size(); i++) {
    		Bug Bug = aliveBugs.get(i);
    		
    		if(Bug.isTouched((int)touchX, (int)touchY)){
    			aliveBugs.remove(i);
    			bugsKilled++;
    		}
    	}
    }

    private int newYcoordinate(){
    	int min = (Game.height /2) + Game.bugImage.getHeight();
    	int max = Game.height;
    	
    	int height = Math.abs(max - min);
    	
    	int newYcoordiante = this.random.nextInt(height) + min;
    			
    	return newYcoordiante;
    }

    private void addNewBug() {
		Bug bug = new Bug(newYcoordinate());
    	this.aliveBugs.add(bug);
		bug.run();
    }
    
}
