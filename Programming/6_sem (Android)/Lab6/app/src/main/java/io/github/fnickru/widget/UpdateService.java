package io.github.fnickru.widget;

import android.app.Service;
import android.appwidget.AppWidgetManager;
import android.content.ComponentName;
import android.content.Intent;
import android.os.IBinder;
import android.support.annotation.Nullable;
import android.widget.RemoteViews;

import java.text.DateFormat;
import java.util.Date;

public class UpdateService extends Service {
    private static DateFormat df = DateFormat.getTimeInstance();

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        RemoteViews view = new RemoteViews(getPackageName(), R.layout.widget);
        view.setTextViewText(R.id.textView, df.format(new Date()));

        ComponentName widget = new ComponentName(this, MyWidget.class);
        AppWidgetManager manager = AppWidgetManager.getInstance(this);
        manager.updateAppWidget(widget, view);

        return super.onStartCommand(intent, flags, startId);
    }
}
