package com.example.monstruos.lab2;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ViewGroup;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    public static final int colNum = 5;

    private SQLiteDatabase db;
    private MySQLiteDB dbHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        dbHelper = new MySQLiteDB(MainActivity.this);
        db = dbHelper.getWritableDatabase();

        TableLayout table = findViewById(R.id.sqldbtable);


        for(int i = 0; i < 50; ++i) {
            Random rand = new Random();
            Integer randInt = rand.nextInt(5)  + i * 5;
            String st_name = "st" + randInt.toString();
            randInt = rand.nextInt(7) + 18;
            String st_age = randInt.toString();
            randInt = rand.nextInt(40) + 70;
            String st_weight = randInt.toString();
            randInt = rand.nextInt(100) + 140;
            String st_height = randInt.toString();
            db.execSQL("INSERT INTO StudTable ('name', 'weight', 'height', 'age') " +
                    "VALUES ('" + st_name + "', '" + st_weight + "', '" +
                    st_height + "', '" + st_age + "')");

        }

        Cursor c;

        c = db.rawQuery("SELECT * FROM StudTable WHERE ?>0", new String[]{"_id"});
        if(c.moveToFirst()) {
            do {
                TableRow tr = new TableRow(this);
                tr.setLayoutParams(new TableRow.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
                        ViewGroup.LayoutParams.MATCH_PARENT, 1.0f));

                int index = c.getColumnIndex("_id");
                TextView labeldbId = new TextView(this);
                labeldbId.setText(c.getString(index));
                tr.addView(labeldbId);

                index = c.getColumnIndex("name");
                TextView labeldbName = new TextView(this);
                labeldbName.setText(c.getString(index));
                tr.addView(labeldbName);

                index = c.getColumnIndex("weight");
                TextView labeldbWeight = new TextView(this);
                labeldbWeight.setText(c.getString(index));
                tr.addView(labeldbWeight);

                index = c.getColumnIndex("height");
                TextView labeldbHeight = new TextView(this);
                labeldbHeight.setText(c.getString(index));
                tr.addView(labeldbHeight);

                index = c.getColumnIndex("age");
                TextView labeldbAge = new TextView(this);
                labeldbAge.setText(c.getString(index));
                tr.addView(labeldbAge);

                table.addView(tr);

            } while(c.moveToNext());
        }
    }
}
