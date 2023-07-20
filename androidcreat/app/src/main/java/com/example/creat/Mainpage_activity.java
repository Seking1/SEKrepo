package com.example.creat;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class Mainpage_activity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.firstlayout);
        Button button1=(Button)findViewById(R.id.button_diary);
        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent= new Intent(Mainpage_activity.this, Wirtediary_activity.class);
                startActivity(intent);
            }
        });
    }
    public boolean onCreateOptionsMenu(Menu menu){
        getMenuInflater().inflate(R.menu.main,menu);
        return true;
    }
    @SuppressLint("NonConstantResourceId")
    public boolean onOptionsItemSelected(MenuItem item){
        if(item.getItemId()==R.id.add_item){
                    Toast.makeText(Mainpage_activity.this,"add_item_option",Toast.LENGTH_SHORT).show();
                }
        if(item.getItemId()==R.id.remove_item){
                Toast.makeText(Mainpage_activity.this,"remove_item_option",Toast.LENGTH_SHORT).show();
        }
        return true;
    }
}