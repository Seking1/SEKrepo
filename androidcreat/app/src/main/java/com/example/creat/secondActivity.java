package com.example.creat;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

public class secondActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
    }
    public boolean onCreateOptionsMenu(Menu menu){
        getMenuInflater().inflate(R.menu.main,menu);
        return true;
    }
    @SuppressLint("NonConstantResourceId")
    public boolean onOptionsItemSelected(MenuItem item){
        if(item.getItemId()==R.id.add_item){
            Toast.makeText(secondActivity.this,"add_item_option",Toast.LENGTH_SHORT).show();
        }
        if(item.getItemId()==R.id.remove_item){
            Toast.makeText(secondActivity.this,"remove_item_option",Toast.LENGTH_SHORT).show();
        }
        return true;
    }
}