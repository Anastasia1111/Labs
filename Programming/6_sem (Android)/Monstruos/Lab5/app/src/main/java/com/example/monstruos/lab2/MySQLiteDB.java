package com.example.monstruos.lab2;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

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
    }
    public void onUpgrade(SQLiteDatabase database, int oldVersion, int newVersion) {
        database.execSQL("DROP TABLE IS EXISTS " + TABLE_NAME);
        database.execSQL("CREATE TABLE StudTable (" +
                "_id INTEGER PRIMARY KEY autoincrement, " +
                "name TEXT, " +
                "weight INTEGER, " +
                "height INTEGER, " +
                "age INTEGER );");
    }
}
