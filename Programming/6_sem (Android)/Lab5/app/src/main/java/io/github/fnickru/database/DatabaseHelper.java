package io.github.fnickru.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DatabaseHelper extends SQLiteOpenHelper {
    public static final String DATABASE_NAME = "studentdb";
    public static final int DATABASE_VERSION = 1;
    public static final String TABLE_NAME = "students";
    public static final String CREATE_TABLE =
                    "CREATE TABLE IF NOT EXISTS " +
                    TABLE_NAME +
                    "(id INTEGER PRIMARY KEY AUTOINCREMENT," +
                    "name TEXT," +
                    "weight INTEGER, " +
                    "height INTEGER, " +
                    "age INTEGER)";
    public static final String DELETE_TABLE = "DROP TABLE IF EXISTS " + TABLE_NAME;

    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);

    }

    public void onCreate(SQLiteDatabase db) {
        db.execSQL(CREATE_TABLE);

    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL(DELETE_TABLE);

        onCreate(db);
    }

    public void insertData(String name, int weight, int height, int age) {
        SQLiteDatabase db = this.getWritableDatabase();

        db.beginTransaction();

        try {
            ContentValues values;
            values = new ContentValues();
            values.put("name", name);
            values.put("weight", weight);
            values.put("height", height);
            values.put("age", age);
            db.insert(TABLE_NAME, null, values);
            db.setTransactionSuccessful();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            db.endTransaction();
            db.close();
        }
    }


}
