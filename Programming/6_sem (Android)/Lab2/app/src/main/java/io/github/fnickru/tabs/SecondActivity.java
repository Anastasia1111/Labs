package io.github.fnickru.tabs;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class SecondActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sec);

        ListView list = findViewById(R.id.list_view);
        ArrayAdapter<String> adapt = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, new String[]{
                "First string", "Вторая строка", "Troisième ligne", "Quarta acie"
        });
        list.setAdapter(adapt);
    }
}
