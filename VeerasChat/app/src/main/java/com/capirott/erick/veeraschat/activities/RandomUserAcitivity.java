package com.capirott.erick.veeraschat.activities;

import android.content.Intent;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.ListAdapter;
import android.widget.ListView;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.managers.ChatMessageManager;
import com.capirott.erick.veeraschat.managers.ChatUserManager;
import com.capirott.erick.veeraschat.models.ChatMessage;
import com.capirott.erick.veeraschat.models.ChatUser;
import com.google.firebase.auth.FirebaseAuth;

public class RandomUserAcitivity extends AppCompatActivity {

    private ListAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_random_user_acitivity);
        displayUsers();
    }

    private void displayUsers() {
        ListView listOfMessages = (ListView)findViewById(R.id.list_of_random_users);
        adapter = ChatUserManager.getAdapter(this);
        listOfMessages.setAdapter(adapter);
        listOfMessages.setEmptyView(findViewById(R.id.empty_element));
        listOfMessages.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                ChatUser user = (ChatUser) adapter.getItem(i);
                Log.d("RandomUserAcitivity", "Clicked on " + user.getNickname());
                Bundle bundle = new Bundle();
                bundle.putString("userId", user.getId());
                bundle.putString("nickname", user.getNickname());
                Intent myIntent = new Intent(RandomUserAcitivity.this, ConversationActivity.class);
                myIntent.putExtras(bundle);
                startActivity(myIntent);
            }
        });
    }
}
