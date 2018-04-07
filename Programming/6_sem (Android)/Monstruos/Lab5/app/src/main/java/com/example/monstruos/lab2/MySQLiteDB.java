package com.example.monstruos.lab2;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.Random;

public class MySQLiteDB extends SQLiteOpenHelper {

    public static final String TABLE_NAME = "StudTable";

    public MySQLiteDB(Context context){
        super(context, TABLE_NAME,null,1);
    }

    public void onCreate(SQLiteDatabase db) {
        db.execSQL("CREATE TABLE " + TABLE_NAME + " (" +
                "_id INTEGER PRIMARY KEY autoincrement, " +
                "name TEXT, " +
                "weight INTEGER, " +
                "height INTEGER, " +
                "age INTEGER );");

        for(int i = 0; i < 50; ++i) {
            Random rand = new Random();
            Integer randInt = rand.nextInt(5)  + i * 5;
            String st_name = "st" + randInt.toString();
            randInt = rand.nextInt(7) + 18;
            String st_age = randInt.toString();
            randInt = rand.nextInt(40) + 70;
            String st_weight = randInt.toString();
            randInt = rand.nextInt(100) + 140;
            String st_height = randInt.toString();
            db.execSQL("INSERT INTO StudTable ('name', 'weight', 'height', 'age') " +
                    "VALUES ('" + st_name + "', '" + st_weight + "', '" +
                    st_height + "', '" + st_age + "')");

        }
    }
    public void onUpgrade(SQLiteDatabase database, int oldVersion, int newVersion) {
        database.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        database.execSQL("CREATE TABLE StudTable (" +
                "_id INTEGER PRIMARY KEY autoincrement, " +
                "name TEXT, " +
                "weight INTEGER, " +
                "height INTEGER, " +
                "age INTEGER );");
    }
}
