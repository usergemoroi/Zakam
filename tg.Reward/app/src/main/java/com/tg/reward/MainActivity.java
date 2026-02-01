package com.tg.reward;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("tgReward");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        redirectToSO2();
    }

    private void redirectToSO2() {
        try {
            Intent intent = getPackageManager().getLaunchIntentForPackage("com.axlebolt.standoff2");
            if (intent != null) {
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
                Toast.makeText(this, "Запуск SO2 с tg.Reward", Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(this, "SO2 не установлен", Toast.LENGTH_LONG).show();
            }
        } catch (Exception e) {
            Toast.makeText(this, "Ошибка запуска SO2", Toast.LENGTH_SHORT).show();
        }
    }
}
