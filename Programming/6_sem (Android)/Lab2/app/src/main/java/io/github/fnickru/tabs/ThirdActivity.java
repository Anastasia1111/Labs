package io.github.fnickru.tabs;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Gravity;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class ThirdActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third);

        TableLayout table = new TableLayout(this);

        table.setShrinkAllColumns(true);
        table.setStretchAllColumns(true);
        table.setLayoutParams(new TableLayout.LayoutParams(
                TableLayout.LayoutParams.WRAP_CONTENT,
                TableLayout.LayoutParams.WRAP_CONTENT));

        TableRow[] row = new TableRow[3];
        TextView[] id = new TextView[3];
        TextView[] name = new TextView[3];
        TextView[] age = new TextView[3];

        for (int i = 0; i < 3; ++i)
        {
            row[i] = new TableRow(this);
            id[i] = new TextView(this);
            name[i] = new TextView(this);
            age[i] = new TextView(this);
        }

        id[0].setText("id");
        name[0].setText("Name");
        age[0].setText("Age");

        row[0].addView(id[0]);
        row[0].addView(name[0]);
        row[0].addView(age[0]);
        row[0].setGravity(Gravity.CENTER_HORIZONTAL);

        id[1].setText("1");
        name[1].setText("John Smith");
        age[1].setText("24");

        row[1].addView(id[1]);
        row[1].addView(name[1]);
        row[1].addView(age[1]);
        row[1].setGravity(Gravity.CENTER_HORIZONTAL);

        id[2].setText("2");
        name[2].setText("Smith John");
        age[2].setText("42");

        row[2].addView(id[2]);
        row[2].addView(name[2]);
        row[2].addView(age[2]);
        row[2].setGravity(Gravity.CENTER_HORIZONTAL);

        table.addView(row[0]);
        table.addView(row[1]);
        table.addView(row[2]);

        setContentView(table);
    }
}
