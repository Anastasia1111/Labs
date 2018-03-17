package io.github.fnickru.bugs;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GamePanel extends SurfaceView implements SurfaceHolder.Callback {
	private Game game;
	private GameLoopThread gameLoopThread;

	private Paint paint = new Paint(Paint.ANTI_ALIAS_FLAG);

	private float initX, initY;
	private float targetX, targetY;
	private boolean drawing = true;
	
	public GamePanel(Context context) {
		super(context);

		getHolder().addCallback(this);
		gameLoopThread = new GameLoopThread(this.getHolder(), this, game);
		//game = new Game(getWidth(), getHeight(), getResources());

		setFocusable(true);

		paint.setStyle(Paint.Style.STROKE);
		paint.setStrokeWidth(3);
		paint.setColor(Color.WHITE);

		initX = targetX = 0;
		initY = targetY = 0;
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {}

	public void surfaceCreated(SurfaceHolder holder) {
		gameLoopThread.start();
	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		boolean retry = true;
		gameLoopThread.stopRun();
		while (retry) {
			try {
				gameLoopThread.join();
				retry = false;
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		int action = event.getAction();

		if(action == MotionEvent.ACTION_DOWN){
			//game.touchEvent(event);

			targetX = event.getX();
			targetY = event.getY();
			drawing = true;
		}

		return true;
	}

	@Override
	protected void onDraw(Canvas canvas) {
		//game.draw(canvas);

		if (drawing) {
			canvas.drawRGB(0, 0, 0);
			canvas.drawCircle(initX, initY, 3, paint);
			if ((initX == targetX) && (initY == targetY)) {
				drawing = false;
			} else {
				initX = (initX + targetX) / 2;
				initY = (initY + targetY) / 2;
			}
		}
	}
}
