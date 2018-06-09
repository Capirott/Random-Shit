package com.capirott.erick.veeraschat.managers;

import android.app.Activity;
import android.text.format.DateFormat;
import android.view.View;
import android.widget.ListAdapter;
import android.widget.TextView;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.models.ChatMessage;
import com.firebase.ui.database.FirebaseListAdapter;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;

public class ChatMessageManager {

    private static final String FIREBASE_REFERENCE = "Messages";

    static public void save(ChatMessage message) {
        FirebaseDatabase.getInstance()
                .getReference(FIREBASE_REFERENCE)
                .push()
                .setValue(message
                );

    }
    static public ChatMessage restore(String id) {
        ChatMessage chat = null;
        FirebaseDatabase.getInstance().getReference(FIREBASE_REFERENCE).child(id);
        DatabaseReference databaseReference = FirebaseDatabase.getInstance().getReference();
        Query query = databaseReference.orderByChild("messageTime").getRef().getDatabase().getReference();

        return chat;
    }

    static public ListAdapter getAdapter(Activity activity) {
        DatabaseReference databaseReference = FirebaseDatabase.getInstance().getReference();
        Query query = databaseReference.orderByChild("messageTime").getRef().getDatabase().getReference(FIREBASE_REFERENCE);
        FirebaseListAdapter<ChatMessage> adapter = new FirebaseListAdapter<ChatMessage>(activity, ChatMessage.class,
                R.layout.message, query) {
            @Override
            protected void populateView(View v, ChatMessage model, int position) {
                // Get references to the views of message.xml
                TextView messageText = (TextView) v.findViewById(R.id.message_text);
                TextView messageUser = (TextView) v.findViewById(R.id.message_user);
                TextView messageTime = (TextView) v.findViewById(R.id.message_time);

                // Set their text
                messageText.setText(model.getText());
                messageUser.setText(model.getUserId());

                // Format the date before showing it
                messageTime.setText(DateFormat.format("dd-MM-yyyy (HH:mm:ss)",
                        model.getTime()));
            }
        };
        return adapter;
    }
}
