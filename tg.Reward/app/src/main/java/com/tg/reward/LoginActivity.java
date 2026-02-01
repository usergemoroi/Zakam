package com.tg.reward;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.animation.ValueAnimator;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class LoginActivity extends Activity {
    
    private static final String SUPER_KEY = "73D37C08";
    private EditText keyInput;
    private Button startButton;
    private LinearLayout rootLayout;
    private TextView titleText;
    private TextView subtitleText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        createUI();
    }

    private void createUI() {
        rootLayout = new LinearLayout(this);
        rootLayout.setOrientation(LinearLayout.VERTICAL);
        rootLayout.setBackgroundColor(Color.BLACK);
        rootLayout.setPadding(50, 100, 50, 100);
        
        applyGradientBackground();

        titleText = new TextView(this);
        titleText.setText("tg.Reward");
        titleText.setTextSize(42);
        titleText.setTextColor(Color.parseColor("#FF0000"));
        titleText.setTypeface(null, android.graphics.Typeface.BOLD);
        titleText.setPadding(0, 50, 0, 20);
        titleText.setGravity(android.view.Gravity.CENTER);
        
        LinearLayout.LayoutParams titleParams = new LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.WRAP_CONTENT
        );
        titleParams.setMargins(0, 0, 0, 30);
        titleText.setLayoutParams(titleParams);
        
        animateText(titleText);

        subtitleText = new TextView(this);
        subtitleText.setText("Система аутентификации");
        subtitleText.setTextSize(18);
        subtitleText.setTextColor(Color.parseColor("#CCCCCC"));
        subtitleText.setPadding(0, 0, 0, 40);
        subtitleText.setGravity(android.view.Gravity.CENTER);
        
        LinearLayout.LayoutParams subtitleParams = new LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.WRAP_CONTENT
        );
        subtitleParams.setMargins(0, 0, 0, 50);
        subtitleText.setLayoutParams(subtitleParams);

        keyInput = new EditText(this);
        keyInput.setHint("Введите ключ...");
        keyInput.setTextColor(Color.WHITE);
        keyInput.setHintTextColor(Color.parseColor("#666666"));
        keyInput.setTextSize(18);
        keyInput.setPadding(30, 30, 30, 30);
        
        GradientDrawable inputBg = new GradientDrawable();
        inputBg.setColor(Color.parseColor("#1A1A1A"));
        inputBg.setStroke(2, Color.parseColor("#FF0000"));
        inputBg.setCornerRadius(15);
        keyInput.setBackground(inputBg);
        
        LinearLayout.LayoutParams inputParams = new LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.WRAP_CONTENT
        );
        inputParams.setMargins(0, 0, 0, 30);
        keyInput.setLayoutParams(inputParams);

        keyInput.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                if (s.toString().equals(SUPER_KEY)) {
                    enableStartButton();
                } else {
                    disableStartButton();
                }
            }

            @Override
            public void afterTextChanged(Editable s) {}
        });

        startButton = new Button(this);
        startButton.setText("СТАРТ");
        startButton.setTextSize(20);
        startButton.setTextColor(Color.parseColor("#666666"));
        startButton.setTypeface(null, android.graphics.Typeface.BOLD);
        startButton.setPadding(40, 30, 40, 30);
        startButton.setEnabled(false);
        
        GradientDrawable buttonBg = new GradientDrawable();
        buttonBg.setColor(Color.parseColor("#2A2A2A"));
        buttonBg.setCornerRadius(15);
        startButton.setBackground(buttonBg);
        
        LinearLayout.LayoutParams buttonParams = new LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.WRAP_CONTENT
        );
        buttonParams.setMargins(0, 30, 0, 0);
        startButton.setLayoutParams(buttonParams);

        startButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (keyInput.getText().toString().equals(SUPER_KEY)) {
                    animateTransition();
                } else {
                    Toast.makeText(LoginActivity.this, "Неверный ключ!", Toast.LENGTH_SHORT).show();
                }
            }
        });

        rootLayout.addView(titleText);
        rootLayout.addView(subtitleText);
        rootLayout.addView(keyInput);
        rootLayout.addView(startButton);
        
        setContentView(rootLayout);
    }

    private void applyGradientBackground() {
        GradientDrawable gradient = new GradientDrawable(
            GradientDrawable.Orientation.TOP_BOTTOM,
            new int[] {
                Color.parseColor("#0D0D0D"),
                Color.parseColor("#1A0000"),
                Color.parseColor("#0D0D0D")
            }
        );
        rootLayout.setBackground(gradient);
    }

    private void enableStartButton() {
        startButton.setEnabled(true);
        startButton.setTextColor(Color.WHITE);
        
        GradientDrawable enabledBg = new GradientDrawable();
        enabledBg.setColors(new int[] {
            Color.parseColor("#FF0000"),
            Color.parseColor("#CC0000")
        });
        enabledBg.setOrientation(GradientDrawable.Orientation.LEFT_RIGHT);
        enabledBg.setCornerRadius(15);
        startButton.setBackground(enabledBg);
        
        animateButton(startButton);
    }

    private void disableStartButton() {
        startButton.setEnabled(false);
        startButton.setTextColor(Color.parseColor("#666666"));
        
        GradientDrawable disabledBg = new GradientDrawable();
        disabledBg.setColor(Color.parseColor("#2A2A2A"));
        disabledBg.setCornerRadius(15);
        startButton.setBackground(disabledBg);
    }

    private void animateText(final TextView textView) {
        textView.setAlpha(0f);
        textView.animate()
            .alpha(1f)
            .setDuration(1000)
            .setInterpolator(new AccelerateDecelerateInterpolator())
            .start();
    }

    private void animateButton(final View button) {
        ValueAnimator scaleAnimator = ValueAnimator.ofFloat(1f, 1.05f, 1f);
        scaleAnimator.setDuration(500);
        scaleAnimator.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
            @Override
            public void onAnimationUpdate(ValueAnimator animation) {
                float scale = (float) animation.getAnimatedValue();
                button.setScaleX(scale);
                button.setScaleY(scale);
            }
        });
        scaleAnimator.start();
    }

    private void animateTransition() {
        rootLayout.animate()
            .alpha(0f)
            .setDuration(500)
            .setListener(new AnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(Animator animation) {
                    Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                    startActivity(intent);
                    finish();
                }
            })
            .start();
    }
}
