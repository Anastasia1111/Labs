package com.example.monstruos.lab2;

import android.app.ActionBar;
import android.content.Intent;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Layout;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;

public class MainActivity extends AppCompatActivity {

    final String[] names = new String[] {
            "Я", "Не я", "Не он", "Не она", "Она", "Он", "A", "r", "qwe0", "retet", "dflgk", "w9867"
    };

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TabHost tabHost = findViewById(android.R.id.tabhost);
        tabHost.setup();

        TabHost.TabSpec tabSpec;

        tabSpec = tabHost.newTabSpec("tag1");
        tabSpec.setIndicator("Вкладка 1");
        tabSpec.setContent(R.id.tab1);
        tabHost.addTab(tabSpec);

        ListView list = findViewById(R.id.main_act_listview);
        ArrayAdapter<String> adapt = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, names);
        list.setAdapter(adapt);

        tabSpec = tabHost.newTabSpec("tag2");
        tabSpec.setIndicator("Вкладка 2");
        tabSpec.setContent(R.id.tab2);
        tabHost.addTab(tabSpec);

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

        tabSpec = tabHost.newTabSpec("tag3");
        tabSpec.setIndicator("Вкладка 3");
        tabSpec.setContent(R.id.tab3);
        tabHost.addTab(tabSpec);

        tabHost.setCurrentTabByTag("tag2");
    }
}