package io.github.fnickru.calc;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.math.BigDecimal;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText editText;
    private Integer arg1;
    private Integer arg2;
    private OperationClicked currOp;

    private enum OperationClicked {
        ADD, SUB, MUL, DIV, EQU
    }

    void doOperation() {
        switch (currOp) {
            case ADD: arg1 = arg1 + arg2; break;
            case SUB: arg1 = arg1 - arg2; break;
            case MUL: arg1 = arg1 * arg2; break;
            case DIV: arg1 = arg1 / arg2; break;
        }
        arg2 = 0;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Button button0 = findViewById(R.id.button0);
        final Button button1 = findViewById(R.id.button1);
        final Button button2 = findViewById(R.id.button2);
        final Button button3 = findViewById(R.id.button3);
        final Button button4 = findViewById(R.id.button4);
        final Button button5 = findViewById(R.id.button5);
        final Button button6 = findViewById(R.id.button6);
        final Button button7 = findViewById(R.id.button7);
        final Button button8 = findViewById(R.id.button8);
        final Button button9 = findViewById(R.id.button9);
        final Button buttonC = findViewById(R.id.buttonC);
        final Button buttonA = findViewById(R.id.buttonA);
        final Button buttonS = findViewById(R.id.buttonS);
        final Button buttonM = findViewById(R.id.buttonM);
        final Button buttonD = findViewById(R.id.buttonD);
        final Button buttonE = findViewById(R.id.buttonE);

        editText = findViewById(R.id.editText);

        button0.setOnClickListener(this);
        button1.setOnClickListener(this);
        button2.setOnClickListener(this);
        button3.setOnClickListener(this);
        button4.setOnClickListener(this);
        button5.setOnClickListener(this);
        button6.setOnClickListener(this);
        button7.setOnClickListener(this);
        button8.setOnClickListener(this);
        button9.setOnClickListener(this);
        buttonC.setOnClickListener(this);
        buttonA.setOnClickListener(this);
        buttonS.setOnClickListener(this);
        buttonM.setOnClickListener(this);
        buttonD.setOnClickListener(this);
        buttonE.setOnClickListener(this);

        arg1 = arg2 = 0;
        currOp = OperationClicked.EQU;
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.button0:
            case R.id.button1:
            case R.id.button2:
            case R.id.button3:
            case R.id.button4:
            case R.id.button5:
            case R.id.button6:
            case R.id.button7:
            case R.id.button8:
            case R.id.button9:
                if (currOp == OperationClicked.EQU) {
                    arg1 = 0;
                    currOp = OperationClicked.ADD;
                }
                arg2 = arg2 * 10 + new Integer(((Button)v).getText().toString());
                break;
            case R.id.buttonC:
                arg1 = arg2 = 0;
                currOp = OperationClicked.ADD;
                break;
            case R.id.buttonA: doOperation(); currOp = OperationClicked.ADD; break;
            case R.id.buttonS: doOperation(); currOp = OperationClicked.SUB; break;
            case R.id.buttonM: doOperation(); currOp = OperationClicked.MUL; break;
            case R.id.buttonD: doOperation(); currOp = OperationClicked.DIV; break;
            case R.id.buttonE: doOperation(); currOp = OperationClicked.EQU; break;
        }
        editText.setText(currOp == OperationClicked.EQU ? arg1.toString() : arg2.toString());
    }
}
