package com.example.monstruos.lab2;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class SecActivity extends AppCompatActivity {

    final String[] names = new String[] {
            "Я", "Не я", "Не он", "Не она", "Она", "Он"
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sec);

//        ListView list = findViewById(R.id.sec_act_listview);
//        ArrayAdapter<String> adapt = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, names);
//        list.setAdapter(adapt);
    }
}
