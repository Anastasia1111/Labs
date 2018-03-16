package io.github.fnickru.bugs;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    private boolean showingMainMenu;
    private GamePanel gamePanel;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        showingMainMenu = true;
    }

    @Override
    public void onBackPressed(){
        if(!showingMainMenu) {
            showingMainMenu = true;

            gamePanel.surfaceDestroyed(null);
            setContentView(R.layout.activity_main);
        } else {

            super.onBackPressed();
        }
    }

    public void onClickStartGame(View v){
        showingMainMenu = false;

        // High score
        HighScore.ctx = this.getBaseContext();
        HighScore.loadHighScore();

        // Start and show game.
        gamePanel = new GamePanel(this);
        setContentView(gamePanel);
    }
}
