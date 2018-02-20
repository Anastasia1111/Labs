package io.github.fnickru.calc;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.math.BigDecimal;

public class MainActivity extends AppCompatActivity {

    private TextView textView;
    private ScientificCalculator calc = ScientificCalculator.INSTANCE;
    private String lastOperand = "";
    private boolean error = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = findViewById(R.id.textView);
    }

    public void onClick(View view) {
        Button button = (Button) view;
        int butId = button.getId();

        String text = textView.getText().toString();

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
                if (error) {
                    text = "";
                    error = false;
                }
                text = text.concat(button.getText().toString());
                lastOperand = lastOperand.concat(button.getText().toString());
                break;

            case R.id.splitter:
                if (!error && !lastOperand.contains(button.getText().toString())) {
                    text = text.concat(button.getText().toString());
                    lastOperand = lastOperand.concat(button.getText().toString());
                }
                break;

            case R.id.openBrack:
            case R.id.clBrack:
                if (error) {
                    text = "";
                    error = false;
                }
                text = text.concat(button.getText().toString());
                lastOperand = "";
                break;

            case R.id.add:
            case R.id.sub:
            case R.id.mul:
            case R.id.div:
                if (!error) text = text.concat(button.getText().toString());
                lastOperand = "";
                break;

            case R.id.mod:
                if (!error) text = text + "%";
                lastOperand = "";
                break;

            case R.id.sin:
            case R.id.cos:
            case R.id.sqrt:
            case R.id.log:
                if (!error) text = text.concat(button.getText().toString() + "(");
                lastOperand = "";
                break;

            case R.id.butC:
                text = "";
                lastOperand = "";
                break;

            case R.id.inv:
                String newOperand;
                if (lastOperand.startsWith("-"))
                    newOperand = lastOperand.replace("-", "");
                else
                    newOperand = "-" + lastOperand;
                text = text.substring(0, text.lastIndexOf(lastOperand)) + newOperand;
                lastOperand = newOperand;
                break;

            case R.id.equal:
                text = text.concat(button.getText().toString());
                if (calc.calculate(text)) {
                    text = calc.result();
                } else {
                    text = calc.errorMessage();
                    error = true;
                }
        }
        textView.setText(text);
    }

}
