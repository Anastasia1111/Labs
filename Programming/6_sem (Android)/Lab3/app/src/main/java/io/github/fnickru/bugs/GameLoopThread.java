package io.github.fnickru.bugs;

import android.graphics.Canvas;
import android.view.SurfaceHolder;

public class GameLoopThread extends Thread {
	
	private final static int MAX_FPS = 30;          		// How many times per second the game should be updated, drawn?
	private final static int MAX_FRAME_SKIPS = 5; 			// Maximum number of frames to be skipped
	private final static int FRAME_PERIOD = 1000 / MAX_FPS; // The frame period
	
	private SurfaceHolder surfaceHolder;
	
	private Game game;
	
	private long gameTime;

	public boolean running;

	public GameLoopThread(SurfaceHolder surfaceHolder, Game game) {
		super();

		this.surfaceHolder = surfaceHolder;
		this.game = game;
		
		this.gameTime = 0;
	}

	@Override
	public void run() {
		Canvas canvas;
		
		long beginTime;
		long timeDiff;
		int sleepTime;
		int framesSkipped;

		sleepTime = 0;
		
		while(running){
			canvas = null;
			
			try {
				canvas = this.surfaceHolder.lockCanvas();
				synchronized(surfaceHolder) {
					beginTime = System.currentTimeMillis();
					framesSkipped = 0;
					
					this.game.update(this.gameTime);
					this.game.Draw(canvas);

					timeDiff = System.currentTimeMillis() - beginTime;
					sleepTime = (int)(FRAME_PERIOD - timeDiff);
					
					if (sleepTime > 0) {
						try {
							Thread.sleep(sleepTime);	
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
					
					while (sleepTime < 0 && framesSkipped < MAX_FRAME_SKIPS) {
						this.game.update(this.gameTime);
						
						sleepTime += FRAME_PERIOD;
						++framesSkipped;
					}
					
					this.gameTime += System.currentTimeMillis() - beginTime;
				}
			} catch(Exception e) {
				e.printStackTrace();
			} finally {
				if (canvas != null) {
					surfaceHolder.unlockCanvasAndPost(canvas);
				}
			}
		}
	}

}
