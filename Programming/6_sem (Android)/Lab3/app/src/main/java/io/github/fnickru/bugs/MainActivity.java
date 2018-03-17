package io.github.fnickru.bugs;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    private boolean isMenuShown;
    private GamePanel gamePanel;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.activity_main);
        //isMenuShown = true;

        onClickStartGame(null);
    }

    /*@Override
    public void onBackPressed(){
        if(!isMenuShown) {
            isMenuShown = true;

            gamePanel.surfaceDestroyed(null);
            setContentView(R.layout.activity_main);
        } else {
            super.onBackPressed();
        }
    }*/

    public void onClickStartGame(View v){
        isMenuShown = false;

        HighScore.ctx = this.getBaseContext();
        HighScore.load();

        gamePanel = new GamePanel(this);
        setContentView(gamePanel);
    }
}
