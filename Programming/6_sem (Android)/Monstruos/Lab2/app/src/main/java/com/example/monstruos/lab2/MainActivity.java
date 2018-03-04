package com.example.monstruos.lab2;

import android.app.ActionBar;
import android.app.TabActivity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.*;

public class MainActivity extends TabActivity {



    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TabHost tabHost = findViewById(android.R.id.tabhost);
        tabHost.setup();

        TabHost.TabSpec tabSpec;

        tabSpec = tabHost.newTabSpec("tag1");
        tabSpec.setIndicator("Вкладка 1");
        Intent intent1 = new Intent().setClass(this, FstActivity.class);
        tabSpec.setContent(intent1);
        tabHost.addTab(tabSpec);

//        ListView list = findViewById(R.id.main_act_listview);
//        ArrayAdapter<String> adapt = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, names);
//        list.setAdapter(adapt);

        tabSpec = tabHost.newTabSpec("tag2");
        tabSpec.setIndicator("Вкладка 2");
        Intent intent2 = new Intent().setClass(this, SecActivity.class);
        tabSpec.setContent(intent2);
        tabHost.addTab(tabSpec);


        tabSpec = tabHost.newTabSpec("tag3");
        tabSpec.setIndicator("Вкладка 3");
        Intent intent3 = new Intent().setClass(this, ThirdActivity.class);
        tabSpec.setContent(intent3);
        tabHost.addTab(tabSpec);

        tabHost.setCurrentTabByTag("tag2");

        tabHost.setOnTabChangedListener(new TabHost.OnTabChangeListener() {
            @Override
            public void onTabChanged(String tabId) {

            }
        });
    }
}