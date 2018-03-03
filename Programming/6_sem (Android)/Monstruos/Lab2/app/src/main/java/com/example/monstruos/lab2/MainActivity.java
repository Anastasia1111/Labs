package com.example.monstruos.lab2;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Gravity;
import android.view.View;
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

//        Intent intent1 = new Intent(this, FstActivity.class);
        tabSpec = tabHost.newTabSpec("tag1");
        tabSpec.setIndicator("Вкладка 1");
        tabSpec.setContent(R.id.tab1);
        tabHost.addTab(tabSpec);

//        Intent intent2 = new Intent(this, SecActivity.class);
        ListView list = findViewById(R.id.main_act_listview);
        ArrayAdapter<String> adapt = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, names);
        list.setAdapter(adapt);

        tabSpec = tabHost.newTabSpec("tag2");
        tabSpec.setIndicator("Вкладка 2");
        tabSpec.setContent(R.id.tab2);
        tabHost.addTab(tabSpec);

//        Intent intent3 = new Intent(this, ThirdActivity.class);
        TableLayout t = new TableLayout(this);
        TableRow r = new TableRow(this);

        t.setShrinkAllColumns(true);
        t.setStretchAllColumns(true);

        TextView txt = new TextView(this);
        txt.setText("new");

        r.addView(txt);
        r.setGravity(Gravity.CENTER);

        t.addView(r);



        tabSpec = tabHost.newTabSpec("tag3");
        tabSpec.setIndicator("Вкладка 3");
        tabSpec.setContent();
        tabHost.addTab(tabSpec);

        tabHost.setCurrentTabByTag("tag2");
    }
}