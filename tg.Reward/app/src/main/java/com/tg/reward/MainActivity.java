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
            android.content.pm.PackageManager pm = getPackageManager();
            Intent intent = pm.getLaunchIntentForPackage("com.axlebolt.standoff2");
            
            if (intent == null) {
                try {
                    pm.getPackageInfo("com.axlebolt.standoff2", 0);
                    intent = new Intent();
                    intent.setClassName("com.axlebolt.standoff2", "com.axlebolt.standoff2.MainActivity");
                    Toast.makeText(this, "SO2 обнаружен, запуск альтернативным методом", Toast.LENGTH_SHORT).show();
                } catch (android.content.pm.PackageManager.NameNotFoundException e) {
                    Toast.makeText(this, "SO2 не установлен. Установите Standoff 2 для использования меню", Toast.LENGTH_LONG).show();
                    return;
                }
            }
            
            if (intent != null) {
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
                Toast.makeText(this, "Запуск SO2 с Tg.Revard", Toast.LENGTH_SHORT).show();
                
                Intent menuServiceIntent = new Intent(this, Menu.class);
                startService(menuServiceIntent);
            }
        } catch (Exception e) {
            Toast.makeText(this, "Ошибка запуска SO2: " + e.getMessage(), Toast.LENGTH_SHORT).show();
        }
    }
}
