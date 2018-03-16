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
	
	public static int screenWidth;
	public static int screenHeight;
	public static float screenDensity;
	
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

	
	public Game(int screenWidth, int screenHeight, Resources resources) {
		Game.screenWidth = screenWidth;
		Game.screenHeight = screenHeight;
		Game.screenDensity = resources.getDisplayMetrics().density;
		
		this.loadContent(resources);
		
		destBackgroundImage = new Rect(0, 0, screenWidth, screenHeight);
		
		paintForImages = new Paint();
		paintForImages.setFilterBitmap(true);
		
		aliveBugs = new ArrayList<>();
		
		textSize = 25;
		paintText = new Paint();
		paintText.setColor(Color.BLACK);
		paintText.setTextSize(textSize * Game.screenDensity);

		textForRestart_x = Game.screenWidth/2 - 95 * Game.screenDensity;
		textForRestart_y = Game.screenHeight / 2 - 20;
		
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
		
		for (int i = 0; i < aliveBugs.size(); i++) {
			Bug Bug = aliveBugs.get(i);
			
			Bug.update();
			
			if(Bug.x > Game.screenWidth || Bug.x < 0 - Game.bugImage.getWidth()){
				gameOver = true;
				
				if(bugsKilled > HighScore.highScore){
					HighScore.highScore = bugsKilled;
					HighScore.saveHighScore();
				}
			}
		}
		
		if( (gameTime - Bug.timeOfLastSpeedup) > Bug.timeBetweenSpeedups ){
			Bug.timeOfLastSpeedup = gameTime;
			
			Bug.speed += 0.03;
			if(Bug.timeBetweenBugs > (0.5 * 1000))
				Bug.timeBetweenBugs -= 90;
		}
	}

	public void Draw(Canvas canvas) {
		canvas.drawColor(Color.BLACK);

		canvas.drawBitmap(Game.backgroundImage, null, this.destBackgroundImage, this.paintForImages);

		for (int i = 0; i < aliveBugs.size(); i++) {
			aliveBugs.get(i).draw(canvas);
		}

		canvas.drawText("Score: "      + Integer.toString(this.bugsKilled), 8.0f, 25.0f * Game.screenDensity, paintText);
		canvas.drawText("High score: " + Integer.toString(HighScore.highScore),  8.0f, textSize * 2 * Game.screenDensity, paintText);
		
		if (gameOver) {
			canvas.drawText("Game over", Game.screenWidth/2 - 65 * Game.screenDensity, Game.screenHeight / 3, paintText);
			canvas.drawText("Touch to restart", textForRestart_x, textForRestart_y, paintText);
		}
	}

	public void touchEvent_actionDown(MotionEvent event){
    	if(!gameOver){
    		this.checkIfAnyBugSmashed(event.getX(), event.getY());
    	} else {
    		if(event.getX() > textForRestart_x && event.getX() < textForRestart_x + 280 &&
    		   event.getY() > textForRestart_y - 50 && event.getY() < textForRestart_y + 50){
    			this.resetGame();
    		}
    	}
    }

    public void touchEvent_actionMove(MotionEvent event){
    	
    }

    public void touchEvent_actionUp(MotionEvent event){
    	
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
    	int min = (Game.screenHeight /2) + Game.bugImage.getHeight();
    	int max = Game.screenHeight;
    	
    	int height = Math.abs(max - min);
    	
    	int newYcoordiante = this.random.nextInt(height) + min;
    			
    	return newYcoordiante;
    }

    private void addNewBug() {
    	this.aliveBugs.add(new Bug(newYcoordinate()));
    }
    
}
