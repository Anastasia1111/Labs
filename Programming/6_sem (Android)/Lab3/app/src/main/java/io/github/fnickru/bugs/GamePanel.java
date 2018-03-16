package io.github.fnickru.bugs;

import android.content.Context;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GamePanel extends SurfaceView implements SurfaceHolder.Callback {
	
	private Game game;
	private GameLoopThread gameLoopThread;
	
	public GamePanel(Context context) {
		super(context);

		this.setFocusable(true);

		this.getHolder().addCallback(this);
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {}

	public void surfaceCreated(SurfaceHolder holder) {
		startGame();
	}
	
	private void startGame(){
		game = new Game(getWidth(), getHeight(), getResources());
		
		gameLoopThread = new GameLoopThread(this.getHolder(), game);
		
		gameLoopThread.running = true;
		gameLoopThread.start();
	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		gameLoopThread.running = false;

		boolean retry = true;
		while(retry) {
			try {
				gameLoopThread.join();
				retry = false;
			} catch (InterruptedException e) {}
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {

		int action = event.getAction();
		
		if(action == MotionEvent.ACTION_DOWN){
			game.touchEvent_actionDown(event);
		}
		
		if(action == MotionEvent.ACTION_MOVE) {
			game.touchEvent_actionMove(event);
		}
		
		if(action == MotionEvent.ACTION_UP){
			game.touchEvent_actionUp(event);
		}
		
		return true;
	}
	
}
