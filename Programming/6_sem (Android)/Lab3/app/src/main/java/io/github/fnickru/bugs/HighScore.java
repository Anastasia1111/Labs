package io.github.fnickru.bugs;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

import android.content.Context;

public class HighScore {
	public static Context ctx;
	
	private static final String HIGHSCORE_FILE_NAME = "high_score";
	
	public static int highScore = 0;

    public static void load() {
    	try {
	        File file = HighScore.ctx.getFileStreamPath(HIGHSCORE_FILE_NAME);

	        if(file.exists()) {
		        FileInputStream in = HighScore.ctx.openFileInput(HIGHSCORE_FILE_NAME);
		        InputStreamReader inputStreamReader = new InputStreamReader(in);
		        BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
		        String line;
		        while ((line = bufferedReader.readLine()) != null) {
		        	HighScore.highScore = Integer.parseInt(line);
		        }
		        bufferedReader.close();
		        inputStreamReader.close();
		        in.close();
	        }
        } catch (Exception e) {
        	System.err.println("Error reading high score!");
        	e.printStackTrace();
        }
	}
	
	public static void save() {
    	try {
            FileOutputStream out = HighScore.ctx.openFileOutput(HIGHSCORE_FILE_NAME, Context.MODE_PRIVATE);
            OutputStreamWriter writer = new OutputStreamWriter(out);

            writer.write(String.valueOf(HighScore.highScore));

            writer.flush();
            writer.close();
            out.close();
    	} catch (Exception e) {
    		System.err.println("Error saving high score!");
        	e.printStackTrace();
    	}
	}
	
}
