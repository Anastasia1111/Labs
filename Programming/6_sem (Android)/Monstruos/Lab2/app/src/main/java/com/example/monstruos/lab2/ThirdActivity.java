package com.example.monstruos.lab2;

import android.app.Activity;
import android.os.Bundle;
import android.view.Gravity;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class ThirdActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third);


        TableLayout table = new TableLayout(this);
        table.setStretchAllColumns(true);
        table.setShrinkAllColumns(true);
        table.setLayoutParams(new TableLayout.LayoutParams(
                TableLayout.LayoutParams.WRAP_CONTENT,
                TableLayout.LayoutParams.WRAP_CONTENT));

        TableRow row0 = new TableRow(this);
        TableRow.LayoutParams params = new TableRow.LayoutParams();
        params.span = 4;
        row0.setLayoutParams(params);

        TextView txt = new TextView(this);
        txt.setText("This is TABLE!!!");
        row0.addView(txt);
        row0.setGravity(Gravity.CENTER_HORIZONTAL);

        TableRow row1 = new TableRow(this);
        TextView id1 = new TextView(this);
        TextView name1 = new TextView(this);
        TextView age1 = new TextView(this);

        id1.setText("1");
        name1.setText("User Userovich");
        age1.setText("18");

        row1.addView(id1);
        row1.addView(name1);
        row1.addView(age1);
        row1.setGravity(Gravity.CENTER_HORIZONTAL);

        TableRow row2 = new TableRow(this);
        TextView id2 = new TextView(this);
        TextView name2 = new TextView(this);
        TextView age2 = new TextView(this);

        id2.setText("2");
        name2.setText("Moder Moderovich");
        age2.setText("99");

        row2.addView(id2);
        row2.addView(name2);
        row2.addView(age2);
        row2.setGravity(Gravity.CENTER_HORIZONTAL);

        table.addView(row0);
        table.addView(row1);
        table.addView(row2);

        LinearLayout Tab3 = findViewById(R.id.tab3);
        Tab3.addView(table);
    }
}
