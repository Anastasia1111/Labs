package io.github.fnickru.bugs;

import android.content.res.Resources;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.view.View;

import java.util.ArrayList;
import java.util.Random;

public class Game {
    public static final int SESSION_TIME = 120000; // 2 min


    private int width;
    private int height;
    private float screenDensity;
    private Paint paintText;
    private int textSize;
    private float textForRestart_x;
    private float textForRestart_y;

    private View view;

    private boolean gameOver;

    private ArrayList<Bug> bugs;
    private int bugsKilled;
    private Random random = new Random();

    private long timeOfLastBug;
    public static final long timeBetweenBugs = 5000; // 5 sec

    public int getScore() {
        return bugsKilled;
    }

    public Game(int width, int height, View view) {
        Resources resources = view.getResources();
        this.width = width;
        this.height = height;
        screenDensity = resources.getDisplayMetrics().density;
        textSize = 25;
        paintText = new Paint();
        paintText.setColor(Color.BLACK);
        paintText.setTextSize(textSize * screenDensity);
        textForRestart_x = width /2 - 95 * screenDensity;
        textForRestart_y = height / 2 - 20;

        this.view = view;

        bugs = new ArrayList<>();
        resetGame();
    }

    private void resetGame() {
        gameOver = false;

        bugs.clear();
        bugsKilled = 0;

        addNewBug();
        addNewBug();

        timeOfLastBug = 0;
    }

    public void update(long gameTime) {
        if (gameOver) {
            return;
        }

        if ((gameTime - timeOfLastBug) > timeBetweenBugs) {
            timeOfLastBug = gameTime;
            addNewBug();
        }
    }

    public void touchHandler(MotionEvent event){
        if (!gameOver) {
            this.checkIfAnyBugSmashed(event.getX(), event.getY());
        } else {
            if(event.getX() > textForRestart_x && event.getX() < textForRestart_x + 280 &&
                    event.getY() > textForRestart_y - 50 && event.getY() < textForRestart_y + 50) {
                this.resetGame();
            }
        }
    }

    private void checkIfAnyBugSmashed(float touchX, float touchY){
        for (int i = 0; i < bugs.size(); ++i) {
            Bug Bug = bugs.get(i);

            if (Bug.isTouched((int)touchX, (int)touchY)) {
                bugs.remove(i);
                ++bugsKilled;
            }
        }
    }

    public void draw(Canvas canvas) {
        for (Bug bug : bugs) {
            bug.draw(canvas);
        }
        canvas.drawText("Score: " + Integer.toString(this.bugsKilled), 8.0f, 25.0f * screenDensity, paintText);

        if (gameOver) {
            canvas.drawText("Game over", width/2 - 65 * screenDensity, height / 3, paintText);
            canvas.drawText("Touch to restart", textForRestart_x, textForRestart_y, paintText);
        }
    }

    private void addNewBug() {
        Bug bug = new Bug(view);
        bug.setY(random.nextFloat() * height);
        bugs.add(bug);
        new Thread(bug).start();
    }
}
