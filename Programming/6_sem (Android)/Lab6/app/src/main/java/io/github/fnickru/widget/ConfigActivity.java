package io.github.fnickru.widget;

import android.app.Activity;
import android.appwidget.AppWidgetManager;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.RadioGroup;

public class ConfigActivity extends Activity implements View.OnClickListener {
    private int widgetID = AppWidgetManager.INVALID_APPWIDGET_ID;
    private Intent result;

    final static String WIDGET_PREF = "widget_pref";
    final static String WIDGET_COLOR = "widget_color_";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent intent = getIntent();
        Bundle extras = intent.getExtras();
        if (extras != null) {
            widgetID = extras.getInt(AppWidgetManager.EXTRA_APPWIDGET_ID,
                    AppWidgetManager.INVALID_APPWIDGET_ID);
        }
        if (widgetID == AppWidgetManager.INVALID_APPWIDGET_ID) {
            finish();
        }

        result = new Intent();
        result.putExtra(AppWidgetManager.EXTRA_APPWIDGET_ID, widgetID);
        setResult(RESULT_CANCELED, result);

        setContentView(R.layout.config);
    }

    @Override
    public void onClick(View v) {
        RadioGroup group = findViewById(R.id.colorGroup);
        int checkedRadioButtonId = group.getCheckedRadioButtonId();
        int color = Color.RED;
        switch (checkedRadioButtonId) {
            case R.id.radioRed:
                color = Color.parseColor("#66ff0000");
                break;
            case R.id.radioGreen:
                color = Color.parseColor("#6600ff00");
                break;
            case R.id.radioBlue:
                color = Color.parseColor("#660000ff");
                break;
        }

        SharedPreferences sp = getSharedPreferences(WIDGET_PREF, MODE_PRIVATE);
        Editor editor = sp.edit();
        editor.putInt(WIDGET_COLOR + widgetID, color);
        editor.commit();

        AppWidgetManager appWidgetManager = AppWidgetManager.getInstance(this);
        MyWidget.updateWidget(this, appWidgetManager, widgetID);

        setResult(RESULT_OK, result);
        finish();
    }
}
