package io.github.fnickru.widget;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.appwidget.AppWidgetManager;
import android.appwidget.AppWidgetProvider;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.SystemClock;
import android.widget.RemoteViews;

import java.text.DateFormat;
import java.util.Date;

public class MyWidget extends AppWidgetProvider {
    private static DateFormat df = DateFormat.getTimeInstance();
    private PendingIntent service;

    @Override
    public void onUpdate(Context context, AppWidgetManager appWidgetManager, int[] appWidgetIds) {
        super.onUpdate(context, appWidgetManager, appWidgetIds);

        final AlarmManager manager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
        final Intent intent = new Intent(context, UpdateService.class);

        if (service == null) {
            service = PendingIntent.getService(context, 0,
                    intent, PendingIntent.FLAG_CANCEL_CURRENT);
        }
        manager.setRepeating(AlarmManager.ELAPSED_REALTIME, SystemClock.elapsedRealtime(), 60000, service);


        for (int id : appWidgetIds) {
            updateWidget(context, appWidgetManager, id);
        }
    }

    @Override
    public void onDeleted(Context context, int[] appWidgetIds) {
        super.onDeleted(context, appWidgetIds);

        Editor editor = context.getSharedPreferences(
                ConfigActivity.WIDGET_PREF, Context.MODE_PRIVATE).edit();
        for (int widgetID : appWidgetIds) {
            editor.remove(ConfigActivity.WIDGET_COLOR + widgetID);
        }
        editor.commit();
    }

    static void updateWidget(Context context, AppWidgetManager appWidgetManager, int widgetID) {
        SharedPreferences sp = context.getSharedPreferences(ConfigActivity.WIDGET_PREF, Context.MODE_PRIVATE);

        int widgetColor = sp.getInt(ConfigActivity.WIDGET_COLOR + widgetID, 0);

        RemoteViews remoteView = new RemoteViews(context.getPackageName(), R.layout.widget);
        remoteView.setTextViewText(R.id.textView, df.format(new Date()));
        remoteView.setInt(R.id.widget_layout, "setBackgroundColor", widgetColor);

        Intent configIntent = new Intent(context, ConfigActivity.class);
        configIntent.setAction(AppWidgetManager.ACTION_APPWIDGET_CONFIGURE);
        configIntent.putExtra(AppWidgetManager.EXTRA_APPWIDGET_ID, widgetID);
        PendingIntent pendingIntent = PendingIntent.getActivity(context, widgetID,
                configIntent, 0);
        remoteView.setOnClickPendingIntent(R.id.textView, pendingIntent);

        appWidgetManager.updateAppWidget(widgetID, remoteView);
    }
}
