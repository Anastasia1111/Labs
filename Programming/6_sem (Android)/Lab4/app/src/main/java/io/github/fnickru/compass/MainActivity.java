package io.github.fnickru.compass;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends Activity implements SensorEventListener {

    private float currentDegree = 0f;
    private ImageView imageView;
    private TextView header;

    private SensorManager sensorManager;
    private Sensor compass;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        imageView = findViewById(R.id.imageViewCompass);
        header = findViewById(R.id.header);
        header.setText(String.format(getResources().getString(R.string.header_text), 0.0));

        sensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
        compass = sensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
        if(compass != null) {
            sensorManager.registerListener(this, compass, SensorManager.SENSOR_DELAY_NORMAL);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        sensorManager.registerListener(this, compass, SensorManager.SENSOR_DELAY_NORMAL);
    }

    @Override
    protected void onPause() {
        super.onPause();

        sensorManager.unregisterListener(this);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        float azimut = event.values[0];
        header.setText(String.format(getResources().getString(R.string.header_text), azimut));

        RotateAnimation ra = new RotateAnimation(
                currentDegree,
                -azimut,
                Animation.RELATIVE_TO_SELF, 0.5f,
                Animation.RELATIVE_TO_SELF, 0.5f);

        ra.setDuration(50);

        ra.setFillAfter(true);

        imageView.startAnimation(ra);
        currentDegree = -azimut;
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {
    }
}
