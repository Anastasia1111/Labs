package io.github.fnickru.bugs;

import android.graphics.Canvas;
import android.view.SurfaceHolder;

public class GameLoopThread extends Thread {
	private SurfaceHolder surfaceHolder;
	private GamePanel surfaceView;
	private boolean running;
	
	private Game game;
	private long gameTime;

	public GameLoopThread(SurfaceHolder surfaceHolder,
						  GamePanel gamePanel,
						  Game game) {
		super();

		this.surfaceHolder = surfaceHolder;
		this.surfaceView = gamePanel;
		this.game = game;
		
		this.gameTime = 0;
	}

	public void stopRun()
	{
		running = false;
	}

	@Override
	public void run() {
		running = true;

		Canvas canvas;

		long beginTime;
		long timeDiff;
		int sleepTime;
		int framesSkipped;
		
		while(running){
			canvas = null;
			
			try {
				canvas = this.surfaceHolder.lockCanvas();

				synchronized(surfaceHolder) {
					//game.update(gameTime);
					beginTime = System.currentTimeMillis();

					surfaceView.draw(canvas);
					/*framesSkipped = 0;
					
					this.game.update(this.gameTime);
					this.game.draw(canvas);

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
					}*/
					
					this.gameTime += System.currentTimeMillis() - beginTime;
				}

				sleep(500);
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
