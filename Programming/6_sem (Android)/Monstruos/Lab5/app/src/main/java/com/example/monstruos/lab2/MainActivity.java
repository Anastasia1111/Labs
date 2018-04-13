package com.example.monstruos.lab2;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ViewGroup;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

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
        TableRow headtr = new TableRow(this);
        headtr.setPadding(2, 0, 10, 0);
        TextView htv1 = new TextView(this);
        htv1.setText("ID");
        headtr.addView(htv1);
        TextView htv2 = new TextView(this);
        htv2.setText("Name");
        headtr.addView(htv2);
        TextView htv3 = new TextView(this);
        htv3.setText("Weight");
        headtr.addView(htv3);
        TextView htv4 = new TextView(this);
        htv4.setText("Height");
        headtr.addView(htv4);
        TextView htv5 = new TextView(this);
        htv5.setText("Age");
        headtr.addView(htv5);
        table.addView(headtr);

        Cursor c;

        c = db.rawQuery("SELECT * FROM StudTable ORDER BY age DESC", null);

        if(c.moveToFirst()) {
            do {
                TableRow tr = new TableRow(this);
                tr.setPadding(2, 0, 10, 0);


                int index = c.getColumnIndex("_id");
                TextView labeldbId = new TextView(this);
                labeldbId.setPadding(0, 0 ,30 ,0);
                labeldbId.setText(c.getString(index));
                tr.addView(labeldbId);

                index = c.getColumnIndex("name");
                TextView labeldbName = new TextView(this);
                labeldbName.setPadding(0, 0 ,30 ,0);
                labeldbName.setText(c.getString(index));
                tr.addView(labeldbName);

                index = c.getColumnIndex("weight");
                TextView labeldbWeight = new TextView(this);
                labeldbWeight.setPadding(0, 0 ,30 ,0);
                labeldbWeight.setText(c.getString(index));
                tr.addView(labeldbWeight);

                index = c.getColumnIndex("height");
                TextView labeldbHeight = new TextView(this);
                labeldbHeight.setPadding(0, 0 ,30 ,0);
                labeldbHeight.setText(c.getString(index));
                tr.addView(labeldbHeight);

                index = c.getColumnIndex("age");
                TextView labeldbAge = new TextView(this);
                labeldbAge.setText(c.getString(index));
                tr.addView(labeldbAge);
                tr.setPadding(0, 0, 0, 10);



                table.addView(tr);

            } while(c.moveToNext());
        }
    }
}
