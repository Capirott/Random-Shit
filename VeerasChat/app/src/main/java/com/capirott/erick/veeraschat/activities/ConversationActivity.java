package com.capirott.erick.veeraschat.activities;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.Toast;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.managers.ChatConversationManager;
import com.capirott.erick.veeraschat.managers.ChatMessageManager;
import com.capirott.erick.veeraschat.managers.ChatUserManager;
import com.capirott.erick.veeraschat.models.ChatMessage;
import com.firebase.ui.auth.AuthUI;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.FirebaseAuth;

public class ConversationActivity extends AppCompatActivity {

    private ListAdapter adapter;
    private ListView listOfMessages = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversation);

        Bundle bundle = getIntent().getExtras();

        String userId = bundle.getString("userId");
        String nickname = bundle.getString("nickname");

        Log.d("ConversationActivity", "Starting conversation with " + nickname);

        listOfMessages = (ListView)findViewById(R.id.list_of_messages);

        ChatConversationManager.createOrUpdate(userId, new Runnable() {
            @Override
            public void run() {
                displayChatMessages();
            }
        });

    }

    private void displayChatMessages() {
        FloatingActionButton fab =
                (FloatingActionButton)findViewById(R.id.fab);

        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText input = (EditText)findViewById(R.id.input);

                // Read the input field and push a new instance
                // of ChatMessage to the Firebase database
                ChatMessage message = new ChatMessage(input.getText().toString(),
                        FirebaseAuth.getInstance()
                                .getCurrentUser()
                                .getUid());
                ChatMessageManager.save(message);
                // Clear the input
                input.setText("");
            }
        });

        adapter = ChatMessageManager.getAdapter(this);
        listOfMessages.setAdapter(adapter);
        listOfMessages.setEmptyView(findViewById(R.id.empty_element));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.conversation_menu, menu);
        MenuItem itemToHide = menu.findItem(R.id.menu_delete_message);
        itemToHide.setVisible(false);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if(item.getItemId() == R.id.menu_sign_out) {
            listOfMessages.setAdapter(null);
            ChatUserManager.createOrUpdate(FirebaseAuth.getInstance().getCurrentUser().getUid(), false, new Runnable() {
                        @Override
                        public void run() {
                            AuthUI.getInstance().signOut(ConversationActivity.this)
                                    .addOnCompleteListener(new OnCompleteListener<Void>() {
                                        @Override
                                        public void onComplete(@NonNull Task<Void> task) {
                                            Toast.makeText(ConversationActivity.this,
                                                    "You have been signed out.",
                                                    Toast.LENGTH_LONG)
                                                    .show();

                                            // Close activity
                                            Intent myIntent = new Intent(ConversationActivity.this, MainActivity.class);
                                            startActivity(myIntent);
                                            finish();
                                        }
                                    });
                        }
                    }
            );

        }
        return true;
    }

}
