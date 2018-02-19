package com.example.monstruos.calc;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private Double Buffer = 0.0;
    private Double Result = 0.0;
    private Integer doubleSign = 0;
    private Integer brackNumber = 0;
    private String sign = "";
    private String text = "";
    private boolean numPrint = false;
    private boolean isDouble = false;
    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.textView);
    }

    public void onClick(View view) {
        Button button = (Button) view;
        int butId = button.getId();

        if(text.indexOf("=") == -1) {
            // take all except sign
            text = textView.getText().toString().substring(0, text.length() - sign.length());
        } else {
            text = String.valueOf(Result);
        }

        switch(butId) {
            case R.id.num0:
            case R.id.num1:
            case R.id.num2:
            case R.id.num3:
            case R.id.num4:
            case R.id.num5:
            case R.id.num6:
            case R.id.num7:
            case R.id.num8:
            case R.id.num9:
                if(!numPrint) {
                    Buffer = 0.0;
                    doubleSign = 0;
                    numPrint = true;
                    isDouble = false;
                    sign = "";
                } else {
                    if (Buffer == 0.0 && !isDouble) { // "00000012" -> "12"
                        text = text.substring(0, text.length() - 1);
                    }
                }

                if(isDouble) {
                    doubleSign++;
                    Buffer = Buffer + Integer.valueOf(button.getText().toString()) / Math.pow(10.0, doubleSign);
                }
                else
                    Buffer = Buffer * 10 + Integer.valueOf(button.getText().toString());

                textView.setText(text + sign + button.getText().toString());
                break;

            case R.id.splitter:
                if(numPrint && !isDouble) {
                    textView.setText(text + ".");
                    isDouble = true;
                }
                break;

            case R.id.add:
            case R.id.sub:
            case R.id.mul:
            case R.id.div:
                numPrint = false;
                sign = button.getText().toString();
                textView.setText(text + sign);
                break;

            case R.id.equal:
                if(!numPrint) {
                    text = text + sign + String.valueOf(Buffer);
                }
                if(brackNumber > 0 || text.endsWith(")")) {
                    for(Integer i = 0; i < brackNumber; ++i) {
                        text = text + ")";
                    }
                    sign = "";
                    Buffer = 0.0;
                }
                //Double res = Calc.calculating(text);
                //textView.setText(text + "=" + String.valueOf(res));

                break;

            case R.id.mod:
                numPrint = false;
                sign = "%";
                textView.setText(text + sign);
                break;

            case R.id.sin:
                numPrint = false;
                sign = "sin(";
                textView.setText(text + sign);
                brackNumber++;
                break;

            case R.id.cos:
                numPrint = false;
                sign = "cos(";
                textView.setText(text + sign);
                brackNumber++;
                break;

            case R.id.sqrt:
                numPrint = false;
                sign = "sqrt(";
                textView.setText(text + sign);
                brackNumber++;
                break;

            case R.id.log:
                numPrint = false;
                sign = "log(";
                textView.setText(text + sign);
                brackNumber++;
                break;

            case R.id.butC:
                Buffer = 0.0;
                doubleSign = 0;
                brackNumber = 0;
                numPrint = false;
                isDouble = false;
                textView.setText("");
                break;

            case R.id.openBrack:
                if(!numPrint) {
                    numPrint = false;
                    textView.setText(text + "(");
                    brackNumber++;
                }
                break;

            case R.id.clBrack:
                if(numPrint && brackNumber > 0) {
                    numPrint = false;
                    textView.setText(text + ")");
                    brackNumber--;
                }
                break;

            case R.id.unarSub:
                if(numPrint) {
                    if (Buffer > 0) {
                        text = text.substring(0, text.length() - String.format("%.0f", Buffer).length()) + "(" +
                                String.format("%.0f", Buffer).length();

                    } else {
                        text = text.substring(0, text.length() - String.format("%.0f", Buffer).length() - 2)
                                + String.format("%.0f", Buffer).length();
                    }
                    Buffer *= -1;
                }
                textView.setText(text);
                break;
        }
    }

}
