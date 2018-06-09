package com.capirott.erick.veeraschat.managers;

import android.app.Activity;
import android.text.format.DateFormat;
import android.view.View;
import android.widget.ListAdapter;
import android.widget.TextView;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.models.ChatMessage;
import com.firebase.ui.database.FirebaseListAdapter;
import com.google.firebase.FirebaseError;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.List;

public class ChatMessageManager {

    private static final String FIREBASE_REFERENCE = "Messages";

    static public void save(ChatMessage message) {
        FirebaseDatabase.getInstance()
                .getReference(FIREBASE_REFERENCE)
                .push()
                .setValue(message
                );

    }

    static public ChatMessage restore(final String id) {

        final List<ChatMessage> events = new ArrayList<>();
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference(FIREBASE_REFERENCE);
        ref.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                for (DataSnapshot snapshot : dataSnapshot.getChildren()) {
                    ChatMessage event = snapshot.getValue(ChatMessage.class);
                    if (snapshot.getKey().equals(id)) {
                        events.add(event);
                    }
                }
            }
            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
        ChatMessage ret = null;
        if (!events.isEmpty())
        {
            ret = events.get(0);
        }
        return ret;
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
                String user = model.getUserId().equals(FirebaseAuth.getInstance().getUid()) ? "You" : "Not You";
                messageUser.setText(user);

                // Format the date before showing it
                messageTime.setText(DateFormat.format("dd-MM-yyyy (HH:mm:ss)",
                        model.getTime()));
            }
        };
        return adapter;
    }
}
